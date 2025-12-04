// LED를 이용한 GPIO 제어 예제
const int LED_PIN = 13;    // 출력 핀

void setup() {
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
    digitalWrite(LED_PIN, HIGH);  // LED 켜기
    delay(1000);
    digitalWrite(LED_PIN, LOW);   // LED 끄기
    delay(1000);
}