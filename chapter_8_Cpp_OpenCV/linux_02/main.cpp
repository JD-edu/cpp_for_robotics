// main.cpp
#include "camera_handler.hpp"
#include <iostream>

int main(int argc, char** argv) {
    CameraHandler camera(0);
  
    if (!camera.initialize(640, 480, 30)) {
        return -1;
    }
  
    std::cout << "카메라 스트림 시작 (q를 눌러 종료)" << std::endl;
  
    cv::Mat frame;
    while (true) {
        if (!camera.captureFrame(frame)) {
            std::cerr << "프레임 캡처 실패" << std::endl;
            break;
        }
    
        camera.addOverlay(frame, "OpenCV Camera");
        cv::imshow("Camera Stream", frame);
    
        if (cv::waitKey(1) == 'q') break;
    }
  
    cv::destroyAllWindows();
    return 0;
}