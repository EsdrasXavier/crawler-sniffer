#include <Arduino.h>
#include <Motor.h>
#include <Servo.h>
#include <ServoMotor.h>
#include <BluetoothPin.h>
#include <SoftwareSerial.h>

Motor *motor = new Motor(PWM, INA, INB, GND, V5);
SoftwareSerial *bluetooth = new SoftwareSerial(RX, TX);
Servo servo;

void initializeRobot();
void bluetoothInterpreter();

void setup() {
  initializeRobot();
}

void loop() {
  bluetoothInterpreter();
}

void bluetoothInterpreter() {
  if (bluetooth->available() > 0) {
    int index = 0;
    byte buff[10];
    byte cmd = bluetooth->read();
    Serial.println("Comando: " + String(cmd));
    if (cmd == 10) {
      for (int i = 0; i < 2; i++) {
        buff[index++] = bluetooth->read();
      }

      int value = buff[0] + (buff[1] << 8);
      Serial.println("Valor: " + String(value));
    }

    buff[index] = 0;
  }
}

void initializeRobot() {
  motor->init();
  servo.attach(SERVO_PIN);
  servo.write(SERVO_STRAIT);
  bluetooth->begin(9600);
  Serial.begin(9600);
}