#include <iostream>
#include "BaseRobot.h"
#include "MilitaryRobot.h"

int main() {
    std::cout << "=== 파라미터가 있는 상속 예제 ===" << std::endl;

    // 군사 로봇 생성 - 부모에게 이름, X좌표, Y좌표를 모두 전달
    MilitaryRobot guardian("Guardian-X1", 100.0, 50.0, "Laser Cannon", 50);

    std::cout << "\n--- 전투 시뮬레이션 ---" << std::endl;

    // 로봇 활성화
    guardian.powerOn();
    guardian.activateWeapon();

    // 초기 상태 확인
    guardian.displayStatus();

    // 전투 행동
    std::cout << "\n[작전 개시]" << std::endl;
    guardian.fire();  // 사격
    guardian.fire();
    guardian.fire();

    // 이동
    guardian.move(10.0, 5.0);

    // 피격
    std::cout << "\n[적의 공격!]" << std::endl;
    guardian.takeDamage(30.0);
    guardian.displayStatus();

    // 손상된 상태로 이동 (속도 감소됨)
    std::cout << "\n[손상 상태 이동]" << std::endl;
    guardian.move(10.0, 5.0);

    // 재장전
    guardian.reload(25);

    // 더 큰 피격
    std::cout << "\n[치명타!]" << std::endl;
    guardian.takeDamage(75.0);  // 방어력 0이 되어 자동 전원 차단

    guardian.displayStatus();

    return 0;
}