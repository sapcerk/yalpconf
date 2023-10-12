cmake_minimum_required(VERSION 3.22)

project(yalpconf_example LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_library(yalpconf SHARED IMPORTED) 
set_target_properties(yalpconf PROPERTIES
  IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/../build/libyalpconf.so"
  INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/../include"
)

add_executable(${PROJECT_NAME} main.cc)
target_link_libraries(${PROJECT_NAME} yalpconf)

