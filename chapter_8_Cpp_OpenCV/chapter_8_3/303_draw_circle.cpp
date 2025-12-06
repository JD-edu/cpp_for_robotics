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
You can build this code using 2 ways.

Method 1: simply using command line 
g++ 303_draw_circle.cpp -o 302_draw_circle -I/usr/local/include/opencv4 -L/usr/local/lib -lopencv_core -lopencv_videoio -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc

Method 2: using cmake 
refer to cmake_build.md 
*/

#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    // 빈 이미지 생성 (320x240, 3채널, 8비트)
    cv::Mat img = cv::Mat::zeros(320, 240, CV_8UC3);

    // 빨간색 원 그리기 (중심: (100, 100), 반지름: 50, 두께: 2)
    cv::circle(img, cv::Point(100, 100), 50, cv::Scalar(0, 0, 255), 2);

    // 노란색 원 그리기 (중심: (150, 150), 반지름: 150, 두께: 2)
    cv::circle(img, cv::Point(150, 150), 150, cv::Scalar(255, 255, 51), 2);

    // 이미지 표시
    cv::imshow("my win", img);

    // 키 입력 대기
    cv::waitKey(0);

    // 창 닫기
    cv::destroyAllWindows();

    return 0;
}
