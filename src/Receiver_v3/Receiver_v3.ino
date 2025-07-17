// serial, radio, and servo libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

// transceiver pins, radio constructor
const int csn_pin = 8;
const int ce_pin = 7;
RF24 radio(ce_pin, csn_pin);

// will store output received
int botton;

// channel matches with transmitter
const byte address[6] = "00001";

// feeder servo constructor, servo pins, angle constants
Servo feeder;
const int servoPin1 = 6;
const int open1 = 137;
const int closed1 = 47;

// mixer servo constructor, servo pins, angle constants
Servo mixer;
const int servoPin2 = 5;
const int open2 = 95;
const int closed2 = 160;

void setup() {
  // set up radio; address 00001, pipe 0, minimum power level, set as receiver
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();

  // set feeder servo pin, move to default position
  feeder.attach(servoPin1);
  feeder.write(closed1);
  // set mixer servo pin, move to default position
  mixer.attach(servoPin2);
  mixer.write(closed2);
  // allow servos time to move
  delay(500);
}

void loop() {
  // check for unread transmission
  if (radio.available()) {
    // read transmission into "botton" int
    radio.read(&botton, sizeof(botton));

    // when button pressed
    if (botton) {
      // open feeder, delay 0.5 seconds, close feeder and move mixer, delay 0.5 seconds to allow everything to move, move mixer again
      feeder.write(open1);
      delay(500);
      feeder.write(closed1);
      mixer.write(open2);
      delay(500);
      mixer.write(closed2);
    }
  }
}