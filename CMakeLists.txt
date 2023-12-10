cmake_minimum_required(VERSION 3.27)
project(TryingOpenGL VERSION 2.0)

add_executable(GRANDE main.cpp)
configure_file(cmakeincluder.h.in cmakeincluder.h)

target_include_directories(GRANDE PUBLIC "${PROJECT_BINARY_DIR}")

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(glfw-3.3.8)
target_link_libraries(GRANDE glfw)
find_package(OpenGL REQUIRED)
target_link_libraries(GRANDE OpenGL::GL )
find_package(GLEW REQUIRED)
target_link_libraries(GRANDE GLEW::GLEW)


add_subdirectory(glm)
target_link_libraries(GRANDE glm)
