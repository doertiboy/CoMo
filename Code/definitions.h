#ifndef definitions
#define definitions

//include libaries
#include <Arduino.h>

//names and pinnumbers of fixed variables
//button variables
#define button1 3
#define button2 4
#define button3 5 
#define button4 6

//vibration motor variables
#define vibration1 7
#define vibration2 8
#define vibration3 9
#define vibration4 10

// condition to go into main menu after the game is finished
extern bool gameFinished;
extern void vibrateAll();

#endif
