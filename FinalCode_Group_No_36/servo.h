
void servo1ninety(void);
void servo1zero(void);
void servo2ninety(void);
void servo2zero(void);

void servo1ninety(void)
{
	
	PORTD = 0x20;
	while(1)
	{
		//Rotate Motor to 0 degree
		PORTD = 0x20;
		_delay_us(1000);
		PORTD = 0x00;
		
		_delay_ms(2000);
		
		//Rotate Motor to 90 degree
		PORTD = 0x20;
		_delay_us(1500);
		PORTD = 0x00;
		
		_delay_ms(2000);
		
		break;
	}
}

void servo1zero(void)
{
	
	PORTD = 0x20;
	while(1)
	{
		//Rotate Motor to 0 degree
		PORTD = 0x20;
		_delay_us(1000);
		PORTD = 0x00;
		
		_delay_ms(2000);
		
		break;
	}
}


void servo2ninety(void)
{
	
	PORTD = 0x10;
	while(1)
	{
		//Rotate Motor to 0 degree
		PORTD = 0x10;
		_delay_us(1000);
		PORTD = 0x00;
		
		_delay_ms(2000);
		
		//Rotate Motor to 90 degree
		PORTD = 0x10;
		_delay_us(1500);
		PORTD = 0x00;
		
		_delay_ms(2000);
		
		break;
	}
}

void servo2zero(void)
{
	
	PORTD = 0x10;
	while(1)
	{
		//Rotate Motor to 0 degree
		PORTD = 0x10;
		_delay_us(1000);
		PORTD = 0x00;
		
		_delay_ms(2000);
		
		break;
		
	}
}