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
g++ 702_otsu_binary.cpp -o 702_otsu_binary -I/usr/local/include/opencv4 -L/usr/local/lib -lopencv_core -lopencv_videoio -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc
*/
#include <opencv2/opencv.hpp>
#include <iostream>

void showHistogram(const std::string& title, const cv::Mat& img) {
    // 히스토그램 계산
    std::vector<cv::Mat> bgr_planes;
    cv::split(img, bgr_planes);

    // get info from bgr_planes
    /*
    std::cout << "size of bgr_plane " << bgr_planes.size() << std::endl;
    for (size_t i = 0; i < bgr_planes.size(); i++) {
        std::cout << "Plane " << i << ": Rows = " << bgr_planes[i].rows 
              << ", Cols = " << bgr_planes[i].cols 
              << ", Type = " << bgr_planes[i].type() << std::endl;
    }
    */

    int histSize = 256;
    float range[] = { 0, 256 }; // 히스토그램 범위
    const float* histRange =  range ;

    cv::Mat hist;
    cv::calcHist(&img, 1, 0, cv::Mat(), hist, 1, &histSize, &histRange);

    // 히스토그램 그리기
    int hist_w = 512; int hist_h = 400;
    int bin_w = cvRound((double)hist_w / histSize);

    cv::Mat histImage(hist_h, hist_w, CV_8UC1, cv::Scalar(0));

    // 히스토그램 정규화
    cv::normalize(hist, hist, 0, histImage.rows, cv::NORM_MINMAX);

    for (int i = 1; i < histSize; i++) {
        cv::line(histImage,
            cv::Point(bin_w * (i - 1), hist_h - cvRound(hist.at<float>(i - 1))),
            cv::Point(bin_w * i, hist_h - cvRound(hist.at<float>(i))),
            cv::Scalar(255), 2, 8, 0);
    }

    cv::imshow(title, histImage);
}

int main() {
    // 이미지 읽기 (그레이스케일)
    cv::Mat img = cv::imread("./resource/lena.jpg", cv::IMREAD_GRAYSCALE);

    if (img.empty()) {
        std::cerr << "Error: Unable to load image!" << std::endl;
        return 1;
    }

    // 1. 전역 임계값
    cv::Mat th1;
    cv::threshold(img, th1, 127, 255, cv::THRESH_BINARY);

    // 2. Otsu 임계값
    cv::Mat th2;
    cv::threshold(img, th2, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);

    // 3. 가우시안 블러 + Otsu 임계값
    cv::Mat blur, th3;
    cv::GaussianBlur(img, blur, cv::Size(5, 5), 0);
    cv::threshold(blur, th3, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);

    // 결과 이미지 표시
    cv::imshow("Original Noisy Image", img);
    showHistogram("Histogram of Original", img);
    cv::imshow("Global Thresholding (v=127)", th1);

    cv::imshow("Otsu's Thresholding", th2);
    showHistogram("Histogram of Otsu Thresholding", img);

    cv::imshow("Gaussian Filtered Image", blur);
    cv::imshow("Otsu's Thresholding After Gaussian", th3);

    // 키 입력 대기
    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}
