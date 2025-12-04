#include <iostream>
using namespace std;

int main() {
    int sensorReadings[5] = {23, 45, 67, 34, 56}; // 센서 측정값들
    int sum = 0;
  
    cout << "센서 측정값들: ";
    for (int i = 0; i < 5; i++) {
        cout << sensorReadings[i] << " ";
        sum += sensorReadings[i];
    }
  
    double average = static_cast<double>(sum) / 5;
    cout << endl;
    cout << "총합: " << sum << endl;
    cout << "평균값: " << average << endl;
  
    return 0;
}