# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(OpenCVCameraExample)

# OpenCV 패키지 찾기
find_package(OpenCV REQUIRED)

# 라이브러리 생성 (재사용 가능한 카메라 핸들러)
add_library(camera_lib 
    camera_handler.cpp
    camera_handler.hpp
)

# 실행 파일 생성 (메인 애플리케이션)
add_executable(camera_app main.cpp)

# C++11 표준 사용
target_compile_features(camera_lib PUBLIC cxx_std_11)
target_compile_features(camera_app PRIVATE cxx_std_11)

# 라이브러리에 OpenCV 링크
target_link_libraries(camera_lib PUBLIC ${OpenCV_LIBS})

# 실행 파일에 라이브러리 링크
target_link_libraries(camera_app PRIVATE camera_lib)

# 헤더 파일 경로 설정
target_include_directories(camera_app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})