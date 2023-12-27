
#include <cstdlib>
#include <COGE/datas/DataLoader.hpp>
#include <COGE/Macros.h>

std::string COGE::typeToString(DATA_TYPE data_type)
{
	if(data_type==DATA_TYPE::COGE_DEFAULT) return "COGE_DEFAULT";
	else if(data_type==DATA_TYPE::COGE_MODEL) return "COGE_MODEL";
	else if(data_type==DATA_TYPE::COGE_SHADER) return "COGE_SHADER";
	else if(data_type==DATA_TYPE::COGE_TEXTURE) return "COGE_TEXTURE";
	else if(data_type==DATA_TYPE::COGE_EVENT) return "COGE_EVENT";
	else if(data_type==DATA_TYPE::COGE_ANIMATION) return "COGE_ANIMATION";
	else return "COGE_???";
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
		DATA_TYPE data_type = DATA_TYPE::COGE_DEFAULT; unsigned int name_size = 0; _FILESIZE data_size = 0;
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

COGE::DataLoader::DataLoader(std::vector<std::string> file_paths)
{
	for(std::vector<std::string>::iterator iter = file_paths.begin();iter!=file_paths.end();iter++)
	{
		files.push_back(DataFile(*iter));
		files[files.size()-1].scan(model_references,shader_references);
	}
}

void COGE::DataLoader::addFile(std::string data_path)
{
	files.push_back(DataFile(data_path));
	files[files.size()-1].scan(model_references,shader_references);
}

GLS::MODEL* COGE::DataLoader::load_model(std::string name)
{
	char* data = nullptr;
	for(unsigned int i = 0;i<model_references.size();i++) 
		if(model_references[i].name == name) 
			data = (char*)files[model_references[i].file_id].read(model_references[i]);
	if (data == nullptr)
	{
		WARN("SEARCHED DATA REFERENCE IS NOT FOUNDED IN MODELS:'" << name << "'");
		return new GLS::MODEL(0,nullptr,0,nullptr);
	}

	unsigned int *vertice_size = (unsigned int*)data;
	float* vertices = (float*)(data+sizeof(unsigned int));

	unsigned int *indice_size = (unsigned int*)(data+sizeof(unsigned int)+*vertice_size);
	unsigned int* indices = &indice_size[1];

	/*GLS::MODEL model;
	model.vertice_size = *vertice_size; model.indice_size = *indice_size;
	model.vertices = (float*)malloc(model.vertice_size);
	model.indices = (unsigned int*)malloc(model.indice_size);

	memcpy(model.vertices, vertices, model.vertice_size);
	memcpy(model.indices, indices, model.indice_size);*/


	GLS::MODEL* model = new GLS::MODEL(*vertice_size,vertices,*indice_size,indices);
	free(data);
	LOG("MODEL LOADED '" << name << "' vertice_size:" << model->vertice_size << " indice_size:" << model->indice_size);
	return model;
}

GLS::ShaderText COGE::DataLoader::read_shader(std::string name)
{
	char* data = nullptr;
	_FILESIZE size = 0;
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

	LOG("REFERENCE FOUND.");
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