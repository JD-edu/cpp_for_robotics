#include <iostream>
using namespace std;

int main() {
    bool isRaining = true;
    bool hasUmbrella = false;

    // AND 연산 (둘 다 true여야 true)
    bool canGoOut = !isRaining || hasUmbrella;
    cout << "외출 가능? " << canGoOut << endl;  // 0 (false)

    // OR 연산 (하나라도 true면 true)
    bool needRainGear = isRaining || hasUmbrella;
    cout << "우산 관련 처리 필요? " << needRainGear << endl;  // 1 (true)

    // NOT 연산 (반대값)
    bool isSunny = !isRaining;
    cout << "맑은 날씨? " << isSunny << endl;  // 0 (false)

    // 복합 조건
    int age = 25;
    bool hasLicense = true;
    bool canDrive = (age >= 18) && hasLicense;
    cout << "운전 가능? " << canDrive << endl;  // 1 (true)

    // 논리 연산 결과를 변수에 저장
    bool result = (10 > 5) && (3 < 7);  // true && true = true
    cout << "논리 연산 결과: " << result << endl;  // 1

    return 0;
}
