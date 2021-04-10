#include "Cheetah.h"

CheetahSerial::CheetahSerial(uint16_t msg_size)
{
  this->contA = 1;
  this->contD = 0;
  this->vel = 30000;
  memset(this->payload , 0 , MSG_SIZE);
  memset(this->digital , 0 , N_SENSORES_DISCRETO);
}

void CheetahSerial::addAnalogSensor(uint16_t value)
{
  this->payload[contA] =  highByte(value);
  this->payload[contA+1] = lowByte(value);
  this->contA += 2;
}

void CheetahSerial::addDigitalSensor(uint16_t value)
{
  this->digital[contD] = value;
  this->contD++;
}

void CheetahSerial::sendPayload()
{
  int temp[N_SENSORES_DISCRETO/8];
  for(int i = 0 ; i < N_SENSORES_DISCRETO/8 ; i++)
  {
    int aux = 0;
    int bin = 1;
    for(int j = i*8 + 7 ; j >= i*8 ; j--)
    {
      aux += this->digital[j] * bin;
      bin *=2;
    }
    temp[i] = aux;
  }

  int cont = 0;
  for (int i = 1 + (N_SENSORES_MEDICAO * 2) ; i < MSG_SIZE-1 ; i++)
  {
    this->payload[i] = temp[cont];
    cont++;
  }
  //this->payload[5] = 255;

  this->contA = 1;
  this->contD = 0;

  this->payload[0] = 255;
  this->payload[MSG_SIZE-1] = 254;
  Serial.write(this->payload, MSG_SIZE);
}

void CheetahSerial::modoTeste()
{
  if(this->subindo)
  {
    this->vel+=100;
    if(this->vel>32768)
      this->subindo = false;
  }
  else
  {
    this->vel-=100;
    if(this->vel<11000)
      this->subindo = true;
    for(int i = 1 ; i < MSG_SIZE - 1 ; i++)
    {
      this->payload[i] = random(0,255);
    }
  }
  this->payload[1] = highByte(this->vel);
  this->payload[2] = lowByte(this->vel);
}
