cmake_minimum_required(VERSION 3.16)
project(ShortestPath LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Release build by default
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS_RELEASE "-O2")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -Wall -Wextra -Wpedantic")

add_executable(shortest_path
    src/main.cpp
    src/AdjMatrix.cpp
    src/AdjList.cpp
    src/Dijkstra.cpp
    src/BellmanFord.cpp
    src/FileIO.cpp
    src/GraphGenerator.cpp
    src/Benchmark.cpp
)

target_include_directories(shortest_path PRIVATE src)
