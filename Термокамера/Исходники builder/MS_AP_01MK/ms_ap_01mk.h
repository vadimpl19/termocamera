/* ms_ap_01mk.h - ������ ����������, �������� � ������� ��� ������ � ��-��-01�� */
#include <vcl.h>
//--- SIZE �������� � WORD
#define MSAP_01MK_QRYRETRY_SIZE 0x01
#define MSAP_01MK_CFG_SIZE 0x03FF-0x017F+1
#define MSAP_01MK_ALARM_SIZE 0x16F-0x160+1
#define MSAP_01MK_STATLINE_SIZE 0x109F-0x1010+1
#define TMAXDEF 80
#define DELTATDEF 3
#define MBREGCNT 64
#define MBWRITEREGCNT 8
/*�������� ��������� � ����������*/
struct DATA_INFO
{
  WORD wdStartPhAddr;
  WORD wdItemCount;
  WORD *pwdDataItem;
};
