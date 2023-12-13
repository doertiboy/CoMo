#ifndef definitions
#define definitions

//include libaries
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
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

// LEDs
#define LED_PIN 12
#define LED_COUNT 6
#define BRIGHTNESS 50 // Set BRIGHTNESS to about 1/5 (max = 255)

//names and pinnumbers of fixed variables for arduino nano
//button variables
#define button1 A0 //rot
#define button2 A1 //grün
#define button3 A2 //gelb
#define button4 A3 //blau
#define buttonThumbLeft A7 //orange
#define buttonThumbRight A6 //orange
// threshold for analog button readout
#define THRESHOLD 300
#define ZERO 50

//vibration motor variables
#define vibration1 3 //rot
#define vibration2 5 //grün
#define vibration3 6 //gelb
#define vibration4 9 //blau
#define vibrationThumbLeft 11 //orange
#define vibrationThumbRight 10 //orange
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

extern Adafruit_NeoPixel leds;

#endif
