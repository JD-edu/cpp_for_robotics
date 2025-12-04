#include <iostream>
using namespace std;

int main() {
    int a = 12, b = 3, c = 12;

    // 비교 연산의 결과는 bool 값
    bool result1 = (a == b);  // false (0)
    bool result2 = (a == c);  // true (1)
    bool result3 = (a > b);   // true (1)

    cout << "a == b: " << result1 << endl;  // 0 출력
    cout << "a == c: " << result2 << endl;  // 1 출력
    cout << "a > b: " << result3 << endl;   // 1 출력

    // bool 값을 정수처럼 사용 가능
    // true는 1, false는 0으로 변환됨
    int x = (10 > 5);   // x = 1 (true)
    int y = (10 < 5);   // y = 0 (false)

    cout << "10 > 5의 결과를 정수로: " << x << endl;  // 1
    cout << "10 < 5의 결과를 정수로: " << y << endl;  // 0

    // 비교 연산 결과를 다른 연산에 사용 가능
    int score = 85;
    int bonus = (score >= 80) * 10;  // 80점 이상이면 10점 보너스
    cout << "보너스: " << bonus << endl;  // 10

    // 연쇄 비교 가능 (하지만 주의 필요!)
    int value = 5;
    // (value > 3) == true 형태로 사용
    cout << "(5 > 3) == true: " << ((value > 3) == true) << endl;  // 1

    // 실용 예제: 범위 체크
    int temperature = 25;
    bool isComfortable = (temperature >= 20) && (temperature <= 28);
    cout << "쾌적한 온도인가? " << isComfortable << endl;  // 1 (true)

    return 0;
}
