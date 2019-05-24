#pragma once

#include <Arduino.h>
#include <MotorPin.h>

#ifndef MOTOR_H
#define MOTOR_H

#define STOPED 0
#define FOWARD 1
#define BACKWARD 2

class Motor {
private:
  int pwm = 0;
  int ina = 0;
  int inb = 0;
  int gnd = 0;
  int v5 = 0;

public:
  Motor(int pwm, int ina, int inb, int gnd, int v5);
  void setDirection(int d);
  void setSpeed(int s);
  void init();
};

#endif