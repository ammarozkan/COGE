#ifndef COGE_DATA_LOADER_HPP
#define COGE_DATA_LOADER_HPP

#include <iostream>
#include <vector>
#include <unordered_map>
#include <thread>

#include <COGE/datas/Datas.hpp>
#include <COGE/drawers_low/GL_Models.hpp>
#include <COGE/drawers_low/GL_Shaders.hpp>
#include <COGE/drawers_low/GL_Textures.hpp>

namespace COGE
{
	std::string typeToString(DATA_TYPE data_type);

	struct Reference
	{
		unsigned int file_id;
		long int where;
		_FILESIZE size;
		//std::string name;
	};

	class FreeFetcher
	{
	private:
		char* first;
		char* pointer;
	public:
		FreeFetcher(void* pointer);
		
		template<typename T>
		T* fetch(unsigned int count = 1)
		{
			T* result = (T*)pointer;
			pointer+=sizeof(T)*count;
			return result;
		}

		unsigned int wh();
	};

	class DataFile
	{
	private:
		std::ifstream in_file;
		DATA_TYPE generic_type = DATA_TYPE::COGE_DEFAULT;
		unsigned int data_count = 0,file_id = 0;
	public:
		DataFile(std::string file_path);

		void scan(std::unordered_map<std::string,Reference> &model_references, std::unordered_map<std::string,Reference> &shader_references);
		void* read(Reference ref);
	};

	class DataLoader
	{
	private:
		std::vector<DataFile> files;
		std::unordered_map<std::string,Reference> model_references, shader_references;
	public:
		DataLoader(std::vector<std::string> file_paths = std::vector<std::string>());
		void addFile(std::string file_path);
		GLS::MODEL* load_model(std::string name);
		GLS::ShaderText read_shader(std::string name);
		GLS::TextureData load_texture(std::string name);
	};

	class SimulDataLoader
	{
	private:
		std::vector<std::string> next_models, next_shaders, next_textures;
		std::unordered_map<std::string,GLS::MODEL*> models;
		std::thread thrd;

	public:
		SimulDataLoader(DataLoader& dataLoader);
		void requestTexture(std::string name, DATA_TYPE type);
		void requestModel(std::string name);
		void requestShader(std::string name);

		void frameClock(); // should be clocked end of the frame. will start new loadings after this.
		// And while loadings are doing, engine cant reach to loaded models.

		bool isLoaded(std::string name, DATA_TYPE type); // if(SDL.isLoaded("cube",DATA_TYPE::MODEL)) cube = SDL.getModel("cube");
		GLS::MODEL getModel(std::string name);

		void begin(); // will create and start the thread.
	};

	struct DataObject 
	{
		void* object;
		std::string name;
	};

	class DataManager
	{
	private:
		std::vector<DataObject> onWork, onLoad;	// when something wanted to add to it, and there isn't place for new one
												// this manager will destroy the last one.
	public:
		void addOnWork(DataObject dataObject);
		void addOnLoad(DataObject dataObject);

		void setReady(std::string name);	// Will load a data to onLoad. if data is already in onLoad, it
											// will put this data to top. if it's already in onWork, not
											// gonna touch.
		DataObject requestData(std::string name); // will search onWork, and then onLoad list. If there's
												  // nothing, it will load the data to onWork.
												  // if the data is onLoad, then it will just
												  // load that data to onWork without
												  // using files.
												  // in the result, we should be getted the data.
	};
}

#endif