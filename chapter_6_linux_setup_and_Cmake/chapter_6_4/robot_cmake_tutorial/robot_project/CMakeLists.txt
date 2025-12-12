# CMakeLists.txt
cmake_minimum_required(VERSION 3.16)
project(RobotProject)

# C++ 표준 설정
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 컴파일러 경고 활성화 (코드 품질 향상)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

# 헤더 파일 디렉토리 추가
include_directories(include)

# 소스 파일들 수집
set(SOURCES
    main.cpp
    src/robot_math.cpp
    src/sensor.cpp
    src/motor.cpp
)

# 실행 파일 생성
add_executable(robot_app ${SOURCES})

# 수학 라이브러리 링크 (sqrt, pow 등 사용을 위해)
target_link_libraries(robot_app m)