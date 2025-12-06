# CMakeLists.txt

# 요구되는 CMake 최소 버전 설정
cmake_minimum_required(VERSION 3.10)

# 프로젝트 이름 설정
project(TCPEchoApp CXX)

# C++ 표준을 C++11 이상으로 설정
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 서버 실행 파일 정의
# 소스 파일: server.cpp
add_executable(tcp_server tcp_server.cpp)

# 클라이언트 실행 파일 정의
# 소스 파일: client.cpp
add_executable(tcp_client tcp_client.cpp)

# --- 소켓 라이브러리 링크 설정 ---

# Linux/macOS 환경에서는 소켓 함수가 기본 C 라이브러리에 포함되어 
# 별도의 링크가 필요 없지만, 일부 시스템을 위해 -lWS2_32(Windows) 또는 
# -lsocket/-lnsl(구형 Unix)와 같은 라이브러리 링크가 필요할 수 있습니다.
# 여기서는 find_package를 사용하여 시스템 네트워킹 라이브러리를 찾습니다.

#find_package(Threads REQUIRED)

# tcp_server 실행 파일에 스레드 라이브러리 링크 (일반적인 C++ 프로그램에 필요)
#target_link_libraries(tcp_server PRIVATE Threads::Threads)

# tcp_client 실행 파일에 스레드 라이브러리 링크
#target_link_libraries(tcp_client PRIVATE Threads::Threads)