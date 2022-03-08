//header files
#include <ESP8266WiFi.h>
//#include <WiFiClient.h>
#include <ESP8266WebServer.h>

//HTML page
const char MAIN_page[] = R"=====(
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
 
<TR><TD>
<INPUT TYPE=SUBMIT VALUE="ON1" name=submit>
<INPUT TYPE=SUBMIT VALUE="OFF1" name=submit>
</TD>
<TD>Light_1</TD></TR>
 
<TR><TD>
<INPUT TYPE=SUBMIT VALUE="ON2" name=submit>
<INPUT TYPE=SUBMIT VALUE="OFF2" name=submit>
</TD>
<TD>Light_2</TD></TR>
 
<TR><TD>
<INPUT TYPE=SUBMIT VALUE="ON3" name=submit>
<INPUT TYPE=SUBMIT VALUE="OFF3" name=submit>
</TD>
<TD>Fan_1</TD></TR>
 
<TR><TD>
<INPUT TYPE=SUBMIT VALUE="ON4" name=submit>
<INPUT TYPE=SUBMIT VALUE="OFF4" name=submit>
</TD>
<TD>Fan_2</TD></TR>
 
</TABLE> 
</CENTER>
</BODY>
</HTML>
)=====";

//ESP_pin_layout
const int Light_1=2;
const int Light_2=14;
const int Fan_1=12;
const int Fan_2=13;

//ID_PAss
const char* ssid = "Ardberry";
const char* password = "ardtech123";
 
IPAddress local_ip(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

ESP8266WebServer server(80);

String L1Status,L2Status,F1Status,F2Status;

void handleRoot() {
  String s = MAIN_page;    
  s.replace("Light_1", L1Status);
  s.replace("Light_2", L2Status);
  s.replace("Fan_1", F1Status);
  s.replace("Fan_2", F2Status);
  server.send(200, "text/html", s);    
}
 
void handleForm() {
  String t_state = server.arg("submit");

//Change Light-1 State as per request
  if(t_state=="ON1")
  {
    L1Status="ON";    
    digitalWrite(Light_1, HIGH);       //Load1 Turned on
  }
  
  if(t_state=="OFF1")
  {
    L1Status="OFF";    
    digitalWrite(Light_1, LOW);      //Load1 Turned off  
  }
//Change Light-2 State as per request
  if(t_state=="ON2")
  {
    L2Status="ON";    
    digitalWrite(Light_2, HIGH);       //Load1 Turned on
  }
  
  if(t_state=="OFF2")
  {
    L2Status="OFF";    
    digitalWrite(Light_2, LOW);      //Load1 Turned off  
  }
//Change Fan-1 State as per request
  if(t_state=="ON3")
  {
    F1Status="ON";    
    digitalWrite(Fan_1, HIGH);       //Load1 Turned on
  }
  
  if(t_state=="OFF3")
  {
    F1Status="OFF";    
    digitalWrite(Fan_1, LOW);      //Load1 Turned off  
  }
//Change Fan-2 State as per request
  if(t_state=="ON4")
  {
    F2Status="ON";    
    digitalWrite(Fan_2, HIGH);       //Load1 Turned on
  }
  
  if(t_state=="OFF4")
  {
    F2Status="OFF";    
    digitalWrite(Fan_2, LOW);      //Load1 Turned off  
  }
 
  server.sendHeader("Location", "/");
  server.send(302, "text/plain", "Updated-- Press Back Button");  //This Line Keeps It on Same Page
   
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
delay(1000);
Serial.begin(115200);

pinMode(Light_1, OUTPUT);
pinMode(Light_2, OUTPUT);
pinMode(Fan_1, OUTPUT);
pinMode(Fan_2, OUTPUT);

WiFi.softAP(ssid,password);
WiFi.softAPConfig(local_ip, gateway, subnet);

/*WiFi.mode(WIFI_STA);
WiFi.begin(ssid, password);
  
Serial.println("");

Serial.println("");
Serial.print("Connected to ");
Serial.println(ssid);
  
Serial.print("IP address: ");
Serial.println(WiFi.localIP());
 
// Wait for connection
while (WiFi.status() != WL_CONNECTED) {
   delay(500);
   Serial.print(".");
}*/
server.on("/", handleRoot);
server.on("/form", handleForm);
server.onNotFound(handleNotFound);

server.begin();
Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
}
