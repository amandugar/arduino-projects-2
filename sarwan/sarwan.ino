

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid     = "rohan";         // The SSID (name) of the Wi-Fi network you want to connect to
const char* password = "123456789";     // The password of the Wi-Fi network
 
//ESP_pin_layout
const int Relay_1A=4;
const int Relay_1B=5;
const int Relay_2A=0;
const int Relay_2B=2;

//HTML page
const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<HTML>
<TITLE>
Ardberry Technology Home Automation System
</TITLE>
<BODY>
<CENTER>
<FORM method="post" action="/form">
<TABLE>
<TR><TD colspan=2><B>IoT Based Home Automation System</B></TD></TR>
</TABLE> 
</CENTER>
</BODY>
</HTML>
)=====";
 
ESP8266WebServer server(80);

void handleRoot() {
  String web = MAIN_page;    
  server.send(200, "text/html", web);    
}
 
void handlespecificArgs(){

  digitalWrite(Relay_1A, LOW);
  digitalWrite(Relay_1B, LOW);
  digitalWrite(Relay_2A, LOW);
  digitalWrite(Relay_2B, LOW);
  
  String message="";
  
  /*if (server.arg("slider1")== "")
  {     message = "Slider1 Argument not found";
  }
  else if
  {     //Parameter found
      message = "slider1 = ";
      message += server.arg("slider1");     //Gets the value of the query parameter
  }
  else if (server.arg("slider2")== "")
  {     message = "Slider2 Argument not found";
  }
  else
  {     //Parameter found
      message = "slider2 = ";
      message += server.arg("slider2");     //Gets the value of the query parameter
  }*/

  
  // 1st Vertical slider system
  //Change Relay-1A State as per request
  if(server.arg("slider1") == "1")
  {    
    digitalWrite(Relay_1A, HIGH);       //Relay_1A forward Turned on
    delay(1000);
    digitalWrite(Relay_1A, LOW);
    ESP.wdtFeed();
  }
  //Change Relay-1B State as per request
  if(server.arg("slider1") == "-1")
  {
    digitalWrite(Relay_1B, HIGH);       //Relay_1B forward Turned on
    delay(1000);
    digitalWrite(Relay_1B, LOW);
    ESP.wdtFeed();
  }

  // 2nd Vertical slider system
  //Change Relay-2A State as per request
  if(server.arg("slider2") == "1")
  {    
    digitalWrite(Relay_2A, HIGH);       //Relay_1A forward Turned on
    delay(1000);
    digitalWrite(Relay_2A, LOW);
    ESP.wdtFeed();
  }
  //Change Relay-1B State as per request
  if(server.arg("slider2") == "-1")
  {
    digitalWrite(Relay_2B, HIGH);       //Relay_1B forward Turned on
    delay(1000);
    digitalWrite(Relay_2B, LOW);
    ESP.wdtFeed();
  }
  
  
  

  server.sendHeader("Location", "/specificArgs");
  server.send(200, "text/plain", message);
  
  delay(500);
}

void handleForm() {
  server.sendHeader("Location", "/");
  delay(500);
}

void handleNotFound() {

  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void setup(){
  
  Serial.begin(115200);
  delay(10);
  Serial.println('\n');

  WiFi.begin(ssid, password);             // Connect to the network
  Serial.print("Connecting to ");
  Serial.print(ssid); Serial.println(" ...");

  int i = 0;
  while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
    delay(1000);
    Serial.print(++i); Serial.print(' ');
  }

  Serial.println('\n');
  Serial.println("Connection established!");  
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());         // Send the IP address of the ESP8266 to the computer


  pinMode(Relay_1A, OUTPUT);
  pinMode(Relay_1B, OUTPUT);
  pinMode(Relay_2A, OUTPUT);
  pinMode(Relay_2B, OUTPUT);

  server.on("/", handleRoot);
  server.on("/form", handleForm);
  server.onNotFound(handleNotFound);

  server.on("/specificArgs", handlespecificArgs);   //app
  
  server.begin();
  Serial.println("HTTP server started");
  Serial.println("Server Listening");     //app
  

}

void loop(){
  server.handleClient();
}
