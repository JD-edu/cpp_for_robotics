#include <iostream>
#include "BaseRobot.h"
#include "ExplorerRobot.h"

int main() {
    std::cout << "=== 탐사 로봇 테스트 ===" << std::endl;

    // 1. 탐사 로봇 생성 (최대 속도 3.0m/s)
    ExplorerRobot explorer("패스파인더", 3.0);
    explorer.displayStatus();

    // 2. 로봇 활성화 및 스캔 모드 켜기
    std::cout << "\n--- 탐사 로봇 작동 ---" << std::endl;
    explorer.powerOn();
    explorer.enableScanMode();

    // 3. 이동하면서 자동 스캔
    std::cout << "\n--- 이동 & 자동 스캔 ---" << std::endl;
    explorer.move(5.0, 5.0);   // 속도 제한으로 3.0m만 이동 + 스캔
    explorer.move(2.0, 1.0);   // 이동 + 스캔

    // 4. 수동 스캔
    std::cout << "\n--- 수동 스캔 ---" << std::endl;
    explorer.scanEnvironment();

    // 5. 탐사 후 상태 확인
    std::cout << "\n--- 탐사 후 상태 ---" << std::endl;
    explorer.displayStatus();

    std::cout << "\n=== 프로그램 종료 ===" << std::endl;
    return 0;
}