#include "max6675.h"
#include "DHT.h"

#define DHTPIN 2
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

int thermoDO = 19;
int thermoCS = 23;
int thermoCLK = 18;
int therm2 = 5;

MAX6675 thermocouple1(thermoCLK, thermoCS, thermoDO);
MAX6675 thermocouple2(thermoCLK, therm2, thermoDO);

void setup() {
  Serial.begin(9600);

  Serial.println("MAX6675 test");
  dht.begin();

  // wait for MAX chip to stabilize
  delay(500);
}

void loop() {
  Serial.println("Hum = ");
  Serial.print(dht.readHumidity());
  Serial.print("   ");
  Serial.println("Temp = ");
  Serial.print(dht.readTemperature());

  Serial.println("C1 = ");
  Serial.print(thermocouple1.readCelsius());
  Serial.print("   ");
  Serial.print("C2 = ");
  Serial.print(thermocouple2.readCelsius());

  // For the MAX6675 to update, you must delay AT LEAST 250ms between reads!
  delay(1000);
}