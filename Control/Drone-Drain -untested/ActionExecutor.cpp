#include "ActionExecutor.h"

ActionExecutor::ActionExecutor(MoveController* moveController)
{
  this->moveController = moveController;
  
  actions[0] = { "Forward", &MoveController::MoveForward };
  actions[1] = { "Backward", &MoveController::MoveBackward };
  actions[2] = { "Left", &MoveController::MoveLeft };
  actions[3] = { "Right", &MoveController::MoveRight };
  actions[4] = { "TurnLeft", &MoveController::TurnLeft };
  actions[5] = { "TurnRight", &MoveController::TurnRight };
  actions[6] = { "Up", &MoveController::MoveUp };
  actions[7] = { "Down", &MoveController::MoveDown };
}

ActionExecutor::~ActionExecutor()
{
  delete(moveController);
}

void ActionExecutor::ExecuteCommand(String command)
{
  for (byte i = 0; i < NumberOfActions; i++)
  {
    if (actions[i].Command == command)
    {
      (moveController->*(actions[i].Callback))();
      break;
    }
  }
}
