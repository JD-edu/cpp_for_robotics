#pragma once
#include <list>
#include <string>
#include <iostream>

// list를 사용한 실행 기록 관리 클래스
class ExecutionHistory {
private:
    std::list<std::string> actions;  // 📌 list로 실행 기록 저장

public:
    // 실행 기록 추가
    void addRecord(const std::string& action) {
        actions.push_back(action);  // ⭐ list에 추가
        std::cout << "기록 추가: " << action << std::endl;
    }

    // 특정 기록 제거 - list의 반복자 활용
    void removeRecord(const std::string& action) {
        for (auto it = actions.begin(); it != actions.end(); ++it) {
            if (*it == action) {
                actions.erase(it);  // ⭐ 중간 삭제 O(1)
                std::cout << "기록 삭제: " << action << std::endl;
                return;
            }
        }
        std::cout << "'" << action << "' 찾을 수 없음" << std::endl;
    }

    // 모든 기록 출력 - list 순회
    void displayAll() const {
        std::cout << "\n=== 실행 기록 (" << actions.size() << "개) ===" << std::endl;

        int count = 1;
        for (const auto& action : actions) {  // ⭐ list 순회
            std::cout << count++ << ". " << action << std::endl;
        }
        std::cout << "========================\n" << std::endl;
    }
};