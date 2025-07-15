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
int ledPIN = 5;
int buttonState;
int prevState; // to store last state of button, preventing resending when holding

// address matches receiver
const byte address[6] = "00001";

void setup() {
  // set button pin input and led pin output; transmitter pins handled automatically by library
  pinMode(buttonPin, INPUT);
  pinMode(ledPIN, OUTPUT);
  digitalWrite(ledPIN, HIGH);
  // set up radio; address 00001, automatically writes to pipe 0, power level minimum, set as transmitter
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {
  // read button input pin; HIGH if pressed, LOW otherwise
  buttonState = digitalRead(buttonPin);
  // if button pressed, and wasn't pressed before, send value of "buttonState" int; set bool "success" to true if receive acknowledgement, false otherwise
  if (buttonState && !prevState) {
    prevState = HIGH;
    success = radio.write(&buttonState, sizeof(buttonState));
    // if received acknowledgement, temporarily turn off LED, and delay, allowing servo to move before resending
    if (success) {
      digitalWrite(ledPIN, LOW);
      delay(500);
      digitalWrite(ledPIN, HIGH);
      delay(500);
    }
  } else if (!buttonState && prevState) {
    prevState = LOW;
  }
  // wait 0.1 seconds to prevent overloading board
  delay(100);
}