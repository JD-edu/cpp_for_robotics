#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;

int main() {
    // 1. VideoCapture 객체 생성 및 카메라 열기
    // 0은 시스템에 연결된 기본 카메라를 의미합니다. 다른 카메라를 사용하려면 숫자를 변경하세요.
    VideoCapture cap(0);

    // 카메라가 성공적으로 열렸는지 확인
    if (!cap.isOpened()) {
        std::cerr << "Error: 카메라를 열 수 없습니다!" << std::endl;
        // 대부분의 경우, 다른 프로그램이 카메라를 사용 중이거나 드라이버 문제일 수 있습니다.
        return -1;
    }

    // 2. 결과를 표시할 윈도우 생성
    namedWindow("Camera Stream", WINDOW_AUTOSIZE);

    Mat frame;

    // 3. 무한 루프를 통한 프레임 연속 처리
    while (true) {
        // 카메라에서 프레임을 읽어 Mat 객체 'frame'에 저장
        cap.read(frame);

        // 프레임을 제대로 읽지 못했거나 프레임이 비어있는 경우 루프 종료
        if (frame.empty()) {
            std::cerr << "Error: 빈 프레임이 감지되어 스트림을 종료합니다." << std::endl;
            break;
        }

        // 4. 프레임 표시
        imshow("Camera Stream", frame);

        // 5. 키 입력 대기 및 종료 조건
        // waitKey(1)은 1ms 동안 키 입력을 대기합니다.
        // 'q' 키를 누르거나 ESC 키(아스키 코드 27)를 누르면 루프 종료
        if (waitKey(1) == 'q' || waitKey(1) == 27) {
            break;
        }
    }

    // 6. 사용한 자원 해제
    // VideoCapture 객체 해제 및 생성된 모든 윈도우 닫기
    cap.release();
    destroyAllWindows();

    return 0;
}