
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
 But the maximum default of 8 MAX72XX will also work.
 */

LedControl lc=LedControl(13,12,11,2);

/* we always wait a bit between updates of the display */
unsigned long delaytime=100;

/* paste code snippets from the reference documentation here */

///////////////////////////////////////////////////////////////////////////////////////
//First 2 digits on VHF AM radio freq
void onVhfamFreq1Change(char* newValue) {
    lc.setChar(0,6,newValue[0],false);
    lc.setChar(0,5,newValue[1],false);
}
DcsBios::StringBuffer<2> vhfamFreq1Buffer(0x1190, onVhfamFreq1Change);
//Knob for changing the first 2 digits on VHF AM radio freq
DcsBios::RotaryEncoder vhfamFreq1("VHFAM_FREQ1", "DEC", "INC", 3, 2);

//Third digit on VHF AM radio freq
void onVhfamFreq2Change(unsigned int newValue) {
    lc.setChar(0,4,newValue, true);
}
DcsBios::IntegerBuffer vhfamFreq2Buffer(0x118e, 0x00f0, 4, onVhfamFreq2Change);
//Knob 
DcsBios::RotaryEncoder vhfamFreq2("VHFAM_FREQ2", "DEC", "INC", 5, 4);

//Fourth digit on VHF AM radio freq
void onVhfamFreq3Change(unsigned int newValue) {
    lc.setChar(0,3,newValue,false);
}
DcsBios::IntegerBuffer vhfamFreq3Buffer(0x118e, 0x0f00, 8, onVhfamFreq3Change);
//Knob
DcsBios::RotaryEncoder vhfamFreq3("VHFAM_FREQ3", "DEC", "INC", 7, 6);

//Last 2 digits on VHF AM radio freq
void onVhfamFreq4Change(char* newValue) {
    lc.setChar(0,2,newValue[0],false);
    lc.setChar(0,1,newValue[1],false);
}
DcsBios::StringBuffer<2> vhfamFreq4Buffer(0x1192, onVhfamFreq4Change);

//VHF AM Volume Control
DcsBios::RotaryEncoder vhfamVol("VHFAM_VOL", "-3200", "+3200", A2, A3);
/////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////
//First 2 digits on VHF FM radio freq
void onVhffmFreq1Change(char* newValue) {
    lc.setChar(1,6,newValue[0],false);
    lc.setChar(1,5,newValue[1],false);
}
DcsBios::StringBuffer<2> vhffmFreq1Buffer(0x119a, onVhffmFreq1Change);
//Knob
DcsBios::RotaryEncoder vhffmFreq1("VHFFM_FREQ1", "DEC", "INC", 9, 10);

//Third digit on VHF FM radio freq
void onVhffmFreq2Change(unsigned int newValue) {
    lc.setChar(1,4,newValue,true);
}
DcsBios::IntegerBuffer vhffmFreq2Buffer(0x119c, 0x000f, 0, onVhffmFreq2Change);
//Knob
DcsBios::RotaryEncoder vhffmFreq2("VHFFM_FREQ2", "DEC", "INC", A4, A5);

//Fourth digit on VHF FM radio freq
void onVhffmFreq3Change(unsigned int newValue) {
    lc.setChar(1,3,newValue,false);
}
DcsBios::IntegerBuffer vhffmFreq3Buffer(0x119c, 0x00f0, 4, onVhffmFreq3Change);

//Last 2 digits on VHF FM radio freq
void onVhffmFreq4Change(char* newValue) {
    lc.setChar(1,2,newValue[0],false);
    lc.setChar(1,1,newValue[1],false);
}
DcsBios::StringBuffer<2> vhffmFreq4Buffer(0x119e, onVhffmFreq4Change);

//VHF FM Volume Control
DcsBios::RotaryEncoder vhffmVol("VHFFM_VOL", "-3200", "+3200", A0, A1);

/////////////////////////////////////////////////////////////////////////////////////



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
