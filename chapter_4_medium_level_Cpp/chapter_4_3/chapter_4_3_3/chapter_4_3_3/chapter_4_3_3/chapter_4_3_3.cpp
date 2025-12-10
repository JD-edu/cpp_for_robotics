#include <iostream>
#include "DataBox.h"
#include "BasicTemplate.h"

int main() {
    std::cout << "=== 로봇 데이터 관리 시스템 ===" << std::endl;

    // ========== 로봇의 다양한 센서 데이터 관리 ==========
    std::cout << "\n--- 센서 데이터 초기화 ---" << std::endl;

    DataBox<int> distanceSensor("초음파센서");
    DataBox<double> tempSensor("온도센서");
    DataBox<double> batterySensor("배터리센서");
    DataBox<int> lightSensor("조도센서");

    // 센서 값 읽기 및 저장
    std::cout << "\n--- 센서 값 읽기 ---" << std::endl;
    distanceSensor.store(150);  // 150cm
    tempSensor.store(28.5);     // 28.5°C
    batterySensor.store(85.3);  // 85.3%
    lightSensor.store(750);     // 750 lux

    // 모든 센서 상태 출력
    std::cout << "\n--- 센서 상태 확인 ---" << std::endl;
    distanceSensor.display();
    tempSensor.display();
    batterySensor.display();
    lightSensor.display();

    // ========== 템플릿 함수로 센서 값 비교 ==========
    std::cout << "\n--- 센서 값 비교 ---" << std::endl;

    int dist1 = 150, dist2 = 200;
    std::cout << "더 먼 거리: " << getMax(dist1, dist2) << "cm" << std::endl;

    double temp1 = 25.5, temp2 = 30.2;
    std::cout << "더 높은 온도: " << getMax(temp1, temp2) << "°C" << std::endl;

    double battery1 = 85.3, battery2 = 45.7;
    std::cout << "더 낮은 배터리: " << getMin(battery1, battery2) << "%" << std::endl;

    // ========== 로봇 위치 관리 (Pair 활용) ==========
    std::cout << "\n--- 로봇 위치 추적 ---" << std::endl;

    Pair<double, double> startPos(0.0, 0.0);
    Pair<double, double> currentPos(15.3, 22.7);
    Pair<double, double> targetPos(50.0, 50.0);

    std::cout << "시작 위치: ";
    startPos.display();
    std::cout << "현재 위치: ";
    currentPos.display();
    std::cout << "목표 위치: ";
    targetPos.display();

    // ========== 센서 히스토리 저장 (SimpleArray 활용) ==========
    std::cout << "\n--- 온도 센서 히스토리 ---" << std::endl;

    SimpleArray<double> tempHistory(6);
    tempHistory[0] = 25.1;
    tempHistory[1] = 25.8;
    tempHistory[2] = 26.5;
    tempHistory[3] = 27.2;
    tempHistory[4] = 28.0;
    tempHistory[5] = 28.5;

    std::cout << "최근 6회 측정값: ";
    tempHistory.displayAll();

    // 최고/최저 온도 찾기
    double maxTemp = tempHistory[0];
    double minTemp = tempHistory[0];
    for (int i = 1; i < tempHistory.getSize(); i++) {
        maxTemp = getMax(maxTemp, tempHistory[i]);
        minTemp = getMin(minTemp, tempHistory[i]);
    }
    std::cout << "최고 온도: " << maxTemp << "°C" << std::endl;
    std::cout << "최저 온도: " << minTemp << "°C" << std::endl;

    return 0;
}