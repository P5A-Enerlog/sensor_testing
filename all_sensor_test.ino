#include "max6675.h"
#include "DHT.h"

int thermoDO = 19;
int thermoCS = 23;
int thermoCLK = 18;
int therm2 = 5;

MAX6675 thermocouple1(thermoCLK, thermoCS, thermoDO);
MAX6675 thermocouple2(thermoCLK, therm2, thermoDO);

void setup() {
  Serial.begin(9600);

  Serial.println("MAX6675 test");
  // wait for MAX chip to stabilize
  delay(500);
}

void loop() {
  // basic readout test, just print the current temp
  
   Serial.print("C = "); 
   Serial.println(thermocouple1.readCelsius());
   Serial.print("C = ");
   Serial.println(thermocouple2.readCelsius());
 
   // For the MAX6675 to update, you must delay AT LEAST 250ms between reads!
   delay(1000);
}