#include <ESP8266WiFi.h>        // Include the Wi-Fi library
#include <ESP8266WebServer.h>

const char* ssid     = "rohan";         // The SSID (name) of the Wi-Fi network you want to connect to
const char* password = "123456789";     // The password of the Wi-Fi network

//ESP_pin_layout
const int steppin_1=4;
const int dirpin_1=5;

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

  String message="";
  
  if (server.arg("slider1")== "")
  {     message = "Slider1 Argument not found";
  }
  else
  {     //Parameter found
      message = "slider1 = ";
      message += server.arg("slider1");     //Gets the value of the query parameter
  }

  String a1 = server.arg("slider1");
  int angle1 = a1.toInt();
  if(angle1 < 0)angle1 *=-1;
  //String a2 = server.arg("slider2");
  //int angle2 = a2.toInt();
  //if(angle2 < 0)angle2 *=-1;
  
  // 1st Vertical slider system
  //To rotate forward as per request
  if(server.arg("slider1")> "0")
  {    
    digitalWrite(dirpin_1,HIGH);
    
    for(int x = 0; x <200*angle1; x++)
    {
      digitalWrite(steppin_1,HIGH);
      delayMicroseconds(1000);           //clockwise one complete rotation
      digitalWrite(steppin_1,LOW);
      delayMicroseconds(1000);   
    }
  }
  //To rotate backward as per request
  if(server.arg("slider1")< "0")
  {
    digitalWrite(dirpin_1,LOW);
    
    for(int x = 0; x <200*angle1; x++)
    {
      digitalWrite(steppin_1,HIGH);
      delayMicroseconds(1000);           //clockwise one complete rotation
      digitalWrite(steppin_1,LOW);
      delayMicroseconds(1000);   
    }
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


void setup() {
  Serial.begin(115200);         // Start the Serial communication to send messages to the computer
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

  pinMode(steppin_1, OUTPUT);
  pinMode(dirpin_1, OUTPUT);
  
  server.on("/", handleRoot);
  server.on("/form", handleForm);
  server.onNotFound(handleNotFound);

  server.on("/specificArgs", handlespecificArgs);   //app
  
  server.begin();
  Serial.println("HTTP server started");
  Serial.println("Server Listening");     //app
  

}

void loop() { 
  server.handleClient();  
}
