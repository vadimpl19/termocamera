/****************************************************************************
 **             - iom128.h -
 **
 **     This file declares the internal register addresses for ATmega128.
 **
 **     Used with iccAVR and aAVR.
 **
 **     Copyright IAR Systems 2001. All rights reserved.
 **
 **     File version: $Revision: 1.7 $
 **
 ***************************************************************************/

#include "iomacro.h"

#if TID_GUARD(3)
#error This file should only be compiled with iccavr or aavr whith processor option -v3
#endif /* TID_GUARD(3) */

/* Include the SFR part if this file has not been included before,
 * OR this file is included by the assembler (SFRs must be defined in
 * each assembler module). */
#if !defined(__IOM128_H) || defined(__IAR_SYSTEMS_ASM__)

#pragma language=extended

/*==========================*/
/* Predefined SFR Addresses */
/*==========================*/

/****************************************************************************
 * An example showing the SFR_B() macro call, 
 * the expanded result and usage of this result:
 *
 * SFR_B_R(0x1F,   AVR) Expands to:
 * __io union {
 *             unsigned char AVR;                 // The sfrb as 1 byte
 *             struct {                           // The sfrb as 8 bits
 *                     unsigned char AVR_Bit0:1,
 *                                   AVR_Bit1:1,
 *                                   AVR_Bit2:1,
 *                                   AVR_Bit3:1,
 *                                   AVR_Bit4:1,
 *                                   AVR_Bit5:1,
 *                                   AVR_Bit6:1,
 *                                   AVR_Bit7:1;
 *                    };
 *            } @ 0x1F;
 * Examples of how to use the expanded result:
 * AVR |= (1<<5);
 * or like this:
 * AVR_Bit5 = 1;
 *
 *
 *
 * An example showing the SFR_B_N() macro call, 
 * the expanded result and usage of this result:
 * SFR_B_N(0x25,  TCCR2, FOC2, WGM20, COM21, COM20, WGM21, CS22, CS21, CS20)
 *  Expands to:
 *  __io union { 
 *              unsigned char TCCR2; 
 *              struct { 
 *                      unsigned char TCCR2_Bit0:1, 
 *                                    TCCR2_Bit1:1, 
 *                                    TCCR2_Bit2:1, 
 *                                    TCCR2_Bit3:1, 
 *                                    TCCR2_Bit4:1, 
 *                                    TCCR2_Bit5:1, 
 *                                    TCCR2_Bit6:1, 
 *                                    TCCR2_Bit7:1; 
 *                     }; 
 *              struct { 
 *                      unsigned char TCCR2_CS20:1, 
 *                                    TCCR2_CS21:1, 
 *                                    TCCR2_CS22:1, 
 *                                    TCCR2_WGM21:1, 
 *                                    TCCR2_COM20:1, 
 *                                    TCCR2_COM21:1, 
 *                                    TCCR2_WGM20:1, 
 *                                    TCCR2_FOC2:1; 
 *                     }; 
 *             } @ 0x25;
 * Examples of how to use the expanded result:
 * TCCR2 |= (1<<5); 
 * or if ENABLE_BIT_DEFINITIONS is defined   
 * TCCR2 |= (1<<COM21);
 * or like this:
 * TCCR2_Bit5 = 1;
 * or like this:
 * TCCR2_COM21 = 1;
 ***************************************************************************/

