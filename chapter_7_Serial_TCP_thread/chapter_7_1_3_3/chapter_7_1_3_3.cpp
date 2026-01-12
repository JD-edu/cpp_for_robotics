#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <cstring>

// g++ -o serial_transmitter chapter_7_1_3_3.cpp

void intToBytes(int32_t value, unsigned char* bytes) {
    bytes[0] = (value >> 24) & 0xFF;
    bytes[1] = (value >> 16) & 0xFF;
    bytes[2] = (value >> 8) & 0xFF;
    bytes[3] = value & 0xFF;
}

int setup_serial(const char* device) {
    int serial_fd = open(device, O_RDWR | O_NOCTTY);
    if (serial_fd == -1) return -1;
  
    struct termios tty;
    memset(&tty, 0, sizeof tty);
    tcgetattr(serial_fd, &tty);
  
    cfsetospeed(&tty, B115200);
    cfsetispeed(&tty, B115200);
  
    tty.c_cflag &= ~PARENB;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;
    tty.c_lflag &= ~ICANON;
    tty.c_lflag &= ~ECHO;
  
    tcsetattr(serial_fd, TCSANOW, &tty);
  
    return serial_fd;
}

void sendIntegerPacket(int serial_fd, int32_t value) {
    unsigned char packet[7];
  
    packet[0] = 0xAA;  // 헤더
    packet[1] = 0x06;  // 패킷 크기
  
    intToBytes(value, &packet[2]);
  
    // 체크섬 계산
    packet[6] = packet[2] ^ packet[3] ^ packet[4] ^ packet[5];
  
    write(serial_fd, packet, 7);
    std::cout << "전송: " << value << std::endl;
}

int main() {
    int serial_fd = setup_serial("/dev/ttyUSB0");  // 이전 함수 사용
    if (serial_fd == -1) {
        std::cerr << "시리얼 포트를 열 수 없습니다." << std::endl;
        return -1;
    }
  
    int32_t value;
    std::cout << "전송할 정수를 입력하세요 (종료하려면 -1): ";
  
    while (std::cin >> value && value != -1) {
        sendIntegerPacket(serial_fd, value);
        usleep(100000);  // 100ms 대기
        std::cout << "다음 정수를 입력하세요: ";
    }
  
    close(serial_fd);
    return 0;
}