//Pyranomètre SP-215
int analogPin = A2; // pin de sortie du pyranomètre
float pyr = 0; // initialisation du pyranomètre


void setup() {


  Serial.begin(9600);

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

}

void loop() {
//PYRANOMETRE

  pyr = analogRead(analogPin); ()
  pyr = pyr * ((0.4 * 5000) / 1023); // conversion de volt à W/m²  output: int between 0 and 1023 corresponding to voltage between 0 and 5V (5000 mV). The sensor output 2.5 mV per W/M²

  Serial.println(pyr);

  delay(500); // Delay de 5 minutes
}