SFR_B_N(0x00,   PINF, PINF7, PINF6, PINF5, PINF4, PINF3, PINF2, PINF1, PINF0)     /* Input Pins, Port F */
SFR_B_N(0x01,   PINE, PINE7, PINE6, PINE5, PINE4, PINE3, PINE2, PINE1, PINE0)     /* Input Pins, Port E */
SFR_B_N(0x02,   DDRE, DDE7,  DDE6,  DDE5,  DDE4,  DDE3,  DDE2,  DDE1,  DDE0)      /* Data Direction Register, Port E */
SFR_B_N(0x03,  PORTE, PORTE7, PORTE6, PORTE5, PORTE4, PORTE3, PORTE2, PORTE1, PORTE0) /* Data Register, Port E */
SFR_W_R(0x04,    ADC)     /* ADC Data register */
SFR_B2_N(0x06, ADCSR, ADCSRA, ADEN, ADSC, ADFR, ADIF, ADIE, ADPS2, ADPS1, ADPS0)  /* ADC Control and Status Register */
SFR_B_N(0x07,  ADMUX, REFS1, REFS0, ADLAR, MUX4, MUX3, MUX2, MUX1, MUX0)          /* ADC Multiplexer Selection Register */
SFR_B_N(0x08,   ACSR, ACD, ACBG, ACO, ACI, ACIE, ACIC, ACIS1, ACIS0)              /* Analog Comparator Control and Status Register */
SFR_B_R(0x09, UBRR0L)     /* USART0 Baud Rate Register Low*/
SFR_B_N(0x0A, UCSR0B, RXCIE0, TXCIE0, UDRIE0, RXEN0, TXEN0, UCSZ02, RXB80, TXB80) /* USART0 Control and Status Register B */
SFR_B_N(0x0B, UCSR0A, RXC0, TXC0, UDRE0, FE0, DOR0, UPE0, U2X0, MPCM0)            /* USART0 Control and Status Register A */
SFR_B_R(0x0C,   UDR0)     /* USART0 I/O Data Register */
SFR_B_N(0x0D,   SPCR, SPIE, SPE, DORD, MSTR, CPOL, CPHA, SPR1, SPR0)              /* SPI Control Register */
SFR_B_N(0x0E,   SPSR, SPIF, WCOL, Dummy5, Dummy4, Dummy3, Dummy2, Dummy1, SPI2X)  /* SPI Status Register */
SFR_B_R(0x0F,   SPDR)     /* SPI I/O Data Register */
SFR_B_N(0x10,   PIND, PIND7, PIND6, PIND5, PIND4, PIND3, PIND2, PIND1, PIND0)     /* Input Pins, Port D */
SFR_B_N(0x11,   DDRD, DDD7, DDD6, DDD5, DDD4, DDD3, DDD2, DDD1, DDD0)             /* Data Direction Register, Port D */
SFR_B_N(0x12,  PORTD, PORTD7, PORTD6, PORTD5, PORTD4, PORTD3, PORTD2, PORTD1, PORTD0) /* Data Register, Port D */
SFR_B_N(0x13,   PINC, PINC7, PINC6, PINC5, PINC4, PINC3, PINC2, PINC1, PINC0)     /* Input Pins, Port C */
SFR_B_N(0x14,   DDRC, DDC7, DDC6, DDC5, DDC4, DDC3, DDC2, DDC1, DDC0)             /* Data Direction Register, Port C */
SFR_B_N(0x15,  PORTC, PORTC7, PORTC6, PORTC5, PORTC4, PORTC3, PORTC2, PORTC1, PORTC0) /* Data Register, Port C */
SFR_B_N(0x16,   PINB, PINB0, PINB1, PINB2, PINB3, PINB4, PINB5, PINB6, PINB7)     /* Input Pins, Port B */
SFR_B_N(0x17,   DDRB, DDB7, DDB6, DDB5, DDB4, DDB3, DDB2, DDB1, DDB0)             /* Data Direction Register, Port B */
SFR_B_N(0x18,  PORTB, PORTB7, PORTB6, PORTB5, PORTB4, PORTB3, PORTB2, PORTB1, PORTB0) /* Data Register, Port B */
SFR_B_N(0x19,   PINA, PINA7, PINA6, PINA5, PINA4, PINA3, PINA2, PINA1, PINA0)     /* Input Pins, Port A */
SFR_B_N(0x1A,   DDRA, DDA7, DDA6, DDA5, DDA4, DDA3, DDA2, DDA1, DDA0)             /* Data Direction Register, Port A */
SFR_B_N(0x1B,  PORTA, PORTA7, PORTA6, PORTA5, PORTA4, PORTA3, PORTA2, PORTA1, PORTA0) /* Data Register, Port A */
SFR_B_N(0x1C,   EECR, Dummy7, Dummy6, Dummy5, Dummy4, EERIE, EEMWE, EEWE, EERE)   /* EEPROM Control Register */
SFR_B_R(0x1D,   EEDR)     /* EEPROM Data Register */
SFR_W_R(0x1E,   EEAR)     /* EEPROM Address Register */
SFR_B_N(0x20,  SFIOR, TSM, Dummy6, Dummy5, Dummy4, ACME, PUD, PSR0, PSR321)       /* Special Function I/O Register */
SFR_B_N(0x21,  WDTCR, Dummy7, Dummy6, Dummy5, WDCE, WDE, WDP2, WDP1, WDP0)        /* Watchdog Timer Control Register */
SFR_B_N(0x22,   OCDR, OCDR7, OCDR6, OCDR5, OCDR4, OCDR3, OCDR2, OCDR1, OCDR0)     /* On-Chip Debug Register */
SFR_B_R(0x23,   OCR2)     /* Timer/Counter 2 Output Compare Register */
SFR_B_R(0x24,  TCNT2)     /* Timer/Counter 2 */
SFR_B_N(0x25,  TCCR2, FOC2, WGM20, COM21, COM20, WGM21, CS22, CS21, CS20)         /* Timer/Counter 2 Control Register */
SFR_W_R(0x26,   ICR1)     /* Timer/Counter 1 Input Capture Register */
SFR_W_R(0x28,  OCR1B)     /* Timer/Counter 1 Output Compare Register B */
SFR_W_R(0x2A,  OCR1A)     /* Timer/Counter 1 Output Compare Register A */
SFR_W_R(0x2C,  TCNT1)     /* Timer/Counter 1 Register */
SFR_B_N(0x2E, TCCR1B, ICNC1, ICES1, Dummy5, WGM13, WGM12, CS12, CS11, CS10)       /* Timer/Counter 1 Control Register B */
SFR_B_N(0x2F, TCCR1A, COM1A1, COM1A0, COM1B1, COM1B0, COM1C1, COM1C0, WGM11, WGM10) /* Timer/Counter 1 Control Register A */
SFR_B_N(0x30,   ASSR, Dummy7, Dummy6, Dummy5, Dummy4, AS0, TCN0UB, OCR0UB, TCR0UB) /* Asynchronous mode Status Register */
SFR_B_R(0x31,   OCR0)     /* Timer/Counter 0 Output Compare Register */
SFR_B_R(0x32,  TCNT0)     /* Timer/Counter 0 */
SFR_B_N(0x33,  TCCR0, FOC0, WGM00, COM01, COM00, WGM01, CS02, CS01, CS00)         /* Timer/Counter 0 Control Register */
SFR_B_N(0x34, MCUCSR, JTD, Dummy6, Dummy5, JTRF, WDRF, BORF, EXTRF, PORF)         /* MCU general Control and Status Register */
SFR_B_N(0x35,  MCUCR, SRE, SRW10, SE, SM1, SM0, SM2, IVSEL, IVCE)                 /* MCU general Control Register */
SFR_B_N(0x36,   TIFR, OCF2, TOV2, ICF1, OCF1A, OCF1B, TOV1, OCF0, TOV0)           /* Timer/Counter Interrupt Flag Register */
SFR_B_N(0x37,  TIMSK, OCIE2, TOIE2, TICIE1, OCIE1A, OCIE1B, TOIE1, OCIE0, TOIE0)  /* Timer/Counter Interrupt Mask Register */
SFR_B_N(0x38,   EIFR, INTF7, INTF6, INTF5, INTF4, INTF3, INTF2, INTF1, INTF0)     /* External Interrupt Flag Register */
SFR_B_N(0x39,  EIMSK, INT7, INT6, INT5, INT4, INT3, INT2, INT1, INT0)             /* External Interrupt Mask Register */
SFR_B_N(0x3A,  EICRB, ISC71, ISC70, ISC61, ISC60, ISC51, ISC50, ISC41, ISC40)     /* External Interrupt Control Register B */
SFR_B_N(0x3B,  RAMPZ, Dummy7, Dummy6, Dummy5, Dummy4, Dummy3, Dummy2, Dummy1, RAMPZ0) /* RAM Page Z Select Register */
SFR_B_N(0x3C,   XDIV, XDIVEN, XDIV6, XDIV5, XDIV4, XDIV3, XDIV2, XDIV1, XDIV0)    /* XTAL Divide Control Register */
SFR_W_N(0x3D,     SP, SP15, SP14, SP13, SP12, SP11, SP10, SP9, SP8, SP7, SP6, SP5, SP4, SP3, SP2, SP1, SP0)     /* Stack Pointer */
SFR_B_N(0x3F,   SREG, I, T, H, S, V, N, Z, C)                                     /* Status Register */

