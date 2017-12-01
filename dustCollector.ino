#include <LiquidCrystal.h>
#define relayPin 2
LiquidCrystal lcd(12, 11, 7, 8, 9, 10);//(RS,E,DB4,DB5,DB6,DB7)
int switchState = 0;
int onSwitch = 0;
int lastSwitchState = 0;
unsigned long delayOff = 0;
int dial = 0;

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
  onSwitch = analogRead(A0);
  
    if (onSwitch >= 900){
    switchState = 1;
    }
    else {
    switchState = 0;
    }

  if (switchState ==1){
    lastSwitchState = switchState;
    lcd.setCursor(10,0);
    lcd.print(switchState);
    digitalWrite(2,1);
  }
if (switchState != lastSwitchState && switchState ==0){
      lcd.setCursor(10,0);
      lcd.print(switchState);
      lastSwitchState = switchState;
      delay(delayOff*1000);
      digitalWrite(2,0);
}
  
dial = analogRead(A1);
 Serial.println(dial);
 delayOff = map (dial, 0, 1023, 0, 305);
 
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
   
delay(17);


}
