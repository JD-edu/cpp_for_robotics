#include <exception>
#include <stdexcept>
#include <iostream>

class MotorController {
public:
    MotorController() : isConnected(true), currentSpeed(0.0) {}

    void setSpeed(double speed) {
        // 범위 검사
        if (speed < -100.0 || speed > 100.0) {
            throw std::out_of_range("속도 범위 초과");
        }

        // 연결 상태 검사
        if (!isConnected) {
            throw std::runtime_error("모터 미연결");
        }

        currentSpeed = speed;
        std::cout << "모터 속도 설정: " << speed << std::endl;
    }

    double getSpeed() const { return currentSpeed; }
    void disconnect() { isConnected = false; }

private:
    bool isConnected;
    double currentSpeed;
};
