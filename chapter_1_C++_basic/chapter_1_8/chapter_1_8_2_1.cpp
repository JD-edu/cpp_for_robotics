#include <iostream>
#include <cmath>

// 두 정수를 더하는 함수
int add(int a, int b) {
    return a + b;
}

// 인사말을 출력하는 함수 (반환값 없음)
void greet() {
    std::cout << "안녕하세요! 로봇 제어 시스템입니다." << std::endl;
}

// 원의 면적을 계산하는 함수
double calculateCircleArea(double radius) {
    return 3.14159 * radius * radius;
}

int main() {
    greet();

    int sum = add(10, 20);
    std::cout << "합계: " << sum << std::endl;

    double area = calculateCircleArea(5.0);
    std::cout << "원의 면적: " << area << std::endl;

    return 0;
}
