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

#ifndef COGE_DONT_FILE_LOG
#ifndef COGE_LOG_FILE_PATH
#define COGE_LOG_FILE_PATH "coge_log.txt"
#endif
std::ofstream log_file(COGE_LOG_FILE_PATH);
#define FLOG(x) log_file << x << std::endl;
#define FLOGnl(x) log_file << x;
#else
#define FLOG(x)
#define FLOGnl(x)
#endif

#ifndef COGE_DONT_LOG
#define PRINT(x) std::cout << x << std::endl; FLOG(x)
#define PRINTnl(x) std::cout << x; FLOGnl(x)
#define LOG(x) std::clog << "COGE:LOG:" << x << std::endl; FLOG("COGE:LOG:" << x)
#define LOGnl(x) std::clog << "COGE:LOG:" << x; FLOGnl("COGE:LOG:" << x)
#else
#define PRINT(x)
#define PRINTnl(x)
#define LOG(x)
#define LOGnl(x)
#endif

#ifdef COGE_EXTREME_LOG
#define E_LOG(x) LOG(x)
#define E_LOGnl(x) LOGnl(x)
#define E_PRINT(x) PRINT(x)
#define E_PRINTnl(x) PRINTnl(x)
#else
#define E_LOG(x)
#define E_LOGnl(x)
#define E_PRINT(x)
#define E_PRINTnl(x)
#endif

#define WARN(x) std::cerr << "COGE:WARNING:" << x << std::endl; FLOG("COGE:WARNING:" << x)
#define WARNnl(x) std::cerr << "COGE:WARNING:" << x; FLOGnl("COGE:WARNING:" << x)
#define WARNPRINT(x) std::cout << x << std::endl;
#define WARNPRINTnl(x) std::cout << x;

#ifndef COGE_DESTROY_QUICK_UNDERSTAND
#define QUICK_UNDERSTAND LOG("---------------------------------Yay.-------------------------------------");
#endif

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "headers/GL_SimpObjects.hpp"
#include "headers/GL_Shaders.hpp"
#include "headers/GL_LeCamera.hpp"
#include "headers/GL_Models.hpp"

#include "headers/GL_Draw.hpp"

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

#include "COGE/COGE_StandardShaders.h"

#include "COGE_extra/generators.h"
#include "COGE_extra/water.h"
#include "COGE_extra/terrain.h"
#include "COGE_extra/tree.h"
#include "COGE_extra/things.h"
#include "COGE_extra/controller.h"

#ifdef COGE_MERGE_STATIC_MODELS
#include "COGE/COGE_Models.h"
#endif

#include "COGE/COGE_DebugUI.h"
#include "COGE/COGE_Data.h"


#include "COGE/COGE_Core.h"