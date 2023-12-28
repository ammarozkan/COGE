cmake_minimum_required(VERSION 3.27)
project(TryingOpenGL VERSION 2.0)

add_executable(GRANDE main.cpp
                    src/COGE/drawers_low/GL_Draw.cpp
                    src/COGE/drawers_low/GL_SimpObjects.cpp
                    src/COGE/drawers_low/GL_LeCamera.cpp
                    src/COGE/drawers_low/GL_Models.cpp
                    src/COGE/drawers_low/GL_Shaders.cpp
                    src/COGE/controller/controller.cpp
                    src/COGE/controller/tpscontroller.cpp
                    src/COGE/controller/planecontroller.cpp
                    src/COGE/core/APIInitializers.cpp
                    src/COGE/core/Initializers.cpp
                    src/COGE/core/StandardShaders.cpp
                    src/COGE/core/Core.cpp
                    src/COGE/core/CoreDestructor.cpp
                    src/COGE/objects/generators.cpp
                    src/COGE/objects/things.cpp
                    src/COGE/datas/DataLoader.cpp
                    src/COGE/datas/DataPacker.cpp
                    src/COGE/debugui/COGE_DebugUI_Letters.cpp
                    src/COGE/Macros.cpp)
configure_file(cmakeincluder.h.in cmakeincluder.h)

target_include_directories(GRANDE PUBLIC "${PROJECT_BINARY_DIR}")
target_include_directories(GRANDE PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(glfw-3.3.8)
target_link_libraries(GRANDE glfw)
find_package(OpenGL REQUIRED)
target_link_libraries(GRANDE OpenGL::GL )
find_package(GLEW REQUIRED)
target_link_libraries(GRANDE GLEW::GLEW)


add_subdirectory(COPhysicsEngine3D)
target_link_libraries(GRANDE COPE3D)


add_subdirectory(glm)
target_link_libraries(GRANDE glm)
