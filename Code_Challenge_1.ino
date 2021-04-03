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


void loop()
{
  
  DDRD = 0xff;	//set all pins in PORTD as output
  PORTD = 0x00;	//set all pins in PORTD in LOW logical level
  
  while(1)	//infinite cycle
  {
   for(uint8_t i=0; i<10; i++)
   {
     segm7(i);		//update the 7-segment indicator display
     delay(1000);	//wait 1 second
   }
  }
  
}

