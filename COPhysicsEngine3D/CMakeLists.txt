cmake_minimum_required(VERSION 3.27)
project(TryingOpenGL VERSION 2.0)

add_library(COPE3D src/cope3d.cpp
				   src/Math.cpp
				   src/Collider.cpp)
#configure_file(cmakeincluder.h.in cmakeincluder.h)

target_include_directories(COPE3D PUBLIC "${PROJECT_BINARY_DIR}")
target_include_directories(COPE3D PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")