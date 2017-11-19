// Program description ( ):
//      TwoAxis Gimbal Control arduino using accel library 
//            or a laser cannon using geared steppers 
//      Features
//           Serial monitor control of 2 steppers on a gimbal.
//           Can aim at a target then remember the stepper position to aim at same target again         
//
// History/Status:  ( most recent at top ** done !! pending )
//        Summary:  Ver1  
//         * Ver1 started 2017 Nov 11
//         
//
// Compile info
//          "TwoAxis Ver1 2017 11 13.25":
//          Sketch uses 11,554 bytes (35%) of program storage space. Maximum is 32,256 bytes.
//          Global variables use 542 bytes (26%) of dynamic memory, leaving 1,506 bytes for local variables. Maximum is 2,048 bytes.
// 
//
// Environment:  
//    Arduino, compile with arduino.exe  1.60
//              Developed on Windows 10 64 bit
//              Running:
//              
//                   use a terminal emulator on the PC side, or the arduino serial monitor,
//                   my python smart terminal program, see 
//                     russ-hensel/python_smart_terminal: A smart serial terminal written in python
//                     https://github.com/russ-hensel/python_smart_terminal
//
//                   For configuation info see header file (.h), comm rates, ports....  ( for program version see VERSION_ID )
//                   also see readme.h which may have some information 
//
// Author:      russ_hensel http://www.opencircuits.com/User:Russ_hensel
//              
//
//     
// ============================= easy modification using #define 's ================================

#include "TwoAxis.h"          // #defines for this project
#include "SerialCmd.h"        // #defines for command interperter 

// ============================= global variables ========

SerialCmd    serialCmd;

#include <AccelStepper.h>      //  http://www.airspayce.com/mikem/arduino/AccelStepper/index.html

AccelStepper   stepper1( STEPPER_DRIVE_TYPE, STEPPER1_PIN_A, STEPPER1_PIN_B, STEPPER1_PIN_C, STEPPER1_PIN_D, true ); 
AccelStepper   stepper2( STEPPER_DRIVE_TYPE, STEPPER2_PIN_A, STEPPER2_PIN_B, STEPPER2_PIN_C, STEPPER2_PIN_D, true ); 

// save last set values  !! should be gone  replace with 1 2 
// could use array ??
float   last_acc_1;
float   last_acc_2;

// very temp for save and restore could be x or y
float   save_speed;
float   save_acc;

int     motor_ix        = 1;    // index to motor 1 or 2  x or y 
int     last_target_ix  = 1;    // index to last target 
int     last_target_x   = 0;
int     last_target_y   = 0;

// ----------------------------------------------------------------
// help just a little intro for the program -- summary of commands and version 
void rptHelp( void ) {  
    Serial.println( F( "" ) );
    Serial.print(   F( "Arduino:  " ) );  
    Serial.println( VERSION_ID  );   
    Serial.println( F( "mnn    chooseMotor  " ) );                     // case 'm':    noSub                              choose motor,  
    Serial.println( F( "tn     move to Target n  " ) );                // case 't':    targetBoth                         ( t negative no to save )
    Serial.println( F( "t-n    save Target n  " ) );                   // case 't':    saveTarget                         ( remember target )  ?? t negative no to save??
    Serial.println( F( "b      baklash adj   " ) );                    // case 'b':    backlashAdj
    Serial.println( F( "nn     cmotor nudge n  !!" ) );                //  case 'n':   adj1   adj2
    Serial.println( F( "snn    cmotor setSpeed" ) );                   // case 's':    setMaxSpeed1   setMaxSpeed2    
    Serial.println( F( "ann    cmotor setAcceleration" ) );            // case 'a'     setAcc1        setAcc2        
    Serial.println( F( "z      both motors zeroPosition" ) );          // case 'z'     for both axis  zeroPosition  
    Serial.println( F( "w      statusReport WhatWhere" ) );            //  case 'w':   what where     statusReport
    Serial.println( F( "v      Version of software" ) );               //  case '      rptVersion
    Serial.println( F( "?      Help" ) );                              //  case '?'    rptHelp

  return;
}

//     other    runThem

