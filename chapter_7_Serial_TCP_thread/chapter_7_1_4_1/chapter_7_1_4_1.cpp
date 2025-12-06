#include "serial_class.hpp"
#include <iostream>
#include <string>
#include <unistd.h> // for usleep

// 시리얼 포트 장치 경로를 여기에 지정하십시오. (예: /dev/ttyUSB0, /dev/ttyACM0 등)
// 아두이노 연결 시 일반적으로 /dev/ttyACM0 또는 /dev/ttyUSB0 입니다.
#define DEVICE_PATH "/dev/ttyUSB0" 
#define BAUD_RATE 115200

int main() {
    // 1. 시리얼 포트 객체 생성
    SerialPort serial(DEVICE_PATH);

    // 2. 시리얼 포트 열기
    if (!serial.open(BAUD_RATE)) {
        std::cerr << "Failed to open serial port on " << DEVICE_PATH << std::endl;
        return 1; // 오류 발생 시 종료
    }
    
    std::cout << "Serial port opened successfully at " << BAUD_RATE << " baud." << std::endl;
    std::cout << "Waiting for data from Arduino (Press Ctrl+C to exit)..." << std::endl;

    // 3. 아두이노로부터 문자열 수신
    while (true) {
        
        std::string received_message = serial.readString();
        
        if (!received_message.empty()) {
            // 아두이노에서 보낸 문자열을 출력합니다.
            // 아두이노 Serial.println()은 개행 문자(\r\n)를 포함합니다.
            std::cout << "Received: " << received_message; 
            std::cout.flush();
        }
      
        // 데이터가 없을 경우 CPU 점유율을 낮추기 위해 짧게 휴식
        usleep(10000); // 10ms 대기
    }
    
    // 4. 시리얼 포트 닫기 (실제로는 무한 루프로 인해 실행되지 않지만, 원칙상 포함)
    serial.close();
    
    return 0;
}