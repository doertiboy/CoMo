#include "memoryGame.h"
#include "definitions.h"

const int MAX_LEVEL  = 100;
int sequenceVib[MAX_LEVEL];
int sequenceLed[MAX_LEVEL];
int your_sequence[MAX_LEVEL];
int level  = 1;


void action2()
{
  delay(500);
  
  Serial.println("action2");
  //set button flags to false
  prestate1 = false;
  prestate2 = false;
  prestate3 = false;
  prestate4 = false;
  prestateThumb = false;
  gameFinished = false;
  level = 1;

  if  (level == 1) {
    generate_sequence();
    delay(1000); //that vibration does not start early
  }

  Serial.println("start");
  for (int i = 0; i < level; i++) {
    show_sequence();
    get_sequence();

    if (gameFinished) {
      break;
    }
  }
}

/**
   shows the sequence by vibrating the buttons in the correct order
*/
void show_sequence()
{
  vibrationOff();

  for (int i = 0; i < level; i++) {
    switch (mode) {
      case vib:
        analogWrite(sequenceVib[i],  SPEED);
        delay(500);
        analogWrite(sequenceVib[i], 0);
        delay(150);
        break;
      case led:
        ledOn(sequenceLed[i]);
        delay(500);
        ledOff();
        delay(150);
        break;
      case both:
        analogWrite(sequenceVib[i],  SPEED);
        ledOn(sequenceLed[i]);
        delay(500);
        analogWrite(sequenceVib[i], 0);
        ledOff();
        delay(150);
        break;
    }
  }
}

/**
   reads the input sequence of the user and evaluates it
*/
void get_sequence()
{
  // flag that indicates if the sequence is correct
  bool state = false;

  for  (int i = 0; i < level; i++)
  {
    state = false;
    while (!state)
    {
      if (getFinger1() > THRESHOLD && !prestate1)
      {
        Serial.println("user pushed 1");
        prestate1 = true;
        state = true;
        delay(500);
        if (vibration1 != sequenceVib[i] || led1 != sequenceLed[i]) {
          wrong_sequence();
          return;
        }
      }

      if (getFinger2() > THRESHOLD && !prestate2)
      {
        prestate2 = true;
        Serial.println("user pushed 2");
        state = true;
        delay(500);
        if (vibration2 != sequenceVib[i] || led2 != sequenceLed[i])
        {
          wrong_sequence();
          return;
        }
      }

      if (getFinger3() > THRESHOLD && !prestate3)
      {
        Serial.println("user pushed 3");
        prestate3 = true;
        state = true;
        delay(500);
        if (vibration3 != sequenceVib[i] || led3 != sequenceLed[i])
        {
          wrong_sequence();
          return;
        }
      }

      if (getFinger4() > THRESHOLD && !prestate4)
      {
        Serial.println("user pushed 4");
        prestate4 = true;
        state = true;
        delay(500);
        if (vibration4 != sequenceVib[i] || led4 != sequenceLed[i])
        {
          wrong_sequence();
          return;
        }
      }

      if (getThumb() > THRESHOLD && !prestateThumb)
      {
        Serial.println("user pushed 4");
        prestateThumb = true;
        state = true;
        delay(500);
        if (vibrationThumb != sequenceVib[i] || ledThumb != sequenceLed[i])
        {
          wrong_sequence();
          return;
        }
      }

      if ((getFinger1() < THRESHOLD) && (getFinger2() < THRESHOLD) && (getFinger3() < THRESHOLD) && (getFinger4() < THRESHOLD) && (getThumb() < THRESHOLD)) {
        prestate1 = false;
        prestate2 = false;
        prestate3 = false;
        prestate4 = false;
        prestateThumb = false;
      }
    }
  }
  right_sequence();
}

/**
   generates a sequence and saves it into an array
*/
void generate_sequence()
{
  Serial.println("generate sequence");
  randomSeed(millis());
  for (int i = 0; i < MAX_LEVEL; i++)
  {
    int index = random(0, 5);
    sequenceVib[i] = vibrations[index];
    sequenceLed[i] = ledArray[index];
  }
}

/**
   turns the vibration off and sets the finished flag to true
*/
void wrong_sequence()
{
  Serial.println("wrong sequence");
  vibrationOff();
  ledOff();
  delay(3000);

  gameFinished = true;
}

/**
   increments the level
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
  }
}

/**
   turns off all the vibration motors
*/
void vibrationOff() {
  analogWrite(vibration1, 0);
  analogWrite(vibration2, 0);
  analogWrite(vibration3, 0);
  analogWrite(vibration4, 0);
}
