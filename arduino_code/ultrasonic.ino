int measuredist(){
  long dist;
  digitalWrite(trigpin,LOW);
  delayMicroseconds(5);                                                                              
  digitalWrite(trigpin,HIGH);
  delayMicroseconds(15);
  digitalWrite(trigpin,LOW);
  dist=pulseIn(echopin,HIGH);
  dist=dist*0.01657; //distanza oggetto in cm
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
  servo.write(120);
  delay(100);
  dist_sxdiag = measuredist();
  if(dist_sxdiag<distancelimit){
    ferma();
    Serial.println("stop");
    alarm();
    }
  servo.write(170); 
  delay(300);
  dist_sx = measuredist();
  if(dist_sx<sidedistancelimit){
    ferma();
    Serial.println("stop");
    alarm();
    }
  servo.write(120);
  delay(100);
  dist_sxdiag = measuredist();
  if(dist_sxdiag<distancelimit){
    ferma();
    Serial.println("stop");
    alarm();
    }
  servo.write(90);
  delay(100);
  dist_avanti = measuredist();
  if(dist_avanti<distancelimit){
    ferma();
    Serial.println("stop");
    alarm();
    }
  servo.write(40);
  delay(100);
  dist_rxdiag = measuredist();
  if(dist_rxdiag<distancelimit){
    ferma();
    Serial.println("stop");
    alarm();
    }
  servo.write(0);
  delay(100);
  dist_rx = measuredist();
  if(dist_rx<sidedistancelimit){
    ferma();
    Serial.println("stop");
    alarm();
    }
  servo.write(90);
  delay(300);
}

void auto_ultrasonic(){
  avanti();
  Serial.println("avanti");
  setspeed(autodrive_speed,autodrive_speed);
  ++ncicli;
  if(ncicli>100){ //ogni 100 controlliamo
    scandist();
    if(dist_sx<sidedistancelimit || dist_sxdiag<distancelimit){
      destra();
      Serial.println("svolta dx");
      setspeed(autodrive_speed,autodrive_speed);
      delay(tempo_svolta);
    }
    if(dist_rx<sidedistancelimit || dist_rxdiag<distancelimit){
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
    ncicli=0;
  }
  distance = measuredist(); // guarda a diritto
  if (distance<distancelimit){ // se segnale sporco ci fermiamo solo quando leggiamo 25 positivi
      ++robaadiritto;}
  if (distance>distancelimit){
      robaadiritto=0;}
  if (robaadiritto > 25){
    ferma(); // c'è roba a diritto
    Serial.println("stop");
    robaadiritto=0;
  }
}

void initultrasonic() {
  pinMode(trigpin, OUTPUT);
  pinMode(echopin, INPUT);
  digitalWrite(trigpin,LOW);
  
  servo.attach(servopin);
  servo.write(90); // guarda a diritto
}

