cmake_minimum_required(VERSION 3.10)
project(OpenCVStudy)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(OpenCV REQUIRED)

add_executable(opencv-study 101_read_image.cpp)
target_link_libraries(opencv-study ${OpenCV_LIBS})

#add_executable(201_video_from_camera 201_video_from_camera.cpp)
#target_link_libraries(201_video_from_camera ${OpenCV_LIBS})

