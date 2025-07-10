#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

int csn_pin = 8;
int ce_pin = 7;
Servo myservo;
int open = 90;
int closed = 5;
RF24 radio(ce_pin, csn_pin);
int botton;
int servoPin = 7;
int lastState;

const uint8_t address[6] = "45678";

void softwareReset() {
  asm volatile ("jmp 0");  // Jump to address 0 (reset vector)
}

void setup() {
  // radio.powerDown();
  // softwareReset();
  Serial.begin(9600);
  SPI.setClockDivider(SPI_CLOCK_DIV8);
  myservo.attach(servoPin);
  myservo.write(closed);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.setDataRate(RF24_250KBPS); // adjust rate and power level ^^ as needed
  radio.startListening(); // set as receiver
}

void loop() {
  if(radio.available()) {
    radio.read(&botton, sizeof(botton));
    Serial.print("Received: ");
    Serial.println(botton);
    if (botton && !lastState) {
      lastState = HIGH;
      myservo.write(open);
      Serial.println(90);
      delay(500);
      myservo.write(closed);
      Serial.println(0);
    } else if (!botton && lastState) {
      lastState = LOW;
    }
  }
}