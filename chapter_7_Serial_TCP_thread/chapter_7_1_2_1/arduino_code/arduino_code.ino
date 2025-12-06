void setup() {
  Serial.begin(115200);  // 시리얼 통신 초기화
}

void loop() {
  Serial.println("Hello from Arduino!");  // 문자열 전송
  delay(1000);  // 1초 대기
}
