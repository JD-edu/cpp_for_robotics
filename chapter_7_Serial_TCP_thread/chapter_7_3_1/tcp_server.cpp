#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

// g++ -o robot_server robot_server.cpp -std=c++11

int main() {
    // 1. 소켓 생성
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        std::cerr << "Socket creation failed" << std::endl;
        return -1;
    }
    
    // 2. 주소 재사용 옵션 설정
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    
    // 3. 주소 구조체 설정
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;  // 모든 IP에서 접속 허용
    address.sin_port = htons(8080);         // 포트 8080
    
    // 4. 소켓에 주소 바인딩
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        std::cerr << "Bind failed" << std::endl;
        close(server_fd);
        return -1;
    }
    
    // 5. 연결 대기 상태로 전환
    if (listen(server_fd, 3) < 0) {
        std::cerr << "Listen failed" << std::endl;
        close(server_fd);
        return -1;
    }
    
    std::cout << "Server listening on port 8080..." << std::endl;
    
    // 6. 클라이언트 연결 수락
    socklen_t addrlen = sizeof(address);
    int client_fd = accept(server_fd, (struct sockaddr*)&address, &addrlen);
    if (client_fd < 0) {
        std::cerr << "Accept failed" << std::endl;
        close(server_fd);
        return -1;
    }
    
    std::cout << "Client connected!" << std::endl;
    
    // 7. 데이터 송수신
    char buffer[1024] = {0};
    while (true) {
        // 데이터 수신
        int bytes_read = recv(client_fd, buffer, 1024, 0);
        if (bytes_read <= 0) {
            std::cout << "Client disconnected" << std::endl;
            break;
        }
        
        std::string command(buffer, bytes_read);
        std::cout << "Received: " << command << std::endl;
        
        // 응답 전송
        std::string response = "ACK: " + command;
        send(client_fd, response.c_str(), response.length(), 0);
        
        memset(buffer, 0, sizeof(buffer));  // 버퍼 초기화
    }
    
    // 8. 소켓 종료
    close(client_fd);
    close(server_fd);
    
    return 0;
}