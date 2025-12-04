#include <iostream>
using namespace std;

int main() {
    // 예: 로봇이 작동한 총 시간 (초 단위)
    int totalSeconds = 3665;  // 1시간 1분 5초

    // 시간, 분, 초 계산
    int hours = totalSeconds / 3600;        // 3600초 = 1시간
    int minutes = (totalSeconds % 3600) / 60;  // 남은 초에서 분 계산
    int seconds = totalSeconds % 60;        // 60으로 나눈 나머지 = 초

    cout << totalSeconds << "초는 ";
    cout << hours << "시간 ";
    cout << minutes << "분 ";
    cout << seconds << "초입니다." << endl;

    // 출력: 3665초는 1시간 1분 5초입니다.

    // 요일 계산 예시
    int days = 10;  // 10일이 지남
    int dayOfWeek = days % 7;  // 0~6 사이의 값 (일주일은 7일)
    cout << days << "일 후는 " << dayOfWeek << "번째 요일입니다." << endl;

    // 짝수/홀수 판별
    int number = 17;
    if (number % 2 == 0) {
        cout << number << "는 짝수입니다." << endl;
    } else {
        cout << number << "는 홀수입니다." << endl;
    }

    return 0;
}
