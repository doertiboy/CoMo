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
// Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

Adafruit_NeoPixel leds(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

//flags for button pushes
bool prestate1;
bool prestate2;
bool prestate3;
bool prestate4;
bool prestateThumb;

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

  // // initialize OLED display with address 0x3C for 128x64
  // if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
  //   Serial.println(F("SSD1306 allocation failed"));
  //   while (true);
  // }
  // delay(2000);         // wait for initializing

  // showComo();
  leds.begin();           // INITIALIZE NeoPixel leds object (REQUIRED)
  leds.show();            // Turn OFF all pixels ASAP
  leds.setBrightness(BRIGHTNESS);
  rainbowFade2White(3, 3, 1);
  
  selectThumb();
  initialize();
}

void loop()
{
  updateMenu();

  // scroll menu
  if (analogRead(buttonScroll) > THRESHOLD && !prestateScroll) {
    menu++;
    if (menu > 2) {
      menu = 1;
    }
    updateMenu();
    prestateScroll = true;
    Serial.print("analogRead: ");
    Serial.println(analogRead(buttonScroll));
    Serial.print("prestate: ");
    Serial.println(prestateScroll);
    delay(500);
  }
  else if (analogRead(buttonScroll) < THRESHOLD){
    Serial.println("set prestate to 0");
    prestateScroll = false;
  }

  // select game
  if (analogRead(buttonThumb) >= THRESHOLD && !prestateSelect) {
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
  while (!thumbRecognition) {
    if (analogRead(buttonThumbLeft) >= THRESHOLD) {
      buttonThumb = buttonThumbLeft;
      vibrationThumb = vibrationThumbLeft;
      buttonScroll = A0;
      Serial.println("rechts");
      // oled.clearDisplay();
      // oled.setCursor(10, 20);
      // oled.setTextSize(3);
      // oled.println("RECHTS");
      // oled.display();
      delay(1500);
      thumbRecognition = true;
    }
    else if (analogRead(buttonThumbRight) >= THRESHOLD) {
      buttonThumb = buttonThumbRight;
      vibrationThumb = vibrationThumbRight;
      buttonScroll = A3;
      Serial.println("links");
      // oled.clearDisplay();
      // oled.setCursor(20, 20);
      // oled.setTextSize(3);
      // oled.println("LINKS");
      // oled.display();
      delay(1500);
      thumbRecognition = true;
    }
  }
}

// void showComo() {
//   oled.clearDisplay();
//   oled.setTextSize(5);
//   oled.setTextColor(WHITE);
//   oled.setCursor(7, 15);
//   oled.println("COMO");
//   oled.display();
//   delay(5000);
// }

void showThumb() {
  Serial.println("daumen drücken");
  //   oled.clearDisplay();
  //   oled.setTextSize(3);
  //   oled.setTextColor(WHITE);
  //   oled.setCursor(13, 10);
  //   oled.println("Daumen");
  //   oled.setTextSize(2);
  //   oled.setCursor(17, 40);
  //   oled.println("druecken");
  //   oled.display();
  //
}

void showMenu(int game) {
  // oled.clearDisplay();
  // oled.setTextSize(2);
  // oled.setTextColor(WHITE);
  // oled.setCursor(1, game);
  // oled.println(">");
  // oled.setCursor(20, 10);
  // oled.println("Reaktion");
  // oled.setCursor(20, 35);
  // oled.println("Merken");
  // oled.display();
  Serial.print("main menu: ");
  Serial.println(game == 10 ? "reaction" : "memory");
}

void showReactionStart() {
  // oled.clearDisplay();
  // oled.setTextSize(2);
  // oled.setTextColor(WHITE);
  // oled.setCursor(10, 10);
  // oled.println("REAKTIONS");
  // oled.setTextSize(3);
  // oled.setCursor(20, 35);
  // oled.println("SPIEL");
  // oled.display();
  Serial.println("reactionsspiel start");
  delay(2000);
}

void showMemoryStart() {
  // oled.clearDisplay();
  // oled.setTextSize(3);
  // oled.setTextColor(WHITE);
  // oled.setCursor(30, 10);
  // oled.println("MERK");
  // oled.setCursor(20, 35);
  // oled.println("SPIEL");
  // oled.display();
  Serial.println("memoryspiel start");
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
      action1();
      break;
    case 2:
      showMemoryStart();
      action2();
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

void rainbowFade2White(int wait, int rainbowLoops, int whiteLoops) {
  int fadeVal=0, fadeMax=100;
  
  for(uint32_t firstPixelHue = 0; firstPixelHue < rainbowLoops*65536;
    firstPixelHue += 256) {

    for(int i=0; i<leds.numPixels(); i++) { // For each pixel in leds...
      uint32_t pixelHue = firstPixelHue + (i * 65536L / leds.numPixels());
      leds.setPixelColor(i, leds.gamma32(leds.ColorHSV(pixelHue, 255,
        255 * fadeVal / fadeMax)));
    }

    leds.show();
    delay(wait);

    if(firstPixelHue < 65536) {                              // First loop,
      if(fadeVal < fadeMax) fadeVal++;                       // fade in
    } else if(firstPixelHue >= ((rainbowLoops-1) * 65536)) { // Last loop,
      if(fadeVal > 0) fadeVal--;                             // fade out
    } else {
      fadeVal = fadeMax; // Interim loop, make sure fade is at max
    }
  }

  for(int k=0; k<whiteLoops; k++) {
    for(int j=0; j<256; j++) { // Ramp up 0 to 255
      // Fill entire leds with white at gamma-corrected brightness level 'j':
      leds.fill(leds.Color(0, 0, 0, leds.gamma8(j)));
      leds.show();
    }
    delay(1000); // Pause 1 second
    for(int j=255; j>=0; j--) { // Ramp down 255 to 0
      leds.fill(leds.Color(0, 0, 0, leds.gamma8(j)));
      leds.show();
    }
  }

  delay(500); 
}
