#pragma once
#include <iostream>
#include <string>

// 로보틱스 최상위 네임스페이스
namespace Robotics {

    // 센서 네임스페이스
    namespace Sensors {
        class TemperatureSensor {
        private:
            std::string name;
            double value;
        public:
            TemperatureSensor(const std::string& n) : name(n), value(25.0) {}
            double read() { return value = 20 + (rand() % 10); }
            std::string getName() const { return name; }
        };
    }

    // 모터 네임스페이스
    namespace Actuators {
        class Motor {
        private:
            std::string name;
            bool running;
        public:
            Motor(const std::string& n) : name(n), running(false) {}
            void start() {
                running = true;
                std::cout << "모터 '" << name << "' 시작" << std::endl;
            }
            void stop() {
                running = false;
                std::cout << "모터 '" << name << "' 정지" << std::endl;
            }
        };
    }

    // 위치 네임스페이스
    namespace Navigation {
        struct Position {
            double x, y;
            Position(double x = 0, double y = 0) : x(x), y(y) {}
            void print() const {
                std::cout << "위치: (" << x << ", " << y << ")" << std::endl;
            }
        };
    }

}  // namespace Robotics 끝

// 네임스페이스 별칭
namespace RS = Robotics::Sensors;
namespace RA = Robotics::Actuators;
namespace RN = Robotics::Navigation;