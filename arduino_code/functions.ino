void buzz_ON()   //open buzzer
{
  digitalWrite(buzzpin, LOW);
}
void buzz_OFF()  //close buzzer
{
  digitalWrite(buzzpin, HIGH);
}

void alarm(){
   buzz_ON();
   delay(100);
   buzz_OFF();
}



