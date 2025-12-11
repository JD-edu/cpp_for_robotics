#include <iostream>
#include "RoboticsNamespace.h"

using namespace std;

int main() {
    cout << "=== 네임스페이스 예제 ===\n" << endl;

    // 1. 센서 (별칭 사용: RS)
    RS::TemperatureSensor sensor("온도센서");
    cout << sensor.getName() << " 값: " << sensor.read() << "°C\n" << endl;

    // 2. 모터 (별칭 사용: RA)
    RA::Motor motor("바퀴");
    motor.start();
    motor.stop();
    cout << endl;

    // 3. 위치 (별칭 사용: RN)
    RN::Position pos(10.0, 20.0);
    pos.print();

    return 0;
}