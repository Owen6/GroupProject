

#include "DHT.h"
#include <LiquidCrystal.h>

#define DHTPIN 6     // what pin we're connected to
#define DHTTYPE DHT11   // DHT 11 

volatile unsigned char *pinB =     (unsigned char *) 0x23;
volatile unsigned char *portDDRB = (unsigned char *) 0x24;
volatile unsigned char *portB =    (unsigned char *) 0x25;
volatile unsigned char *pinH =     (unsigned char *) 0x100;
volatile unsigned char *portDDRH = (unsigned char *) 0x101;
volatile unsigned char *portH =    (unsigned char *) 0x102;

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 5, en = 4, d4 = 22, d5 = 23, d6 = 24, d7 = 25;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);








// Initialize DHT sensor for normal 16mhz Arduino
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  lcd.begin(16, 2);       // set up the LCD's number of columns and rows:
  Serial.begin(9600); 
  
    dht.begin();
 
 
 // lcd.print("test");
  Serial.println("DHTxx test!");
 

  // set PB7-PB4 to output
  *portDDRB |= 0xF0;
  //set PH6-5 to output
  *portDDRH |= 0x60;
  //set PH4 to input 
  *portDDRH &= 0xEF;
  // Initialize PB7-4 to low
  *portB &= 0x0F;
  // Initialize PH6-5 to low
  *portH &= 0x9F;


  //sets PH5 to high
  *portH |= 0x20;

 

}

void loop() {

 // lcd.clear();
  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Fahrenheit
  float f = dht.readTemperature(true);
  

  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(f);
  lcd.setCursor(0, 1);       // set the cursor to column 0, line 1
  lcd.print("Humidity: ");
  lcd.print(h);

  Serial.print("Humidity: "); 
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print(f);
  Serial.println(" *F");
}