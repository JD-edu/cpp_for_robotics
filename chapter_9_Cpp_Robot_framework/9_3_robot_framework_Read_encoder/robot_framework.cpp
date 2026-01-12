// g++ -O2 robot_framework.cpp -o robot_framework
#include <iostream>
#include <fcntl.h>    
#include <unistd.h>   
#include <termios.h>  
#include <cstring>    
#include <cstdint>    
#include <errno.h>

// g++ -O2 robot_framework.cpp -o robot_framework

// 전역 변수
int serial_fd = -1;
const uint8_t HEADER1 = 0xF5;
const uint8_t HEADER2 = 0xFA;

// 로봇 데이터 저장용 구조체 (엔코더 추가)
struct RobotData {
    int16_t accX, accY, accZ;
    int16_t gyroX, gyroY, gyroZ;
    int16_t enc1, enc2; // 추가된 엔코더 데이터
};

// 시리얼 포트 초기화 (기존과 동일)
bool initSerial(const char* portName) {
    serial_fd = open(portName, O_RDWR | O_NOCTTY | O_NDELAY);
    if (serial_fd == -1) {
        std::cerr << "포트를 열 수 없습니다: " << portName << std::endl;
        return false;
    }
    fcntl(serial_fd, F_SETFL, 0); 

    struct termios options;
    memset(&options, 0, sizeof(options));
    if (tcgetattr(serial_fd, &options) != 0) return false;

    cfsetispeed(&options, B115200);
    cfsetospeed(&options, B115200);

    options.c_cflag |= (CLOCAL | CREAD);
    options.c_cflag &= ~PARENB;
    options.c_cflag &= ~CSTOPB;
    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8;
    options.c_cflag &= ~CRTSCTS;

    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    options.c_iflag &= ~(IXON | IXOFF | IXANY);
    options.c_iflag |= IGNPAR;
    options.c_oflag &= ~OPOST;

    options.c_cc[VMIN] = 1;
    options.c_cc[VTIME] = 0;

    tcflush(serial_fd, TCIFLUSH);
    if (tcsetattr(serial_fd, TCSANOW, &options) != 0) return false;
    
    return true;
}

// 데이터 수신 및 파싱 함수 (수정됨)
bool receiveRobotData(RobotData &data) {
    uint8_t h_buf;
    uint8_t data_buffer[16]; // IMU(12) + Encoder(4) = 16바이트

    // 1. 2바이트 헤더(0xF5, 0xFA) 찾기
    while (true) {
        if (read(serial_fd, &h_buf, 1) <= 0) return false;
        
        if (h_buf == HEADER1) {
            if (read(serial_fd, &h_buf, 1) <= 0) return false;
            if (h_buf == HEADER2) {
                break; // 헤더 0xF5 0xFA 확인 완료
            }
        }
    }

    // 2. 나머지 16바이트 데이터 읽기
    int totalRead = 0;
    while (totalRead < 16) {
        int n = read(serial_fd, data_buffer + totalRead, 16 - totalRead);
        if (n <= 0) return false;
        totalRead += n;
    }

    // 3. 비트 연산을 통한 데이터 복원 (Big Endian)
    data.accX  = (int16_t)((data_buffer[0] << 8)  | data_buffer[1]);
    data.accY  = (int16_t)((data_buffer[2] << 8)  | data_buffer[3]);
    data.accZ  = (int16_t)((data_buffer[4] << 8)  | data_buffer[5]);
    data.gyroX = (int16_t)((data_buffer[6] << 8)  | data_buffer[7]);
    data.gyroY = (int16_t)((data_buffer[8] << 8)  | data_buffer[9]);
    data.gyroZ = (int16_t)((data_buffer[10] << 8) | data_buffer[11]);
    
    // 추가된 엔코더 데이터 복원
    data.enc1  = (int16_t)((data_buffer[12] << 8) | data_buffer[13]);
    data.enc2  = (int16_t)((data_buffer[14] << 8) | data_buffer[15]);

    return true;
}

int main() {
    const char* port = "/dev/ttyUSB0"; // 시스템 상황에 맞게 수정
    RobotData robot;

    if (!initSerial(port)) return 1;

    std::cout << "데이터 수신 시작 (Header: 0xF5 0xFA)..." << std::endl;

    while (true) {
        if (receiveRobotData(robot)) {
            printf("ACC: [%d, %d, %d] | GYRO: [%d, %d, %d] | ENC: [%d, %d]\n", 
                    robot.accX, robot.accY, robot.accZ, 
                    robot.gyroX, robot.gyroY, robot.gyroZ,
                    robot.enc1, robot.enc2);
        }
    }

    close(serial_fd);
    return 0;
}