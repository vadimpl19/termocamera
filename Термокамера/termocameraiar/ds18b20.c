//definitions
//массив Scratchpad


#define FALSE 0
#define TRUE 1
////////////////////////////////////////////////////////////////////////////
// GLOBAL VARIABLES
//
//unsigned char ROM[8]; // ROM Bit - мне не надо, у меня по одному на линии.
/*unsigned char lastDiscrep = 0; // last discrepancy
unsigned char doneFlag = 0; // Done flag
unsigned char FoundROM[5][8]; // table of found ROM codes
unsigned char numROMs;*/
volatile static unsigned char ScratchpadTable[9];
unsigned char dowcrc;
unsigned char flash dscrc_table[] = {
0, 94,188,226, 97, 63,221,131,194,156,126, 32,163,253, 31, 65,
157,195, 33,127,252,162, 64, 30, 95, 1,227,189, 62, 96,130,220,
35,125,159,193, 66, 28,254,160,225,191, 93, 3,128,222, 60, 98,
190,224, 2, 92,223,129, 99, 61,124, 34,192,158, 29, 67,161,255,
70, 24,250,164, 39,121,155,197,132,218, 56,102,229,187, 89, 7,
219,133,103, 57,186,228, 6, 88, 25, 71,165,251,120, 38,196,154,
101, 59,217,135, 4, 90,184,230,167,249, 27, 69,198,152,122, 36,
248,166, 68, 26,153,199, 37,123, 58,100,134,216, 91, 5,231,185,
140,210, 48,110,237,179, 81, 15, 78, 16, 242, 172, 47, 113,147,205,
17, 79,173,243,112, 46,204,146,211,141,111, 49,178,236, 14, 80,
175,241, 19, 77,206,144,114, 44,109, 51,209,143, 12, 82,176,238,
50,108,142,208, 83, 13,239,177,240,174, 76, 18,145,207, 45,115,
202,148,118, 40,171,245, 23, 73, 8, 86,180,234,105, 55,213,139,
87, 9,235,181, 54,104,138,212,149,203, 41,119,244,170, 72, 22,
233,183, 85, 11,136,214, 52,106, 43,117,151,201, 74, 20,246,168,
116, 42,200,150, 21, 75,169,247,182,232, 10, 84,215,137,107, 53};

//////////////////////////////////////////////////////////////////////////////
// OW_RESET - performs a reset on the one-wire bus and
// returns the presence detect. Reset is 480us, so delay
// value is (480-24)/16 = 28.5 - we use 29. Presence checked
// another 70us later, so delay is (70-24)/16 = 2.875 - we use 3.
//
unsigned char ow_reset(pinnumberr)
{
unsigned char presence = 0;
PORTD &= ~(1<<pinnumberr);//pull DQ line low
__delay_cycles(3860);// leave it low for >480us
PORTD |= (1<<pinnumberr);// allow line to return high
__delay_cycles(576);// wait for presence 72us
presence = (PIND & (1<<pinnumberr)); // get presence signal
__delay_cycles(3400);// wait for end of timeslot  480-72=408 us
return(presence); // presence signal returned 
} // 0=presence, X = no part

/////////////////////////////////////////////////////////////////
// READ_BIT - reads a bit from the one-wire bus. The delay
// required for a read is 15us, so the DELAY routine won't work.
// We put our own delay function in this routine in the form of a
// for() loop.
//520 тактов при 8МГц = 65мкс
unsigned char read_bit(pinnbr)
{
char temp;
PORTD &= ~(1<<pinnbr);// pull DQ low to start timeslot
__delay_cycles(8);   //вкл датчик  (2)
PORTD |= (1<<pinnbr); //then return high
__delay_cycles(104);  //в пределах 15мкс (13)
temp = PIND;
temp &= (1<<pinnbr);
temp = (temp >> pinnbr);
//delay to 15us from start of timeslot + 
__delay_cycles(680);// до >65us->слот для чтения бита плюс запас=>можно 
                    //брать след бит.
return(temp);       //return value of DQ line
}

