// #define COGE_VULKAN -> this is a self explanatory defining. Yeah. implements vulkan.

// customisation instructions:
// #define COGE_EDITOR -> will let compiler to compiler editor special classes in example DataPackager
// #define COGE_DONT_FILE_LOG -> this definition will prevent "file logging" to the file "coge_log.txt"
// #define COGE_LOG_FILE_PATH "mylogpath/mylogfile.txt" -> compile master can change log path with this definition
// #define COGE_DONT_LOG -> this definition will prevent command line logging.
// Engine programmer is used to understand mistakes that made by himself with QUICK_UNDERSTAND macro.
// #define COGE_DESTROY_QUICK_UNDERSTAND -> this definition will destroy QUICK_UNDERSTAND macro.
// #define COGE_EXTREME_LOG -> this will log nearly everything that could be important
// #define COGE_TEMP_DATA_EXTENSION -> with this, temp data extension can be changed
// #define COGE_DATA_EXTENSION -> with this, data extension can be changed
// #define COGE_MERGE_STATIC_MODELS -> library not defaultly includes COGE_Models.h file. Only includes when that thing is defined.

#ifndef COGE_ENGINE_H
#define COGE_ENGINE_H

#define COGE_VERSION_NAME "In the Beginning"

#ifndef COGE_VULKAN
#include <GL/glew.h>
#else
#define GLFW_INCLUDE_VULKAN
#endif
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <cmath>
#include <thread>

#include <COGE/Macros.h>

#include <COGE/Mathematics.h>

#include <COGE/drawers_low/GL_SimpObjects.hpp>
#include <COGE/drawers_low/GL_Shaders.hpp>
#include <COGE/drawers_low/GL_LeCamera.hpp>
#include <COGE/drawers_low/GL_Models.hpp>
#include <COGE/drawers_low/GL_Draw.hpp>

void print(glm::vec3 t)
{
	std::cout << "X:" << t.x << " Y:" << t.y << " Z:" << t.z << std::endl;
}

void print(glm::vec4 t)
{
	std::cout << "X:" << t.x << " Y:" << t.y << " Z:" << t.z << " W:" << t.w << std::endl;
}

void print(float t)
{
	std::cout << "Float:" << t << std::endl;
}

#include <COGE/core/StandardShaders.h>

#include <COGE/objects/generators.h>
#include <COGE/objects/water.h>
#include <COGE/objects/terrain.h>
#include <COGE/objects/tree.h>
#include <COGE/objects/things.h>

#include <COGE/controller/controller.h>

#ifdef COGE_MERGE_STATIC_MODELS
#include <COGE_STATIC_MODELS.h>
#endif

#include <COGE/debugui/DebugUI.hpp>
#include <COGE/datas/Datas.hpp> // bad name. ill change it

#include <COGE/core/Core.h>

#endif