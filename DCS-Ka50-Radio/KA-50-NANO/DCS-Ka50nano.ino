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
 pin 13 is connected to the DataIn 
 pin 12 is connected to the CLK 
 pin 11 is connected to LOAD 
 ***** Please set the number of devices you have *****
 But the maximum default of 8 MAX72XX wil also work.
 */

LedControl lc=LedControl(13,12,11,2);

/* we always wait a bit between updates of the display */
unsigned long delaytime=100;

/* paste code snippets from the reference documentation here */

///////////////////////////////////////////////////////////////////////////////
//R-800 AM Radio (eg: 126.000 AM)
//Display first 2 digits on radio freq
void onR800Freq1Change(char* newValue) {
    lc.setChar(0,6,newValue[0],false);
    lc.setChar(0,5,newValue[1],false);
}
DcsBios::StringBuffer<2> r800Freq1Buffer(0x190e, onR800Freq1Change);
//1st rotary knob
DcsBios::RotaryEncoder r800Freq1("R800_FREQ1", "DEC", "INC", 3, 2);

//Display third digit on radio freq
void onR800Freq2Change(unsigned int newValue) {
    lc.setChar(0,4,newValue,true);
}
DcsBios::IntegerBuffer r800Freq2Buffer(0x190c, 0x3c00, 10, onR800Freq2Change);
//2nd rotary
DcsBios::RotaryEncoder r800Freq2("R800_FREQ2", "DEC", "INC", 4, 5);

//Fourth digit on R-800 AM radio freq
void onR800Freq3Change(unsigned int newValue) {
    lc.setChar(0,3,newValue,false);
}
DcsBios::IntegerBuffer r800Freq3Buffer(0x1910, 0x000f, 0, onR800Freq3Change);
//3rd rotary
DcsBios::RotaryEncoder r800Freq3("R800_FREQ3", "DEC", "INC", 6, 7);

//Fifth and sixth digits on R-800 AM radio freq
void onR800Freq4Change(char* newValue) {
    lc.setChar(0,2,newValue[0],false);
    lc.setChar(0,1,newValue[1],false);
}
DcsBios::StringBuffer<2> r800Freq4Buffer(0x1912, onR800Freq4Change);

//R-800 AM / ADF Volume Knob
DcsBios::RotaryEncoder adfVolume("ADF_VOLUME", "-3200", "+3200", A3, A2);
////////////////////////////////////////////////////////////////////////////////////////////////

//R-828 FM Radio (eg: 30.000AM)
void onR828ChannelChange(unsigned int newValue) {
    // write "C" as the first char
    lc.setLed(1,7,1,true);
    lc.setLed(1,7,4,true);
    lc.setLed(1,7,5,true);
    lc.setLed(1,7,6,true);
    // write "H" as the second char
    lc.setLed(1,6,2,true);
    lc.setLed(1,6,3,true);
    lc.setLed(1,6,5,true);
    lc.setLed(1,6,6,true);
    lc.setLed(1,6,7,true);
    // display the current preset channel number
    lc.setChar(1,4,newValue+1,false);
}
DcsBios::IntegerBuffer r828ChannelBuffer(0x194a, 0x003c, 2, onR828ChannelChange);

//R-828 FM Channel Selector
DcsBios::RotaryEncoder r828Channel("R828_CHANNEL", "DEC", "INC", 9, 10);

//R-828 FM Volume Knob
DcsBios::RotaryEncoder r828Volume("R828_VOLUME", "-3200", "+3200", A5, A4);

///////////////////////////////////////////////////////////////////////////////////////////////
//Radio Communicator Selector
DcsBios::RotaryEncoder radioSelector("RADIO_SELECTOR", "DEC", "INC", A0, A1);

//////////////////////////////////////////////////////////////////////////////////////////

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
