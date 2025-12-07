#include <iostream>
#include "BaseRobot.h"
#include "CleaningRobot.h"

int main() {
    std::cout << "=== 청소 로봇 테스트 ===" << std::endl;

    // 1. 청소 로봇 생성
    CleaningRobot cleaner("룸바");
    cleaner.displayStatus();

    // 2. 로봇 활성화 및 청소기 켜기
    std::cout << "\n--- 청소 로봇 작동 ---" << std::endl;
    cleaner.powerOn();
    cleaner.startVacuum();

    // 3. 이동하면서 자동 청소
    std::cout << "\n--- 이동 & 자동 청소 ---" << std::endl;
    cleaner.move(3.0, 0.0);    // 이동하면서 1㎡ 청소
    cleaner.move(0.0, 3.0);    // 이동하면서 1㎡ 청소
    cleaner.move(2.0, 2.0);    // 이동하면서 1㎡ 청소

    // 4. 수동 청소
    std::cout << "\n--- 수동 청소 ---" << std::endl;
    cleaner.clean(10.0);       // 10㎡ 청소

    // 5. 청소 후 상태 확인
    std::cout << "\n--- 청소 후 상태 ---" << std::endl;
    cleaner.displayStatus();

    // 6. 먼지통 비우기
    std::cout << "\n--- 먼지통 비우기 ---" << std::endl;
    cleaner.emptyDustbin();
    cleaner.displayStatus();

    std::cout << "\n=== 프로그램 종료 ===" << std::endl;
    return 0;
}