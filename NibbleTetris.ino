//Tetris clone for the Nibble gaming console
//Sinisa Dosen. Mar. 2021. - Jan. 2023.

//#include <Arduino.h>
#include <CircuitOS.h>
#include <Nibble.h>
//#include <EEPROM.h>

#include "include/defines.h"
#include "include/variables.h"
#include "include/tetrominos.h"
#include "include/audio.h"

//Game version
#define GAME_VERSION    "1.0"

//For debugging purposes
//#define DEBUG

//For testing purposes
//#define TEST_CLEARANCE

Display* display;
Sprite* sprite;

void setup() {
#ifdef DEBUG
  Serial.begin(115200);
  Serial.println();
  
  //Wait a while for terminal to be available.
  //I'm not sure who's at fault here (Arduino, ESP, USB-TTL) but we have to wait
  delay(1000);
  
  Serial.println("Debugging started.");
  Serial.print("Free heap: ");
  Serial.println(ESP.getFreeHeap());
#endif

  Nibble.begin();
  display = Nibble.getDisplay();
  sprite = display->getBaseSprite();

  RegisterButtonCallbacks();
  randomSeed(millis());

#ifdef DEBUG
  Serial.print("Free heap after init: ");
  Serial.println(ESP.getFreeHeap());
  Serial.flush();
#endif
}

void loop() {
  currentMillis = millis();
  
  Input::getInstance()->loop(0);

#ifdef DEBUG
  ScreenCapHandler();
#endif

  //Frame counting
  if (currentMillis - previousMillis >= FRAME_INTERVAL && !screenShoot) {
    previousMillis = currentMillis;

    ClearScreen();
    RunScene();
    
    display->commit();
  }else{
    AudioTick();
    yield();
  }
}
