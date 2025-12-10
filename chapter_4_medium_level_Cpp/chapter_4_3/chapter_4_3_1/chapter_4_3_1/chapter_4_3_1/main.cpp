#include <iostream>
#include "BasicTemplate.h"

int main() {
    std::cout << "=== 함수 템플릿 예제 ===" << std::endl;

    // ========== 정수형 테스트 ==========
    std::cout << "\n--- 정수형 (int) 테스트 ---" << std::endl;
    int intA = 10, intB = 25;

    std::cout << "최댓값 (" << intA << ", " << intB << "): "
        << getMax(intA, intB) << std::endl;
    std::cout << "최솟값 (" << intA << ", " << intB << "): "
        << getMin(intA, intB) << std::endl;
    std::cout << "평균값: " << average(intA, intB) << std::endl;

    std::cout << "\n값 교환 전: a=" << intA << ", b=" << intB << std::endl;
    swap(intA, intB);
    std::cout << "값 교환 후: a=" << intA << ", b=" << intB << std::endl;

    // ========== 실수형 테스트 ==========
    std::cout << "\n--- 실수형 (double) 테스트 ---" << std::endl;
    double doubleA = 15.7, doubleB = 12.3, doubleC = 18.9;

    std::cout << "최댓값 (" << doubleA << ", " << doubleB << "): "
        << getMax(doubleA, doubleB) << std::endl;
    std::cout << "세 값 중 최댓값 (" << doubleA << ", " << doubleB << ", "
        << doubleC << "): " << getMax3(doubleA, doubleB, doubleC) << std::endl;

    double negative = -45.8;
    std::cout << negative << "의 절댓값: " << absolute(negative) << std::endl;
    std::cout << "평균값: " << average(doubleA, doubleB) << std::endl;

    // ========== float 타입 테스트 ==========
    std::cout << "\n--- float 타입 테스트 ---" << std::endl;
    float floatA = 3.14f, floatB = 2.71f;
    std::cout << "최댓값: " << getMax(floatA, floatB) << std::endl;

    // ========== char 타입 테스트 ==========
    std::cout << "\n--- 문자형 (char) 테스트 ---" << std::endl;
    char charA = 'A', charB = 'Z';
    std::cout << "최댓값 ('" << charA << "', '" << charB << "'): "
        << getMax(charA, charB) << std::endl;

    // ========== 로봇 센서 값 비교 예제 ==========
    std::cout << "\n--- 로봇 센서 값 비교 ---" << std::endl;
    double temp1 = 25.5, temp2 = 27.8;  // 온도 센서
    int distance1 = 150, distance2 = 200;  // 거리 센서 (cm)

    std::cout << "더 높은 온도: " << getMax(temp1, temp2) << "°C" << std::endl;
    std::cout << "더 먼 거리: " << getMax(distance1, distance2) << "cm" << std::endl;

    return 0;
}