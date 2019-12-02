//#include "stationDefines.h"
/* LCD */
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// Variables
int red;
int grn;
int blu;
String color = "";
int count = 0;
long startTiming = 0;
long elapsedTime = 0;
boolean DEBUG = true;


#define s0 4
#define s1 5
#define s2 6
#define s3 7
#define outPin 8
void setup() {

  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(outPin, INPUT); //out from sensor becomes input to arduino

  // Setting frequency scaling to 100%
  digitalWrite(s0, HIGH);
  digitalWrite(s1, HIGH);

  Serial.begin(9600);
                       // initialize the lcd
  lcd.init();
  lcd.backlight();
  lcd.print("MJRoBot ColorDet");
  Serial.println("MJRoBot Color Detector");
  startTiming = millis();
}



  
                                                                                                                                                                                   
void getColor()
{
  readRGB();
 
  if (red > 1 && red < 5 && grn > 5 && grn < 10&& blu > 2 && blu < 3) color = "WHITE";
  else if (red > 23 && red < 35 && grn                     > 28 && grn < 39 && blu > 15&& blu < 35) color = "BLACK";
  else if (red > 4 && red < 10 && grn > 18 && grn < 25 && blu > 12 && blu < 20) color = "RED";
  else if (red > 10 && red < 20 && grn > 5 && grn < 20 &                                     & blu > 5 && blu < 25) color = "GREEN";
  else if (red > 2 && red < 7 && grn > 4 && grn < 10 && blu > 7 && blu < 14) color = "YELLOW";
  else if (red > 11 && red < 25 && grn > 6 && grn < 17&& blu > 3 && blu < 13  ) color = "BLUE";
   else if (red > 3 && red < 7 && grn >8 && grn < 15 && blu > 10 && blu <20) color = "orange";
  else  color = "NO_COLOR";
}

/* read RGB components */
void readRGB()
{
  red = 0;
  grn = 0;
  blu = 0;
  int n = 10;
  for (int i = 0; i < n; ++i)
  {
    //read red component
    digitalWrite(s2, LOW);
    digitalWrite(s3, LOW);
    red = red + pulseIn(outPin, LOW);

    //read green component
    digitalWrite(s2, HIGH);
    digitalWrite(s3, HIGH);
    grn = grn + pulseIn(outPin, LOW);

    //let's read blue component
    digitalWrite(s2, LOW);
    digitalWrite(s3, HIGH);
    blu = blu + pulseIn(outPin, LOW);
  }
  red = red / n;
  grn = grn / n;
  blu = blu / n;
}





void showDataLCD(void)
{
  lcd.clear();
  lcd.setCursor (0, 0);
  lcd.print("R");
  lcd.setCursor (1, 0);
  lcd.print("    ");
  lcd.setCursor (1, 0);
  lcd.print(red);
  lcd.setCursor (5, 0);
  lcd.print(" G");
  lcd.setCursor (7, 0);
  lcd.print("    ");
  lcd.setCursor (7, 0);
  lcd.print(grn);
  lcd.setCursor (12, 0);
  lcd.print("B");
  lcd.setCursor (13, 0);
  lcd.print("    ");
  lcd.setCursor (13, 0);
  lcd.print(blu);

  lcd.setCursor (0, 1);
  lcd.print("Color: ");
  lcd.setCursor (7, 1);
  lcd.print("        ");
  lcd.setCursor (7, 1);
  lcd.print(color);

}

/***************************************************
  Showing captured data at Serial Monitor
****************************************************/
void printData(void)
{
  Serial.print("red= ");
  Serial.print(red);
  Serial.print("   green= ");
  Serial.print(grn);
  Serial.print("   blue= ");
  Serial.print(blu);
  Serial.print (" - ");
  Serial.print (color);
  Serial.println (" detected!");
}





void loop() {

  getColor();
  if (DEBUG) printData();
  elapsedTime = millis() - startTiming;
  if (elapsedTime > 1000)
  {
    showDataLCD();
    startTiming = millis();
  }
}
