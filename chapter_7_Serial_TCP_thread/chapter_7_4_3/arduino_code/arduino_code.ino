#include <WiFi.h>

const char* ssid = "SK_WiFiGIGA73BA_2.4G";
const char* password = "1609043407";

WiFiServer server(8080);
WiFiClient client;

void setup() {
  Serial.begin(115200);
  
  // Wi-Fi 연결
  WiFi.begin(ssid, password);
  Serial.print("Wi-Fi 연결 중");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println();
  Serial.println("Wi-Fi 연결 완료!");
  Serial.print("IP 주소: ");
  Serial.println(WiFi.localIP());
  
  // TCP 서버 시작
  server.begin();
  Serial.println("TCP 서버가 포트 8080에서 시작되었습니다.");
}

void loop() {
  // 클라이언트 연결 확인
  WiFiClient newClient = server.available();
  
  if (newClient) {
    if (!client || !client.connected()) {
      client = newClient;
      Serial.println("새 클라이언트 연결됨");
      client.println("ESP32 TCP 서버에 연결되었습니다.");
    }
  }
  
  // 클라이언트로부터 데이터 수신
  if (client && client.connected() && client.available()) {
    String receivedData = client.readStringUntil('\n');
    receivedData.trim();
  
    Serial.println("수신된 데이터: " + receivedData);
  
    // 에코 응답 전송
    client.println("에코: " + receivedData);
  
    // 특정 명령 처리
    if (receivedData == "LED_ON") {
      digitalWrite(2, HIGH);  // 내장 LED 켜기
      client.println("LED가 켜졌습니다.");
    } else if (receivedData == "LED_OFF") {
      digitalWrite(2, LOW);   // 내장 LED 끄기
      client.println("LED가 꺼졌습니다.");
    } else if (receivedData == "STATUS") {
      client.println("시스템 상태: 정상");
      client.println("업타임: " + String(millis()) + "ms");
    }
  }
  
  delay(10);
}