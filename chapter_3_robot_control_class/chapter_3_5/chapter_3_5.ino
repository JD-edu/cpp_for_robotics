// Motor.h - 헤더 파일
class Motor {
private:
  // 멤버 변수 (private으로 외부에서 직접 접근 불가)
  int pin1;      // 모터 방향 제어 핀 1
  int pin2;      // 모터 방향 제어 핀 2
  int enablePin; // 모터 속도 제어 핀 (PWM)
  
public:
  // 생성자: 객체 생성 시 핀 번호 초기화
  Motor(int p1, int p2, int ena);
  
  // 멤버 함수들 (public으로 외부에서 호출 가능)
  void init();                    // 초기화
  void forward(int speed);        // 전진
  void backward(int speed);       // 후진
  void stop();                    // 정지
  void setSpeed(int speed);       // 속도 설정
};

// Motor.cpp - 구현 파일
// 생성자 구현
Motor::Motor(int p1, int p2, int ena) {
  pin1 = p1;
  pin2 = p2;
  enablePin = ena;
}

// 초기화 함수
void Motor::init() {
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(enablePin, OUTPUT);
}

// 전진 함수
void Motor::forward(int speed) {
  digitalWrite(pin1, HIGH);
  digitalWrite(pin2, LOW);
  analogWrite(enablePin, speed);
}

// 후진 함수
void Motor::backward(int speed) {
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, HIGH);
  analogWrite(enablePin, speed);
}

// 정지 함수
void Motor::stop() {
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, LOW);
  analogWrite(enablePin, 0);
}

// 속도 설정 함수
void Motor::setSpeed(int speed) {
  analogWrite(enablePin, speed);
}