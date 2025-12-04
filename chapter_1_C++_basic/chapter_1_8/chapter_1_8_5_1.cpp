#include <iostream>
#include <cmath>

// 정수형 거리 계산
double calculateDistance(int x1, int y1, int x2, int y2) {
    std::cout << "정수형 좌표로 거리 계산" << std::endl;
    return sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
}

// 실수형 거리 계산
double calculateDistance(double x1, double y1, double x2, double y2) {
    std::cout << "실수형 좌표로 거리 계산" << std::endl;
    return sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
}

// 3차원 거리 계산 (매개변수 개수가 다름)
double calculateDistance(double x1, double y1, double z1, double x2, double y2, double z2) {
    std::cout << "3차원 좌표로 거리 계산" << std::endl;
    return sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1) + (z2-z1)*(z2-z1));
}

// 모터 제어 함수 오버로딩
void controlMotor(int speed) {
    std::cout << "단일 모터 속도 설정: " << speed << std::endl;
}

void controlMotor(int leftSpeed, int rightSpeed) {
    std::cout << "좌측 모터: " << leftSpeed << ", 우측 모터: " << rightSpeed << std::endl;
}

void controlMotor(int speed, bool direction) {
    std::cout << "모터 속도: " << speed << ", 방향: " << (direction ? "정방향" : "역방향") << std::endl;
}

int main() {
    // 거리 계산 함수 오버로딩 사용
    double dist1 = calculateDistance(0, 0, 3, 4);                    // 정수형
    double dist2 = calculateDistance(0.0, 0.0, 3.5, 4.2);          // 실수형
    double dist3 = calculateDistance(0.0, 0.0, 0.0, 1.0, 1.0, 1.0); // 3차원

    std::cout << "2D 거리 (정수): " << dist1 << std::endl;
    std::cout << "2D 거리 (실수): " << dist2 << std::endl;
    std::cout << "3D 거리: " << dist3 << std::endl;

    // 모터 제어 함수 오버로딩 사용
    controlMotor(100);        // 단일 모터
    controlMotor(100, 150);   // 양쪽 모터
    controlMotor(100, true);  // 속도와 방향

    return 0;
}
