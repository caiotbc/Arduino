/* Código fonte para teste da comunicação CAN
 * Arquivo do transmissor
 * Plataforma: ATmega328p
 * Teste: 3.2 - Teste STM32 Bidirecional
 * Autor: Caio Tácito
 * Data: 30/04/2021
*/
#include "Cheetah.h"

CheetahCAN can(10);
void setup()
{
  Serial.begin(115200);
  int resultado = can.beginCAN();
  (resultado ? Serial.println("Falha na inicializacao do modulo CAN") : Serial.println("Modulo CAN inicializado com sucesso"));
}

void loop()
{
  can.addToPayload8(0xFC);
  can.addToPayload8(0xFE);
  can.addToPayload8(0xAB);
  can.addToPayload8(0xAC);
  can.addToPayload8(millis()%255);
  can.addToPayload8(random(0,255));
  can.addToPayload8(random(0,16));
  can.addToPayload8(random(0,1));
  if(!can.sendMessage(0x1))
    Serial.println("Mensagem enviada com sucesso");
  else
    Serial.println("Erro ao enviar mensagem");
  delay(1);
}