/* Extended I/O space */
SFR_B_N(0x61,   DDRF, DDF7, DDF6, DDF5, DDF4, DDF3, DDF2, DDF1, DDF0)             /* Data Direction Register, Port F */
SFR_B_N(0x62,  PORTF, PORTF7, PORTF6, PORTF5, PORTF4, PORTF3, PORTF2, PORTF1, PORTF0) /* Data Register, Port F */
SFR_B_N(0x63,   PING, Dummy7, Dummy6, Dummy5, PING4, PING3, PING2, PING1, PING0)  /* Input Pins, Port G */
SFR_B_N(0x64,   DDRG, Dummy7, Dummy6, Dummy5, DDG4, DDG3, DDG2, DDG1, DDG0 )      /* Data Direction Register, Port G */
SFR_B_N(0x65,  PORTG, Dummy7, Dummy6, Dummy5, PORTG4, PORTG3, PORTG2, PORTG1, PORTG0) /* Data Register, Port G */
SFR_B_N(0x68, SPMCSR, SPMIE, RWWSB, Dummy5, RWWSRE, BLBSET, PGWRT, PGERS, SPMEN)  /* Store Program Memory Control and Status Register */
SFR_B_N(0x6A,  EICRA, ISC31, ISC30, ISC21, ISC20, ISC11, ISC10, ISC01, ISC00)     /* External Interrupt Control Register A */
SFR_B_N(0x6C,  XMCRB, XMBK, Dummy6, Dummy5, Dummy4, Dummy3, XMM2, XMM1, XMM0)     /* External Memory Control Register B */
SFR_B_N(0x6D,  XMCRA, Dummy7, SRL2, SRL1, SRL0, SRW01, SRW00, SRW11, Dummy0)      /* External Memory Control Register A */
SFR_B_R(0x6F, OSCCAL)     /* Oscillator Calibration Register */
SFR_B_R(0x70,   TWBR)     /* TWI Bit Rate Register */
SFR_B_N(0x71,   TWSR, TWS7, TWS6, TWS5, TWS4, TWS3, Dummy2, TWPS1, TWPS0)         /* TWI Status Register */
SFR_B_N(0x72,   TWAR, TWA6, TWA5, TWA4, TWA3, TWA2, TWA1, TWA0, TWGCE)            /* TWI Address Register */
SFR_B_R(0x73,   TWDR)     /* TWI Data Register */
SFR_B_N(0x74,   TWCR, TWINT, TWEA, TWSTA, TWSTO, TWWC, TWEN, Dummy1, TWIE)        /* TWI Control Register */
SFR_W_R(0x78,  OCR1C)     /* Timer/Counter 1 Output Compare Register C Low */
SFR_B_N(0x7A, TCCR1C, FOC1A, FOC1B, FOC1C, Dummy4, Dummy3, Dummy2, Dummy1, Dummy0)/* Timer/Counter 1 Control Register C */
SFR_B_N(0x7C,  ETIFR, Dummy7, Dummy6, ICF3, OCF3A, OCF3B, TOV3, OCF3C, OCF1C)     /* Extended Timer/Counter Interrupt Flag Register */
SFR_B_N(0x7D, ETIMSK, Dummy7, Dummy6, TICIE3, OCIE3A, OCIE3B, TOIE3, OCIE3C, OCIE1C) /* Extended Timer/Counter Interrupt Mask Register */
SFR_W_R(0x80,   ICR3)     /* Timer/Counter 3 Input Capture Register Low */
SFR_W_R(0x82,  OCR3C)     /* Timer/Counter 3 Output Compare Register C Low */
SFR_W_R(0x84,  OCR3B)     /* Timer/Counter 3 Output Compare Register B Low */
SFR_W_R(0x86,  OCR3A)     /* Timer/Counter 3 Output Compare Register A Low */
SFR_W_R(0x88, TCNT3)      /* Timer/Counter 3 Register Low */
SFR_B_N(0x8A, TCCR3B, ICNC3, ICES3, Dummy5, WGM33, WGM32, CS32, CS31, CS30)       /* Timer/Counter 3 Control Register B */
SFR_B_N(0x8B, TCCR3A, COM3A1, COM3A0, COM3B1, COM3B0, COM3C1, COM3C0, WGM31, WGM30) /* Timer/Counter 3 Control Register A */
SFR_B_N(0x8C, TCCR3C, FOC3A, FOC3B, FOC3C, Dummy4, Dummy3, Dummy2, Dummy1, Dummy0)/* Timer/Counter 3 Control Register C */

