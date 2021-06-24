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

void setup()
{
  Serial.begin(115200);
  can.beginCAN();
}

void loop()
{
  int dados[32];
  for(int i = 0 ; i < 32 ; i++)
  {
    dados[i] = i;
  }

  int teste;
  int id = 0x14;
  for(int j = 0 ; j < 4; j++)
  {
    for(int i = 0 ; i < 8 ; i++)
    {
      can.addToPayload8(dados[i + 8*j]);
    }
    teste = can.sendMessage(id);
    id++;
  }

  if(teste!=0)
  {
    Serial.print("Erro ao enviar mensagem CAN:");
    Serial.println(teste);
  }
  else
  {
    Serial.println("Mensagem enviada com sucesso");
  }
  delay(100);
}
