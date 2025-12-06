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
g++ 404_get_image_roi.cpp -o 404_get_image_roi -I/usr/local/include/opencv4 -L/usr/local/lib -lopencv_core -lopencv_videoio -lopencv_highgui -lopencv_imgcodec
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

    // 이미지 크기 확인
    int img_width = img.cols;
    int img_height = img.rows;

    // ROI 좌표 및 크기 정의
    int roi_x = 100, roi_y = 100, roi_width = 50, roi_height = 50;

    // ROI가 이미지 크기를 초과하지 않도록 검증
    if (roi_x + roi_width > img_width || roi_y + roi_height > img_height) {
        std::cerr << "Error: ROI exceeds image boundaries!" << std::endl;
        return 1;
    }

    // ROI 추출
    cv::Rect roi(roi_x, roi_y, roi_width, roi_height);
    cv::Mat array_ROI = img(roi);

    // ROI를 원본 이미지의 (0, 0) 위치에 복사
    array_ROI.copyTo(img(cv::Rect(0, 0, roi_width, roi_height)));

    // 결과 이미지 표시
    cv::imshow("Modified Image", img);

    // 키 입력 대기
    cv::waitKey(0);

    // 창 닫기
    cv::destroyAllWindows();

    return 0;
}

