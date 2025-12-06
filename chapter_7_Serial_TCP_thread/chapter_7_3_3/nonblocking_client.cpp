#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>

// 종료 플래그
volatile sig_atomic_t running = 1;

// Ctrl+C 시그널 핸들러
void signalHandler(int signum) {
    std::cout << "\nShutting down..." << std::endl;
    running = 0;
}

int main() {
    // Ctrl+C 시그널 핸들러 등록
    signal(SIGINT, signalHandler);
    
    // 소켓 생성 및 논블로킹 설정
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    int flags = fcntl(sock_fd, F_GETFL, 0);
    fcntl(sock_fd, F_SETFL, flags | O_NONBLOCK);
    
    // 서버에 연결
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);
    
    connect(sock_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    std::cout << "Connected (non-blocking mode)" << std::endl;
    std::cout << "Press Ctrl+C to exit" << std::endl;
    
    char buffer[1024];
    int msg_index = 0;
    std::string messages[] = {"MOVE_FORWARD", "ROTATE_LEFT"};
    int num_messages = 2;
    
    while (running) {
        // 번갈아가며 메시지 전송
        std::string msg = messages[msg_index];
        int sent = send(sock_fd, msg.c_str(), msg.length(), 0);
        if (sent > 0) {
            std::cout << "Sent: " << msg << std::endl;
            msg_index = (msg_index + 1) % num_messages;  // 다음 메시지로
        }
        
        // 응답 수신
        int bytes = recv(sock_fd, buffer, 1024, 0);
        if (bytes > 0) {
            std::cout << "Received: " << std::string(buffer, bytes) << std::endl;
        } else if (bytes == 0) {
            std::cout << "Server disconnected" << std::endl;
            break;
        }
        // bytes < 0 && EWOULDBLOCK: 데이터 없음 (정상)
        
        // 다른 로봇 제어 작업 수행 가능
        usleep(500000);  // 500ms 대기 (더 천천히 전송)
    }
    
    close(sock_fd);
    std::cout << "Client terminated" << std::endl;
    return 0;
}