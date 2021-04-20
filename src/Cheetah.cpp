#include "Cheetah.h"

MCP_CAN CAN0(10);

CheetahSerial::CheetahSerial()
{
  this->contA = 1;
  this->contD = 0;
  this->vel = 30;
  memset(this->payload , 0 , sizeof(this->payload));
  memset(this->digital , 0 , sizeof(this->digital));
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
  int qtdTeste = 2;
  for(int th = 0 ; th < qtdTeste ; th++)
  {
    if(this->subindo)
    {
      this->vel+=1;
      if(this->vel>4096)
        this->subindo = false;
    }
    else
    {
      this->vel-=1;
      if(this->vel<1)
        this->subindo = true;
      for(int i = 1 ; i < MSG_SIZE - 1 ; i++)
      {
        this->payload[i] = random(0,255);
      }
    }
  }
  this->payload[1] = highByte(this->vel);
  this->payload[2] = lowByte(this->vel);
  this->payload[3] = highByte(this->vel);
  this->payload[4] = lowByte(this->vel);
  this->payload[5] = highByte(this->vel);
  this->payload[6] = lowByte(this->vel);
  this->payload[7] = highByte(this->vel);
  this->payload[8] = lowByte(this->vel);
  this->payload[9] = highByte(this->vel);
  this->payload[10] = lowByte(this->vel);
  this->payload[11] = highByte(this->vel);
  this->payload[12] = lowByte(this->vel);
  this->payload[13] = highByte(this->vel);
  this->payload[14] = lowByte(this->vel);
  this->payload[15] = highByte(this->vel);
  this->payload[16] = lowByte(this->vel);
  this->payload[17] = highByte(this->vel);
  this->payload[18] = lowByte(this->vel);
  this->payload[19] = highByte(this->vel);
  this->payload[20] = lowByte(this->vel);
}


Acelerometro::Acelerometro()
{
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);

  //Inicializa o MPU-6050
  Wire.write(0);
  Wire.endTransmission(true);

  memset(variaveis, 0, sizeof(variaveis));
}

uint16_t* Acelerometro::leituraVariaveis()
{
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  //Solicita os dados do sensor
  Wire.requestFrom(MPU,14,true);

  for(int i = 0; i < 7; i++)
  {
    variaveis[i] = Wire.read()<<8|Wire.read();
  }

  return variaveis;
}

void CheetahCAN::beginReceiver()
{
  if(CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_16MHZ) == CAN_OK)
    Serial.println("MCP2515 Initialized Successfully!");
  else
    Serial.println("Error Initializing MCP2515...");

  CAN0.setMode(MCP_NORMAL);                     // Set operation mode to normal so the MCP2515 sends acks to received data.

  pinMode(CAN0_INT, INPUT);                            // Configuring pin for /INT input

  Serial.println("MCP2515 Library Receive Example...");
}

void CheetahCAN::beginTransmitter()
{
  Serial.begin(115200);
  // Initialize MCP2515 running at 16MHz with a baudrate of 500kb/s and the masks and filters disabled.
  if(CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_16MHZ) == CAN_OK) Serial.println("MCP2515 Initialized Successfully!");
  else Serial.println("Error Initializing MCP2515...");

  CAN0.setMode(MCP_NORMAL);   // Change to normal mode to allow messages to be transmitted
}

void CheetahCAN::sendMessage(byte data[])
{
  // send data:  ID = 0x100, Standard CAN Frame, Data length = 8 bytes, 'data' = array of data bytes to send
  byte sndStat = CAN0.sendMsgBuf(0x100, 0, 8, data);
  if(sndStat == CAN_OK){
    Serial.println("Message Sent Successfully!");
  } else {
    Serial.println("Error Sending Message...");
  }
  delay(100);   // send data per 100ms
}

bool CheetahCAN::readMessage()
{
  if(!digitalRead(CAN0_INT))
  {
    CAN0.readMsgBuf(&rxId, &rxLen, rxBuf);
    return true;
  }
  return false;
}

byte* CheetahCAN::getMsg()
{
  return rxBuf;
}

uint16_t CheetahCAN::getMsgId()
{
  return rxId;
}

uint16_t CheetahCAN::getMsgLen()
{
  return rxLen;
}
