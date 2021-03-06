#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>

const char *ssid = "ROBO";
const char *password = "semsenha";

ESP8266WebServer server(80);
//192.168.4.1


#define D0 16
#define D1 5
#define D2 4
#define D3 0

void handleRoot() {
    response();
}

void frente() {
digitalWrite(5,HIGH);
digitalWrite(16,LOW);
digitalWrite(4,HIGH);
digitalWrite(0,LOW);
  response();
}

void direita() {
digitalWrite(5,HIGH);
digitalWrite(16,LOW);
digitalWrite(4,LOW);
digitalWrite(0,LOW);
  response();
}

void esquerda() {
digitalWrite(5,LOW);
digitalWrite(16,LOW);
digitalWrite(4,HIGH);
digitalWrite(0,LOW);
  response();
}

void parar() {
digitalWrite(5,LOW);
digitalWrite(16,LOW);
digitalWrite(4,LOW);
digitalWrite(0,LOW);
  response();
}

void traz() {
digitalWrite(16,HIGH);
digitalWrite(5,LOW);
digitalWrite(0,HIGH);
digitalWrite(4,LOW);
  response();
}


const String HtmlHtml = "<html><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\" /></head>";
const String HtmlHtmlClose = "</html>";
const String HtmlTitle = "<h1><font color='RED'><center>ROBO MOVEL</center></font></h1><br/>\n";

const String HtmlButtons = "<a href=\"frente\"><button style=\"display: block; width: 100%;\"><strong>FRENTE</strong></button></a><br/><a href=\"parar\"><button style=\"display: block; width: 100%;\"><strong>PARAR</strong></button></a><br/><a href=\"traz\"><button style=\"display: block; width: 100%;\"><strong>TRAZ</strong></button></a><br/><a href=\"esquerda\"><button style=\"display: block; width: 100%;\"><strong>ESQUERDA</strong></button></a><br/><a href=\"direita\"><button style=\"display: block; width: 100%;\"><strong>DIREITA</strong></button></a><br/>";

void response(){
  String htmlRes = HtmlHtml + HtmlTitle;
  htmlRes += HtmlButtons;
  htmlRes += HtmlHtmlClose;

  server.send(200, "text/html", htmlRes);
}

void setup() {
  delay(1000);
  Serial.begin(115200);
 pinMode(16,OUTPUT);
digitalWrite(16,0); 
pinMode(5, OUTPUT); 
digitalWrite(5, 0); 
pinMode(4, OUTPUT);
digitalWrite(4, 0); 
pinMode(0, OUTPUT); 
digitalWrite(0, 0); 
  Serial.println();
  Serial.print("Configuring access point...");
  // 5 e 4 frente -- 16 e 0 traz

  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/", handleRoot);
  server.on("/frente", frente);
  server.on("/traz", traz);
  server.on("/parar", parar);
  server.on("/direita", direita);
  server.on("/esquerda", esquerda);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
server.handleClient();

} 


