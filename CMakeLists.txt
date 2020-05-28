cmake_minimum_required(VERSION 2.8.8)
project(vtk-realtime-plotter-example)
find_package(VTK REQUIRED)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-pthread")

include(${VTK_USE_FILE})
include_directories(${CMAKE_SOURCE_DIR}/jthread/source ${VTK_INCLUDE_DIRS})

add_executable(example example.cpp)
target_link_libraries(example ${VTK_LIBRARIES})