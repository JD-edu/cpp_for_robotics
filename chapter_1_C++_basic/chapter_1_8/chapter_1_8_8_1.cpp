#include <iostream>
#include <string>

// 참조를 이용한 값 교환
void swapByReference(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// 로봇 위치 업데이트 (참조 사용)
void updatePosition(double& x, double& y, double deltaX, double deltaY) {
    x += deltaX;
    y += deltaY;
}

// 센서 데이터 읽기 (여러 값을 참조로 반환)
void readSensors(int& temperature, int& humidity, double& distance) {
    temperature = 25;    // 섭씨 온도
    humidity = 60;       // 습도 %
    distance = 15.7;     // 거리 cm
}

// 모터 상태 업데이트
void updateMotorStatus(std::string& status, int& speed, bool& isRunning) {
    status = "정상 작동";
    speed = 1500;
    isRunning = true;
}

// 배터리 잔량 계산 및 경고 메시지 설정
bool checkBattery(double voltage, std::string& message, int& percentage) {
    if (voltage > 12.0) {
        percentage = 100;
        message = "배터리 상태 양호";
        return true;
    } else if (voltage > 10.0) {
        percentage = static_cast<int>((voltage - 10.0) / 2.0 * 100);
        message = "배터리 잔량 부족 주의";
        return true;
    } else {
        percentage = 0;
        message = "긴급! 배터리 교체 필요";
        return false;
    }
}

int main() {
    // 값 교환 예시
    int leftMotor = 100, rightMotor = 200;
    std::cout << "교환 전 - 좌측: " << leftMotor << ", 우측: " << rightMotor << std::endl;
    swapByReference(leftMotor, rightMotor);
    std::cout << "교환 후 - 좌측: " << leftMotor << ", 우측: " << rightMotor << std::endl;

    // 로봇 위치 업데이트
    double robotX = 10.0, robotY = 15.0;
    std::cout << "\n이동 전 위치: (" << robotX << ", " << robotY << ")" << std::endl;
    updatePosition(robotX, robotY, 5.0, -3.0);
    std::cout << "이동 후 위치: (" << robotX << ", " << robotY << ")" << std::endl;

    // 센서 데이터 읽기
    int temp, humid;
    double dist;
    readSensors(temp, humid, dist);
    std::cout << "\n센서 데이터:" << std::endl;
    std::cout << "온도: " << temp << "°C" << std::endl;
    std::cout << "습도: " << humid << "%" << std::endl;
    std::cout << "거리: " << dist << "cm" << std::endl;

    // 모터 상태 확인
    std::string motorStatus;
    int motorSpeed;
    bool motorRunning;
    updateMotorStatus(motorStatus, motorSpeed, motorRunning);
    std::cout << "\n모터 상태: " << motorStatus << std::endl;
    std::cout << "모터 속도: " << motorSpeed << " RPM" << std::endl;
    std::cout << "작동 상태: " << (motorRunning ? "가동중" : "정지") << std::endl;

    // 배터리 확인
    double batteryVolt = 11.2;
    std::string batteryMsg;
    int batteryPercent;
    bool batteryOK = checkBattery(batteryVolt, batteryMsg, batteryPercent);
    std::cout << "\n배터리 전압: " << batteryVolt << "V" << std::endl;
    std::cout << "배터리 잔량: " << batteryPercent << "%" << std::endl;
    std::cout << "상태 메시지: " << batteryMsg << std::endl;
    std::cout << "시스템 상태: " << (batteryOK ? "정상" : "경고") << std::endl;

    return 0;
}
