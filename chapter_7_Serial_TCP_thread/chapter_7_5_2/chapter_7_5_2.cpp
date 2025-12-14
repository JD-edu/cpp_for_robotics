#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>

// g++ -std=c++11 chapter_7_5_2.cpp -o basic_multithread -pthread

// 전역 종료 플래그
std::atomic<bool> g_running(true);

// 쓰래드 1: 숫자를 출력하는 함수
void numberPrinter() {
    int count = 0;
    std::cout << "[Thread 1] Number printer started" << std::endl;
  
    while (g_running) {
        std::cout << "[Thread 1] Count: " << count++ << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // 0.5초 간격
    }
  
    std::cout << "[Thread 1] Terminated" << std::endl;
}

// 쓰래드 2: 문장을 출력하는 함수
void sentencePrinter() {
    const char* sentences[] = {
        "Robot is moving forward",
        "Sensor data received",
        "Processing camera image",
        "Communication check OK",
        "Battery level normal"
    };
    int index = 0;
  
    std::cout << "[Thread 2] Sentence printer started" << std::endl;
  
    while (g_running) {
        std::cout << "[Thread 2] Status: " << sentences[index % 5] << std::endl;
        index++;
        std::this_thread::sleep_for(std::chrono::milliseconds(700)); // 0.7초 간격
    }
  
    std::cout << "[Thread 2] Terminated" << std::endl;
}

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "  Multi-thread Example Started" << std::endl;
    std::cout << "========================================" << std::endl;

    // 두 개의 쓰래드 생성 및 시작
    std::thread t1(numberPrinter);
    std::thread t2(sentencePrinter);

    std::cout << "[Main] Two threads are running..." << std::endl;

    // 5초 동안 대기
    std::this_thread::sleep_for(std::chrono::seconds(5));

    // 종료 신호 전송
    std::cout << "\n[Main] Sending termination signal..." << std::endl;
    g_running = false;

    // 두 쓰래드가 종료될 때까지 대기
    if (t1.joinable()) {
        t1.join();
    }
    if (t2.joinable()) {
        t2.join();
    }

    std::cout << "\n========================================" << std::endl;
    std::cout << "  All Threads Finished" << std::endl;
    std::cout << "========================================" << std::endl;

    return 0;
}