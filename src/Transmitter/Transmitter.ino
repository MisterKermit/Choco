#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <esp_system.h>

int ce_pin = 7;
int csn_pin = 8;
RF24 radio(ce_pin, csn_pin);

const uint8_t address[6] = "45678";
int buttonState;
bool success;
int buttonPin = 3;
int ledPin = 4;

void softwareReset() {
  esp_restart();
}

void setup() {
  // radio.powerDown();
  // softwareReset();
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  SPI.setClockDivider(SPI_CLOCK_DIV8);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.setDataRate(RF24_250KBPS); // adjust rate and power level ^^ as needed
  radio.stopListening(); // set as transmitter
}

void loop() {
  Serial.println(buttonState);
  buttonState = digitalRead(buttonPin);
  if (buttonState) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }
  success = radio.write(&buttonState, sizeof(buttonState));
  if (success) {
    Serial.print("Sent: ");
    Serial.println(buttonState);
  } else {
    Serial.println("Failed to send");
  }
  delay(100);
}