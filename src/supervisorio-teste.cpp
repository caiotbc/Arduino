/* Código fonte para teste de comunicação CAN - BMS
 * Não esquecer de configurar os pinos no config.h
 * Plataforma: ATmega2560
 * Autor: Caio Tácito
 * Data: 03/05/2021
 * CHEETAHPORRA!
*/
#include "Cheetah.h"

//Instanciando objetos
CheetahSerial serial;
CheetahCAN can(10);
byte *msg , *msg1 , *msg2 , *msg3;

void setup()
{
  memset(msg , 0 , sizeof(msg));
  memset(msg1 , 0 , sizeof(msg));
  memset(msg2 , 0 , sizeof(msg));
  memset(msg3 , 0 , sizeof(msg));
  //Incializa serial
  Serial.begin(115200);
  //Inicializa CAN
  can.beginCAN();
}
uint16_t j = 43;
int speed = 100;


void loop()
{
  // out:
  // if(can.readMessage())
  // {
  //   if (can.getMsgId()!= 0x0)
  //   {
  //     goto out;
  //   }
  //   byte *msg = can.getMsg();
  //   serial.addAnalogSensor(msg[0] | msg[1]<<8);
  //   serial.addAnalogSensor(msg[2] | msg[3]<<8);
  //   serial.addAnalogSensor(msg[4] | msg[5]<<8);
  //   while (1)
  //   {
  //     can.readMessage();
  //     if(can.getMsgId() == 0x5)
  //     {
  //       break;
  //     }
  //   }
  //   msg = can.getMsg();
  //   serial.addDigitalSensor((msg[0] & 0b10000000) >> 7);
  //   serial.addDigitalSensor((msg[0] & 0b01000000) >> 6);
  //   serial.addDigitalSensor((msg[0] & 0b00100000) >> 5);
  //   serial.addAnalogSensor(msg[2] | msg[3]<<8);
  //   serial.addAnalogSensor(msg[4] | msg[5]<<8);
  //   serial.addAnalogSensor(msg[6] | msg[7]<<8);
  //   serial.sendPayload();
  //   delay(100);
  // }

    //   uint16_t lta = latitude[i] & 0xFFFF;
    // uint16_t ltb = latitude[i] >> 16;

    // uint16_t lga = longitude[i] & 0xFFFF;
    // uint16_t lgb = longitude[i] >> 16;

  if(can.readMessage())
  { 
    msg = can.getMsg();

    if(can.getMsgId()==0x14)
    {
      for(int i = 0 ; i < 7 ; i+=2)
      {
        serial.addAnalogSensor(msg[i+1]  | msg[i] <<8);
      }
      serial.sendPayload();
    }
  }
}
