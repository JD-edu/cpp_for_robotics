#include <iostream>
#include <vector>
#include <memory>
#include "BaseRobot.h"
#include "CleaningRobot.h"
#include "ExplorerRobot.h"

// 다형성을 활용한 로봇 관리 함수
void controlRobot(BaseRobot* robot) {
    std::cout << "\n=== 로봇 제어 시작 ===" << std::endl;

    robot->powerOn();
    robot->move(5.0, 3.0);
    robot->displayStatus();  // 각 로봇의 오버라이드된 메서드 호출

    std::cout << "=== 로봇 제어 완료 ===\n" << std::endl;
}

int main() {
    std::cout << "로보틱스 C++ - 상속과 오버라이드 예제" << std::endl;

    // 다양한 로봇 객체 생성
    CleaningRobot cleaner("로보청소기-1");
    ExplorerRobot explorer("탐사로봇-Alpha", 3.5);

    // 청소 로봇 테스트
    std::cout << "\n--- 청소 로봇 테스트 ---" << std::endl;
    cleaner.powerOn();
    cleaner.startVacuum();
    cleaner.move(2.0, 2.0);  // 이동하면서 청소
    cleaner.clean(10.0);     // 추가 청소
    cleaner.displayStatus();

    // 탐사 로봇 테스트  
    std::cout << "\n--- 탐사 로봇 테스트 ---" << std::endl;
    explorer.powerOn();
    explorer.enableScanMode();
    explorer.move(10.0, 5.0);  // 고속 이동하면서 스캔
    explorer.scanEnvironment();
    explorer.displayStatus();  // 최근 스캔 데이터는 displayStatus()에 표시됨

    // 다형성 활용 - 같은 함수로 다른 타입의 로봇 제어
    std::cout << "\n--- 다형성 테스트 ---" << std::endl;
    controlRobot(&cleaner);
    controlRobot(&explorer);

    // 스마트 포인터를 사용한 로봇 배열
    std::vector<std::unique_ptr<BaseRobot>> robotFleet;
    robotFleet.push_back(std::make_unique<CleaningRobot>("청소로봇-2"));
    robotFleet.push_back(std::make_unique<ExplorerRobot>("탐사로봇-Beta", 4.0));

    std::cout << "\n--- 로봇 함대 관리 ---" << std::endl;
    for (auto& robot : robotFleet) {
        controlRobot(robot.get());
    }

    return 0;
}