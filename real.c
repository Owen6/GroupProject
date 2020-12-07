

#include "DHT.h"
#include <LiquidCrystal.h>
#include <Servo.h>

#define DHTPIN 6     // what pin we're connected to
#define DHTTYPE DHT11   // DHT 11 

volatile unsigned char *pinB =     (unsigned char *) 0x23;
volatile unsigned char *portDDRB = (unsigned char *) 0x24;
volatile unsigned char *portB =    (unsigned char *) 0x25;
volatile unsigned char *pinH =     (unsigned char *) 0x100;
volatile unsigned char *portDDRH = (unsigned char *) 0x101;
volatile unsigned char *portH =    (unsigned char *) 0x102;
volatile unsigned char *pinE =     (unsigned char *) 0x2C;
volatile unsigned char *portDDRE = (unsigned char *) 0x2D;
volatile unsigned char *portE =    (unsigned char *) 0x2E;

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 5, en = 4, d4 = 22, d5 = 23, d6 = 24, d7 = 25;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Initialize DHT sensor for normal 16mhz Arduino
DHT dht(DHTPIN, DHTTYPE);
Servo myservo;

//set state to start disabled
int state = 1;
int wPin = A0;
int level;
//Set Variables
float waterThresh = 100;
float tempThresh = 73;
char val;

//------------
// States - 0 Disabled - 1 Idle - 2 Running - 3 Error 
//functions
void lcdDisplay(float hum, float temp, int error);
void ledState(int state);
void vent(char var);

void setup() {
  lcd.begin(16, 2);       // set up the LCD's number of columns and rows:
  Serial.begin(9600); 
  dht.begin(); 
  myservo.attach(9);


  // set PB7-PB4 to output           //Register B
  *portDDRB |= 0xF0;
  // Initialize PB7-4 to low
  *portB &= 0x0F;

  //set PH6-5 to output             //Register H
  *portDDRH |= 0x60;
  //set PH4 to input 
  *portDDRH &= 0xEF;
  // Initialize PH6-5 to low
  *portH &= 0x9F;
  //sets PH5 to high
  *portH |= 0x20;

   // set PE4 to output            //Register E
  *portDDRE |= 0x10;
  // set PE5 to output
  *portDDRE |= 0x20;
  // Initialize PE5 to low
  *portE &= 0xDF;  // 0b1101 1111
  //initialize water sensor power to PE4
  *portE |= 0x10;  // 0b0001 0000
  
}

void loop(){
  delay(2000);
  //Update Variables
  float h = dht.readHumidity();
  float f = dht.readTemperature(true);
  //Temp variables until we get the water sensor working
  level = analogRead(wPin);

  val = Serial.read();
  vent(val);
   // level = 200;
  //switch led for state
  ledState(state);
  //checks the state
  switch(state){
    case 0 :
      //Disabled
      break;
    case 1 : 
      //Idle State
      //Display Temp and Humidity
      lcdDisplay(h, f, state);
      if(level < waterThresh){
        //Error State if water level too low
        state = 3;
      }else if(f > tempThresh){
        //Running State if temperature too high
        state = 2;
      }
      //Idle
      break;
    case 2 :
      //Running
      lcdDisplay(h, f, state);
      *portE |= 0x20;
      if(level < waterThresh){
        //Error State if water level too low
        state = 3;
        *portE &= 0xDF;
      }else if(f <= tempThresh){
        //Idle state if temperature is back within threshold
        state = 1;
        *portE &= 0xDF;
      }
      break;
    case 3 :
      //Error
      lcdDisplay(h, f, state);
      if(level >= waterThresh){
        state = 1;
      }
      break;
    default : 
      //Idle
      state = 1;
      break;
  }

  //Temporary Console print for testing purposes
  Serial.print("Humidity: "); 
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print(f);
  Serial.println(" *F");
  Serial.println(level);
}

void lcdDisplay(float hum, float temp, int error){

   lcd.clear();
  if(error == 3){
   
    lcd.setCursor(0,0);
    lcd.print("Error Water Level too low");
    return;
  }

  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temp);
  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(hum);

}

void ledState(int state){
  switch(state){
    case 0 : 
      *portB |= 0x10;
      *portB &= 0x1F;
      break;
    case 1 : 
      *portB |= 0x80;
      *portB &= 0x8F;
      break;
    case 2 : 
      *portB |= 0x40;
      *portB &= 0x4F;
      break;
    case 3 : 
      *portB |= 0x20;
      *portB &= 0x2F;
      break;
  }
}

void vent(char var){
  switch(var){
    case 'a' :
      myservo.write(90);
      delay(15);
      break;
    case 's' :
      myservo.write(180);
      delay(15);
      break;
    case 'd' :
      myservo.write(0);
      delay(15);
      break;
    default :
      break;
  }
}