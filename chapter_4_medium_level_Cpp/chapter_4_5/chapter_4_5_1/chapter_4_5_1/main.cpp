#include <iostream>
#include "RobotConfig.h"

int main() {
    RobotConfig config;

    // 설정 로드 또는 기본값 사용
    if (config.loadConfig("robot.cfg")) {
        std::cout << "설정 로드 성공" << std::endl;
    }
    else {
        std::cout << "기본 설정 사용" << std::endl;
        config.saveConfig("robot.cfg");  // 기본값으로 파일 생성
    }

    config.printConfig();

    // 설정 변경 및 저장
    config.setMaxSpeed(2.5);
    config.saveConfig("robot.cfg");
    std::cout << "설정 저장 완료" << std::endl;

    return 0;
}
