// serial, radio, and servo libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

// transceiver pins, radio constructor
int csn_pin = 8;
int ce_pin = 7;
RF24 radio(ce_pin, csn_pin);

// will store output received
int botton;

// channel matches with transmitter
const byte address[6] = "00001";

// servo constructor, servo pins
Servo myservo;
int servoPin = 5;
int open = 127;
int closed = 37;

void setup() {
  // baud rate 9600
  Serial.begin(9600);

  // set up radio; address 00001, pipe 0, minimum power level, set as receiver
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();

  // set servo pin, move to default position
  myservo.attach(servoPin);
  myservo.write(closed);
}

void loop() {
  // check for unread transmission
  if (radio.available()) {
    // read transmission into "botton" int
    radio.read(&botton, sizeof(botton));
    Serial.println(botton);

    // when button pressed
    if (botton) {
      // open, delay .5 seconds, close
      myservo.write(open);
      delay(500);
      myservo.write(closed);
      // second delay to allow servo to move before receiving again
      delay(500);
    }
  }
}