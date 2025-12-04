#include <iostream>
#include <cmath>
#include <string>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// 로봇 상태 구조체
struct RobotState {
    double x, y, angle;        // 위치와 방향
    int batteryLevel;          // 배터리 잔량 (%)
    bool isMoving;             // 이동 상태
    std::string lastCommand;   // 마지막 명령
};

// 센서 데이터 구조체
struct SensorData {
    double frontDistance;      // 전방 거리 (cm)
    double leftDistance;       // 좌측 거리 (cm)
    double rightDistance;      // 우측 거리 (cm)
    int lightLevel;           // 조도 (0-1023)
    double temperature;        // 온도 (°C)
};

// === 센서 관련 함수 ===
// 거리 센서 시뮬레이션 (실제로는 하드웨어에서 읽어옴)
inline double readDistanceSensor(const std::string& direction = "front") {
    // 시뮬레이션을 위한 임의 값 생성
    if (direction == "front") return 25.0 + (rand() % 20);
    if (direction == "left") return 15.0 + (rand() % 15);
    if (direction == "right") return 20.0 + (rand() % 10);
    return 50.0;
}

// 모든 센서 데이터 읽기 (참조를 이용한 다중 반환값)
void readAllSensors(SensorData& data) {
    data.frontDistance = readDistanceSensor("front");
    data.leftDistance = readDistanceSensor("left");
    data.rightDistance = readDistanceSensor("right");
    data.lightLevel = 400 + (rand() % 300);
    data.temperature = 20.0 + (rand() % 10);
}

// === 모터 제어 함수 ===
// 기본 매개변수를 가진 모터 제어
void controlMotors(int leftSpeed, int rightSpeed = -1, bool smoothStart = true) {
    if (rightSpeed == -1) rightSpeed = leftSpeed; // 우측 모터 속도 기본값

    std::cout << "모터 제어: 좌측=" << leftSpeed << "%, 우측=" << rightSpeed << "%";
    if (smoothStart) std::cout << " (부드러운 시작)";
    std::cout << std::endl;
}

// 함수 오버로딩을 이용한 다양한 이동 방식
void moveRobot(RobotState& robot, double distance) {
    // 직진 이동
    robot.x += distance * cos(robot.angle * M_PI / 180.0);
    robot.y += distance * sin(robot.angle * M_PI / 180.0);
    robot.isMoving = true;
    robot.lastCommand = "직진 이동";
    controlMotors(70); // 양쪽 모터 동일 속도
}

void moveRobot(RobotState& robot, double distance, double angle) {
    // 각도를 바꾸며 이동
    robot.angle += angle;
    robot.x += distance * cos(robot.angle * M_PI / 180.0);
    robot.y += distance * sin(robot.angle * M_PI / 180.0);
    robot.isMoving = true;
    robot.lastCommand = "회전 후 이동";

    // 회전 방향에 따른 모터 제어
    if (angle > 0) controlMotors(30, 70);  // 좌회전
    else controlMotors(70, 30);            // 우회전
}

void moveRobot(RobotState& robot, double x, double y, double targetAngle) {
    // 목표 좌표로 이동
    robot.x = x;
    robot.y = y;
    robot.angle = targetAngle;
    robot.isMoving = true;
    robot.lastCommand = "좌표 이동";
    controlMotors(80, 80, true);
}

// === 의사결정 함수 ===
// 장애물 회피 알고리즘
std::string decideAction(const SensorData& sensors, RobotState& robot) {
    const double SAFE_DISTANCE = 20.0; // 안전 거리 (cm)

    if (sensors.frontDistance < SAFE_DISTANCE) {
        if (sensors.leftDistance > sensors.rightDistance) {
            moveRobot(robot, 0, -15); // 좌회전
            return "좌회전으로 장애물 회피";
        }
        else {
            moveRobot(robot, 0, 15);  // 우회전
            return "우회전으로 장애물 회피";
        }
    }
    else if (sensors.lightLevel < 200) {
        moveRobot(robot, 5.0);  // 어두우면 조심스럽게 전진
        return "저조도 환경 - 천천히 이동";
    }
    else {
        moveRobot(robot, 10.0); // 일반 속도로 전진
        return "정상 이동";
    }
}

// === 상태 출력 함수 ===
void printRobotStatus(const RobotState& robot) {
    std::cout << "=== 로봇 상태 ===" << std::endl;
    std::cout << "위치: (" << robot.x << ", " << robot.y << ")" << std::endl;
    std::cout << "방향: " << robot.angle << "도" << std::endl;
    std::cout << "배터리: " << robot.batteryLevel << "%" << std::endl;
    std::cout << "이동 상태: " << (robot.isMoving ? "이동중" : "정지") << std::endl;
    std::cout << "마지막 명령: " << robot.lastCommand << std::endl;
}

void printSensorData(const SensorData& sensors) {
    std::cout << "=== 센서 데이터 ===" << std::endl;
    std::cout << "전방 거리: " << sensors.frontDistance << "cm" << std::endl;
    std::cout << "좌측 거리: " << sensors.leftDistance << "cm" << std::endl;
    std::cout << "우측 거리: " << sensors.rightDistance << "cm" << std::endl;
    std::cout << "조도: " << sensors.lightLevel << std::endl;
    std::cout << "온도: " << sensors.temperature << "°C" << std::endl;
}

// === 메인 로봇 제어 루프 ===
int main() {
    // 로봇 초기화
    RobotState robot = { 0.0, 0.0, 0.0, 85, false, "시스템 시작" };
    SensorData sensors;

    std::cout << "🤖 로봇 제어 시스템 시작" << std::endl;
    std::cout << "============================" << std::endl;

    // 시뮬레이션 루프 (3번 반복)
    for (int cycle = 1; cycle <= 3; cycle++) {
        std::cout << "\n--- 제어 사이클 " << cycle << " ---" << std::endl;

        // 1. 센서 데이터 읽기
        readAllSensors(sensors);

        // 2. 상태 출력
        printSensorData(sensors);
        printRobotStatus(robot);

        // 3. 의사결정 및 행동
        std::string action = decideAction(sensors, robot);
        std::cout << "결정: " << action << std::endl;

        // 4. 배터리 소모 시뮬레이션
        robot.batteryLevel -= 5;

        // 5. 배터리 경고
        if (robot.batteryLevel < 20) {
            std::cout << "⚠️ 배터리 부족 경고! 충전이 필요합니다." << std::endl;
        }

        std::cout << std::endl;
    }

    // 최종 상태 출력
    std::cout << "🏁 시뮬레이션 완료" << std::endl;
    printRobotStatus(robot);

    return 0;
}