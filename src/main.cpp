#include "Cheetah.h"
CheetahSerial serial(12);
void setup()
{
  Serial.begin(9600);
  delay(500);
}
void loop()
{
  //serial.modoTeste();
  serial.addAnalogSensor(34000);
  serial.addAnalogSensor(39570);
  serial.addDigitalSensor(1);
  serial.addDigitalSensor(0);
  serial.addDigitalSensor(0);
  serial.addDigitalSensor(1);
  serial.addDigitalSensor(0);
  serial.addDigitalSensor(1);
  serial.addDigitalSensor(1);
  serial.addDigitalSensor(1);
  serial.sendPayload();
  delay(1000);
}
