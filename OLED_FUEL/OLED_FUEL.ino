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

int A0PIN = 0;

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif
void DrawBar(int reading);

void setup()   {                
  Serial.begin(9600);
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  Display.begin(SSD1306_SWITCHCAPVCC);
  Display.clearDisplay();
  DrawTitles(false);
  //DrawBar(readPotValue());
  Display.display();
}

void loop() {
   //Display.clearDisplay();
   DrawBar(readPotValue());
   delay(5000);
   Display.clearDisplay();
   //doDraw(512);
   //delay(5000);
}

int readPotValue(){
  return analogRead(A0PIN);  
}

void DrawTitles(boolean fuelLow) {
  Display.setTextSize(3);
  Display.setTextColor(WHITE);
  Display.setCursor(0, 0);
  //if (fuelLow) {
  //  Display.println("FUEL LOW");
  //} else {
    Display.println("FUEL");
  //}
  Display.display();
}

void DrawBar(int inputReading){
  Display.drawRect(2,30,120,34,WHITE);
  Display.display();
  double readingAsPercentage = ((double)inputReading/388);
  double barWidth = 118*readingAsPercentage;
  Serial.print("Reading:");
  Serial.print(inputReading);
  printDouble(readingAsPercentage, 10);
  Serial.print(" Bar:");
  printDouble(barWidth, 10);

  Display.fillRect(4,33,118,28,BLACK);      
  Display.display();
  Display.fillRect(4,33,barWidth+2,28,WHITE);  
  Display.display();
  
  if (barWidth < 105 && barWidth > 10){
    Display.fillRect(barWidth+4,38,6,18,WHITE);
    Display.display();
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

