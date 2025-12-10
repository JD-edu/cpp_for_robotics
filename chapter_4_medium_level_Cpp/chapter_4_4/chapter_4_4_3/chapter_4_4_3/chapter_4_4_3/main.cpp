#include <iostream>
#include "ExecutionHistory.h"

int main() {
    std::cout << "=== list 활용: 로봇 실행 기록 ===\n" << std::endl;

    ExecutionHistory history;

    // 1. 기록 추가
    history.addRecord("전진 10cm");
    history.addRecord("좌회전 90도");
    history.addRecord("장애물 스캔");
    history.addRecord("후진 5cm");

    // 2. 모든 기록 출력
    history.displayAll();

    // 3. 중간 기록 삭제 (list의 강점!)
    history.removeRecord("좌회전 90도");
    history.displayAll();

    return 0;
}