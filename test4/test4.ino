#include <EEPROM.h>

int addr = 0;

int counter=0;

void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
EEPROM.begin(512);

counter = EEPROM.read(1);
}

void loop() {
  Serial.println(ESP.getFreeSketchSpace());
  counter +=1;
  Serial.println(counter);
  delay(1000);

  if (analogRead(A0) ==1023){
 
  //EEPROM.put(1, counter);
  addr = addr + 1;
 if (addr == 512) {
 addr = 0;
   EEPROM.commit();
 }
 } 

}
