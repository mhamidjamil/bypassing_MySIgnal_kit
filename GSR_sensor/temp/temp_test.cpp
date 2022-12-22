// read analog input from A0:
void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);
}
void loop() {
  //   int sensorValue = analogRead(A0);
  //   Serial.println(sensorValue);

  float sum = 0.0;
  for (int n = 0; n < 100; n++) {
    sum += analogRead(A0) + 0.5;
  }
  sum /= 100.0;
  sum = sum / _stepsInRange * _powerSupplyVoltage;
  Serial.println("data: " + String(sum));
  delay(1000);
}