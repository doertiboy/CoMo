// TO DO
// measure time
// count wrong pushes

#include "reactionGame.h"
#include "definitions.h"

int zufall1 = 0;
int zufall2 = 0;
int vibration = 0;

void action1() {
  delay(500); //vibration does not start early
  
  //game ends after 10 buttons are pushed
  for (int i = 0; i < 10; i++) {
    generateRandomVibration();
    checkUserInput(); 
    delay(100);  
  }
  gameFinished = true;
  delay(1000);
  vibrateAll();
}

/**
 * generates a random vibration
 * generates a random number and compares it to the last one to not select the same pin again
 * sets the according pin to HIGH to activate the vibration motor
*/
void generateRandomVibration() {
  zufall2 = zufall1;
  vibration = zufall2;
  int index = random(0, 5);       //generates a random index
  zufall1 = vibrations[index];    //generates a random vibration

  if (zufall1 == zufall2) {                        //if second random number is same as first than find a new second random number
    while (zufall1 == zufall2){                    //that first random number is not the same as second random number
      index = random(0, 5); 
      zufall1 = vibrations[index];
    }
    analogWrite(zufall1, 1023);
  }
  else {                                           //if it is not the same, start vibration motor
    analogWrite(zufall1, 1023);
    Serial.println(zufall1);
  }
}

/**
 * checks the pushed buttons of the user and compares them to the randomized vibration
 * leaves while loop if vibration and button of the same finger are set to high
*/
void checkUserInput() {
  Serial.println("check user input");
  bool state = false;
  while (!state) { 
    if (digitalRead(vibration1) && digitalRead(button1)) { // digitalRead(vibration1) == HIGH       
      //turns off vibration motor
      analogWrite(vibration1, 0);
      state = true;                 //sets variable to remeber the right button had been pushed
    }

    else if (digitalRead(vibration2) && digitalRead(button2)) {  
      //turns off vibration motor
      analogWrite(vibration2, 0);
      state = true;                 //sets variable to remeber the right button had been pushed
    }
    
    else if (digitalRead(vibration3) && digitalRead(button3)) {  
      //turns off vibration motor
      analogWrite(vibration3, 0);
      state = true;                 //sets variable to remeber the right button had been pushed
    }
    
    else if (digitalRead(vibration4) && digitalRead(button4)) {  
      //turns off vibration motor
      analogWrite(vibration4, 0);
      state = true;                 //sets variable to remeber the right button had been pushed
    }
    else if (digitalRead(vibrationThumb) && digitalRead(buttonThumb)) {  
      //turns off vibration motor
      analogWrite(vibrationThumb, 0);
      state = true;                 //sets variable to remeber the right button had been pushed
    }
  }        
}

void vibrateReactionStart() {
  analogWrite(vibration1, 1023);
  analogWrite(vibration2, 1023);
  analogWrite(vibration3, 1023);
  analogWrite(vibration4, 1023);
  analogWrite(vibrationThumb, 1023);
  delay(500);
  analogWrite(vibration1, 0);
  analogWrite(vibration2, 0);
  analogWrite(vibration3, 0);
  analogWrite(vibration4, 0);
  analogWrite(vibrationThumb, 0);
  delay(500);
}