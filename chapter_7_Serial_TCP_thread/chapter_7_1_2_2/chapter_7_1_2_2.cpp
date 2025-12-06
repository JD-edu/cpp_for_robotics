#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <cstring>
#include <string>

// g++ -o serial_receive chapter_7_1_2_2.cpp

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

void send_command(int serial_fd, const std::string& command) {
    std::string cmd = command + "\n";
    write(serial_fd, cmd.c_str(), cmd.length());
    std::cout << "전송: " << command << std::endl;
}

int main() {
    int serial_fd = setup_serial("/dev/ttyUSB0");
    if (serial_fd == -1) {
        std::cerr << "시리얼 포트를 열 수 없습니다." << std::endl;
        return -1;
    }

    std::cout << "아두이노 제어 프로그램" << std::endl;
    std::cout << "명령어: LED_ON, LED_OFF, MOTOR_FORWARD, MOTOR_BACKWARD, MOTOR_STOP, quit" << std::endl;

    std::string input;
    while (true) {
        std::cout << "명령 입력: ";
        std::getline(std::cin, input);

        if (input == "quit") break;

        if (input == "LED_ON" || input == "LED_OFF" || 
            input == "MOTOR_FORWARD" || input == "MOTOR_BACKWARD" || 
            input == "MOTOR_STOP") {
            send_command(serial_fd, input);
            usleep(100000);  // 100ms 대기
        } else {
            std::cout << "잘못된 명령입니다." << std::endl;
        }
    }

    close(serial_fd);
    return 0;
}
