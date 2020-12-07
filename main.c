#include <stdio.h>

#include <dht.h>
#include <LiquidCrystal.h>

// States - 0 Disabled - 1 Idle - 2 Running - 3 Error 
// LEDs --Disabled = yellow -- Idle = Green -- Running = Blue -- Error = Red

//dht DHT;
const int RD = 2, EN = 3, D4 = 4, D5 = 5, D6 = 6, D7 = 7;
LiquidCrystal lcd(RS,EN,D4,D5,D6,D7);

DHT dht(DHTPIN, DHTTYPE);

volatile unsigned char *myUCSR0A = (unsigned char *)0x00C0;
volatile unsigned char *myUCSR0B = (unsigned char *)0x00C1;
volatile unsigned char *myUCSR0C = (unsigned char *)0x00C2;
volatile unsigned int  *myUBRR0  = (unsigned int *) 0x00C4;
volatile unsigned char *myUDR0   = (unsigned char *)0x00C6;
volatile unsigned char *myTCCR1A = (unsigned char *) 0x80;
volatile unsigned char *myTCCR1B = (unsigned char *) 0x81;
volatile unsigned char *myTCCR1C = (unsigned char *) 0x82;
volatile unsigned char *myTIMSK1 = (unsigned char *) 0x6F;
volatile unsigned int  *myTCNT1  = (unsigned  int *) 0x84;
volatile unsigned char *myTIFR1 =  (unsigned char *) 0x36;

volatile unsigned char *pinB =     (unsigned char *) 0x23;
volatile unsigned char *portDDRB = (unsigned char *) 0x24;
volatile unsigned char *portB =    (unsigned char *) 0x25;
volatile unsigned char *pinH =     (unsigned char *) 0x100;
volatile unsigned char *portDDRH = (unsigned char *) 0x101;
volatile unsigned char *portH =    (unsigned char *) 0x102;

volatile unsigned char *my_ADMUX =  (unsigned char*)  0x7C;
volatile unsigned char *my_ADCSRB = (unsigned char*) 0x7B;
volatile unsigned char *my_ADCSRA = (unsigned char*) 0x7A;
volatile unsigned int *my_ADC_DATA = (unsigned int*) 0x78;

void idleState(int *state);
void runningState(int *state);
void errorState(int *state);

int main(){
  //starts here
  int state = 0;
  
  return 0;
}


void setup()
{
  lcd.begin(16,2);
  dht.begin();
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

  *myTCCR1A = 0x00;
  *myTCCR1B = 0x00;
  *myTCCR1C = 0x00;
  Serial.begin(9600);
  
}

void loop()
{
  /**int readDHT = DHT.read11(8);
  lcd.setCursor(0,0);
  lcd.print("Temp: ");
  lcd.print(DHT.temperature);
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("")
  **/

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if(isnan(h) || isnan(t)){
    Serial.println("failed");
    return;
  }

  lcd.setCursor(0,0);
  lcd.print("Temp: ");
  lcd.print(t);
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("Humidity: ");
  lcd.print(h);

  delay(2000);

}





int water_Level()
{
 
}

ISR(TIMER0_COMPA_vect, int *val){
  int historyValue = analogRead(adc_id);
  val = historyValue;
  if(historyValue < threshold){
    PORTB |= 0x20;
    PORTB &= 0x7F;
  }else{
    PORTB &= 0xDF;
    PORTB |= 0x80;

  }
}

void stateDisable(int *state){
  if(*state == 0){
    //Already in Disabled so we set to Idle
    *state = 1;
    // turn off other LEDs 
    *portB &= 0x8F;
    //turn on green LED at pb6
    *portB |= 0x80;
  }else{
    //Any other state we turn it off to Disabled
    *state = 0;
    // turn on yellow LED at PB4
    *portB |= 0x10;
    // turn off all other LEDs PB7-5
    *portB &= 0x1F;
  }
}

void idleState(int *state){
  *state = 1;
  *portB &= 0xDF;
  *portB &= 
  *portB &= 
  *portB |= 0x80;
}

void runningState(int *state){
  *state = 2;
  *portB &= 0x7F;
  *portB &= 0xDF;
  *portB &=-
  *portB |=  
}

void errorState(int *state){
  *state = 3;

}

void printLCD(){
   
}



void adc_init()
{
  //setup the A register
  *my_ADCSRA |= 0b10000000; // set bit 7 to 1 to enable the ADC
  *my_ADCSRA &= 0b11011111; // clear bit 5 to 0 to disable the ADC trigger mode
  *my_ADCSRA &= 0b11110111; // clear bit 5 to 0 to disable the ADC interrupt
  *my_ADCSRA &= 0b11111000; // clear bit 5 to 0 to set prescaler selection to slow reading

  //setup the B register
  *my_ADCSRB &= 0b11110111; //clear bit 3 to 0 to reset the channel and gain bits
  *my_ADCSRB &= 0b11111000; //clear bits 2-0 to set free running mode
  
  //setup the MUX register
  *my_ADMUX &= 0b01111111; // clear bit 7 to 0 for AVCC analog reference
  *my_ADMUX |= 0b01000000; // set bit 6 to 1 for AVCC analog reference
  *my_ADMUX &= 0b11011111; // clear bit 5 to 0 for right adjust result
  *my_ADMUX &= 0b11100000; //clear bit 4-0 to 0 to reset the channel and gain bits
}


unsigned int adc_read_temp (unsigned char adc_channel_num){

//clear the channel select bits 0-4          
  *my_ADMUX  &= 0b11100000;
  //clears channel select bit MUX 5
  *my_ADCSRB &= 0b11110111;
  //set bit 6 to 1 to start the conversion
  *my_ADCSRA |= 0b00100000;

  //wait for the conversion to be complete
  while((*my_ADCSRA & 0x40) != 0);
  //return the result in the ADC register
  return *my_ADC_DATA;

}
