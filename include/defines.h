#ifndef DEFINES_H
#define DEFINES_H

  //Framerate
  #define FRAME_INTERVAL  33  //33ms - 30 FPS

  //Scenes throughout the game
  #define SCENE_INTRO   0
  #define SCENE_MENU    1
  #define SCENE_LOAD    2
  #define SCENE_GAME    3

  //Blocks
  #define BLOCK_SIZE    6

  //Playfield
  #define FIELD_WIDTH   10    //Number of horizonstal tiles
  #define FIELD_HEIGHT  20    //Number of vertical tiles
  #define FIELD_HIDDEN  2     //Number of top "hidden" tiles

  #define FIELD_X_OFFSET  4   //Screen offset
  #define FIELD_Y_OFFSET  4

  //Tetrominos
  #define TETROMINO_COUNT       7
  #define TETROMINO_FRAME_COUNT 4
  #define TETROMINO_X_DEF       3   //Default tetromino position in blocks
  #define TETROMINO_Y_DEF       0

  #define FALL_TIMEOUT      30  //Number of frames to wait on level zero
  #define MOVE_TIMEOUT		  4

  #define TETROMINO_WIDTH   4   //Maximum width of tetromino in blocks
  #define TETROMINO_HEIGHT  4   //Maximum height of tetromino in blocks

  #define I_TETROMINO_INDEX   1 //Index for I tetromino, for special case
  #define J_TETROMINO_INDEX   3
  #define L_TETROMINO_INDEX   4

  #define ROTATE_LEFT         0
  #define ROTATE_RIGHT        1
  #define DEBOUNCE_VALUE      5   //Number of frames to wait for the next available rotation
  
  //Input
  #define DEBOUNCE_KEYS_MS    16  //Number of miliseconds to sample for debouncing

  //Scoreboard
  #define BOARD_X_OFFSET	68
  #define BOARD_Y_OFFSET	0

  //Scores
  #define SCORE_DROPDOWN  10
  #define SCORE_SINGLE    40
  #define SCORE_DOUBLE    100
  #define SCORE_TRIPLE    300
  #define SCORE_QUAD      1200

  //Levels
  #define LINES_NEXT_LV   10    //Required number of lines to reach next level
  #define MAX_LEVEL       15

#endif
