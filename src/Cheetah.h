#ifndef CHEETAHSERIAL_H
#define CHEETAHSERIAL_H
#define lowByte(w) ((uint8_t) ((w) & 0xff))
#define highByte(w) ((uint8_t) ((w) >> 8))
#define MSG_SIZE 28
#define N_SENSORES_MEDICAO 10
#define N_SENSORES_DISCRETO 48
#include "Arduino.h"

class CheetahSerial
{
  private:
    byte payload[MSG_SIZE];
    uint16_t digital[N_SENSORES_DISCRETO];
    uint16_t contA;
    uint16_t contD;
    bool subindo;
    unsigned int vel;
  public:
    CheetahSerial(uint16_t msg_size);
    void addToPayload(uint16_t value);
    void modoTeste();
    void sendPayload();
    void addAnalogSensor(uint16_t value);
    void addDigitalSensor(uint16_t value);
};

class Acelerometro
{
  public:
      void banana();
};

#endif
