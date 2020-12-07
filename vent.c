#include<Servo.h> // include server library


Servo myservo; // create servo object to control a servo
char val; // initial value of input


void setup() {
  
  Serial.begin(9600); // Serial comm begin at 9600bps
  myservo.attach(9);// server is connected at pin 9

  
}

void loop() {
      
  val = Serial.read();

  switch(val){
    case 'a' :
       
        // reset servo to normal
        myservo.write(90);
        //delay for the servo to get to the position
        delay(15);
      break;
    case 's' :
           
          // servo counter clockwise
          myservo.write(180);
          //delay for the servo to get to the position
          delay(15);
 

      break;
    case 'd' :
        // servo moves clockwise
        myservo.write(0);
        //delay for the servo to get to the position
        delay(15);
    break;
      
    default :
      break;
  }


}