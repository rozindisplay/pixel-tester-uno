#include <Arduino.h>
#include <Wire.h>
#include <config/Config.h>

void setup() {
  Serial.begin(9600);
  CMD_RUNNER.printHelp();
}

void loop() {
  CMD_RUNNER.run();
}