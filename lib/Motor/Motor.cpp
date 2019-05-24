#include <Motor.h>

Motor::Motor(int pwm, int ina, int inb, int gnd, int v5)
{
  this->pwm = pwm;
  this->ina = ina;
  this->inb = inb;
  this->gnd = gnd;
  this->v5 = v5;
}

void Motor::init() {
  pinMode(this->pwm, OUTPUT);
  pinMode(this->ina, OUTPUT);
  pinMode(this->inb, OUTPUT);
  pinMode(this->gnd, OUTPUT);
  pinMode(this->v5, OUTPUT);

  digitalWrite(this->gnd, LOW);
  digitalWrite(this->v5, HIGH);
  this->setSpeed(0);
}

void Motor::setDirection(int d) {
  if (d == FOWARD) {
    digitalWrite(this->ina, LOW);
    digitalWrite(this->inb, HIGH);
  } else if (d == BACKWARD) {
    digitalWrite(this->ina, HIGH);
    digitalWrite(this->inb, LOW);
  } else {
    digitalWrite(this->ina, LOW);
    digitalWrite(this->inb, LOW);
  }
}

void Motor::setSpeed(int s) {
  if (s < 0) {
    s = -s;
    this->setDirection(BACKWARD);
  } else {
    this->setDirection(FOWARD);
  }

  analogWrite(this->pwm, s);
}