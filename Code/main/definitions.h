#ifndef definitions
#define definitions

//include libaries
#include <Arduino.h>

//names and pinnumbers of fixed variables for arduino nano
//button variables
#define button1 A0
#define button2 A1
#define button3 A2 
#define button4 A3
#define buttonThumbLeft A6
#define buttonThumbRight A7

//vibration motor variables
#define vibration1 3
#define vibration2 5
#define vibration3 6
#define vibration4 9
#define vibrationThumbLeft 10
#define vibrationThumbRight 11

// condition to go into main menu after the game is finished
extern bool gameFinished;
extern void vibrateAll();

// thumb button variable 
extern int buttonThumb;
extern int vibrationThumb;
extern int vibrations[];

#endif
