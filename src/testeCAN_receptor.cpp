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
int timer=0;
void setup()
{
  TCCR0A=(1<<WGM01);
  OCR0A=0xF9;
  TIMSK0|=(1<<OCIE0A);
  sei();
  TCCR0B|=(1<<CS01);
  TCCR0B|=(1<<CS00);
  Serial.begin(460800);
  int resultado = can.beginCAN();
  (resultado ? Serial.println("Falha na inicializacao do modulo CAN") : Serial.println("Modulo CAN inicializado com sucesso"));
}

void loop()
{
  /*if(can.readMessage())
  {
    serial.addAnalogSensor(can.getMsg()[0] << 8 | can.getMsg()[1]);
    serial.addAnalogSensor(can.getMsg()[2] << 8 | can.getMsg()[3]);
    serial.addAnalogSensor(can.getMsg()[4] << 8 | can.getMsg()[5]);
    serial.addAnalogSensor(can.getMsg()[6] << 8 | can.getMsg()[7]);
    serial.sendPayload();
  }*/
  if(timer>0)
  {
    serial.addAnalogSensor(can.getMsg()[0] << 8 | can.getMsg()[1]);
    serial.addAnalogSensor(can.getMsg()[2] << 8 | can.getMsg()[3]);
    serial.addAnalogSensor(can.getMsg()[4] << 8 | can.getMsg()[5]);
    serial.addAnalogSensor(can.getMsg()[6] << 8 | can.getMsg()[7]);
    serial.sendPayload();
    timer=0;
  }
}

ISR(TIMER0_COMPA_vect){ 
  timer++;
}
