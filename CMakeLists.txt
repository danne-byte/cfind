cmake_minimum_required(VERSION 3.25)

project(
  cdiff 
  VERSION 0.2.0
  DESCRIPTION "A content diff utility"
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# configure compile flags
set(GCC_COMPILE_OPTS_DBG -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Werror -Wsign-conversion -g)
set(GCC_COMPILE_OPTS_REL -O3 -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Werror -Wsign-conversion -g)

if(${CMAKE_BUILD_TYPE} MATCHES Debug)
	set(COMPILE_OPTS ${GCC_COMPILE_OPTS})
else()
	set(COMPILE_OPTS ${GCC_COMPILE_OPTS})
endif()


include(FetchContent)

add_subdirectory(src)
add_subdirectory(tests)

