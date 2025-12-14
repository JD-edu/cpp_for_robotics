// tcp_client.cpp
#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    std::string serverIP = "127.0.0.1";  // 기본값: localhost
    int port = 8080;
  
    // 명령줄 인자로 서버 IP와 포트 지정 가능
    if (argc > 1) {
        serverIP = argv[1];
    }
    if (argc > 2) {
        port = std::atoi(argv[2]);
    }

    // 1. 소켓 생성
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0) {
        std::cerr << "[Client] Failed to create socket." << std::endl;
        return -1;
    }

    // 2. 서버 주소 구조체 설정
    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
  
    // IP 주소 변환
    if (inet_pton(AF_INET, serverIP.c_str(), &serverAddr.sin_addr) <= 0) {
        std::cerr << "[Client] Invalid address: " << serverIP << std::endl;
        close(clientSocket);
        return -1;
    }

    // 3. 서버에 연결
    std::cout << "[Client] Connecting to " << serverIP << ":" << port << "..." << std::endl;
  
    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "[Client] Connection failed." << std::endl;
        close(clientSocket);
        return -1;
    }

    std::cout << "[Client] Connected successfully!" << std::endl;

    // 4. 서버로부터 환영 메시지 수신
    char buffer[1024];
    int bytesRead = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
    if (bytesRead > 0) {
        buffer[bytesRead] = '\0';
        std::cout << "[Server says] " << buffer;
    }

    // 5. 메시지 송수신 루프
    std::cout << "\n--- Type messages to send to server (type 'quit' to exit) ---\n" << std::endl;
  
    while (true) {
        std::cout << ">> ";
        std::string message;
        std::getline(std::cin, message);
  
        // 종료 명령 확인
        if (message == "quit" || message == "exit") {
            std::cout << "[Client] Closing connection..." << std::endl;
            break;
        }
  
        // 빈 메시지는 보내지 않음
        if (message.empty()) {
            continue;
        }
  
        // 개행 문자 추가
        message += "\n";
  
        // 서버로 메시지 전송
        ssize_t bytesSent = send(clientSocket, message.c_str(), message.length(), 0);
        if (bytesSent < 0) {
            std::cerr << "[Client] Send failed." << std::endl;
            break;
        }
  
        // 서버로부터 응답 수신
        memset(buffer, 0, sizeof(buffer));
        bytesRead = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
  
        if (bytesRead <= 0) {
            std::cout << "[Client] Server disconnected." << std::endl;
            break;
        }
  
        buffer[bytesRead] = '\0';
        std::cout << "[Server] " << buffer;
    }

    // 6. 소켓 닫기
    close(clientSocket);
    std::cout << "[Client] Disconnected." << std::endl;
  
    return 0;
}