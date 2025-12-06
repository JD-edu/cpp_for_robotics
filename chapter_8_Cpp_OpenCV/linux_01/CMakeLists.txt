# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(OpenCVCameraExample)

# OpenCV 패키지 찾기
find_package(OpenCV REQUIRED)

# OpenCV 정보 출력
message(STATUS "OpenCV 버전: ${OpenCV_VERSION}")

# 실행 파일 생성
add_executable(camera_stream camera_stream.cpp)

# C++11 표준 사용
target_compile_features(camera_stream PRIVATE cxx_std_11)

# OpenCV 라이브러리 링크
target_link_libraries(camera_stream PRIVATE ${OpenCV_LIBS})

# OpenCV 헤더 파일 경로 포함
target_include_directories(camera_stream PRIVATE ${OpenCV_INCLUDE_DIRS})