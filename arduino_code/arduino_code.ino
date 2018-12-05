#include <Servo.h>
#include <IRremote.h>
#include "conf.h"
Servo servo;


void setup() {
  initbuzzer();
  initmotors();
  initultrasonic();

  initirsensors();

  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop() {
  uart_comm();
  //serialcopy();
  guida();
}
