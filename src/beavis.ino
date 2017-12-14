#include "HttpClient/HttpClient.h"

int led = D0;
int sensor = A0;
int lightLevel = 0;
int threshold = 3200;
bool occupied = false;
bool oldOccupied = false;
String occupiedDescription;

HttpClient http;
http_request_t request;
http_response_t response;

http_header_t headers[] = {
  { "Accept", "*/*" },
  { "Content-Type", "application/x-www-form-urlencoded" },
  { NULL, NULL },
};

void setup() {
  pinMode(led, OUTPUT);
  pinMode(sensor, INPUT);

  Particle.function("setThreshold", setThreshold);
  Particle.variable("lightLevel", lightLevel);
  Particle.variable("occupied", occupied);

  request.hostname = "beavis-web.herokuapp.com";
  request.path = "/rooms/" + System.deviceID();
  request.port = 80;
}

void loop() {
  oldOccupied = occupied;
  lightLevel = analogRead(sensor);
  occupied = lightLevel > threshold;

  digitalWrite(led, occupied ? HIGH : LOW);

  if (occupied != oldOccupied) {
    occupiedDescription = occupied ? "true" : "false";
    Particle.publish("occupied", occupiedDescription);
    request.body = "occupied=" + occupiedDescription;
    http.patch(request, response, headers);
  }

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