SFR_B_R(0x90, UBRR0H)     /* USART0 Baud Rate Register High*/

SFR_B_N(0x95, UCSR0C, Dummy7, UMSEL0, UPM01, UPM00, USBS0, UCSZ01, UCSZ00, UCPOL0)/* USART0 Control and Status Register C */
SFR_B_R(0x98, UBRR1H)     /* USART1 Baud Rate Register High */
SFR_B_R(0x99, UBRR1L)     /* USART1 Baud Rate Register Low */
SFR_B_N(0x9A, UCSR1B, RXCIE1, TXCIE1, UDRIE1, RXEN1, TXEN1, UCSZ12, RXB81, TXB81) /* USART1 Control and Status Register B */
SFR_B_N(0x9B, UCSR1A, RXC1, TXC1, UDRE1, FE1, DOR1, UPE1, U2X1, MPCM1)            /* USART1 Control and Status Register A */
SFR_B_R(0x9C,   UDR1)     /* USART1 I/O Data Register */
SFR_B_N(0x9D, UCSR1C, Dummy7, UMSEL1, UPM11, UPM10, USBS1, UCSZ11, UCSZ10, UCPOL1)/* USART1 Control and Status Register C */

#ifndef __IOM128_H
#define __IOM128_H


/* SFRs are local in assembler modules (so this file may need to be */
/* included in more than one module in the same source file), */
/* but #defines must only be made once per source file. */

