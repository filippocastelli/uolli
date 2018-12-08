int measuredist(){
  long dist;
  //tempo = millis();
  digitalWrite(trigpin,LOW);
  //Serial.println("debug time 1: ");
  //Serial.println(millis()-tempo);
  delayMicroseconds(5);                                                                              
  digitalWrite(trigpin,HIGH);
  //Serial.println("debug time 2: ");
  //Serial.println(millis()-tempo);
  delayMicroseconds(15);
  digitalWrite(trigpin,LOW);
  //Serial.println("debug time 3: ");
  //Serial.println(millis()-tempo);
  dist=pulseIn(echopin,HIGH);
  dist=dist*0.01657; //distanza oggetto in cm
  //Serial.print((int)dist);
  //Serial.println(" cm");

  return round(dist);
}

void scandist(){
  Serial.println(distancelimit);
  Serial.println(sidedistancelimit);                  
  dist_avanti = measuredist();
  Serial.println(dist_avanti);
  if(dist_avanti< distancelimit){
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
  delay(100);
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
  delay(100);
}

void auto_ultrasonic(){
  tempo = millis();
  avanti();
  Serial.println("AUTO: avanti");
  setspeed(autodrive_speed,autodrive_speed);
  ++ncicli;
  Serial.println("ciclo");
  Serial.println(ncicli);
  if(ncicli>20){ //ogni 100 controlliamo
    scandist();
    if(dist_sx<sidedistancelimit || dist_sxdiag<distancelimit){
      destra();
      Serial.println("AUTO: svolta dx");
      setspeed(autodrive_speed,autodrive_speed);
      delay(tempo_svolta);
    }
    if(dist_rx<sidedistancelimit || dist_rxdiag<distancelimit){
      sinistra();
      Serial.println("AUTO: svolta sx");
      setspeed(autodrive_speed,autodrive_speed);
      delay(tempo_svolta);
    }
    // cul de sac
    if((dist_rx<sidedistancelimit || dist_rxdiag<distancelimit)&&(dist_sx<sidedistancelimit || dist_sxdiag<distancelimit)&&(dist_avanti<distancelimit)){
          indietro();
          Serial.println("AUTO: torna indietro");
          setspeed(autodrive_speed,autodrive_speed);
          delay(2*tempo_svolta);
          sinistra();
          setspeed(autodrive_speed,autodrive_speed); //prob. inutile, devo testare sulla macchina
          delay(tempo_svolta);
        }
    ncicli=0;
  }

  distance = measuredist(); // guarda a diritto
  
//  Serial.println("debug time autofunc: ");
//  Serial.println(millis()-tempo);
  
  if (distance<distancelimit){ // se segnale sporco ci fermiamo solo quando leggiamo 25 positivi
      ++robaadiritto;}
  if (distance>distancelimit){
      robaadiritto=0;}
  if (robaadiritto > 15){
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
  delay(500);
  servo.write(1);
  delay(500);
  servo.write(179);
  delay(500);
  servo.write(90);
  //scandist();
  alarm();
  
}
