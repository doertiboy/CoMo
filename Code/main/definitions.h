#ifndef definitions
#define definitions

//include libaries
#include <Arduino.h>
// #include <Wire.h>
// #include <Adafruit_GFX.h>
// #include <Adafruit_SSD1306.h>

// OLED 
// #define SCREEN_WIDTH 128 // OLED display width,  in pixels
// #define SCREEN_HEIGHT 64 // OLED display height, in pixels
// // extern Adafruit_SSD1306 oled;
// // display menu
#define menuReaction 10
#define menuMemory 35

//names and pinnumbers of fixed variables for arduino nano
//button variables
#define button1 A0
#define button2 A1
#define button3 A2 
#define button4 A3
#define buttonThumbLeft A6
#define buttonThumbRight A7
// threshold for analog button readout
#define THRESHOLD 700
#define ZERO 100

//vibration motor variables
#define vibration1 3
#define vibration2 5
#define vibration3 6
#define vibration4 9
#define vibrationThumbLeft 10
#define vibrationThumbRight 11
#define SPEED 1023

// condition to go into main menu after the game is finished
extern bool gameFinished;
extern void vibrateAll();

// thumb button variable 
extern int buttonThumb;
extern int vibrationThumb;
extern int vibrations[];

//flags for button pushes
extern bool prestate1;
extern bool prestate2;
extern bool prestate3;
extern bool prestate4;
extern bool prestateThumb;

#endif
