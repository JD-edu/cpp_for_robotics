// camera_handler.cpp
#include "camera_handler.hpp"
#include <iostream>

CameraHandler::CameraHandler(int device_id) 
    : device_id(device_id), is_initialized(false) {}

CameraHandler::~CameraHandler() {
    release();
}

bool CameraHandler::initialize(int width, int height, int fps) {
    cap.open(device_id);
  
    if (!cap.isOpened()) {
        std::cerr << "Error: 카메라를 열 수 없습니다!" << std::endl;
        return false;
    }
  
    cap.set(cv::CAP_PROP_FRAME_WIDTH, width);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, height);
    cap.set(cv::CAP_PROP_FPS, fps);
  
    is_initialized = true;
    return true;
}

bool CameraHandler::captureFrame(cv::Mat& frame) {
    if (!is_initialized) return false;
  
    cap >> frame;
    return !frame.empty();
}

void CameraHandler::addOverlay(cv::Mat& frame, const std::string& text) {
    cv::putText(frame, text, cv::Point(10, 30), 
                cv::FONT_HERSHEY_SIMPLEX, 0.7, 
                cv::Scalar(0, 255, 0), 2);
}

void CameraHandler::release() {
    if (cap.isOpened()) {
        cap.release();
    }
    is_initialized = false;
}