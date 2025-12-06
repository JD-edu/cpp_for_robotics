const byte HEADER = 0xAA;
const byte PACKET_SIZE = 0x06;

struct DataPacket {
    byte header;
    byte size;
    byte data[4];
    byte checksum;
};

bool receivePacket(DataPacket& packet) {
    if (Serial.available() < 7) return false;
  
    // 헤더 찾기
    while (Serial.available() > 0) {
        byte b = Serial.read();
        if (b == HEADER) {
            packet.header = b;
            break;
        }
    }
  
    if (Serial.available() < 6) return false;
  
    packet.size = Serial.read();
    if (packet.size != PACKET_SIZE) return false;
  
    // 데이터 읽기
    for (int i = 0; i < 4; i++) {
        packet.data[i] = Serial.read();
    }
  
    packet.checksum = Serial.read();
  
    // 체크섬 검증
    byte calculated = packet.data[0] ^ packet.data[1] ^ 
                     packet.data[2] ^ packet.data[3];
  
    return (calculated == packet.checksum);
}

int32_t bytesToInt(byte* bytes) {
    return ((int32_t)bytes[0] << 24) | ((int32_t)bytes[1] << 16) | 
           ((int32_t)bytes[2] << 8) | (int32_t)bytes[3];
}

void setup() {
    Serial.begin(115200);
    Serial.println("Arduino ready to receive data");
    pinMode(13, OUTPUT);
}

void loop() {
    DataPacket packet;
  
    if (receivePacket(packet)) {
        int32_t value = bytesToInt(packet.data);
        Serial.print("Received integer: ");
        Serial.println(value);
      
        // 받은 값에 따른 동작 수행
        if (value > 0) {
            digitalWrite(13, HIGH);  // LED 켜기
        } else {
            digitalWrite(13, LOW);   // LED 끄기
        }
    }
}
