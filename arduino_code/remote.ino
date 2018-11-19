void uart_comm()
{

  char istruzioni=0;
  if(Serial.available()) 
  {
    size_t message_length = Serial.available();
    uint8_t serial_buffer[message_length + 1];
    serial_buffer[message_length] = 0x00;
    Serial.readBytes(serial_buffer, message_length);
    //parseUartPackage((char*)serial_buffer);
    memcpy(buffUART + buffUARTIndex, serial_buffer, message_length);
    buffUARTIndex += message_length;
    preUARTTick = millis();
    if(buffUARTIndex >= MAX_PACKETSIZE - 1) //messaggio troppo lungo
    {
      buffUARTIndex = MAX_PACKETSIZE - 2;
      preUARTTick = preUARTTick - 200;
    }
  }
  
  if(buffUARTIndex > 0 && (millis() - preUARTTick >= 100)) //messaggio lunghezza giusta, 100 ms per sicurezza
  { //data ready
    buffUART[buffUARTIndex] = 0x00;
    if(buffUART[0]=='C') 
    {
      Serial.println(buffUART);
      Serial.println("You have modified the parameters!");//indicates that the obstacle avoidance distance parameter has been modified
      sscanf(buffUART,"CMD%d,%d,%d",&distancelimit,&sidedistancelimit,&tempo_svolta);
      // Serial.println(distancelimit);
      // Serial.println(sidedistancelimit);
      // Serial.println(turntime);
    }
    else  istruzioni=buffUART[0];
    buffUARTIndex = 0;
  }
  /*
  if(Serial.available()>0)
  {
      char temp[32];
      memset(temp,0x00,32);
      size_t message_length=Serial.available();
      if(message_length<32) Serial.readBytes(temp,message_length);
      if(temp[0]=='C') {
        Serial.println(temp);
        Serial.println("You have modified the parameters!");
        sscanf(temp,"CMD%d,%d,%d",&distancelimit,&sidedistancelimit,&turntime);
      }
      else if(message_length<=1&&temp!=NULL) Uart_Date=temp[0];
*/
  switch (istruzioni)    //istruzioni da seriale
  {
    case '2':stato_guida=GUIDA_MANUALE; azione=AVANTI;Serial.println("AVANTI"); break;
    case '4':stato_guida=GUIDA_MANUALE; azione=SINISTRA; Serial.println("SINISTRA");break;
    case '6':stato_guida=GUIDA_MANUALE; azione=DESTRA; Serial.println("DESTRA");break;
    case '8':stato_guida=GUIDA_MANUALE; azione=INDIETRO; Serial.println("INDIETRO");break;
    case '5':stato_guida=GUIDA_MANUALE; azione=FERMA;buzz_OFF();Serial.println("STOP");break;
    case '3':stato_guida=ULTRASONIC; Serial.println("ULTRASONIC...");break;
    case '1':stato_guida=LINE_FOLLOW; Serial.println("LINE FOLLOW...");break;
    default:break;
  }
}


void guida()
{
  if(stato_guida == GUIDA_MANUALE)
  {
    switch (azione) 
    {
      case AVANTI:
          avanti();
          setspeed(255,255);
          RunningFlag = true;
          RunningTimeCnt = 1;
          RunningTime=millis();
          break;
      case SINISTRA: 
          sinistra();
          setspeed(255,255);
          RunningFlag = true;
          RunningTimeCnt = 1;
          RunningTime=millis();
          break;
      case DESTRA:  
          destra();
          setspeed(255,255);
          RunningFlag = true;
          RunningTimeCnt = 1;
          RunningTime=millis();
          break;
      case INDIETRO: 
          indietro();
          setspeed(255,255);
          RunningFlag = true;
          RunningTimeCnt = 1;
          RunningTime=millis();
          break;
      case FERMA: 
          ferma();
          RunningTime = 0;
          break;
      default:
          break;
    }
    azione=DEF;
    //keep the car running for 100ms
    if(millis()-RunningTime>=100)
    {
      RunningTime=millis();
      if(RunningFlag == true) 
      {
        stopFlag = false;
        if(RunningTimeCnt <= 0) 
        {
          RunningFlag = false;
          stopFlag = true;
        }
        RunningTimeCnt--;
      }
      if(stopFlag == true) 
      {
        RunningTimeCnt=0;
        ferma();
      }
    }
  }
  else if(stato_guida==LINE_FOLLOW)
  {
    follow_line();
  }
  else if(stato_guida==ULTRASONIC)
  {
   auto_ultrasonic();
  }
}
