// tcp_multithread_server.cpp
#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <cstring>
#include <atomic>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

// 전역 클라이언트 카운터 (원자적 연산으로 쓰래드 안전성 보장)
std::atomic<int> g_clientCounter(0);

// 개별 클라이언트를 담당하는 쓰래드 함수
void clientHandler(int clientSocket, int clientId, std::string clientIP) {
    char buffer[1024];
    std::string clientName = "Client[" + std::to_string(clientId) + "]@" + clientIP;
  
    std::cout << "[Server] " << clientName << " connected." << std::endl;
  
    // 클라이언트에게 환영 메시지 전송
    std::string welcomeMsg = "Welcome! You are client #" + std::to_string(clientId) + "\n";
    send(clientSocket, welcomeMsg.c_str(), welcomeMsg.length(), 0);

    while (true) {
        memset(buffer, 0, sizeof(buffer));
        int bytesRead = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
  
        if (bytesRead <= 0) {
            // 연결 종료 또는 오류
            if (bytesRead == 0) {
                std::cout << "[Server] " << clientName << " disconnected gracefully." << std::endl;
            } else {
                std::cout << "[Server] " << clientName << " connection error." << std::endl;
            }
            break;
        }
  
        // NULL 종료 문자 추가
        buffer[bytesRead] = '\0';
  
        // 받은 데이터 출력
        std::cout << "[Server] Received from " << clientName << ": " << buffer;
  
        // 응답 메시지 생성 (Echo + 타임스탬프)
        std::string response = "[Echo] " + std::string(buffer);
  
        // 클라이언트에게 응답 전송
        send(clientSocket, response.c_str(), response.length(), 0);
    }
  
    // 소켓 닫기
    close(clientSocket);
    g_clientCounter--; // 클라이언트 수 감소
    std::cout << "[Server] " << clientName << " thread terminated. Active clients: " 
              << g_clientCounter.load() << std::endl;
}

int main(int argc, char* argv[]) {
    int port = 8080;
  
    // 포트 번호를 명령줄 인자로 받을 수 있음
    if (argc > 1) {
        port = std::atoi(argv[1]);
    }

    // 1. 소켓 생성
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        std::cerr << "[Server] Failed to create socket." << std::endl;
        return -1;
    }

    // 2. 소켓 옵션 설정 (주소 재사용 허용)
    int opt = 1;
    if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        std::cerr << "[Server] setsockopt failed." << std::endl;
        close(serverSocket);
        return -1;
    }

    // 3. 서버 주소 구조체 설정
    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY; // 모든 네트워크 인터페이스에서 수신
    serverAddr.sin_port = htons(port);

    // 4. 소켓에 주소 바인딩
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "[Server] Bind failed on port " << port << std::endl;
        close(serverSocket);
        return -1;
    }

    // 5. 연결 대기 (최대 대기 큐: 10)
    if (listen(serverSocket, 10) < 0) {
        std::cerr << "[Server] Listen failed." << std::endl;
        close(serverSocket);
        return -1;
    }

    std::cout << "========================================" << std::endl;
    std::cout << "  Multi-threaded TCP Server Started" << std::endl;
    std::cout << "  Listening on Port: " << port << std::endl;
    std::cout << "========================================" << std::endl;

    // 6. 클라이언트 접속 대기 루프
    int clientId = 0;
    while (true) {
        struct sockaddr_in clientAddr;
        socklen_t clientAddrLen = sizeof(clientAddr);
  
        // 클라이언트 접속 대기 (Blocking)
        int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrLen);
  
        if (clientSocket < 0) {
            std::cerr << "[Server] Accept failed." << std::endl;
            continue;
        }

        // 클라이언트 IP 주소 얻기
        char clientIP[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &clientAddr.sin_addr, clientIP, INET_ADDRSTRLEN);
  
        // 클라이언트 수 증가
        g_clientCounter++;
        clientId++;
  
        std::cout << "[Server] New connection from " << clientIP 
                  << " (Total clients: " << g_clientCounter.load() << ")" << std::endl;

        // 7. 클라이언트 전담 쓰래드 생성 및 detach
        std::thread clientThread(clientHandler, clientSocket, clientId, std::string(clientIP));
        clientThread.detach(); // 쓰래드를 독립적으로 실행 (메인 쓰래드는 기다리지 않음)
    }

    // 서버 소켓 닫기 (실제로는 Ctrl+C 등으로 종료됨)
    close(serverSocket);
    return 0;
}