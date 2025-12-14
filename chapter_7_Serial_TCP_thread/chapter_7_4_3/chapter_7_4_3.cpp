#include <iostream>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>
#include <chrono>

class ESP32Client {
private:
    int sock;
    struct sockaddr_in server_addr;
    std::string esp32_ip;
    int port;
    bool connected;

public:
    ESP32Client(const std::string& ip, int p) : esp32_ip(ip), port(p), connected(false) {
        sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock < 0) {
            throw std::runtime_error("소켓 생성 실패");
        }
    }
  
    ~ESP32Client() {
        disconnect();
    }
  
    bool connect() {
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(port);
      
        if (inet_pton(AF_INET, esp32_ip.c_str(), &server_addr.sin_addr) <= 0) {
            std::cerr << "잘못된 IP 주소" << std::endl;
            return false;
        }
      
        if (::connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
            std::cerr << "ESP32 연결 실패" << std::endl;
            return false;
        }
      
        connected = true;
        std::cout << "ESP32에 연결되었습니다: " << esp32_ip << ":" << port << std::endl;
      
        // 서버 환영 메시지 수신
        receiveMessage();
        return true;
    }
  
    void disconnect() {
        if (connected) {
            close(sock);
            connected = false;
            std::cout << "ESP32 연결이 종료되었습니다." << std::endl;
        }
    }
  
    bool sendMessage(const std::string& message) {
        if (!connected) return false;
      
        std::string full_message = message + "\n";
        ssize_t sent = send(sock, full_message.c_str(), full_message.length(), 0);
      
        if (sent < 0) {
            std::cerr << "메시지 전송 실패" << std::endl;
            return false;
        }
      
        std::cout << "전송: " << message << std::endl;
        return true;
    }
  
    std::string receiveMessage() {
        if (!connected) return "";
      
        char buffer[1024] = {0};
        ssize_t received = recv(sock, buffer, sizeof(buffer) - 1, 0);
      
        if (received < 0) {
            std::cerr << "메시지 수신 실패" << std::endl;
            return "";
        } else if (received == 0) {
            std::cout << "서버가 연결을 종료했습니다." << std::endl;
            connected = false;
            return "";
        }
      
        std::string message(buffer, received);
        std::cout << "수신: " << message;
        return message;
    }
  
    bool isConnected() const {
        return connected;
    }
};

int main() {
    std::string esp32_ip;
    std::cout << "ESP32 IP 주소를 입력하세요: ";
    std::cin >> esp32_ip;
  
    try {
        ESP32Client client(esp32_ip, 8080);
      
        if (!client.connect()) {
            return -1;
        }
      
        std::string command;
        std::cout << "\n사용 가능한 명령:" << std::endl;
        std::cout << "- LED_ON: LED 켜기" << std::endl;
        std::cout << "- LED_OFF: LED 끄기" << std::endl;
        std::cout << "- STATUS: 상태 확인" << std::endl;
        std::cout << "- quit: 종료" << std::endl << std::endl;
      
        while (client.isConnected()) {
            std::cout << "명령 입력: ";
            std::getline(std::cin, command);
          
            if (command == "quit") {
                break;
            }
          
            if (!command.empty()) {
                if (client.sendMessage(command)) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
                    client.receiveMessage();
                }
            }
        }
      
    } catch (const std::exception& e) {
        std::cerr << "오류: " << e.what() << std::endl;
        return -1;
    }
  
    return 0;
}