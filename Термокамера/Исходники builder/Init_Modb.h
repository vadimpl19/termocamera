//---------------------------------------------------------------------------

#ifndef Init_ModbH
#define Init_ModbH
//---------------------------------------------------------------------------
bool LoadModb();
extern int _stdcall (*init_comm  )(char *port_name,UINT baud_rate,UCHAR parity);
/*port_name - ��� ����� (COM1,COM2,�)
baud_rate - �������� �������� ������ (9600,1200,�)
parity - ��������
0 - No parity
1 - Odd
2 - Even
 ���������� FR_SUCCESS � ������ ������, ���� ��� ������
*/
extern int _stdcall (*invoke_modb)(UCHAR slave_adress, UCHAR func,
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
extern int _stdcall (*EnumParameters)(char *port_name, WORD type,
        WORD sernum, BYTE address, UINT* baud, BYTE* parity);
extern DWORD  _stdcall (*Send_And_Receive)(DWORD num_send,void* data);
extern void  _stdcall (*SetTout)(DWORD msec);
#endif
