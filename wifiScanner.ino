#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WiFiUdp.h> 
#include <ESP8266WebServer.h>
 
ESP8266WebServer server(8080);

IPAddress local_IP(10,0,0,130);
IPAddress gateway(10,0,0,104);
IPAddress subnet(255,255,255,0);

void handle_OnConnect() {
	String resp ;
	resp = "Conectado";
	Serial.println();
	Serial.print("Conneted: ");
	Serial.println(resp);
	server.send(200, "text/html", resp); 
}

void request(){
	String resp ;
	String vrg;

	for (int i = 0; i < server.args(); i++) {
		if(i+1 == server.args()){
			vrg = "";
		}else{
			vrg = ";";
		}
		resp += server.argName(i) + ":" + server.arg(i) + vrg;     
	}

	Serial.println(resp);
	String msg = "";
	
	int count = 1;
	while (msg == ""){
		msg =  SerialStringConstructor();
		count += 1;
		if(count == 200*1000){
			msg = "ST:erro;ME:falha na comunicação com o controlador";
		}
	}

  	server.send(200, "text/html", msg); 
}

void setup(){
	Serial.begin(115200);

	//wifiClientBegin(local_IP, gateway, subnet);
	softApBegin(local_IP, gateway, subnet);

	server.on("/", handle_OnConnect);
	server.on("/request", request);
	server.enableCORS(true);
	server.begin();
}
void loop() {
	server.handleClient();
	delay(200);
}
  
