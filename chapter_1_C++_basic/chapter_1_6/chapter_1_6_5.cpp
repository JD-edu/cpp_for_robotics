#include <iostream>
using namespace std;

int main() {
    int a = 10, b = 3;

    cout << "=== 산술 연산 ===" << endl;
    cout << "a + b = " << a + b << endl;  // 13
    cout << "a - b = " << a - b << endl;  // 7
    cout << "a * b = " << a * b << endl;  // 30
    cout << "a / b = " << a / b << endl;  // 3 (정수 나눗셈)
    cout << "a % b = " << a % b << endl;  // 1 (나머지)

    cout << "\n=== 비교 연산 (결과는 bool) ===" << endl;
    cout << "a == b: " << (a == b) << endl;  // 0 (false)
    cout << "a != b: " << (a != b) << endl;  // 1 (true)
    cout << "a > b: " << (a > b) << endl;    // 1 (true)
    cout << "a < b: " << (a < b) << endl;    // 0 (false)

    cout << "\n=== 논리 연산 (결과는 bool) ===" << endl;
    cout << "(a > 5) && (b < 5): " << ((a > 5) && (b < 5)) << endl;  // 1 (true)
    cout << "(a > 15) || (b < 5): " << ((a > 15) || (b < 5)) << endl;  // 1 (true)
    cout << "!(a == b): " << !(a == b) << endl;  // 1 (true)

    cout << "\n=== 증감 연산자 ===" << endl;
    int x = 5;
    cout << "x = " << x << endl;          // 5
    cout << "x++ = " << x++ << endl;      // 5 (후위 증가: 출력 후 증가)
    cout << "x = " << x << endl;          // 6
    cout << "++x = " << ++x << endl;      // 7 (전위 증가: 증가 후 출력)
    cout << "x = " << x << endl;          // 7

    return 0;
}
