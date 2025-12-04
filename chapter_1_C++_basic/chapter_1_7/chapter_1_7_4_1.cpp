#include <iostream>
using namespace std;

int main() {
    int sensorValue;
  
    cout << "=== 센서 캘리브레이션 ===" << endl;
  
    do {
        cout << "센서 값을 읽는 중... ";
        sensorValue = 85 + (rand() % 31); // 85-115 사이의 랜덤 값
        cout << sensorValue << endl;
    
        if (sensorValue < 95 || sensorValue > 105) {
            cout << "캘리브레이션 범위를 벗어남 (95-105)" << endl;
            cout << "다시 측정합니다..." << endl << endl;
        }
    
    } while (sensorValue < 95 || sensorValue > 105);
  
    cout << "센서 캘리브레이션 완료!" << endl;
    cout << "최종 센서 값: " << sensorValue << endl;
  
    return 0;
}