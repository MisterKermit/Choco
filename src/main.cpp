// #include <Arduino.h>
// #include <pitches.h>
// #include <string.h>

// // Define the buzzer pin
// const int buzzerPin = 8;

// const int buttonPIN = 38;

// int melody[] = {
//   NOTE_A5, 0, NOTE_E5, NOTE_D5, NOTE_CS5, 
//   0, NOTE_CS5, NOTE_D5, NOTE_E5, NOTE_FS5,
//   NOTE_GS5, NOTE_E5, 0, NOTE_FS5, 0, NOTE_E5,
//   NOTE_D5, 0, NOTE_CS5, 0, NOTE_CS5, 0, NOTE_B4,
//   0, NOTE_CS5, 0, NOTE_D5, 0, NOTE_A5, 0, NOTE_E5, NOTE_D5, NOTE_CS5, 
//   0, NOTE_CS5, NOTE_D5, NOTE_E5, NOTE_FS5, NOTE_D5, 0,
//   NOTE_FS5, NOTE_E5, NOTE_D5, NOTE_CS5, NOTE_B4, NOTE_CS5, NOTE_D5, NOTE_FS5,
//   NOTE_E5, NOTE_D5, NOTE_CS5, NOTE_B4, NOTE_A4, 0
// };

// int jingle[] = {
//   NOTE_C5, NOTE_C5, NOTE_C5, NOTE_F5, NOTE_A5, NOTE_C5, NOTE_C5, NOTE_C5, NOTE_F5, NOTE_A5, 0,
//   NOTE_F5, NOTE_F5, NOTE_E5, NOTE_E5, NOTE_D5, NOTE_D5, NOTE_C5
// };

// int jingleDuration[] = {
//   8, 8, 8, 2, 4, 8, 8, 8, 2, 2, 4, 8, 8 ,8 ,8 ,8 ,8, 2
// };

// int noteDurations[] = {
//   8, 8, 8, 8, 4, 8, 8, 8, 8, 8, 8, 4, 4, 
//   8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 4,
//   8, 8, 8, 8, 4, 4, 8, 8, 8, 8, 4, 4,
//   8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 4
// };


// void setup() {

//   pinMode(buzzerPin, OUTPUT);
//   pinMode(buttonPIN, INPUT);
//   randomSeed(analogRead(0));
//   Serial.begin(9600);
// }

// void playNotes(int notes[], int duration[], int numNotes){

//   // Iterate over the notes of the melody:
//   for (int thisNote = 0; thisNote < numNotes; thisNote++) {
//     // To calculate the note duration, take one second divided by the note type.
//     int noteDuration = 1000 / duration[thisNote];
//     tone(buzzerPin, notes[thisNote], noteDuration);

//     // To distinguish the notes, set a minimum time between them.
//     int pauseBetweenNotes = noteDuration * 1.2;
//     delay(pauseBetweenNotes);

//     // Stop the tone playing:
//     noTone(buzzerPin);
//   }
// }


// void loop() {
//   // No need to repeat the melody in the loop for this example.
//   // The setup() is enough to play it once.
//   int numNotes = 0;
//   int buttonState = digitalRead(buttonPIN);

//   int randomNum = random(1, 3);
//   Serial.println(randomNum);
//   if (buttonState == HIGH) {
//     Serial.println("hi");
//     switch(randomNum) {
//       case 1:
//         numNotes = sizeof(melody) / sizeof(melody[0]);
//         playNotes(melody, noteDurations, numNotes);
//         break;
//       case 2:
//         numNotes = sizeof(jingle) / sizeof(jingle[0]);
//         playNotes(jingle, jingleDuration, numNotes);
//         break;
//     }
//   }
  


//   delay(500);

// }