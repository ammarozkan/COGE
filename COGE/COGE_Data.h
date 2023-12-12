//  COGE DATA STYLE:
/*

COGE can handle the datas from only one data file. Data style shall be:
[DATAHEADER]=[GENERIC_TYPE][GENERIC_DATA_COUNT]
[DATA1_TYPE][DATA1_NAME_SIZE][DATA1_NAME][DATA1_SIZE][DATA1]
[DATA2_TYPE][DATA2_NAME_SIZE][DATA2_NAME][DATA2_SIZE][DATA2]
...


COGE_MODEL
	COGE handles model datas in a byte order. The first 4 bytes of data tells
the size of vertices to the reader. And after the vertices, another 4 bytes
will came out. These 4 bytes shall tell size of the indices to the reader.
So order is always important. Reader shall be capable of handling that.

	For more standart model initializion, define of a vertex buffer
will be: [aPos]vec3(3*float) + [TexCoord]vec2(2*float) + [BoneBind]vec1(1*float)


COGE_SHADER
	COGE handles shader datas as only bunch of texts. Just seperating 
vertex and fragment by #GLSL_Fragment and #GLSL_Vertex lines.


//TODO
COGE_MAPPROP_EXPLANATOR
	COGE puts the props of the map by that explanator. This explanator
refers to position and the model of static props on the map. COGE just
generates them by looking to player position.

	The Standard : [Position]vec3(3*float) + [specs]byte(bruh)

COGE_BONE_ANIMATION
	COGE scans COGE_BONE_ANIMATION and creates an animation for bones.
And creates matrixes for bones. Then uses shaders to move bone binded
vertexes.
*/

#ifdef COGE_EDITOR

#ifndef COGE_TEMP_DATA_EXTENSION
#define COGE_TEMP_DATA_EXTENSION ".COGE.temp"
#endif
#ifndef COGE_DATA_EXTENSION
#define COGE_DATA_EXTENSION ".COGE"
#endif

#endif


namespace COGE
{
	enum DATA_TYPE
	{
		COGE_DEFAULT, COGE_MODEL, COGE_SHADER, COGE_TEXTURE, COGE_EVENT, COGE_ANIMATION
	};
	std::string typeToString(DATA_TYPE data_type)
	{
		if(data_type==DATA_TYPE::COGE_DEFAULT) return "COGE_DEFAULT";
		else if(data_type==DATA_TYPE::COGE_MODEL) return "COGE_MODEL";
		else if(data_type==DATA_TYPE::COGE_SHADER) return "COGE_SHADER";
		else if(data_type==DATA_TYPE::COGE_TEXTURE) return "COGE_TEXTURE";
		else if(data_type==DATA_TYPE::COGE_EVENT) return "COGE_EVENT";
		else if(data_type==DATA_TYPE::COGE_ANIMATION) return "COGE_ANIMATION";
		else return "COGE_???";
	}

	struct Reference
	{
		unsigned int file_id;
		long int where;
		unsigned int size;
		std::string name;
	};

	class DataFile
	{
	private:
		std::ifstream in_file;
		DATA_TYPE generic_type = DATA_TYPE::COGE_DEFAULT;
		unsigned int data_count = 0,file_id = 0;
	public:
		DataFile(std::string file_path);

		void scan(std::vector<Reference> &model_references, std::vector<Reference> &shader_references);
		void* read(Reference ref);
	};

	class DataReader
	{
	private:
		std::vector<DataFile> files;
		std::vector<Reference> model_references, shader_references;
	public:
		DataReader(std::vector<std::string> file_paths = std::vector<std::string>());
		void addFile(std::string file_path);
		GLS::MODEL read_model(std::string name);
		GLS::ShaderText read_shader(std::string name);
	};

#ifdef COGE_EDITOR
	class DataPacker
	{
	private:
		std::fstream temp_file;
		unsigned int data_count = 0;
		std::string file_name;
		std::vector<DATA_TYPE> included_types;
	public:
		DataPacker(std::string file_name); // file_name should be putten here without file extension

		void addData(DATA_TYPE type, std::string name, unsigned int data_size, void* data);
		void addModelData(std::string name, GLS::MODEL model);
		void addShaderData(std::string name, std::string shader_code);
		void addShaderData_fromFile(std::string name, std::string shader_path);

		void pack(); // sets the data header and closes file. And wholah! Flush the data!
	};
#endif
}


//// Functions


////	DataFile

COGE::DataFile::DataFile(std::string file_path) :
	in_file(file_path,std::ios::binary)
{
	if(!in_file)
	{
		WARN("FILE " << file_path << " COULD NOT BE OPENED.");
	}
	static unsigned int stat_file_id = 0;
	this->file_id = stat_file_id;
}

