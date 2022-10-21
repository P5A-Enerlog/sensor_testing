//Pyranomètre SP-215
#define analogPin 2 // pin de sortie du pyranomètre

float pyr = 0; // initialisation du pyranomètre


void setup() {
  pinMode(analogPin, INPUT);


  Serial.begin(9600);

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

}


void loop() {
//PYRANOMETRE

  pyr = analogRead(analogPin);
  //pyr = pyr * ((0.4 * 5000) / 1023); // Arduino Mega conversion output: int between 0 and 1023 corresponding to voltage between 0 and 5V (5000 mV). The sensor output 2.5 mV per W/M²
  pyr = pyr * ((0.4 * 3300) / 4095); // ESP32 conversion : 0-4096 -> 0-3.3Vs

  Serial.println(pyr);

  delay(500); // Delay de 5 minutes
}
