#include <LiquidCrystal.h>
#define relayPin 2
LiquidCrystal lcd(12, 11, 7, 8, 9, 10);//(RS,E,DB4,DB5,DB6,DB7)
int switchState = 0;
int onSwitch = 0;
int lastSwitchState = 0;
unsigned long delayOff = 0;
int dial = 0;
int peakPower = 0;

void setup() {
  // set up the number of columns and rows on the LCD
  lcd.begin(16, 2);

  digitalWrite(4,1);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  digitalWrite(3,1); //just using this as another 5v power node
 
  Serial.begin(9600);
  
}

void loop() {
  
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
  


  onSwitch = analogRead(A0);
  
    if (onSwitch >= 900 || RMSCurrent >=.5){ //leave low value for testing purposes but need to increase later (value in Amps)
    switchState = 1;
    }
    else {
    switchState = 0;
    }

   

  if (switchState == 1){
    lastSwitchState = switchState;
    lcd.setCursor(10,0);
    lcd.print(switchState);
    digitalWrite(2,1);
  }
if (switchState != lastSwitchState && switchState ==0){  //saw has been turned OFF
      lastSwitchState = switchState;
      delay(delayOff*1000);

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

   if (onSwitch >= 900 || RMSCurrent >=.5){ //leave low value for testing purposes but need to increase later (value in Amps)
    switchState = 1;
    }
    else {
    switchState = 0;
    }




      if (switchState == 0){
      digitalWrite(2,0);
      }
}
  
dial = analogRead(A1);
 //Serial.println(dial);
 delayOff = map (dial, 0, 1023, 1, 305);
 
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Over-Ride: ");
      lcd.setCursor(10, 0);
      lcd.print(switchState);
      lcd.setCursor(0,1);
      lcd.print("Delay:");
      lcd.print(delayOff/60);
      lcd.setCursor(8,1);
      lcd.print("(");
      lcd.setCursor(9,1);
      lcd.print(delayOff);
      lcd.setCursor(13,1);
      lcd.print(")");
      Serial.print(RMSCurrent);
      Serial.println(" A");
     // Serial.print(RMSPower);
      //Serial.println(" W");
      Serial.println("");
   
delay(50);


}
