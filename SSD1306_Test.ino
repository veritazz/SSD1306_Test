#include <Arduboy2.h>

Arduboy2 arduboy;

void setup() {
 arduboy.begin();
 arduboy.setFrameRate(60);

 arduboy.LCDCommandMode();
 SPI.transfer(0xd9);
 SPI.transfer(0x2f);

 SPI.transfer(0xdb);
 SPI.transfer(0x00);
}

static int left = 0;

void loop() {
  uint8_t contrast;
  uint8_t x;

  if (!(arduboy.nextFrame()))
    return;

  if (left & 1) {
    /* left rectangle */
    contrast = 100;
    x = 0;
  } else {
    /* right rectangle */
    contrast = 255;
    x = 64;
  }
  left++;

  arduboy.clear();
  arduboy.fillRect(x, 0, 64, 63, WHITE);
  arduboy.LCDCommandMode();
  SPI.transfer(0x81);
  SPI.transfer(contrast);

  arduboy.LCDDataMode();
  arduboy.display();
}
