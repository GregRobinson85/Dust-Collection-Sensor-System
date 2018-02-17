//Michael Klements
//The DIY Life
//27 October 2014

#include <LiquidCrystal.h>

double kilos = 0;
int peakPower = 0;
LiquidCrystal lcd(12, 11, 7, 8, 9, 10);  //Assign LCD screen pins

void setup() 
{ 
  lcd.begin(16,2);              // columns, rows.  use 16,2 for a 16x2 LCD, etc.
  lcd.clear();
  lcd.setCursor(0,0);           // set cursor to column 0, row 0 (the first row)
  lcd.print("Running");
  Serial.begin(9600);
  pinMode(3,OUTPUT);
  digitalWrite(3,1);
}

void loop() 
{ 
  int current = 0;
  int maxCurrent = 0;
  int minCurrent = 1000;
  for (int i=0 ; i<=200 ; i++)  //Monitors and logs the current input for 200 cycles to determine max and min current
  {
    current = analogRead(A2);    //Reads current input
  //  Serial.println(current);
      
    if(current >= maxCurrent)
      maxCurrent = current;
    else if(current <= minCurrent)
      minCurrent = current;
  }
  if (maxCurrent <= 517)
  {
    maxCurrent = 516;
  }
  double RMSCurrent = ((maxCurrent - 516)*0.707)/2.3;    //Calculates RMS current based on maximum value
  int RMSPower = 122*RMSCurrent;    //Calculates RMS Power Assuming Voltage 220VAC, change to 110VAC accordingly
  if (RMSPower > peakPower)
  {
    peakPower = RMSPower;
  }
 // kilos = kilos + (RMSPower * (2.05/60/60/1000));    //Calculate kilowatt hours used
 
  lcd.clear();
  lcd.setCursor(0,0);           // Displays all current data
  lcd.print(RMSCurrent);
  lcd.print("A");
  lcd.setCursor(10,0);
  lcd.print(RMSPower);
  lcd.print("W");
  lcd.setCursor(0,1);
  lcd.print(kilos);
  lcd.print("kWh");
  lcd.setCursor(10,1);
  lcd.print(peakPower);
  lcd.print("W");
  Serial.print(RMSCurrent);
  Serial.println(" A");
  //Serial.print(RMSPower);
  //Serial.println(" W");
  Serial.println("");
 delay (50);
}
