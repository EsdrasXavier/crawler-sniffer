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
  int index = 0;
  int int_size = sizeof(int);

  char buffer[10];
  byte cmd = bluetooth->read();

  Serial.println("Comando: " + String(cmd));

  if (cmd == MOTOR_CONTROL) { // Aqui serão lidos 4 bytes

    for (int i = 0; i < int_size * 2; i++) {
      char a = bluetooth->read();
      buffer[index++] = a;
      delayMicroseconds(100);
    }

    int left=0, right=0;
    for (int i = 0; i < int_size * 2; i++) {
      if (i < int_size) {
        left = (buffer[i] << (8 * i)) | left;
      } else {
        int j = i - int_size;
        right = (buffer[i] << (8 * j)) | right;
      }
    }

    Serial.println("Velocidades ==> " + String(left) + " -=- " + String(right));

    for (int i = 0; i < 4; i++) {
      Serial.println(buffer[i], DEC);
    }
  }
}

void initializeRobot() {
  // motor->init();
  // servo.attach(SERVO_PIN);
  // servo.write(SERVO_STRAIT);
  bluetooth->begin(9600);
  Serial.begin(9600);
}