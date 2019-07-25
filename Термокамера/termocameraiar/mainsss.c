/* RemHolod monitoring device ver. 0.1 alpha*/
/*================================================
программа должна делать:
1) по команде с компьютера высылать пакет информации состоящей из
	а) температуры (Датчик 1);
	б) температуры (Датчик 2);
	в) состояния ключей канала 1; СЛ
	г) состояния ключей канала 2;	О
	д) состояния ключей канала 3;	  В	
	е) состояния ключей канала 4;	   О
2) по команде с компьютера включать и выключать периферийные 
устройства и сообщать состояния ключей после выполнения команды
Если в данный момент контроллер ожидает конвертации температуры,
то он должен сообщить об этом.
==================================================*/

// 8MHz gives 1/8000000 = 0.000000125 sec
// microseconds: 0.000001/0.000000125 = 8 for "__delay_cycles"

/*12,02,02 не вижу причины считывать ROM таблицу каждого датчика 
температуры*/
/*считывать ром не требуется если по одному датчику на линию, но теперь 
прийдется ставить несколько на линию
*/

#include "io8515.h"
#include "ina90.h"

//*************************************

//volatile unsigned char Table_incom_state[8];
static volatile unsigned char buff, error, buffalo;
static volatile unsigned char packet_length, packet_counter=0;
volatile static __no_init char receive_buffer[6];
volatile static __no_init char send_buffer[6];
static volatile unsigned char CRC = 0, packet_done=0, outsider=0;
volatile static __no_init char ROM_number[6];


/*//ФЛАГИ - ПОЧЕМУ ТО НЕ РАБОТАЮТ ???
static volatile unsigned char flags;

#define marker 0;
#define need_temperature 1;
#define need_channel 2;
*/
//СЕТЕВОЙ АДРЕС фОРМАТ - СТАРШАЯ ТЕТРАДА, В НЕЙ НУМЕРАЦИЯ С НУЛЯ!!!
flash unsigned char adress=0X00;//НОМЕР КОНТРОЛЛЕРА ОТСЛЕЖИВАТЬ ЗДЕСЬ
//команды
#define send_keys 0x0A;
// подпрограмма отправки байта поллингом... (мона заменить на прерываением)

void Send_Buff_PC (void)
{
 buffalo = 1;
 UCR |= (1<<UDRIE);
 while (buffalo);
}

#include "ds18b20.c"
# define baudrate 103 ; //set the speed, 8MHz crystal, to 4800bps
#define Bit(n) (1 << (n));
//#include "ReadROM.c"

#define LSB 0;
#define MSB 1;
#define Th 2;     // МОЖНО РЕЗЕТИТЬ??? - НЕТ КОНЕЧНО _ КАК ЦРЦ ЩИТАТЬ?
#define Tl 3;
#define user1 4;
#define Res1 5;
#define Res2 6;
#define Res3 7;
#define RamCRC 8;

/* Prototypes */

void Send_error (char err_code)
{
	_SEI();
	buff = (adress | 0x02); CRC = buff;
	Send_Buff_PC();
//	buff = 0xF0 + (err_code & 0xF); CRC += buff; // ошибка - нераспознана команда
	buff = err_code; CRC += buff; // ошибка - нераспознана команда
	Send_Buff_PC();
	buff = (~CRC)+1;
	Send_Buff_PC();
	err_code = 0;
	return;
}
/*
//ПРЕОБРАЗОВАНИЕ В ЦЕЛЬЧИИ И ПОСЫЛ температуры
void Send_Temp_Celsium (void)
{
	char temp_lsb, temp_msb, sig =0;
	unsigned int Celsium = 0;
	Celsium = ((Celsium || ScratchpadTable[1])<<8);
	Celsium |= (ScratchpadTable[0]);
	if (ScratchpadTable[1] >= 0xf8) // binary 1111 1000 - look table for DS18
		{
		Celsium = (~Celsium)+1;
		//signal1 = 0xff;
		}
	//else signal1 = 0x00;
	temp_lsb=(Celsium>>4);		//except 4 MSBits
	sig = ((Celsium >> 8) & 0x07);	//except 5 MSBits
	sig &= 0x07;				//
	temp_msb=(sig<<4);				//
	temp_lsb |= temp_msb;
	temp_msb=((Celsium >> 8)&0x0F);
	sig=(Celsium >>11);
	//sig = (sig >>3);
	PORTD &= ~Bit(7);     

	
	_SEI();
	buff = 0xaa;
	Send_Buff_PC();
	_CLI();
	
	_SEI();
	buff = 0xab;
	Send_Buff_PC();
	_CLI();	

	_SEI();
	buff = 0xac;
	Send_Buff_PC();
	_CLI();


	_SEI();
	//buff = 0xaa; //CRC+=buff;
	buff = sig; CRC+=buff;
	Send_Buff_PC();//отправка температуры
	_CLI();
	_SEI();
	buff = temp_lsb; CRC+=buff;
	Send_Buff_PC();
	_CLI();
	_SEI();
	buff = temp_msb;CRC+=buff;
	Send_Buff_PC(); 
	_CLI();
	send_buffer[0]=sig;
	send_buffer[1]=temp_lsb;
	send_buffer[2]=temp_msb;

	_SEI();
	
return;	
}//Send_Temp_Celsium
*/

