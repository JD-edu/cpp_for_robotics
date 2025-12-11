#include <Wire.h>
#include <U8g2lib.h>
#include <VL53L0X.h>

// I2C 디바이스 객체 생성
// U8G2_SSD1306_128X64_NONAME_F_HW_I2C: 
//   - SSD1306: 컨트롤러 칩 종류
//   - 128X64: 해상도
//   - NONAME: 제조사 미지정 (일반형)
//   - F: Full buffer mode (전체 화면 버퍼 사용)
//   - HW_I2C: 하드웨어 I2C 사용
U8G2_SSD1306_128X64_NONAME_F_HW_I2C oled(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
// U8G2_R0: 회전 없음 (R1=90도, R2=180도, R3=270도)
// U8X8_PIN_NONE: 리셋 핀 사용 안 함

VL53L0X distanceSensor;  // 거리센서 객체

void setup() {
  Serial.begin(9600);
  Wire.begin();  // I2C 통신 초기화
  
  // OLED 초기화
  oled.begin();
  oled.clearBuffer();  // 내부 버퍼 초기화
  
  // 시작 메시지 표시
  oled.setFont(u8g2_font_ncenB08_tr);  // 폰트 설정
  oled.drawStr(0, 15, "Robot Control");  // (x, y, 문자열)
  oled.drawStr(0, 30, "Initializing...");
  oled.sendBuffer();  // 버퍼 내용을 화면에 출력
  
  delay(1000);
  
  // 거리센서 초기화
  if (!distanceSensor.init()) {
    oled.clearBuffer();
    oled.drawStr(0, 15, "Sensor Error!");
    oled.drawStr(0, 30, "Check Wiring");
    oled.sendBuffer();
    Serial.println("VL53L0X 초기화 실패!");
    while(1);
  }
  
  distanceSensor.startContinuous();
  Serial.println("시스템 초기화 완료");
}

void loop() {
  // 거리 측정
  int distance = distanceSensor.readRangeContinuousMillimeters();
  
  // OLED에 그래픽으로 표시
  oled.clearBuffer();  // 화면 지우기 (버퍼 초기화)
  
  // 제목 표시 (작은 폰트)
  oled.setFont(u8g2_font_ncenB08_tr);  // 8px 볼드 폰트
  oled.drawStr(0, 10, "Distance Sensor");
  
  // 거리 값 표시 (큰 폰트)
  oled.setFont(u8g2_font_ncenB14_tr);  // 14px 볼드 폰트
  char distanceStr[20];
  sprintf(distanceStr, "%d mm", distance);  // 문자열 포맷팅
  oled.drawStr(0, 35, distanceStr);
  
  // 상태 바 그리기 (거리에 따라 길이 변화)
  int barLength = map(distance, 0, 2000, 0, 128);  // 0~2000mm를 0~128px로 변환
  if (barLength > 128) barLength = 128;  // 최대값 제한
  oled.drawFrame(0, 45, 128, 10);  // 외곽선 그리기
  oled.drawBox(2, 47, barLength - 4, 6);  // 채워진 박스 그리기
  
  // 경고 메시지 (가까운 거리)
  if (distance < 200) {
    oled.setFont(u8g2_font_ncenB08_tr);
    oled.drawStr(0, 64, "WARNING: Too Close!");
  }
  
  oled.sendBuffer();  // 버퍼의 모든 내용을 OLED에 전송
  
  // 시리얼 모니터 출력
  Serial.print("측정 거리: ");
  Serial.print(distance);
  Serial.println(" mm");
  
  delay(100);  // 0.1초 간격 업데이트
}