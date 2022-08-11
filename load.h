uint8_t hx711H=0; //Load Scale High Bits
uint16_t hx711L=0;//Load Scale Low Bits
volatile uint16_t TimerCal=0;// variable for collect echo data
float loadCellRead(){
	hx711H=0;hx711L=0;  //clear variables
	for(uint8_t i=0;i<8;i++){  // Load cell data high 8 bits
		PORTA|=(1<<0); //Clock pin high
		_delay_us(10);
		if ((PINA&(1<<1))>>1){
			hx711H|=(1<<(7-i));
		}
		else{
			hx711H&=~(1<<(7-i));
		}
		PORTA&=~(1<<0); //Clock pin low
		_delay_us(5);
	}
	
	
	for(uint8_t i=0;i<16;i++){ // Load cell data low 16 bits
		PORTA|=(1<<0); //Clock pin high
		_delay_us(10);
		if ((PINA&(1<<1))>>1){
			hx711L|=(1<<(15-i));
		}
		else{
			hx711L&=~(1<<(15-i));
		}
		PORTA&=~(1<<0); //Clock pin low
		_delay_us(5);
	}
	
	hx711L=hx711L>>1; //shift bits
	
	if (hx711H&1){
		hx711L|=(1<<15);
	}
	else{
		hx711L&=~(1<<15);
	}
	hx711H=hx711H>>1;
	
	return (hx711H*(65536/18029.6))+hx711L/18029.6; //load cell calibration
}