// Arduino Serial Sender
// 이 코드를 Arduino IDE에서 컴파일하여 아두이노 보드에 업로드하세요.

// 전송할 보드레이트는 C++ 코드의 BAUD_RATE와 일치해야 합니다.
const long BAUD_RATE = 115200;

void setup() {
  // 시리얼 통신을 설정합니다.
  Serial.begin(BAUD_RATE);
  Serial.println("Arduino Serial Sender Initialized.");
}

void loop() {
  // 1초(1000ms)마다 메시지를 보냅니다.
  // Serial.println()은 메시지 끝에 캐리지 리턴(\r)과 개행 문자(\n)를 자동으로 추가합니다.
  static int counter = 0;
  
  Serial.print("Hello from Arduino, Count: ");
  Serial.println(counter);
  
  counter++;

  // 다음 메시지 전송까지 대기합니다.
  delay(1000); 
}