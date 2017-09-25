#include "SerialController.h"

SerialController::SerialController(int baud)
{
  Serial.begin(baud);
  WriteLine("SerialController initialized");
}

SerialController::~SerialController()
{
  Serial.end();
}

String SerialController::ReadLine()
{
  if (!Serial.available())
  {
    return "";
  }
  
  return Serial.readString();
}

void SerialController::Write(String text)
{
  if (text != "")
  {
    Serial.print(text);
    Serial.flush();  
  }
}

void SerialController::WriteLine(String text)
{
  if (text != "")
  {
    Serial.print(text);
    Serial.print("\r\n");
    Serial.flush();  
  }
}
