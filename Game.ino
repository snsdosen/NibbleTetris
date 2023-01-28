//This file contains routines for the actual game

void NewGame(){
  ClearPlayfield();
  activeTetromino = random(TETROMINO_COUNT);
  currentScore = 0;
  currentLevel = 0;
  currentLines = 0;
  gameOver = false;
}

void ClearPlayfield(){
  memset (&playField, 0, sizeof(playField));
  fallTimeoutCounter = FALL_TIMEOUT;

#ifdef DEBUG
#ifdef TEST_CLEARANCE
for(int yy=0; yy< 4; yy++){
  for(int xx = 0; xx < FIELD_WIDTH - 1; xx++){
    playField[xx][FIELD_HEIGHT - FIELD_HIDDEN + yy] = 1;
  }
}
#endif
#endif

  NewTetromino();
}

//Start playing with new tetromino
void NewTetromino(){
  activeLine = TETROMINO_Y_DEF;
  activeColumn = TETROMINO_X_DEF;
  activeFrame = 0;
  moveTimeout = 0;
  rotateDebounce = 0;
  rotateLockout = false;
  activeTetromino = nextTetromino;
  nextTetromino = random(TETROMINO_COUNT);

  //Check if playfield is full, aka Game Over
  gameOver = !sideCheck(activeFrame, activeColumn, 0);

  if(gameOver) gamePaused = true;
}

//Rotate piece either left or right
void rotateTetromino(int side){
  PlayAudio(RotateSoundSample);

  switch(side){
    case ROTATE_LEFT:
      rotateDebounce = DEBOUNCE_VALUE;
      rotateLockout = true;
      activeFrame = ((activeFrame - 1) + (TETROMINO_FRAME_COUNT)) % (TETROMINO_FRAME_COUNT);
      break;
      
    case ROTATE_RIGHT:
      rotateDebounce = DEBOUNCE_VALUE;
      rotateLockout = true;
      activeFrame = ((activeFrame + 1) + (TETROMINO_FRAME_COUNT)) % (TETROMINO_FRAME_COUNT);
      break;
  }
}

//Left side checking routines
bool sideCheck(int frame, int column, int sideOffset){

  //Run through every tetromino "block"
  for(int xT = 0; xT < TETROMINO_WIDTH; xT++){
    for(int yT = 0; yT < TETROMINO_HEIGHT; yT++){
      //Check if out of bounds
      if((sideOffset < 0 && (xT + column + sideOffset) < 0) || (sideOffset > 0 && (xT + column + sideOffset) > FIELD_WIDTH - 1)) {
        if(GetTetrominoValue(activeTetromino, frame, xT, yT) > 0) return false;
      }else{
        if(playField[xT + column + sideOffset][yT + activeLine] > 0 && GetTetrominoValue(activeTetromino, frame, xT, yT) > 0) return false;
      }
    }
  }

  return true;
}

//Move tetromino one block down if it's allowed to move
void moveDown(){
    int addition = 0;

    //Fix for edge cases
    if((activeTetromino == I_TETROMINO_INDEX && (activeFrame == 0 || activeFrame == 2)) || (activeTetromino == J_TETROMINO_INDEX && activeFrame == 2) || (activeTetromino == L_TETROMINO_INDEX && activeFrame == 2)){
      addition = 1;
    }

    if(activeLine < FIELD_HEIGHT - FIELD_HIDDEN + addition) {
      
      //Run through every tetromino "block"
      for(int xT = 0; xT < TETROMINO_WIDTH; xT++){
        for(int yT = 0; yT < TETROMINO_HEIGHT; yT++){
          if((xT + activeColumn) >= 0 && (xT + activeColumn) < FIELD_WIDTH){
            if(playField[xT + activeColumn][yT + activeLine + 1] > 0 && GetTetrominoValue(activeTetromino, activeFrame, xT, yT) > 0){
              ImprintTetromino();
              return;
            }
          }
        }
      }

      //Tetromino is free to move
      activeLine++;
    }else{
      ImprintTetromino();
    }
}

