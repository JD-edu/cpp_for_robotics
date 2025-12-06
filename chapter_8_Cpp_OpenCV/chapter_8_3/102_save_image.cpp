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
g++ 102_save_image.cpp -o 102_save_image -I/usr/local/include/opencv4 -L/usr/local/lib -lopencv_core -lopencv_videoio -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc

Method 2: using cmake 
refer to cmake_build.md 
*/
#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    // 이미지 읽기 (컬러 모드)
    cv::Mat img = cv::imread("./resource/lena.jpg", cv::IMREAD_COLOR);

    // 이미지 로드 확인
    if (img.empty()) {
        std::cerr << "Error: Unable to load image!" << std::endl;
        return 1; // 프로그램 종료
    }
    
    // 이미지 표시
    cv::imshow("Image Window", img);

    // 키 입력 대기
    int key = cv::waitKey(0) & 0xFF;

    // ESC 키가 아닐 경우 이미지 저장
    if (key != 27) { // 27은 ESC 키 코드
        if (cv::imwrite("lena_2.jpg", img)) {
            std::cout << "Image saved as 'lena_2.jpg'" << std::endl;
        }
        else {
            std::cerr << "Error: Unable to save image!" << std::endl;
        }
    }

    // 모든 창 닫기
    cv::destroyAllWindows();

    return 0;
}
