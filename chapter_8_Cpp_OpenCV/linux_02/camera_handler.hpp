// camera_handler.hpp
#ifndef CAMERA_HANDLER_HPP
#define CAMERA_HANDLER_HPP

#include <opencv2/opencv.hpp>
#include <string>

class CameraHandler {
public:
    CameraHandler(int device_id = 0);
    ~CameraHandler();
  
    bool initialize(int width = 640, int height = 480, int fps = 30);
    bool captureFrame(cv::Mat& frame);
    void addOverlay(cv::Mat& frame, const std::string& text);
    void release();
  
private:
    cv::VideoCapture cap;
    int device_id;
    bool is_initialized;
};

#endif // CAMERA_HANDLER_HPP