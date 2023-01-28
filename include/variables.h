#ifndef VARIABLES_H
#define VARIABLES_H

  //Framerate
  unsigned long previousMillis = 0;
  unsigned long currentMillis = 0;

  //Scene tracking
  int currentScene = SCENE_LOAD;

  //Playing field
  byte playField[FIELD_WIDTH][FIELD_HEIGHT + FIELD_HIDDEN];

  //Active game
  int fallTimeoutCounter = 0;   //Counter for the fall timeout period
  bool gamePaused = false;
  bool gameOver = false;

  //Levels
  int currentLevel = 0;
  int currentLines = 0;

  //Tetromino
  int activeTetromino = 0;
  int activeFrame = 0;
  int activeLine = 0;
  int activeColumn = 0;

  int nextTetromino = 0;

  int moveTimeout = 0;
  int rotateDebounce = 0;
  bool rotateLockout = false;

  //Controller
  bool upFlag = false;
  bool downFlag = false;
  bool leftFlag = false;
  bool rightFlag = false;
  bool aFlag = false;
  bool bFlag = false;
  bool cFlag = false;

  //Debouncing
  unsigned long aPressedAt = 0;
  unsigned long bPressedAt = 0;
  unsigned long cPressedAt = 0;

  //Score
  int HiScore = 0;
  int currentScore = 0;

  //Audio
  bool SoundEnabled = true;

  //Screenshot
  bool screenShoot = false;

#endif
