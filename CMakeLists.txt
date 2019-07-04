cmake_minimum_required(VERSION 3.5)
project(ORI_CODING)

add_definitions(-O3)

SET (THIS_COM "${PROJECT_SOURCE_DIR}/" )
CONFIGURE_FILE(${PROJECT_SOURCE_DIR}/config.h.cmake ${PROJECT_SOURCE_DIR}/Configuration.h)
set(CMAKE_CXX_FLAGS "-std=c++11")

include_directories("./")
include_directories("./include")
file(GLOB sources "src/*.cpp" )

add_executable(ori_test ${sources})