/*==============================*/
/* Interrupt Vector Definitions */
/*==============================*/

/* NB! vectors are specified as byte addresses */

#define    RESET_vect           (0x00)
#define    INT0_vect            (0x04)
#define    INT1_vect            (0x08)
#define    INT2_vect            (0x0C)
#define    INT3_vect            (0x10)
#define    INT4_vect            (0x14)
#define    INT5_vect            (0x18)
#define    INT6_vect            (0x1C)
#define    INT7_vect            (0x20)
#define    TIMER2_COMP_vect     (0x24)
#define    TIMER2_OVF_vect      (0x28)
#define    TIMER1_CAPT_vect     (0x2C)
#define    TIMER1_COMPA_vect    (0x30)
#define    TIMER1_COMPB_vect    (0x34)
#define    TIMER1_OVF_vect      (0x38)
#define    TIMER0_COMP_vect     (0x3C)
#define    TIMER0_OVF_vect      (0x40)
#define    SPI_STC_vect         (0x44)
#define    USART0_RXC_vect      (0x48)
#define    USART0_UDRE_vect     (0x4C)
#define    USART0_TXC_vect      (0x50)
#define    ADC_vect             (0x54)
#define    EE_RDY_vect          (0x58)
#define    ANA_COMP_vect        (0x5C)
#define    TIMER1_COMPC_vect    (0x60)
#define    TIMER3_CAPT_vect     (0x64)
#define    TIMER3_COMPA_vect    (0x68)
#define    TIMER3_COMPB_vect    (0x6C)
#define    TIMER3_COMPC_vect    (0x70)
#define    TIMER3_OVF_vect      (0x74)
#define    USART1_RXC_vect      (0x78)
#define    USART1_UDRE_vect     (0x7C)
#define    USART1_TXC_vect      (0x80)
#define    TWI_vect             (0x84)
#define    SPM_RDY_vect         (0x88)

#ifdef __IAR_SYSTEMS_ASM__   
#ifndef ENABLE_BIT_DEFINITIONS
#define  ENABLE_BIT_DEFINITIONS
#endif /* ENABLE_BIT_DEFINITIONS */
#endif /* __IAR_SYSTEMS_ASM__ */

#ifdef ENABLE_BIT_DEFINITIONS


/* Bit definitions for use with the IAR Assembler   
   The Register Bit names are represented by their bit number (0-7).
*/

/* USART1 Control and Status Register C */
#define    UMSEL1   6
#define    UPM11    5
#define    UPM10    4
#define    USBS1    3
#define    UCSZ11   2
#define    UCSZ10   1
#define    UCPOL1   0

/* USART1 Control and Status Register A */
#define    RXC1     7
#define    TXC1     6
#define    UDRE1    5
#define    FE1      4
#define    DOR1     3
#define    UPE1     2
#define    U2X1     1
#define    MPCM1    0

/* USART1 Control and Status Register B */
#define    RXCIE1   7
#define    TXCIE1   6
#define    UDRIE1   5
#define    RXEN1    4
#define    TXEN1    3
#define    UCSZ12   2
#define    RXB81    1
#define    TXB81    0

/* USART0 Control and Status Register C */
#define    UMSEL0   6
#define    UPM01    5
#define    UPM00    4
#define    USBS0    3
#define    UCSZ01   2
#define    UCSZ00   1
#define    UCPOL0   0

/* USART0 Control and Status Register A */
#define    RXC0     7
#define    TXC0     6
#define    UDRE0    5
#define    FE0      4
#define    DOR0     3
#define    UPE0     2
#define    U2X0     1
#define    MPCM0    0

/* USART0 Control and Status Register B */
#define    RXCIE0   7
#define    TXCIE0   6
#define    UDRIE0   5
#define    RXEN0    4
#define    TXEN0    3
#define    UCSZ02   2
#define    RXB80    1
#define    TXB80    0

/* Timer/Counter 3 Control Register C */
#define    FOC3A    7
#define    FOC3B    6
#define    FOC3C    5

/* Timer/Counter 3 Control Register A */
#define    COM3A1   7
#define    COM3A0   6
#define    COM3B1   5
#define    COM3B0   4
#define    COM3C1   3
#define    COM3C0   2
#define    WGM31    1
#define    WGM30    0

/* Timer/Counter 3 Control Register B */
#define    ICNC3    7
#define    ICES3    6
#define    WGM33    4
#define    WGM32    3
#define    CS32     2
#define    CS31     1
#define    CS30     0

/* Extended Timer/Counter Interrupt Mask Register */
#define    TICIE3   5
#define    OCIE3A   4
#define    OCIE3B   3
#define    TOIE3    2
#define    OCIE3C   1
#define    OCIE1C   0

