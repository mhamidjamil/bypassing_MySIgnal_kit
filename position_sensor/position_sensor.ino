#include "SPI.h"
#include <Wire.h>
#define SD_CS 8
#define EXPANDER 56
//----------------------------------------------------------------
float x_data, y_data, z_data;

//----------------------------------------------------------------
void setup() {
  Serial.begin(9600);

  Wire.begin();
  SPI.begin();
  Wire.beginTransmission(0x0A);

  // low pass filter, range settings
  Wire.write(0x20);
  Wire.write(0x05);
  Wire.endTransmission();
  pinMode(SD_CS, OUTPUT);

  uint8_t expanderState = B10100001;
  digitalWrite(SD_CS, HIGH); // Disable SD CS

  // Variable to store the value of the expander digital pins, initialized with
  // default value B10100001 default values,disable all SPI CS, turn off all
  // powers
  expanderWrite(expanderState);
}

void loop() {
  uint8_t position = getBodyPosition();
  // Serial.print("Current position : <2_");
  // print body position
  // MySignals.printPosition(position);
  if (position == 1) {
    Serial.print(F("Prone position"));
    // mysignalData.position = "Prone_position";
  } else if (position == 2) {
    Serial.print(F("Left lateral decubitus"));
    // mysignalData.position = "Left_lateral_decubitus";
  } else if (position == 3) {
    Serial.print(F("Rigth lateral decubitus"));
    // mysignalData.position = "Rigth_lateral_decubitus";
  } else if (position == 4) {
    Serial.print(F("Supine position"));
    // mysignalData.position = "Supine_position";
  } else if (position == 5) {
    Serial.print(F("Stand or sit position"));
    // mysignalData.position = "Stand_or_sit_position";
  } else {
    Serial.print(F("non-defined position"));
    Serial.println(position);
    // mysignalData.position = "non-defined_position";
  }
  Serial.println();
  //   MySignals.getAcceleration();
  delay(1000);
}
uint8_t getBodyPosition() {
  // Accelerometer acceleration buffer
  byte Version[3];
  // It stores current body position
  uint8_t bodyPos;

  // address of the accelerometer
  Wire.beginTransmission(0x0A);

  // reset the accelerometer
  Wire.write(0x04); // Y data
  Wire.endTransmission();

  // request 6 bytes from slave device
  Wire.requestFrom(0x0A, 1);

  // slave may send less than requested
  while (Wire.available()) {
    // receive a byte as character
    Version[0] = Wire.read();
  }

  x_data = (int8_t)Version[0] >> 2;

  // address of the accelerometer
  Wire.beginTransmission(0x0A);

  // reset the accelerometer
  // Y data
  Wire.write(0x06);
  Wire.endTransmission();

  // request 6 bytes from slave device
  Wire.requestFrom(0x0A, 1);

  // slave may send less than requested
  while (Wire.available()) {
    // receive a byte as character
    Version[1] = Wire.read();
  }

  y_data = (int8_t)Version[1] >> 2;

  // address of the accelerometer
  Wire.beginTransmission(0x0A);

  // reset the accelerometer
  // Y data
  Wire.write(0x08);
  Wire.endTransmission();

  // request 6 bytes from slave device
  Wire.requestFrom(0x0A, 1);

  // slave may send less than requested
  while (Wire.available()) {
    // receive a byte as character
    Version[2] = Wire.read();
  }

  z_data = (int8_t)Version[2] >> 2;

  delay(100);

  // determinate the patient position
  bodyPos = bodyPosition();

  return bodyPos;
}
uint8_t bodyPosition(void) {
  uint8_t bodyPos;

  if (z_data >= 12) {
    bodyPos = 1;
  }

  else if (y_data >= 12) {
    bodyPos = 2;
  }

  else if (y_data <= -12) {
    bodyPos = 3;
  }

  else if (z_data <= -12) {
    bodyPos = 4;
  } else if (x_data <= -12) {
    bodyPos = 5;
  } else {
    bodyPos = 6;
  }
  //   Serial.println("returning : " + String(bodyPos) + " # ");
  return bodyPos;
}
void getAcceleration(void) {
  // convert the raw data to acceleration
  float LSB_parameter = 0.0625;
  x_data = x_data * LSB_parameter;
  y_data = y_data * LSB_parameter;
  z_data = z_data * LSB_parameter;
}
void expanderWrite(byte data) {
  Wire.beginTransmission(EXPANDER);
  Wire.write(data);
  Wire.endTransmission();
}
