#ifndef COGE_DATA_PACKER_HPP
#define COGE_DATA_PACKER_HPP

#ifndef COGE_TEMP_DATA_EXTENSION
#define COGE_TEMP_DATA_EXTENSION ".COGE.temp"
#endif
#ifndef COGE_DATA_EXTENSION
#define COGE_DATA_EXTENSION ".COGE"
#endif

#include <fstream>
#include <COGE/datas/Datas.hpp>


namespace COGE
{
	class DataPacker
	{
	private:
		std::fstream temp_file;
		unsigned int data_count = 0;
		std::string file_name;
		std::vector<DATA_TYPE> included_types;
	public:
		DataPacker(std::string file_name); // file_name should be putten here without file extension

		void addData(DATA_TYPE type, std::string name, _FILESIZE data_size, void* data);
		void addModelData(std::string name, GLS::MODEL model);
		void addShaderData(std::string name, std::string shader_code);
		void addShaderData_fromFile(std::string name, std::string shader_path);

		void pack(); // sets the data header and closes file. And wholah! Flush the data!
	};
}

#endif