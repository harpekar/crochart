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

  int row_count;
  int stitch_count;

void setup(void) {
  u8g2.begin();
  pinMode(5, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP); 

  row_count = 0;
  stitch_count = 0;

}

void loop(void) {

  int row_val = digitalRead(5);
  int stitch_val = digitalRead(4);
  //Serial.println(val);

  if (row_val == LOW) { 

      row_count++;  
      //delay(1000); 

  } 

  if (stitch_val == LOW) {

      stitch_count++;

  }

  delay(250);
  
  u8g2.clearBuffer();					// clear the internal memory
  u8g2.setFont(u8g2_font_ncenB08_tr);	// choose a suitable font

  char buf[9];
  sprintf(buf,"%d %d", row_count, stitch_count);

  u8g2.drawStr(0,10,buf);	// write something to the internal memory
  u8g2.sendBuffer();					// transfer internal memory to the display

}
