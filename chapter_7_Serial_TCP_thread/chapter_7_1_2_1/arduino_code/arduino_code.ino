void setup() {
  Serial.begin(115200); 
}

int count = 0;
void loop() {
  Serial.print("Hello from Arduino!");  
  Serial.println(count++);
  delay(50);  // to test thoughput, reduceing delay time  
}
