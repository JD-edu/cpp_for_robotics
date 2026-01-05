#include <iostream>
#include <memory>
#include <vector>

// 카메라 영상 프레임을 저장하는 클래스
class CameraFrame {
public:
    CameraFrame(int frameNo) : frameNumber(frameNo) {
        std::cout << "[Frame " << frameNumber << "] 메모리 할당됨" << std::endl;
    }
    ~CameraFrame() {
        std::cout << "[Frame " << frameNumber << "] 메모리 해제됨" << std::endl;
    }
    void process(const std::string& module) {
        std::cout << module << "에서 Frame " << frameNumber << " 처리 중" << std::endl;
    }

private:
    int frameNumber;
};

int main() {
    std::cout << "=== shared_ptr 테스트 ===" << std::endl;

    // 1. make_shared로 프레임 생성 (참조 카운트: 1)
    std::shared_ptr<CameraFrame> frame = std::make_shared<CameraFrame>(1);

    {
        std::cout << "\n[내부 블록 시작]" << std::endl;

        // 2. SLAM 모듈이 프레임을 공유받음 (참조 카운트: 2)
        std::shared_ptr<CameraFrame> slamPtr = frame;
        slamPtr->process("SLAM 모듈");
        std::cout << "현재 참조 카운트: " << frame.use_count() << std::endl;

        // 3. 객체 인식 모듈이 프레임을 공유받음 (참조 카운트: 3)
        std::shared_ptr<CameraFrame> objectPtr = frame;
        objectPtr->process("AI 모듈");
        std::cout << "현재 참조 카운트: " << frame.use_count() << std::endl;

        std::cout << "[내부 블록 종료]" << std::endl;
        // slamPtr과 objectPtr이 소멸됨 (참조 카운트 감소: 3 -> 1)
    }

    std::cout << "\n블록 탈출 후 참조 카운트: " << frame.use_count() << std::endl;
    frame->process("메인 로직");

    std::cout << "\n프로그램 종료" << std::endl;
    return 0;
    // frame 포인터가 소멸되면서 참조 카운트가 0이 됨 -> 실제 메모리 해제
}