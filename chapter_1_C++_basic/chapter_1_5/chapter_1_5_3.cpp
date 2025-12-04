#include <iostream>
#include <string>
#include <climits>
using namespace std;

int main() {
    cout << "=== 데이터 타입 크기 확인 ===" << endl;
    cout << "int 크기: " << sizeof(int) << " bytes" << endl;
    cout << "float 크기: " << sizeof(float) << " bytes" << endl;
    cout << "double 크기: " << sizeof(double) << " bytes" << endl;
    cout << "char 크기: " << sizeof(char) << " byte" << endl;
    cout << "bool 크기: " << sizeof(bool) << " byte" << endl;
    cout << endl;

    // === 오버플로우/언더플로우 시연 ===
    cout << "=== 오버플로우/언더플로우 시연 ===" << endl;
    int maxInt = INT_MAX;
    int minInt = INT_MIN;

    cout << "int 최대값: " << maxInt << endl;
    cout << "최대값 + 1 (오버플로우): " << maxInt + 1 << endl;
    cout << "int 최소값: " << minInt << endl;
    cout << "최소값 - 1 (언더플로우): " << minInt - 1 << endl;
    cout << endl;

    // === Signed vs Unsigned 비교 ===
    cout << "=== Signed vs Unsigned 비교 ===" << endl;
    int signedNum = -10;
    unsigned int unsignedNum = 10;

    cout << "signed int: " << signedNum << endl;
    cout << "unsigned int: " << unsignedNum << endl;

    // 음수를 unsigned에 대입하면?
    unsigned int unsignedFromNegative = -1;
    cout << "unsigned에 -1 대입: " << unsignedFromNegative << endl;
    cout << endl;

    // === Bool 변수 활용 ===
    cout << "=== Bool 변수 활용 ===" << endl;
    bool flag1 = true;
    bool flag2 = false;
    bool flag3 = 5;      // 0이 아닌 값은 true
    bool flag4 = 0;      // 0은 false

    cout << "flag1 (true): " << flag1 << endl;
    cout << "flag2 (false): " << flag2 << endl;
    cout << "flag3 (5를 대입): " << flag3 << endl;
    cout << "flag4 (0을 대입): " << flag4 << endl;

    // 조건문에서 활용
    if (flag1 && !flag2) {
        cout << "조건문 실행: flag1은 참이고 flag2는 거짓" << endl;
    }
    cout << endl;

    // === Char와 ASCII 코드 ===
    cout << "=== Char와 ASCII 코드 ===" << endl;
    char ch1 = 'A';
    char ch2 = 65;       // ASCII 코드로 직접 대입
    char ch3 = '0';

    cout << "문자 'A': " << ch1 << ", ASCII 코드: " << (int)ch1 << endl;
    cout << "ASCII 65를 대입: " << ch2 << endl;
    cout << "문자 '0': " << ch3 << ", ASCII 코드: " << (int)ch3 << endl;

    // 문자 연산
    char nextChar = ch1 + 1;
    cout << "'A' + 1 = " << nextChar << endl;
    cout << endl;

    // === String 클래스 함수들 ===
    cout << "=== String 클래스 함수들 ===" << endl;

    // 다양한 초기화 방법
    string str1 = "Hello";
    string str2("World");
    string str3(5, 'A');        // "AAAAA"
    string str4;                // 빈 문자열

    cout << "str1: " << str1 << endl;
    cout << "str2: " << str2 << endl;
    cout << "str3 (5개의 'A'): " << str3 << endl;

    // 크기 관련 함수들
    cout << "str1 길이: " << str1.length() << endl;
    cout << "str1 크기: " << str1.size() << endl;
    cout << "str4가 비어있는가? " << str4.empty() << endl;

    // 문자열 연결
    string combined = str1 + " " + str2;
    cout << "연결된 문자열: " << combined << endl;

    str1 += "!";
    cout << "str1에 '!' 추가: " << str1 << endl;

    // 부분 문자열
    string sub = combined.substr(0, 5);    // 0번째부터 5개 문자
    cout << "부분 문자열 (0~4): " << sub << endl;

    // 문자열 검색
    size_t pos = combined.find("World");
    if (pos != string::npos) {
        cout << "'World'를 " << pos << "번째 위치에서 발견" << endl;
    }

    // C 스타일 문자열로 변환
    const char* cStr = combined.c_str();
    cout << "C 스타일 문자열: " << cStr << endl;

    return 0;
}
