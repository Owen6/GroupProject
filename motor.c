
volatile unsigned char *pinE =     (unsigned char *) 0x2C;
volatile unsigned char *portDDRE = (unsigned char *) 0x2D;
volatile unsigned char *portE =    (unsigned char *) 0x2E;
 
void setup() 
{ 
  Serial.begin(9600);
  // set PE5 to output
  *portDDRE |= 0x20;
  // Initialize PE5 to low
  *portE &= 0xDF;
  
  
} 
 
 
void loop() 
{ 
  //drive PE5high
  *portE |= 0x20;
  
} 