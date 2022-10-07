#define FAN_PIN 25

int fanSpeed=100;
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;

void setup() {
  //pinMode(FAN_PIN, OUTPUT);
  // configure LED PWM functionalitites
  ledcSetup(ledChannel, freq, resolution);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(FAN_PIN, ledChannel);

  Serial.begin(9600);

}

void loop() {
  fanSpeed = (fanSpeed+5)%255;
  //analogWrite(FAN_PIN,fanSpeed);  
  ledcWrite(ledChannel, fanSpeed);
  Serial.println(fanSpeed);
  delay(500);
}
