#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>

RF24 radio(7,8);
RF24Network network(radio);

const uint16_t this_node = 01;

struct payload_t {
  unsigned long ms;
  unsigned long counter;
};

void setup() {
  pinMode(5, OUTPUT);
  digitalWrite(5, HIGH);
  SPI.begin();
  radio.begin();
  network.begin(/*channel*/ 90, /*node address*/ this_node);

}

void loop() {
  network.update();

}
