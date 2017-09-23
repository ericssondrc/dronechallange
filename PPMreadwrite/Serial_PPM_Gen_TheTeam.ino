//Ez a gagyi program soros porton várja a 4db csatorna adatot és egy lezárót (242) összesen 5 byte
// A csatorna adatok 0-200 között változhatnak, 0 jelenti a 1000uS-et, 200 a 2000uS-et
// Csatornakiosztás roll-pitch-throttle-yaw-lezáró(242 érték)

//////////////////////CONFIGURATION///////////////////////////////
#define chanel_number 8  //set the number of chanels
#define default_servo_value 1700  //set the default servo value
#define PPM_FrLen 22500  //set the PPM frame length in microseconds (1ms = 1000µs)
#define PPM_PulseLen 300  //set the pulse length
#define onState 1  //set polarity of the pulses: 1 is positive, 0 is negative
#define sigPin 4  //set PPM signal output pin on the arduino
//////////////////////////////////////////////////////////////////
byte val[5], i;



int ppm[chanel_number];

void setup(){
  Serial.begin(9600);         //Baud rate beállítása
  
  for(int i=0; i<chanel_number; i++){
    ppm[i]= default_servo_value;
  }

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
bool res = false;
void loop()
{   
    if(Serial.available())
    {
      Serial.readBytesUntil((unsigned char)242,val,5); // 5Byte-ot olvas ki amíg a 242-es lezáró meg nem érkezik
    }

    ppm[0]= 1000 + (val[4]*5); // Csatornakiosztások és a byte adatból pwm adat számolása
    ppm[1]= 1000 + (val[0]*5);
    ppm[2]= 1000 + (val[1]*5);
    ppm[3]= 1000 + (val[2]*5);
      
    
   
   
   // ppm[2]=1200;
   // delay(1000);
   // ppm[2]=1800;
   // delay(1000);
    
}





 



ISR(TIMER1_COMPA_vect){  //leave this alone
  static boolean state = true;

  TCNT1 = 0;

  if(state) {  //start pulse
    digitalWrite(sigPin, onState);
    OCR1A = PPM_PulseLen * 2;
    state = false;
  }
  else{  //end pulse and calculate when to start the next pulse
    static byte cur_chan_numb;
    static unsigned int calc_rest;

    digitalWrite(sigPin, !onState);
    state = true;

    if(cur_chan_numb >= chanel_number){
      cur_chan_numb = 0;
      calc_rest = calc_rest + PPM_PulseLen;//
      OCR1A = (PPM_FrLen - calc_rest) * 2;
      calc_rest = 0;
    }
    else{
      OCR1A = (ppm[cur_chan_numb] - PPM_PulseLen) * 2;
      calc_rest = calc_rest + ppm[cur_chan_numb];
      cur_chan_numb++;
    }
  }
}
