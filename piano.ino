// bluetooth header
#include <LBT.h>
#include <LBTServer.h>
#define btName "Project"
char BTread;

// LED_bar header
#include <Suli.h>
#include <Wire.h>
#include "Seeed_LED_Bar_Arduino.h"
SeeedLedBar bar(3, 2);   // CLK -> D3, DTA -> D2

//buzzer_alarm header
const int speaker = 4;
int tempo = 300; 

// Do, Re, Mi, Fa, So, La, Si
readCharacter = ['q','w','e','r','t','y','u'];
ledBar = [0b0000000001, 0b0000000010, 0b0000000100, 0b0000001000, 0b0000010000, 0b0000100000, 0b0001000000];
toneFQ = [1915, 1700, 1519, 1432, 1275, 1136, 1014]; 

void setup() {
  // bluetooth
  LBTServer.begin((uint8_t*)btName);
  while(!LBTServer.accept(5)) { 
  }

  // speaker
  pinMode(speaker, OUTPUT);

  // LED bar
  bar.begin(3, 2);
}

void loop() {

  if(LBTServer.available()) {
    
	BTread = LBTServer.read();
	for(int i = 0; i < 7 ; i++){
		if(BTread == readCharacter[i]){
			bar.indexBit(ledBar[i]);
			playTone(toneFQ[i], tempo);
			delay(50);
		}
	}
	
	// Remove connextion
    if(BTread == 'm') {
      LBTServer.end();
      LBTServer.begin((uint8_t*)btName);
      while(!LBTServer.accept(5)) {
      }
    }

    delay(200);
  }
}

void playTone(int tone, int duration) {
   for (long i = 0; i < duration * 1000L; i += tone ) {
      digitalWrite(speaker, HIGH);
      delayMicroseconds(tone / 2);
      digitalWrite(speaker, LOW);
      delayMicroseconds(tone / 2);
   }
}
