#include <iostream>
#include "BaseRobot.h"

int main() {
    std::cout << "=== BaseRobot 클래스 테스트 ===" << std::endl;

    // 1. 로봇 생성
    BaseRobot robot("탐험가-1");
    robot.displayStatus();

    // 2. 로봇 활성화 및 이동
    std::cout << "\n--- 로봇 작동 ---" << std::endl;
    robot.powerOn();
    robot.move(5.0, 3.0);
    robot.move(2.0, -1.0);

    // 3. 이동 후 상태 확인
    std::cout << "\n--- 이동 후 상태 ---" << std::endl;
    robot.displayStatus();

    // 4. 전원 꺼진 상태 테스트
    std::cout << "\n--- 비활성 상태 테스트 ---" << std::endl;
    robot.powerOff();
    robot.move(5.0, 5.0);  // 이동 안 됨

    std::cout << "\n=== 프로그램 종료 ===" << std::endl;
    return 0;
}