// include serial and radio libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// radio pins and constructor
int ce_pin = 7;
int csn_pin = 8;
RF24 radio(ce_pin, csn_pin);

// to store output of RF24.write(): true if received acknowledgement of transmisison, false otherwise
bool success;

// button pin, light pin; var to store output of digitalRead() of button
int buttonPin = 3;
int ledPIN = 4;
int buttonState;

// address matches receiver
const byte address[6] = "00001";

void setup() {
  // baud rate 9600
  Serial.begin(9600);
  // set button pin input and led pin output; transmitter pins handled automatically by library
  pinMode(buttonPin, INPUT);
  pinMode(ledPIN, OUTPUT);
  // set up radio; address 00001, automatically writes to pipe 0, power level minimum, set as transmitter
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {
  // read button input pin; HIGH if pressed, LOW otherwise
  buttonState = digitalRead(buttonPin);
  Serial.print("button state: ");
  Serial.println(buttonState);
  // if button pressed, send value of "buttonState" int; set bool "success" to true if receive acknowledgement, false otherwise
  if (buttonState) {
    success = radio.write(&buttonState, sizeof(buttonState));
    // TODO: NOT SURE WHAT TO DO WITH LED
    // if (success) {
    //   digitalWrite(ledPIN, HIGH);
    // } else {
    //   digitalWrite(ledPIN, LOW);
    // }
    Serial.println(success);
  }
  // wait 0.1 seconds to prevent overloading board
  delay(100);
}