// ---------- Main ----------   
void loop()   {
    
    unsigned char   locCmd;
    long            cmdPriorNbr;

    serialCmd.tryRecCmd( );

    if ( serialCmd.gotCmd  )   {
     
      locCmd   = serialCmd.cmdPrior[0];     // in case access is expensive
      // lower case the command as necessary // combine with above and make sub, possibly inline -- beware special char 
      if ( ( locCmd < 97 ) && ( locCmd > 64 ) ) {
          locCmd += 32;
      }
      // decode command....
      cmdPriorNbr   = serialCmd.parseCmdNbr( serialCmd.cmdPrior );
      switch ( locCmd )  {
     
        case 'a':  // 
            if ( motor_ix == 1 ){
              setAcc1( cmdPriorNbr );
            }
            else {
              setAcc2( cmdPriorNbr );
            }
            break;
            
        case 'b':  // 
            backlashAdj(  );
            break;
            
        case 'm':  // choose motor  1  or 2, if not 2 then 1 by default
            if ( cmdPriorNbr != 2 )  {
               cmdPriorNbr = 1;
            }
            motor_ix     =  cmdPriorNbr;
            Serial.print(   F( "motor_ix = "  ) );    
            Serial.println( motor_ix );             
            break;

        case 'n':  //          
            if ( motor_ix == 1 ){
               adj1( cmdPriorNbr );
            }
            else {
               adj2( cmdPriorNbr );
            }
            break;   

      case 's':  // 
            if ( motor_ix == 1 ){
              setMaxSpeed1( cmdPriorNbr );
            }
            else {
              setMaxSpeed2( cmdPriorNbr );
            }
            break;
            
        case 't':  // 
              if ( cmdPriorNbr > 0 )  {
                   targetBoth(  cmdPriorNbr );
              } else {
                   saveTarget(  - cmdPriorNbr );
              }
              break;

         case 'v':  // report version 
            rptVersion();
            break; 

         case 'w':  //  
            statusReport( );
            break;   

         case 'z':  // !! fix me for motor 1 or 2 or do both   
            disableOutputs(   );    //  ::disableOutputs  (   )
            zeroPosition();
            break;
                 
         case '?':  // report help
            rptHelp();
            break; 
                                                  
        default:
          Serial.print( F( "!Bad Command = " ) );
          Serial.println( serialCmd.cmdPrior );
        } 
        Serial.println( F( "ok"  ) );

        serialCmd.gotCmd    = 0;
    }           
}

// ---------------------------------------------- 
void  runThem( int a_motor_ix, int a_auto_off ) {     // runThem( 1, true );
      switch ( a_motor_ix )  {
     
        case 1:  // 
            stepper1.enableOutputs( ); 
            stepper2.enableOutputs( );
            while ( stepper1.run() || stepper2.run() ) {
                // consider print for slow loops  
            }
            
//            while ( stepper1.run() ) {
//                // consider print for slow loops  
//            }
//            while ( stepper2.run() ) {
//                // consider print for slow loops  
//            }

            
            if ( a_auto_off ){
                stepper1.disableOutputs( );
                stepper2.disableOutputs( ); 
            }
            break;
            
        case 2:  // 
            stepper1.enableOutputs( ); 
            stepper2.enableOutputs( );
            while ( stepper1.run() || stepper2.run() ) {
                // consider print for slow loops  
            }
           
//            while ( stepper1.run() ) {
//                // consider print for slow loops  
//            }
//            while ( stepper2.run() ) {
//                // consider print for slow loops  
//            }
            
            if ( a_auto_off ){
                stepper1.disableOutputs( );
                stepper2.disableOutputs( ); 
            }

            break;

        default:  // this is 0 by intention and the rest 
            stepper1.enableOutputs( ); 
            stepper2.enableOutputs( );
            while ( stepper1.run() || stepper2.run() ) {
                // consider print for slow loops  
            }

            if ( a_auto_off ){
                stepper1.disableOutputs( );
                stepper2.disableOutputs( ); 
            }
        } 
}

// ---------------------------------------------- 
//    
void enableOutputs( ){
    stepper1.enableOutputs( ); 
    stepper2.enableOutputs( );
}

// ---------------------------------------------- 
void disableOutputs( ){
    stepper1.disableOutputs( );
    stepper2.disableOutputs( ); 
}

// ---------------------------------------------- 
void zeroPosition()   {
    //Serial.print(   last_target_y   );
    Serial.println( F( "Zero both motors position xy"  ) );
    stepper1.setCurrentPosition( 0 );  
    stepper1.setCurrentPosition( 0 ); 
}

