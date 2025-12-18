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


// ========== 객체 생성 - 핵심! ==========
// 클래스는 설계도, 아래는 설계도로부터 만든 실제 모터 4개
//Motor leftFront(9, 3, 4);    // 좌측 전방 모터 (핀 9, 3, 4 사용) 테스트 못함 아두이노 PWM 핀 설정할 것  
Motor rightFront(5, 6, 7);   // 우측 전방 모터 (핀 5, 6, 7 사용) 테스트 했음 동작 양호 
//Motor leftRear(8, 9, 10);    // 좌측 후방 모터 (핀 8, 9, 10 사용) 테스트 못함 아두이노 PWM 핀 설정할 것  
//Motor rightRear(11, 12, 13); // 우측 후방 모터 (핀 11, 12, 13 사용)  테스트 못함 아두이노 PWM 핀 설정할 것  
// 각 객체는 독립적인 핀 번호를 가지며, 서로 영향을 주지 않음!

void setup() {
  // 각 모터 초기화
  //leftFront.init();
  rightFront.init();
  //leftRear.init();
  //rightRear.init();
  
  Serial.begin(9600);
  pinMode(10, OUTPUT);
  digitalWrite(10, HIGH);
}

void loop() {
  // 전진
  robotForward(200);
  delay(1000);
  
  // 정지
  robotStop();
  delay(1000);
  
  // 좌회전
  robotTurnLeft(150);
  delay(1000);
  
  // 정지
  robotStop();
  delay(1000);
}

// 로봇 전진 함수
void robotForward(int speed) {
  //leftFront.forward(speed);
  rightFront.forward(speed);
  //leftRear.forward(speed);
  //rightRear.forward(speed);
}

// 로봇 후진 함수
void robotBackward(int speed) {
  //leftFront.backward(speed);
  rightFront.backward(speed);
  //leftRear.backward(speed);
  //rightRear.backward(speed);
}

// 로봇 좌회전 함수 (제자리 회전)
void robotTurnLeft(int speed) {
  //leftFront.backward(speed);   // 좌측 모터 후진
  rightFront.forward(speed);   // 우측 모터 전진
  //leftRear.backward(speed);
  //rightRear.forward(speed);
}

// 로봇 우회전 함수
void robotTurnRight(int speed) {
  //leftFront.forward(speed);    // 좌측 모터 전진
  rightFront.backward(speed);  // 우측 모터 후진
  //leftRear.forward(speed);
  //rightRear.backward(speed);
}

// 로봇 정지 함수
void robotStop() {
  //leftFront.stop();
  rightFront.stop();
  //leftRear.stop();
  //rightRear.stop();
}