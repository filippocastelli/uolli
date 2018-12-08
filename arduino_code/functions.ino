void initleds(){
  pinMode(led1pin, OUTPUT);
  pinMode(led2pin, OUTPUT);
  pinMode(led3pin, OUTPUT);
  pinMode(led4pin, OUTPUT);
  pinMode(led5pin, OUTPUT);

  pinMode(btnpin, INPUT);
  btntime = millis();
}

void button_tic(){
  if ((digitalRead(btnpin) == HIGH)&&(btntime-millis() > 100)){
    change_drivemode();
    light_leds();
    btntime = millis();
    }
}

void change_drivemode(){
  int temp_status = stato_guida;
  temp_status++;
  if (temp_status < 4){
   stato_guida = temp_status;
  }
  else{
    stato_guida = 0;
  }
}

void light_leds(){
  for(int i = 0; i<=3; i++){
    if (i == stato_guida){
      pinMode(mode_leds[i], HIGH);
    }
    else {
      pinMode(mode_leds[i], LOW);
    }
  }
}


