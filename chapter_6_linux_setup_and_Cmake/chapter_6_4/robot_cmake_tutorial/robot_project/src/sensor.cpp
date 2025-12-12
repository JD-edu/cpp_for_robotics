// src/sensor.cpp
#include "sensor.h"
#include <iostream>

Sensor::Sensor(const std::string& sensor_name) 
    : name(sensor_name), value(0) {
}

void Sensor::updateValue(int new_value) {
    value = new_value;
}

int Sensor::getValue() const {
    return value;
}

void Sensor::displayInfo() const {
    std::cout << "Sensor [" << name << "]: " << value << std::endl;
}