//Check if game should go to the next level
void CheckNextLevel(int lastLines){
  currentLines += lastLines;
  if(currentLines < LINES_NEXT_LV) return;

  currentLines = 0;
  currentLevel++;

  //Play level complete sound
  PlayAudio(LevelSoundSample);
}

//Place tetromino on the playfield
void ImprintTetromino(){

  for(int xT = 0; xT < TETROMINO_WIDTH; xT++){
    for(int yT = 0; yT < TETROMINO_HEIGHT; yT++){
      //Draw only visible blocks
      if(GetTetrominoValue(activeTetromino, activeFrame, xT, yT) > 0){
        //Check if available data is within boundaries
        if((xT + activeColumn) >= 0 && (xT + activeColumn) < FIELD_WIDTH){
          playField[xT + activeColumn][yT + activeLine] = 1;
        }
      }
    }
  }

  AddScore(SCORE_DROPDOWN);
  PlayAudio(ImprintSoundSample);

  int clearedLines = CheckLines();
  int totalLines = clearedLines;

  //Continue checking untill there are no cleared lines
  while(clearedLines > 0){
    clearedLines = CheckLines();
    totalLines += clearedLines;
  }

  //Add score for cleared lines
  switch(totalLines){
    case 1:
      AddScore(SCORE_SINGLE * (currentLevel + 1));
      break;

    case 2:
      AddScore(SCORE_DOUBLE * (currentLevel + 1));
      break;

    case 3:
      AddScore(SCORE_TRIPLE * (currentLevel + 1));
      break;

    case 4:
      AddScore(SCORE_QUAD * (currentLevel + 1));
      break;
  }

  CheckNextLevel(totalLines);

  NewTetromino();
}

//Main function regarding tetromino movement
void AnimateTetromino(){

  //Check if user tried rotating
  if(aFlag && !rotateLockout && rotateDebounce == 0 && (millis() - aPressedAt) > DEBOUNCE_KEYS_MS) {
    if(activeColumn < 2){
      if (sideCheck(((activeFrame - 1) + (TETROMINO_FRAME_COUNT)) % (TETROMINO_FRAME_COUNT), activeColumn + 1, -1)) rotateTetromino(ROTATE_LEFT);
    }else{
      if (sideCheck(((activeFrame - 1) + (TETROMINO_FRAME_COUNT)) % (TETROMINO_FRAME_COUNT), activeColumn - 1, 1)) rotateTetromino(ROTATE_LEFT);
    }
  }
  if(bFlag && !rotateLockout && rotateDebounce == 0 && (millis() - bPressedAt) > DEBOUNCE_KEYS_MS) {
    if(activeColumn < 2){
      if (sideCheck(((activeFrame + 1) + (TETROMINO_FRAME_COUNT)) % (TETROMINO_FRAME_COUNT), activeColumn + 1, -1)) rotateTetromino(ROTATE_RIGHT);
    }else{
      if (sideCheck(((activeFrame + 1) + (TETROMINO_FRAME_COUNT)) % (TETROMINO_FRAME_COUNT), activeColumn - 1, 1)) rotateTetromino(ROTATE_RIGHT);
    }
  }

  //Clear rotation flag if rotation buttons are released
  if(!aFlag && !bFlag) rotateLockout = false;

  if(rotateDebounce > 0) rotateDebounce--;
  
  //Try moving left
  if(leftFlag && moveTimeout == 0){
    if(activeColumn > -TETROMINO_WIDTH) {
      if(sideCheck(activeFrame, activeColumn, -1)) {
        PlayAudio(MoveSoundSample);
        activeColumn--;
      }
    }
    
    moveTimeout = MOVE_TIMEOUT;
  }

  //Try moving right
  if(rightFlag && moveTimeout == 0){
    if(activeColumn < FIELD_WIDTH) {
      if(sideCheck(activeFrame, activeColumn, 1)) {
        PlayAudio(MoveSoundSample);
        activeColumn++;
      }
    }
    
    moveTimeout = MOVE_TIMEOUT;
  }
  
  //Decrement move timeout
  if(moveTimeout > 0) moveTimeout--;

  //Instant drop
  if(upFlag) moveDown();

  //Check if fall timeout reached zero
  if(fallTimeoutCounter > 0){
    //Check if down is pressed for faster falling speed
    if(downFlag) fallTimeoutCounter = 0;
    else fallTimeoutCounter--;
  }else{
    if(currentLevel < MAX_LEVEL) fallTimeoutCounter = FALL_TIMEOUT - (currentLevel);
    else fallTimeoutCounter = FALL_TIMEOUT - (MAX_LEVEL);

    moveDown();
  }
}

