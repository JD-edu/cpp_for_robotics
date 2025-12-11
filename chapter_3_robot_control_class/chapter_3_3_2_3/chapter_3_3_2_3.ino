// 시리얼 모니터로 다양한 데이터 형식 확인
void setup() {
  Serial.begin(115200);
  
  // 시작 메시지
  Serial.println("=== 시리얼 통신 테스트 ===");
  Serial.println();
  
  // 정수 출력
  int value = 1023;
  Serial.print("10진수: ");
  Serial.println(value);           // 1023
  Serial.print("16진수: 0x");
  Serial.println(value, HEX);      // 3FF
  Serial.print("2진수: 0b");
  Serial.println(value, BIN);      // 1111111111
  
  // 실수 출력
  float voltage = 3.14159;
  Serial.print("전압(기본): ");
  Serial.println(voltage);         // 3.14
  Serial.print("전압(소수점 4자리): ");
  Serial.println(voltage, 4);      // 3.1416
  
  // 문자 출력
  char letter = 'A';
  Serial.print("문자: ");
  Serial.println(letter);          // A
  Serial.print("ASCII 코드: ");
  Serial.println((int)letter);     // 65
}

void loop() {
  // 센서 값을 읽어서 포맷팅하여 출력
  int sensorValue = analogRead(A0);
  
  // 방법 1: 간단한 출력
  Serial.print("센서: ");
  Serial.println(sensorValue);
  
  // 방법 2: 상세한 출력
  Serial.print("[");
  Serial.print(millis());        // 경과 시간
  Serial.print("ms] 센서 값: ");
  Serial.print(sensorValue);
  Serial.print(" (");
  Serial.print(sensorValue * 5.0 / 1023.0, 2);  // 전압으로 변환
  Serial.println("V)");
  
  delay(1000);
}