// ---------------------------------------------- 
void targetBoth( int a_target_ix )  {
    int   ix;

    last_target_ix   = a_target_ix;
    ix               = 2 * a_target_ix;
    last_target_x    = target_coords[ ix     ];
    last_target_y    = target_coords[ ix + 1 ];
    Serial.print(   F( "x, y = "  ) );
    Serial.print(   last_target_x  );
    Serial.print(   F( " "  ) );
    Serial.print(   last_target_y   );
    Serial.println( F( " ... "  ) );
    stepper1.moveTo( last_target_x  ); 
    stepper2.moveTo( last_target_y  ); 
    // try to combine compute speeds to end moves at about the same time ??
    runThem( 0, true );    // 0 is both motors  else use 1 or 2 
    backlashAdj(   );
}

// ---------------------------------------------- 
void backlashAdj(   )  {
    int   adj  = 8;
    long  go_to;
    Serial.println( F( "Adj Backlash... "  ) );
    
    go_to     = stepper1.currentPosition() + adj; 
    stepper1.moveTo( go_to  ); 
    runThem( 0, true );  
    go_to    -= adj;
    stepper1.moveTo( go_to  ); 
    runThem( 0, true ); 

    go_to     = stepper2.currentPosition() + adj; 
    stepper2.moveTo( go_to  ); 
    runThem( 0, true );  
    go_to    -= adj;
    stepper2.moveTo( go_to  ); 
    runThem( 0, true );
}

// ---------------------------------------------- 
// save current position into current or specified target coords 
void saveTarget( int a_target_ix )  {
    int   ix;
    if ( a_target_ix > MAX_TARGET_IX ){
      Serial.print(   F( "Target to large, max target is " ) );
      Serial.println( MAX_TARGET_IX );
    }
    if ( a_target_ix == 0 ){
       // use current ix else set 
    } else {
       last_target_ix  = a_target_ix;
    }

    // same as last_target_x last_target_y  are these redundant ??
    ix                        = 2 * last_target_ix;
    target_coords[ ix     ]   = stepper1.currentPosition();  
    target_coords[ ix + 1 ]   = stepper2.currentPosition(); 
}

// ---------------------------------------------- 
// 
void saveArg2(  ) {
     save_speed   = stepper2.maxSpeed ();  
     save_acc     = last_acc_2;
}
    
// ---------------------------------------------- 
// nudge 
void adj1( int arg_steps  ) {
      long ret_long;
      Serial.print( F( "nudge 1 x by: " ) );
      Serial.print(  arg_steps );
      Serial.println( F( " ... " ) );
      ret_long = stepper1.currentPosition();
      ret_long += arg_steps;
      stepper1.moveTo( ret_long );
      runThem( 1, true );    // 0 is both motors  else use 1 or 2 
      Serial.print( F( "motor 1 at : " ) );
      Serial.println(  stepper1.currentPosition()  );
}

// ---------------------------------------------- 
//  
void adj2( int arg_steps  ) {
      long ret_long;
      Serial.print( F( "nudge 2 y by: " ) );
      Serial.print(  arg_steps );
      Serial.println( F( " ... " ) );
      ret_long = stepper2.currentPosition();
      ret_long += arg_steps;
      stepper2.moveTo( ret_long );
      runThem( 2, true );    // 0 is both motors  else use 1 or 2 
      Serial.print( F( "motor 2 at : " ) );
      Serial.println(  stepper2.currentPosition()  );
}

// ---------------------------------------------- 
// setMaxSpeed ( float   speed ) [in]  speed The desired maximum speed in steps per second. Must be > 0.
// maybe scaled ( avoid ui floats )  
void setMaxSpeed1( long arg_speed ) {
      float speed;

      Serial.println( arg_speed );
      speed           = arg_speed / 10.;
      stepper1.setMaxSpeed( speed );
      Serial.print( F( "setMaxSpeed1 " )  );
      Serial.println( speed );
}

// ---------------------------------------------- 
// setMaxSpeed ( float   speed ) [in]  speed The desired maximum speed in steps per second. Must be > 0.
// maybe scaled ( avoid ui floats ) 
void setMaxSpeed2( long arg_speed ) {
      float speed;

      Serial.println( arg_speed );
      speed           = arg_speed / 10.;
      stepper2.setMaxSpeed( speed );
      Serial.print( F( "setMaxSpeed2 " )  );
      Serial.println( speed );
}

