// include/sensor.h
#ifndef SENSOR_H
#define SENSOR_H

#include <string>

class Sensor {
private:
    std::string name;
    int value;
  
public:
    Sensor(const std::string& sensor_name);
    void updateValue(int new_value);
    int getValue() const;
    void displayInfo() const;
};

#endif