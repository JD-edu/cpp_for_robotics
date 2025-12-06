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
g++ 904_morph_ex_option.cpp  -o 904_morph_ex_option -I/usr/local/include/opencv4 -L/usr/local/lib -lopencv_core -lopencv_videoio -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc
*/
#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    // 이미지 읽기
    cv::Mat img = cv::imread("./resource/morph_char.png", cv::IMREAD_COLOR);
    if (img.empty()) {
        std::cerr << "Error: Unable to load image!" << std::endl;
        return 1;
    }

    // 커널 생성
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));

    // 모폴로지 연산 결과 저장
    cv::Mat img_dilate, img_erode, img_open, img_close, img_gradient, img_tophat, img_blackhat;

    // Dilation (팽창)
    cv::dilate(img, img_dilate, kernel, cv::Point(-1, -1), 1);

    // Erosion (침식)
    cv::erode(img, img_erode, kernel, cv::Point(-1, -1), 1);

    // Opening (열기)
    cv::morphologyEx(img, img_open, cv::MORPH_OPEN, kernel);

    // Closing (닫기)
    cv::morphologyEx(img, img_close, cv::MORPH_CLOSE, kernel);

    // Gradient (모폴로지 그래디언트)
    cv::morphologyEx(img, img_gradient, cv::MORPH_GRADIENT, kernel);

    // Top Hat
    cv::morphologyEx(img, img_tophat, cv::MORPH_TOPHAT, kernel);

    // Black Hat
    cv::morphologyEx(img, img_blackhat, cv::MORPH_BLACKHAT, kernel);

    // 결과 표시
    cv::imshow("Original", img);
    cv::imshow("Dilation", img_dilate);
    cv::imshow("Erosion", img_erode);
    cv::imshow("Opening", img_open);
    cv::imshow("Closing", img_close);
    cv::imshow("Gradient", img_gradient);
    cv::imshow("Top Hat", img_tophat);
    cv::imshow("Black Hat", img_blackhat);

    // 키 입력 대기
    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}
