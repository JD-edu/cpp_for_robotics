#include <iostream>
#include "RobotCommandQueue.h"

int main() {
    std::cout << "=== queue 활용: 로봇 명령 큐 ===\n" << std::endl;

    RobotCommandQueue cmdQueue;

    // 1. 명령 추가 (FIFO 순서대로)
    cmdQueue.addCommand("전진 50cm");
    cmdQueue.addCommand("좌회전 90도");
    cmdQueue.addCommand("장애물 스캔");
    cmdQueue.addCommand("후진 20cm");

    // 2. 큐 상태 확인
    cmdQueue.displayStatus();

    // 3. 명령 순차 실행
    std::cout << "[ 명령 실행 ]" << std::endl;
    cmdQueue.executeNext();
    cmdQueue.executeNext();

    // 4. 남은 명령 확인
    cmdQueue.displayStatus();

    // 5. 나머지 실행
    while (cmdQueue.executeNext()) {
        // 모든 명령 실행
    }

    cmdQueue.displayStatus();

    return 0;
}