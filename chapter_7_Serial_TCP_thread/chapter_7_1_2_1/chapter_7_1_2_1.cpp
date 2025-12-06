#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <cstring>

// g++ -o serial_receive chapter_7_1_2_1.cpp

int main() {
    // 1. 시리얼 포트 열기
    int serial_fd = open("/dev/ttyUSB0", O_RDWR);
    if (serial_fd < 0) {
        std::cerr << "시리얼 포트를 열 수 없습니다." << std::endl;
        return -1;
    }

    // 2. 시리얼 포트 설정
    struct termios tty;
    tcgetattr(serial_fd, &tty);

    // 9600 bps, 8N1 설정
    cfsetispeed(&tty, B115200);
    cfsetospeed(&tty, B115200);

    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;     // 8비트
    tty.c_cflag &= ~(PARENB | PARODD);          // 패리티 없음
    tty.c_cflag &= ~CSTOPB;                         // 1 스톱비트
    tty.c_cflag |= (CLOCAL | CREAD);                // 로컬 모드, 읽기 활성화

    tty.c_lflag = 0;                                // non-canonical 모드
    tty.c_oflag = 0;                                // raw 출력
    tty.c_iflag = 0;                                // raw 입력

    tcsetattr(serial_fd, TCSANOW, &tty);

    // 3. 데이터 수신
    char buffer[256];
    std::cout << "아두이노로부터 데이터 수신 중..." << std::endl;

    while (true) {
        int n = read(serial_fd, buffer, sizeof(buffer) - 1);
        if (n > 0) {
            buffer[n] = '\0';
            std::cout << buffer << std::flush;
        }
    }

    close(serial_fd);
    return 0;
}
