#include <boost/asio.hpp>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>

// g++ -o boost_arduino chapter_7_1_4_2.cpp -lboost_system -pthread

class ArduinoController {
private:
    boost::asio::io_service io;
    boost::asio::serial_port serial;
    bool running;

public:
    ArduinoController(const std::string& port) 
        : serial(io, port), running(true) {

        // 시리얼 포트 설정
        serial.set_option(boost::asio::serial_port_base::baud_rate(9600));
        serial.set_option(boost::asio::serial_port_base::character_size(8));
        serial.set_option(boost::asio::serial_port_base::parity(
            boost::asio::serial_port_base::parity::none));
        serial.set_option(boost::asio::serial_port_base::stop_bits(
            boost::asio::serial_port_base::stop_bits::one));
        serial.set_option(boost::asio::serial_port_base::flow_control(
            boost::asio::serial_port_base::flow_control::none));
    }

    ~ArduinoController() {
        running = false;
        if (serial.is_open()) {
            serial.close();
        }
    }

    // 명령 전송
    void sendCommand(const std::string& command) {
        std::string cmd = command + "\n";
        boost::asio::write(serial, boost::asio::buffer(cmd));
        std::cout << "전송: " << command << std::endl;
    }

    // 데이터 수신 (한 줄 읽기)
    std::string readLine() {
        boost::asio::streambuf buffer;
        boost::asio::read_until(serial, buffer, '\n');

        std::istream is(&buffer);
        std::string line;
        std::getline(is, line);

        // 개행 문자 제거
        if (!line.empty() && line[line.length()-1] == '\r') {
            line.erase(line.length()-1);
        }

        return line;
    }

    // LED 제어
    void setLED(bool on) {
        sendCommand(on ? "LED_ON" : "LED_OFF");

        // 응답 대기
        std::string response = readLine();
        std::cout << "아두이노 응답: " << response << std::endl;
    }

    // 센서 값 요청
    int getSensorValue() {
        sendCommand("GET_SENSOR");

        // 응답 대기
        std::string response = readLine();
        std::cout << "아두이노 응답: " << response << std::endl;

        // "SENSOR:123" 형식 파싱
        if (response.substr(0, 7) == "SENSOR:") {
            return std::stoi(response.substr(7));
        }
        return -1;
    }

    // 비동기 데이터 수신 (백그라운드 스레드에서 실행)
    void startListening() {
        std::thread([this]() {
            while (running && serial.is_open()) {
                try {
                    std::string data = readLine();

                    // "DATA:" 접두사로 시작하는 주기적 데이터
                    if (data.substr(0, 5) == "DATA:") {
                        int value = std::stoi(data.substr(5));
                        std::cout << "[자동 수신] 센서 값: " << value << std::endl;
                    }
                } catch (const std::exception& e) {
                    if (running) {
                        std::cerr << "수신 오류: " << e.what() << std::endl;
                    }
                }
            }
        }).detach();
    }
};

int main() {
    try {
        ArduinoController arduino("/dev/ttyUSB0");

        std::cout << "Boost.Asio 시리얼 통신 시작" << std::endl;
        std::cout << "명령어: on, off, get, quit" << std::endl;

        // 백그라운드에서 데이터 수신 시작
        arduino.startListening();

        // 아두이노 초기화 대기
        std::this_thread::sleep_for(std::chrono::seconds(2));

        std::string input;
        while (true) {
            std::cout << "\n명령 입력: ";
            std::getline(std::cin, input);

            if (input == "quit") {
                break;
            }
            else if (input == "on") {
                arduino.setLED(true);
            }
            else if (input == "off") {
                arduino.setLED(false);
            }
            else if (input == "get") {
                int value = arduino.getSensorValue();
                if (value >= 0) {
                    std::cout << "센서 값: " << value << std::endl;
                }
            }
            else {
                std::cout << "잘못된 명령입니다." << std::endl;
            }
        }

    } catch (std::exception& e) {
        std::cerr << "오류: " << e.what() << std::endl;
        return -1;
    }

    return 0;
}
