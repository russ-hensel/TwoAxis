

status

compiles lots of old and dead stuff, 







======================= code notes =========================

//  Number of pins to interface to. Integer values are supported, but it is preferred to use the MotorInterfaceType symbolic names. 
//  AccelStepper::DRIVER (1) means a stepper driver (with Step and Direction pins). If an enable line is also needed, call setEnablePin() after construction. 
//  You may also invert the pins using setPinsInverted(). AccelStepper::FULL2WIRE (2) means a 2 wire stepper (2 pins required). 
//  AccelStepper::FULL3WIRE (3) means a 3 wire stepper, such as HDD spindle (3 pins required). AccelStepper::FULL4WIRE (4) means a 4 wire stepper (4 pins required). 
//  AccelStepper::HALF3WIRE (6) means a 3 wire half stepper, such as HDD spindle (3 pins required) AccelStepper::HALF4WIRE (8) means a 4 wire half stepper (4 pins required)
//  Defaults to AccelStepper::FULL4WIRE (4) pins.

// Define some steppers and the pins the will use this version is for 2 wire driver 
// AccelStepper stepper1( AccelStepper::DRIVER, STEPPER1_STEP_PIN, STEPPER1_DIR_PIN );
// AccelStepper stepper2( AccelStepper::DRIVER, STEPPER2_STEP_PIN, STEPPER2_DIR_PIN );




========================= info on perms =====================


D:\Russ\0000\python00\python3\_projects\misc_progs\make_perms.py
short list
0  [('A', 'B', 'C', 'D'), 
1  ('A', 'B', 'D', 'C'), 
2  ('A', 'C', 'B', 'D'), 
3  ('A', 'C', 'D', 'B'), 
 4 ('A', 'D', 'B', 'C'), 
5  ('A', 'D', 'C', 'B')]
len 6
>>> 

and now from same program

============================ stepper 1 ========================



#define STEPPER1_PIN_A 5
#define STEPPER1_PIN_B 6
#define STEPPER1_PIN_C 7
#define STEPPER1_PIN_D 8

// 1  from make perms 
#define STEPPER1_PIN_A 5
#define STEPPER1_PIN_B 6
#define STEPPER1_PIN_D 7
#define STEPPER1_PIN_C 8

// 2  from make perms 
#define STEPPER1_PIN_A 5
#define STEPPER1_PIN_C 6
#define STEPPER1_PIN_B 7
#define STEPPER1_PIN_D 8

#define STEPPER1_PIN_A 5
#define STEPPER1_PIN_C 6
#define STEPPER1_PIN_D 7
#define STEPPER1_PIN_B 8

#define STEPPER1_PIN_A 5
#define STEPPER1_PIN_D 6
#define STEPPER1_PIN_B 7
#define STEPPER1_PIN_C 8

#define STEPPER1_PIN_A 5
#define STEPPER1_PIN_D 6
#define STEPPER1_PIN_C 7
#define STEPPER1_PIN_B 8



==================================== stepper 2  =======================

#define STEPPER2_PIN_A 9
#define STEPPER2_PIN_B 10
#define STEPPER2_PIN_C 11
#define STEPPER2_PIN_D 12

#define STEPPER2_PIN_A 9
#define STEPPER2_PIN_B 10
#define STEPPER2_PIN_D 11
#define STEPPER2_PIN_C 12

// 2  from make perms 
#define STEPPER2_PIN_A 9
#define STEPPER2_PIN_C 10
#define STEPPER2_PIN_B 11
#define STEPPER2_PIN_D 12

#define STEPPER2_PIN_A 9
#define STEPPER2_PIN_C 10
#define STEPPER2_PIN_D 11
#define STEPPER2_PIN_B 12

#define STEPPER2_PIN_A 9
#define STEPPER2_PIN_D 10
#define STEPPER2_PIN_B 11
#define STEPPER2_PIN_C 12

#define STEPPER2_PIN_A 9
#define STEPPER2_PIN_D 10
#define STEPPER2_PIN_C 11
#define STEPPER2_PIN_B 12



-------------------


# 0  from make perms   
#define STEPPER2_PIN_A 5
#define STEPPER2_PIN_B 6
#define STEPPER2_PIN_C 7
#define STEPPER2_PIN_D 8

# 1  from make perms 
#define STEPPER2_PIN_A 5
#define STEPPER2_PIN_B 6
#define STEPPER2_PIN_D 7
#define STEPPER2_PIN_C 8

# 2  from make perms 
#define STEPPER2_PIN_A 5
#define STEPPER2_PIN_C 6
#define STEPPER2_PIN_B 7
#define STEPPER2_PIN_D 8

# 3  from make perms 
#define STEPPER2_PIN_A 5
#define STEPPER2_PIN_C 6
#define STEPPER2_PIN_D 7
#define STEPPER2_PIN_B 8


# 4  from make perms 
#define STEPPER2_PIN_A 5
#define STEPPER2_PIN_D 6
#define STEPPER2_PIN_B 7
#define STEPPER2_PIN_C 8

// 5  from make perms 
#define STEPPER2_PIN_A 5
#define STEPPER2_PIN_D 6
#define STEPPER2_PIN_C 7
#define STEPPER2_PIN_B 8