//////////////////////////////////////////////////////////////////
// WRITE_BIT - writes a bit to the one-wire bus, passed in bitval.
//
void write_bit(char bitval, char pnumber) //all time - 640cyc = 80us (60<t<120)
{
PORTD &= ~(1<<pnumber);	// pull DQ low to start timeslot
__delay_cycles(8); 	//чуть больше 1 мкс 
if(bitval==1) PORTD |= (1<<pnumber);// return DQ high if write 1
__delay_cycles(520);	//65- to 65us hold value 4 remainder of timeslot
PORTD |= (1<<pnumber);
__delay_cycles(24); 	//between timeslots
}// Delay provides 16us per loop, plus 24us. 
//Therefore delay(5) = 104us

//////////////////////////////////////////////////////////////////////////////
// READ_BYTE - reads a byte from the one-wire bus.
//
unsigned char read_byte(char pinnm)
{
unsigned char i;
unsigned char value = 0;
for (i=0;i<8;i++)
  if(read_bit(pinnm)) value|=(0x01<<i); // reads byte in, one bit at a time 
                                   //and then shifts it left
return(value);
}
//////////////////////////////////////////////////////////////////////////////
// WRITE_BYTE - writes a byte to the one-wire bus.
//
void write_byte(char val, char pinnum)
{
unsigned char i;
unsigned char temp;
for (i=0; i<8; i++) // writes byte, one bit at a time
  {
  temp = val>>i; // shifts val right 'i' spaces
  temp &= 0x01; // copy that bit to temp
  write_bit(temp, pinnum); // write bit in temp into
  }
//__delay_cycles(80); // between words
}

//////////////////////////////////////////////////////////////////////////////
// ONE WIRE CRC
//
unsigned char ow_crc( unsigned char x)
{
dowcrc = dscrc_table[dowcrc^x];
return dowcrc;
}
/* //вычисление температуры
void CalcTemperature (void)
{
__no_init static char TemperatureFrac;
__no_init static char TemperatureBase;
__no_init static char TemperatureSign;
//tempLSB == Scratchpad[LSB];
TemperatureSign = (Scratchpad[MSB]>>3);
TemperatureFrac = (Scratchpad[LSB]) & 0x0F;
TemperatureFrac >>= 2;
TemperatureFrac = 100 * TemperatureFrac;
if (TemperatureFrac) TemperatureFrac = 5;
TemperatureBase = (Scratchpad[LSB]>>4) | (Scratchpad[MSB]<<5);
TemperatureBase |= 0x7F; // mask 1111111 (7 x 1)
}
//tempMSB == Scratchpad[MSB];*/

void Read_Temperature (char pinnumber)
{
char k;
_CLI(); 
k = 3;
Read_Temp:
	if (!ow_reset(pinnumber))
		{
		write_byte(0xCC, pinnumber); 	//Skip ROM
		write_byte(0x44, pinnumber); 	// Start Conversion
		}
	else 					//нет отклика на резет 
		{
		k--;//пробуем 3 раза резетить - потом сообщаем об ошибке и уходим
		if (!k) 
			{
			_SEI();
			
//***************************						
			error = 0x12;//UCR |= (1<<UDRIE);while (error);//НЕТ ОТКЛИКА ОТ ДАТЧИКА
			return;
			}
		else goto Read_Temp;
		}
	
	while (!(PIND & (1<<pinnumber))) PORTD &= ~(1<<PIND6);
	
	//ПРОВЕРКА ПИНА ТЕМПЕРАТУРЫ ПО АДРЕСУ ИЗ RECEIVED_BUFFER

	dowcrc=0;
	if (!ow_reset(pinnumber))
		{
		write_byte(0xCC, pinnumber); 	// Skip ROM
		write_byte(0xBE, pinnumber); 	// Read Scratch Pad
		for (k=0;k<9;k++)
			{
			ScratchpadTable[k]=read_byte(pinnumber);
			ow_crc(ScratchpadTable[k]);
			}
		ow_reset(pinnumber);
		}
	else 					
		{
		_SEI();
		error = 0x13;//UCR |= (1<<UDRIE);while (buff);//нет отклика на резет ПОСЛЕ КОНВЕРСИИ
		return;
		}
	if (dowcrc) 			
		{
		_SEI();
		error = 0x14;//UCR |= (1<<UDRIE);while (buff);//CRC <> 0 - ошибка
		return;
		}
	else
		{
				
		}	//else
	_SEI();
}			//Read_Temperature
