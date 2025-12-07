#pragma once
#include "BaseRobot.h"

// 탐사 로봇: BaseRobot을 상속받아 환경 탐사 기능 추가
class ExplorerRobot : public BaseRobot {
private:
    // 탐사 로봇만의 추가 멤버 변수들
    double maxSpeed;           // 탐사 로봇의 최대 속도
    bool isScanMode;           // 스캔 모드 활성화 여부
    int scanCount;             // 스캔 횟수 카운터

    // 가장 최근 센서 데이터 (간단하게 단일 값으로 저장)
    double lastTemperature;
    double lastHumidity;
    double lastObstacleDistance;

public:
    // 생성자 - maxSpeed를 매개변수로 받음 (청소 로봇과 다른 점)
    ExplorerRobot(const std::string& robotName, double speed = 2.0)
        : BaseRobot(robotName),  // 부모 생성자 호출
        maxSpeed(speed),       // 탐사 로봇 멤버 초기화
        isScanMode(false),
        scanCount(0),
        lastTemperature(0.0),
        lastHumidity(0.0),
        lastObstacleDistance(0.0) {
        std::cout << "탐사 로봇 '" << name << "' 초기화 완료 (최대속도: "
            << maxSpeed << "m/s)" << std::endl;
    }

    // ========== 탐사 로봇만의 고유 메서드들 ==========

    void enableScanMode() {
        if (!isActive) {
            std::cout << "로봇을 먼저 켜주세요." << std::endl;
            return;
        }

        isScanMode = true;
        std::cout << name << " 스캔 모드 활성화" << std::endl;
    }

    void disableScanMode() {
        isScanMode = false;
        std::cout << name << " 스캔 모드 비활성화" << std::endl;
    }

    // 환경을 스캔하여 센서 데이터 수집 (탐사 로봇의 핵심 기능!)
    void scanEnvironment() {
        if (!isActive || !isScanMode) {
            std::cout << "스캔 모드를 먼저 활성화하세요." << std::endl;
            return;
        }

        // 실제 로봇에서는 센서로부터 데이터를 읽어옴
        // 여기서는 시뮬레이션을 위해 랜덤 데이터 생성
        lastTemperature = 20.0 + (rand() % 30);           // 20~50°C
        lastHumidity = 40.0 + (rand() % 40);              // 40~80%
        lastObstacleDistance = 1.0 + (rand() % 50) / 10.0;  // 1~6m

        scanCount++;  // 스캔 횟수 증가
        battery -= 1.0;  // 스캔은 배터리를 많이 소모 (이동의 2배)

        std::cout << name << " 환경 스캔 완료 - 온도: " << lastTemperature
            << "°C, 습도: " << lastHumidity << "%, 장애물 거리: "
            << lastObstacleDistance << "m" << std::endl;
    }

    // ========== 부모 클래스 메서드 오버라이드 (청소 로봇과 다른 방식!) ==========

    // move() 메서드를 완전히 재정의 - 청소 로봇과는 다른 전략!
    void move(double deltaX, double deltaY) {
        if (!isActive) {
            std::cout << "로봇이 비활성 상태입니다." << std::endl;
            return;
        }

        // 탐사 로봇의 특별한 기능: 속도 제한 체크
        // 청소 로봇은 천천히 움직이지만, 탐사 로봇은 빠르게 이동!
        double distance = sqrt(deltaX * deltaX + deltaY * deltaY);
        if (distance > maxSpeed) {
            // 요청된 이동 거리가 최대 속도를 초과하면 제한
            deltaX = deltaX / distance * maxSpeed;
            deltaY = deltaY / distance * maxSpeed;
            distance = maxSpeed;
        }

        // 위치 업데이트 (부모의 move()를 호출하지 않고 직접 처리)
        x += deltaX;
        y += deltaY;
        battery -= distance * 0.3;  // 고속 이동이라 배터리 소모가 더 큼

        std::cout << name << " 고속 이동: (" << x << ", " << y << ")"
            << " [이동거리: " << distance << "m]" << std::endl;

        // 탐사 로봇의 특별한 동작: 이동하면서 자동 환경 스캔!
        // (청소 로봇은 청소하고, 탐사 로봇은 스캔함 - 같은 패턴, 다른 동작)
        if (isScanMode) {
            scanEnvironment();
        }
    }

    // displayStatus()도 재정의하여 탐사 로봇 정보 추가
    void displayStatus() {
        BaseRobot::displayStatus();  // 부모의 상태 먼저 표시
        // 탐사 로봇만의 추가 정보
        std::cout << "최대 속도: " << maxSpeed << "m/s" << std::endl;
        std::cout << "스캔 모드: " << (isScanMode ? "활성" : "비활성") << std::endl;
        std::cout << "스캔 횟수: " << scanCount << "회" << std::endl;
        if (scanCount > 0) {
            std::cout << "최근 측정값 - 온도: " << lastTemperature << "°C, "
                << "습도: " << lastHumidity << "%, "
                << "장애물: " << lastObstacleDistance << "m" << std::endl;
        }
        std::cout << "==================" << std::endl;
    }
};