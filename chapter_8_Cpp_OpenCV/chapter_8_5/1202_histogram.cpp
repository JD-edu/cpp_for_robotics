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
g++ 1202_histogram.cpp  -o 1202_histogram -I/usr/local/include/opencv4 -L/usr/local/lib -lopencv_core -lopencv_videoio -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc
*/

#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    // 이미지 읽기 (그레이스케일로)
    cv::Mat img1 = cv::imread("./resource/flower1.jpg", cv::IMREAD_GRAYSCALE);
    cv::Mat img2 = cv::imread("./resource/flower2.jpg", cv::IMREAD_GRAYSCALE);

    if (img1.empty() || img2.empty()) {
        std::cerr << "Error: Unable to load images!" << std::endl;
        return 1;
    }

    // 히스토그램 계산
    int histSize = 256; // 히스토그램 bin 크기
    float range[] = { 0, 256 }; // 픽셀 값 범위
    const float* histRange = { range };

    cv::Mat hist1, hist2;
    cv::calcHist(&img1, 1, 0, cv::Mat(), hist1, 1, &histSize, &histRange);
    cv::calcHist(&img2, 1, 0, cv::Mat(), hist2, 1, &histSize, &histRange);

    // 히스토그램 정규화 (0-255 범위로)
    cv::normalize(hist1, hist1, 0, 255, cv::NORM_MINMAX);
    cv::normalize(hist2, hist2, 0, 255, cv::NORM_MINMAX);

    // 히스토그램을 시각화하기 위한 이미지 생성
    int histImageWidth = 512;  // 히스토그램 너비
    int histImageHeight = 400; // 히스토그램 높이
    int binWidth = cvRound((double)histImageWidth / histSize);

    cv::Mat histImage(histImageHeight, histImageWidth, CV_8UC3, cv::Scalar(0, 0, 0));

    // 히스토그램 데이터 그리기
    for (int i = 1; i < histSize; i++) {
        cv::line(histImage,
            cv::Point(binWidth * (i - 1), histImageHeight - cvRound(hist1.at<float>(i - 1))),
            cv::Point(binWidth * i, histImageHeight - cvRound(hist1.at<float>(i))),
            cv::Scalar(0, 0, 255), 2, 8, 0); // 빨간색 (img1 히스토그램)

        cv::line(histImage,
            cv::Point(binWidth * (i - 1), histImageHeight - cvRound(hist2.at<float>(i - 1))),
            cv::Point(binWidth * i, histImageHeight - cvRound(hist2.at<float>(i))),
            cv::Scalar(0, 255, 0), 2, 8, 0); // 초록색 (img2 히스토그램)
    }

    // 결과 표시
    cv::imshow("Image 1", img1);
    cv::imshow("Image 2", img2);
    cv::imshow("Histogram", histImage);

    // 키 입력 대기
    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}
