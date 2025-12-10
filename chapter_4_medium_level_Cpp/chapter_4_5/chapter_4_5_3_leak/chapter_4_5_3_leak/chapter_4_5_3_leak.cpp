#include <iostream>
#include "SafeArray.h"

int main() {
    std::cout << "=== 메모리 누수 vs 올바른 관리 ===" << std::endl;

    // 1. 메모리 누수 시뮬레이션 (실제로는 실행하지 마세요!)
    std::cout << "\n[나쁜 예] 메모리 누수 발생:" << std::endl;
    for (int i = 0; i < 5; ++i) {
        int* leak = new int[100];  // 400바이트씩 누수
        std::cout << "반복 " << i + 1 << ": 메모리 할당만 하고 해제 안함" << std::endl;
        // delete[] leak;  // 주석 처리됨 - 메모리 누수!
    }
    std::cout << "→ 총 2000바이트 누수 발생!" << std::endl;

    // 2. 올바른 메모리 관리
    std::cout << "\n[좋은 예] 올바른 메모리 관리:" << std::endl;
    for (int i = 0; i < 5; ++i) {
        int* temp = new int[100];
        std::cout << "반복 " << i + 1 << ": 메모리 할당 후 해제" << std::endl;
        delete[] temp;  // 제대로 해제
    }
    std::cout << "→ 메모리 누수 없음!" << std::endl;

    // 3. RAII 패턴 사용
    std::cout << "\n[더 좋은 예] RAII 패턴 (자동 관리):" << std::endl;
    {
        SafeArray arr(100);
        arr[0] = 42;
        std::cout << "SafeArray 사용 중..." << std::endl;
        std::cout << "arr[0] = " << arr[0] << std::endl;
    }  // 스코프 종료 - 자동으로 소멸자 호출되어 메모리 해제
    std::cout << "→ 자동으로 메모리 해제됨!" << std::endl;

    return 0;
}
