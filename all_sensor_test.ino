#include "max6675.h"
#include "DHT.h"

DHT dht1(36, DHT22);
DHT dht2(39, DHT22);
DHT dht3(34, DHT22);
DHT dht4(35, DHT22);

DHT dht();

int thermoDO = 19;
int thermoCS = 23;
int thermoCLK = 18;
int therm2 = 5;

MAX6675 thermocouple1(thermoCLK, thermoCS, thermoDO);
MAX6675 thermocouple2(thermoCLK, therm2, thermoDO);

void setup() {
  Serial.begin(9600);
  Serial.println("What DHT22 sensor do you want to test:");
  int dhtNum = Serial.read();
  char conv = dhtNum + '0';
  char* dhtSelect = "dht";
  strcat(dhtSelect, &conv);

  DHT dht(36, DHT22);
  
  dht1.begin();

  // wait for MAX chip to stabilize
  delay(500);
}

void loop() {
  Serial.println("Hum = ");
  Serial.print(dht1.readHumidity());
  Serial.print("   ");
  Serial.println("Temp = ");
  Serial.print(dht1.readTemperature());

  Serial.println("C1 = ");
  Serial.print(thermocouple1.readCelsius());
  Serial.print("   ");
  Serial.print("C2 = ");
  Serial.print(thermocouple2.readCelsius());

  delay(1000);
}