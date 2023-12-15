#include "reactionGame.h"
#include "definitions.h"
//#include "show.h"

int rndNumber = 0;
int rndNumberOld = 0;
int vibration = 0;
int cntWrong = 0;
bool correctButton;
unsigned long starttimer, stoptimer, time, buttonTimer, buttonStartTimer, buttonEndTimer, s, nachkommastelle;

void action1() {
  // initialization
  buttonTimer = 0;
  buttonStartTimer = 0;
  buttonEndTimer = 0;
  correctButton = false;
  prestate1 = false;
  prestate2 = false;
  prestate3 = false;
  prestate4 = false;
  prestateThumb = false;

  delay(200); //vibration does not start early

  //game ends after 10 buttons are pushed
  for (int i = 0; i < 10; i++) {
    // start timer after 1st pushed button
    if (i == 1) {
      starttimer = millis();
    }
    generateRandomVibration();
    checkUserInput(); 
    delay(100);  
  }
  stopTimer();
  gameFinished = true;
}

/**
 * generates a random vibration
 * generates a random number and compares it to the last one to not select the same pin again
 * sets the according pin to SPEED to activate the vibration motor
*/
void generateRandomVibration() {
  rndNumberOld = rndNumber;
  int index = random(0, 5);       //generates a random index
  rndNumber = vibrations[index];  //generates a random vibration

  if (rndNumber == rndNumberOld) {                        //if second random number is same as first than find a new second random number
    while (rndNumber == rndNumberOld){                    //that first random number is not the same as second random number
      index = random(0, 5); 
      rndNumber = vibrations[index];
    }
    analogWrite(rndNumber, SPEED);
    Serial.println(rndNumber);
    
  }
  else {                                           //if it is not the same, start vibration motor
    analogWrite(rndNumber, SPEED);
    Serial.println(rndNumber);
  }
}

