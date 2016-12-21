/*********************************************************************
This is an example for our Monochrome OLEDs based on SSD1306 drivers

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/category/63_98

This example is for a 128x64 size display using SPI to communicate
4 or 5 pins are required to interface

Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!

Written by Limor Fried/Ladyada  for Adafruit Industries.  
BSD license, check license.txt for more information
All text above, and the splash screen must be included in any redistribution
*********************************************************************/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_MOSI 9
#define OLED_CLK 10
#define OLED_DC 11
#define OLED_CS 12
#define OLED_RESET 13
Adafruit_SSD1306 Display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

/* Uncomment this block to use hardware SPI
#define OLED_DC     6
#define OLED_CS     7
#define OLED_RESET  8
Adafruit_SSD1306 display(OLED_DC, OLED_RESET, OLED_CS);
*/

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 
static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif
void setup()   {                
  Serial.begin(9600);

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  Display.begin(SSD1306_SWITCHCAPVCC);
  // init done
  Display.clearDisplay();
  //display.setTextColor(WHITE);
  //display.setTextSize(1);
  //display.setCursor(0,24);
  //display.print("Hello World!");
//int sensorValue=200;
//int w = map(sensorValue, 0, 1023, 0, Display.width()*0.7);
// Draw filled part of bar starting from left of screen:
//Display.fillRect(0, 0, w, Display.height()/2, 1);
// Erase the area to the right of the bar:
//Display.fillRect(w, 0, Display.width()*0.7 - w, Display.height()/2, 0);
// Update the screen:

  DrawTitles();
  
  Display.drawRect(2,30,120,34,WHITE);
  DrawBar(256);
  //Display.drawPixel(35, 60, WHITE);

  Display.display();
//LCD_progress_bar (30,50,1,100);
 }


void loop() {

}

void DrawTitles(void) {

  Display.setTextSize(3);
  Display.setTextColor(WHITE);
  Display.setCursor(0, 0);
  Display.println("FUEL");


  //Display.setTextSize(1);
  //Display.setTextColor(WHITE);
  //Display.setCursor(1, 20);
  //Display.println("Measured Volts");
  //Display.println("Random number");
  //Display.display();

}

void DrawBar(int inputReading){
  double readingAsPercentage = ((double)inputReading/512);
  double barPercentage = 118*readingAsPercentage;
  Serial.print("Reading:");
  printDouble(readingAsPercentage, 10);
  Serial.print(" Bar:");
  printDouble(barPercentage, 10);

    
  Display.fillRect(4,33,barPercentage,28,WHITE);  
}

void printDouble( double val, unsigned int precision){
// prints val with number of decimal places determine by precision
// NOTE: precision is 1 followed by the number of zeros for the desired number of decimial places
// example: printDouble( 3.1415, 100); // prints 3.14 (two decimal places)

   Serial.print (int(val));  //prints the int part
   Serial.print("."); // print the decimal point
   unsigned int frac;
   if(val >= 0)
       frac = (val - int(val)) * precision;
   else
       frac = (int(val)- val ) * precision;
   Serial.println(frac,DEC) ;
} 
/*
void LCD_progress_bar (int row, int var, int minVal, int maxVal)
{
  int block = map(var, minVal, maxVal, 0, 16);   // Block represent the current LCD space (modify the map setting to fit your LCD)
  int line = map(var, minVal, maxVal, 0, 80);     // Line represent the theoretical lines that should be printed 
  int bar = (line-(block*5));                             // Bar represent the actual lines that will be printed
  
  / * LCD Progress Bar Characters, create your custom bars * /

  byte bar1[8] = { 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10};
  byte bar2[8] = { 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18};
  byte bar3[8] = { 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C};
  byte bar4[8] = { 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E};
  byte bar5[8] = { 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F};
  Display.createChar(1, bar1);
  Display.createChar(2, bar2);
  Display.createChar(3, bar3);
  Display.createChar(4, bar4);
  Display.createChar(5, bar5);
  
  for (int x = 0; x < block; x++)                        // Print all the filled blocks
  {
    Display.setCursor (x, row);
    Display.write (1023);
  }
  
  Display.setCursor (block, row);                            // Set the cursor at the current block and print the numbers of line needed
  if (bar != 0) Display.write (bar);
  if (block == 0 && line == 0) Display.write (1022);   // Unless there is nothing to print, in this case show blank
  
  for (int x = 16; x > block; x--)                       // Print all the blank blocks
  {
    Display.setCursor (x, row);
    Display.write (1022);
  }
}

*/

