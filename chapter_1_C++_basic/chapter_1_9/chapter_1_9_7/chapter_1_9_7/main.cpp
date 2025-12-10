#include "SimpleRobot.h"
#include <iostream>
// 사용 예제
int main() {
    // 객체 생성 (생성자 오버로딩 활용)
    SimpleRobot robot1;                    // 기본 생성자
    SimpleRobot robot2("아두이노봇");       // 이름 지정 생성자

    cout << "=== 로봇 1 테스트 ===" << endl;
    cout << "이름: " << robot1.getName() << endl;
    cout << "초기 배터리: " << robot1.getBattery() << "%" << endl;

    robot1.powerOn();
    cout << "전원 ON - 상태: " << (robot1.getStatus() ? "작동중" : "정지") << endl;

    // 함수 오버로딩 활용
    robot1.move();                         // 기본 이동
    cout << "기본 이동 후 배터리: " << robot1.getBattery() << "%" << endl;

    robot1.move(50);                       // 거리 지정 이동
    cout << "50 거리 이동 후 배터리: " << robot1.getBattery() << "%" << endl;

    robot1.powerOff();
    cout << "전원 OFF - 상태: " << (robot1.getStatus() ? "작동중" : "정지") << endl;

    cout << "\n=== 로봇 2 테스트 ===" << endl;
    cout << "이름: " << robot2.getName() << endl;
    cout << "배터리: " << robot2.getBattery() << "%" << endl;

    return 0;
}