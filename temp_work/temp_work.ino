// working sensor
#include "SPI.h"
#include "Wire.h"

void setup() {
  Serial.begin(115200);

  MySignals.begin();
}

void loop() {

  float conductance = MySignals.getGSR(CONDUCTANCE);
  float resistance = MySignals.getGSR(RESISTANCE);
  float conductanceVol = MySignals.getGSR(VOLTAGE);

  Serial.print("Conductance : ");
  Serial.print(conductance, 2);
  Serial.println("");

  Serial.print("Resistance : ");
  Serial.print(resistance, 2);
  Serial.println("");

  Serial.print("Conductance Voltage : ");
  Serial.print(conductanceVol, 4);
  Serial.println("");

  Serial.print("\n");

  // wait for a second
  delay(1000);
}
