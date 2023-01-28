//This file contains code for scene handling

void RunScene(){
  switch(currentScene){
    case SCENE_INTRO:
      break;
  
    case SCENE_MENU:
      break;

    case SCENE_LOAD:
      NewGame();
      currentScene++;
      break;
  
    case SCENE_GAME:
      RunGame();
      break;
  }
}
