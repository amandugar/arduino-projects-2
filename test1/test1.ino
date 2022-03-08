#include <EEPROM.h>

//int addr = 0;


int counter ;
void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
EEPROM.begin(512);
delay(4000);
counter = EEPROM.read(0);
}

void loop() {
  counter ++;
  Serial.println("counter==");
  Serial.println(EEPROM.read(0));
  Serial.println(EEPROM.read(1));
 delay(3000);

// if (analogRead(A0) <= 730){
 EEPROM.write(0, counter);
 EEPROM.write(1, counter);
   EEPROM.commit();
// } 

}
