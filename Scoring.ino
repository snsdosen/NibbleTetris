//This file contains routines for the scoring system

void DrawScoreboard(){
  sprite->setTextFont(2);
  sprite->setTextSize(1);
  sprite->setTextColor(TFT_WHITE);
  sprite->setTextDatum(TL_DATUM);

  sprite->drawString("SCORE", BOARD_X_OFFSET, BOARD_Y_OFFSET);
  sprite->drawString(String(currentScore), BOARD_X_OFFSET, BOARD_Y_OFFSET + 12);

  sprite->drawString("LEVEL", BOARD_X_OFFSET, BOARD_Y_OFFSET + 30);
  sprite->drawString(String(currentLevel), BOARD_X_OFFSET, BOARD_Y_OFFSET + 42);

  sprite->drawString("NEXT", BOARD_X_OFFSET, BOARD_Y_OFFSET + 60);

  DrawNextTetromino();
}

//Not scoring but still on a scoreboard
void DrawNextTetromino(){
  for(int yT = 0; yT < TETROMINO_HEIGHT; yT++){
    for(int xT = 0; xT < TETROMINO_WIDTH; xT++){
      //Don't draw hidden blocks
      if(GetTetrominoValue(nextTetromino, 0, xT, yT) > 0) sprite->fillRect(BOARD_X_OFFSET + (6 * xT), BOARD_Y_OFFSET + (6 * yT) + 72, 6, 6, TFT_BLUE);
    }
  }
}

void AddScore(int value){
  currentScore += value;
}
