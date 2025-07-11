// all libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

int csn_pin = 8;
int ce_pin = 7;
RF24 radio(ce_pin, csn_pin);

int botton;
int bottonState = false;

const byte address[6] = "00001";

Servo myservo;
int servoPin = 5;
int open = 127;
int closed = 37;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();

  myservo.attach(servoPin);
  myservo.write(closed);
}

void loop() {
  if (radio.available()) {
    // char text[32] = "";
    radio.read(&botton, sizeof(botton));
    Serial.println(botton);

    if (botton && !bottonState) {
      bottonState = true;
      myservo.write(open);
      delay(500);
      myservo.write(closed);
      delay(500);
    } else if (!botton && bottonState) {
      bottonState = false;
    }
  }
}