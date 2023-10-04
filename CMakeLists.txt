cmake_minimum_required(VERSION 3.22)
project(yalpconf VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDART 20)
set(CMAKE_CXX_STANDART_REQUIRED ON)

set(SOURCE_FILES
  src/error.cc
  src/reader/blocking_file_reader.cc
  src/reader/string_reader.cc
  src/lexical_analyzer/blocking_lexical_analyzer.cc
)

enable_testing()

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(tests)
