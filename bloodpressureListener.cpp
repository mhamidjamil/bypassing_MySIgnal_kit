#include <SoftwareSerial.h>

SoftwareSerial bloodpressure(2, 3);
void setup() {
  Serial.begin(19200);
  bloodpressure.begin(19200);
}
void loop() {
  if (bloodpressure.available()) {
    Serial.write(bloodpressure.read());
  }
  //   if (Serial.available()) {
  //     bloodpressure.write(Serial.read());
  //   }
}