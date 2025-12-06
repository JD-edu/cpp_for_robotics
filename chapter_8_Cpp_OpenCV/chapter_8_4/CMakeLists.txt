cmake_minimum_required(VERSION 3.10)
project(OpenCVStudy)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(OpenCV REQUIRED)

add_executable(701_threshold 701_threshold.cpp)
target_link_libraries(701_threshold ${OpenCV_LIBS})

