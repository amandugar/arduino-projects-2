#include <EEPROM.h>


void setup() {
  // put your setup code here, to run once:
//EEPROM.begin(512);
Serial.begin(9600);
}

void loop() {
  Serial.println("Value = ");
  EEPROM.write(2,50);
  for(int x = 0; x <= 255; x++)
  {
    Serial.println(EEPROM.read(x));
    delay(1000);
  }
  //Serial.println(analogRead(A0));
  //Serial.println("length = ");
 // Serial.println(EEPROM.length());
  // put your main code here, to run repeatedly:
//delay(2000);
}
