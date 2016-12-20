#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_MOSI 9
#define OLED_CLK 10
#define OLED_DC 11
#define OLED_CS 12
#define OLED_RESET 13
Adafruit_SSD1306 display1(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

uint8_t waterTemp  = 0;
uint8_t fuelLevel  = 128;
uint8_t delayValue = 500;
uint8_t oilTemp    = 0;
uint8_t voltage    = 0;

void setup()   {                
  Serial.begin(9600);
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display1.begin(SSD1306_SWITCHCAPVCC);
  //display1.begin(SSD1306_EXTERNALVCC);
  display1.display(); // show splashscreen on screen 1
  
 
  display1.clearDisplay();   // clears the screen and buffer

  fuelLevel = 128;
  drawFUEL();             //draw the FUEL gauge
  display1.display();
  delay(50);
  display1.clearDisplay();
  updateFUEL();

}


void loop() {
  
  static unsigned long nextFUELReadTime = 5000L; //300000L; //5mins
    if( nextFUELReadTime < millis() )
    {
      nextFUELReadTime = millis() + 5000L; //300000L; //5mins

      //read the FUEL sensor (probably do this once a minute? doesn't need to be that accurate!)
      //if changed then output the change to the correct display
      if(fuelLevel <= 10) {
        fuelLevel = 0;
      } else {
        fuelLevel = fuelLevel - 1;
      }
      Serial.print("FuelLevel=");Serial.println(fuelLevel);
      updateFUEL();
    }
  delay(delayValue);
}

void drawFUEL(void) {
  display1.clearDisplay();
  display1.drawTriangle(64,0,  0,50, 128,50, WHITE);
  display1.drawTriangle(64,0, 20,50, 108,50, WHITE);
  display1.drawTriangle(64,0, 40,50,  88,50, WHITE);
  display1.drawLine(64,0, 64,50, WHITE);
  display1.fillRect(0, 0, 128, 40, BLACK);
  display1.drawFastHLine(0,50, 128, BLACK);

  display1.setTextSize(1);
  display1.setTextColor(WHITE);
  display1.setCursor(47,5);
  display1.println("SMITHS");
  display1.setCursor(41,20);
  display1.println("CAPACITY");
  display1.setCursor(44,29);
  display1.println("8 GALLS");
  display1.setCursor(0,54);
  display1.println("0");
  display1.setCursor(57,54);
  display1.println("1/2");
  display1.setCursor(122,54);
  display1.println("F");
}

void drawFUELGauge(uint8_t fuellevel)
{
  display1.drawLine(64,0, fuellevel,  58, WHITE);
  display1.drawLine(65,0, fuellevel+1,58, WHITE);
  display1.drawLine(66,0, fuellevel+2,58, WHITE);
  display1.drawLine(66,0, fuellevel+3,58, WHITE);
  display1.drawLine(66,0, fuellevel+4,58, WHITE);
}

void updateFUEL(void) {
  if(fuelLevel >= 30) {
    drawFUEL();
    drawFUELGauge(fuelLevel);
  } else if(fuelLevel != 0){
    drawFUEL();
    drawFUELGauge(fuelLevel);
    display1.setTextSize(2);
    display1.setTextColor(WHITE);
    display1.setCursor(20,51);
    display1.println("FUEL LOW");
  } else if(fuelLevel == 0) {
    drawFUEL();
    drawFUELGauge(fuelLevel);
    display1.setTextSize(3);
    display1.setTextColor(WHITE);
    display1.setCursor(30,5);
    display1.println("FUEL");
    display1.setCursor(20,35);
    display1.println("EMPTY");
    display1.invertDisplay(true);
    delay(150);
    display1.invertDisplay(false);
    delay(150);
    display1.invertDisplay(true);
    delay(150);
    display1.invertDisplay(false);
    delay(150);
    display1.invertDisplay(true);
    delay(150);
    display1.invertDisplay(false);
  }
  display1.display();
  display1.clearDisplay();
}