/* Extended Timer/Counter Interrupt Flag Register */
#define    ICF3     5
#define    OCF3A    4
#define    OCF3B    3
#define    TOV3     2
#define    OCF3C    1
#define    OCF1C    0

/* TWI Control Register */
#define    TWINT    7
#define    TWEA     6
#define    TWSTA    5
#define    TWSTO    4
#define    TWWC     3
#define    TWEN     2
#define    TWIE     0

/* TWI (slave) Address Register */
#define    TWA6     7
#define    TWA5     6
#define    TWA4     5
#define    TWA3     4
#define    TWA2     3
#define    TWA1     2
#define    TWA0     1
#define    TWGCE    0

/* TWI Status Register */
#define    TWS7     7
#define    TWS6     6
#define    TWS5     5
#define    TWS4     4
#define    TWS3     3
#define    TWPS1    1
#define    TWPS0    0

/* External Memory Control Register A */
#define    SRL2     6
#define    SRL1     5
#define    SRL0     4
#define    SRW01    3
#define    SRW00    2
#define    SRW11    1

/* External Memory Control Register B */
#define    XMBK     7 
#define    XMM2     2
#define    XMM1     1
#define    XMM0     0

/* External Interrupt Control Register A */
#define    ISC31    7
#define    ISC30    6
#define    ISC21    5
#define    ISC20    4
#define    ISC11    3
#define    ISC10    2
#define    ISC01    1
#define    ISC00    0

/* Store Program Memory Control and Status Register */
#define    SPMIE    7
#define    RWWSB    6
#define    RWWSRE   4
#define    BLBSET   3
#define    PGWRT    2
#define    PGERS    1
#define    SPMEN    0

/* Data Register, Port G */
#define    PG4      4
#define    PG3      3
#define    PG2      2
#define    PG1      1
#define    PG0      0

 /* Data Register, Port G */
#define    PORTG4   4
#define    PORTG3   3
#define    PORTG2   2
#define    PORTG1   1
#define    PORTG0   0

/* Data Direction Register, Port G */
#define    DDG4     4
#define    DDG3     3
#define    DDG2     2
#define    DDG1     1
#define    DDG0     0

/* Input Pins, Port G */
#define    PING4    4
#define    PING3    3
#define    PING2    2
#define    PING1    1
#define    PING0    0

/* Data Register, Port F */
#define    PF7      7
#define    PF6      6
#define    PF5      5
#define    PF4      4
#define    PF3      3
#define    PF2      2
#define    PF1      1
#define    PF0      0
 
/* Data Register, Port F */
#define    PORTF7   7
#define    PORTF6   6
#define    PORTF5   5
#define    PORTF4   4
#define    PORTF3   3
#define    PORTF2   2
#define    PORTF1   1
#define    PORTF0   0
 
/* Data Direction Register, Port F */
#define    DDF7     7
#define    DDF6     6
#define    DDF5     5
#define    DDF4     4
#define    DDF3     3
#define    DDF2     2
#define    DDF1     1
#define    DDF0     0
 
/* Input Pins, Port F */
#define    PINF7    7
#define    PINF6    6
#define    PINF5    5
#define    PINF4    4
#define    PINF3    3
#define    PINF2    2
#define    PINF1    1
#define    PINF0    0

/* Stack Pointer High */
#define    SP15     7
#define    SP14     6
#define    SP13     5
#define    SP12     4
#define    SP11     3
#define    SP10     2
#define    SP9      1
#define    SP8      0

/* Stack Pointer Low */
#define    SP7      7
#define    SP6      6
#define    SP5      5
#define    SP4      4
#define    SP3      3
#define    SP2      2
#define    SP1      1
#define    SP0      0

/* XTAL Divide Control Register */
#define    XDIVEN   7
#define    XDIV6    6
#define    XDIV5    5
#define    XDIV4    4
#define    XDIV3    3
#define    XDIV2    2
#define    XDIV1    1
#define    XDIV0    0

/* RAM Page Z Select Register */
#define    RAMPZ0   0

/* External Interrupt Control Register B */
#define    ISC71    7
#define    ISC70    6
#define    ISC61    5
#define    ISC60    4
#define    ISC51    3
#define    ISC50    2
#define    ISC41    1
#define    ISC40    0

/* External Interrupt Mask Register */
#define    INT7     7
#define    INT6     6
#define    INT5     5
#define    INT4     4
#define    INT3     3
#define    INT2     2
#define    INT1     1
#define    INT0     0

/* External Interrupt Flag Register */
#define    INTF7    7
#define    INTF6    6
#define    INTF5    5
#define    INTF4    4
#define    INTF3    3
#define    INTF2    2
#define    INTF1    1
#define    INTF0    0

