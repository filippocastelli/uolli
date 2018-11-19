#include <Servo.h>
#include "conf.h"
Servo servo;


void setup() {
  initmotors();
  initultrasonic();
  initbuzzer();
  initirsensors();

  Serial.begin(9600);
}

void loop() {
  uart_comm();
  guida();
}



