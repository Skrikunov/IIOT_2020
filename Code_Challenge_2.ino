void setup()
{
 
}



void segm7(uint8_t digit)	//update the 7-segment indicator display function
{
  switch (digit) 
  {
  case 0:
    PORTD = 0b11111101;
    break;
  case 1:
    PORTD = 0b01100001;		//we need to light up B and C segments and dot (dp)
    break;
  case 2:
    PORTD = 0b11011011;		//we need to light up A,B,D,E,G segments and dot (dp)
    break;
  case 3:
    PORTD = 0b11110011;
    break;
  case 4:
    PORTD = 0b01100111;
    break;
  case 5:
    PORTD = 0b10110111;
    break;
  case 6:
    PORTD = 0b10111111;
    break;
  case 7:
    PORTD = 0b11100001;
    break;
  case 8:
    PORTD = 0b11111111;
    break;
  case 9:
    PORTD = 0b11110111;
    break;
  default:
    PORTD = 0x00;
    break;
  }
}

void tim1_start(uint16_t numb_16b)
{
  TCCR1A = 0;

  TCNT1 = 0;
  OCR1A = numb_16b;	//the TOP value of the timer1

  TIMSK1 = 0;
  TIMSK1 |= (1<<OCIE1A);	//interrupt enable
  
  TCCR1B = 0;
  TCCR1B |= (1<<WGM12)|(1<<CS12);	//set prescaller to 256 and CTC mode
}

uint8_t i = 0;	//global variable for the counter

ISR(TIMER1_COMPA_vect)
{
  segm7(i);	//update the 7-segment indicator display
  if(i<9){	//just a counter from 0 to 9
    i++;
  }else{
    i=0;
  }
}

void loop()
{
  
  
  DDRD = 0xff;	//set all pins in PORTD as output
  PORTD = 0x00;	//set all pins in PORTD in LOW logical level
  
  tim1_start(62500);	//set the timer1 to work with 1 second period
  
  
  sei();	//enable all interrupts
  while(1)
  {
    //do nothing
  }
  
}

