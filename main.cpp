#include "cmakeincluder.h"

/// spell coge like koj. prend le mat comme en francais

#define COGE_DONT_FILE_LOG
#define COGE_EDITOR
#define COGE_EXTREME_LOG

//#define COGE_PACK
//#define COGE_UNPACK

#ifdef COGE_PACK
#define COGE_MERGE_STATIC_MODELS
#endif

#include <COGE/Engine.h>
#ifdef COGE_EDITOR
#include <COGE/editor/Editor.h>
#endif

int main()
{
	ThatCode_print_version(); // works for cmake
	GLFWwindow* window = COGE::Engine::init_gl(); // BOOOM opengl
#ifndef COGE_EDITOR
	LOG("ENGINE CREATION.");
	COGE::Engine engine(window); 
	engine.Work(); // hmmm
#else
	COGE::Editor editor(window);
	editor.Work();
#endif
	

#ifdef COGE_PACK
	COGE::DataPacker test_pack("packages/early_package");
	test_pack.addShaderData_fromFile("generalshader", "assets/generalshader.glsl");
	test_pack.addShaderData_fromFile("uishader", "assets/uishader.glsl");
	test_pack.addShaderData_fromFile("watershader", "assets/watershader.glsl");
	test_pack.addShaderData_fromFile("skyboxshader", "assets/skyboxshader.glsl");
	test_pack.addModelData("model_plane", COGE::MODEL_Plane());
	test_pack.addModelData("model_tree_grass", COGE::MODEL_TreeGrass());
	test_pack.addModelData("model_tree_wood", COGE::MODEL_TreeWood());
	test_pack.addModelData("model_basic_cube", COGE::MODEL_Cube());
	test_pack.pack();
#endif
#ifdef COGE_UNPACK
	std::vector<std::string> files; files.push_back("packages/early_package.COGE");
	COGE::DataReader test_unpack(files);
	//std::cout << test_unpack.read_shader("uishader").vertex << std::endl;
	GLS::MODEL un_model = test_unpack.read_model("model_plane");
	for(unsigned int i = 0;i<un_model.vertice_size/sizeof(float);i++)
	{
		std::cout << un_model.vertices[i] << ",";
		if((i+1)%3 == 0) std::cout << std::endl;
	}
	std::cout << std::endl;
#endif

	return 0;
}
