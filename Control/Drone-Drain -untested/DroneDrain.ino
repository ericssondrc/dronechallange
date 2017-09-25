#include "MovingValueManager.h"
#include "SerialController.h"
#include "MoveController.h"
#include "ActionExecutor.h"

//this program will put out a PPM signal

//////////////////////CONFIGURATION///////////////////////////////

#define PPM_FrLen 22500  //set the PPM frame length in microseconds (1ms = 1000µs)
#define PPM_PulseLen 300  //set the pulse length
#define onState 1  //set polarity of the pulses: 1 is positive, 0 is negative
#define sigPin 4  //set PPM signal output pin on the arduino
//////////////////////////////////////////////////////////////////

/*this array holds the servo values for the ppm signal
 change these values in your code (usually servo values move between 1000 and 2000)*/

MovingValueManager *movingValueManager;
MoveController *moveController;
SerialController* serialController;
ActionExecutor* actionExecutor;

void setup()
{
  serialController = new SerialController(9600);
  movingValueManager = new MovingValueManager();
  moveController = new MoveController(movingValueManager, serialController);
  actionExecutor = new ActionExecutor(moveController);

  pinMode(sigPin, OUTPUT);
  digitalWrite(sigPin, !onState);  //set the PPM signal pin to the default state (off)
  
  cli();
  TCCR1A = 0; // set entire TCCR1 register to 0
  TCCR1B = 0;
  
  OCR1A = 100;  // compare match register, change this
  TCCR1B |= (1 << WGM12);  // turn on CTC mode
  TCCR1B |= (1 << CS11);  // 8 prescaler: 0,5 microseconds at 16mhz
  TIMSK1 |= (1 << OCIE1A); // enable timer compare interrupt
  sei();

  movingValueManager->SetMoveValue(MoveController::DefaultMoveValue);
  movingValueManager->SetMoveInterval(MoveController::DefaultInterval);
  movingValueManager->SetSmooth(MoveController::DefaultSmooth);
  movingValueManager->SetSmoothInterval(MoveController::DefaultSmoothInterval);
  movingValueManager->SetBrakeMoveValue(MoveController::DefaultBrakeMoveValue);
  movingValueManager->SetBrakeMoveInterval(MoveController::DefaultBrakeInterval);
  movingValueManager->SetBrakeSmooth(MoveController::DefaultBrakeSmooth);
  movingValueManager->SetBrakeSmoothInterval(MoveController::DefaultBrakeSmoothInterval);
}

const char separator = ';';
String command, part;

void loop()
{
  command = serialController->ReadLine();
  if (command != "")
  {
    if (command.indexOf(separator) > -1)
    {
      int startIndex = 0, endIndex, resultIndex = 0;
      do
      {
        endIndex = command.indexOf(separator, startIndex + 1);
        part = endIndex == -1 ? command.substring(startIndex, command.length()) : command.substring(startIndex, endIndex);

        switch (resultIndex++)
        {
          case 0:
            serialController->WriteLine("Set move value to: " + part);
            movingValueManager->SetMoveValue(part.toInt());
            break;
          case 1:
            serialController->WriteLine("Set move interval to: " + part);
            movingValueManager->SetMoveInterval(part.toInt());
            break;
          case 2:
            serialController->WriteLine("Set smooth value to: " + part);
            movingValueManager->SetSmooth(part.toInt());
            break;
          case 3:
            serialController->WriteLine("Set smooth interval to: " + part);
            movingValueManager->SetSmoothInterval(part.toInt());
            break;
          case 4:
            serialController->WriteLine("Set brake value to: " + part);
            movingValueManager->SetBrakeMoveValue(part.toInt());
            break;
          case 5:
            serialController->WriteLine("Set brake interval to: " + part);
            movingValueManager->SetBrakeMoveInterval(part.toInt());
            break;
          case 6:
            serialController->WriteLine("Set brake smooth value to: " + part);
            movingValueManager->SetBrakeSmooth(part.toInt());
            break;
          case 7:
            serialController->WriteLine("Set brake smooth interval to: " + part);
            movingValueManager->SetBrakeSmoothInterval(part.toInt());
            break;
        }
        startIndex = endIndex + 1;
      }
      while (endIndex != -1);
    }
    else
    {
      serialController->WriteLine("Received command: " + command);
      actionExecutor->ExecuteCommand(command);
    }
  }
}

ISR(TIMER1_COMPA_vect)
{
  //leave this alone
  static boolean state = true;
  
  TCNT1 = 0;
  
  if (state)
  {
    //start pulse
    digitalWrite(sigPin, onState);
    OCR1A = PPM_PulseLen * 2;
    state = false;
  }
  else
  {
    //end pulse and calculate when to start the next pulse
    static byte cur_chan_numb;
    static unsigned int calc_rest;
  
    digitalWrite(sigPin, !onState);
    state = true;

    if (cur_chan_numb >= MoveController::NumberOfChannels)
    {
      cur_chan_numb = 0;
      calc_rest = calc_rest + PPM_PulseLen;
      OCR1A = (PPM_FrLen - calc_rest) * 2;
      calc_rest = 0;
    }
    else
    {
      OCR1A = (moveController->ppm[cur_chan_numb] - PPM_PulseLen) * 2;
      calc_rest = calc_rest + moveController->ppm[cur_chan_numb];
      cur_chan_numb++;
    }
  }
}
