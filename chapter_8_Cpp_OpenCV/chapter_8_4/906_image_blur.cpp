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
g++ 906_image_blur.cpp  -o 906_image_blur -I/usr/local/include/opencv4 -L/usr/local/lib -lopencv_core -lopencv_videoio -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc
*/

#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    // 이미지 읽기
    cv::Mat img = cv::imread("./resource/lena.jpg");
    if (img.empty()) {
        std::cerr << "Error: Unable to load image!" << std::endl;
        return 1;
    }

    // BGR -> RGB 변환 (Matplotlib와 유사한 색상 순서를 위해)
    cv::Mat imgRGB;
    cv::cvtColor(img, imgRGB, cv::COLOR_BGR2RGB);

    // Blur (일반 블러)
    cv::Mat dst1;
    cv::blur(imgRGB, dst1, cv::Size(7, 7));

    // Gaussian Blur
    cv::Mat dst2;
    cv::GaussianBlur(imgRGB, dst2, cv::Size(5, 5), 0);

    // Median Blur
    cv::Mat dst3;
    cv::medianBlur(imgRGB, dst3, 9);

    // Bilateral Filtering
    cv::Mat dst4;
    cv::bilateralFilter(imgRGB, dst4, 9, 75, 75);

    // 결과 표시 (윈도우 생성 및 순차 표시)
    cv::imshow("Original", imgRGB);
    cv::imshow("Blur (7x7)", dst1);
    cv::imshow("Gaussian Blur (5x5)", dst2);
    cv::imshow("Median Blur", dst3);
    cv::imshow("Bilateral", dst4);

    // 키 입력 대기
    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}
