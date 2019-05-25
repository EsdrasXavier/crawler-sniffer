#include <Arduino.h>
#include <Motor.h>
#include <Servo.h>
#include <ServoMotor.h>
#include <BluetoothPin.h>
#include <SoftwareSerial.h>

#define MAX_BUFFER 5

Motor *motor = new Motor(PWM, INA, INB, GND, V5);
SoftwareSerial *bluetooth = new SoftwareSerial(RX, TX);
Servo servo;
char cmd[20];

void initializeRobot();
void parseString(String code);

void setup() {
  initializeRobot();
}

void loop() {
  if (bluetooth->available() > 0) {
    String command = bluetooth->readStringUntil(';');
    if (tolower(command.charAt(0)) == 'd' || tolower(command.charAt(0)) == 's') {
      parseString(command);
    }
  }
}

void parseString(String code) {
  int i;
  int d;
  int v;
  for (i = 0; i < code.length(); i++) {
    if (code.charAt(i) == ' ')
      break;
  }

  d = code.substring(1, i).toInt();
  v = code.substring(i + 2).toInt();
  if (d < 0) {
    d = 180 + d;
  }
  d = constrain(d, 0, 180);
  v = constrain(v, 100, 255);
  motor->setSpeed(255);
  servo.write(d);
}

void initializeRobot() {
  motor->init();
  servo.attach(SERVO_PIN);
  servo.write(SERVO_STRAIT);
  bluetooth->begin(9600);
  Serial.begin(9600);
}