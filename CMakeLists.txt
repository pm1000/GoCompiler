cmake_minimum_required(VERSION 3.19)
project(Y_Raster_A)

set(CMAKE_CXX_STANDARD 20)

add_executable(Y_Raster_A src/cpp/main.cpp src/cpp/Tree/Tree.cpp src/header/Tree/Tree.h src/cpp/Tree/TokenTree.cpp src/header/Tree/TokenTree.h src/cpp/Tree/BranchTree.cpp src/header/Tree/BranchTree.h src/cpp/IOController.cpp src/header/IOController.h src/cpp/Compiler/Parser.cpp src/header/Compiler/Parser.h src/cpp/Compiler/CompileController.cpp src/header/Compiler/CompileController.h)