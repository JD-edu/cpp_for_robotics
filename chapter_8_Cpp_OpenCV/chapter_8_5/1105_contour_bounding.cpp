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
g++ 1105_contour_bounding.cpp -o 1105_contour_bounding -I/usr/local/include/opencv4 -L/usr/local/lib -lopencv_core -lopencv_videoio -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc
*/
#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    // 이미지 읽기
    cv::Mat img = cv::imread("./resource/image_single_obj.jpg");
    if (img.empty()) {
        std::cerr << "Error: Unable to load image!" << std::endl;
        return 1;
    }

    // 원본 이미지 복사
    cv::Mat img1 = img.clone();

    // 그레이스케일 변환
    cv::Mat imgray;
    cv::cvtColor(img, imgray, cv::COLOR_BGR2GRAY);

    // 이진화 (Thresholding)
    cv::Mat thresh;
    cv::threshold(imgray, thresh, 127, 255, 0);

    // 윤곽선 찾기
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(thresh, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

    if (!contours.empty()) {
        // 첫 번째 윤곽선
        std::vector<cv::Point> cnt = contours[0];

        // Straight Rectangle (직사각형)
        cv::Rect straightRect = cv::boundingRect(cnt);
        cv::rectangle(img1, straightRect, cv::Scalar(0, 255, 0), 3); // Green

        // Rotated Rectangle (회전된 직사각형)
        cv::RotatedRect rotatedRect = cv::minAreaRect(cnt);
        cv::Point2f boxPoints[4];
        rotatedRect.points(boxPoints);
        for (int i = 0; i < 4; i++) {
            cv::line(img1, boxPoints[i], boxPoints[(i + 1) % 4], cv::Scalar(0, 0, 255), 3); // Blue
        }

        // Minimum Enclosing Circle (최소 외접 원)
        cv::Point2f center;
        float radius;
        cv::minEnclosingCircle(cnt, center, radius);
        cv::circle(img1, center, static_cast<int>(radius), cv::Scalar(255, 255, 0), 3); // Yellow

        // Fitting an Ellipse (타원)
        if (cnt.size() >= 5) { // 타원을 적합시키려면 최소 5개의 점이 필요
            cv::RotatedRect ellipse = cv::fitEllipse(cnt);
            cv::ellipse(img1, ellipse, cv::Scalar(255, 0, 0), 3); // Red
        }
    }
    else {
        std::cerr << "No contours found!" << std::endl;
    }

    // 결과 표시
    cv::imshow("Original", img);
    cv::imshow("Result", img1);

    // 키 입력 대기
    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}