void COGE::DataFile::scan(std::vector<Reference> &model_references, std::vector<Reference> &shader_references)
{
	in_file.read(reinterpret_cast<char*>(&generic_type),sizeof(generic_type));
	in_file.read(reinterpret_cast<char*>(&data_count),sizeof(data_count));
	LOG("FILE HEADER SCAN RESULTS:data_count=" << data_count << "generic_type=" << typeToString(generic_type));
	for(unsigned int i = 0;i<data_count&&!in_file.eof();i++)
	{
		DATA_TYPE data_type = DATA_TYPE::COGE_DEFAULT; unsigned int name_size = 0, data_size = 0;
		in_file.read(reinterpret_cast<char*>(&data_type),sizeof(DATA_TYPE));
		in_file.read(reinterpret_cast<char*>(&name_size),sizeof(unsigned int));
		char* name_cstr = (char*)malloc(name_size+1);
		in_file.read(name_cstr,name_size);
		name_cstr[name_size] = '\0';
		in_file.read(reinterpret_cast<char*>(&data_size),sizeof(data_size));

		Reference ref = {file_id, in_file.tellg(), data_size, std::string(name_cstr)};
		if(data_type == DATA_TYPE::COGE_MODEL) model_references.push_back(ref);
		else if(data_type == DATA_TYPE::COGE_SHADER) shader_references.push_back(ref);
		else WARN("READER READED AN UNDEFINED DATA_TYPE=" << data_type);

		LOG("<REFERENCE:'" << ref.name << "' \t type:" << typeToString(data_type) << "\t in " << ref.where << ">");

		in_file.seekg(in_file.tellg() + data_size);
	}
}

void* COGE::DataFile::read(Reference ref)
{
	in_file.seekg(ref.where);
	void* data = malloc(ref.size);
	in_file.read(reinterpret_cast<char*>(data),ref.size);
	return data;
}

////	DataReader

COGE::DataReader::DataReader(std::vector<std::string> file_paths)
{
	for(std::vector<std::string>::iterator iter = file_paths.begin();iter!=file_paths.end();iter++)
	{
		files.push_back(DataFile(*iter));
		files[files.size()-1].scan(model_references,shader_references);
	}
}

void COGE::DataReader::addFile(std::string data_path)
{
	files.push_back(DataFile(data_path));
	files[files.size()-1].scan(model_references,shader_references);
}

GLS::MODEL COGE::DataReader::read_model(std::string name)
{
	void* data = nullptr;
	for(unsigned int i = 0;i<model_references.size();i++) 
		if(model_references[i].name == name) 
			data = files[model_references[i].file_id].read(model_references[i]);
	if (data == nullptr)
	{
		WARN("SEARCHED DATA REFERENCE IS NOT FOUNDED IN MODELS:'" << name << "'");
		return GLS::MODEL(0,nullptr,0,nullptr);
	}

	unsigned int *vertice_size = (unsigned int*)data;
	float* vertices = (float*)(data+sizeof(unsigned int));

	unsigned int *indice_size = (unsigned int*)(data+sizeof(unsigned int)+*vertice_size);
	unsigned int* indices = &indice_size[1];

	GLS::MODEL model(*vertice_size,vertices,*indice_size,indices);
	LOG("MODEL LOADED '" << name << "' vertice_size:" << model.vertice_size << " indice_size:" << model.indice_size);
	return model;
}

GLS::ShaderText COGE::DataReader::read_shader(std::string name)
{
	char* data = nullptr;
	unsigned int size = 0;
	for(unsigned int i = 0;i<shader_references.size();i++) 
	{
		if(!name.compare(shader_references[i].name)) 
		{
			data = (char*)files[shader_references[i].file_id].read(shader_references[i]);
			size = shader_references[i].size;
			break;
		}
	}
	if (data == nullptr)
	{
		WARN("SEARCHED DATA REFERENCE IS NOT FOUNDED IN SHADERS:'" << name << "'");
		return {"",""};
	}

	LOG("REFERENCE FOUND.")
	char* start = &data[0];
	std::string vertex_shader = "",fragment_shader = "";
	std::string control = ""; bool shaderSwitch = false; // false if vertex is wanted, otherwise fragment shall be usen

	for(;data-start<size;data++)
	{
		if(*data=='\n')
		{
			if(control == "#GLSL_vertex") shaderSwitch = false;
			else if(control == "#GLSL_fragment") shaderSwitch = true;
			else
			{
				control+="\n";
				if(shaderSwitch == false) vertex_shader+=control;
				else fragment_shader+=control;
			}
			control = "";
		}
		else control+=*data;
	}
	return {vertex_shader+'\0',fragment_shader+'\0'};
}

