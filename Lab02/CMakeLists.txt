cmake_minimum_required(VERSION 3.19)
project(Lab02)

set(CMAKE_CXX_STANDARD 17)

find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

bison_target(Parser src/FlexBison/parser.yy ${CMAKE_HOME_DIRECTORY}/FlexBisonOutput/parser.cc)
flex_target(Scanner src/FlexBison/scanner.ll ${CMAKE_HOME_DIRECTORY}/FlexBisonOutput/scanner.cc)
ADD_FLEX_BISON_DEPENDENCY(Scanner Parser)

include_directories(${CMAKE_HOME_DIRECTORY}/FlexBisonOutput)


add_executable(Lab02 src/body/main.cpp src/header/CompileController.h src/body/CompileController.cpp src/header/IOController.h src/body/IOController.cpp src/header/driver.hh src/body/driver.cc src/body/TreeNode.cpp src/header/TreeNode.h ${BISON_Parser_OUTPUTS} ${FLEX_Scanner_OUTPUTS} src/body/Symbol/SemanticCheck.cpp src/header/Symbol/SemanticCheck.h src/body/Symbol/Symbol.cpp src/header/Symbol/Symbol.h src/body/Symbol/SymbolTree.cpp src/header/Symbol/SymbolTree.h)