//This file contains display routines

//Convert 24bit color to 16bit
uint16_t Color565(uint8_t r, uint8_t g, uint8_t b) {
  return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}

//As the name implies, clear contents of the screen
void ClearScreen(){
  sprite->clear(TFT_BLACK);
}
