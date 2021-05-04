/* Código fonte para teste da comunicação CAN
 * Arquivo do receptor
 * Plataforma: ATmega2560
 * Teste: 3.2 - Teste STM32 Bidirecional
 * Autor: Caio Tácito
 * Data: 30/04/2021
*/
#include "Cheetah.h"

CheetahCAN can(10);
CheetahSerial serial;
void setup()
{
  Serial.begin(115200);
  int resultado = can.beginCAN();
  (resultado ? Serial.println("Falha na inicializacao do modulo CAN") : Serial.println("Modulo CAN inicializado com sucesso"));
}

void loop()
{
  if(can.readMessage())
  {
    Serial.print("ID = ");
    Serial.print(can.getMsgId());
    Serial.print("|");
    Serial.println(can.getMsg()[0]);
    delay(500);
  }
  /*
  if(timer>1000)
  {

    serial.addAnalogSensor(can.getMsg()[0] << 8 | can.getMsg()[1]);
    serial.addAnalogSensor(can.getMsg()[2] << 8 | can.getMsg()[3]);
    serial.addAnalogSensor(can.getMsg()[4] << 8 | can.getMsg()[5]);
    serial.addAnalogSensor(can.getMsg()[6] << 8 | can.getMsg()[7]);
    serial.sendPayload();

    timer=0;
  }*/
}
