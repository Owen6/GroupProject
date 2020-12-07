#include <LiquidCrystal.h>
LiquidCrystal lcd(12,11,5,4,3,2);
float temp;
float tempC;
//float tempF;
int tempPin = A0;

void setup(){
  lcd.begin(16,2);
}

void loop(){
  temp = analogRead(tempPin);
  temp = temp * .48828125;

  tempC = temp;
  tempF = tempC * 1.8 + 32;

  lcd.setCursor(0,0);
  lcd.print(tempC);
  lcd.setCursor(5,0);
  lcd.print("*");
  lcd.setCursor(7,0);
  lcd.print("Celsius");
  delay(1000);
}