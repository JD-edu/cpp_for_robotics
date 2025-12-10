#include <iostream>

// ❌ 나쁜 예: 메모리 누수 발생
void badMemoryManagement() {
    int* data = new int[1000];  // 4000바이트 할당

    // 데이터 사용...
    data[0] = 42;

    // delete[] data;  // 해제하지 않음! 메모리 누수!

    return;  // 함수 종료 시 포인터는 사라지지만 메모리는 남아있음
}

// ✅ 좋은 예: 제대로 관리
void goodMemoryManagement() {
    int* data = new int[1000];  // 4000바이트 할당

    // 데이터 사용...
    data[0] = 42;

    delete[] data;  // 반드시 해제!
    data = nullptr;  // 안전을 위해 nullptr로 설정
}

// ✅ 더 좋은 예: RAII 패턴 (클래스 사용)
class SafeArray {
public:
    SafeArray(int size) : arr(new int[size]), size(size) {}
    ~SafeArray() { delete[] arr; }  // 자동 해제

    int& operator[](int index) { return arr[index]; }

private:
    int* arr;
    int size;
};
