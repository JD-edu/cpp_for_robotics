#include <iostream>
#include <cmath>
using namespace std;

int main() {
    // 로봇의 현재 위치
    double robotX = 0.0, robotY = 0.0;
  
    // 목표 지점
    double targetX = 10.0, targetY = 8.0;
  
    // 이동 속도 (미터/초)
    double speed = 1.5;
  
    cout << "=== 로봇 자율 주행 시스템 ===" << endl;
    cout << "시작 위치: (" << robotX << ", " << robotY << ")" << endl;
    cout << "목표 위치: (" << targetX << ", " << targetY << ")" << endl << endl;
  
    int step = 0;
  
    // 목표 지점까지의 거리가 0.5미터 이상일 때까지 반복
    while (true) {
        // 현재 위치에서 목표까지의 거리 계산
        double distance = sqrt(pow(targetX - robotX, 2) + pow(targetY - robotY, 2));
    
        cout << "스텝 " << ++step << ":" << endl;
        cout << "  현재 위치: (" << robotX << ", " << robotY << ")" << endl;
        cout << "  목표까지 거리: " << distance << "m" << endl;
    
        // 목표 지점에 충분히 가까우면 종료
        if (distance < 0.5) {
            cout << "목표 지점에 도달했습니다!" << endl;
            break;
        }
    
        // 목표 방향 계산
        double directionX = (targetX - robotX) / distance;
        double directionY = (targetY - robotY) / distance;
    
        // 로봇 이동
        robotX += directionX * speed;
        robotY += directionY * speed;
    
        cout << "  이동 후 위치: (" << robotX << ", " << robotY << ")" << endl;
        cout << "  ========================" << endl;
    
        // 안전을 위한 최대 스텝 제한
        if (step >= 10) {
            cout << "최대 스텝 수에 도달했습니다." << endl;
            break;
        }
    }
  
    cout << endl << "총 이동 스텝: " << step << endl;
    cout << "최종 위치: (" << robotX << ", " << robotY << ")" << endl;
  
    return 0;
}