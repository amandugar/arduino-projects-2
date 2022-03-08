#include <Stepper.h>  //stepper moter header file

#include <IRremote.h> //Ir remote header file
#define STEPS 2038 // the number of steps in one revolution of your motor (28BYJ-48)

Stepper stepper(STEPS, 8, 10, 9, 11); //stepper moter pins

const int RECV_PIN = 7; //ir reciever pins
IRrecv irrecv(RECV_PIN);
decode_results results;
unsigned long key_value = 0;

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
  irrecv.blink13(true);
}

void loop()
{
  if (irrecv.decode(&results))
  {
        if (results.value == 0XFFFFFFFF)
          results.value = key_value;
        
        if (results.value == 0xFF02FD)
        {
            Serial.println(">>|");
            stepper.setSpeed(10);
            stepper.step(509);
          
            switch(results.value){
            case 0xFF22DD:
            Serial.println("|<<");  //if (|<<) revieved moter rotates 90 degree clockwise.
            stepper.setSpeed(10); // 10 rpm
            stepper.step(-509); // 90 degree Rotation clockwise
            break;

            default:
            Serial.println("False");
            stepper.setSpeed(0); 
            stepper.step(0);
            break ;
             
             /*if (results.value == 0xFF22DD)
            {    Serial.println("|<<");
                stepper.setSpeed(10);
                stepper.step(-509);
            }
            else
            {
                Serial.println("False");
                stepper.setSpeed(0); 
                stepper.step(0);
            }*/
        }
  
        /*switch(results.value){
          case 0xFF22DD:
          Serial.println("|<<");  //if (|<<) revieved moter rotates 90 degree clockwise.
          stepper.setSpeed(10); // 10 rpm
          stepper.step(-509); // 90 degree Rotation clockwise
          break;

          
          case 0xFF02FD:
          Serial.println(">>|");  //if (|<<) revieved moter rotates 90 degree counter-clockwise.
          stepper.setSpeed(10); // 10 rpm
          stepper.step(509); // 90 degree Rotation counter-clockwise
          break ;

          default:
          Serial.println("False");
          stepper.setSpeed(0); 
          stepper.step(0);
          break ;
        }*/
        key_value = results.value;
        irrecv.resume();
}
}
