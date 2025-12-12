// robot_math.cpp
#include "robot_math.h"
#include <cmath>

double degreeToRadian(double degree) {
    return degree * M_PI / 180.0;
}

double radianToDegree(double radian) {
    return radian * 180.0 / M_PI;
}

double calculateDistance(double x1, double y1, double x2, double y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}