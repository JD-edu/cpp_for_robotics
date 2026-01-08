#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <cstring>
#include <iomanip>

// g++ -o serial_receive chapter_7_1_3_2.cpp


const unsigned char HEADER = 0xAA;
const unsigned char PACKET_SIZE = 0x06;

struct DataPacket {
    unsigned char header;
    unsigned char size;
    unsigned char data[4];
    unsigned char checksum;
};

int setup_serial(const char* device) {
    int serial_fd = open(device, O_RDWR | O_NOCTTY | O_NDELAY);
    if (serial_fd == -1) return -1;

    fcntl(serial_fd, F_SETFL, 0); // Blocking 모드로 복구
    struct termios options;

    // Configure serial port
    if (tcgetattr(serial_fd, &options) != 0) return -1;

    // --- 모든 설정을 0으로 초기화하여 깨끗한 상태로 시작 ---
    memset(&options, 0, sizeof(options));

    cfsetispeed(&options, B115200);
    cfsetospeed(&options, B115200);

    // 2. 제어 모드 (Control Options)
    options.c_cflag |= (CLOCAL | CREAD); // 로컬 연결, 수신 활성화
    options.c_cflag &= ~PARENB;          // 패리티 없음
    options.c_cflag &= ~CSTOPB;          // 1 스톱비트
    options.c_cflag &= ~CSIZE;           // 크기 마스크 제거
    options.c_cflag |= CS8;              // 8비트 데이터

    // 핵심: 하드웨어 흐름 제어(RTS/CTS) 비활성화 (이게 파이썬과 차이날 확률 높음)
    options.c_cflag &= ~CRTSCTS;

    // 3. 로컬 모드 (Local Options)
    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); // Raw 입력 모드 설정

    // 4. 입력 모드 (Input Options)
    // 소프트웨어 흐름 제어(XON/XOFF) 비활성화
    options.c_iflag &= ~(IXON | IXOFF | IXANY);
    options.c_iflag |= IGNPAR;           // 패리티 오류 무시

    // 5. 출력 모드 (Output Options)
    options.c_oflag &= ~OPOST;           // Raw 출력 모드


    // 6. 대기 설정 (VMIN, VTIME)
    options.c_cc[VMIN] = 1;  
    options.c_cc[VTIME] = 0;

    tcflush(serial_fd, TCIFLUSH);

    tcsetattr(serial_fd, TCSANOW, &options);
    return serial_fd;if (tcsetattr(serial_fd, TCSANOW, &options) != 0) {
        return -1;
    }

    return serial_fd;
}

bool receivePacket(int serial_fd, DataPacket& packet) {
    unsigned char currByte;
    //unsigned char byte;
    //unsigned  char  bytes[1];
    //int byte_read;
    // 헤더 바이트 찾기
    while (true) {
        int n = read(serial_fd, &currByte, 1);
        if (n <= 0) return false; // 읽기 실패 시 리턴
        if (currByte == HEADER) {
            packet.header = currByte;
            break; // 헤더 발견! 루프 탈출
        }
    }
    
    // 패킷 크기 읽기
    if (read(serial_fd, &packet.size, 1) != 1) return false;
    if (packet.size != PACKET_SIZE) return false;

    // 데이터 읽기 (4바이트)
    // 3. 데이터 4바이트 읽기 (버추얼박스 레이턴시 대응: 다 읽을 때까지 반복)
    int totalDataRead = 0;
    while (totalDataRead < 4) {
        int n = read(serial_fd, packet.data + totalDataRead, 4 - totalDataRead);
        if (n <= 0) return false;
        totalDataRead += n;
    }

    // 체크섬 읽기
    if (read(serial_fd, &packet.checksum, 1) != 1) return false;

    // 체크섬 검증
    unsigned char calculated_checksum = packet.data[0] ^ packet.data[1] ^ 
                                       packet.data[2] ^ packet.data[3];

    if (calculated_checksum != packet.checksum) {
        // 체크섬이 틀리면 패킷이 깨진 것이므로 무시
        return false;
    }

    return true;
}

int32_t bytesToInt(const unsigned char* bytes) {
    return ((int32_t)bytes[0] << 24) | ((int32_t)bytes[1] << 16) | 
           ((int32_t)bytes[2] << 8) | (int32_t)bytes[3];
}

int main() {
    int serial_fd = setup_serial("/dev/ttyUSB0");
    if (serial_fd == -1) {
        std::cerr << "시리얼 포트를 열 수 없습니다." << std::endl;
        return -1;
    }

    std::cout << "아두이노로부터 헥사 데이터 수신 중..." << std::endl;

    DataPacket packet;
    while (true) {
        if (receivePacket(serial_fd, packet)) {
            int32_t value = bytesToInt(packet.data);

            std::cout << "수신된 정수: " << value << " (0x" 
                      << std::hex << std::setfill('0') << std::setw(8) 
                      << value << std::dec << ")" << std::endl;
        } else {
            std::cout << "패킷 수신 오류 또는 체크섬 불일치" << std::endl;
        }
    }

    close(serial_fd);
    return 0;
}
