cmake_minimum_required(VERSION 3.5)
project(VideoSimilarityMeasurement)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(VideoSimilarityMeasurement ${SOURCE_FILES})

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCUDE_DIRS})
target_link_libraries(VideoSimilarityMeasurement ${OpenCV_LIBS})

