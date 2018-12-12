void avanti(void)  
{
  //Serial.println("avanti");
  digitalWrite(L1pin, HIGH);
  digitalWrite(L2pin,LOW);
  digitalWrite(R1pin,HIGH);
  digitalWrite(R2pin,LOW);
}
void sinistra()  
{
  digitalWrite(L1pin, HIGH);
  digitalWrite(L2pin,LOW);
  digitalWrite(R1pin,LOW);
  digitalWrite(R2pin,HIGH);
}
void destra()  
{
  digitalWrite(L1pin, LOW);
  digitalWrite(L2pin,HIGH);
  digitalWrite(R1pin,HIGH);
  digitalWrite(R2pin,LOW);
}
void indietro()  
{
  digitalWrite(L1pin, LOW);
  digitalWrite(L2pin,HIGH);
  digitalWrite(R1pin,LOW);
  digitalWrite(R2pin,HIGH);
}
void ferma()
{
  digitalWrite(L1pin, LOW);
  digitalWrite(L2pin,LOW);
  digitalWrite(R1pin,LOW);
  digitalWrite(R2pin,LOW);
}

void setspeed(int speed_L,int speed_R)
{
  analogWrite(speed_lpin,speed_L); 
  analogWrite(speed_rpin,speed_R);   
}

void initmotors()
{
  pinMode(L1pin, OUTPUT); 
  pinMode(L2pin, OUTPUT); 
  pinMode(speed_lpin, OUTPUT);  
  pinMode(R1pin, OUTPUT);
  pinMode(R2pin, OUTPUT); 
  pinMode(speed_rpin, OUTPUT); 
  ferma();
}
