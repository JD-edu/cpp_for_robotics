#include <WiFi.h>
#include <WiFiUdp.h>

const char* ssid = "YourWiFiSSID";
const char* password = "YourWiFiPassword";

WiFiUDP udp;
const int udpPort = 8888;
char udpBuffer[512];

void setup() {
  Serial.begin(115200);
  pinMode(2, OUTPUT);  // 내장 LED
  
  // Wi-Fi 연결
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\nWi-Fi 연결 완료!");
  Serial.print("IP 주소: ");
  Serial.println(WiFi.localIP());
  
  // UDP 서버 시작
  udp.begin(udpPort);
  Serial.printf("UDP 서버 시작 - 포트: %d\n", udpPort);
}

void loop() {
  // UDP 패킷 수신 확인
  int packetSize = udp.parsePacket();
  
  if (packetSize) {
    // 패킷 데이터 읽기
    int length = udp.read(udpBuffer, sizeof(udpBuffer) - 1);
    udpBuffer[length] = '\0';
    String command = String(udpBuffer);
    command.trim();
  
    Serial.printf("UDP 수신 [%s:%d]: %s\n", 
                  udp.remoteIP().toString().c_str(), 
                  udp.remotePort(), 
                  command.c_str());
  
    // 명령 처리 및 응답
    String response = processCommand(command);
  
    // 응답 전송 (송신자에게 자동으로 전송)
    udp.beginPacket(udp.remoteIP(), udp.remotePort());
    udp.print(response);
    udp.endPacket();
  }
  
  delay(10);
}

String processCommand(const String& cmd) {
  if (cmd == "SENSOR") {
    // 센서 데이터를 간단한 형식으로 반환
    float temp = 25.0 + random(-50, 50) / 10.0;  // 시뮬레이션
    int distance = random(10, 200);
    return "TEMP:" + String(temp, 1) + ",DIST:" + String(distance);
  
  } else if (cmd == "LED_ON") {
    digitalWrite(2, HIGH);
    return "OK";
  
  } else if (cmd == "LED_OFF") {
    digitalWrite(2, LOW);
    return "OK";
  
  } else if (cmd == "PING") {
    return "PONG:" + String(millis());
  
  } else {
    return "ERROR:UNKNOWN";
  }
}