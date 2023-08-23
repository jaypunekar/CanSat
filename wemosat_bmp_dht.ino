#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include "DHT.h"
#include "index.h" //Our HTML webpage contents with javascripts 

float ref;

Adafruit_BMP280 bmp; // I2C
#define DHTPIN D4     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);
 
//SSID and Password of your WiFi router
const char* ssid = "Gags";
const char* password = "268620880000";
 
ESP8266WebServer server(80); //Server on port 80
 
//===============================================================
// This routine is executed when you open its IP in browser
//===============================================================
void handleRoot() {
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}
 
float h=0, t=0, tf=0, a=0, dp=0, Alt=0;
 
void handleADC() {

 String data = "{\"ADC\":\""+String(a)+"\", \"East_Temp\":\""+ String(t) +"\", \"West_Temp\":\""+ String(tf) +"\", \"Humidity\":\""+ String(h) +"\", \"Altitude\":\""+ String(Alt) +"\"}";
 
 server.send(200, "text/plane", data); //Send ADC value, temperature and humidity JSON to client ajax request
 
    h = dht.readHumidity();
    t = bmp.readTemperature();
    tf = dht.readTemperature();
    dp = t-0.36*(100.0-h);
    Alt = bmp.readAltitude(ref);
    a = bmp.readPressure()/1000.0F;

    delay(100);
 
  Serial.print(h, 1);
  Serial.print(t, 1);
  Serial.print(a, 1);
}
 
//==============================================================
//                  SETUP
//==============================================================

void setup()
{
  Serial.begin(9600);
  Serial.println();
 
 // Wire.begin(D3, D4);
 // Wire.setClock(100000);
  
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("");
 

  
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
 
  server.on("/", handleRoot);      //Which routine to handle at root location. This is display page
  server.on("/readADC", handleADC); //This page is called by java Script AJAX
 
  server.begin();                  //Start server
  Serial.println("HTTP server started");

  if (!bmp.begin(0x76)) {
    Serial.println("Could not find a valid BMP280 sensor, check wiring!");
 //   while (1); 
 }

  dht.begin();

  ref = bmp.readPressure() / 100;
}
 
//==============================================================
//                     LOOP
//==============================================================
void loop()
{
  server.handleClient();          //Handle client requests
}
