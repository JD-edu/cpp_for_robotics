#pragma once
#include <queue>
#include <string>
#include <iostream>

// queue를 사용한 로봇 명령 큐 클래스
class RobotCommandQueue {
private:
    std::queue<std::string> commands;  // 📌 queue로 명령 저장 (FIFO)

public:
    // 명령 추가 (큐의 뒤에)
    void addCommand(const std::string& command) {
        commands.push(command);  // ⭐ queue에 추가
        std::cout << "명령 추가: " << command << std::endl;
    }

    // 다음 명령 실행 (큐에서 제거)
    bool executeNext() {
        if (commands.empty()) {
            std::cout << "실행할 명령이 없습니다." << std::endl;
            return false;
        }

        std::string cmd = commands.front();  // ⭐ 맨 앞 확인
        commands.pop();                       // ⭐ 큐에서 제거
        std::cout << "▶ 실행: " << cmd << std::endl;
        return true;
    }

    // 큐 상태 출력
    void displayStatus() const {
        std::cout << "\n대기 중인 명령: " << commands.size() << "개" << std::endl;
        if (!commands.empty()) {
            std::cout << "다음 실행 예정: " << commands.front() << std::endl;
        }
        std::cout << std::endl;
    }
};