// interrupt handlers 
#pragma vector=UART_RX_vect
__interrupt void UART_RX_interrupt(void)
{
char buffer = UDR;

//ИЗМЕНЕНИЯ ПАКЕТ ПРОВЕРКА ПРИСУТСТВИЯ
//if (buffer == 0xff) buff = buffer;

if (packet_counter) //получаем пакет
	{
	if (outsider) 
		{
		packet_counter--; 
		return;
		}//не мне
	receive_buffer[packet_counter-1] = buffer;
	packet_counter--;
	if (!packet_counter) 
		{
		packet_done = 1;
		CRC = (~CRC)+1;
		CRC -= receive_buffer[0]; 
		return;
		}	
	else //ЕЩЕ не все байтики получены
		{
		CRC += buffer;return;
		} //ЕЩЕ не все байтики получены
	}//получаем пакет
else //пока НЕ получаем пакет
	{
	if ((buffer&0XF0) == adress)//НОМЕР КОНТРОЛЛЕРА ОТСЛЕЖИВАТЬ ЗДЕСЬ!!!
		{
		//UDR = buffer; UCR|=(1<<TXEN);
		packet_counter = (buffer & 0x0f);
		packet_length = packet_counter;
		CRC = buffer;
		packet_done = 0;
		outsider = 0;
		return;
		}//if controller number
	else
		{
		packet_counter = (buffer & 0x0f);
		outsider = 1;
		}//not mine adress
	}//if begin receive packet
return;
}
//отправление байта из подпрограммы обработки прерывания 
//получения байта -> перехлест стека.

#pragma vector=UART_UDRE_vect
__interrupt void UART_UDRE_interrupt(void)
{
UDR = buff;
buffalo = 0;
UCR &= ~(1<<UDRIE);
} 

/*#pragma vector =TIMER0_OVF0_vect
__interrupt void TIMER0_OVF0_interrupt (void) 
{

}
*/

//################################################################
//MAIN
__C_task void  main( void )
{
// *******initialize UART 
UBRR = baudrate; 	// set the baud rate 
// enable UART receiver and transmitter, and receive interrupt
UCR = ( (1<<RXCIE) | (1<<RXEN) | (1<<TXEN) );
_SEI(); 			// enable interrupts => enable UART
DDRA = 0X00;		//Port A - inputs.
DDRB = 0XFF;		//Port B - outputs.
DDRD = 0xFF; 		//Port D - outputs.
PORTD = 0xff;
PORTD |= Bit(3);	//SENSOR_2
PORTD &= ~Bit(PIND4);
PORTD = 0xff;
PORTB = 8;
packet_counter=0;
WDTCR = 0x0F;		// WATCHDOG TIMER STARTING 

while (1)           // forever 
	{		
	_WDR();
	
	if (packet_done)//если пришел пакет полностью
		{
		if (!CRC) //не ошибка - посчитанное CRC равно полученному CRC
			{
			char temp_var;
			temp_var = receive_buffer[packet_length-1];
			if (((receive_buffer[packet_length-1]) & 0xf0) == 0xf0) 
				{
				PORTD = 0X00;
				buff = (adress | 0x02);CRC += buff;
				Send_Buff_PC();
				buff = 0xF0;CRC += buff;
				Send_Buff_PC();
				CRC = (~CRC) + 1;
				buff = CRC;
				Send_Buff_PC();				
				goto end_check;
				}//ответ на проверку присутствия
			if ((temp_var & 0xF0) == 0xA0)
				{
				PORTD = 0X00;
				PORTB = ((receive_buffer[packet_length-1])&0x0f);//адрес на дешифратор 
				PORTB |= 0x08; //разрешить дешифратор
				buff = (adress | 0x03);CRC+= buff;
				Send_Buff_PC();
				buff = (receive_buffer[packet_length-1]);CRC += buff;
				Send_Buff_PC();
				buff = ~PINA; CRC += buff;
				Send_Buff_PC();
				buff = (~CRC)+1;
				Send_Buff_PC();
				packet_done = 0;	
				CRC = 0;
				PORTD = 0X00;
				goto end_check;
				}
			if ((temp_var & 0XF0) == 0xB0)
				{
				Read_Temperature((receive_buffer[packet_length-1])&0x0f);
				//проверка на ошибку, связанную с датчиком температуры.
				if (error) 
					{
					Send_error(error);
					goto end_check;
					}
				buff = (adress | 0x04);CRC+= buff;
				Send_Buff_PC();
				buff = (receive_buffer[packet_length-1]);CRC += buff;
				Send_Buff_PC();
				buff = ScratchpadTable[1];CRC += buff;
				Send_Buff_PC();
				buff = ScratchpadTable[0];CRC += buff;
				Send_Buff_PC();
				buff =(~CRC)+1;  
				Send_Buff_PC();
				packet_done = 0;
				CRC = 0;	
				goto end_check;
				}
			_SEI();
			
//			error = 0x11;
//			Send_error(error);
			/*buff = (adress | 0x02); CRC = buff;
			Send_Buff_PC();
			buff = 0x11; CRC += buff; // ошибка - нераспознана команда
			Send_Buff_PC();
			buff = (~CRC)+1;
			Send_Buff_PC();*/
end_check:
			_SEI();
			error = 0;
			PORTD = 0xF5;
			packet_done = 0;
			CRC = 0;
			}//не ошибка - посчитанное CRC равно полученному CRC
		else //ошибка - посчитанное CRC не равно полученному CRC
			{
			error = 0x10;
			Send_error (error);
			/*CRC = 0;
			buff = (adress |0x02); CRC += buff; 
			Send_Buff_PC();
			buff = 0x10; CRC += buff;
			Send_Buff_PC();
			buff = (~CRC)+1;
			Send_Buff_PC();*/
			CRC = 0;
			error = 0;
			packet_done = 0;
			PORTD = 0x00;
			}//ошибка - посчитанное CRC не равно полученному CRC
		} //обработка пакета packet handling.
	} // WHILE (1)
} // new for MAIN;

//#################################################################
