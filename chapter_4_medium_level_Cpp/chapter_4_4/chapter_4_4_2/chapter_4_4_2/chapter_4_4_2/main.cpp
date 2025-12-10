#include <iostream>
#include "RobotConfig.h"

int main() {
    std::cout << "=== map 활용: 로봇 설정 관리 ===\n" << std::endl;

    RobotConfig config;

    // 1. 설정 추가 (map의 [])
    std::cout << "[ 1단계: 설정 추가 ]" << std::endl;
    config.setSetting("maxSpeed", 100.0);
    config.setSetting("minSpeed", 10.0);
    config.setSetting("acceleration", 50.0);
    config.setSetting("batteryCapacity", 5000.0);

    // 2. 모든 설정 출력 (자동 정렬됨!)
    config.displayAll();

    // 3. 설정 조회 (map의 find)
    std::cout << "[ 2단계: 설정 조회 ]" << std::endl;
    double maxSpeed = config.getSetting("maxSpeed");
    std::cout << "최대 속도: " << maxSpeed << " cm/s" << std::endl;

    double turnSpeed = config.getSetting("turnSpeed", 30.0);  // 없는 키 (기본값 사용)

    // 4. 설정 존재 확인 (map의 count)
    std::cout << "\n[ 3단계: 설정 존재 확인 ]" << std::endl;
    std::cout << "maxSpeed 설정 있음? "
        << (config.hasSetting("maxSpeed") ? "예" : "아니오") << std::endl;
    std::cout << "turnSpeed 설정 있음? "
        << (config.hasSetting("turnSpeed") ? "예" : "아니오") << std::endl;

    // 5. 설정 수정 (기존 키에 다시 저장)
    std::cout << "\n[ 4단계: 설정 수정 ]" << std::endl;
    config.setSetting("maxSpeed", 150.0);  // 100 → 150으로 수정
    config.displayAll();

    // 6. 설정 삭제 (map의 erase)
    std::cout << "[ 5단계: 설정 삭제 ]" << std::endl;
    config.removeSetting("minSpeed");
    config.displayAll();

    return 0;
}