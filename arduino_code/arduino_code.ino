#include <Servo.h>
#include <IRremote.h>
#include "conf.h"
Servo servo;


void setup() {
  initleds();
  initbuzzer();
  initmotors();
  initultrasonic();
  initirguide();
  initirsensors();

  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop() {
  receive_commands();
  button_tic();
  //serialcopy();
  guida();
  
}
