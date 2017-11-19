// all # define options should be defined here,  this keeps them together in a nice way

#define    VERSION_ID         F( "TwoAxis Ver1 2017 11 19.00" )


// !! fix next to right name 
#ifndef ddclock17_h     

#define ddclock17_h

// #include "WProgram.h" 
// #  https://github.com/adafruit/DHT-sensor-library/issues/1   changed 2015 Feb 21  this include is in several of the files
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

// redefinition: in many cases no reason not to go faster, use a standard rate
// including 19200 .......
//#define    BAUD_RATE          9600            
#define    BAUD_RATE          19200           
//#define    BAUD_RATE          38400 

// ---------------  configure hardware setup -------------  

// #define STEPPER_DRIVE_TYPE   AccelStepper::FULL4WIRE
#define STEPPER_DRIVE_TYPE   AccelStepper::HALF4WIRE    


//// 1  from make perms 
//#define STEPPER1_PIN_A 5
//#define STEPPER1_PIN_B 6
//#define STEPPER1_PIN_D 7
//#define STEPPER1_PIN_C 8

// 2  from make perms 
#define STEPPER1_PIN_A 5
#define STEPPER1_PIN_C 6
#define STEPPER1_PIN_B 7
#define STEPPER1_PIN_D 8

// =================== stepper 2 y altitude =======================


// 2  from make perms 
#define STEPPER2_PIN_A 9
#define STEPPER2_PIN_C 10
#define STEPPER2_PIN_B 11
#define STEPPER2_PIN_D 12



// update to match array below -- consider multiple versions commented out 
#define MAX_TARGET_IX 12
//                               0x   y   1x   y   2x   y   3x   y   4x    y    5x    y   6x   6y
int       target_coords[]  = {    12, 12,  24, 24,  36, 36,  50, 50,  150, 150,  200, 200, 250, 250,
                                  12, 12,  24, 24,  36, 36,  50, 50,  150, 150,  200, 200, 250, 250  };               


// use for blinker 
//#define    LIGHT_PIN          3 

// =============== LCD if used ===================
                              // old names
#define LCD_RS         13     // register select, pin to digital pin 12
#define LCD_ENABLE     12     // pin to digital pin 11
#define LCD_D4         8      // pin to digital pin 5
#define LCD_D5         9      // pin to digital pin 4
#define LCD_D6         10     // pin to digital pin 3
#define LCD_D7         11     // pin to digital pin 2


// ----------------------------------


    
#endif     // from the top
    

// ====================== eof ========================



