cmake_minimum_required(VERSION 3.5)
project(DetectCornerInSubpixel)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(DetectCornerInSubpixel ${SOURCE_FILES})

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(DetectCornerInSubpixel ${OpenCV_LIBS})