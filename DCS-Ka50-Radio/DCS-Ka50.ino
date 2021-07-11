
/*
  Tell DCS-BIOS to use a serial connection and use interrupt-driven
  communication. The main program will be interrupted to prioritize
  processing incoming data.
  
  This should work on any Arduino that has an ATMega328 controller
  (Uno, Pro Mini, many others).
 */
#define DCSBIOS_IRQ_SERIAL

#include "DcsBios.h"
#include "LedControl.h"
/*
 Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin 12 is connected to the DataIn 
 pin 11 is connected to the CLK 
 pin 10 is connected to LOAD 
 ***** Please set the number of devices you have *****
 But the maximum default of 8 MAX72XX wil also work.
 */

LedControl lc=LedControl(12,11,10,2);

/* we always wait a bit between updates of the display */
unsigned long delaytime=200;

/* paste code snippets from the reference documentation here */

//First 2 digits on r800 radio freq
void onR800Freq1Change(char* newValue) {
    lc.setChar(0,6,newValue[0],false);
    lc.setChar(0,5,newValue[1],false);
}
DcsBios::StringBuffer<2> r800Freq1Buffer(0x190e, onR800Freq1Change);
//1st rotary
DcsBios::RotaryEncoder r800Freq1("R800_FREQ1", "DEC", "INC", 3, 2);

//Third digit on r800 radio freq
void onR800Freq2Change(unsigned int newValue) {
    lc.setChar(0,4,newValue,true);
}
DcsBios::IntegerBuffer r800Freq2Buffer(0x190c, 0x3c00, 10, onR800Freq2Change);
//2nd rotary
DcsBios::RotaryEncoder r800Freq2("R800_FREQ2", "DEC", "INC", 5, 4);

//Fourth digit on r800 radio freq
void onR800Freq3Change(unsigned int newValue) {
    lc.setChar(0,3,newValue,false);
}
DcsBios::IntegerBuffer r800Freq3Buffer(0x1910, 0x000f, 0, onR800Freq3Change);
//3rd rotary
DcsBios::RotaryEncoder r800Freq3("R800_FREQ3", "DEC", "INC", 7, 6);

//Fifth and sixth digits on r800 radio freq
void onR800Freq4Change(char* newValue) {
    lc.setChar(0,2,newValue[0],false);
    lc.setChar(0,1,newValue[1],false);
    lc.setLed(0,0,7,false);  
}
DcsBios::StringBuffer<2> r800Freq4Buffer(0x1912, onR800Freq4Change);


void setup() {
  DcsBios::setup();
  //This initializes the first MAX7219 display and gets it ready of use:
 lc.shutdown(0,false); //turn on the display
 lc.setIntensity(0,2);//set the brightness 
 lc.clearDisplay(0); //clear the display 
 
 //second display init
 lc.shutdown(1,false); //turn on the display
 lc.setIntensity(1,2);//set the brightness 
 lc.clearDisplay(1); //clear the display
}

void loop() {
   DcsBios::loop();
}
