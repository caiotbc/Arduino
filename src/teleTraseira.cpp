#include <mcp_can.h>
#include <SPI.h>
#include "Cheetah.h"

CheetahCAN can;
byte enviar[8] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};

void setup()
{
  Serial.begin(115200);
  can.beginTransmitter();
}

void loop()
{
  can.sendMessage(enviar);
  enviar[1]+=1;
}
