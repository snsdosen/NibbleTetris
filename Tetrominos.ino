//Tetromino handling

//Grab a single byte out of tetromino "stack"
byte GetTetrominoValue(int index, int frame, int xPos, int yPos){
  return tetrominos[(index * TETROMINO_WIDTH * TETROMINO_HEIGHT * TETROMINO_FRAME_COUNT) + (frame * TETROMINO_WIDTH * TETROMINO_HEIGHT) + xPos + (yPos * TETROMINO_WIDTH)];
}
