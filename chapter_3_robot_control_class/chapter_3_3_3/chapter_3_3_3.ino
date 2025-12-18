// TB6612FNG를 이용한 DC 모터 제어
// 모터 A 연결 핀
const int MOTOR_A_IN1 = 7;    // AIN1
const int MOTOR_A_IN2 = 8;    // AIN2  
const int MOTOR_A_PWM = 5;    // PWMA (PWM 핀 필수)

// Standby 핀 (공통)
const int STBY = 10;          // STBY 핀

void setup() {
  // 모터 제어 핀을 출력으로 설정
  pinMode(MOTOR_A_IN1, OUTPUT);
  pinMode(MOTOR_A_IN2, OUTPUT);
  pinMode(MOTOR_A_PWM, OUTPUT);
  pinMode(STBY, OUTPUT);
  
  // TB6612FNG 활성화 (STBY를 HIGH로)
  digitalWrite(STBY, HIGH);
  
  Serial.begin(9600);
  Serial.println("TB6612FNG 모터 드라이버 초기화 완료");
}

void loop() {
  // 전진
  motorForward(200);    // 속도 200 (0-255)
  delay(2000);
  
  // 부드러운 정지 (Coast)
  motorCoast();
  delay(1000);
  
  // 후진
  motorBackward(150);   // 속도 150
  delay(2000);
  
  // 급정지 (Brake)
  motorBrake();
  delay(1000);
  
  // 저전력 모드
  motorStandby();
  delay(2000);
  
  // 다시 활성화
  digitalWrite(STBY, HIGH);
  delay(100);
}

// 모터 전진 함수
void motorForward(int speed) {
  digitalWrite(MOTOR_A_IN1, HIGH);
  digitalWrite(MOTOR_A_IN2, LOW);
  analogWrite(MOTOR_A_PWM, speed);  // PWM으로 속도 제어
  Serial.print("모터 전진 - 속도: ");
  Serial.println(speed);
}

// 모터 후진 함수
void motorBackward(int speed) {
  digitalWrite(MOTOR_A_IN1, LOW);
  digitalWrite(MOTOR_A_IN2, HIGH);
  analogWrite(MOTOR_A_PWM, speed);
  Serial.print("모터 후진 - 속도: ");
  Serial.println(speed);
}

// 모터 관성 정지 (Coast) - 천천히 멈춤
void motorCoast() {
  digitalWrite(MOTOR_A_IN1, LOW);
  digitalWrite(MOTOR_A_IN2, LOW);
  analogWrite(MOTOR_A_PWM, 0);
  Serial.println("모터 관성 정지");
}

// 모터 브레이크 (Brake) - 빠르게 정지
void motorBrake() {
  digitalWrite(MOTOR_A_IN1, HIGH);
  digitalWrite(MOTOR_A_IN2, HIGH);
  analogWrite(MOTOR_A_PWM, 255);  // 브레이크는 최대 PWM
  Serial.println("모터 급정지 (브레이크)");
}

// 저전력 모드 (Standby)
void motorStandby() {
  digitalWrite(STBY, LOW);
  Serial.println("모터 드라이버 저전력 모드");
}

// 정상 동작 모드 복귀
void motorWakeup() {
  digitalWrite(STBY, HIGH);
  delay(1);  // 안정화 대기
  Serial.println("모터 드라이버 활성화");
}