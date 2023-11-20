// TO DO 
// excel file output

#include "definitions.h"
#include "reactionGame.h"
#include "memoryGame.h"

bool gameFinished = true;
bool thumbRecognition = false;
bool prestateScroll = false;
bool prestateSelect = false;

int buttonThumb;
int vibrationThumb;
int buttonScroll;
int vibrations[5];
int menu = 1;

// declare an SSD1306 display object connected to I2C
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup()
{ 
  Serial.begin(19200);
  //initialization of pins
  pinMode(vibration1, OUTPUT);
  pinMode(vibration2, OUTPUT);
  pinMode(vibration3, OUTPUT);
  pinMode(vibration4, OUTPUT);
  pinMode(vibrationThumbLeft, OUTPUT);
  pinMode(vibrationThumbRight, OUTPUT);

  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  pinMode(button4, INPUT);
  pinMode(buttonThumbLeft, INPUT);
  pinMode(buttonThumbRight, INPUT);

  // initialize OLED display with address 0x3C for 128x64
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true);
  }
  delay(2000);         // wait for initializing

  showComo();
  selectThumb();
  initialize();
}

void loop()
{
  updateMenu();

  // scroll menu
  if (analogRead(buttonScroll) >= THRESHOLD && !prestateScroll) {
    menu++;
    if (menu > 2) {
      menu = 1;
    }
    updateMenu();
    prestateScroll = true;
  }
  else {
    prestateScroll = false;
  }

  // select game
  if(analogRead(buttonThumb) >= THRESHOLD && !prestateSelect) {
    startGame();
    prestateSelect = true;
  }
  else {
    prestateSelect = false;
  }

  delay(100);
}

// ----------------------------------------- FUNCTIONS ----------------------------------------

void selectThumb() {
  showThumb();
  while(!thumbRecognition) {
    if(analogRead(buttonThumbLeft) >= THRESHOLD) {
      buttonThumb = buttonThumbLeft;
      vibrationThumb = vibrationThumbLeft;
      buttonScroll = A0;
      oled.clearDisplay();
      oled.setCursor(10, 20);
      oled.setTextSize(3);
      oled.println("RECHTS");
      oled.display();
      delay(1500);
      thumbRecognition = true;
    }
    else if (analogRead(buttonThumbRight) >= THRESHOLD) {
      buttonThumb = buttonThumbRight;
      vibrationThumb = vibrationThumbRight;
      buttonScroll = A3;
      oled.clearDisplay();
      oled.setCursor(20, 20);
      oled.setTextSize(3);
      oled.println("LINKS");
      oled.display();
      delay(1500);
      thumbRecognition = true;
    }
  }
}

void showComo() {
  oled.clearDisplay(); 
  oled.setTextSize(5);         
  oled.setTextColor(WHITE);     
  oled.setCursor(7, 15);       
  oled.println("COMO");        
  oled.display(); 
  delay(5000);           
}

void showThumb() {
  oled.clearDisplay(); 
  oled.setTextSize(3);          
  oled.setTextColor(WHITE);     
  oled.setCursor(13, 10);       
  oled.println("Daumen");        
  oled.setTextSize(2);          
  oled.setCursor(17, 40);       
  oled.println("druecken");        
  oled.display();               
}

void showMenu(int game) {
  oled.clearDisplay(); 
  oled.setTextSize(2);          
  oled.setTextColor(WHITE);     
  oled.setCursor(1, game);       
  oled.println(">");  
  oled.setCursor(20, 10); 
  oled.println("Reaktion");  
  oled.setCursor(20, 35);       
  oled.println("Merken");
  oled.display();  
}

void showReactionStart() {
  oled.clearDisplay(); 
  oled.setTextSize(2);         
  oled.setTextColor(WHITE);     
  oled.setCursor(10, 10);       
  oled.println("REAKTIONS");   
  oled.setTextSize(3);   
  oled.setCursor(20, 35);      
  oled.println("SPIEL");      
  oled.display();   
  delay(2000);  
}

void showMemoryStart() {
  oled.clearDisplay(); 
  oled.setTextSize(3);         
  oled.setTextColor(WHITE);     
  oled.setCursor(30, 10);       
  oled.println("MERK");     
  oled.setCursor(20, 35);       
  oled.println("SPIEL");      
  oled.display();  
  delay(2000);     
}

void updateMenu () {
  switch (menu) {
    case 1:
      showMenu(menuReaction);
      break;
    case 2:
      showMenu(menuMemory);
      break;
  }
}

void startGame() {
  switch (menu) {
    case 1: 
      showReactionStart();
      // action1();
      break;
    case 2: 
      showMemoryStart();
      // action2();
      break;
  }
}

void initialize() {
  vibrations[0] = vibration1;
  vibrations[1] = vibration2;
  vibrations[2] = vibration3;
  vibrations[3] = vibration4;
  vibrations[4] = vibrationThumb;
}

void vibrateAll() {
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
  
  delay(50);
  
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
  
  delay(50);
  
  analogWrite(vibration1, 1023);
  analogWrite(vibration2, 1023);
  analogWrite(vibration3, 1023);
  analogWrite(vibration4, 1023);
  analogWrite(vibrationThumb, 1023); 
  delay(1000);
  analogWrite(vibration1, 0);
  analogWrite(vibration2, 0);
  analogWrite(vibration3, 0);
  analogWrite(vibration4, 0);
  analogWrite(vibrationThumb, 0); 
}