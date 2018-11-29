// -- buzzer --
#include "pitches.h"
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

void buzz_ON()   //open buzzer
{
  digitalWrite(buzzpin, LOW);
}
void buzz_OFF()  //close buzzer
{
  digitalWrite(buzzpin, HIGH);
}

void alarm(){
//   buzz_ON();
//   delay(100);
//   buzz_OFF();
  ticnote();
  ticnote();
}

void ticnote() {
  buzz_ON();
  delay(50);
  buzz_OFF();
  delay(50);
}

void oksound(){
  ticnote();
  ticnote();
  ticnote();
  //tone(buzzpin, 52, 4);
}

void obstaclesound(){
  ticnote();
  ticnote();
}

void sing(){
    for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(buzzpin, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(buzzpin);
  }
}

void initbuzzer(){
  pinMode(buzzpin, OUTPUT);
  buzz_OFF();
  //alarm();
  oksound();
  //sing();
}
