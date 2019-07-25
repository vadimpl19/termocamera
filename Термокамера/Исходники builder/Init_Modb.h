//---------------------------------------------------------------------------

#ifndef Init_ModbH
#define Init_ModbH
//---------------------------------------------------------------------------
bool LoadModb();
extern int _stdcall (*init_comm  )(char *port_name,UINT baud_rate,UCHAR parity);
/*port_name - имя порта (COM1,COM2,…)
baud_rate - скорость передачи данных (9600,1200,…)
parity - четность
0 - No parity
1 - Odd
2 - Even
 Возвращает FR_SUCCESS в случае успеха, либо код ошибки
*/
extern int _stdcall (*invoke_modb)(UCHAR slave_adress, UCHAR func,
 USHORT start_address, USHORT points, void *data);
/*slave_address - адрес станции modbus-slave
func - код функции modbus
start_address - начальный адрес
points - количество элементов данных
data - в зависимости от кода функции
	функции записи - содержит points элементов данных, предназначенных для записи
	функции чтения  - резервирует память для запрашиваемых данных
Возвращает FR_SUCCESS в случае успеха, либо код исключения modbus. В случае возникновения исключения буффер data не заполняется данными. Порядок следования младшего и старшего байта нормальный
*/
extern int _stdcall (*EnumParameters)(char *port_name, WORD type,
        WORD sernum, BYTE address, UINT* baud, BYTE* parity);
extern DWORD  _stdcall (*Send_And_Receive)(DWORD num_send,void* data);
extern void  _stdcall (*SetTout)(DWORD msec);
#endif
