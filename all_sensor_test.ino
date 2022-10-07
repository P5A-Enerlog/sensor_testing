#include "max6675.h"
#include "DHT.h"

#define FAN_PIN 14

#define DHTPIN 26
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

const int RecordTime = 3; //Define Measuring Time (Seconds)
const int SensorPin = 27;  //Define Interrupt Pin (2 for Arduino Uno)

int fanSpeed=200;
int fanCount =0;
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;

int InterruptCounter;
float WindSpeed;

int thermoDO = 19;
int thermoCS = 5;
int thermoCLK = 18;

MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);

void setup() {
  Serial.begin(9600);
  dht.begin();


  // wait for MAX chip to stabilize
  delay(500);

  ledcSetup(ledChannel, freq, resolution);
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(FAN_PIN, ledChannel);

  delay(500);  
}

void loop() {
  // DHT
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
  } else {
 // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.println(F("°C "));
  }
 

  delay(1000);

  //thermocouple
  Serial.print("Thermocouple, C = "); 
  Serial.println(thermocouple.readCelsius());

  delay(1000);
  
 //anemometer
  measure();
  Serial.print("Wind Speed: ");
  Serial.print(WindSpeed);       //Speed in km/h
  Serial.print(" km/h - ");
  Serial.print(WindSpeed / 3.6); //Speed in m/s
  Serial.println(" m/s"); 

  delay(1000);

  //fan
  fanSpeed = (fanCount%2==0)*255;
  ledcWrite(ledChannel, fanSpeed);
  Serial.print("fan speed: ");
  Serial.println(fanSpeed);
  fanCount++;


  delay(2000);
  Serial.println("------------------");
}

void measure() {
  InterruptCounter = 0;
  attachInterrupt(digitalPinToInterrupt(SensorPin), countup, RISING);
  delay(1000 * RecordTime);
  detachInterrupt(digitalPinToInterrupt(SensorPin));
  WindSpeed = (float)InterruptCounter / (float)RecordTime * 2.4;
}

void countup() {
  InterruptCounter++;
}