

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char *ssid = "Ardberry_Technology"; // The name of the Wi-Fi network that will be created
const char *password = "ardberrytechnology";

IPAddress local_ip(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);


//ESP_pin_layout
const int Relay_1A=0;
const int Relay_1B=1;
const int Relay_2A=2;
const int Relay_2B=3;

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
  else 
  {     //Parameter found
      message = "slider1 = ";
      message += server.arg("slider1");     //Gets the value of the query parameter
  }
  if (server.arg("slider2")== "")
  {     message = "Slider2 Argument not found";
  }
  else
  {     //Parameter found
      message = "slider2 = ";
      message += server.arg("slider2");     //Gets the value of the query parameter
  }*/

  String a1 = server.arg("slider1");
  int angle1 = a1.toInt();
  if(angle1 < 0)angle1 *=-1;
  String a2 = server.arg("slider2");
  int angle2 = a2.toInt();
  if(angle2 < 0)angle2 *=-1;
  
  // 1st Vertical slider system
  //Change Relay-1A State as per request
  if(server.arg("slider1")> "0")
  {    
    digitalWrite(Relay_1A, HIGH);       //Relay_1A forward Turned on
    delay(1000*angle1);
    digitalWrite(Relay_1A, LOW);
  }
  //Change Relay-1B State as per request
  if(server.arg("slider1")< "0")
  {
    digitalWrite(Relay_1B, HIGH);       //Relay_1B forward Turned on
    delay(1000*angle1);
    digitalWrite(Relay_1B, LOW);
  }

  // 2nd Vertical slider system
  //Change Relay-2A State as per request
  if(server.arg("slider2")> "0")
  {    
    digitalWrite(Relay_2A, HIGH);       //Relay_1A forward Turned on
    delay(1000*angle2);
    digitalWrite(Relay_2A, LOW);
  }
  //Change Relay-1B State as per request
  if(server.arg("slider2")< "0")
  {
    digitalWrite(Relay_2B, HIGH);       //Relay_1B forward Turned on
    delay(1000*angle2);
    digitalWrite(Relay_2B, LOW);
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

  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  
  Serial.print("Access Point \"");
  Serial.print(ssid);
  Serial.println("\" started");

  Serial.print("IP address:\t");
  Serial.println(WiFi.softAPIP());

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

void loop(void){
  server.handleClient();
}