/**
 * checks the pushed buttons of the user and compares them to the randomized vibration
 * leaves while loop if vibration and button of the same finger are set to high
*/
void checkUserInput() {
  Serial.println("check user input");
  bool state = false;
  correctButton = false;
  prestate1 = false;
  prestate2 = false;
  prestate3 = false;
  prestate4 = false;
  prestateThumb = false;

  while (!state) { 
    if (rndNumber == vibration1) { //analogRead(vibration1) == SPEED
      if(analogRead(button1) >= THRESHOLD) {
        buttonStartTimer = millis();  //start timer for pushing state of button     
        analogWrite(vibration1, 0);   //turns off vibration motor
        correctButton = true;         //sets variable to remeber the right button had been pushed
      }
      // checks if another button is pushed and increments cntWrong 
      else if ((analogRead(button2) >= THRESHOLD) && !prestate2){
        cntWrong ++;
        prestate2 = true;
      }
      else if ((analogRead(button3) >= THRESHOLD) && !prestate3){
        cntWrong ++;
        prestate3 = true;
      }
      else if ((analogRead(button4) >= THRESHOLD) && !prestate4){
        cntWrong ++;
        prestate4 = true;
      }
      else if ((analogRead(buttonThumb) >= THRESHOLD) && !prestateThumb){
        cntWrong ++;
        prestateThumb = true;
      } 
    }

    else if (rndNumber == vibration2) { //analogRead(vibration2) == SPEED
      if (analogRead(button2) >= THRESHOLD) {
        buttonStartTimer = millis();  //start timer for pushing state of button     
        analogWrite(vibration2, 0);   //turns off vibration motor
        correctButton = true;         //sets variable to remeber the right button had been pushed
      }    
      // checks if another button is pushed and increments cntWrong 
      else if ((analogRead(button1) >= THRESHOLD) && !prestate1){
        cntWrong ++;
        prestate1 = true;
      }
      else if ((analogRead(button3) >= THRESHOLD) && !prestate3){
        cntWrong ++;
        prestate3 = true;
      }
      else if ((analogRead(button4) >= THRESHOLD) && !prestate4){
        cntWrong ++;
        prestate4 = true;
      }
      else if ((analogRead(buttonThumb) >= THRESHOLD) && !prestateThumb){
        cntWrong ++;
        prestateThumb = true;
      }   
    }
    
    else if (rndNumber == vibration3) {  //analogRead(vibration3) == SPEED
      if (analogRead(button3) >= THRESHOLD) {
        buttonStartTimer = millis();  //start timer for pushing state of button     
        analogWrite(vibration3, 0);   //turns off vibration motor
        correctButton = true;         //sets variable to remeber the right button had been pushed
      }    
      // checks if another button is pushed and increments cntWrong 
      else if ((analogRead(button1) >= THRESHOLD) && !prestate1){
        cntWrong ++;
        prestate1 = true;
      }
      else if ((analogRead(button2) >= THRESHOLD) && !prestate2){
        cntWrong ++;
        prestate2 = true;
      }
      else if ((analogRead(button4) >= THRESHOLD) && !prestate4){
        cntWrong ++;
        prestate4 = true;
      } 
      else if ((analogRead(buttonThumb) >= THRESHOLD) && !prestateThumb){
        cntWrong ++;
        prestateThumb = true;
      }  
    }
    
    else if (rndNumber == vibration4) { //analogRead(vibration4) == SPEED
      if (analogRead(button4) >= THRESHOLD) {
        buttonStartTimer = millis();  //start timer for pushing state of button     
        analogWrite(vibration4, 0);   //turns off vibration motor
        correctButton = true;         //sets variable to remeber the right button had been pushed
      }    
      // checks if another button is pushed and increments cntWrong 
      else if ((analogRead(button1) >= THRESHOLD) && !prestate1){
        cntWrong ++;
        prestate1 = true;
      }
      else if ((analogRead(button2) >= THRESHOLD) && !prestate2){
        cntWrong ++;
        prestate2 = true;
      }
      else if ((analogRead(button3) >= THRESHOLD) && !prestate3){
        cntWrong ++;
        prestate3 = true;
      }  
      else if ((analogRead(buttonThumb) >= THRESHOLD) && !prestateThumb){
        cntWrong ++;
        prestateThumb = true;
      }  
    }
    else if (rndNumber == vibrationThumb) { // analogRead(vibrationThumb) == SPEED
      if (analogRead(buttonThumb) >= THRESHOLD) {
        buttonStartTimer = millis();  //start timer for pushing state of button     
        analogWrite(vibrationThumb, 0);   //turns off vibration motor
        correctButton = true;         //sets variable to remeber the right button had been pushed
      }    
      // checks if another button is pushed and increments cntWrong 
      else if ((analogRead(button1) >= THRESHOLD) && !prestate1){
        Serial.println("wrong");
        cntWrong ++;
        prestate1 = true;
        delay(100);
      }
      else if ((analogRead(button2) >= THRESHOLD) && !prestate2){
        cntWrong ++;
        prestate2 = true;
      }
      else if ((analogRead(button3) >= THRESHOLD) && !prestate3){
        cntWrong ++;
        prestate3 = true;
      }  
      else if ((analogRead(button4) >= THRESHOLD) && !prestate4){
        cntWrong ++;
        prestate4 = true;
      } 
    }
    // only leave while loop if correct button has been pushed and is released again to avoid wrong counting in next iteration
    if ((analogRead(button1) <= ZERO && analogRead(button2) <= ZERO && analogRead(button3) <= ZERO && analogRead(button4) <= ZERO && analogRead(buttonThumb) <= ZERO) && correctButton){
      // end button timer and sum it up
      buttonEndTimer = millis();
      buttonTimer += (buttonEndTimer - buttonStartTimer);            
      state = true;
    }
    if ((analogRead(button1) || analogRead(button2) || analogRead(button3) || analogRead(button4) || analogRead(buttonThumb)) >= ZERO){ // or threshold??
      prestate1 = false;
      prestate2 = false;
      prestate3 = false;
      prestate4 = false;
      prestateThumb = false;
    }
  }        
}

void stopTimer() {
  stoptimer = millis();
  time = stoptimer - starttimer - buttonTimer - 900;  // 900 ms delay in for loop
  s = time / 1000;                                    //calculation to get the needed time in seconds
  nachkommastelle = (time - (s * 1000)) / 100;        //calculation to get the decimale place of the number

  Serial.print("Time: ");
  Serial.println(time);
  Serial.print("wrong Buttons: ");
  Serial.println(cntWrong);
}
