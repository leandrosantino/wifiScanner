String SerialStringConstructor(){
  String conteudo = "";
  char caractere;
  while(Serial.available() > 0) {
    caractere = Serial.read();
    if (caractere != '\n'){
      conteudo.concat(caractere);
    }else{
      conteudo.concat("");
    }
    delay(10);
  }
  return conteudo;
}

void softApBegin(IPAddress local_IP,IPAddress gateway,IPAddress subnet){
    const char *ssid = "ManuServer";
    const char *password = "MAN@adler";

    Serial.println();
    Serial.print("Setting soft-AP configuration ... ");
    Serial.println(WiFi.softAPConfig(local_IP, gateway, subnet) ? "Ready" : "Failed!");
    Serial.print("Setting soft-AP ... ");
    Serial.println(WiFi.softAP(ssid,password) ? "Ready" : "Failed!");

    Serial.print("Soft-AP IP address = ");
    Serial.println(WiFi.softAPIP()); 
}

void wifiClientBegin(IPAddress local_IP,IPAddress gateway,IPAddress subnet){
    const char* ssid = "Click.com";
    const char* pass = "comum104";

    WiFi.begin(ssid, pass);
    WiFi.config(local_IP, gateway, subnet, gateway);
    
    while(WiFi.status() != WL_CONNECTED){
        delay(200);
        Serial.print(".");
    }

    Serial.print("Connected!! IP_address: ");
    Serial.println(WiFi.localIP());
}