#include <iostream>
using namespace std;

int main() {
    cout << "=== 6축 로봇 팔 초기화 시퀀스 ===" << endl;
  
    // 각 관절의 목표 각도 (도 단위)
    double targetAngles[6] = {0, 45, -30, 90, 0, 180};
    string jointNames[6] = {"베이스", "어깨", "팔꿈치", "손목1", "손목2", "손목3"};
  
    for (int joint = 0; joint < 6; joint++) {
        cout << "관절 " << (joint + 1) << " (" << jointNames[joint] << ") 이동 중..." << endl;
    
        // 각 관절을 10도씩 점진적으로 이동
        for (int step = 0; step <= targetAngles[joint]; step += 10) {
            cout << "  현재 각도: " << step << "° ";
        
            // 진행률 표시
            if (targetAngles[joint] != 0) {
                int progress = (step * 100) / static_cast<int>(targetAngles[joint]);
                cout << "(" << progress << "% 완료)";
            }
            cout << endl;
        }
    
        cout << "관절 " << (joint + 1) << " 목표 위치 도달: " 
             << targetAngles[joint] << "°" << endl << endl;
    }
  
    cout << "모든 관절 초기화 완료!" << endl;
  
    return 0;
}