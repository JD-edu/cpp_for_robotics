// Arduino 코드 (arduino_sensor.ino)
int sensorValue = 0;
float temperature = 25.0;

void setup() {
  Serial.begin(115200);
  randomSeed(analogRead(0));
}

void loop() {
  // 센서 값 시뮬레이션 (랜덤 값)
  sensorValue = random(0, 1024);
  temperature = 20.0 + random(0, 100) / 10.0;
  
  // 텍스트 형태로 전송
  Serial.print("Distance: ");
  Serial.print(sensorValue);
  Serial.print(" mm, Temp: ");
  Serial.print(temperature);
  Serial.println(" C");
  
  delay(500);  // 0.5초 주기로 전송
}
