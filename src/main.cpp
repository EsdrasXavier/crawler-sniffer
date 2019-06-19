#include <Arduino.h>
#include <Motor.h>
#include <Servo.h>
#include <ServoMotor.h>
#include <BluetoothPin.h>
#include <SoftwareSerial.h>
#include "constants.h"

Motor *motor = new Motor(PWM, INA, INB, GND, V5);
SoftwareSerial *bluetooth = new SoftwareSerial(RX, TX);
Servo servo;

void initializeRobot();
void parseCommand();
void setup() {
  initializeRobot();
}

void loop() {
  if (bluetooth->available() > 0) {
    parseCommand();
  }
}

void parseCommand() {
  byte cmd = bluetooth->read();
  Serial.println("Comando: " + String(cmd));

  if (cmd == MOTOR_CONTROL) { // Aqui serão lidos 4 bytes
    uint8_t buffer[4];
    uint8_t int_size = sizeof(int);
    int left=0, right=0;

    bluetooth->readBytes(buffer, 4);

    for (int i = 0; i < int_size * 2; i++) {
      if (i < int_size) {
        left = (buffer[i] << (8 * i)) | left;
      } else {
        int j = i - int_size;
        right = (buffer[i] << (8 * j)) | right;
      }
    }

    Serial.println("Velocidades ==> " + String(left) + " -=- " + String(right));
  }
}

void initializeRobot() {
  // motor->init();
  // servo.attach(SERVO_PIN);
  // servo.write(SERVO_STRAIT);
  bluetooth->begin(9600);
  Serial.begin(9600);
}