/* Timer/Counter Interrupt Mask Register */
#define    OCIE2    7
#define    TOIE2    6
#define    TICIE1   5
#define    OCIE1A   4
#define    OCIE1B   3
#define    TOIE1    2
#define    OCIE0    1
#define    TOIE0    0

/* Timer/Counter Interrupt Flag Register */
#define    OCF2     7
#define    TOV2     6
#define    ICF1     5
#define    OCF1A    4
#define    OCF1B    3
#define    TOV1     2
#define    OCF0     1
#define    TOV0     0


/* MCU general Control Register */
#define    SRE      7
#define    SRW10    6
#define    SE       5
#define    SM1      4
#define    SM0      3
#define    SM2      2
#define    IVSEL    1
#define    IVCE     0

/* MCU general Control and Status Register */
#define    JTD      7
#define    JTRF     4
#define    WDRF     3
#define    BORF     2
#define    EXTRF    1
#define    PORF     0

/* Timer/Counter 0 Control Register */
#define    FOC0     7
#define    WGM00    6
#define    COM01    5
#define    COM00    4
#define    WGM01    3
#define    CS02     2
#define    CS01     1
#define    CS00     0

/* Asynchronous mode Status Register */
#define    AS0      3
#define    TCN0UB   2
#define    OCR0UB   1
#define    TCR0UB   0

/* Timer/Counter 1 Control Register C */
#define    FOC1A    7
#define    FOC1B    6
#define    FOC1C    5

/* Timer/Counter 1 Control Register A */
#define    COM1A1   7
#define    COM1A0   6
#define    COM1B1   5
#define    COM1B0   4
#define    COM1C1   3
#define    COM1C0   2
#define    WGM11    1
#define    WGM10    0

/* Timer/Counter 1 Control Register B */
#define    ICNC1    7
#define    ICES1    6
#define    WGM13    4
#define    WGM12    3
#define    CS12     2
#define    CS11     1
#define    CS10     0

/* Timer/Counter 2 Control Register */
#define    FOC2     7
#define    WGM20    6
#define    COM21    5
#define    COM20    4
#define    WGM21    3
#define    CS22     2
#define    CS21     1
#define    CS20     0

/* On-Chip Debug Register */
#define    IDRD     7
#define    OCDR7    7
#define    OCDR6    6
#define    OCDR5    5
#define    OCDR4    4
#define    OCDR3    3
#define    OCDR2    2
#define    OCDR1    1
#define    OCDR0    0

/* Watchdog Timer Control Register */
#define    WDCE     4
#define    WDE      3
#define    WDP2     2
#define    WDP1     1
#define    WDP0     0

/* Special Function I/O Register */
#define    TSM      7
#define    ADHSM    4
#define    ACME     3
#define    PUD      2
#define    PSR0     1
#define    PSR321   0

/* EEPROM Control Register */
#define    EERIE    3
#define    EEMWE    2
#define    EEWE     1
#define    EERE     0

/* Data Register, Port A */
#define    PA7      7
#define    PA6      6
#define    PA5      5
#define    PA4      4
#define    PA3      3
#define    PA2      2
#define    PA1      1
#define    PA0      0
 
/* Data Register, Port A */
#define    PORTA7   7
#define    PORTA6   6
#define    PORTA5   5
#define    PORTA4   4
#define    PORTA3   3
#define    PORTA2   2
#define    PORTA1   1
#define    PORTA0   0
 
/* Data Direction Register, Port A */
#define    DDA7     7
#define    DDA6     6
#define    DDA5     5
#define    DDA4     4
#define    DDA3     3
#define    DDA2     2
#define    DDA1     1
#define    DDA0     0
 
/* Input Pins, Port A */
#define    PINA7    7
#define    PINA6    6
#define    PINA5    5
#define    PINA4    4
#define    PINA3    3
#define    PINA2    2
#define    PINA1    1
#define    PINA0    0

/* Data Register, Port B */
#define    PB7      7
#define    PB6      6
#define    PB5      5
#define    PB4      4
#define    PB3      3
#define    PB2      2
#define    PB1      1
#define    PB0      0
 
/* Data Register, Port B */
#define    PORTB7   7
#define    PORTB6   6
#define    PORTB5   5
#define    PORTB4   4
#define    PORTB3   3
#define    PORTB2   2
#define    PORTB1   1
#define    PORTB0   0
 
/* Data Direction Register, Port B */
#define    DDB7     7
#define    DDB6     6
#define    DDB5     5
#define    DDB4     4
#define    DDB3     3
#define    DDB2     2
#define    DDB1     1
#define    DDB0     0
 
