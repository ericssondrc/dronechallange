//this program will put out a PPM signal

//////////////////////CONFIGURATION///////////////////////////////

#define PPM_FrLen 22500  //set the PPM frame length in microseconds (1ms = 1000µs)
#define PPM_PulseLen 300  //set the pulse length
#define onState 1  //set polarity of the pulses: 1 is positive, 0 is negative
#define sigPin 3  //set PPM signal output pin on the arduino
#define inpin 7 // input pin
//////////////////////////////////////////////////////////////////

/*this array holds the servo values for the ppm signal
 change these values in your code (usually servo values move between 1000 and 2000)*/

class MoveController
{
  public: static const byte number_of_channels = 8;
  private: static const unsigned short default_servo_value = 1520;
  private: static const byte roll_axis = 0;
  private: static const byte pitch_axis = 1;
  private: static const byte trust_axis = 2;
  private: static const byte yaw_axis = 3;
  
  private: static const unsigned short default_moveValue = 100;
  private: static const unsigned short default_moveValue2 = 200;
  private: static const unsigned short default_brakeInterval = 300;
  
  public: int ppm[MoveController::number_of_channels];
  
  public: void reset()
  {
    for (int i = 0; i < MoveController::number_of_channels; i++)
    {
      ppm[i] = default_servo_value;
    }
  }
  
  public: void moveBackward(unsigned short interval , unsigned short moveValue = default_moveValue)
  {
    movingBasePlus(pitch_axis, moveValue, interval);
    moveValue = calculateX(moveValue, interval, default_brakeInterval);
    movingBaseMinus(pitch_axis, moveValue, default_brakeInterval);
  }

  public: void moveForward(unsigned short interval , unsigned short moveValue = default_moveValue)
  {
    movingBasePlus(pitch_axis, moveValue, interval);
    moveValue = calculateX(moveValue, interval, default_brakeInterval);
    movingBaseMinus(pitch_axis, moveValue, default_brakeInterval);
  }

  public: void moveLeft(unsigned short interval , unsigned short moveValue = default_moveValue)
  {
    movingBasePlus(roll_axis, moveValue, interval);
    moveValue = calculateX(moveValue, interval, default_brakeInterval);
    movingBaseMinus(roll_axis, moveValue, default_brakeInterval);
  }

  public: void moveRight(unsigned short interval , unsigned short moveValue = default_moveValue)
  {
    movingBaseMinus(roll_axis, moveValue, interval);
    moveValue = calculateX(moveValue, interval, default_brakeInterval);
    movingBasePlus(roll_axis, moveValue, default_brakeInterval);
  }
/*
  public: void moveUp(unsigned short interval , unsigned short moveValue = default_moveValue)
  {
    movingBasePlus(trust_axis, moveValue, interval);
    moveValue = calculateX(moveValue, interval, default_brakeInterval);
    movingBaseMinus(trust_axis, moveValue, default_brakeInterval);
    
  }

  public: void moveDown(unsigned short interval , unsigned short moveValue = default_moveValue)
  {
    movingBaseMinus(trust_axis, moveValue, interval);
    moveValue = calculateX(moveValue, interval, default_brakeInterval);
    movingBaseMinus(trust_axis, moveValue, default_brakeInterval);
  }
*/
  public: void turnRight(unsigned short interval , unsigned short moveValue = default_moveValue2)
  {
    movingBasePlus(yaw_axis, moveValue, interval);
  }

  public: void turnLeft(unsigned short interval , unsigned short moveValue = default_moveValue2)
  {
    movingBaseMinus(yaw_axis, moveValue, interval);
  }

  private: unsigned short calculateX(unsigned short moveValue, unsigned short interval, unsigned short default_brakeInterval)
  {
    return moveValue *( interval / default_brakeInterval);
  }
  
  private: void movingBasePlus(byte channel_number, unsigned short move_value, unsigned short interval)
  {
    ppm[channel_number] = default_servo_value + move_value;
    delay(interval);
    ppm[channel_number] = default_servo_value;
  }
  
  private: void movingBaseMinus(byte channel_number, unsigned short move_value, unsigned short interval)
  {
    ppm[channel_number] = default_servo_value - move_value;
    delay(interval);
    ppm[channel_number] = default_servo_value;
  }

};
  
MoveController *moveController = new MoveController();

void setup(){  
  //initialize default ppm values
 pinMode(inpin, INPUT);
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
}
void loop(){
  
  moveController->reset();
  
int inp = digitalRead(inpin);
if (inp != 0){
    moveController->moveForward(600);
    delay(500);
   /* moveController->moveLeft(600);
    delay(500);
    moveController->moveBackward(600);
    delay(500);
    moveController->moveRight(600);
    delay(500);
    moveController->turnLeft(2835);
    delay(500);
    moveController->turnRight(2835);*/
}
//  moveController->moveUp(1000);
/*
if(){
  moveController->moveForward(500);
}
if(){
  moveController->moveBackward(500);
}
if(){
  moveController->moveLeft(500);
}
if(){
  moveController->moveRight(500);
}
if(){
  moveController->turnLeft(500);
}
if(){
  moveController->turnRight(500);
}
*/
//  moveController->moveDown(1000);
}

ISR(TIMER1_COMPA_vect)
{
  //leave this alone
  static boolean state = true;
  
  TCNT1 = 0;
  
  if(state)
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

    if (cur_chan_numb >= MoveController::number_of_channels)
    {
      cur_chan_numb = 0;
      calc_rest = calc_rest + PPM_PulseLen;// 
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
