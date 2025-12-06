const byte HEADER = 0xAA;
const byte PACKET_SIZE = 0x06;  // 데이터 4바이트 + 체크섬 1바이트

void sendIntegerData(int32_t value) {
    byte packet[7];
  
    packet[0] = HEADER;
    packet[1] = PACKET_SIZE;
    packet[2] = (value >> 24) & 0xFF;  // 상위 바이트
    packet[3] = (value >> 16) & 0xFF;
    packet[4] = (value >> 8) & 0xFF;
    packet[5] = value & 0xFF;         // 하위 바이트
  
    // 체크섬 계산 (헤더와 패킷 크기 제외한 데이터의 XOR)
    byte checksum = packet[2] ^ packet[3] ^ packet[4] ^ packet[5];
    packet[6] = checksum;
  
    // 패킷 전송
    Serial.write(packet, 7);
}

void setup() {
    Serial.begin(115200);
    while (!Serial) {
        ; // 시리얼 포트 연결 대기
    }
}

void loop() {
    static int32_t counter = 0;
  
    sendIntegerData(counter);
    counter += 100;
  
    if (counter > 10000) counter = 0;
  
    delay(1000);  // 1초마다 전송
}