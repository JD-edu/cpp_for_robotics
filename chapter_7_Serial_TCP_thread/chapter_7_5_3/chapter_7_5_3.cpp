// camera_serial_multithread.cpp
#include <iostream>
#include <thread>
#include <atomic>
#include <string>
#include <fcntl.h>    // File control (open)
#include <unistd.h>   // UNIX standard (read, write, close)
#include <termios.h>  // POSIX terminal control
#include <opencv2/opencv.hpp>

// g++ -std=c++11 chapter_7_5_2.cpp -o robot_system \
    -pthread \
    `pkg-config --cflags --libs opencv4`

// 전역 종료 플래그 (atomic을 사용하여 쓰래드 간 안전한 접근 보장)
std::atomic<bool> g_isRunning(true);

// 시리얼 포트 설정 함수
int openSerialPort(const char* portName, int baudRate) {
    int fd = open(portName, O_RDWR | O_NOCTTY | O_SYNC);
    if (fd < 0) {
        std::cerr << "[Serial] Error opening " << portName << std::endl;
        return -1;
    }

    struct termios tty;
    if (tcgetattr(fd, &tty) != 0) {
        std::cerr << "[Serial] Error from tcgetattr" << std::endl;
        close(fd);
        return -1;
    }

    // Baud rate 설정
    cfsetospeed(&tty, B115200);
    cfsetispeed(&tty, B115200);

    // 8N1 모드 설정 (8 data bits, No parity, 1 stop bit)
    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;
    tty.c_cflag &= ~(PARENB | PARODD);
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CRTSCTS;
    tty.c_cflag |= (CLOCAL | CREAD);

    // Raw 모드 설정
    tty.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    tty.c_iflag &= ~(IXON | IXOFF | IXANY);
    tty.c_oflag &= ~OPOST;

    // Read timeout 설정 (0.5초)
    tty.c_cc[VMIN] = 0;
    tty.c_cc[VTIME] = 5;

    if (tcsetattr(fd, TCSANOW, &tty) != 0) {
        std::cerr << "[Serial] Error from tcsetattr" << std::endl;
        close(fd);
        return -1;
    }

    return fd;
}

// [Task 1] 시리얼 통신 쓰래드 - 아두이노로부터 센서 데이터 수신
void serialThreadTask(const char* portName) {
    int serialPort = openSerialPort(portName, 9600);
  
    if (serialPort < 0) {
        std::cerr << "[Serial] Failed to open port. Thread terminating." << std::endl;
        g_isRunning = false;
        return;
    }

    std::cout << "[Serial] Port " << portName << " opened successfully." << std::endl;
  
    // 아두이노 리셋 대기 (포트 오픈 시 아두이노가 리셋됨)
    std::this_thread::sleep_for(std::chrono::seconds(2));

    char buffer[256];
    std::string lineBuffer;

    while (g_isRunning) {
        int n = read(serialPort, buffer, sizeof(buffer) - 1);
  
        if (n > 0) {
            buffer[n] = '\0';
            lineBuffer += buffer;

            // 줄바꿈 문자를 찾아서 완전한 라인 처리
            size_t pos;
            while ((pos = lineBuffer.find('\n')) != std::string::npos) {
                std::string line = lineBuffer.substr(0, pos);
                lineBuffer.erase(0, pos + 1);

                // 빈 줄이 아니면 출력
                if (!line.empty() && line != "\r") {
                    std::cout << "[Serial] Sensor Data: " << line << std::endl;
                }
            }
        }
  
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    close(serialPort);
    std::cout << "[Serial] Thread terminated." << std::endl;
}

// [Task 2] 카메라 영상 처리 쓰래드
void cameraThreadTask() {
    cv::VideoCapture cap(0);
  
    if (!cap.isOpened()) {
        std::cerr << "[Camera] Error opening camera" << std::endl;
        g_isRunning = false;
        return;
    }

    // 카메라 해상도 설정 (선택사항)
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);

    cv::Mat frame;
    std::cout << "[Camera] Streaming started. Press ESC to exit." << std::endl;

    while (g_isRunning) {
        cap >> frame;
  
        if (frame.empty()) {
            std::cerr << "[Camera] Empty frame captured" << std::endl;
            break;
        }

        // 프레임에 정보 텍스트 추가
        cv::putText(frame, "Robot Vision System", 
                    cv::Point(10, 30), 
                    cv::FONT_HERSHEY_SIMPLEX, 
                    0.7, 
                    cv::Scalar(0, 255, 0), 
                    2);

        cv::imshow("Robot Camera View", frame);
  
        // ESC 키(ASCII 27)를 누르면 종료
        int key = cv::waitKey(30);
        if (key == 27) {
            std::cout << "[Camera] ESC pressed. Shutting down..." << std::endl;
            g_isRunning = false;
        }
    }

    cap.release();
    cv::destroyAllWindows();
    std::cout << "[Camera] Thread terminated." << std::endl;
}

int main(int argc, char** argv) {
    // 시리얼 포트 이름 설정 (기본값: /dev/ttyUSB0)
    const char* serialPort = "/dev/ttyUSB0";
  
    if (argc > 1) {
        serialPort = argv[1];
    }

    std::cout << "===== Robot Multi-threaded System =====" << std::endl;
    std::cout << "Serial Port: " << serialPort << std::endl;
    std::cout << "Camera: /dev/video0" << std::endl;
    std::cout << "========================================" << std::endl;

    // 두 개의 독립적인 작업을 쓰래드로 생성
    std::thread t_serial(serialThreadTask, serialPort);
    std::thread t_camera(cameraThreadTask);

    // 쓰래드들이 종료될 때까지 대기
    t_camera.join();  // 카메라 윈도우에서 ESC를 누르면 종료
    t_serial.join();  // g_isRunning이 false가 되면 시리얼 쓰래드도 종료

    std::cout << "\nSystem shutdown complete." << std::endl;
    return 0;
}