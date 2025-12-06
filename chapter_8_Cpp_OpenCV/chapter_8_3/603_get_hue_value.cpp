/*
MIT License

Copyright (c) 2024 JD edu. http://jdedu.kr author: conner.jeong@gmail.com
     
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
     
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
     
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN TH
SOFTWARE.
*/

/*
g++ 603_get_hue_value.cpp -o 603_get_hue_value -I/usr/local/include/opencv4 -L/usr/local/lib -lopencv_core -lopencv_videoio -lopencv_highgui -lopencv_imgproc
*/

#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    // 초기값 설정
    int hue = 0;

    // BGR 색상 정의
    cv::Mat bgrColor(300, 300, CV_8UC3, cv::Scalar(85, 109, 215)); // BGR: (85, 109, 215)

    // BGR을 HSV로 변환
    cv::Mat hsvColor;
    cv::cvtColor(bgrColor, hsvColor, cv::COLOR_BGR2HSV);

    // Hue 값 추출
    //hue = hsvColor.at<cv::Vec3b>(0, 0)[0];
    cv::Vec3b pixel = hsvColor.at<cv::Vec3b>(0, 0); // Get the pixel at (0, 0)
    hue = pixel[0];         // Hue channel
    //int saturation = pixel[1];  // Saturation channel
    //int value = pixel[2];       // Value (Brightness) channel


    // HSV 하한 및 상한 값 계산
    int lowerHue = std::max(hue - 10, 0); // Hue는 0 이상이어야 함
    int upperHue = std::min(hue + 10, 180); // Hue는 180을 초과하지 않음 (OpenCV HSV 범위)

    // 결과 출력
    std::cout << "Lower bound is :" << std::endl;
    std::cout << "[" << lowerHue << ", 100, 100]" << std::endl;

    std::cout << "Upper bound is :" << std::endl;
    std::cout << "[" << upperHue << ", 255, 255]" << std::endl;

    std::cout << "Hue: " << hue << std::endl;

    cv::imshow("hsv", hsvColor);
    cv::imshow("bgr", bgrColor);
    cv::waitKey(0);

    return 0;
}
