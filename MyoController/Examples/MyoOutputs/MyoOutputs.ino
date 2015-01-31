#include "MyoController.h"

#define fistP 4
#define waveinP 5
#define waveoutP 6
#define fingersSpreadP 7
#define doubletapP 8

MyoController myo = MyoController();

void setup() {

  pinMode(fistP, OUTPUT);
  pinMode(waveinP, OUTPUT);
  pinMode(waveoutP, OUTPUT);
  pinMode(fingersSpreadP, OUTPUT);
  pinMode(doubletapP, OUTPUT);
  
  myo.initMyo();
}

void loop()
{
   
   myo.updatePose();
   switch ( myo.getCurrentPose() ) {
    case rest:
      digitalWrite(fistP,LOW); 
      digitalWrite(waveinP,LOW);
      digitalWrite(waveoutP,LOW);
      digitalWrite(fingersSpreadP,LOW);
      digitalWrite(doubletapP,LOW);
      break;
    case fist:
      digitalWrite(fistP,HIGH);
      break;
    case waveIn:
      digitalWrite(waveinP,HIGH);
      break;
    case waveOut:
      digitalWrite(waveoutP,HIGH);
      break;
    case fingersSpread:
      digitalWrite(fingersSpreadP,HIGH);
      break;
    case doubleTap:
      digitalWrite(doubletapP,HIGH);
      break;
   } 
   delay(100);
}
