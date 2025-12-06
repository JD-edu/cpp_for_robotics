#define LED_PIN 13
#define SENSOR_PIN A0

void setup() {
    Serial.begin(9600);
    pinMode(LED_PIN, OUTPUT);
    Serial.println("Arduino Ready");
}

void loop() {
    // PC로부터 명령 수신
    if (Serial.available()) {
        String command = Serial.readStringUntil('\n');
        command.trim();

        if (command == "LED_ON") {
            digitalWrite(LED_PIN, HIGH);
            Serial.println("ACK:LED_ON");
        } 
        else if (command == "LED_OFF") {
            digitalWrite(LED_PIN, LOW);
            Serial.println("ACK:LED_OFF");
        }
        else if (command == "GET_SENSOR") {
            int sensorValue = analogRead(SENSOR_PIN);
            Serial.print("SENSOR:");
            Serial.println(sensorValue);
        }
    }

    // 주기적으로 센서 데이터 전송 (5초마다)
    static unsigned long lastSend = 0;
    if (millis() - lastSend > 5000) {
        int sensorValue = analogRead(SENSOR_PIN);
        Serial.print("DATA:");
        Serial.println(sensorValue);
        lastSend = millis();
    }
}