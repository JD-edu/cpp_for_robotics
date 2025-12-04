#include <iostream>

// 포인터를 이용한 전달 - 원본값이 변경됨
void setMotorSpeedPtr(int* speed) {
    *speed = *speed * 2; // 원본값이 변경됨
}

// 두 값을 교환하는 함수
void swapValues(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 로봇 위치를 업데이트하는 함수
void updateRobotPosition(double* x, double* y, double deltaX, double deltaY) {
    *x += deltaX;
    *y += deltaY;
}

int main() {
    int motorSpeed = 100;
    std::cout << "원래 속도: " << motorSpeed << std::endl;
    setMotorSpeedPtr(&motorSpeed);
    std::cout << "함수 호출 후 속도: " << motorSpeed << std::endl; // 변경됨

    int servo1 = 90, servo2 = 180;
    std::cout << "교환 전: servo1=" << servo1 << ", servo2=" << servo2 << std::endl;
    swapValues(&servo1, &servo2);
    std::cout << "교환 후: servo1=" << servo1 << ", servo2=" << servo2 << std::endl;

    double robotX = 10.0, robotY = 20.0;
    std::cout << "이동 전 위치: (" << robotX << ", " << robotY << ")" << std::endl;
    updateRobotPosition(&robotX, &robotY, 5.0, 3.0);
    std::cout << "이동 후 위치: (" << robotX << ", " << robotY << ")" << std::endl;

    return 0;
}
