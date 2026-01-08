// g++ robot_framework.cpp -o robot_framework
#include <iostream>
#include <fcntl.h>   // 포트 제어 (open)
#include <termios.h> // 시리얼 통신 설정
#include <unistd.h>  // read, close
#include <cstring>

int main() {
    // 1. 시리얼 포트 열기 (ESP32 연결 경로 확인 필요)
    const char* portName = "/dev/ttyUSB0"; 
    int serialPort = open(portName, O_RDONLY | O_NOCTTY);

    if (serialPort < 0) {
        std::cerr << "Error: Could not open serial port " << portName << std::endl;
        return 1;
    }

    // 2. 시리얼 통신 설정
    struct termios tty;
    if (tcgetattr(serialPort, &tty) != 0) {
        std::cerr << "Error from tcgetattr" << std::endl;
        return 1;
    }

    cfsetispeed(&tty, B115200); // 수신 보드레이트 115200 설정
    
    tty.c_cflag &= ~PARENB;        // 패리티 비트 없음
    tty.c_cflag &= ~CSTOPB;        // 정지 비트 1개
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;            // 데이터 비트 8개
    tty.c_cflag |= CREAD | CLOCAL; // 수신 가능 및 로컬 연결 설정

    // 3. 설정 적용
    tcsetattr(serialPort, TCSANOW, &tty);

    std::cout << "Listening for IMU data on " << portName << "..." << std::endl;

    char readBuffer[256];
    
    while (true) {
        std::memset(readBuffer, 0, sizeof(readBuffer));
        int n = read(serialPort, readBuffer, sizeof(readBuffer) - 1);
        
        if (n > 0) {
            // 수신된 데이터를 화면에 출력
            std::cout << readBuffer << std::flush;
        }
    }

    close(serialPort);
    return 0;
}