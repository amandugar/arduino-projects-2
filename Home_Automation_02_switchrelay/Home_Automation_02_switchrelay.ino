#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char *ssid = "Ardberry"; // The name of the Wi-Fi network that will be created
const char *password = "ardtech";

IPAddress local_ip(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);


//ESP_pin_layout
const int Switch_1=0;
const int Switch_2=1;
const int Switch_3=2;
const int Switch_4=3;

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
 
<TR><TD>
<INPUT TYPE=SUBMIT VALUE="switch1on" name=submit>
<INPUT TYPE=SUBMIT VALUE="switch1off" name=submit>
</TD>
<TD>Switch_1</TD></TR>
 
<TR><TD>
<INPUT TYPE=SUBMIT VALUE="switch2on" name=submit>
<INPUT TYPE=SUBMIT VALUE="switch2off" name=submit>
</TD>
<TD>Switch_2</TD></TR>
 
<TR><TD>
<INPUT TYPE=SUBMIT VALUE="switch3on" name=submit>
<INPUT TYPE=SUBMIT VALUE="switch3off" name=submit>
</TD>
<TD>Switch_3</TD></TR>
 
<TR><TD>
<INPUT TYPE=SUBMIT VALUE="switch4on" name=submit>
<INPUT TYPE=SUBMIT VALUE="switch4off" name=submit>
</TD>
<TD>Switch_4</TD></TR>
 
</TABLE> 
</CENTER>
</BODY>
</HTML>
)=====";
 
ESP8266WebServer server(80);

String S1Status,S2Status,S3Status,S4Status;   //web

String appinput;    //app
String readString;

void handleRoot() {
  String web = MAIN_page;    
  web.replace("Switch_1", S1Status);
  web.replace("Switch_2", S2Status);
  web.replace("Switch_3", S3Status);
  web.replace("Switch_4", S4Status);
  server.send(200, "text/html", web);    
}
 
void handlespecificArgs(){

  String message="";
  
  if (server.arg("switch")== "")
  {     message = "Switch Argument not found";
  }
  else
  {     //Parameter found
      message = "switch = ";
      message += server.arg("switch");     //Gets the value of the query parameter
  }     

  //Change Switch-1 State as per request
  if(server.arg("switch")== "switch1on")
  {    
    digitalWrite(Switch_1, HIGH);       //Load1 Turned on
  }
  if(server.arg("switch")== "switch1off")
  {
    digitalWrite(Switch_1, LOW);      //Load1 Turned off  
  }

  //Change Switch-2 State as per request
  if(server.arg("switch")== "switch2on")
  {    
    digitalWrite(Switch_2, HIGH);       //Load1 Turned on
  }
  if(server.arg("switch")== "switch2off")
  {
    digitalWrite(Switch_2, LOW);      //Load1 Turned off  
  }

  //Change Switch-3 State as per request
  if(server.arg("switch")== "switch3on")
  {    
    digitalWrite(Switch_3, HIGH);       //Load1 Turned on
  }
  if(server.arg("switch")== "switch3off")
  {
    digitalWrite(Switch_3, LOW);      //Load1 Turned off  
  }

  //Change Switch-4 State as per request
  if(server.arg("switch")== "switch4on")
  {    
    digitalWrite(Switch_4, HIGH);       //Load1 Turned on
  }
  if(server.arg("switch")== "switch4off")
  {
    digitalWrite(Switch_4, LOW);      //Load1 Turned off  
  }

  server.sendHeader("Location", "/specificArgs");
  server.send(200, "text/plain", message);
  
  delay(500);
}

void handleForm() {
  String t_state = server.arg("submit");    //web
  
//Change Switch-1 State as per request      //web
  if(t_state=="switch1on")
  {
    S1Status="ON";    
    digitalWrite(Switch_1, HIGH);       //Load1 Turned on
  }
  
  if(t_state=="switch1off")
  {
    S1Status="OFF";    
    digitalWrite(Switch_1, LOW);      //Load1 Turned off  
  }
//Change Switch-2 State as per request
  if(t_state=="switch2on")
  {
    S2Status="ON";    
    digitalWrite(Switch_2, HIGH);       //Load1 Turned on
  }
  
  if(t_state=="switch2off")
  {
    S2Status="OFF";    
    digitalWrite(Switch_2, LOW);      //Load1 Turned off  
  }
//Change Switch-3 State as per request
  if(t_state=="switch3on")
  {
    S3Status="ON";    
    digitalWrite(Switch_3, HIGH);       //Load1 Turned on
  }
  
  if(t_state=="switch3off")
  {
    S3Status="OFF";    
    digitalWrite(Switch_3, LOW);      //Load1 Turned off  
  }
//Change Switch-4 State as per request
  if(t_state=="switch4on")
  {
    S4Status="ON";    
    digitalWrite(Switch_4, HIGH);       //Load1 Turned on
  }
  
  if(t_state=="switch4off")
  {
    S4Status="OFF";    
    digitalWrite(Switch_4, LOW);      //Load1 Turned off  
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

  pinMode(Switch_1, OUTPUT);
  pinMode(Switch_2, OUTPUT);
  pinMode(Switch_3, OUTPUT);
  pinMode(Switch_4, OUTPUT);

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
