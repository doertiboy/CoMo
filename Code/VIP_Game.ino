#include "definitions.h"
#include "reactionGame.h"
#include "memoryGame.h"

bool gameFinished = true;

void setup()
{ 
  Serial.begin(19200);

  //initialization of pins
  pinMode(vibration1, OUTPUT);
  pinMode(vibration2, OUTPUT);
  pinMode(vibration3, OUTPUT);
  pinMode(vibration4, OUTPUT);

  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  pinMode(button4, INPUT);
}

void loop()
{
  bool prestate1 = false;                          //variables to count button pushing and save the state of a button
  bool prestate2 = false;

  Serial.println("main menu"); 
  if (digitalRead(button1) == HIGH && !prestate1 && gameFinished) {       //checks if button 1 is pressed to start reaction game
    Serial.println("menu button 1");
    gameFinished = false;
    prestate1 = true;
    action1();                                    
    }
  else if (digitalRead(button2) == HIGH && !prestate2 && gameFinished) {  //checks if button 1 is pressed to start reaction game
    Serial.println("menu button 2");
    gameFinished = false;
    prestate2 = true;
    action2();                                           
  }
}

void vibrateAll() {
  analogWrite(vibration1, 1023);
  analogWrite(vibration2, 1023);
  analogWrite(vibration3, 1023);
  analogWrite(vibration4, 1023);
  delay(500);
  analogWrite(vibration1, 0);
  analogWrite(vibration2, 0);
  analogWrite(vibration3, 0);
  analogWrite(vibration4, 0);
  
  delay(50);
  
  analogWrite(vibration1, 1023);
  analogWrite(vibration2, 1023);
  analogWrite(vibration3, 1023);
  analogWrite(vibration4, 1023);
  delay(500);
  analogWrite(vibration1, 0);
  analogWrite(vibration2, 0);
  analogWrite(vibration3, 0);
  analogWrite(vibration4, 0);
  
  delay(50);
  
  analogWrite(vibration1, 1023);
  analogWrite(vibration2, 1023);
  analogWrite(vibration3, 1023);
  analogWrite(vibration4, 1023);
  delay(1000);
  analogWrite(vibration1, 0);
  analogWrite(vibration2, 0);
  analogWrite(vibration3, 0);
  analogWrite(vibration4, 0);
}
