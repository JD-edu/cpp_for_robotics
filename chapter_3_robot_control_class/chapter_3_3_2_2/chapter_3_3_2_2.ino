// 시리얼 통신을 이용한 센서 데이터 출력
void setup() {
  Serial.begin(115200);  // 시리얼 통신 초기화 (9600 bps)
  Serial.println("아두이노 시리얼 통신 시작");
}

void loop() {
  int sensorValue = analogRead(A0);  // 아날로그 입력 읽기
  
  // 시리얼 모니터에 데이터 출력
  Serial.print("센서 값: ");
  Serial.println(sensorValue);
  
  delay(500);  // 0.5초 간격으로 출력
}