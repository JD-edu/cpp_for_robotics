#include <iostream>
#include "PathManager.h"

int main() {
    std::cout << "=== vector 활용: 로봇 경로 관리 ===\n" << std::endl;

    PathManager pathMgr;

    // 1. 경유점 추가 (vector의 push_back)
    std::cout << "[ 1단계: 경유점 추가 ]" << std::endl;
    pathMgr.addWaypoint(Point(0, 0));      // 시작점
    pathMgr.addWaypoint(Point(10, 0));     // 동쪽으로 10m
    pathMgr.addWaypoint(Point(10, 10));    // 북쪽으로 10m
    pathMgr.addWaypoint(Point(0, 10));     // 서쪽으로 10m

    // 2. 경로 정보 출력 (vector 순회)
    pathMgr.displayPath();

    // 3. 경유점 제거 (vector의 erase)
    std::cout << "[ 2단계: 2번째 경유점 제거 ]" << std::endl;
    pathMgr.removeWaypoint(1);
    pathMgr.displayPath();

    // 4. vector 메서드 활용
    std::cout << "[ 3단계: 상태 확인 ]" << std::endl;
    std::cout << "경유점 개수: " << pathMgr.getWaypointCount() << "개" << std::endl;
    std::cout << "경로 비어있음? " << (pathMgr.isEmpty() ? "예" : "아니오") << std::endl;

    return 0;
}