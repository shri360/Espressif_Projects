#define LCD_CS 33 // Chip Select goes to Analog 3
#define LCD_RS 15 // LCD_RS = Register Select or LCD_CD = Command/Data goes to Analog 2
#define LCD_WR 4 // LCD Write goes to Analog 1
#define LCD_RD 2 // LCD Read goes to Analog 0
#define LCD_RESET 32 // Can alternately just connect to Arduino's reset pinCan alternately just connect to Arduino's reset pin

#include <SPI.h>          // f.k. for Arduino-1.5.2
#include "Adafruit_GFX.h"// Hardware-specific library
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;
//#include <Adafruit_TFTLCD.h>
//Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

// Assign human-readable names to some common 16-bit color values:
#define  BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

void setup()
{
    Serial.begin(9600);
    uint16_t ID = tft.readID();
    if (ID == 0xD3) ID = 0x9481;
    tft.begin(ID);
    tft.setRotation(0);
}

void loop()
{
    tft.fillScreen(YELLOW);
    delay (1000);
    tft.fillScreen(BLACK);
    delay (500);
    tft.fillScreen(MAGENTA);
    delay (1500);
}
