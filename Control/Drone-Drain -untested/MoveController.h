#ifndef MoveController_h
#define MoveController_h

#include "MovingValueManager.h"
#include "SerialController.h"
#include "MoveController.h"

#include <stdlib.h>

class MoveController
{
  public:
    static const byte NumberOfChannels = 8;

    static const short MaxMoveValue = 500;
    static const unsigned short DefaultServoValue = 1500; // 1520?
    
    static const unsigned short DefaultMoveValue = 200;
    static const unsigned short DefaultInterval = 200;
    static const unsigned short DefaultBrakeMoveValue = 200;
    static const unsigned short DefaultBrakeInterval = 200;
    static const byte DefaultSmooth = 10;
    static const byte DefaultSmoothInterval = 20;
    static const byte DefaultBrakeSmooth = 10;
    static const byte DefaultBrakeSmoothInterval = 0;

  private:
    static const byte RollAxis = 0;
    static const byte PitchAxis = 1;
    static const byte TrustAxis = 2;
    static const byte YawAxis = 3;
      
  public: int ppm[MoveController::NumberOfChannels];
  public:

    MoveController(MovingValueManager *, SerialController *);
    ~MoveController();
 
    void Reset();
    void MoveForward();
    void MoveBackward();
    void MoveRight();
    void MoveLeft();
    void MoveUp();
    void MoveDown();
    void TurnRight();
    void TurnLeft();
    
  private:
    MovingValueManager* movingValueManager;
    SerialController* serialController;
    
    void MovingBase(boolean, byte, boolean);
    short GetAdjustedMoveValue(short);
    void SetMoveValue(byte, short, unsigned short);
    void SmoothToMax(byte, short, byte, byte);
    void SmoothToMin(byte, short, byte, byte);
};

#endif
