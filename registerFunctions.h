//set port to high and low
#define portHigh(register,pinNumber) register =  register | (1<<pinNumber)
#define portLow(register,pinNumber) register = register & (~(1<<pinNumber))
//read input
#define pinRead(register,pinNumber) (register & (1<<pinNumber))
//pin mode, Input or Output
#define setOutput(register,pinNumber) register = register | (1<<pinNumber)
//enable pull up
#define enablePullup(register,pinNumber) register = register | (1<<pinNumber)

/*
setOutput(DDRC,1);
portHigh(PORTC,1);
portLow(PORTC,1);
*/