#include <iostream>
#include <cmath>

// 특정 환경에서 M_PI가 정의되지 않았을 경우, 수동으로 정의를 활성화합니다.
// 이 코드는 M_PI가 <cmath>에 포함되도록 보장합니다.

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// 인라인 함수 정의
inline double degreesToRadians(double degrees) {
    return degrees * M_PI / 180.0;
}

inline double radiansToDegrees(double radians) {
    return radians * 180.0 / M_PI;
}

// 간단한 수학 연산 인라인 함수들
inline int max(int a, int b) {
    return (a > b) ? a : b;
}

inline int min(int a, int b) {
    return (a < b) ? a : b;
}

// 로봇 제어용 인라인 함수들
inline bool isValidAngle(double angle) {
    return (angle >= 0.0 && angle <= 360.0);
}

inline double constrainValue(double value, double minVal, double maxVal) {
    if (value < minVal) return minVal;
    if (value > maxVal) return maxVal;
    return value;
}

// PWM 값 계산 (0-255 범위)
inline int calculatePWM(double percentage) {
    return static_cast<int>(constrainValue(percentage * 2.55, 0, 255));
}

int main() {
    // 각도 변환
    double angle = 90.0;
    double radians = degreesToRadians(angle);
    std::cout << angle << "도 = " << radians << " 라디안" << std::endl;
    std::cout << radians << " 라디안 = " << radiansToDegrees(radians) << "도" << std::endl;

    // 센서 값 처리
    int sensor1 = 150, sensor2 = 200;
    std::cout << "센서값 최댓값: " << max(sensor1, sensor2) << std::endl;
    std::cout << "센서값 최솟값: " << min(sensor1, sensor2) << std::endl;

    // 각도 유효성 검사
    double testAngle = 270.0;
    std::cout << testAngle << "도는 " << (isValidAngle(testAngle) ? "유효" : "무효") << "한 각도입니다." << std::endl;

    // 값 제한
    double speed = 120.0; // 100%를 초과하는 속도
    double limitedSpeed = constrainValue(speed, 0.0, 100.0);
    std::cout << "원래 속도: " << speed << "% → 제한된 속도: " << limitedSpeed << "%" << std::endl;

    // PWM 계산
    double motorPower = 75.0; // 75%
    int pwmValue = calculatePWM(motorPower);
    std::cout << "모터 출력 " << motorPower << "% = PWM " << pwmValue << std::endl;

    return 0;
}
