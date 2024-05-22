cmake_minimum_required(VERSION 3.25)
project(opProject)

file(GLOB MAIN "main.cpp")
file(GLOB FUNC "func.cpp")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
add_executable(${PROJECT_NAME} ${MAIN} ${FUNC})