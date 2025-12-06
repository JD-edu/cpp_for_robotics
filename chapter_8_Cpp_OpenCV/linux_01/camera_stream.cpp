// camera_stream.cpp
// Linux/POSIX 시스템에서 올바른 include 방법
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

// main 함수는 반드시 이 형식을 따라야 합니다
int main(int argc, char** argv)
{
    // 웹캠 캡처 객체 생성 (기본 카메라: 0)
    VideoCapture cap(0);
  
    // 카메라 연결 확인
    if (!cap.isOpened()) {
        cerr << "Error: 카메라를 열 수 없습니다!" << endl;
        return -1;
    }
  
    // 카메라 설정
    cap.set(CAP_PROP_FRAME_WIDTH, 640);
    cap.set(CAP_PROP_FRAME_HEIGHT, 480);
    cap.set(CAP_PROP_FPS, 30);
  
    cout << "카메라 라이브 스트림을 시작합니다..." << endl;
    cout << "종료하려면 'q' 키를 누르세요." << endl;
  
    Mat frame;
    char key;
  
    while (true) {
        // 프레임 캡처
        cap >> frame;
    
        if (frame.empty()) {
            cerr << "Error: 빈 프레임이 캡처되었습니다!" << endl;
            break;
        }
    
        // 현재 시간을 프레임에 오버레이
        string timestamp = "Time: " + 
            to_string(getTickCount() / getTickFrequency());
        putText(frame, timestamp, Point(10, 30), 
                FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 255, 0), 2);
    
        // 프레임 해상도 정보 표시
        string resolution = "Resolution: " + 
            to_string(frame.cols) + "x" + to_string(frame.rows);
        putText(frame, resolution, Point(10, 60), 
                FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 0, 0), 1);
    
        // 프레임 출력
        imshow("Camera Live Stream", frame);
    
        // 키 입력 대기 (1ms)
        key = waitKey(1) & 0xFF;
        if (key == 'q' || key == 27) { // 'q' 또는 ESC 키
            break;
        }
    }
  
    // 리소스 해제
    cap.release();
    destroyAllWindows();
  
    cout << "프로그램을 종료합니다." << endl;
    return 0;
}