
#define US_PORT PORTA
#define	US_PIN	PINA  
#define US_DDR 	DDRA
#define US_ERROR		-1
#define	US_NO_OBSTACLE	-2


void lcd_command( unsigned char );

void HCSR04Init(char trig){
	US_DDR|=(1<<trig);
}

void HCSR04Trigger(char trig){ 
	US_PORT|=(1<<trig);
	_delay_us(15);
	US_PORT&=~(1<<trig);
}

uint16_t GetPulseWidth(char echo){
	uint32_t i,result;
	for(i=0;i<600000;i++){
		if(!(US_PIN & (1<<echo)))
			continue;
		else
			break;
	}
	if(i==600000)
	return US_ERROR;
	TCCR1A=0X00;
	TCCR1B=(1<<CS11);
	TCNT1=0x00;
	for(i=0;i<600000;i++){
		if(US_PIN & (1<<echo)){
			if(TCNT1 > 60000) break; else continue;
		}
		else
			break;
	}
	if(i==600000)
		return US_NO_OBSTACLE;
	result=TCNT1;
	TCCR1B=0x00;
	if(result > 60000)
	return US_NO_OBSTACLE;
	else
	return (result>>1);
}

int calculateDistance(char trig, char echo, int distance){
	int Bowldistance;
	uint16_t r;
	HCSR04Init(trig);
	HCSR04Trigger(trig);
	r=GetPulseWidth(echo);
	Bowldistance=(r*0.034/2.0);
	if(Bowldistance<distance){
		return 1;
		}else{
		return 0;
	}
	_delay_ms(30);
}