void DrawTetromino(){
  for(int yT = 0; yT < TETROMINO_HEIGHT; yT++){
    for(int xT = 0; xT < TETROMINO_WIDTH; xT++){
      //Don't draw hidden blocks
      if(activeLine + yT > 1 && GetTetrominoValue(activeTetromino, activeFrame, xT, yT) > 0) sprite->fillRect((6 * activeColumn) + (6 * xT) + FIELD_X_OFFSET, (6 * activeLine) + (6 * yT) + FIELD_Y_OFFSET - (FIELD_HIDDEN * 6), 6, 6, TFT_BLUE);
    }
  }
}

void DrawPlayfield(){
  //Draw outline
  sprite->fillRect(FIELD_X_OFFSET - 2, FIELD_Y_OFFSET - 2, (FIELD_WIDTH * BLOCK_SIZE) + 4, (FIELD_HEIGHT * BLOCK_SIZE) + 4, TFT_LIGHTGREY);

  //Draw field
  sprite->fillRect(FIELD_X_OFFSET, FIELD_Y_OFFSET, (FIELD_WIDTH * BLOCK_SIZE), (FIELD_HEIGHT * BLOCK_SIZE), TFT_BLACK);

  //Draw only visible portion, ignore hidden
  for(int yT = 0; yT < FIELD_HEIGHT; yT++){
    for(int xT = 0; xT < FIELD_WIDTH; xT++){

      if(playField[xT][yT + FIELD_HIDDEN] > 0){
        sprite->fillRect((6 * xT) + FIELD_X_OFFSET, (6 * yT) + FIELD_Y_OFFSET, 6, 6, TFT_GREEN);
      }else{
        //Draw nothing
      }
    }
  }
}

//Clear full line
void ClearLine(int line){
  //Move everything down up untill the cleared line
  for(int i = 0; line - i > 0; i++){
    for(int fX = 0; fX < FIELD_WIDTH; fX++){
      playField[fX][line-i] = playField[fX][line -i - 1];
    }
  }
}

//Go through each line after imprint to check if the line is cleared
int CheckLines(){
  bool fullLine = false;
  int clearLineCount = 0;

  for(int fY = FIELD_HEIGHT + FIELD_HIDDEN; fY >= 0; fY--){
    fullLine = true;
      for(int fX = 0; fX < FIELD_WIDTH; fX++){
        if(playField[fX][fY] < 1) fullLine = false;
      }
      if(fullLine){
        ClearLine(fY);
        clearLineCount++;
      }
  }

  //Return number of lines cleared
  return clearLineCount;
}

void PrintMessageMenu(String message) {
  sprite->setTextFont(2);
  sprite->setTextSize(1);
  sprite->setTextColor(TFT_WHITE);
  sprite->setTextDatum(TC_DATUM);
  sprite->fillRect(5, 55, 120, 18, TFT_RED);
  sprite->drawString(message, 64, 56);
}

void PauseGame(){
  if(!gamePaused && cFlag){
    gamePaused = true;
    cFlag = false;
    PlayAudio(PauseSoundSample);
  }else if(gamePaused && cFlag){
    gamePaused = false;
    cFlag = false;
    PlayAudio(PauseSoundSample);
    if(gameOver)NewGame();
  }
}

void RunGame(){
  DrawPlayfield();
  DrawScoreboard();
  DrawTetromino();

  if(gamePaused && !gameOver) PrintMessageMenu("PAUSE");
  else if(gameOver) PrintMessageMenu("GAME OVER");
  else AnimateTetromino();

  PauseGame();
}
