#include <iostream>

using namespace std;
class SimpleRobot {
private:
    string name;
    int battery;
    bool isActive;

public:
    // 생성자 오버로딩
    SimpleRobot() : name("로봇"), battery(100), isActive(false) {}
    SimpleRobot(string robotName) : name(robotName), battery(100), isActive(false) {}

    // 로봇 제어 메서드
    void powerOn() {
        if (battery > 0) {
            isActive = true;
        }
    }

    void powerOff() {
        isActive = false;
    }

    // 함수 오버로딩 - 이동 명령
    void move() {
        if (isActive) {
            battery -= 1;
        }
    }

    void move(int distance) {
        if (isActive) {
            battery -= distance / 10;
        }
    }

    // 상태 확인 (캡슐화)
    int getBattery() const { return battery; }
    bool getStatus() const { return isActive; }
    string getName() const { return name; }
};

