#include <iostream>

// 값에 의한 전달 - 원본값은 변경되지 않음
void setMotorSpeed(int speed) {
    speed = speed * 2; // 지역적으로만 변경됨
    std::cout << "함수 내부 속도: " << speed << std::endl;
}

// 로봇 좌표를 이동시키는 함수
void moveRobot(double x, double y, double distance) {
    x += distance;
    y += distance;
    std::cout << "함수 내부 새 위치: (" << x << ", " << y << ")" << std::endl;
}

int main() {
    int motorSpeed = 100;
    std::cout << "원래 속도: " << motorSpeed << std::endl;
    setMotorSpeed(motorSpeed);
    std::cout << "함수 호출 후 속도: " << motorSpeed << std::endl; // 변경되지 않음

    double robotX = 10.0, robotY = 20.0;
    std::cout << "원래 위치: (" << robotX << ", " << robotY << ")" << std::endl;
    moveRobot(robotX, robotY, 5.0);
    std::cout << "함수 호출 후 위치: (" << robotX << ", " << robotY << ")" << std::endl; // 변경되지 않음

    return 0;
}
