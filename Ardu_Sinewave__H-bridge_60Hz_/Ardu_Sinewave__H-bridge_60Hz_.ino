#include <avr/io.h>
#include <avr/interrupt.h>


int lookUp1[] = {
  0,  
  0, 
//  200, 
//  379, 
//  472, 
//  563, 
//  654, 
//  743, 
//  831, 
//  916, 
  0, 0, 0, 0, 0, 0, 0, 0, 
//  1000,
//  1081, 
//  1160, 
//  1236, 
//  1310, 
//  1380, 
//  1447, 
//  1511, 
  0, 0, 0, 0, 0, 0, 0, 0, 
  1572, 
  1629, 
  1683, 
  1732, 
  1778, 
  1819, 
  1857, 
  1890, 
  1919, 
  1944, 
  1964, 
  1980, 
  1991, 
  1998, 
  2000,
  1998, 
  1991, 
  1980, 
  1964, 
  1944, 
  1919, 
  1890, 
  1857, 
  1819, 
  1778, 
  1732, 
  1683, 
  1629, 
  1572, 
  0, 0, 0, 0, 0, 0, 0, 0, 
//  1511, 
//  1447, 
//  1380, 
//  1310, 
//  1236, 
//  1160, 
//  1081, 
//  1000, 
  0, 0, 0, 0, 0, 0, 0, 0, 
//  916, 
//  831, 
//  743, 
//  654, 
//  563, 
//  472, 
//  379, 
//  200, 
  0, 
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0
};
int lookUp2[] = {
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0, 
  0, 
//  200, 
//  379, 
//  472, 
//  563, 
//  654, 
//  743, 
//  831, 
//  916, 
  0, 0, 0, 0, 0, 0, 0, 0, 
//  1000,
//  1081, 
//  1160, 
//  1236, 
//  1310, 
//  1380, 
//  1447, 
//  1511, 
  0, 0, 0, 0, 0, 0, 0, 0, 
  1572, 
  1629, 
  1683, 
  1732, 
  1778, 
  1819, 
  1857, 
  1890, 
  1919, 
  1944, 
  1964, 
  1980, 
  1991, 
  1998, 
  2000,
  1998, 
  1991, 
  1980, 
  1964, 
  1944, 
  1919, 
  1890, 
  1857, 
  1819, 
  1778, 
  1732, 
  1683, 
  1629, 
  1572, 
  0, 0, 0, 0, 0, 0, 0, 0, 
//  1511, 
//  1447, 
//  1380, 
//  1310, 
//  1236, 
//  1160, 
//  1081, 
//  1000, 
  0, 0, 0, 0, 0, 0, 0, 0, 
//  916, 
//  831, 
//  743, 
//  654, 
//  563, 
//  472, 
//  379, 
//  200, 
  0, 
  0,
  0
};


void setup() {
  // Register initilisation, see datasheet for more detail.
    TCCR1A = 0b10100010;
       /*10 clear on match, set at BOTTOM for compA.
         10 clear on match, set at BOTTOM for compB.
         00
         10 WGM1 1:0 for waveform 15.
       */
    TCCR1B = 0b00011001;
       /*000
         11 WGM1 3:2 for waveform 15.
         001 no prescale on the counter.
       */
    TIMSK1 = 0b00000001;
       /*0000000
         1 TOV1 Flag interrupt enable. 
       */
    ICR1   = 2000;     // Period for 16MHz crystal, for a switching frequency of 8KHz for 133 subdivisions per 60Hz sin wave cycle.
    sei();             // Enable global interrupts.
    DDRB = 0b00000110; // Set PB1 and PB2 as outputs.
    pinMode(8,OUTPUT);
    pinMode(12,OUTPUT);
    digitalWrite(12, 0);
    digitalWrite(13, 0);
}

void loop() {}


ISR(TIMER1_OVF_vect){
    static int num;
    
    // change duty-cycle every period.
    OCR1A = lookUp1[num];
    OCR1B = lookUp2[num];
    
    if(num == 0)   digitalWrite(13, 1);
    if(num == 66)  digitalWrite(13, 0);
    if(num == 67)  digitalWrite(12, 1);
    if(num == 132) digitalWrite(12, 0);
    
    if(++num >= 133) num = 0;
    
}

