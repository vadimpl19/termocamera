//---------------------------------------------------------------------------

#ifndef funcH
#define funcH
enum tagGnd{bin,dec,_dec,hex};
bool LoadModb();
bool IniPort(const AnsiString& port,UINT baud,UCHAR parity);
void WriteReg(USHORT adr, USHORT value);
void ReadReg(USHORT adr, USHORT& value);
void WriteRegs(USHORT adr, USHORT num,void* data);
void ReadRegs(USHORT adr,USHORT num ,void* data);
void WriteSafeRegs(USHORT adr, USHORT num,void* data);
void WriteSafeReg(USHORT adr,USHORT data);
char* WordToStr(USHORT val,tagGnd gnd);
char* FloatToStr(float val,USHORT ndig);
WORD StrToWord(AnsiString& str,tagGnd gnd);
void SendData(HANDLE hwnd,void* data, DWORD count);

class ECommError:public Exception
{
public:
ECommError():Exception("Нет связи!"){};
ECommError(int);
};

class ECalibError:public Exception
{
public:
ECalibError(int);
};

extern UCHAR slave;
extern AnsiString port;
extern UINT baud;
extern UCHAR parity;
extern AnsiString alpha;

const
 USHORT
// num=0x0,
// manuf=0x1,
// adr=0x101,
// speed=0x102,
// parity_stopbits=0x103,
 count_res=0x104,
// type=0x300,
// ver=0x301,
 TMD101=6,
 TMD101MK=12,
 timeTU1=0x108,
 timeTU2=0x109,
 timeTU3=0x10A,
 timeTU4=0x10B,
 timeTU5=0x10C,
 timeTU6=0x10D,
 timeTU7=0x10E,
 timeTU8=0x10F,
 status=0x400,
 statTU=0x401,
 statOut=0x402,
 TU1=0x403,
 TU2=0x404,
 TU3=0x405,
 TU4=0x406,
 TU5=0x407,
 TU6=0x408,
 TU7=0x409,
 TU8=0x40A,
 
 setTU=0x5555,
 clearTU=0xAAAA,
 res=0x777,
 key=0xAAAA
 ;


//---------------------------------------------------------------------------
#endif
