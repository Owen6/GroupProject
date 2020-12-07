#include <dht.h>

int pin = A1

dht DHT;

void setup(){

}

void loop(){
  DHT.read11(pin);

  Serial.println(DHT.humidity);
  Serial.println(DHT.temperature);
  delay(1000)
}



//red 
portb