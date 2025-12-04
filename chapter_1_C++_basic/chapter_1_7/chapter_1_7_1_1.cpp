#include <iostream>
using namespace std;

int main() {
    int temperature = 25;

    if (temperature > 30) {
        cout << "온도가 높습니다. 냉각 시스템을 가동합니다." << endl;
    } else if (temperature < 10) {
        cout << "온도가 낮습니다. 가열 시스템을 가동합니다." << endl;
    } else {
        cout << "온도가 적정합니다. 현재 온도: " << temperature << "°C" << endl;
    }

    return 0;
}