/* Input Pins, Port B */
#define    PINB7    7
#define    PINB6    6
#define    PINB5    5
#define    PINB4    4
#define    PINB3    3
#define    PINB2    2
#define    PINB1    1
#define    PINB0    0

/* Data Register, Port C */
#define    PC7      7
#define    PC6      6
#define    PC5      5
#define    PC4      4
#define    PC3      3
#define    PC2      2
#define    PC1      1
#define    PC0      0
 
/* Data Register, Port C */
#define    PORTC7   7
#define    PORTC6   6
#define    PORTC5   5
#define    PORTC4   4
#define    PORTC3   3
#define    PORTC2   2
#define    PORTC1   1
#define    PORTC0   0
 
/* Data Direction Register, Port C */
#define    DDC7     7
#define    DDC6     6
#define    DDC5     5
#define    DDC4     4
#define    DDC3     3
#define    DDC2     2
#define    DDC1     1
#define    DDC0     0
 
/* Input Pins, Port C */
#define    PINC7    7
#define    PINC6    6
#define    PINC5    5
#define    PINC4    4
#define    PINC3    3
#define    PINC2    2
#define    PINC1    1
#define    PINC0    0

/* Data Register, Port D */
#define    PD7      7
#define    PD6      6
#define    PD5      5
#define    PD4      4
#define    PD3      3
#define    PD2      2
#define    PD1      1
#define    PD0      0
 
/* Data Register, Port D */
#define    PORTD7   7
#define    PORTD6   6
#define    PORTD5   5
#define    PORTD4   4
#define    PORTD3   3
#define    PORTD2   2
#define    PORTD1   1
#define    PORTD0   0
 
/* Data Direction Register, Port D */
#define    DDD7     7
#define    DDD6     6
#define    DDD5     5
#define    DDD4     4
#define    DDD3     3
#define    DDD2     2
#define    DDD1     1
#define    DDD0     0
 
/* Input Pins, Port D */
#define    PIND7    7
#define    PIND6    6
#define    PIND5    5
#define    PIND4    4
#define    PIND3    3
#define    PIND2    2
#define    PIND1    1
#define    PIND0    0

/* SPI Status Register */
#define    SPIF     7
#define    WCOL     6
#define    SPI2X    0

/* SPI Control Register */
#define    SPIE     7
#define    SPE      6
#define    DORD     5
#define    MSTR     4
#define    CPOL     3
#define    CPHA     2
#define    SPR1     1
#define    SPR0     0

/* Analog Comparator Control and Status Register */
#define    ACD      7
#define    ACBG     6
#define    ACO      5
#define    ACI      4
#define    ACIE     3
#define    ACIC     2
#define    ACIS1    1
#define    ACIS0    0

/* ADC Multiplexer Selection Register */
#define    REFS1    7
#define    REFS0    6
#define    ADLAR    5
#define    MUX4     4
#define    MUX3     3
#define    MUX2     2
#define    MUX1     1
#define    MUX0     0

/* ADC Control and Status Register */
#define    ADEN     7
#define    ADSC     6
#define    ADFR     5
#define    ADIF     4
#define    ADIE     3
#define    ADPS2    2
#define    ADPS1    1
#define    ADPS0    0

/* Data Register, Port E */
#define    PE7      7
#define    PE6      6
#define    PE5      5
#define    PE4      4
#define    PE3      3
#define    PE2      2
#define    PE1      1
#define    PE0      0
 
/* Data Register, Port E */
#define    PORTE7   7
#define    PORTE6   6
#define    PORTE5   5
#define    PORTE4   4
#define    PORTE3   3
#define    PORTE2   2
#define    PORTE1   1
#define    PORTE0   0
 
/* Data Direction Register, Port E */
#define    DDE7     7
#define    DDE6     6
#define    DDE5     5
#define    DDE4     4
#define    DDE3     3
#define    DDE2     2
#define    DDE1     1
#define    DDE0     0
 
/* Input Pins, Port E */
#define    PINE7    7
#define    PINE6    6
#define    PINE5    5
#define    PINE4    4
#define    PINE3    3
#define    PINE2    2
#define    PINE1    1
#define    PINE0    0


/* Pointer definition */
#define    XL     r26
#define    XH     r27
#define    YL     r28
#define    YH     r29
#define    ZL     r30
#define    ZH     r31

/* Contants */
#define    RAMEND   0x10FF    /*Last On-Chip SRAM location*/
#define    XRAMEND  0xFFFF
#define    E2END    0x0FFF
#define    FLASHEND 0x1FFFF

#endif /* ENABLE_BIT_DEFINITIONS */ 
#endif /* __IOM128_H (define part) */
#endif /* __IOM128_H (SFR part) */
