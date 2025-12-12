// main.cpp
#include <iostream>
#include "robot_math.h"
#include "sensor.h"
#include "motor.h"

int main() {
    std::cout << "=== Robot System Test ===" << std::endl << std::endl;
  
    // 수학 함수 테스트
    std::cout << "1. Math Functions Test:" << std::endl;
    double angle = 90.0;
    double radian = RobotMath::degreeToRadian(angle);
    std::cout << angle << " degrees = " << radian << " radians" << std::endl;
  
    double distance = RobotMath::calculateDistance(0, 0, 3, 4);
    std::cout << "Distance from (0,0) to (3,4): " << distance << std::endl;
    std::cout << std::endl;
  
    // 센서 테스트
    std::cout << "2. Sensor Test:" << std::endl;
    Sensor ultrasonic("Ultrasonic");
    ultrasonic.updateValue(150);
    ultrasonic.displayInfo();
  
    Sensor infrared("Infrared");
    infrared.updateValue(200);
    infrared.displayInfo();
    std::cout << std::endl;
  
    // 모터 테스트
    std::cout << "3. Motor Test:" << std::endl;
    Motor left_motor;
    left_motor.start();
    left_motor.setSpeed(100);
    std::cout << "Motor is running: " << (left_motor.isRunning() ? "Yes" : "No") << std::endl;
    left_motor.stop();
    std::cout << std::endl;
  
    std::cout << "=== Test Complete ===" << std::endl;
  
    return 0;
}