int led = D7;
int sensor = A0;
int lightLevel = 0;

void setup() {
  pinMode(led, OUTPUT);
  pinMode(sensor, INPUT);

  Particle.variable("lightLevel", lightLevel);
}

void loop() {
  lightLevel = analogRead(sensor);
  delay(100);
}
