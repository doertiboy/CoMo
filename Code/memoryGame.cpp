#include "memoryGame.h"
#include "definitions.h"

const int MAX_LEVEL  = 100;
int sequence[MAX_LEVEL];
int your_sequence[MAX_LEVEL];
int level  = 1;

//flags for button pushes
bool prestate1;
bool prestate2;
bool prestate3;
bool prestate4;

void action2()
{
  delay(500);

  //vibrateMemoryStart();

  Serial.println("action2");
  //set button flags to false
  prestate1 = false;                            
  prestate2 = false;
  prestate3 = false;
  prestate4 = false;
  gameFinished = false;
  level = 1;
  
  if  (level == 1){
    generate_sequence();
    delay(1000); //that vibration does not start early
  } 
  
  Serial.println("start");
  for (int i = 0; i < level; i++){
    show_sequence();    
    get_sequence();

    if (gameFinished) {
      vibrateAll();
      break;
    }
  }
}

/**
 * shows the sequence by vibrating the buttons in the correct order
 */
void show_sequence()
{ 
  vibrationOff();

  for (int i = 0; i < level; i++)
  {
    Serial.println(sequence[i]);
    analogWrite(sequence[i],  1023);
    delay(500);
    analogWrite(sequence[i], 0);
    delay(150);
  }
}

/**
 * reads the input sequence of the user and evaluates it 
*/
void get_sequence()
{ 
  // flag that indicates if the sequence is correct
  bool state = false;
  
  for  (int i = 0; i < level; i++)
  {
    state = false;
    while(!state)
    {
      if (digitalRead(button1) == HIGH && !prestate1)
      {
        Serial.println("get sequence 1");
        // analogWrite(vibration1, 1023);  
        prestate1 = true;
        state = true;
        delay(500);
        if  (vibration1 != sequence[i])
        {
          wrong_sequence();
          return;
        }
        // analogWrite(vibration1,  0);
      }
      
      if (digitalRead(button2) == HIGH && !prestate2) 
      {
        prestate2 = true;
        Serial.println("get sequence 2");
        // analogWrite(vibration2, 1023); 
        state = true;
        delay(500);
        if (vibration2 != sequence[i])
        {
          wrong_sequence();
          return;
        }
        // analogWrite(vibration2,  0); 
      }
      
      if (digitalRead(button3) == HIGH && !prestate3) 
      {
        Serial.println("get sequence 3");
        // analogWrite(vibration3, 1023); 
        prestate3 = true;
        state = true;
        delay(500);
        if (vibration3 != sequence[i])
        {
          wrong_sequence();
          return;
        }
        // analogWrite(vibration3,  0); 
      }
      
      if (digitalRead(button4) == HIGH && !prestate4) 
      {
        Serial.println("get sequence 4");
        // analogWrite(vibration4, 1023); 
        prestate4 = true;
        state = true;
        delay(500);
        if (vibration4 != sequence[i])
        {
          wrong_sequence();
          return;
        }
        // analogWrite(vibration4,  0);
      }
      
      if ((digitalRead(button1) || digitalRead(button2) || digitalRead(button3) || digitalRead(button4)) == LOW){
        prestate1 = false;
        prestate2 = false;
        prestate3 = false;
        prestate4 = false;
      }
    }
  }
  right_sequence();
}

/**
 * generates a sequence and saves it into an array
*/
void generate_sequence()
{
  Serial.println("generate sequence");
  randomSeed(millis());  
  for (int i = 0; i < MAX_LEVEL; i++)
  {
    sequence[i]  = random(vibration1, vibration4 + 1); //7, 11
  } 
}

/**
 * turns the vibration off and sets the finished flag to true
*/
void wrong_sequence()
{
  Serial.println("wrong sequence");
  vibrationOff();
  delay(3000);
  
  gameFinished = true; 
}

/**
 * increments the level 
*/
void right_sequence()
{
  Serial.println("right sequence");
  delay(100); 
  if  (level < MAX_LEVEL) {
    level++;
  }
  else {
    gameFinished = true;
    vibrateAll();
  } 
} 

/**
 * turns off all the vibration motors
*/
void vibrationOff() {
  analogWrite(vibration1, 0); 
  analogWrite(vibration2, 0); 
  analogWrite(vibration3, 0); 
  analogWrite(vibration4, 0); 
}

void vibrateMemoryStart() {
  analogWrite(vibration1, 1023);
  analogWrite(vibration2, 1023);
  analogWrite(vibration3, 1023);
  analogWrite(vibration4, 1023);
  delay(500);
  analogWrite(vibration1, 0);
  analogWrite(vibration2, 0);
  analogWrite(vibration3, 0);
  analogWrite(vibration4, 0);
  delay(100);
  analogWrite(vibration1, 1023);
  analogWrite(vibration2, 1023);
  analogWrite(vibration3, 1023);
  analogWrite(vibration4, 1023);
  delay(500);
  analogWrite(vibration1, 0);
  analogWrite(vibration2, 0);
  analogWrite(vibration3, 0);
  analogWrite(vibration4, 0);
  delay(500);
}
