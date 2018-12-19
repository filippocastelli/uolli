void receive_commands()
{
  int istruzioni = -1;
  if(Serial1.available()>0)
  {
      int temp = -1;
      size_t message_length=Serial1.available();
      temp = Serial1.parseInt();

      if(temp!=-1 && temp != 0){
        istruzioni = temp;
        Serial.println("istruzioni ricevute:");
        Serial.println(temp);
      }

  }

  switch (istruzioni)    //istruzioni da seriale
  {
    case 2:stato_guida=GUIDA_MANUALE; azione=AVANTI;Serial.println("AVANTI"); break;
    case 4:stato_guida=GUIDA_MANUALE; azione=SINISTRA; Serial.println("SINISTRA");break;
    case 6:stato_guida=GUIDA_MANUALE; azione=DESTRA; Serial.println("DESTRA");break;
    case 8:stato_guida=GUIDA_MANUALE; azione=INDIETRO; Serial.println("INDIETRO");break;
    case 5:stato_guida=GUIDA_MANUALE; azione=FERMA;buzz_OFF();Serial.println("STOP");break;
    case 3:stato_guida=ULTRASONIC; Serial.println("ULTRASONIC...");break;
    case 1:stato_guida=LINE_FOLLOW; Serial.println("LINE FOLLOW..."); primae_noctis = true; break;
    case 7:stato_guida=IRMODE; Serial.println("IRMODE...");  
    default:break;
  }

  if (stato_guida == IRMODE){
    azione = ir_getaction();
  }
}


void guida()
{
//  Serial.println("sto facendo: ");
//  Serial.println(azione);
  if(stato_guida == GUIDA_MANUALE || stato_guida == IRMODE)
  {
    //Serial.println(azione);
    switch (azione) 
    {
      case AVANTI:
          avanti();
          setspeed(manual_speed,manual_speed);
          RunningFlag = true;
          RunningTimeCnt = 1;
          RunningTime=millis();
          break;
      case SINISTRA: 
          sinistra();
          setspeed(manual_speed,manual_speed);
          RunningFlag = true;
          RunningTimeCnt = 1;
          RunningTime=millis();
          break;
      case DESTRA:  
          destra();
          setspeed(manual_speed,manual_speed);
          RunningFlag = true;
          RunningTimeCnt = 1;
          RunningTime=millis();
          break;
      case INDIETRO: 
          indietro();
          setspeed(manual_speed,manual_speed);
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
    if(millis()-RunningTime>=manual_time)
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
    primae_noctis = follow_line(primae_noctis);
  }
  else if(stato_guida==ULTRASONIC)
  {
   auto_ultrasonic();
  }
}

void serialcopy(){
  if(Serial1.available()){
    int intByte = Serial1.parseInt();
    Serial.println(intByte);
    //Serial.println(intByte);
    if (intByte == 2){
      Serial.println("ciao");
    }
  }
}
