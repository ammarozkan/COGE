
#include <cstdlib>
#include <cstring>
#include <COGE/datas/DataLoader.hpp>
#include <COGE/Macros.h>

COGE::FreeFetcher::FreeFetcher(void* pointer)
{
	first = this->pointer = (char*)pointer;
}

unsigned int COGE::FreeFetcher::wh()
{
	return pointer-first;
}

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

void COGE::DataFile::scan(std::unordered_map<std::string,Reference> &model_references, std::unordered_map<std::string,Reference> &shader_references)
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

		std::string ref_name(name_cstr);
		Reference ref = {file_id, in_file.tellg(), data_size};

		if(data_type == DATA_TYPE::COGE_MODEL) model_references[ref_name] = ref;
		else if(data_type == DATA_TYPE::COGE_SHADER) shader_references[ref_name] = ref; //shader_references.push_back(ref);
		else WARN("READER READED AN UNDEFINED DATA_TYPE=" << data_type);

		LOG("<REFERENCE:'" << ref_name << "' \t type:" << typeToString(data_type) << "\t in " << ref.where << ">");

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
	if(model_references.find(name) == model_references.end()) return new GLS::MODEL(0,nullptr,0,nullptr);
	Reference& ref = model_references[name];
	data = (char*)files[ref.file_id].read(ref);

	if (data == nullptr)
	{
		WARN("SEARCHED DATA REFERENCE IS NOT FOUNDED IN MODELS:'" << name << "'");
		return new GLS::MODEL(0,nullptr,0,nullptr);
	}
	FreeFetcher ff((void*)data);
	unsigned int *vertice_size = ff.fetch<unsigned int>();
	float* vertices = ff.fetch<float>(*vertice_size/sizeof(float));

	unsigned int *indice_size = ff.fetch<unsigned int>();
	unsigned int* indices = ff.fetch<unsigned int>(*indice_size);

	GLS::MODEL* model = new GLS::MODEL(*vertice_size,vertices,*indice_size,indices);
	free(data);
	LOG("MODEL LOADED '" << name << "' vertice_size:" << model->vertice_size << " indice_size:" << model->indice_size);
	return model;
}

GLS::ShaderText COGE::DataLoader::read_shader(std::string name)
{
	char* data = nullptr;
	_FILESIZE size = 0;

	if(shader_references.find(name) == shader_references.end())
	{
		WARN("SEARCHED DATA REFERENCE IS NOT FOUNDED IN SHADERS:'" << name << "'");
		return {"",""};
	}
	Reference& ref = shader_references[name];
	data = (char*)files[ref.file_id].read(ref);
	size = ref.size;

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
	free(start);
	return {vertex_shader+'\0',fragment_shader+'\0'};
}

GLS::TextureData COGE::DataLoader::load_texture(std::string name)
{
	char* data = nullptr;
	_FILESIZE size = 0;

	if(shader_references.find(name) == shader_references.end())
	{
		WARN("SEARCHED DATA REFERENCE IS NOT FOUNDED IN SHADERS:'" << name << "'");
		return {0,0,0,nullptr};
	}
	Reference& ref = shader_references[name];
	data = (char*)files[ref.file_id].read(ref);
	size = ref.size;
	LOG("REFERENCE FOUND.");

	FreeFetcher ff((void*)data);

	int *width = ff.fetch<int>();
	int *height = ff.fetch<int>();
	unsigned int* type = ff.fetch<unsigned int>();
	unsigned char* texture_data_pos = (unsigned char*)&data[ff.wh()];
	GLS::TextureData tex_data;
	tex_data.width = *width; tex_data.height = *height;
	tex_data.type = *type;

	tex_data.data = (unsigned char*)malloc(ref.size-ff.wh());
	memcpy(tex_data.data, texture_data_pos, ref.size-ff.wh());
	free(data);
	return tex_data;
}