// #include <Arduino.h>
// #include <SPI.h>
// #include <nRF24L01.h>
// #include <RF24.h>

// /*
// * Arduino Wireless Communication Tutorial
// *     Example 1 - Transmitter Code
// *                
// * by Dejan Nedelkovski, www.HowToMechatronics.com
// * 
// * Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
// */
// // 
// #include <SPI.h>
// #include <nRF24L01.h>
// #include <RF24.h>
// #include <Servo.h>

// #define buttonPin 22

// RF24 radio(9, 10); // CE, CSN

// const byte address[][6] = {"00001", "00002"};

// int buttonState;

// Servo servy;


// void setup() {
//   pinMode(buttonPin, INPUT);
//   servy.attach(6);
//   radio.begin();
//   radio.openWritingPipe(address[1]);
//   radio.openReadingPipe(1, address[0]);

//   radio.setPALevel(RF24_PA_MIN);
//   radio.stopListening();
// }

// void loop() {
//   buttonState = digitalRead(buttonPin);
//   radio.write(&buttonState, sizeof(buttonState));
//   delay(1000);
// }