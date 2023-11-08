cmake_minimum_required(VERSION 3.20)
project(jsonParserProjectFinal)

set(CMAKE_CXX_STANDARD 14)

add_executable(jsonParserProjectFinal main.cpp json/json.cpp json/json.h json/Parser.cpp json/Parser.h)


include_directories(json)