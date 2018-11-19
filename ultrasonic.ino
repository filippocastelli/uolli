int measuredist(){
  long dist;
  digitalWrite(trigpin,LOW);
  delayMicroseconds(5);                                                                              
  digitalWrite(trigpin,HIGH);
  delayMicroseconds(15);
  digitalWrite(trigpin,LOW);
  dist=pulseIn(echopin,HIGH);
  dist=dist*0.01657; //how far away is the object in cm
  //Serial.print((int)dist);
  //Serial.println(" cm");
  return round(dist);
}

void scandist(){                     
  dist_avanti = measuredist();
  if(dist_avanti<distancelimit){
    ferma();
    Serial.println("stop");
    alarm();
    }
  head.write(120);
  delay(100);
  dist_sxdiag = measuredist();
  if(dist_sxdiag<distancelimit){
    ferma();
    Serial.println("stop");
    alarm();
    }
  head.write(170); //Didn't use 180 degrees because my servo is not able to take this angle
  delay(300);
  dist_sx = measuredist();
  if(dist_sx<sidedistancelimit){
    ferma();
    Serial.println("stop");
    alarm();
    }
  head.write(120);
  delay(100);
  dist_sxdiag = measuredist();
  if(dist_sxdiag<distancelimit){
    ferma();
    Serial.println("stop");
    alarm();
    }
  head.write(90); //use 90 degrees if you are moving your servo through the whole 180 degrees
  delay(100);
  dist_avanti = measuredist();
  if(dist_avanti<distancelimit){
    ferma();
    Serial.println("stop");
    alarm();
    }
  head.write(40);
  delay(100);
  dist_rxdiag = measuredist();
  if(dist_rxdiag<distancelimit){
    ferma();
    Serial.println("stop");
    alarm();
    }
  head.write(0);
  delay(100);
  dist_rx = measuredist();
  if(dist_rx<sidedistancelimit){
    ferma();
    Serial.println("stop");
    alarm();
    }
  head.write(90);
  delay(300);
}

void auto_avoidance(){
  avanti();  // if nothing is wrong go forward using go() function above.
  Serial.println("avanti");
  setspeed(autodrive_speed,autodrive_speed);
  ++ncicli;
  if(numcycles>100){ //Watch if something is around every 100 loops while moving forward 
    scandist();
    if(dist_sx<sidedistancelimit || dist_sxdiag<distancelimit){
      destra();
      Serial.println("svolta dx");
      setspeed(autodrive_speed,autodrive_speed);
      delay(tempo_svolta);
    }
    if(rightscanval<sidedistancelimit || rdiagonalscanval<distancelimit){
      sinistra();
      Serial.println("svolta sx");
      setspeed(autodrive_speed,autodrive_speed);
      delay(tempo_svolta);
    }
    // cul de sac
    if((dist_rx<sidedistancelimit || dist_rxdiag<distancelimit)&&(dist_sx<sidedistancelimit || dist_sxdiag<distancelimit)&&(dist_avanti<distancelimit)){
          indietro();
          Serial.println("torna indietro");
          setspeed(autodrive_speed,autodrive_speed);
          delay(2*tempo_svolta);
          sinistra();
          setspeed(autodrive_speed,autodrive_speed); //prob. inutile, devo testare sulla macchina
          delay(tempo_svolta);
        }
    numcycles=0;
  }
  distance = measuredist(); // guarda a diritto
  if (distance<distancelimit){ // se segnale sporco ci fermiamo solo quando leggiamo 25 positivi
      ++robaadiritto;}
  if (distance>distancelimit){
      robaadiritto=0;} //Count is restarted
  if (robaadiritto > 25){
    ferma(); // Since something is ahead, stop moving.
    Serial.println("stop");
    robaadiritto=0;
  }
}
