int led = D0;
int sensor = A0;
int lightLevel = 0;
int threshold = 3200;
bool occupied = false;

void setup() {
  pinMode(led, OUTPUT);
  pinMode(sensor, INPUT);

  Particle.function("setThreshold", setThreshold);
  Particle.variable("lightLevel", lightLevel);
  Particle.variable("occupied", occupied);
}

void loop() {
  lightLevel = analogRead(sensor);
  occupied = lightLevel > threshold;
  digitalWrite(led, occupied ? HIGH : LOW);
  delay(100);
}

int setThreshold(String thresholdString) {
  int newThreshold = thresholdString.toInt();
  if (newThreshold > 0) {
    threshold = newThreshold;
    return threshold;
  } else {
    return -1;
  }
}
