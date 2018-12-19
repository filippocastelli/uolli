// -- buzzer --

void buzz_ON()   //open buzzer
{
  digitalWrite(buzzpin, LOW);
}
void buzz_OFF()  //close buzzer
{
  digitalWrite(buzzpin, HIGH);
}

void alarm(){
//   buzz_ON();
//   delay(100);
//   buzz_OFF();
  ticnote();
  ticnote();
}

void ticnote() {
  buzz_ON();
  delay(50);
  buzz_OFF();
  delay(50);
}

void oksound(){
  ticnote();
  ticnote();
  ticnote();
}

void obstaclesound(){
  ticnote();
  ticnote();
}

void initbuzzer(){
  pinMode(buzzpin, OUTPUT);
  buzz_OFF();
  //alarm();
  oksound();
}
