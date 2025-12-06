#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

// g++ -o robot_client tcp_client.cpp -std=c++11

int main() {
    // 1. 소켓 생성
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0) {
        std::cerr << "Socket creation failed" << std::endl;
        return -1;
    }
    
    // 2. 서버 주소 설정
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);  // 서버 포트
    
    // IP 주소 변환 (127.0.0.1 = localhost)
    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0) {
        std::cerr << "Invalid address" << std::endl;
        close(sock_fd);
        return -1;
    }
    
    // 3. 서버에 연결
    if (connect(sock_fd, (struct sockaddr*)&server_addr, 
                sizeof(server_addr)) < 0) {
        std::cerr << "Connection failed" << std::endl;
        close(sock_fd);
        return -1;
    }
    
    std::cout << "Connected to server!" << std::endl;
    
    // 4. 데이터 송수신
    std::string command;
    char buffer[1024] = {0};
    
    while (true) {
        std::cout << "Enter command (or 'quit' to exit): ";
        std::getline(std::cin, command);
        
        if (command == "quit") {
            break;
        }
        
        // 명령 전송
        send(sock_fd, command.c_str(), command.length(), 0);
        
        // 응답 수신
        int bytes_read = recv(sock_fd, buffer, 1024, 0);
        if (bytes_read > 0) {
            std::string response(buffer, bytes_read);
            std::cout << "Server: " << response << std::endl;
            memset(buffer, 0, sizeof(buffer));  // 버퍼 초기화
        } else {
            std::cout << "Server disconnected" << std::endl;
            break;
        }
    }
    
    // 5. 소켓 종료
    close(sock_fd);
    
    return 0;
}