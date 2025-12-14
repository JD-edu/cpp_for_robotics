#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

class ESP32UDPClient {
private:
    int sock;
    struct sockaddr_in server_addr;
  
public:
    ESP32UDPClient(const std::string& ip, int port) {
        // UDP 소켓 생성 (SOCK_DGRAM)
        sock = socket(AF_INET, SOCK_DGRAM, 0);
        if (sock < 0) {
            throw std::runtime_error("UDP 소켓 생성 실패");
        }
      
        // 서버 주소 설정
        memset(&server_addr, 0, sizeof(server_addr));
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(port);
        inet_pton(AF_INET, ip.c_str(), &server_addr.sin_addr);
      
        std::cout << "UDP 클라이언트 초기화: " << ip << ":" << port << std::endl;
    }
  
    ~ESP32UDPClient() {
        close(sock);
    }
  
    std::string sendCommand(const std::string& cmd) {
        // 명령 전송 (연결 없이 바로 전송)
        sendto(sock, cmd.c_str(), cmd.length(), 0,
               (struct sockaddr*)&server_addr, sizeof(server_addr));
        std::cout << "전송: " << cmd << std::endl;
      
        // 응답 수신 (타임아웃 설정)
        fd_set readfds;
        struct timeval timeout;
        FD_ZERO(&readfds);
        FD_SET(sock, &readfds);
        timeout.tv_sec = 2;   // 2초 타임아웃
        timeout.tv_usec = 0;
      
        if (select(sock + 1, &readfds, NULL, NULL, &timeout) <= 0) {
            return "TIMEOUT";
        }
      
        char buffer[512];
        socklen_t addr_len = sizeof(server_addr);
        ssize_t received = recvfrom(sock, buffer, sizeof(buffer) - 1, 0,
                                    (struct sockaddr*)&server_addr, &addr_len);
      
        if (received > 0) {
            buffer[received] = '\0';
            std::string response(buffer);
            std::cout << "수신: " << response << std::endl;
            return response;
        }
      
        return "";
    }
};

int main() {
    std::string esp32_ip;
    std::cout << "로봇 IP 주소를 입력하세요: ";
    std::cin >> esp32_ip;
    std::cin.ignore();
  
    try {
        ESP32UDPClient client(esp32_ip, 9999);  // 포트 9999
      
        std::cout << "\n로봇 제어 명령:" << std::endl;
        std::cout << "- FORWARD: 전진" << std::endl;
        std::cout << "- BACKWARD: 후진" << std::endl;
        std::cout << "- LEFT: 좌회전" << std::endl;
        std::cout << "- RIGHT: 우회전" << std::endl;
        std::cout << "- STOP: 정지" << std::endl;
        std::cout << "- STATUS: 상태 조회" << std::endl;
        std::cout << "- quit: 종료\n" << std::endl;
      
        std::string command;
        while (true) {
            std::cout << "명령 입력: ";
            std::getline(std::cin, command);
          
            if (command == "quit") break;
            if (!command.empty()) {
                client.sendCommand(command);
            }
        }
      
    } catch (const std::exception& e) {
        std::cerr << "오류: " << e.what() << std::endl;
        return -1;
    }
  
    return 0;
}