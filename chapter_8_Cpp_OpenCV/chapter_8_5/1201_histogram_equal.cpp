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
g++ 1201_histogram_equal.cpp  -o 1201_histogram_equal -I/usr/local/include/opencv4 -L/usr/local/lib -lopencv_core -lopencv_videoio -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc
*/

#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

int main() {
    // 이미지 읽기
    cv::Mat img = cv::imread("./resource/hist_equ.jpg", cv::IMREAD_GRAYSCALE);
    if (img.empty()) {
        std::cerr << "Error: Unable to load image!" << std::endl;
        return 1;
    }

    // 히스토그램 계산
    int histSize = 256;
    float range[] = { 0, 256 };
    const float* histRange = { range };
    cv::Mat hist;
    cv::calcHist(&img, 1, 0, cv::Mat(), hist, 1, &histSize, &histRange);

    // 누적 분포 함수(CDF) 계산
    /*
    Creates a vector of float values.
    The vector has histSize elements.
    All elements are initialized to 0.
    */
    std::vector<float> cdf(histSize, 0); 
    cdf[0] = hist.at<float>(0);
    for (int i = 1; i < histSize; i++) {
        cdf[i] = cdf[i - 1] + hist.at<float>(i);
    }

    // CDF 정규화 (0~255 범위로)
    float cdfMin = *std::min_element(cdf.begin(), cdf.end());
    float cdfMax = *std::max_element(cdf.begin(), cdf.end());
    std::vector<uchar> cdfNormalized(histSize, 0);
    for (int i = 0; i < histSize; i++) {
        cdfNormalized[i] = static_cast<uchar>((cdf[i] - cdfMin) * 255 / (cdfMax - cdfMin));
    }

    // 히스토그램 평활화 적용
    cv::Mat imgEqualized = img.clone();
    for (int y = 0; y < img.rows; y++) {
        for (int x = 0; x < img.cols; x++) {
            imgEqualized.at<uchar>(y, x) = cdfNormalized[img.at<uchar>(y, x)];
        }
    }

    // 결과 표시
    cv::imshow("Original", img);
    cv::imshow("Equalized", imgEqualized);

    // 키 입력 대기
    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}
