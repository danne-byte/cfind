cmake_minimum_required(VERSION 3.25)

project(
  cdiff 
  VERSION 0.2.0
  DESCRIPTION "A content diff utility"
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)

add_subdirectory(src)
add_subdirectory(tests)

