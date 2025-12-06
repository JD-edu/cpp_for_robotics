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
g++ 502_bit_image_operation.cpp -o 502_bit_image_operation -I/usr/local/include/opencv4 -L/usr/local/lib -lopencv_core -lopencv_videoio -lopencv_highgui -lopencv_imgcodecs
*/

#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    // 두 이미지 읽기 (컬러 모드)
    cv::Mat img1 = cv::imread("./resource/black_white1.jpg", cv::IMREAD_COLOR);
    cv::Mat img2 = cv::imread("./resource/black_white2.jpg", cv::IMREAD_COLOR);

    // 이미지 로드 확인
    if (img1.empty() || img2.empty()) {
        std::cerr << "Error: Unable to load one or both images!" << std::endl;
        return 1;
    }

    // 두 이미지의 크기가 같은지 확인 및 조정
    if (img1.size() != img2.size()) {
        std::cerr << "Error: Images must have the same size for bitwise operations!" << std::endl;
        return 1;
    }

    // 비트 연산 수행
    cv::Mat img_NOT, img_AND, img_OR;
    cv::bitwise_not(img1, img_NOT);     // NOT 연산
    cv::bitwise_and(img1, img2, img_AND); // AND 연산
    cv::bitwise_or(img1, img2, img_OR);  // OR 연산

    // 결과 표시
    cv::imshow("bit_NOT", img_NOT);
    cv::imshow("bit_AND", img_AND);
    cv::imshow("bit_OR", img_OR);

    // 키 입력 대기
    cv::waitKey(0);

    // 창 닫기
    cv::destroyAllWindows();

    return 0;
}
