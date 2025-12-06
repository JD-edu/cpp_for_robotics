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
g++ 803_move_image.cpp -o 803_move_image -I/usr/local/include/opencv4 -L/usr/local/lib -lopencv_core -lopencv_videoio -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc
*/

#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    // 웹캠 초기화
    cv::VideoCapture cap(0);

    // 웹캠 열기 확인
    if (!cap.isOpened()) {
        std::cerr << "Error: Unable to open the webcam!" << std::endl;
        return 1;
    }

    while (true) {
        cv::Mat frame, movedFrame;

        // 웹캠에서 프레임 읽기
        bool ret = cap.read(frame);
        if (!ret) {
            std::cerr << "Error: Unable to read frame from webcam!" << std::endl;
            break;
        }

        // 원본 프레임 표시
        cv::imshow("my win", frame);

        // 프레임 이동 변환 행렬 정의
        int rows = frame.rows;
        int cols = frame.cols;
        cv::Mat M = (cv::Mat_<float>(2, 3) << 1, 0, 50, 0, 1, 50);

        // 프레임 이동 적용
        cv::warpAffine(frame, movedFrame, M, cv::Size(cols, rows));

        // 이동된 프레임 표시
        cv::imshow("move", movedFrame);

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