#ifdef COGE_EDITOR
////	DataPacker
COGE::DataPacker::DataPacker(std::string file_name) :
	temp_file(file_name+COGE_TEMP_DATA_EXTENSION,std::ios::binary | std::ios::app)
{
	if(!temp_file)
	{
		LOG("eof():" << temp_file.eof() << ", fail()" << temp_file.fail() << ", bad()" << temp_file.bad());
		WARN("TEMP FILE "<< file_name << COGE_TEMP_DATA_EXTENSION <<" COULD NOT BE OPENED.");
		return;
	}
	this->file_name = file_name;
	E_LOG("WRITING THE VIRTUAL HEADER FOR " << file_name << COGE_TEMP_DATA_EXTENSION << ".");
	COGE::DATA_TYPE def = COGE::DATA_TYPE::COGE_DEFAULT;
	temp_file.write(reinterpret_cast<char*>(&def),sizeof(COGE::DATA_TYPE));
	temp_file.write(reinterpret_cast<char*>(&data_count),sizeof(unsigned int));
	E_LOG("VIRTUAL HEADER FOR " << file_name << COGE_TEMP_DATA_EXTENSION << " COMPLETE.");
}

void COGE::DataPacker::addData(COGE::DATA_TYPE type, std::string name, unsigned int data_size, void* data)
{
	// Append data to out_file
	temp_file.write(reinterpret_cast<char*>(&type), sizeof(DATA_TYPE));
	unsigned int name_size = name.size();
	temp_file.write(reinterpret_cast<char*>(&name_size), sizeof(unsigned int));
	temp_file.write(reinterpret_cast<char*>((char*)name.c_str()), sizeof(char)*name_size);
	temp_file.write(reinterpret_cast<char*>(&data_size), sizeof(unsigned int));
	temp_file.write(reinterpret_cast<char*>(data), data_size);
	data_count++;
	LOG("DATA " << name << " IS LOADED TO " << file_name << ".\n");
}


void COGE::DataPacker::addModelData(std::string name, GLS::MODEL model)
{
	unsigned int data_size = sizeof(unsigned int)+model.vertice_size+sizeof(unsigned int)+model.indice_size;
	char* model_data = (char*)malloc(data_size);

	memcpy((void*)model_data, (void*)&model.vertice_size, sizeof(unsigned int));

	char* vertices_pos = model_data+sizeof(unsigned int);
	memcpy((void*)vertices_pos,(void*)model.vertices, model.vertice_size);

	char* indice_size_pos = vertices_pos+model.vertice_size;
	memcpy((void*)indice_size_pos, (void*)&model.indice_size,sizeof(unsigned int));

	char* indices_pos = indice_size_pos+sizeof(unsigned int);
	memcpy((void*)indices_pos, (void*)model.indices, model.indice_size);

	addData(COGE::DATA_TYPE::COGE_MODEL,name,data_size,(void*)model_data);
}

void COGE::DataPacker::addShaderData(std::string name, std::string shader_code)
{
	addData(COGE::DATA_TYPE::COGE_SHADER,name,shader_code.size(),(void*)shader_code.c_str());
}

void COGE::DataPacker::addShaderData_fromFile(std::string name, std::string shader_path)
{
	std::ifstream shader_file(shader_path);
	std::string shader_code = "";
	for(std::string line;std::getline(shader_file, line);) if((line.size() < 2) || (line[0] != '/' && line[1] != '/'))shader_code+=line+"\n";
	//E_LOG("SHADER FROM " << shader_path << " IS LOADED. \n" << shader_code);
	addShaderData(name,shader_code);
}

void COGE::DataPacker::pack()
{
	temp_file.close();

	if(remove((file_name+COGE_DATA_EXTENSION).c_str())) WARN("REAL " << file_name + COGE_DATA_EXTENSION << " COULD NOT BE REMOVED.")
	std::ofstream file(file_name+COGE_DATA_EXTENSION, std::ios::binary);
	if(!file)
	{
		WARN("FILE "<< file_name << COGE_DATA_EXTENSION << " COULD NOT BE OPENED. (maybe it is opened in another thing?)");
		return;
	}

	// writing the header
	COGE::DATA_TYPE def = COGE::DATA_TYPE::COGE_DEFAULT;
	file.write(reinterpret_cast<char*>(&def),sizeof(COGE::DATA_TYPE));
	file.write(reinterpret_cast<char*>(&data_count),sizeof(unsigned int));

	std::ifstream temp_file_read(file_name+COGE_TEMP_DATA_EXTENSION,std::ios::binary);
	temp_file_read.seekg(sizeof(COGE::DATA_TYPE)+sizeof(unsigned int));
	char pDat;

	while(true)
	{
		temp_file_read.read(&pDat,1);
		if(temp_file_read.eof()) break;
		file.write(&pDat,1);
	} // Copying exact same things from temp to real file
	E_LOG(std::endl << " WRITING COMPLETE.");

	temp_file_read.close();
	if(remove((file_name+COGE_TEMP_DATA_EXTENSION).c_str())) WARN("TEMP " << file_name << COGE_TEMP_DATA_EXTENSION << " COULD NOT BE REMOVED.");
	file.close();

	LOG("PACK OF '" << file_name + COGE_DATA_EXTENSION << "' COMPLETE");
}
#endif