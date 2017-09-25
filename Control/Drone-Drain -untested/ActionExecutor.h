#ifndef ActionExecutor_h
#define ActionExecutor_h

#include "MoveController.h"

typedef void (MoveController::*VoidResultVoidParam)();

const byte NumberOfActions = 8;

struct Action
{
  String Command;
  VoidResultVoidParam Callback;
};

class ActionExecutor
{
  public:
    ActionExecutor(MoveController*);
    ~ActionExecutor();
    
    void ExecuteCommand(String command);
    
  private:
    MoveController* moveController;
    struct Action actions[NumberOfActions];    
};

#endif
