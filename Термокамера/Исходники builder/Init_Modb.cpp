//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Init_Modb.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
int _stdcall (*init_comm  )(char *port_name,UINT baud_rate,UCHAR parity);
/*port_name - ��� ����� (COM1,COM2,�)
baud_rate - �������� �������� ������ (9600,1200,�)
parity - ��������
0 - No parity
1 - Odd
2 - Even
 ���������� FR_SUCCESS � ������ ������, ���� ��� ������
*/
int _stdcall (*invoke_modb)(UCHAR slave_adress, UCHAR func,
 USHORT start_address, USHORT points, void *data);
/*slave_address - ����� ������� modbus-slave
func - ��� ������� modbus
start_address - ��������� �����
points - ���������� ��������� ������
data - � ����������� �� ���� �������
	������� ������ - �������� points ��������� ������, ��������������� ��� ������
	������� ������  - ����������� ������ ��� ������������� ������
���������� FR_SUCCESS � ������ ������, ���� ��� ���������� modbus. � ������ ������������� ���������� ������ data �� ����������� �������. ������� ���������� �������� � �������� ����� ����������
*/
int _stdcall (*EnumParameters)(char *port_name, WORD type,WORD sernum,
  BYTE address, UINT* baud, BYTE* parity);

DWORD  _stdcall (*Send_And_Receive)(DWORD num_send,void* data);
void  _stdcall (*SetTout)(DWORD msec);

bool LoadModb()
{
HANDLE hLib;
hLib=LoadLibrary("comm_mb.dll");
if(!hLib)
 {
  MessageBox(0,"�� ������� comm_mb.dll!","������!",MB_OK|MB_ICONERROR);
  return false;
 }
 init_comm=(int _stdcall (* )(char *,UINT ,UCHAR ))GetProcAddress(hLib,"init_comm");
 if(!init_comm)
 {
  MessageBox(0,"comm_mb.dll �� �������� ������� init_comm!","������!",MB_OK|MB_ICONERROR);
  return false;
 }
 invoke_modb=(int _stdcall (*)(UCHAR, UCHAR, USHORT , USHORT , void *))GetProcAddress(hLib,"invoke_modb");
 if(!invoke_modb)
 {
  MessageBox(0,"comm_mb.dll �� �������� ������� invoke_modb!","������!",MB_OK|MB_ICONERROR);
  return false;
 }
 EnumParameters=(int _stdcall (*)(char*, WORD, WORD , BYTE , UINT *,BYTE*))GetProcAddress(hLib,"EnumParameters");
 if(!EnumParameters)
 {
  MessageBox(0,"comm_mb.dll �� �������� ������� EnumParameters!","������!",MB_OK|MB_ICONERROR);
  return false;
 }

Send_And_Receive=(DWORD _stdcall (*)(DWORD ,void*))GetProcAddress(hLib,"Send_And_Receive");
 if(!EnumParameters)
 {
  MessageBox(0,"comm_mb.dll �� �������� ������� Send_And_Receive!","������!",MB_OK|MB_ICONERROR);
  return false;
 }
SetTout=(void _stdcall (*)(DWORD))GetProcAddress(hLib,"SetTout");
 if(!EnumParameters)
 {
  MessageBox(0,"comm_mb.dll �� �������� ������� SetTout!","������!",MB_OK|MB_ICONERROR);
  return false;
 }
return true;
}



