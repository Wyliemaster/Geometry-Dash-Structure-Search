cmake_minimum_required(VERSION 3.10)

project(Geometry-Dash-Structure-Search)

# Set C++ version to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Specify the relative path to zlib directory
set(ZLIB_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/lib/zlib")

# Add your executable
add_executable(search src/*.cpp)

# Include zlib directory
target_include_directories(search PUBLIC ${ZLIB_INCLUDE_DIR})

# Link zlib library
if(CMAKE_SIZEOF_VOID_P EQUAL 8 AND WIN32)
    target_link_libraries(search PRIVATE "${CMAKE_SOURCE_DIR}/lib/zlibstatic.lib")
elseif(UNIX)
    target_link_libraries(search PRIVATE "${CMAKE_SOURCE_DIR}/lib/zlibstatic.so")
endif()
