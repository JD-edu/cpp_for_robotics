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
g++ 202_video_from_file.cpp -o 202_video_from_file -I/usr/local/include/opencv4 -L/usr/local/lib -lopencv_core -lopencv_videoio -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc

Method 2: using cmake 
refer to cmake_build.md 
*/

#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    // 비디오 파일 열기
    cv::VideoCapture cap("./resource/video.avi");

    // 비디오 파일 열기 확인
    if (!cap.isOpened()) {
        std::cerr << "Error: Unable to open video file!" << std::endl;
        return 1;
    }

    while (true) {
        cv::Mat frame, grayFrame;
        bool ret = cap.read(frame); // 프레임 읽기

        // 프레임 읽기 확인
        if (!ret) {
            std::cout << "End of video or error reading frame!" << std::endl;
            break;
        }

        // 프레임을 그레이스케일로 변환
        cv::cvtColor(frame, grayFrame, cv::COLOR_BGR2GRAY);

        // 변환된 프레임 표시
        cv::imshow("my win", grayFrame);

        // 종료 키 체크 ('q' 키로 종료)
        if (cv::waitKey(1) == 'q') {
            break;
        }
    }

    // 리소스 해제
    cap.release();
    cv::destroyAllWindows();

    return 0;
}
