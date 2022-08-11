#define F_CPU 8000000UL
#include "headerfiles.h"
void prepareMeal(int);
int main(void){
	DDRD=0xF4;
	LCD_Init();_delay_ms(50);
	ADC_Init();
	PWM_init();
	USART_init(9600);
	char RFID[12]="/0"; memset(RFID,0,15);
	LCD_Clear(); LCD_String("Welcome");LCD_Command(0xC0); LCD_String("Press Start");
	_delay_ms(2000);
	
	start:
    while (1){
		//read milk level
		int MilkFlag=calculateDistance(PA6,PA7,12);//24 in proteus
		if(MilkFlag != 1){
			LCD_Clear();
			LCD_String("Low milk level");
			while(1){}
		}else{
			//read temperature and turn on heater
			LCD_Clear();
			while((ADC_Read(2)/2)<=65){
				LCD_String("Milk Heating");
				LCD_Command(0xC0);
				LCD_String("in Process");
				_delay_ms(2000);
				LCD_Clear();
				PORTD=0x04;
			}
			PORTD = 0x00;
		}
		//start button 1
		int keyStart =keyfind();
		if(keyStart==1){
			LCD_Clear();
			LCD_String("Show RFID tag");
			for (int i=0;i<12;i++){ //read rfid chars
				RFID[i]=USART_rxc();
			}
			LCD_Clear();
			if(strcmp(RFID,"123456789012")==0){//if registered user
				LCD_String("Select The Size");
				LCD_Command(0xC0);
				LCD_String("3: Small 4:Large");
				int key=keyfind();
				if(key==3){
					prepareMeal(50);
				}else if(key==4){
					prepareMeal(80);
				}else{
					goto start;
				}
			}else{
				LCD_Clear();
				LCD_String("Unregistered");
				LCD_Command(0xC0);
				LCD_String("User");
				_delay_ms(3000);
				goto start;
			}
		}
    }
}

void prepareMeal(int weight){
	
	//weight can be 50g(key 3) 80g(key 4)
	LCD_Clear();
	LCD_String("Place the Bowl");
	_delay_ms(100);
	int BowlFlag=calculateDistance(PA3,PA5,10);//20 in proteus
	if(BowlFlag==1){
		LCD_Clear();
		LCD_String("Press cook(2)");
		_delay_ms(1000);
		int key1=keyfind();
		if(key1==2){
			LCD_Clear();
			LCD_String("Preparing");
			_delay_ms(1000);
			LCD_Clear();
			servo1ninety();//servo top lid
			char lcddata[20];
			int hx=0;
			while(hx<=weight){
				DDRA|=(1<<0);		//Load cell clock pin
				PORTA&=~(1<<0);		//Clock pin low
				hx=loadCellRead();		//inserting load cell calibration function
				_delay_ms(100);
				itoa(hx,lcddata,10);		//convert int to string
				LCD_String(lcddata);		//data to be displayed on lcd
				_delay_ms(1000);
				LCD_Clear();
				};
			LCD_String("Limit exceeded");
			servo1zero();//close servo top lid
			_delay_ms(10);
			servo2ninety();//servo bottom lid open
			_delay_ms(20);
			servo2zero();//servo bottom close
			LCD_Clear();
			LCD_String("Moving Belt");
			portHigh(PORTD,6);
			_delay_ms(5);
			PORTD = 0x00;
			_delay_ms(5000);
			LCD_Clear();
			LCD_String("Flowing Milk");
			portHigh(PORTD,7);
			_delay_ms(10);
			PORTD =0x00;
			_delay_ms(15000);
			LCD_Clear();
			
			
			LCD_String("Cornflakes");
			LCD_Command(0XC0);
			LCD_String("Ready");
			_delay_ms(10000);
			LCD_Clear();
			
		}
		
		
	}else{
		LCD_Clear();
		LCD_String("Place Bowl");
	}
}