// ----------------------------------------------
// maybe scaled ( avoid ui floats ) 
void setAcc1( long arg_acc ) {
      last_acc_1   = arg_acc/10;
      stepper1.setAcceleration( last_acc_1 );
      Serial.print( F( "setAcc1 " ) );
      Serial.println( last_acc_1 );
}

// ----------------------------------------------
// setAcceleration( 200.0 ); 
// maybe scaled ( avoid ui floats ) 
void setAcc2( int arg_acc ) {
      last_acc_2   = arg_acc/10;
      stepper2.setAcceleration( last_acc_2 );
      Serial.print( F( "setAcc2 " ) );
      Serial.println( last_acc_2 );
}

// ----------------------------------------------------------------
// lots of status info 
void statusReport( void ) {
    long     ret_long;
    float    ret_float;
    
    Serial.println( F( "" ) );
    Serial.println( F( "Status") );  
    Serial.println( VERSION_ID  );
    
    Serial.print( F( "Current Motor: ") ); 
      if ( motor_ix == 1 ){
        Serial.println(  "1 = x" );
      }  else {
        Serial.println(  "2 = y" );;
      }

    ret_long      = stepper1.targetPosition(   );   //  long AccelStepper::targetPosition (   ) 
    Serial.print( F( "Target Position: ") ); 
    Serial.println(  ret_long ); 

    ret_long = stepper1.currentPosition();     //  long AccelStepper::currentPosition (   )      The currently motor position.
    Serial.print( F( "Current Position 1, x : ") ); 
    Serial.println(  ret_long ); 

    ret_long = stepper2.currentPosition();     //  long AccelStepper::currentPosition (   )      The currently motor position.
    Serial.print( F( "Current Position 2, y : ") ); 
    Serial.println(  ret_long );

    ret_float = stepper1.maxSpeed ();          // float AccelStepper::maxSpeed ()     The most recently set max speed
    Serial.print( F( "Motor 1, x Speed = ") ); 
    Serial.print(  ret_float ); 
    Serial.print( F( "  Acc = ") ); 
    Serial.println(  last_acc_1 ); 

    ret_float = stepper2.maxSpeed ();          // float AccelStepper::maxSpeed ()     The most recently set max speed
    Serial.print( F( "Motor 2, Y Speed = ") ); 
    Serial.print(  ret_float ); 
    Serial.print( F( "  Acc = ") ); 
    Serial.println(  last_acc_2 ); 

    Serial.println( F( "print out targets:... ") ); 
    for( int ix_t = 1; ix_t <= MAX_TARGET_IX; ix_t = ix_t + 1 ){
        Serial.print(  "Target: " ); 
        Serial.print(  ix_t  );
        Serial.print(  " x: " );   
        Serial.print( target_coords[ 2* ix_t ] );
        Serial.print(  " y: " );   
        Serial.println( target_coords[ 2* ix_t +1 ] );
    }
    Serial.println( F( "c format for targets:... ") ); 
// look much like this 
//    int       target_coords[]  = {    12, 12,  24, 24,  36, 36,  50, 50,  150, 150,  200, 200, 250, 250,
//                                  12, 12,  24, 24,  36, 36,  50, 50,  150, 150,  200, 200, 250, 250  }; 
    Serial.print(  F( "int  target_coords[]  = { " ) );
    for( int ix_t = 1; ix_t <=  2* MAX_TARGET_IX; ix_t = ix_t + 1 ){
        //Serial.print(  "Target: " ); 
        //Serial.print(  ix_t  );
        //Serial.print(  " x: " );   
        Serial.print( target_coords[ ix_t ] );
        Serial.print(  ", " );   
    }
    Serial.println(  F( " }; " ) );
}

// ------------------------------------------------------
// ------------------------------------------------------
void rptVersion( )   {
    Serial.println( VERSION_ID  );
}

// -----------------------------------------------------
// ---------- begin setup ----------
void setup()   {
  
      Serial.begin( BAUD_RATE );
      serialCmd             = SerialCmd();
      serialCmd.resetCmd(  );
 
      delay( 1000 );     // setup time, may or may not be needed 

      // need to init stepper values  ??
      stepper1.setMaxSpeed( 1000 );
      stepper2.setMaxSpeed( 1000 ); 
      //stepper1.setAcceleration( 50  );
      setAcc1( 500 );
      setAcc2( 500 );
      rptVersion();
      Serial.println( F( "ok"  ) );
}

// ======================= eof ==============================













