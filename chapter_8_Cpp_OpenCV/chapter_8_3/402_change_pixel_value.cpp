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
To build this code
g++ 402_change_pixel_value.cpp -o 402_change_pixel_value -I/usr/local/include/opencv4 -L/usr/local/lib -lopencv_core -lopencv_videoio -lopencv_highgui -lopencv_imgcodecs
*/

#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    // 이미지 읽기 (컬러 모드)
    cv::Mat img = cv::imread("./resource/lena.jpg", cv::IMREAD_COLOR);

    // 이미지 로드 확인
    if (img.empty()) {
        std::cerr << "Error: Unable to load image!" << std::endl;
        return 1;
    }

    // 특정 픽셀 값 변경

    //img.at<cv::Vec3b>(10, 10) = cv::Vec3b(255, 255, 255); // (10, 10)
    //img.at<cv::Vec3b>(10, 11) = cv::Vec3b(255, 255, 255); // (10, 11)
    //img.at<cv::Vec3b>(11, 10) = cv::Vec3b(255, 255, 255); // (11, 10)
    //img.at<cv::Vec3b>(11, 11) = cv::Vec3b(255, 255, 255); // (11, 11)

    cv::Vec3b& p1 = img.at<cv::Vec3b>(10, 10);
    cv::Vec3b& p2 = img.at<cv::Vec3b>(10, 11);
    cv::Vec3b& p3 = img.at<cv::Vec3b>(11, 10);
    cv::Vec3b& p4 = img.at<cv::Vec3b>(10, 11);
    
    p1 = cv::Vec3b(255, 255, 255); // (10, 10)
    p2 = cv::Vec3b(255, 255, 255); // (10, 11)
    p3 = cv::Vec3b(255, 255, 255); // (11, 10)
    p4 = cv::Vec3b(255, 255, 255); // (11, 11)

    // 이미지 표시
    cv::imshow("my win", img);

    // 키 입력 대기
    cv::waitKey(0);

    // 창 닫기
    cv::destroyAllWindows();

    return 0;
}
