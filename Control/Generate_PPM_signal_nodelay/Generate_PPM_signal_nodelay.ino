//this program will put out a PPM signal

//////////////////////CONFIGURATION///////////////////////////////

#define PPM_FrLen 22500  //set the PPM frame length in microseconds (1ms = 1000µs)
#define PPM_PulseLen 300  //set the pulse length
#define onState 1  //set polarity of the pulses: 1 is positive, 0 is negative
#define sigPin 10  //set PPM signal output pin on the arduino
//////////////////////////////////////////////////////////////////

/*this array holds the servo values for the ppm signal
 change these values in your code (usually servo values move between 1000 and 2000)*/

class MoveController
{
  public: static const byte number_of_channels = 8;
  private: static const unsigned short default_servo_value = 1500;
  private: static const byte roll_axis = 0;
  private: static const byte pitch_axis = 1;
  private: static const byte trust_axis = 2;
  private: static const byte yaw_axis = 3;
  
  private: static const unsigned short default_interval = 200;
  private: static const unsigned short max_move_value = 500;
  
  public: int ppm[MoveController::number_of_channels];
  
  public: void reset()
  {
    for (int i = 0; i < MoveController::number_of_channels; i++)
    {
      ppm[i] = default_servo_value;
    }
  }
  
  public: void moveForward(unsigned short moveValue, unsigned short interval = default_interval)
  {
    movingBasePlus(pitch_axis, moveValue, interval);
  }

  public: void moveBackward(unsigned short moveValue, unsigned short interval = default_interval)
  {
    movingBaseMinus(pitch_axis, moveValue, interval);
  }

  public: void moveRight(unsigned short moveValue, unsigned short interval = default_interval)
  {
    movingBasePlus(roll_axis, moveValue, interval);
  }

  public: void moveLeft(unsigned short moveValue, unsigned short interval = default_interval)
  {
    movingBaseMinus(roll_axis, moveValue, interval);
  }

  public: void moveUp(unsigned short moveValue, unsigned short interval = default_interval)
  {
    movingBasePlus(trust_axis, moveValue, interval);
  }

  public: void moveDown(unsigned short moveValue, unsigned short interval = default_interval)
  {
    movingBaseMinus(trust_axis, moveValue, interval);
  }

  public: void turnRight(unsigned short moveValue, unsigned short interval = default_interval)
  {
    movingBasePlus(yaw_axis, moveValue, interval);
  }

  public: void turnLeft(unsigned short moveValue, unsigned short interval = default_interval)
  {
    movingBaseMinus(yaw_axis, moveValue, interval);
  }
  
  private: void movingBasePlus(byte channel_number, unsigned short move_value, unsigned short interval = default_interval)
  {
    move_value = getAdjustedMoveValue(move_value);
    ppm[channel_number] = default_servo_value + move_value;
    Serial.println(String(ppm[channel_number]));
    delay(interval);
    ppm[channel_number] = default_servo_value;
    Serial.println(String(ppm[channel_number]));
  }
  
  private: void movingBaseMinus(byte channel_number, unsigned short move_value, unsigned short interval = default_interval)
  {
    move_value = getAdjustedMoveValue(move_value);
    ppm[channel_number] = default_servo_value - move_value;
    delay(interval);
    ppm[channel_number] = default_servo_value;
  }

  private: unsigned short getAdjustedMoveValue(unsigned short moveValue)
  {
    if (moveValue > MoveController::max_move_value)
    {
      return MoveController::max_move_value;
    }
  
    return moveValue;
  }
};
  
MoveController *moveController = new MoveController();

void setup(){  
  Serial.println("lefut: Steiner Dániel");
 //initialize default ppm values

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

  Serial.begin(9600);
}

void loop(){
  moveController->reset();
//  moveController->moveUp(100);
  moveController->moveForward(100);
  moveController->moveBackward(100);
  moveController->moveLeft(100);
  moveController->moveRight(100);
  moveController->turnLeft(100);
  moveController->turnRight(100);
//  moveController->moveDown(100);
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
