#pragma once
#include <map>
#include <string>
#include <iostream>

// map을 사용한 로봇 설정 관리 클래스
class RobotConfig {
private:
    std::map<std::string, double> settings;  // 📌 map으로 설정 저장 (키: 설정 이름, 값: 설정 값)

public:
    // 설정 값 저장/수정 - map의 [] 연산자 활용
    void setSetting(const std::string& key, double value) {
        settings[key] = value;  // ⭐ map에 저장 (키가 없으면 생성, 있으면 수정)
        std::cout << "설정: " << key << " = " << value << std::endl;
    }

    // 설정 값 조회 - map의 find() 활용
    double getSetting(const std::string& key, double defaultValue = 0.0) const {
        auto it = settings.find(key);  // ⭐ 키 검색

        if (it != settings.end()) {  // 찾았으면
            return it->second;  // 값 반환
        }
        else {
            std::cout << "경고: '" << key << "' 설정 없음 (기본값: "
                << defaultValue << ")" << std::endl;
            return defaultValue;
        }
    }

    // 설정 존재 확인 - map의 count() 활용
    bool hasSetting(const std::string& key) const {
        return settings.count(key) > 0;  // ⭐ count()는 0 또는 1 반환
    }

    // 설정 삭제 - map의 erase() 활용
    void removeSetting(const std::string& key) {
        if (settings.erase(key)) {  // ⭐ 삭제 성공하면 true
            std::cout << "설정 삭제: " << key << std::endl;
        }
        else {
            std::cout << "삭제 실패: '" << key << "' 설정 없음" << std::endl;
        }
    }

    // 모든 설정 출력 - map 순회
    void displayAll() const {
        std::cout << "\n=== 모든 설정 ===" << std::endl;
        std::cout << "총 " << settings.size() << "개 설정" << std::endl;  // ⭐ size()

        // 범위 기반 for문으로 순회 (자동 정렬된 순서로 출력됨!)
        for (const auto& pair : settings) {  // ⭐ map 순회
            std::cout << "  " << pair.first << " = " << pair.second << std::endl;
            //                  ↑ 키              ↑ 값
        }
        std::cout << "================\n" << std::endl;
    }

    // 설정 개수 반환
    size_t getSettingCount() const {
        return settings.size();  // ⭐ size()
    }
};