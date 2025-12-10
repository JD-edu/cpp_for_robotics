#pragma once
#pragma once
#include <iostream>

// ========== 예제 1: 두 값 중 최댓값 반환 ==========
template<typename T>
T getMax(T a, T b) {
    std::cout << "getMax 호출됨 (타입: " << typeid(T).name() << ")" << std::endl;
    return (a > b) ? a : b;
}

// ========== 예제 2: 두 값 중 최솟값 반환 ==========
template<typename T>
T getMin(T a, T b) {
    return (a < b) ? a : b;
}

// ========== 예제 3: 두 값을 교환 ==========
template<typename T>
void swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

// ========== 예제 4: 절댓값 반환 ==========
template<typename T>
T absolute(T value) {
    return (value < 0) ? -value : value;
}

// ========== 예제 5: 세 값 중 최댓값 ==========
template<typename T>
T getMax3(T a, T b, T c) {
    T max = a;
    if (b > max) max = b;
    if (c > max) max = c;
    return max;
}

// ========== 예제 6: 평균값 계산 ==========
template<typename T>
T average(T a, T b) {
    return (a + b) / 2;
}

// ========== 예제 7: 값을 출력하는 템플릿 함수 ==========
template<typename T>
void printValue(const T& value) {
    std::cout << "값: " << value << std::endl;
}