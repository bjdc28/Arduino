/*
 Copyright (C) 2012 James Coliz, Jr. <maniacbug@ymail.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 
 Update 2014 - TMRh20
 */

/**
 * Simplest possible example of using RF24Network,
 *
 * RECEIVER NODE
 * Listens for messages from the transmitter and prints them out.
 */

#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>


RF24 radio(7,8);                // nRF24L01(+) radio attached using Getting Started board 

RF24Network network(radio);      // Network uses that radio
const uint16_t this_node = 02;    // Address of our node in Octal format ( 04,031, etc)
const uint16_t other_node = 0111;   // Address of the other node in Octal format

struct payload_t {                 // Structure of our payload
  double spv1;
  double btv1;
  double spc1;
//  double spv2;
//  double btv2;
//  double spc2;
  int Rs1;
  int Rb1;
  int Rl1;
//  int Rs2;
//  int Rb2;
//  int Rl2;
};
payload_t payload;


void setup(void)
{
  Serial.begin(9600);
  Serial.println("RF24Network/examples/helloworld_rx/");
 
  SPI.begin();
  radio.begin();
  network.begin(/*channel*/ 90, /*node address*/ this_node);
}

void loop(void){
  
  network.update();                  // Check the network regularly

  
  while ( network.available() ) {     // Is there anything ready for us?
    
    RF24NetworkHeader header;        // If so, grab it and print it out
    
    network.read(header,&payload,sizeof(payload));
  }
}

