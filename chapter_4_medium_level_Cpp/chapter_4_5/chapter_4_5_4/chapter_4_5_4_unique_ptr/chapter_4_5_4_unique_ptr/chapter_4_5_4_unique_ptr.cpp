#include <iostream>
#include <memory>
#include <string>

// 로봇의 그리퍼(집게) 하드웨어를 제어하는 클래스
class GripperInterface {
public:
    GripperInterface(int id) : gripperID(id) {
        std::cout << "[Gripper " << gripperID << "] 초기화 및 연결" << std::endl;
    }

    ~GripperInterface() {
        std::cout << "[Gripper " << gripperID << "] 연결 해제 및 소멸" << std::endl;
    }

    void grab() {
        std::cout << "[Gripper " << gripperID << "] 물체 파지 동작 수행" << std::endl;
    }

private:
    int gripperID;
};

int main() {
    std::cout << "=== unique_ptr 테스트 ===" << std::endl;

    // 1. make_unique를 사용한 생성 (권장 방식)
    // gripperA가 유일하게 객체를 소유함
    std::unique_ptr<GripperInterface> gripperA = std::make_unique<GripperInterface>(101);
    gripperA->grab();

    // 2. 소유권 이전 (Move Semantics)
    std::cout << "\n소유권 이전을 시도합니다..." << std::endl;

    // std::unique_ptr<GripperInterface> gripperB = gripperA; // 컴파일 에러! (복사 불가)
    std::unique_ptr<GripperInterface> gripperB = std::move(gripperA); // 소유권 이동

    if (!gripperA) {
        std::cout << "gripperA는 이제 비어있습니다." << std::endl;
    }

    if (gripperB) {
        std::cout << "gripperB가 객체를 소유하고 있습니다." << std::endl;
        gripperB->grab();
    }

    std::cout << "\n메인 함수 종료" << std::endl;
    return 0;
    // gripperB가 스코프를 벗어나며 소멸자 호출
}