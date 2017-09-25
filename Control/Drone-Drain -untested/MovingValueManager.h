#ifndef MovingValueManager_h
#define MovingValueManager_h

#include "Arduino.h"

class MovingValueManager
{
  public:
    void SetMoveValue(unsigned short);
    void SetMoveInterval(unsigned short);
    void SetBrakeMoveValue(unsigned short);
    void SetBrakeMoveInterval(unsigned short);
    void SetSmooth(byte);
    void SetSmoothInterval(byte);
    void SetBrakeSmooth(byte);
    void SetBrakeSmoothInterval(byte);

    unsigned short GetMoveValue();
    unsigned short GetMoveInterval();
    unsigned short GetBrakeMoveValue();
    unsigned short GetBrakeMoveInterval();
    byte GetSmooth();
    byte GetSmoothInterval();
    byte GetBrakeSmooth();
    byte GetBrakeSmoothInterval();
	
  private:
    unsigned short moveValue;
    unsigned short moveInterval;
    unsigned short brakeMoveValue;
    unsigned short brakeMoveInterval;
    byte smooth;
    byte smoothInterval;
    byte brakeSmooth;
    byte brakeSmoothInterval;
};

#endif
