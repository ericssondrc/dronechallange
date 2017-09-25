#include "MoveController.h"

MoveController::MoveController(MovingValueManager *movingValueManager, SerialController* serialController)
{
  this->movingValueManager = movingValueManager;
  this->serialController = serialController;
  Reset();
}

MoveController::~MoveController()
{
  delete(movingValueManager);
  delete(serialController);
}

void MoveController::Reset()
{
  for (int i = 0; i < MoveController::NumberOfChannels; i++)
  {
    ppm[i] = DefaultServoValue;
  }
}
  
void MoveController::MoveForward()
{
  serialController->WriteLine("MoveForward");
  MovingBase(true, PitchAxis, true);
}

void MoveController::MoveBackward()
{
  serialController->WriteLine("MoveBackward");
  MovingBase(false, PitchAxis, true);
}

void MoveController::MoveRight()
{
  serialController->WriteLine("MoveRight");
  MovingBase(true, RollAxis, true);
}

void MoveController::MoveLeft()
{
  serialController->WriteLine("MoveLeft");
  MovingBase(false, RollAxis, true);
}

void MoveController::MoveUp()
{
  serialController->WriteLine("MoveUp");
  MovingBase(true, TrustAxis, true);
}

void MoveController::MoveDown()
{
  serialController->WriteLine("MoveDown");
  MovingBase(false, TrustAxis, true);
}

void MoveController::TurnRight()
{
  serialController->WriteLine("TurnRight");
  MovingBase(true, YawAxis, false);
}

void MoveController::TurnLeft()
{
  serialController->WriteLine("TurnLeft");
  MovingBase(false, YawAxis, false);
}

void MoveController::MovingBase(boolean add, byte channelNumber, boolean useBrake)
{
  short moveValue;
  if (add)
  {
    moveValue = DefaultServoValue + movingValueManager->GetMoveValue();
    SmoothToMax(channelNumber, moveValue, movingValueManager->GetSmooth(), movingValueManager->GetSmoothInterval());
  }
  else
  {
    moveValue = DefaultServoValue - movingValueManager->GetMoveValue();
    SmoothToMin(channelNumber, moveValue, movingValueManager->GetSmooth(), movingValueManager->GetSmoothInterval());
  }
  SetMoveValue(channelNumber, moveValue, movingValueManager->GetMoveInterval());

  if (useBrake)
  {
    short brakeMoveValue;
    if (add)
    {
      brakeMoveValue = DefaultServoValue - movingValueManager->GetBrakeMoveValue();
      SmoothToMin(channelNumber, brakeMoveValue, movingValueManager->GetBrakeSmooth(), movingValueManager->GetBrakeSmoothInterval());
    }
    else
    {
      brakeMoveValue = DefaultServoValue + movingValueManager->GetBrakeMoveValue();
      SmoothToMax(channelNumber, brakeMoveValue, movingValueManager->GetBrakeSmooth(), movingValueManager->GetBrakeSmoothInterval());
    }
    SetMoveValue(channelNumber, brakeMoveValue, movingValueManager->GetBrakeMoveInterval());
  }
  ppm[channelNumber] = DefaultServoValue;
  serialController->WriteLine(String(ppm[channelNumber]));
}

void MoveController::SetMoveValue(byte channelNumber, short moveValue, unsigned short interval)
{
  serialController->WriteLine(String(moveValue));
  ppm[channelNumber] = moveValue;
  delay(interval);
}

void MoveController::SmoothToMax(byte channelNumber, short maxValue, byte smooth, byte smoothInterval)
{
  if (smooth != 0)
  {
    while (ppm[channelNumber] < maxValue)
    {
      serialController->WriteLine(String(ppm[channelNumber]));
      ppm[channelNumber] += smooth;
      delay(smoothInterval);
    }
  }
}

void MoveController::SmoothToMin(byte channelNumber, short minValue, byte smooth, byte smoothInterval)
{
  if (smooth != 0)
  {
    while (ppm[channelNumber] > minValue)
    {
      serialController->WriteLine(String(ppm[channelNumber]));
      ppm[channelNumber] -= smooth;
      delay(smoothInterval);
    }
  }
}

short MoveController::GetAdjustedMoveValue(short moveValue)
{
  if (moveValue > MoveController::MaxMoveValue)
  {
    return MoveController::MaxMoveValue;
  }
  if (moveValue < -MoveController::MaxMoveValue)
  {
    return -MoveController::MaxMoveValue;
  }

  return moveValue;
}
