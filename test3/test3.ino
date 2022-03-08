#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
const char *ssid = "Ardberry"; // The name of the Wi-Fi network that will be created
const char *password = "ardtech123";
IPAddress local_ip(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);
//HTML page
const char MAIN_page[]  = R"=====(
<!DOCTYPE html>
<HTML>
<TITLE>
Ardberry Technology Home Automation System
</TITLE>
<BODY>
<CENTER>
ABC

</CENTER>
</BODY>
</HTML>
)=====";
ESP8266WebServer server(80);
String readString;
void handleRoot() {
  String web = MAIN_page;    
  server.send(200, "text/html", web);    
}

void setup(){
  
  Serial.begin(115200);
  delay(10);
  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  server.on("/", handleRoot); 
  server.begin();
}

void loop(void){
  server.handleClient();
}
