#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

/*
  U8g2lib Example Overview:
    Frame Buffer Examples: clearBuffer/sendBuffer. Fast, but may not work with all Arduino boards because of RAM consumption
    Page Buffer Examples: firstPage/nextPage. Less RAM usage, should work with all Arduino boards.
    U8x8 Text Only Example: No RAM usage, direct communication with display controller. No graphics, 8x8 Text only.
    
*/

U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/14,/*data=*/12,U8X8_PIN_NONE);

  int rowCount;
  int stitchCount;

  int rowsPerProject;
  int stitchPerRow;

void updateScreen(void) {

  u8g2.clearBuffer();					// clear the internal memory

  char buf[9];
  sprintf(buf,"%d %d", rowCount, stitchCount);

  u8g2.drawStr(0,10,buf);	// write to the internal memory
  u8g2.sendBuffer();					// transfer internal memory to the display

}

void setup(void) {
  u8g2.begin();
  u8g2.setFont(u8g2_font_ncenB08_tr);	// choose a suitable font


  pinMode(5, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP); 

  rowCount = 0;
  stitchCount = 0;

  stitchPerRow = 10;

  updateScreen();

}

void loop(void) {

  int rowVal = digitalRead(5);
  int stitchVal = digitalRead(4);
  //Serial.println(val);

  if (rowVal == LOW) { 

      rowCount++;  
      stitchCount = 0;
      //delay(1000); 
      updateScreen();

  } 

  if (stitchVal == LOW) {

      stitchCount++;

      if (stitchCount == stitchPerRow) {

        stitchCount = 0; 
        rowCount++;

      }

      updateScreen();

  }

  //delay(200);

}
