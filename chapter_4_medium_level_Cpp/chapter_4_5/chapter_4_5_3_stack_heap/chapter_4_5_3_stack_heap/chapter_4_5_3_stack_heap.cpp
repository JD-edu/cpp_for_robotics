#include <iostream>

int main() {
    std::cout << "=== 스택과 힙 메모리 비교 ===" << std::endl;

    // 스택 메모리: 자동 할당 및 해제
    int stackVar = 10;              // 스택에 4바이트 할당
    double stackArray[5];           // 스택에 40바이트 할당

    std::cout << "\n[스택 메모리]" << std::endl;
    std::cout << "스택 변수: " << stackVar << std::endl;
    std::cout << "스택 배열 크기: " << sizeof(stackArray) << " 바이트" << std::endl;

    // 힙 메모리: 수동 할당 및 해제 필요
    int* heapVar = new int;         // 힙에 4바이트 할당
    *heapVar = 20;

    double* heapArray = new double[100];  // 힙에 800바이트 할당

    std::cout << "\n[힙 메모리]" << std::endl;
    std::cout << "힙 변수: " << *heapVar << std::endl;
    std::cout << "힙 배열 크기: " << 100 * sizeof(double) << " 바이트" << std::endl;

    // 힙 메모리 해제 (필수!)
    std::cout << "\n힙 메모리 해제 중..." << std::endl;
    delete heapVar;
    delete[] heapArray;
    std::cout << "힙 메모리 해제 완료!" << std::endl;

    std::cout << "\n프로그램 종료 - 스택 변수는 자동으로 해제됨" << std::endl;
    return 0;
    // 함수 종료 시 스택 변수는 자동 해제됨
}
