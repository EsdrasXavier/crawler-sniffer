#include <Arduino.h>
#include <Servo.h>
#include <ServoMotor.h>
#include <BluetoothPin.h>
#include <SoftwareSerial.h>
#include <DualVNH5019MotorShield.h>
#include "constants.h"

DualVNH5019MotorShield *motorFront = new DualVNH5019MotorShield();
DualVNH5019MotorShield *motorBack = new DualVNH5019MotorShield();
SoftwareSerial *bluetooth = new SoftwareSerial(RX, TX);
Servo servo;

void initializeRobot();
void parseCommand();
void setup() {
  initializeRobot();
}

void loop() {
  if (Serial3.available() > 0) {
    parseCommand();
  }
}

void parseCommand() {
  byte cmd = Serial3.read();
  // Serial.println("Comando: " + String(cmd));

  if (cmd == MOTOR_CONTROL) { // Aqui serão lidos 4 bytes
    uint8_t buffer[4];
    uint8_t int_size = sizeof(int);
    int left=0, right=0;

    Serial3.readBytes(buffer, 4);

    for (int i = 0; i < int_size * 2; i++) {
      if (i < int_size) {
        left = (buffer[i] << (8 * i)) | left;
      } else {
        int j = i - int_size;
        right = (buffer[i] << (8 * j)) | right;
      }
    }

    motorFront->setSpeeds(left, right);
    motorBack->setSpeeds(left, right);
    // Serial.println("Velocidades ==> " + String(left) + " -=- " + String(right));
  }
}

void initializeRobot() {
  motorFront->setPorts(M1F_INA, M1F_INB, M1F_EN, M1F_CS, M1F_PWM, M2F_INA, M2F_INB, M2F_EN, M2F_CS, M2F_PWM);
  motorBack->setPorts(M1T_INA, M1T_INB, M1T_EN, M1T_CS, M1T_PWM, M2T_INA, M2T_INB, M2T_EN, M2T_CS, M2T_PWM);

  motorFront->init();
  motorBack->init();

  motorFront->setSpeeds(0, 0);
  motorBack->setSpeeds(0, 0);

  Serial3.begin(9600);
  Serial.begin(9600);
}