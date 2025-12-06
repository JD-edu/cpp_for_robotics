#ifndef SERIAL_PORT_H
#define SERIAL_PORT_H

#include <string>
#include <vector>
#include <functional>

class SerialPort {
private:
    int fd;
    std::string device_path;
    bool is_open;
  
    struct DataPacket {
        unsigned char header;
        unsigned char size;
        unsigned char data[4];
        unsigned char checksum;
    };
  
public:
    SerialPort(const std::string& device);
    ~SerialPort();
  
    bool open(int baud_rate = 9600);
    void close();
    bool isOpen() const { return is_open; }
  
    // 기본 읽기/쓰기
    int write(const void* data, size_t size);
    int read(void* buffer, size_t size);
  
    // 문자열 통신
    bool writeString(const std::string& str);
    std::string readString();
  
    // 패킷 통신
    bool sendPacket(int32_t value);
    bool receivePacket(int32_t& value);
  
    // 유틸리티
    bool waitForData(int timeout_ms = 1000);
    void flush();
};

#endif