#include <ESP8266WiFi.h>        // Librería Wi-Fi
#include "DHT.h"        // Librería DHT
int timeSinceLastRead = 0;
const char* ssid ="TeleCentro-f729";
const char* password ="JZYCJYJZWZHD";
#define DHTPIN 4 // Declaración de pin (D2)
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);         // Velocidad
  delay(10);
  Serial.println('\n');
  WiFi.begin(ssid, password);             // Conexión a la red
  Serial.print("Connecting to ");
  Serial.print(ssid); Serial.println(" ...");
  int timeSinceLastRead = 0;
  int i = 0;
  while (WiFi.status() != WL_CONNECTED) { // Esperando a que se conecte
    delay(1000);
    Serial.print(++i); Serial.print(' ');
  }
  Serial.println('\n');
  Serial.println("Connection established!");  
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());         // Muestra IP del ESP8266
  dht.begin();
}


void loop() {
  if(timeSinceLastRead > 2000) {
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    float f = dht.readTemperature(true);
    if (isnan(h) || isnan(t) || isnan(f)) {
      Serial.println("Failed to read from DHT sensor!");
      timeSinceLastRead = 0;
      return;
    }
    float hif = dht.computeHeatIndex(f, h);
    float hic = dht.computeHeatIndex(t, h, false);
    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.print(" %\t");
    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.print(" *C ");
    Serial.print(f);
    Serial.print(" *F\t");
    Serial.print("Heat index: ");
    Serial.print(hic);
    Serial.print(" *C ");
    Serial.print(hif);
    Serial.println(" *F");

    timeSinceLastRead = 0;
  }
  delay(100);
  timeSinceLastRead += 100;
}
