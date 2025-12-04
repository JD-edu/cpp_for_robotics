// millis()를 이용한 논블로킹 방식 (권장)
unsigned long previousTime = 0;
const long interval = 1000;  // 1초

const int LED_PIN = 13;
void setup(){
	pinMode(LED_PIN, OUTPUT);
}
void loop() {
  unsigned long currentTime = millis();
  if (currentTime - previousTime >= interval) {
    previousTime = currentTime;
    // 1초마다 실행할 코드
    digitalWrite(LED_PIN, !digitalRead(LED_PIN));  // LED 토글
  }
  // 대기 시간 동안 다른 작업 가능
}