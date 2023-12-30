
#include <cstring>
#include <COGE/Macros.h>
#include <COGE/datas/DataPacker.hpp>


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

void COGE::DataPacker::addData(COGE::DATA_TYPE type, std::string name, _FILESIZE data_size, void* data)
{
	// Append data to out_file
	temp_file.write(reinterpret_cast<char*>(&type), sizeof(DATA_TYPE));
	unsigned int name_size = name.size();
	temp_file.write(reinterpret_cast<char*>(&name_size), sizeof(unsigned int));
	temp_file.write(reinterpret_cast<char*>((char*)name.c_str()), sizeof(char)*name_size);
	temp_file.write(reinterpret_cast<char*>(&data_size), sizeof(data_size));
	temp_file.write(reinterpret_cast<char*>(data), data_size);
	data_count++;
	LOG("DATA " << name << " IS LOADED TO " << file_name << ".\n");
}


void COGE::DataPacker::addModelData(std::string name, GLS::MODEL model)
{
	_FILESIZE data_size = sizeof(unsigned int)+model.vertice_size+sizeof(unsigned int)+model.indice_size;
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

	if(remove((file_name+COGE_DATA_EXTENSION).c_str())) WARN("REAL " << file_name + COGE_DATA_EXTENSION << " COULD NOT BE REMOVED.");
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