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
g++ 1102_contour_center.cpp -o 1102_contour_center -I/usr/local/include/opencv4 -L/usr/local/lib -lopencv_core -lopencv_videoio -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc
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

    // 그레이스케일 변환
    cv::Mat imgray;
    cv::cvtColor(img, imgray, cv::COLOR_BGR2GRAY);

    // 이진화 (Thresholding)
    cv::Mat thresh;
    std::cout << "thresh size: " << thresh.rows << " " << thresh.cols << std::endl; 
    cv::threshold(imgray, thresh, 127, 255, 0);

    // 윤곽선 찾기
    /*
    This line declares a nested vector (a vector of vectors) named contours, 
    where each inner vector contains cv::Point objects. 
    */
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(thresh, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

    // 윤곽선 그리기 (첫 번째 윤곽선)
    cv::drawContours(img, contours, 0, cv::Scalar(0, 0, 255), 2);

    // 첫 번째 윤곽선의 Moments 계산
    if (!contours.empty()) {
        cv::Moments M = cv::moments(contours[0]);

        // 중심 좌표 계산
        int cx = static_cast<int>(M.m10 / M.m00);
        int cy = static_cast<int>(M.m01 / M.m00);

        // 중심 좌표 출력
        std::cout << "Centroid: (" << cx << ", " << cy << ")" << std::endl;

        // 중심 좌표 표시
        cv::circle(img, cv::Point(cx, cy), 3, cv::Scalar(255, 0, 0), 4);
    }
    else {
        std::cerr << "No contours found!" << std::endl;
    }

    // 결과 표시
    cv::imshow("win", img);
    cv::imshow("thresold", thresh);


    // 키 입력 대기
    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}
