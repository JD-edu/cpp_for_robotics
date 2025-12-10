#pragma once
#include <vector>
#include <iostream>
#include <cmath>

// 로봇 경로의 좌표점
struct Point {
    double x, y;

    Point(double x_val = 0.0, double y_val = 0.0) : x(x_val), y(y_val) {}

    // 두 점 사이의 거리 계산 (피타고라스 정리)
    double distanceTo(const Point& other) const {
        double dx = x - other.x;
        double dy = y - other.y;
        return sqrt(dx * dx + dy * dy);
    }

    void print() const {
        std::cout << "(" << x << ", " << y << ")";
    }
};

// vector를 사용한 로봇 경로 관리 클래스
class PathManager {
private:
    std::vector<Point> waypoints;  // 📌 vector로 경유점 저장

public:
    // 경유점 추가 - vector의 push_back() 활용
    void addWaypoint(const Point& point) {
        waypoints.push_back(point);  // ⭐ vector에 추가
        std::cout << "경유점 추가: ";
        point.print();
        std::cout << " (총 " << waypoints.size() << "개)" << std::endl;
    }

    // 특정 인덱스의 경유점 제거 - vector의 erase() 활용
    void removeWaypoint(size_t index) {
        if (index >= waypoints.size()) {
            std::cout << "잘못된 인덱스: " << index << std::endl;
            return;
        }

        std::cout << "경유점 제거: ";
        waypoints[index].print();
        std::cout << std::endl;

        waypoints.erase(waypoints.begin() + index);  // ⭐ vector에서 삭제
    }

    // 총 경로 거리 계산 - vector 순회
    double getTotalDistance() const {
        double total = 0.0;
        for (size_t i = 1; i < waypoints.size(); ++i) {
            total += waypoints[i - 1].distanceTo(waypoints[i]);
        }
        return total;
    }

    // 경로 정보 출력 - vector의 size()와 인덱스 접근
    void displayPath() const {
        std::cout << "\n=== 경로 정보 ===" << std::endl;
        std::cout << "총 경유점: " << waypoints.size() << "개" << std::endl;  // ⭐ size()

        for (size_t i = 0; i < waypoints.size(); ++i) {
            std::cout << "  " << (i + 1) << ". ";
            waypoints[i].print();  // ⭐ 인덱스 접근 waypoints[i]

            if (i < waypoints.size() - 1) {
                double dist = waypoints[i].distanceTo(waypoints[i + 1]);
                std::cout << " → " << dist << "m";
            }
            std::cout << std::endl;
        }

        std::cout << "총 거리: " << getTotalDistance() << "m" << std::endl;
        std::cout << "=================\n" << std::endl;
    }

    // vector가 비어있는지 확인
    bool isEmpty() const {
        return waypoints.empty();  // ⭐ empty()
    }

    // 경유점 개수 반환
    size_t getWaypointCount() const {
        return waypoints.size();  // ⭐ size()
    }
};