cmake_minimum_required(VERSION 3.5)
project(HoughLineTransform)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(HoughLineTransform ${SOURCE_FILES})

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(HoughLineTransform ${OpenCV_LIBS})
