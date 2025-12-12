// 라이브러리 사용 예제
// main.cpp
#include <iostream>
#include "robot_math.h"

int main() {
    double angle = 45.0;
    std::cout << angle << " degrees = " << degreeToRadian(angle) << " radians" << std::endl;
    return 0;
}