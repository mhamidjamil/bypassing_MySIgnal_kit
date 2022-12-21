// working sensor
#include "SPI.h"
#include "Wire.h"
#define ADC_GSR 3
uint16_t gsr_raw;
void setup() {
  Serial.begin(9600);

  //   MySignals.begin();
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
float getGSR(uint8_t format) {
  // Local variable declaration.
  float resistance;
  float conductance;

  // disable global interrupts
  // cli();
  // Read an analogic value from analogic2 pin.
  gsr_raw = readADC(ADC_GSR);
  // enable global interrupts
  // sei();
  // Serial.print("grs raw:");
  // Serial.println(gsr_raw);

  float voltage = gsr_raw * 5.0 / 1023;

  conductance = 2 * ((voltage - 0.5) / 100000);

  // Conductance calculation
  resistance = 1 / conductance;
  conductance = conductance * 1000000;

  // #if MYHOSPITAL_DEBUG > 0
  //   Serial.println();
  //   Serial.println("-----------------> GSR SENSOR");
  //   Serial.print("GSR conductance = ");
  //   Serial.println(conductance);
  //   Serial.print("GSR resistance = ");
  //   Serial.println(resistance);
  //   Serial.print("GSR voltage = ");
  //   Serial.println(voltage);
  // #endif

  if (conductance > 1.0) {
    if (format == 1)
      return conductance;
    else if (format == 2)
      return resistance;
    else if (format == 3)
      return voltage;
    else if (format == 4)
      return gsr_raw;
  } else
    return 0;
}