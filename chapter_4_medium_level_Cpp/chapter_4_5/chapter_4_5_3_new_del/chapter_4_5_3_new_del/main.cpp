#include "SensorData.h"
#include <iostream>

int main() {
    std::cout << "=== 동적 메모리 할당 테스트 ===" << std::endl;

    // 센서 데이터 객체 생성 (스택에 객체, 내부 배열은 힙에)
    SensorData sensor(10);

    // 데이터 저장
    for (int i = 0; i < sensor.getSize(); ++i) {
        sensor.setData(i, i * 1.5);
    }

    // 데이터 읽기
    std::cout << "\n센서 데이터 출력:" << std::endl;
    for (int i = 0; i < sensor.getSize(); ++i) {
        std::cout << "sensor[" << i << "] = " << sensor.getData(i) << std::endl;
    }

    std::cout << "\n함수 종료 - 소멸자 호출됨" << std::endl;
    return 0;
    // 여기서 sensor 객체가 소멸되면서 자동으로 delete[] 호출
}
