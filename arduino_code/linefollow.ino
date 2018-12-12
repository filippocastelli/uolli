void initirsensors(){
  pinMode(IRsensor0pin, INPUT);
  pinMode(IRsensor1pin, INPUT);
  pinMode(IRsensor2pin, INPUT);
  pinMode(IRsensor3pin, INPUT);
  pinMode(IRsensor4pin, INPUT);
}

void measure_ir(){
  sensori_ir[0]=digitalRead(IRsensor0pin);
  sensori_ir[1]=digitalRead(IRsensor1pin);
  sensori_ir[2]=digitalRead(IRsensor2pin);
  sensori_ir[3]=digitalRead(IRsensor3pin);
  sensori_ir[4]=digitalRead(IRsensor4pin);

  if(invert_ir){
    for(int i = 0; i < 5; i++){
      sensori_ir[i] = (sensori_ir[i] == HIGH ? LOW : HIGH);
      }
    }
  //Serial.println(sensori_ir);
}

//follow_line
void follow_line(){
  measure_ir();
  if(sensori_ir[2]==HIGH){ //sensore centrale su linea nera
    if(sensori_ir[1]==LOW && sensori_ir[3]==LOW){ //sensori adiacenti su bianco
      avanti();  //finchè la barca va
      setspeed(linefollow_speed,linefollow_speed);
    }
    else if(sensori_ir[1]==HIGH && sensori_ir[3]==LOW){ //sensore dx su linea nera
       sinistra();  //sinistra
       setspeed(0,linefollow_speed);
    }
    else if(sensori_ir[1]==LOW && sensori_ir[3]==HIGH){  //sensore sx su linea nera
      destra();  //gira a destra
      setspeed(linefollow_speed,0);
    }
  }
  else if(sensori_ir[2]==LOW){  //sensore centrale fuori linea
    if(sensori_ir[1]==HIGH && sensori_ir[3]==LOW){ //sensore 
      sinistra();  
      setspeed(0,linefollow_speed);
    }
    else if(sensori_ir[1]==LOW && sensori_ir[3]==HIGH){ 
       destra();
       setspeed(linefollow_speed,0);
    }
    //controllo sensori periferici
    else if(sensori_ir[0]==HIGH && sensori_ir[4]==LOW){
      sinistra();
      setspeed(0, linefollow_speed);
    }
    else if(sensori_ir[0] == LOW && sensori_ir[4]==HIGH){
      destra();
      setspeed(linefollow_speed, 0);
    }
  }
}
