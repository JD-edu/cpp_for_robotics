#pragma once
#include <fstream>
#include <iostream>
#include <string>

class RobotConfig {
public:
    void saveConfig(const std::string& filename) {
        std::ofstream outFile(filename);
        if (outFile.is_open()) {
            outFile << "max_speed=" << maxSpeed << std::endl;
            outFile.close();
        }
    }

    bool loadConfig(const std::string& filename) {
        std::ifstream inFile(filename);
        if (!inFile.is_open()) return false;

        std::string line;
        while (std::getline(inFile, line)) {
            size_t pos = line.find('=');
            if (pos != std::string::npos) {
                maxSpeed = std::stod(line.substr(pos + 1));
            }
        }
        inFile.close();
        return true;
    }

    void printConfig() const {
        std::cout << "최대 속도: " << maxSpeed << " m/s" << std::endl;
    }

    void setMaxSpeed(double speed) { maxSpeed = speed; }

private:
    double maxSpeed = 1.0;  // 기본값
};
