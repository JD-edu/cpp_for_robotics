#include <iostream>
using namespace std;

int main() {
    double distance = 15.0; // 초음파 센서로 측정된 거리 (cm)
    int motorSpeed = 100;   // 모터 속도 (0-255)

    cout << "=== 로봇 장애물 회피 시스템 ===" << endl;
    cout << "감지된 거리: " << distance << "cm" << endl;

    if (distance < 10) {
        cout << "위험! 장애물이 매우 가깝습니다." << endl;
        cout << "동작: 즉시 정지 및 후진" << endl;
        motorSpeed = -50; // 후진
    } else if (distance < 20) {
        cout << "주의! 장애물이 감지되었습니다." << endl;
        cout << "동작: 속도 감소 및 우회 경로 탐색" << endl;
        motorSpeed = 30; // 저속 전진
    } else if (distance < 50) {
        cout << "안전 거리 유지" << endl;
        cout << "동작: 정상 속도로 전진" << endl;
        motorSpeed = 80; // 중간 속도
    } else {
        cout << "전방 경로 확보" << endl;
        cout << "동작: 최대 속도로 전진" << endl;
        motorSpeed = 100; // 최대 속도
    }

    cout << "설정된 모터 속도: " << motorSpeed << endl;

    return 0;
}
