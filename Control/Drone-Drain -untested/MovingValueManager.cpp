#include "MovingValueManager.h"

void MovingValueManager::SetMoveValue(unsigned short value)
{
  moveValue = value;
}

void MovingValueManager::SetMoveInterval(unsigned short value)
{
  moveInterval = value;
}

void MovingValueManager::SetBrakeMoveValue(unsigned short value)
{
  brakeMoveValue = value;
}

void MovingValueManager::SetBrakeMoveInterval(unsigned short value)
{
  brakeMoveInterval = value;
}

void MovingValueManager::SetSmooth(byte value)
{
  smooth = value;
}

void MovingValueManager::SetSmoothInterval(byte value)
{
  smoothInterval = value;
}

void MovingValueManager::SetBrakeSmooth(byte value)
{
  brakeSmooth = value;
}

void MovingValueManager::SetBrakeSmoothInterval(byte value)
{
  brakeSmoothInterval = value;
}

unsigned short MovingValueManager::GetMoveValue()
{
  return moveValue;
}

unsigned short MovingValueManager::GetMoveInterval()
{
  return moveInterval;
}

unsigned short MovingValueManager::GetBrakeMoveValue()
{
  return brakeMoveValue;
}

unsigned short MovingValueManager::GetBrakeMoveInterval()
{
  return brakeMoveInterval;
}

byte MovingValueManager::GetSmooth()
{
  return smooth;
}

byte MovingValueManager::GetSmoothInterval()
{
  return smoothInterval;
}

byte MovingValueManager::GetBrakeSmooth()
{
  return brakeSmooth;
}

byte MovingValueManager::GetBrakeSmoothInterval()
{
  return brakeSmoothInterval;
}
