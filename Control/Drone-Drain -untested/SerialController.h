#ifndef SerialController_h
#define SerialController_h

#include "Arduino.h"

#include <stdlib.h>

class SerialController
{
  public:
    SerialController(int);
    ~SerialController();
    
    String ReadLine();
    void Write(String);
    void WriteLine(String);
};

#endif
