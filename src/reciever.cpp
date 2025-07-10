#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>
#include <pitches.h>

const int buzzerPin = 5;

const int buttonPIN = 38;

int melody[] = {
  NOTE_A5, 0, NOTE_E5, NOTE_D5, NOTE_CS5, 
  0, NOTE_CS5, NOTE_D5, NOTE_E5, NOTE_FS5,
  NOTE_GS5, NOTE_E5, 0, NOTE_FS5, 0, NOTE_E5,
  NOTE_D5, 0, NOTE_CS5, 0, NOTE_CS5, 0, NOTE_B4,
  0, NOTE_CS5, 0, NOTE_D5, 0, NOTE_A5, 0, NOTE_E5, NOTE_D5, NOTE_CS5, 
  0, NOTE_CS5, NOTE_D5, NOTE_E5, NOTE_FS5, NOTE_D5, 0,
  NOTE_FS5, NOTE_E5, NOTE_D5, NOTE_CS5, NOTE_B4, NOTE_CS5, NOTE_D5, NOTE_FS5,
  NOTE_E5, NOTE_D5, NOTE_CS5, NOTE_B4, NOTE_A4, 0
};

int jingle[] = {
  NOTE_C5, NOTE_C5, NOTE_C5, NOTE_F5, NOTE_A5, NOTE_C5, NOTE_C5, NOTE_C5, NOTE_F5, NOTE_A5, 0,
  NOTE_F5, NOTE_F5, NOTE_E5, NOTE_E5, NOTE_D5, NOTE_D5, NOTE_C5
};

int loonboon[] = {
  NOTE_GS3, NOTE_A3
};

int loonboonDuration[] = {
  4, 8
};

int jingleDuration[] = {
  8, 8, 8, 2, 4, 8, 8, 8, 2, 2, 4, 8, 8 ,8 ,8 ,8 ,8, 2
};

int noteDurations[] = {
  8, 8, 8, 8, 4, 8, 8, 8, 8, 8, 8, 4, 4, 
  8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 4,
  8, 8, 8, 8, 4, 4, 8, 8, 8, 8, 4, 4,
  8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 4
};

RF24 radio(7, 8); // CE, CSN

Servo servy;

const byte address[][6] = {"00001", "00002"};


int buttonState;
int lastButtonState;
// 
void playNotes(int notes[], int duration[], int numNotes){

  // Iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < numNotes; thisNote++) {
    // To calculate the note duration, take one second divided by the note type.
    int noteDuration = 1000 / duration[thisNote];
    tone(buzzerPin, notes[thisNote], noteDuration);

    // To distinguish the notes, set a minimum time between them.
    int pauseBetweenNotes = noteDuration * 1.2;
    delay(pauseBetweenNotes);

    // Stop the tone playing:
    noTone(buzzerPin);
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(buzzerPin, OUTPUT);
  pinMode(buttonPIN, INPUT);
  randomSeed(analogRead(0));
  Serial.begin(9600);
  servy.attach(6);
  radio.begin();
  // radio.openWritingPipe(address[1]);
  radio.openReadingPipe(1, address[0]);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    int numNotes = 0;

    radio.read(&buttonState, sizeof(buttonState));
    if (buttonState == HIGH) {
      int randomNum = random(1, 3);
      Serial.println(randomNum);
      servy.write(90);
      lastButtonState = 1;

      Serial.println("hi");
      numNotes = sizeof(loonboon) / sizeof(loonboon[0]);

      playNotes(loonboon, loonboonDuration, numNotes);
    }
    
    
  
  } else {
    servy.write(180);
  }
  delayMicroseconds(1);
  
}