#define LED_PIN 13
#define MOTOR_AIN1 7
#define MOTOR_AIN2 8
#define MOTOR_PWMA 9

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  pinMode(MOTOR_AIN1, OUTPUT);
  pinMode(MOTOR_AIN2, OUTPUT);
  pinMode(MOTOR_PWMA, OUTPUT);

  Serial.println("Arduino Ready");
}

void loop() {
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    command.trim();

    if (command == "LED_ON") {
      digitalWrite(LED_PIN, HIGH);
      Serial.println("LED ON");
    } 
    else if (command == "LED_OFF") {
      digitalWrite(LED_PIN, LOW);
      Serial.println("LED OFF");
    }
    else if (command == "MOTOR_FORWARD") {
      digitalWrite(MOTOR_AIN1, HIGH);
      digitalWrite(MOTOR_AIN2, LOW);
      analogWrite(MOTOR_PWMA, 200);  // 속도 200
      Serial.println("MOTOR FORWARD");
    }
    else if (command == "MOTOR_BACKWARD") {
      digitalWrite(MOTOR_AIN1, LOW);
      digitalWrite(MOTOR_AIN2, HIGH);
      analogWrite(MOTOR_PWMA, 200);
      Serial.println("MOTOR BACKWARD");
    }
    else if (command == "MOTOR_STOP") {
      digitalWrite(MOTOR_AIN1, LOW);
      digitalWrite(MOTOR_AIN2, LOW);
      analogWrite(MOTOR_PWMA, 0);
      Serial.println("MOTOR STOP");
    }
  }
}
