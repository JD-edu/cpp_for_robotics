#include <iostream>
#include "DataBox.h"

int main() {
    std::cout << "=== 클래스 템플릿 예제 ===" << std::endl;

    // ========== DataBox 예제 ==========
    std::cout << "\n--- DataBox 예제 ---" << std::endl;

    // 정수를 저장하는 DataBox
    DataBox<int> motorSpeed("모터속도");
    motorSpeed.store(100);
    motorSpeed.display();
    std::cout << "현재 속도: " << motorSpeed.get() << " RPM\n" << std::endl;

    // 실수를 저장하는 DataBox
    DataBox<double> temperature("온도센서");
    temperature.store(25.5);
    temperature.display();
    std::cout << "현재 온도: " << temperature.get() << "°C\n" << std::endl;

    // 문자열을 저장하는 DataBox
    DataBox<std::string> robotName("로봇이름");
    robotName.store("Explorer-X1");
    robotName.display();

    // ========== Pair 예제 ==========
    std::cout << "\n--- Pair 예제 ---" << std::endl;

    // 로봇 위치 (x, y 좌표)
    Pair<double, double> position(10.5, 20.3);
    std::cout << "로봇 위치: ";
    position.display();

    // 센서 이름과 값
    Pair<std::string, int> sensorData("거리센서", 150);
    std::cout << "센서: " << sensorData.getFirst()
        << ", 값: " << sensorData.getSecond() << "cm" << std::endl;

    // 서로 다른 타입 조합
    Pair<int, std::string> robotStatus(1, "Active");
    std::cout << "로봇 상태 코드: " << robotStatus.getFirst()
        << " (" << robotStatus.getSecond() << ")" << std::endl;

    // ========== SimpleArray 예제 ==========
    std::cout << "\n--- SimpleArray 예제 ---" << std::endl;

    // 정수 배열
    SimpleArray<int> distances(5);
    std::cout << "거리 센서 값 입력:" << std::endl;
    distances[0] = 100;
    distances[1] = 150;
    distances[2] = 200;
    distances[3] = 120;
    distances[4] = 180;
    distances.displayAll();

    // 실수 배열
    SimpleArray<double> temperatures(4);
    std::cout << "\n온도 센서 값 입력:" << std::endl;
    temperatures[0] = 25.5;
    temperatures[1] = 26.3;
    temperatures[2] = 24.8;
    temperatures[3] = 27.1;
    temperatures.displayAll();

    // 배열 값 수정
    std::cout << "\n세 번째 온도 값 수정:" << std::endl;
    temperatures[2] = 30.0;
    temperatures.displayAll();

    return 0;
}