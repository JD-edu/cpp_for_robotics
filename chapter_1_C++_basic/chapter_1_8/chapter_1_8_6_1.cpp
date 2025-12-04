#include <iostream>

// 기본 매개변수를 가진 로봇 이동 함수
void moveRobot(double distance, double speed = 1.0, bool enableSafety = true) {
    std::cout << "로봇 이동 - 거리: " << distance << "m, 속도: " << speed << "m/s, 안전모드: " 
              << (enableSafety ? "ON" : "OFF") << std::endl;
}

// 서보 모터 제어 함수
void controlServo(int angle, int speed = 50, int torque = 100) {
    std::cout << "서보 제어 - 각도: " << angle << "도, 속도: " << speed 
              << "%, 토크: " << torque << "%" << std::endl;
}

// LED 제어 함수
void controlLED(int brightness, int red = 255, int green = 255, int blue = 255) {
    std::cout << "LED 제어 - 밝기: " << brightness << "%, RGB(" 
              << red << ", " << green << ", " << blue << ")" << std::endl;
}

int main() {
    // 기본 매개변수 사용 예시
    std::cout << "=== 로봇 이동 제어 ===" << std::endl;
    moveRobot(10.0);                    // 기본 속도, 기본 안전모드
    moveRobot(5.0, 2.0);               // 사용자 지정 속도, 기본 안전모드
    moveRobot(15.0, 1.5, false);       // 모든 매개변수 지정

    std::cout << "\n=== 서보 모터 제어 ===" << std::endl;
    controlServo(90);           // 기본 속도, 기본 토크
    controlServo(45, 30);       // 사용자 지정 속도, 기본 토크
    controlServo(180, 70, 80);  // 모든 매개변수 지정

    std::cout << "\n=== LED 제어 ===" << std::endl;
    controlLED(80);                     // 기본 RGB (흰색)
    controlLED(60, 255, 0, 0);         // 빨간색
    controlLED(100, 0, 255, 0);        // 녹색

    return 0;
}
