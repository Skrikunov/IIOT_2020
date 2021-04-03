void setup()
{

}

uint16_t result = 0; /// storage for ADC result

void segm7(uint8_t digit)  //update the 7-segment indicator display function
{
  switch (digit)
  {
    case 0:
      PORTD = 0b11111101;
      break;
    case 1:
      PORTD = 0b01100001;   //we need to light up B and C segments and dot (dp)
      break;
    case 2:
      PORTD = 0b11011011;   //we need to light up A,B,D,E,G segments and dot (dp)
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
  OCR1A = numb_16b; //the TOP value of the timer1

  TIMSK1 = 0;
  TIMSK1 |= (1 << OCIE1A); //interrupt enable

  TCCR1B = 0;
  TCCR1B |= (1 << WGM12) | (1 << CS12); //set prescaller to 256 and CTC mode
}

void tim2_start(uint8_t numb_8b)
{
  TCCR2A = 0; /// clear TCCR2A (Waveform Generation Mode)
  TCCR2A |= (1 << COM2A1) | (1 << WGM21) | (1 << WGM20); //set TCCR2A: non-inverting mode | WGM21 | WGM20 (fast PWM, TOV FlagSet on MAX)

  TCNT2 = 0; /// clear TCNT2 (Counter)
  OCR2A = numb_8b; //set value of compare register OCR2A

  TCCR2B = 0; /// clear TCCR2B (Clock prescaller)
  TCCR2B |= (1 << CS22); //set prescaller to 64 (WGM22=0)
}

void ADC_init()
{
  DDRC &= ~(1 << DDC0); ///configure DDRC0 as input
  PORTC &= ~(1 << PORTC0); ///without pull-up (influence in precision)

  ADMUX = 0; ///clear ADMUX (Multiplexer Selection Register)
  ADMUX |= (1 << REFS0); ///REFS0=1 - VCC as ref, ADLAR=0 (right adjusted), all MUX=0 (pin A0)
  
  ADCSRA = 0; ///clear ADCSRA (Control and Status Register A)
  ADCSRA |= (1 << ADEN) | (1 << ADATE) | (1 << ADPS2); ///ADC enable, Auto Trigger Source on (for ADCSRB), prescaler=16 (ADPS2)
  
  ADCSRB = 0; //clear ADCSRB (Control and Status Register b) - Free Running mode
}

uint8_t i = 0;  //global variable for the counter

ISR(TIMER1_COMPA_vect)
{
  do {
    ADCSRA |= (1 << ADSC); /// start conversion
  }
  while ((ADCSRA & (1 << ADIF)) == 0); // while ADIF = 0
  
  result = (ADCL | ADCH << 8); // read value (ADCH-MSB,ADCL-LSB)

  i = (uint8_t) 9.0 * (result / 1023.0); //counter value according PWM duty cycle

  OCR2A = (uint8_t) 255.0 * (i/ 9.0); ///discretly brightness changing (PWM)

  segm7(i); //update the 7-segment indicator display
}

void loop()
{ 
  DDRB |= (1 << DDB3); ///configure DDRB3 as output

  ADC_init(); ///init ADC
  
  DDRD = 0xff;  //set all pins in PORTD as output
  PORTD = 0x00; //set all pins in PORTD in LOW logical level

  tim1_start(625);  //set the timer1 to work with 0.01 second period
  tim2_start(0); ///start pwm on OC2A

  sei();  //enable all interrupts
  while (1)
  {
    //do nothing
  }
}
