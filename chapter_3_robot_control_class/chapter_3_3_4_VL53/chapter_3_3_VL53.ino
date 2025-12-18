#include <Wire.h>
#include <VL53L0X.h>

VL53L0X sensor;  // 거리센서 객체 생성

void setup() {
  Serial.begin(9600);
  Wire.begin();    // I2C 통신 초기화

  // 센서 초기화
  if (!sensor.init()) {
    Serial.println("센서 초기화 실패!");
    while(1);
  }

  // 연속 측정 모드 시작
  sensor.startContinuous();
  Serial.println("거리 측정 시작");
}

void loop() {
  // 거리 측정 (mm 단위)
  int distance = sensor.readRangeContinuousMillimeters();

  Serial.print("거리: ");
  Serial.print(distance);
  Serial.println(" mm");

  // 장애물 감지 로직
  if (distance < 200) {  // 20cm 이내 장애물
    Serial.println("장애물 감지!");
  }

  delay(100);
}
