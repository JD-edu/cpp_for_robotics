#include <WiFi.h>
#include <WiFiUdp.h>

const char* ssid = "SK_WiFiGIGA73BA_2.4G";
const char* password = "1609043407";

WiFiUDP udp;
const int udpPort = 9999;
char udpBuffer[256];

// 모터 핀 (L298N 드라이버 사용 가정)
const int MOTOR_LEFT_PWM = 12;
const int MOTOR_LEFT_DIR = 14;
const int MOTOR_RIGHT_PWM = 13;
const int MOTOR_RIGHT_DIR = 27;

// 센서 핀
const int ULTRASONIC_TRIG = 5;
const int ULTRASONIC_ECHO = 18;

int leftSpeed = 0, rightSpeed = 0;
unsigned long lastCommand = 0;

void setup() {
  Serial.begin(115200);
  
  pinMode(MOTOR_LEFT_PWM, OUTPUT);
  pinMode(MOTOR_LEFT_DIR, OUTPUT);
  pinMode(MOTOR_RIGHT_PWM, OUTPUT);
  pinMode(MOTOR_RIGHT_DIR, OUTPUT);
  pinMode(ULTRASONIC_TRIG, OUTPUT);
  pinMode(ULTRASONIC_ECHO, INPUT);
  
  // Wi-Fi 연결
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n로봇 준비 완료!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
  
  udp.begin(udpPort);
  Serial.printf("UDP 포트: %d\n", udpPort);
}

void loop() {
  handleCommands();
  checkSafety();
  delay(10);
}

void handleCommands() {
  int packetSize = udp.parsePacket();
  if (!packetSize) return;
  
  int length = udp.read(udpBuffer, sizeof(udpBuffer) - 1);
  udpBuffer[length] = '\0';
  String cmd = String(udpBuffer);
  cmd.trim();
  
  Serial.println("수신: " + cmd);
  String response = processCommand(cmd);
  
  // 응답 전송
  udp.beginPacket(udp.remoteIP(), udp.remotePort());
  udp.print(response);
  udp.endPacket();
  
  lastCommand = millis();
}

String processCommand(String cmd) {
  if (cmd == "FORWARD") {
    setMotors(200, 200);
    return "OK:FORWARD";
  } 
  else if (cmd == "BACKWARD") {
    setMotors(-200, -200);
    return "OK:BACKWARD";
  }
  else if (cmd == "LEFT") {
    setMotors(0, 200);
    return "OK:LEFT";
  }
  else if (cmd == "RIGHT") {
    setMotors(200, 0);
    return "OK:RIGHT";
  }
  else if (cmd == "STOP") {
    setMotors(0, 0);
    return "OK:STOP";
  }
  else if (cmd == "STATUS") {
    float distance = getDistance();
    return "DIST:" + String(distance, 1) + 
           ",L:" + String(leftSpeed) + 
           ",R:" + String(rightSpeed);
  }
  else {
    return "ERROR:UNKNOWN";
  }
}

void setMotors(int left, int right) {
  leftSpeed = constrain(left, -255, 255);
  rightSpeed = constrain(right, -255, 255);
  
  // 왼쪽 모터
  digitalWrite(MOTOR_LEFT_DIR, leftSpeed >= 0 ? HIGH : LOW);
  analogWrite(MOTOR_LEFT_PWM, abs(leftSpeed));
  
  // 오른쪽 모터
  digitalWrite(MOTOR_RIGHT_DIR, rightSpeed >= 0 ? HIGH : LOW);
  analogWrite(MOTOR_RIGHT_PWM, abs(rightSpeed));
  
  Serial.printf("모터: L=%d, R=%d\n", leftSpeed, rightSpeed);
}

float getDistance() {
  digitalWrite(ULTRASONIC_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(ULTRASONIC_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(ULTRASONIC_TRIG, LOW);
  
  long duration = pulseIn(ULTRASONIC_ECHO, HIGH, 30000);
  return (duration * 0.034) / 2;  // cm
}

void checkSafety() {
  // 2초간 명령 없으면 안전 정지
  if (millis() - lastCommand > 2000) {
    if (leftSpeed != 0 || rightSpeed != 0) {
      Serial.println("안전 정지!");
      setMotors(0, 0);
    }
  }
}