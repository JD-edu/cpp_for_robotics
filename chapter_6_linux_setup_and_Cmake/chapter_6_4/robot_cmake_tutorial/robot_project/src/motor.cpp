// src/motor.cpp
#include "motor.h"
#include <iostream>

Motor::Motor() : speed(0), running(false) {
}

void Motor::setSpeed(int s) {
    speed = s;
    std::cout << "Motor speed set to: " << speed << std::endl;
}

void Motor::start() {
    running = true;
    std::cout << "Motor started" << std::endl;
}

void Motor::stop() {
    running = false;
    speed = 0;
    std::cout << "Motor stopped" << std::endl;
}

bool Motor::isRunning() const {
    return running;
}

int Motor::getSpeed() const {
    return speed;
}