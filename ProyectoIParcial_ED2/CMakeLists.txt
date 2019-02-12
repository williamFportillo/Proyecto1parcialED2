cmake_minimum_required(VERSION 3.8)
project(ProyectoIParcial_ED2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Disk.cpp Disk.h archivos.cpp archivos.h bitmap.cpp bitmap.h)
add_executable(ProyectoIParcial_ED2 ${SOURCE_FILES})