#include "Cheetah.h"
CheetahSerial serial(MSG_SIZE);
void setup()
{
  Serial.begin(9600);
  delay(500);
}
void loop()
{
  serial.modoTeste();
  //int sensor = analogRead(A0);
  /*if(sensor <=65)
  {
    sensor = 65;
  }
  if(sensor >= 867)
  {
    sensor = 867;
  }
  sensor = map(sensor, 65 ,867,0,1500);

  serial.addAnalogSensor(sensor);
  serial.addAnalogSensor(39570);
  serial.addDigitalSensor(1);
  serial.addDigitalSensor(0);
  serial.addDigitalSensor(0);
  serial.addDigitalSensor(1);
  serial.addDigitalSensor(0);
  serial.addDigitalSensor(1);
  serial.addDigitalSensor(1);
  serial.addDigitalSensor(1);
  */
  serial.sendPayload();

  delay(50);
}
