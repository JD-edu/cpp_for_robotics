#include "Wire.h"
#include <MPU6050_light.h>

MPU6050 mpu(Wire);
long timer = 0;

int16_t virtualEncoder1 = 0;
int16_t virtualEncoder2 = 0;

// 데이터 구조: Header(2) + IMU(12) + Encoder(4) = 총 18바이트
byte dataBuffer[18]; 

void setup(){
  Serial.begin(115200);
  Wire.begin();

  byte status = mpu.begin();
  while(status != 0){
    delay(100);
    status = mpu.begin(); 
  }

  delay(1000);
  mpu.calcOffsets(true, true);
}

void loop() {
  if(millis() - timer > 50){ 
    mpu.update();
    
    int16_t accelX = (int16_t)(mpu.getAccX()*1000);
    int16_t accelY = (int16_t)(mpu.getAccY()*1000);
    int16_t accelZ = (int16_t)(mpu.getAccZ()*1000);
    int16_t gyroX = (int16_t)(mpu.getGyroX()*1000);
    int16_t gyroY = (int16_t)(mpu.getGyroY()*1000);
    int16_t gyroZ = (int16_t)(mpu.getGyroZ()*1000);

    virtualEncoder1++;
    virtualEncoder2++;

    // --- 패킷 조립 ---
    dataBuffer[0] = 0xF5; // Header 1
    dataBuffer[1] = 0xFA; // Header 2

    // IMU 데이터 (Big-Endian)
    dataBuffer[2] = (accelX >> 8) & 0xFF;
    dataBuffer[3] = accelX & 0xFF;
    dataBuffer[4] = (accelY >> 8) & 0xFF;
    dataBuffer[5] = accelY & 0xFF;
    dataBuffer[6] = (accelZ >> 8) & 0xFF;
    dataBuffer[7] = accelZ & 0xFF;
    dataBuffer[8] = (gyroX >> 8) & 0xFF;
    dataBuffer[9] = gyroX & 0xFF;
    dataBuffer[10] = (gyroY >> 8) & 0xFF;
    dataBuffer[11] = gyroY & 0xFF;
    dataBuffer[12] = (gyroZ >> 8) & 0xFF;
    dataBuffer[13] = gyroZ & 0xFF;
    
    // Encoder 데이터
    dataBuffer[14] = (virtualEncoder1 >> 8) & 0xFF;
    dataBuffer[15] = virtualEncoder1 & 0xFF;
    dataBuffer[16] = (virtualEncoder2 >> 8) & 0xFF;
    dataBuffer[17] = virtualEncoder2 & 0xFF;
    
    Serial.write(dataBuffer, 18); 
    timer = millis();
  }
}