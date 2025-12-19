#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <cstring>
#include <iomanip>

const unsigned char HEADER = 0xAA;
const unsigned char PACKET_SIZE = 0x06;

struct DataPacket {
    unsigned char header;
    unsigned char size;
    unsigned char data[4];
    unsigned char checksum;
};

int setup_serial(const char* device) {
    int serial_fd = open(device, O_RDWR | O_NOCTTY);
    if (serial_fd == -1) return -1;

        // Configure serial port
        struct  termios  options;
        tcgetattr(serial_fd, &options);
        cfsetispeed(&options, B115200);
        cfsetospeed(&options, B115200);
        options.c_cflag  = CS8 | CLOCAL | CREAD;
        options.c_iflag  = IGNPAR;
        options.c_oflag  =  0;
        options.c_lflag  =  0;
        tcflush(serial_fd, TCIFLUSH);
        tcsetattr(serial_fd, TCSANOW, &options);
        return serial_fd;
}

bool receivePacket(int serial_fd, DataPacket& packet) {
    unsigned char byte;
    unsigned  char  bytes[1];
    int byte_read;
    // 헤더 바이트 찾기
    byte_read =  read(serial_fd, bytes, 1);
    if(byte_read ==  0){
        //std::cout <<  "error"  <<  std::endl;
        return  false;
    }else if(bytes[0] == HEADER){
        std::cout <<  "got head"  <<  std::endl;
    }else{
        //std::cout <<  "error"  <<  std::hex << (int)bytes[0] <<  std::endl;
    }
    packet.header = byte;

    // 패킷 크기 읽기
    if (read(serial_fd, &packet.size, 1) != 1) return false;
    if (packet.size != PACKET_SIZE) return false;

    // 데이터 읽기 (4바이트)
    if (read(serial_fd, packet.data, 4) != 4) return false;

    // 체크섬 읽기
    if (read(serial_fd, &packet.checksum, 1) != 1) return false;

    // 체크섬 검증
    unsigned char calculated_checksum = packet.data[0] ^ packet.data[1] ^ 
                                       packet.data[2] ^ packet.data[3];

    return (calculated_checksum == packet.checksum);
}

int32_t bytesToInt(const unsigned char* bytes) {
    return ((int32_t)bytes[0] << 24) | ((int32_t)bytes[1] << 16) | 
           ((int32_t)bytes[2] << 8) | (int32_t)bytes[3];
}

int main() {
    int serial_fd = setup_serial("/dev/ttyUSB1");
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
