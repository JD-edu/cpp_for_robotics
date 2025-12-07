#pragma once
#include <iostream>
#include <string>

class BaseRobot {
public:    // 모든 멤버를 public으로 간단하게 시작
    std::string name;
    double x, y;        // 위치 좌표
    double battery;     // 배터리 잔량 (0.0 ~ 100.0)
    bool isActive;

    // 생성자
    BaseRobot(const std::string& robotName, double startX = 0.0, double startY = 0.0)
        : name(robotName), x(startX), y(startY), battery(100.0), isActive(false) {
        std::cout << "기본 로봇 '" << name << "' 생성됨" << std::endl;
    }

    // 소멸자
    ~BaseRobot() {
        std::cout << "로봇 '" << name << "' 해제됨" << std::endl;
    }

    // 기본 동작 메서드들
    void powerOn() {
        isActive = true;
        std::cout << name << " 전원 켜짐" << std::endl;
    }

    void powerOff() {
        isActive = false;
        std::cout << name << " 전원 꺼짐" << std::endl;
    }

    void move(double deltaX, double deltaY) {
        if (!isActive) {
            std::cout << "로봇이 비활성 상태입니다." << std::endl;
            return;
        }

        x += deltaX;
        y += deltaY;
        battery -= 0.5;  // 이동 시 배터리 소모

        std::cout << name << " 이동: (" << x << ", " << y << ")" << std::endl;
    }

    void displayStatus() {
        std::cout << "=== " << name << " 상태 ===" << std::endl;
        std::cout << "위치: (" << x << ", " << y << ")" << std::endl;
        std::cout << "배터리: " << battery << "%" << std::endl;
        std::cout << "활성화: " << (isActive ? "예" : "아니오") << std::endl;
    }
};