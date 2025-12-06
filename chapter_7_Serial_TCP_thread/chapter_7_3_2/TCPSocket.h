#ifndef TCP_SOCKET_H
#define TCP_SOCKET_H

#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

class TCPSocket {
private:
    int socket_fd;
    struct sockaddr_in address;
    
public:
    TCPSocket() : socket_fd(-1) {}
    
    ~TCPSocket() {
        if (socket_fd != -1) {
            close(socket_fd);
        }
    }
    
    // 서버: 소켓 생성 및 바인딩
    bool createServer(int port) {
        socket_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (socket_fd < 0) return false;
        
        int opt = 1;
        setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
        
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(port);
        
        if (bind(socket_fd, (struct sockaddr*)&address, sizeof(address)) < 0)
            return false;
        if (listen(socket_fd, 5) < 0)
            return false;
        
        return true;
    }
    
    // 서버: 클라이언트 연결 수락
    TCPSocket* acceptClient() {
        socklen_t addrlen = sizeof(address);
        int client_fd = accept(socket_fd, (struct sockaddr*)&address, &addrlen);
        if (client_fd < 0) return nullptr;
        
        TCPSocket* client = new TCPSocket();
        client->socket_fd = client_fd;
        client->address = address;
        return client;
    }
    
    // 클라이언트: 서버에 연결
    bool connectToServer(const std::string& ip, int port) {
        socket_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (socket_fd < 0) return false;
        
        address.sin_family = AF_INET;
        address.sin_port = htons(port);
        if (inet_pton(AF_INET, ip.c_str(), &address.sin_addr) <= 0)
            return false;
        
        return connect(socket_fd, (struct sockaddr*)&address, 
                      sizeof(address)) >= 0;
    }
    
    // 데이터 전송
    bool send(const std::string& data) {
        return ::send(socket_fd, data.c_str(), data.length(), 0) > 0;
    }
    
    // 데이터 수신
    std::string receive(size_t buffer_size = 1024) {
        char buffer[buffer_size];
        int bytes = recv(socket_fd, buffer, buffer_size, 0);
        if (bytes > 0) {
            return std::string(buffer, bytes);
        }
        return "";
    }
    
    // 연결 상태 확인
    bool isValid() const {
        return socket_fd != -1;
    }
};

#endif // TCP_SOCKET_H