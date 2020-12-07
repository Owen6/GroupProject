

volatile unsigned char *pinB =     (unsigned char *) 0x23;
volatile unsigned char *portDDRB = (unsigned char *) 0x24;
volatile unsigned char *portB =    (unsigned char *) 0x25;
volatile unsigned char *pinH =     (unsigned char *) 0x100;
volatile unsigned char *portDDRH = (unsigned char *) 0x101;
volatile unsigned char *portH =    (unsigned char *) 0x102;
volatile unsigned char *pinE =     (unsigned char *) 0x2C;
volatile unsigned char *portDDRE = (unsigned char *) 0x2D;
volatile unsigned char *portE =    (unsigned char *) 0x2E;


int button = 0;


void setup() {

 Serial.begin(9600);
  // put your setup code here, to run once:

  // set PB7-PB4 to output
  *portDDRB |= 0xF0;
  //set PH4 to input 
  *portDDRH &= 0xEF;
  // Initialize PB7-4 to low
  *portB &= 0x0F;
   // sets pullup resistor for PH4
  *portH |= 0x10;
  
  //initialize PB4 to high
 *portB |= 0x10;

}

void loop() {
  
// Debouncing input code here

  if(!(*pinH & 0b00010000)) {
    for(volatile unsigned int i = 0; i < 100; i++);
    if(!(*pinH & 0b00010000)) {
      while(!(*pinH & 0b00010000));

      Serial.println(button);
      if(button == 0){
        button = 1;
        //turn off yellow LED
        *portB &= 0xEF;
        
      }
      else{
        button = 0;
        //turn on yellow LED
        *portB |= 0x10;
      }

    }
  }
}