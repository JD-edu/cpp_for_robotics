#include <iostream>
#include <vector>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main() {
    // 서버 소켓 생성 및 설정
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    
    // 논블로킹 모드 설정
    int flags = fcntl(server_fd, F_GETFL, 0);
    fcntl(server_fd, F_SETFL, flags | O_NONBLOCK);
    
    // 바인드 및 리슨
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);
    
    bind(server_fd, (struct sockaddr*)&address, sizeof(address));
    listen(server_fd, 5);
    
    std::cout << "Non-blocking server started on port 8080" << std::endl;
    
    std::vector<int> clients;
    char buffer[1024];
    
    while (true) {
        // 새 클라이언트 연결 확인
        int client_fd = accept(server_fd, nullptr, nullptr);
        if (client_fd >= 0) {
            fcntl(client_fd, F_SETFL, fcntl(client_fd, F_GETFL, 0) | O_NONBLOCK);
            clients.push_back(client_fd);
            std::cout << "Client connected (fd: " << client_fd << ")" << std::endl;
        }
        
        // 모든 클라이언트 데이터 처리
        for (size_t i = 0; i < clients.size(); ) {
            int bytes = recv(clients[i], buffer, 1024, 0);
            
            if (bytes > 0) {
                // 데이터 수신 성공
                std::cout << "Received: " << std::string(buffer, bytes) << std::endl;
                send(clients[i], buffer, bytes, 0);  // 에코
                i++;
            } else if (bytes == 0 || (bytes < 0 && errno != EWOULDBLOCK && errno != EAGAIN)) {
                // 연결 종료 또는 오류
                std::cout << "Client disconnected (fd: " << clients[i] << ")" << std::endl;
                close(clients[i]);
                clients.erase(clients.begin() + i);
            } else {
                i++;  // 데이터 없음 (정상)
            }
        }
        
        usleep(1000);  // 1ms 대기
    }
    
    close(server_fd);
    return 0;
}