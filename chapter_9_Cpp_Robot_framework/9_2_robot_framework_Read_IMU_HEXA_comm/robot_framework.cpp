// g++ -O2 robot_framework.cpp -o robot_framework
#include <iostream>
#include <fcntl.h>    // O_RDWR, O_NOCTTY 등
#include <unistd.h>   // read(), close()
#include <termios.h>  // 시리얼 포트 설정
#include <cstring>    // memset()
#include <cstdint>    // int16_t, uint8_t

// 전역 변수 (하드코딩 스타일)
int serial_fd = -1;
const uint8_t HEADER_BYTE = 0xF5;

// IMU 데이터 저장용 구조체
struct IMUData {
    int16_t accX, accY, accZ;
    int16_t gyroX, gyroY, gyroZ;
};

// 시리얼 포트 초기화 함수
bool initSerial(const char* portName) {
    // 1. O_NDELAY로 열고 나서 fcntl로 다시 Blocking 모드로 전환 (안정적인 오픈 방식)
    serial_fd = open(portName, O_RDWR | O_NOCTTY | O_NDELAY);
    if (serial_fd == -1) {
        std::cerr << "포트를 열 수 없습니다: " << portName << std::endl;
        return false;
    }
    fcntl(serial_fd, F_SETFL, 0); // 다시 블로킹 모드로 설정

    struct termios options;
    // --- 매우 중요: 설정 초기화 ---
    memset(&options, 0, sizeof(options));

    if (tcgetattr(serial_fd, &options) != 0) return false;

    // 2. 보드레이트 설정
    cfsetispeed(&options, B115200);
    cfsetospeed(&options, B115200);

    // 3. 제어 모드 (Control Modes)
    options.c_cflag |= (CLOCAL | CREAD); // 로컬 연결, 수신 활성화
    options.c_cflag &= ~PARENB;          // 패리티 없음
    options.c_cflag &= ~CSTOPB;          // 1 스톱비트
    options.c_cflag &= ~CSIZE;           // 크기 마스크 제거
    options.c_cflag |= CS8;              // 8비트 데이터
    options.c_cflag &= ~CRTSCTS;         // 하드웨어 흐름 제어 비활성화 (핵심!)

    // 4. 로컬 모드 (Local Modes)
    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); // Raw 입력 모드

    // 5. 입력 모드 (Input Modes)
    options.c_iflag &= ~(IXON | IXOFF | IXANY); // 소프트웨어 흐름 제어 비활성화
    options.c_iflag |= IGNPAR;                  // 패리티 오류 무시

    // 6. 출력 모드 (Output Modes)
    options.c_oflag &= ~OPOST;                  // Raw 출력 모드

    // 7. 블로킹 동작 설정 (최소 1바이트 올 때까지 대기)
    options.c_cc[VMIN] = 1;
    options.c_cc[VTIME] = 0;

    tcflush(serial_fd, TCIFLUSH);
    if (tcsetattr(serial_fd, TCSANOW, &options) != 0) {
        return false;
    }
    return true;
}

// 데이터 수신 및 파싱 함수
bool receiveIMU(IMUData &data) {
    uint8_t header_buffer[1]; // 헤더 바이트를 읽기 위한 버퍼
    uint8_t data_buffer[12];  // 헤더를 제외한 20바이트 데이터를 위한 버퍼
    int bytes_read;

    // 1. 헤더(0xF5) 찾기
    while (true) {
        bytes_read = read(serial_fd, header_buffer, 1);
        if (bytes_read == 0) { // 타임아웃 (non-blocking 모드일 경우)
            // 데이터가 없음. 다시 시도
            //std::cout << "No data, retrying header read..." << std::endl; // Debugging
            return false; // 데이터가 없으므로 다음 루프에서 다시 시도
        }
        if (bytes_read == -1) { // read 에러 발생
            std::cerr << "Error reading serial port for header: " << strerror(errno) << std::endl; // Debugging
            return false; // 에러 발생
        }

        if (header_buffer[0] == HEADER_BYTE) {
            // 헤더를 찾았음! 이제 나머지 데이터를 읽는다.
            break;
        } else {
            // 헤더가 아님. 다음 바이트를 계속 확인
            //std::cout << "Skipping byte: 0x" << std::hex << (int)header_buffer[0] << std::dec << std::endl; // Debugging
        }
    }
    // 2. 나머지 12바이트 데이터 읽기
    int totalRead = 0;
    while (totalRead < 12) {
        int n = read(serial_fd, data_buffer + totalRead, 12 - totalRead);
        if (n <= 0) return false;
        totalRead += n;
    }

    // 3. 비트 연산을 통한 데이터 복원 (Big Endian 방식)
    data.accX  = (int16_t)((data_buffer[0] << 8)  | data_buffer[1]);
    data.accY  = (int16_t)((data_buffer[2] << 8)  | data_buffer[3]);
    data.accZ  = (int16_t)((data_buffer[4] << 8)  | data_buffer[5]);
    data.gyroX = (int16_t)((data_buffer[6] << 8)  | data_buffer[7]);
    data.gyroY = (int16_t)((data_buffer[8] << 8)  | data_buffer[9]);
    data.gyroZ = (int16_t)((data_buffer[10] << 8) | data_buffer[11]);

    return true;
}

int main() {
    const char* port = "/dev/ttyUSB0"; // 사용자의 환경에 맞춰 변경 (/dev/ttyACM0 등)
    IMUData imu;

    if (!initSerial(port)) {
        return 1;
    }

    std::cout << "데이터 수신 시작..." << std::endl;

    while (true) {
        if (receiveIMU(imu)) {
            // 결과 출력
            printf("ACC: [%6d, %6d, %6d] | GYRO: [%6d, %6d, %6d]\n", 
                    imu.accX, imu.accY, imu.accZ, 
                    imu.gyroX, imu.gyroY, imu.gyroZ);
        }
        //usleep(100); // 10ms 대기 (CPU 점유율 방지)
    }

    close(serial_fd);
    return 0;
}