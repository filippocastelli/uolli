IRrecv IR(IRreceiverpin);
decode_results IRresults;

void irguide_setup{
  pinMode(IRreceiverpin, INPUT);
  digitalWrite(IRreceiverpin, HIGH);
  IR.enableIRIn();
}
void ir_getaction(){
  if (IR.decode(&IRresults)){
    if(IRresults.value==IR_AVANTI)
    {
      azione = AVANTI;
    }
    else if (IRresults.value == IR_INDIETRO) {
      azione = INDIETRO;
    }
    else if (IRresults.value == IR_DX){
      azione = DESTRA;
    }
    else if (IRresults.value == IR_SX){
      azione = SINISTRA;
    }
    else if (IRresults.value == IR_STOP){
      azione = FERMA;
    }

    IRresults.value = 0;
    IR.resume();
  }
}

