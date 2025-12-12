// include/motor.h
#ifndef MOTOR_H
#define MOTOR_H

class Motor {
private:
    int speed;
    bool running;
  
public:
    Motor();
    void setSpeed(int s);
    void start();
    void stop();
    bool isRunning() const;
    int getSpeed() const;
};

#endif