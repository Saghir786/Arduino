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

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif
void setup()   {                
  Serial.begin(9600);

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  Display.begin(SSD1306_SWITCHCAPVCC);
  // init done
  Display.clearDisplay();

  DrawTitles();
  
  Display.drawRect(2,30,120,34,WHITE);

  DrawBar(300);
  //Display.drawPixel(35, 60, WHITE);

  Display.display();
}


void loop() {

}

void DrawTitles(void) {

  Display.setTextSize(3);
  Display.setTextColor(WHITE);
  Display.setCursor(0, 0);
  Display.println("FUEL");

}

void DrawBar(int inputReading){
  double readingAsPercentage = ((double)inputReading/512);
  double barWidth = 118*readingAsPercentage;
  Serial.print("Reading:");
  printDouble(readingAsPercentage, 10);
  Serial.print(" Bar:");
  printDouble(barWidth, 10);    
  Display.fillRect(4,33,barWidth+2,28,WHITE);  

  if (barWidth <105){
    Display.fillRect(barWidth+4,38,6,18,WHITE);
  }
}

/*
 * Prints val with number of decimal places determine by precision
 * NOTE: precision is 1 followed by the number of zeros for the desired number of decimial places
 * example: printDouble( 3.1415, 100); // prints 3.14 (two decimal places)
 * 
 */
void printDouble( double val, unsigned int precision){
   Serial.print (int(val));  //prints the int part
   Serial.print("."); // print the decimal point
   unsigned int frac;
   if(val >= 0)
       frac = (val - int(val)) * precision;
   else
       frac = (int(val)- val ) * precision;
   Serial.println(frac,DEC) ;
} 

