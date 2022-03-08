int Relay = 12;

void setup() {
  Serial.begin(9600);
  pinMode(Relay, OUTPUT);
}

void loop() {
  digitalWrite(Relay, HIGH);
  
  delay(1);
  digitalWrite(Relay, LOW);
  delay(1);
}
