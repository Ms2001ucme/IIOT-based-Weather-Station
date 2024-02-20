#include <DHT.h>
#include <WiFi.h>
#include <ThingsBoard.h>

#define DHTPIN 5
#define DHTTYPE DHT11

#define rainAnalog 35
//#define rainDigital 34

int moisture,sensor_analog;
const int sensor_pin = A0;  /* Soil moisture sensor O/P pin*/


DHT dht(DHTPIN, DHTTYPE);
WiFiClient wifiClient;
ThingsBoard tb(wifiClient);

const char* ssid = "iPhone";
const char* password = "abhi12356";
const char* tbHost = "demo.thingsboard.io";
const char* tbToken = "bzzvDlNgXjXZDgjKQhNp";

void setup() {
 
  Serial.begin(115200);
  dht.begin();
  Serial.println("Connecting to Wi-Fi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to Wi-Fi...");
  }

  Serial.println("Connected to Wi-Fi");
  Serial.println("Connecting to ThingsBoard...");

  if (!tb.connect(tbHost, tbToken)) {
    Serial.println("Failed to connect to ThingsBoard");
    while (1);
  }
  Serial.println("Connected to ThingsBoard");
}

void loop() {
  //int moist_value = analogRead(34);
  //int rain_value = analogRead(35);
 
  sensor_analog = analogRead(sensor_pin);
  moisture = ( 100 - ( (sensor_analog/4095.00) * 100 ) );

  //int rain = map(rain_value,4095,25,0,100);
  int rainAnalogVal = analogRead(rainAnalog);
  int rain = ( 100 - ( (rainAnalogVal/4095.00) * 100 ) );
  //int rainDigitalVal = digitalRead(rainDigital);
   
 
 
   
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  
  Serial.print("Soil moisture: ");
  Serial.print(moisture);
  Serial.println("%");

  Serial.print("Rain: ");
  Serial.print(rain);
  Serial.println(" %");
  // Serial.print("\t");
  // Serial.println(rainDigitalVal);
 
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");
  
 
  tb.sendTelemetryFloat("temperature", temperature);
  tb.sendTelemetryFloat("humidity", humidity);
  tb.sendTelemetryFloat("Soil moisture", moisture);
  tb.sendTelemetryFloat("Rain", rain);

  delay(2000);
}
