#define KEY_PRT 	PORTC
#define KEY_DDR		DDRC
#define KEY_PIN		PINC
unsigned char keypad[4][3] = {	
		{'1','2','3'},
		{'4','5','6'},
		{'7','8','9'},
		{'*','0','#'}
	};
unsigned char colloc, rowloc;
char keyfind(){
	while(1){
		KEY_DDR = 0xF0;                /* set port direction as input-output */
		KEY_PRT = 0xFF;

		do
		{
			KEY_PRT &= 0x0F;           /* mask PORT for column read only */
			asm("NOP");
			colloc = (KEY_PIN & 0x0F); /* read status of column */
		}while(colloc != 0x0F);
		
		
		do
		{
			_delay_ms(20);			   /* 20ms key debounce time */
			colloc = (KEY_PIN & 0x0F); /* read status of column */
			}while(colloc == 0x0F);        /* check for any key press */
			
			

			/* now check for rows */
			KEY_PRT = 0xEF;            /* check for pressed key in 1st row */
			asm("NOP");
			colloc = (KEY_PIN & 0x0F);
			if(colloc != 0x0F)
			{
				rowloc = 0;
				break;
			}

			KEY_PRT = 0xDF;			  /* check for pressed key in 2nd row */
			asm("NOP");
			colloc = (KEY_PIN & 0x0F);
			if(colloc != 0x0F)
			{
				rowloc = 1;
				break;
			}
			
			KEY_PRT = 0xBF;			  /* check for pressed key in 3rd row */
			asm("NOP");               /* no operation*/
			colloc = (KEY_PIN & 0x0F);
			if(colloc != 0x0F)
			{
				rowloc = 2;
				break;
			}

			KEY_PRT = 0x7F;			  /* check for pressed key in 4th row */
			asm("NOP");
			colloc = (KEY_PIN & 0x0F);
			if(colloc != 0x0F)
			{
				rowloc = 3;
				break;
			}
		}

		if(colloc == 0x0E)
		return(keypad[rowloc][0]-48);
		else if(colloc == 0x0D)
		return(keypad[rowloc][1]-48);
		else if(colloc == 0x0B)
		return(keypad[rowloc][2]-48);
		else
		return(keypad[rowloc][3]-48);
	}

	int charToInt(char c)
	{
		return c - '0';
	}