#pragma once
#include "BaseRobot.h"
#include <string>

// 군사 로봇: 초기 위치와 무장 정보를 받아 생성
class MilitaryRobot : public BaseRobot {
private:
    // 군사 로봇만의 추가 멤버
    std::string weaponType;     // 무장 타입
    int ammunition;             // 탄약 수
    double armor;               // 방어력 (0.0 ~ 100.0)
    bool isWeaponActive;        // 무장 활성화 상태

public:
    // 파라미터가 많은 생성자
    // 부모 클래스에 이름 + 초기 위치(startX, startY)를 모두 전달!
    MilitaryRobot(const std::string& robotName,
        double startX,           // 배치 X 좌표
        double startY,           // 배치 Y 좌표
        const std::string& weapon = "Machine Gun",
        int ammo = 100)
        : BaseRobot(robotName, startX, startY),  // 부모에게 3개 파라미터 전달!
        weaponType(weapon),
        ammunition(ammo),
        armor(100.0),
        isWeaponActive(false) {
        std::cout << "군사 로봇 '" << name << "' 배치 완료" << std::endl;
        std::cout << "  위치: (" << x << ", " << y << ")" << std::endl;
        std::cout << "  무장: " << weaponType << " (탄약: " << ammunition << ")" << std::endl;
    }

    // ========== 군사 로봇만의 고유 메서드 ==========

    void activateWeapon() {
        if (!isActive) {
            std::cout << "로봇을 먼저 활성화하세요." << std::endl;
            return;
        }

        isWeaponActive = true;
        std::cout << name << " " << weaponType << " 활성화!" << std::endl;
    }

    void deactivateWeapon() {
        isWeaponActive = false;
        std::cout << name << " " << weaponType << " 비활성화" << std::endl;
    }

    void fire() {
        if (!isActive || !isWeaponActive) {
            std::cout << "무장을 먼저 활성화하세요." << std::endl;
            return;
        }

        if (ammunition <= 0) {
            std::cout << "탄약 부족! 재장전이 필요합니다." << std::endl;
            return;
        }

        ammunition--;
        battery -= 2.0;  // 사격 시 배터리 소모
        std::cout << name << " 발사! (잔여 탄약: " << ammunition << ")" << std::endl;
    }

    void reload(int ammo) {
        ammunition += ammo;
        std::cout << name << " 재장전: +" << ammo << " (총 " << ammunition << "발)" << std::endl;
    }

    void takeDamage(double damage) {
        armor -= damage;
        if (armor < 0) armor = 0;

        std::cout << name << " 피격! (데미지: " << damage << ", 잔여 방어력: "
            << armor << "%)" << std::endl;

        if (armor == 0) {
            std::cout << "경고: " << name << " 방어력이 0입니다!" << std::endl;
            powerOff();  // 자동 전원 차단
        }
    }

    // ========== 오버라이드 메서드 ==========

    // 군사 로봇은 전투 중 이동하므로 더 신중하게 움직임
    void move(double deltaX, double deltaY) {
        if (!isActive) {
            std::cout << "로봇이 비활성 상태입니다." << std::endl;
            return;
        }

        // 방어력이 낮으면 이동 속도 감소
        double moveFactor = armor / 100.0;  // 0.0 ~ 1.0
        deltaX *= moveFactor;
        deltaY *= moveFactor;

        x += deltaX;
        y += deltaY;
        battery -= 0.8;  // 무거운 장비로 인한 배터리 소모 증가

        std::cout << name << " 전술 이동: (" << x << ", " << y << ")";
        if (moveFactor < 1.0) {
            std::cout << " [손상으로 인한 속도 " << (int)(moveFactor * 100) << "%]";
        }
        std::cout << std::endl;

        // 이동 중에도 경계 태세 유지
        if (isWeaponActive) {
            std::cout << "  (무장 활성화 상태로 이동 중)" << std::endl;
        }
    }

    void displayStatus() {
        BaseRobot::displayStatus();
        std::cout << "무장: " << weaponType << std::endl;
        std::cout << "탄약: " << ammunition << "발" << std::endl;
        std::cout << "방어력: " << armor << "%" << std::endl;
        std::cout << "무장 상태: " << (isWeaponActive ? "활성" : "비활성") << std::endl;
        std::cout << "==================" << std::endl;
    }
};