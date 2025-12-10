#include <iostream>
#include <string>

class FileLogger {
public:
    FileLogger(const std::string& filename) : name(filename) {
        std::cout << "[로거] 파일 열기: " << name << std::endl;
        // 실제로는 파일을 열어야 함
    }

    ~FileLogger() {
        std::cout << "[로거] 파일 닫기: " << name << std::endl;
        // 파일 자동 닫기 - 예외 발생 시에도 실행됨!
    }

    void log(const std::string& message) {
        std::cout << "[로그] " << message << std::endl;
    }

private:
    std::string name;
};

void riskyOperation() {
    FileLogger logger("robot.log");  // 생성자에서 파일 열림

    logger.log("작업 시작");
    logger.log("센서 초기화");

    // 오류 발생!
    throw std::runtime_error("센서 초기화 실패");

    logger.log("작업 완료");  // 실행되지 않음

    // 여기서 logger가 스코프를 벗어나면 소멸자가 자동 호출되어 파일이 닫힘
}
