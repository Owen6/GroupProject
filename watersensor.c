volatile unsigned char *pinB =     (unsigned char *) 0x23;
volatile unsigned char *portDDRB = (unsigned char *) 0x24;
volatile unsigned char *portB =    (unsigned char *) 0x25;
volatile unsigned char *pinH =     (unsigned char *) 0x100;
volatile unsigned char *portDDRH = (unsigned char *) 0x101;
volatile unsigned char *portH =    (unsigned char *) 0x102;
volatile unsigned char *pinE =     (unsigned char *) 0x2C;
volatile unsigned char *portDDRE = (unsigned char *) 0x2D;
volatile unsigned char *portE =    (unsigned char *) 0x2E;

int ammount = 0;
int pin = A0;
int threshold = 150;


void setup(){
  Serial.begin(9600);
  
  // set PB7-PB4 to output
  *portDDRB |= 0xF0;
  // set PE4 to output
  *portDDRE |= 0x10;
  //set PH6-5 to output
  *portDDRH |= 0x60;
  //set PH4 to input 
  *portDDRH &= 0xEF;
  // Initialize PB7-4 to low
  *portB &= 0x0F;
  // Initialize PH6-5 to low
  *portH &= 0x9F;
  
  
  //initialize water sensor power to PE4
  *portE |= 0x10;
}

void loop(){
  ammount = analogRead(pin);
  if(ammount < threshold){
    Serial.println("Error");
    // turn off other LEDs 
    *portB &= 0x2F;
    //turn on red LED at pb5
    *portB |= 0x20;
  }else{
    Serial.println(ammount);
    // turn off Red LED
    *portB &= 0xDF;
  }
  delay(1000);
}