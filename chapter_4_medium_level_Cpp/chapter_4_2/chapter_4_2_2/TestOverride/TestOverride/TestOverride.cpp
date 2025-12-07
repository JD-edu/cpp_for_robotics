#include <iostream>
#include "BaseRobot.h"
#include "CleaningRobot.h"
#include "ExplorerRobot.h"

int main() {
    std::cout << "=== 오버라이드 동작 비교 예제 ===" << std::endl;

    // ========== 1. 기본 로봇 (부모) ==========
    std::cout << "\n--- 1. 기본 로봇 (BaseRobot) ---" << std::endl;
    BaseRobot baseRobot("기본로봇");
    baseRobot.powerOn();

    std::cout << "\n[이동 전 상태]" << std::endl;
    baseRobot.displayStatus();

    std::cout << "\n[move(5, 3) 실행]" << std::endl;
    baseRobot.move(5.0, 3.0);

    std::cout << "\n[이동 후 상태]" << std::endl;
    baseRobot.displayStatus();

    // ========== 2. 청소 로봇 ==========
    std::cout << "\n\n--- 2. 청소 로봇 (CleaningRobot) ---" << std::endl;
    CleaningRobot cleanBot("청소로봇");
    cleanBot.powerOn();
    cleanBot.startVacuum();  // 청소기 켜기

    std::cout << "\n[이동 전 상태]" << std::endl;
    cleanBot.displayStatus();

    std::cout << "\n[move(5, 3) 실행 - 청소하면서 이동!]" << std::endl;
    cleanBot.move(5.0, 3.0);

    std::cout << "\n[이동 후 상태]" << std::endl;
    cleanBot.displayStatus();

    // ========== 3. 탐사 로봇 ==========
    std::cout << "\n\n--- 3. 탐사 로봇 (ExplorerRobot) ---" << std::endl;
    ExplorerRobot explorerBot("탐사로봇", 2.0);  // 최대속도 2m/s
    explorerBot.powerOn();
    explorerBot.enableScanMode();  // 스캔 모드 켜기

    std::cout << "\n[이동 전 상태]" << std::endl;
    explorerBot.displayStatus();

    std::cout << "\n[move(5, 3) 실행 - 스캔하면서 이동!]" << std::endl;
    explorerBot.move(5.0, 3.0);

    std::cout << "\n[이동 후 상태]" << std::endl;
    explorerBot.displayStatus();

    // ========== 4. 오버라이드의 효과 비교 ==========
    std::cout << "\n\n=== 오버라이드 효과 비교 ===" << std::endl;
    std::cout << "\n같은 move(5, 3) 명령이지만:" << std::endl;
    std::cout << "• 기본 로봇: 단순히 (5, 3)만큼 이동" << std::endl;
    std::cout << "• 청소 로봇: 이동 + 1㎡ 청소" << std::endl;
    std::cout << "• 탐사 로봇: 속도 제한 체크 + 이동 + 환경 스캔" << std::endl;

    std::cout << "\n배터리 소모도 다릅니다:" << std::endl;
    std::cout << "• 기본 로봇: 0.5% 고정" << std::endl;
    std::cout << "• 청소 로봇: 0.5% (이동) + 청소 추가 소모" << std::endl;
    std::cout << "• 탐사 로봇: 거리 × 0.3% (고속 이동)" << std::endl;

    return 0;
}