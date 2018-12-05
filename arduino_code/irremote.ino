IRrecv IR(IRreceiverpin);
decode_results IRresults;


void initirguide(){
  pinMode(IRreceiverpin, INPUT);
  digitalWrite(IRreceiverpin, HIGH);
  IR.enableIRIn();
}
AZIONI ir_getaction(){
  if (IR.decode(&IRresults)){
    if(IRresults.value==IR_AVANTI)
    {
      azione = AVANTI;
      Serial.println("avanti_ir");
    }
    else if (IRresults.value == IR_INDIETRO) {
      azione = INDIETRO;
      Serial.println("indietro_ir");
    }
    else if (IRresults.value == IR_DX){
      azione = DESTRA;
      Serial.println("dx_ir");
    }
    else if (IRresults.value == IR_SX){
      azione = SINISTRA;
      Serial.println("sx_ir");
    }
    else if (IRresults.value == IR_STOP){
      azione = FERMA;
      Serial.println("stop_ir");
    }

    IRresults.value = 0;
    IR.resume();
    return azione;
  }
}

void irguida(){
  ir_getaction();
}
