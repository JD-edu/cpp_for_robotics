cmake_minimum_required(VERSION 3.10)
project(TCPMultithreadServer)

set(CMAKE_CXX_STANDARD 11)

# 서버 실행 파일
add_executable(server tcp_multithread_server.cpp)
target_link_libraries(server pthread)

# 클라이언트 실행 파일
add_executable(client tcp_client.cpp)
target_link_libraries(client pthread)