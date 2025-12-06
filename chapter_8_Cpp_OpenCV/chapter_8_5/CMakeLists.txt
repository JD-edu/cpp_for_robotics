cmake_minimum_required(VERSION 3.10)
project(OpenCVStudy)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(OpenCV REQUIRED)

add_executable(1001_canny_edge 1001_canny_edge.cpp)
target_link_libraries(1001_canny_edge ${OpenCV_LIBS})

