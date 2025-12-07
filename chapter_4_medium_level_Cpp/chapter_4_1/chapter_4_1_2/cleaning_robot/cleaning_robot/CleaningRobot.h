#pragma once
#include <iostream>
#include "BaseRobot.h"

// CleaningRobot은 BaseRobot을 public으로 상속받습니다
// public 상속: 부모의 public 멤버는 자식에서도 public으로 유지됩니다
class CleaningRobot : public BaseRobot {
private:
    // 청소 로봇만의 추가 멤버 변수들
    double dustCapacity;      // 먼지통 최대 용량 (g)
    double currentDust;       // 현재 먼지통에 쌓인 먼지량 (g)
    bool isVacuumOn;         // 진공청소기 작동 상태

public:
    // 생성자 - 부모 클래스(BaseRobot)의 생성자를 먼저 호출해야 합니다
    // : BaseRobot(robotName) 부분이 부모 생성자 호출입니다
    CleaningRobot(const std::string& robotName, double capacity = 500.0)
        : BaseRobot(robotName),  // 부모 클래스 생성자 호출
        dustCapacity(capacity),
        currentDust(0.0),
        isVacuumOn(false) {
        std::cout << "청소 로봇 '" << name << "' 초기화 완료" << std::endl;
        // 여기서 name을 사용할 수 있는 이유는 부모 클래스의 public 멤버이기 때문입니다
    }

    // ========== 청소 로봇만의 고유 메서드들 ==========

    void startVacuum() {
        // 부모 클래스의 isActive 멤버 변수를 직접 사용 가능 (public이므로)
        if (!isActive) {
            std::cout << "로봇을 먼저 켜주세요." << std::endl;
            return;
        }

        isVacuumOn = true;
        std::cout << name << " 청소 시작!" << std::endl;
    }

    void stopVacuum() {
        isVacuumOn = false;
        std::cout << name << " 청소 중지" << std::endl;
    }

    void clean(double area) {
        if (!isActive || !isVacuumOn) {
            std::cout << "청소기를 먼저 켜주세요." << std::endl;
            return;
        }

        double dustCollected = area * 0.1;  // 1㎡당 0.1g의 먼지 수집

        // 먼지통 용량 확인
        if (currentDust + dustCollected > dustCapacity) {
            std::cout << "먼지통이 가득참! 비워주세요." << std::endl;
            return;
        }

        currentDust += dustCollected;
        battery -= area * 0.02;  // 청소 시 배터리 추가 소모 (1㎡당 0.02%)

        std::cout << name << " " << area << "㎡ 청소 완료. 수집된 먼지: "
            << dustCollected << "g" << std::endl;
    }

    void emptyDustbin() {
        currentDust = 0.0;
        std::cout << name << " 먼지통 비움" << std::endl;
    }

    // ========== 부모 클래스 메서드 오버라이드 ==========

    // move() 메서드를 재정의하여 청소 로봇만의 동작 추가
    // override 키워드: 실수로 오타를 내면 컴파일 에러로 알려줌 (안전장치)
    void move(double deltaX, double deltaY) {
        // 먼저 부모 클래스의 move()를 호출하여 기본 이동 수행
        BaseRobot::move(deltaX, deltaY);

        // 청소 로봇의 특별한 동작: 이동하면서 동시에 청소!
        if (isVacuumOn && isActive) {
            clean(1.0);  // 이동 경로 1㎡를 자동으로 청소
        }
    }

    // displayStatus()도 재정의하여 청소 로봇 정보 추가 출력
    void displayStatus() {
        BaseRobot::displayStatus();  // 부모의 상태 먼저 표시
        // 추가로 청소 로봇만의 정보 표시
        std::cout << "먼지통: " << currentDust << "/" << dustCapacity << "g" << std::endl;
        std::cout << "청소기: " << (isVacuumOn ? "작동 중" : "정지") << std::endl;
        std::cout << "==================" << std::endl;
    }
};