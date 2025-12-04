#include <iostream>
#include <string>

// 정수 반환
int getMotorSpeed() {
    return 1500; // RPM
}

// 실수 반환
double getTemperature() {
    return 25.7; // 섭씨 온도
}

// 문자열 반환
std::string getRobotStatus() {
    return "정상 작동 중";
}

// 불린값 반환
bool isSensorActive() {
    return true;
}

// 조건부 반환값
int checkBatteryLevel(double voltage) {
    if (voltage > 12.0) {
        return 100; // 배터리 완충
    } else if (voltage > 10.0) {
        return 50;  // 배터리 반충전
    } else {
        return 0;   // 배터리 방전
    }
}

int main() {
    std::cout << "모터 속도: " << getMotorSpeed() << " RPM" << std::endl;
    std::cout << "온도: " << getTemperature() << "°C" << std::endl;
    std::cout << "로봇 상태: " << getRobotStatus() << std::endl;
    std::cout << "센서 활성화: " << (isSensorActive() ? "예" : "아니오") << std::endl;
    std::cout << "배터리 레벨: " << checkBatteryLevel(11.5) << "%" << std::endl;

    return 0;
}
