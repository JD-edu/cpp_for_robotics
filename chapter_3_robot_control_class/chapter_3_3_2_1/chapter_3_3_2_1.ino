#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11);  // RX, TX 핀 지정

void setup() {
  mySerial.begin(9600);  // 소프트웨어 시리얼 시작
}

void loop() {
  if (mySerial.available()) {
    char c = mySerial.read();
    Serial.write(c);  // USB 시리얼로 전달
  }
}