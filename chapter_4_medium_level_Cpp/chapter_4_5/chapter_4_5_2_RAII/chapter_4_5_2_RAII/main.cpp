#include <iostream>
#include "FileLogger.h"

int main() {
    std::cout << "=== RAII 자원 관리 테스트 ===" << std::endl;

    try {
        riskyOperation();
    }
    catch (const std::exception& e) {
        std::cerr << "\n예외 포착: " << e.what() << std::endl;
        std::cout << "\n주목: 예외가 발생했지만 FileLogger 소멸자가 "
            << "자동으로 호출되어 파일이 안전하게 닫혔습니다!" << std::endl;
    }

    std::cout << "\n프로그램 정상 종료" << std::endl;
    return 0;
}
