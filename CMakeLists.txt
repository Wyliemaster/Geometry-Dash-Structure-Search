cmake_minimum_required(VERSION 3.10)
project(Geometry-Dash-Structure-Search)

# Set C++ version to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Specify the relative path to zlib directory
set(ZLIB_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/lib/zlib")

# Add your executable
file(GLOB SOURCES "src/*.cpp")
add_executable(search ${SOURCES})

# Include zlib directory
target_include_directories(search PUBLIC ${ZLIB_INCLUDE_DIR})

# Link zlib library
if(WIN32)
    # Windows
    target_link_libraries(search PRIVATE "${CMAKE_SOURCE_DIR}/lib/zlibstatic.lib")
elseif(UNIX)
    # Unix/Linux
    find_library(ZLIB_LIBRARY NAMES z PATHS "${CMAKE_SOURCE_DIR}/lib")
    if(ZLIB_LIBRARY)
        target_link_libraries(search PRIVATE ${ZLIB_LIBRARY})
    else()
        message(FATAL_ERROR "zlib library not found")
    endif()
else()
    message(FATAL_ERROR "Unsupported platform")
endif()
