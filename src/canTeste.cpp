#include <mcp_can.h>
#include <SPI.h>
#include "Cheetah.h"

CheetahCAN can;

void setup()
{
  Serial.begin(115200);
  can.beginReceiver();
}

void loop()
{
  if(can.readMessage())
  {
    byte *a = can.getMsg();
    char saida[128];
    sprintf(saida, "ID: 0x%.3X       Tamanho: %1d Mensagem recebida: ", can.getMsgId(), can.getMsgLen());
    Serial.print(saida);
    for(int i = 0 ; i < 8 ; i++)
    {
      sprintf(saida," 0x%1.2X" , a[i]);
      Serial.print(saida);
    }
    Serial.println();
  }
}
