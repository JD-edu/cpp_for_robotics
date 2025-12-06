#include "serial_class.hpp"
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <sys/select.h>
#include <cstring>
#include <iostream>

const unsigned char HEADER = 0xAA;
const unsigned char PACKET_SIZE = 0x06;

SerialPort::SerialPort(const std::string& device) 
    : fd(-1), device_path(device), is_open(false) {
}

SerialPort::~SerialPort() {
    if (is_open) {
        close();
    }
}

bool SerialPort::open(int baud_rate) {
    fd = ::open(device_path.c_str(), O_RDWR | O_NOCTTY | O_NONBLOCK);
    if (fd == -1) {
        return false;
    }
  
    struct termios tty;
    memset(&tty, 0, sizeof(tty));
  
    if (tcgetattr(fd, &tty) != 0) {
        ::close(fd);
        fd = -1;
        return false;
    }
  
    // 보드레이트 설정
    speed_t speed;
    switch (baud_rate) {
        case 9600: speed = B9600; break;
        case 19200: speed = B19200; break;
        case 38400: speed = B38400; break;
        case 57600: speed = B57600; break;
        case 115200: speed = B115200; break;
        default: speed = B9600; break;
    }
  
    cfsetospeed(&tty, speed);
    cfsetispeed(&tty, speed);
  
    // 시리얼 포트 설정
    tty.c_cflag &= ~PARENB;        // 패리티 없음
    tty.c_cflag &= ~CSTOPB;        // 1 스톱비트
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;            // 8 데이터비트
    tty.c_cflag &= ~CRTSCTS;       // 하드웨어 플로우 컨트롤 없음
    tty.c_cflag |= CREAD | CLOCAL; // 읽기 활성화, 로컬 모드
  
    tty.c_lflag &= ~ICANON;        // 비정규 모드
    tty.c_lflag &= ~ECHO;          // 에코 비활성화
    tty.c_lflag &= ~ECHOE;
    tty.c_lflag &= ~ISIG;          // 시그널 문자 해석 비활성화
  
    tty.c_iflag &= ~(IXON | IXOFF | IXANY); // 소프트웨어 플로우 컨트롤 비활성화
    tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL);
  
    tty.c_oflag &= ~OPOST;         // 출력 처리 비활성화
  
    tty.c_cc[VTIME] = 1;           // 100ms 타임아웃
    tty.c_cc[VMIN] = 0;            // 블로킹하지 않음
  
    if (tcsetattr(fd, TCSANOW, &tty) != 0) {
        ::close(fd);
        fd = -1;
        return false;
    }
  
    is_open = true;
    return true;
}

void SerialPort::close() {
    if (is_open) {
        ::close(fd);
        fd = -1;
        is_open = false;
    }
}

int SerialPort::write(const void* data, size_t size) {
    if (!is_open) return -1;
    return ::write(fd, data, size);
}

int SerialPort::read(void* buffer, size_t size) {
    if (!is_open) return -1;
    return ::read(fd, buffer, size);
}

bool SerialPort::writeString(const std::string& str) {
    std::string data = str + "\n";
    return write(data.c_str(), data.length()) == (int)data.length();
}

std::string SerialPort::readString() {
    if (!is_open) return "";
  
    std::string result;
    char buffer[256];
    int bytes_read = read(buffer, sizeof(buffer) - 1);
  
    if (bytes_read > 0) {
        buffer[bytes_read] = '\0';
        result = buffer;
    }
  
    return result;
}
