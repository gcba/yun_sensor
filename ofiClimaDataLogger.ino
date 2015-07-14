#include <FileIO.h>
#include <Process.h>
#include "DHT.h"
#define DHTPIN 7
#define DHTTYPE DHT11
#define SENSORID 90
DHT dht(DHTPIN, DHTTYPE);


float h , t, l;
boolean getSensorsData(){
  Serial.println("OBTENIENDO INFORMACION DE SENSORES");
  Serial.println("");
  boolean r = false;
   l = analogRead(0);
   l = 900-l;
   h = dht.readHumidity();
   t = dht.readTemperature();
    if (!isnan(h) & !isnan(t) & !isnan(l)) {
      r=true;
  }else{
    Serial.println("FALLO-SENSORES");
    }
  return r;
}
void setup() {
  Bridge.begin();
  Serial.begin(9600);
  Serial.println("INICIANDO...");
  Serial.print("-------------------[");
  Serial.print(getTimeStamp());
  Serial.print("]-------------------");
  getConexionStatus();
  }

  String getTimeStamp() {
  String result;
  Process time;
  time.begin("date");
  time.addParameter("+%D-%T");
  time.run();
  while (time.available() > 0) {
    char c = time.read();
    if (c != '\n')
      result += c;
  }
  return result;
}

String pushData() {
  
  Serial.println("PUSHEANDO DATOS A LA API");
  Serial.println("");
  Process upload;
  String cmd = "python /mnt/sda1/labDL/pushDataToApi.py "+String(SENSORID)+" "+String(t)+" "+ String(h)+" "+String(l);
  upload.runShellCommand(cmd);
  String r = "";
  while (upload.available()) {
    char c = upload.read();
    r += c;
    //Serial.print(c);
  }
  return r;
}



void printSensorsData(){
  Serial.print("DATOS SENSADOS A LAS: ");
  Serial.println(getTimeStamp());
  Serial.print("humedad: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperatura: ");
  Serial.print(t);
  Serial.print(" ªC \t");
  Serial.print("Luminosidad: ");
  Serial.print(l);
  Serial.println(" lums. ");
  Serial.println("");
}




void getConexionStatus() {
  Process wifiCheck;
  wifiCheck.runShellCommand("/usr/bin/pretty-wifi-info.lua");  // command you want to run
  while (wifiCheck.available() > 0) {
    char c = wifiCheck.read();
    Serial.print(c);
  }
  Serial.println();
  delay(500);
}




void loop() {
  if(getSensorsData() == true){
    printSensorsData();
    pushData();
  }
  delay(8000);
}
