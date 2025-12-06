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
g++ 701_threshold.cpp -o 701_threshold -I/usr/local/include/opencv4 -L/usr/local/lib -lopencv_core -lopencv_videoio -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc
*/
#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    // 이미지 읽기 (컬러 모드 -> 그레이스케일 변환)
    cv::Mat img = cv::imread("./resource/image_single_obj.jpg", cv::IMREAD_COLOR);

    // 이미지 로드 확인
    if (img.empty()) {
        std::cerr << "Error: Unable to load image!" << std::endl;
        return 1;
    }

    // 그레이스케일 변환
    cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);

    // 다양한 임계값 변환 결과 저장
    cv::Mat img_thresh, img_thresh1, img_thresh2, img_thresh3, img_thresh4;

    cv::threshold(img, img_thresh, 127, 255, cv::THRESH_BINARY);
    cv::threshold(img, img_thresh1, 127, 255, cv::THRESH_BINARY_INV);
    cv::threshold(img, img_thresh2, 127, 255, cv::THRESH_TRUNC);
    cv::threshold(img, img_thresh3, 127, 255, cv::THRESH_TOZERO);
    cv::threshold(img, img_thresh4, 127, 255, cv::THRESH_TOZERO_INV);

    // 결과 이미지 표시
    cv::imshow("Original Gray", img);
    cv::imshow("Binary", img_thresh);
    cv::imshow("Binary Inverted", img_thresh1);
    cv::imshow("Truncation", img_thresh2);
    cv::imshow("To Zero", img_thresh3);
    cv::imshow("To Zero Inverted", img_thresh4);

    // 키 입력 대기
    cv::waitKey(0);

    // 창 닫기
    cv::destroyAllWindows();

    return 0;
}
