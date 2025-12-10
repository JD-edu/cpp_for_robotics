#include <iostream>
#include "MotorController.h"

int main() {
    MotorController motor;

    std::cout << "=== 예외 처리 테스트 ===" << std::endl;

    // 1. 정상 동작
    try {
        motor.setSpeed(50.0);
        std::cout << "현재 속도: " << motor.getSpeed() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "오류: " << e.what() << std::endl;
    }

    // 2. 범위 초과 예외 발생
    try {
        motor.setSpeed(150.0);  // 범위 초과!
    }
    catch (const std::out_of_range& e) {
        std::cerr << "범위 오류: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "기타 오류: " << e.what() << std::endl;
    }

    // 3. 연결 해제 후 예외 발생
    motor.disconnect();
    try {
        motor.setSpeed(30.0);  // 연결 안됨!
    }
    catch (const std::runtime_error& e) {
        std::cerr << "실행 오류: " << e.what() << std::endl;
    }

    std::cout << "\n프로그램 정상 종료" << std::endl;
    return 0;
}
