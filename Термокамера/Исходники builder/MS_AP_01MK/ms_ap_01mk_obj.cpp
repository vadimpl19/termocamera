#pragma hdrstop
#include "ms_ap_01mk_obj.h"
#include "main.h"
#include "frmModuleParam.h"

TAp01mkObj::TAp01mkObj(TForm1 *a_pfrnIn)
{
  pfrmMainForm = a_pfrnIn;
  bAp01mkMode = false;

  stQryRetryData.wdStartPhAddr = 0x104;
  stQryRetryData.wdItemCount = MSAP_01MK_QRYRETRY_SIZE;
  stQryRetryData.pwdDataItem = new WORD[stQryRetryData.wdItemCount+1];
  InitDataInfo(stQryRetryData.pwdDataItem, stQryRetryData.wdItemCount);

  stLineCfgData.wdStartPhAddr = 0x017f;
  stLineCfgData.wdItemCount = MSAP_01MK_CFG_SIZE;
  stLineCfgData.pwdDataItem = new WORD[stLineCfgData.wdItemCount+1];
  InitDataInfo(stLineCfgData.pwdDataItem, stLineCfgData.wdItemCount);

  stAlarmData.wdStartPhAddr = 0x160;
  stAlarmData.wdItemCount = MSAP_01MK_ALARM_SIZE;
  stAlarmData.pwdDataItem = new WORD[stAlarmData.wdItemCount];
  InitDataInfo(stAlarmData.pwdDataItem, stAlarmData.wdItemCount);

  stLineStatData.wdStartPhAddr = 0x1010;
  stLineStatData.wdItemCount = MSAP_01MK_STATLINE_SIZE;
  stLineStatData.pwdDataItem = new WORD[stLineStatData.wdItemCount];
  InitDataInfo(stLineStatData.pwdDataItem, stLineStatData.wdItemCount);

  bCfgChanged = false;
  bMicrolanMode = false;
  bGetStatMode = false;
  bIsCfg = false;

}

bool TAp01mkObj::InitToEmptyCfg()
{
  //--- Устанавливаем адрес в FF
  int iCount;
  WORD wdAddr, wdVal;
  wdAddr = 0x180;   iCount = 0x37F-0x180+1;
  for (int i=0; i< iCount; i++)
  {
    if(!SetWordDataInfo(etdiLineCfg, wdAddr+i,0xFFFF))
      return false;
  }
  if (!TwoByte2Word(TMAXDEF,DELTATDEF, &wdVal))
    return false;
   wdAddr = 0x380;   iCount = 0x3FF-0x380+1;

  for (int i=0; i< iCount; i++)
  {
    if(!SetWordDataInfo(etdiLineCfg, wdAddr+i,wdVal))
    {
      AnsiString astWrk;
      astWrk.printf("Ошибка, обращения к адресу 0х %0X", wdAddr+i);
      ShowMessage(astWrk);
      return false;

    }
  }
  InitTPSArrays(0);
  return true;
}
void TAp01mkObj::SetModParamForm(TfrmModuleParamForm *a_pfrmIn)
{
  pfrmModParam = a_pfrmIn;
}
TAp01mkObj::~TAp01mkObj()
{
  delete[] stQryRetryData.pwdDataItem;
  delete[] stLineCfgData.pwdDataItem;
  delete[] stAlarmData.pwdDataItem;
  delete[] stLineStatData.pwdDataItem;
}

void TAp01mkObj::SetWrkMode(bool a_bMode)
{
  bAp01mkMode = a_bMode;
  //--- Set form caption
  if (bAp01mkMode)
  {
    pfrmMainForm->Caption = "Выбор режима";
  }
  else
  {
    pfrmMainForm->Caption = "Выбор режима";
  }


  
}

void TAp01mkObj::SwitchWrkMode(void)
{
  SetWrkMode(!bAp01mkMode);
}
bool TAp01mkObj::GetWrkMode(void)
{
  return bAp01mkMode;
}

bool TAp01mkObj::SaveCfgToFile(AnsiString a_astFileName)
{
  FILE *fWrk;
  if ( (fWrk=fopen(a_astFileName.c_str(),"wb"))== NULL)
  { //--- Ошибка открытия файла
    return false;
  }
  //--- Записываем в файл конфигурацию. size_t
  if (fwrite((unsigned char *)stQryRetryData.pwdDataItem, 2, stQryRetryData.wdItemCount, fWrk) != (size_t)stQryRetryData.wdItemCount)
  { //--- Ошибка сохранения в файл.
    return false;
  }

  if (fwrite((unsigned char *)stLineCfgData.pwdDataItem, 2, stLineCfgData.wdItemCount, fWrk) != (size_t)stLineCfgData.wdItemCount)
  { //--- Ошибка сохранения в файл.
    return false;
  }
  fclose (fWrk);
  return true;
}

bool TAp01mkObj::LoadCfgFromFile(AnsiString a_astFileName)
{
  FILE *fWrk;
  int iRes;
  if ( (fWrk=fopen(a_astFileName.c_str(),"rb"))== NULL)
  { //--- Ошибка открытия файла
    return false;
  }
  //--- Читаем конфигурацию из файла.
  iRes = fread((unsigned char *)stQryRetryData.pwdDataItem, 2, stQryRetryData.wdItemCount, fWrk);
  if ((size_t)iRes != (size_t)(stQryRetryData.wdItemCount))
  { //--- Ошибка чтения из файла.
    return false;
  }

  if (fread((unsigned char *)stLineCfgData.pwdDataItem, 2, stLineCfgData.wdItemCount, fWrk) != (size_t)(stLineCfgData.wdItemCount))
  { //--- Ошибка чтения из файла.
    return false;
  }
  fclose (fWrk);
  return true;
}

void TAp01mkObj::InitDataInfo(WORD *pa_Data, WORD a_Len)
{
  memset(pa_Data, 0, a_Len*2);
}

bool TAp01mkObj::SetWordDataInfo(enTypeDataInfo a_type, WORD a_Addr, WORD a_wdData)
{
  struct DATA_INFO *pWrk;
  int iIdx;
  switch(a_type)
  {
    case etdiQryRetry:
    {
      pWrk = &stQryRetryData;
      break;
    }
    case etdiLineCfg:
    {
      pWrk = &stLineCfgData;
      break;
    }
    case etdiAlarm:
    {
      pWrk = &stAlarmData;
      break;
    }
    case etdiLineStat:
    {
      pWrk = &stLineStatData;
      break;
    }
    default:
    {
      return false;
    }
  }
  //--- проверка
  iIdx = a_Addr - pWrk->wdStartPhAddr;
  if (iIdx < 0 || iIdx >=pWrk->wdItemCount)
    return false;
  //--- Присваиваем значение
  pWrk->pwdDataItem[iIdx] = a_wdData;
  return true;
}

bool TAp01mkObj::GetWordDataInfo(enTypeDataInfo a_type, WORD a_Addr, WORD *ap_wdData)
{
  struct DATA_INFO *pWrk;
  int iIdx;
  switch(a_type)
  {
    case etdiQryRetry:
    {
      pWrk = &stQryRetryData;
      break;
    }
    case etdiLineCfg:
    {
      pWrk = &stLineCfgData;
      break;
    }

    case etdiAlarm:
    {
      pWrk = &stAlarmData;
      break;
    }
    case etdiLineStat:
    {
      pWrk = &stLineStatData;
      break;
    }
    default:
    {
      return false;
    }
  }
  //--- проверка
  iIdx = a_Addr - pWrk->wdStartPhAddr;
  if (iIdx < 0 || iIdx >=pWrk->wdItemCount)
    return false;
  //--- Возвращаем значение
   *ap_wdData = pWrk->pwdDataItem[iIdx];
   return true;
}

bool TAp01mkObj::SetByteDataInfo(enTypeDataInfo a_type, WORD a_Addr, BYTE a_btData, int a_idx)
{
  struct DATA_INFO *pWrk;
  int iIdx;
  union
  {
    WORD wdData;
    struct
    {
     BYTE byte00:8;
     BYTE byte01:8;
    };
  }uw2cWrk;

  switch(a_type)
  {
    case etdiQryRetry:
    {
      pWrk = &stQryRetryData;
      break;
    }
    case etdiLineCfg:
    {
      pWrk = &stLineCfgData;
      break;
    }
    case etdiAlarm:
    {
      pWrk = &stAlarmData;
      break;
    }
    case etdiLineStat:
    {
      pWrk = &stLineStatData;
      break;
    }
    default:
    {
      return false;
    }
  }
  //--- проверка
  iIdx = a_Addr - pWrk->wdStartPhAddr;
  if (iIdx < 0 || iIdx >=pWrk->wdItemCount)
    return false;
  //--- Присваиваем значение
  uw2cWrk.wdData = pWrk->pwdDataItem[iIdx];
  if (a_idx == 0)
    uw2cWrk.byte00 = a_btData;
  else
    uw2cWrk.byte01 = a_btData;

  pWrk->pwdDataItem[iIdx] = uw2cWrk.wdData;

  return true;
}

bool TAp01mkObj::GetByteDataInfo(enTypeDataInfo a_type, WORD a_Addr, BYTE *ap_btData, int a_idx)
{
  struct DATA_INFO *pWrk;
  int iIdx;
  union
  {
    WORD wdData;
    struct
    {
     BYTE byte00:8;
     BYTE byte01:8;
    };
  }uw2cWrk;

  switch(a_type)
  {
    case etdiQryRetry:
    {
      pWrk = &stQryRetryData;
      break;
    }
    case etdiLineCfg:
    {
      pWrk = &stLineCfgData;
      break;
    }
    case etdiAlarm:
    {
      pWrk = &stAlarmData;
      break;
    }
    case etdiLineStat:
    {
      pWrk = &stLineStatData;
      break;
    }
    default:
    {
      return false;
    }
  }
  //--- проверка
  iIdx = a_Addr - pWrk->wdStartPhAddr;
  if (iIdx < 0 || iIdx >=pWrk->wdItemCount)
    return false;
  //--- Присваиваем значение

  uw2cWrk.wdData = pWrk->pwdDataItem[iIdx];
  if (a_idx == 0)
    *ap_btData = uw2cWrk.byte00;
  else
    *ap_btData = uw2cWrk.byte01;

  return true;
}

bool TAp01mkObj::SetBitDataInfo(enTypeDataInfo a_type, WORD a_Addr, BYTE a_btData, int a_idx)
{
  struct DATA_INFO *pWrk;
  int iIdx;
  union
  {
    WORD wdData;
    struct
    {
     BYTE bit00:1;
     BYTE bit01:1;
     BYTE bit02:1;
     BYTE bit03:1;
     BYTE bit04:1;
     BYTE bit05:1;
     BYTE bit06:1;
     BYTE bit07:1;
     BYTE bit08:1;
     BYTE bit09:1;
     BYTE bit10:1;
     BYTE bit11:1;
     BYTE bit12:1;
     BYTE bit13:1;
     BYTE bit14:1;
     BYTE bit15:1;
     BYTE bit16:1;
     BYTE bit17:1;
     BYTE bit18:1;
     BYTE bit19:1;
     BYTE bit20:1;
     BYTE bit21:1;
     BYTE bit22:1;
     BYTE bit23:1;
     BYTE bit24:1;
     BYTE bit25:1;
     BYTE bit26:1;
     BYTE bit27:1;
     BYTE bit28:1;
     BYTE bit29:1;
     BYTE bit30:1;
     BYTE bit31:1;
    };
  }uw2btWrk;

  switch(a_type)
  {
    case etdiQryRetry:
    {
      pWrk = &stQryRetryData;
      break;
    }
    case etdiLineCfg:
    {
      pWrk = &stLineCfgData;
      break;
    }
    case etdiAlarm:
    {
      pWrk = &stAlarmData;
      break;
    }
    case etdiLineStat:
    {
      pWrk = &stLineStatData;
      break;
    }
    default:
    {
      return false;
    }
  }
  //--- проверка
  iIdx = a_Addr - pWrk->wdStartPhAddr;
  if (iIdx < 0 || iIdx >=pWrk->wdItemCount)
    return false;
  //--- Присваиваем значение
  uw2btWrk.wdData = pWrk->pwdDataItem[iIdx];
  switch(a_idx)
  {
    case 0: uw2btWrk.bit00 = a_btData; break;
    case 1: uw2btWrk.bit01 = a_btData; break;
    case 2: uw2btWrk.bit02 = a_btData; break;
    case 3: uw2btWrk.bit03 = a_btData; break;
    case 4: uw2btWrk.bit04 = a_btData; break;
    case 5: uw2btWrk.bit05 = a_btData; break;
    case 6: uw2btWrk.bit06 = a_btData; break;
    case 7: uw2btWrk.bit07 = a_btData; break;
    case 8: uw2btWrk.bit08 = a_btData; break;
    case 9: uw2btWrk.bit09 = a_btData; break;
    case 10: uw2btWrk.bit10 = a_btData; break;
    case 11: uw2btWrk.bit11 = a_btData; break;
    case 12: uw2btWrk.bit12 = a_btData; break;
    case 13: uw2btWrk.bit13 = a_btData; break;
    case 14: uw2btWrk.bit14 = a_btData; break;
    case 15: uw2btWrk.bit15 = a_btData; break;
    case 16: uw2btWrk.bit16 = a_btData; break;
    case 17: uw2btWrk.bit17 = a_btData; break;
    case 18: uw2btWrk.bit18 = a_btData; break;
    case 19: uw2btWrk.bit19 = a_btData; break;
    case 20: uw2btWrk.bit20 = a_btData; break;
    case 21: uw2btWrk.bit21 = a_btData; break;
    case 22: uw2btWrk.bit22 = a_btData; break;
    case 23: uw2btWrk.bit23 = a_btData; break;
    case 24: uw2btWrk.bit24 = a_btData; break;
    case 25: uw2btWrk.bit25 = a_btData; break;
    case 26: uw2btWrk.bit26 = a_btData; break;
    case 27: uw2btWrk.bit27 = a_btData; break;
    case 28: uw2btWrk.bit28 = a_btData; break;
    case 29: uw2btWrk.bit29 = a_btData; break;
    case 30: uw2btWrk.bit30 = a_btData; break;
    case 31: uw2btWrk.bit31 = a_btData; break;
    default: return false;

  };

  pWrk->pwdDataItem[iIdx] = uw2btWrk.wdData;

  return true;
}

bool TAp01mkObj::GetBitDataInfo(enTypeDataInfo a_type, WORD a_Addr, BYTE *ap_btData, int a_idx)
{
  struct DATA_INFO *pWrk;
  int iIdx;
  union
  {
    WORD wdData;
    struct
    {
     BYTE bit00:1;
     BYTE bit01:1;
     BYTE bit02:1;
     BYTE bit03:1;
     BYTE bit04:1;
     BYTE bit05:1;
     BYTE bit06:1;
     BYTE bit07:1;
     BYTE bit08:1;
     BYTE bit09:1;
     BYTE bit10:1;
     BYTE bit11:1;
     BYTE bit12:1;
     BYTE bit13:1;
     BYTE bit14:1;
     BYTE bit15:1;
     BYTE bit16:1;
     BYTE bit17:1;
     BYTE bit18:1;
     BYTE bit19:1;
     BYTE bit20:1;
     BYTE bit21:1;
     BYTE bit22:1;
     BYTE bit23:1;
     BYTE bit24:1;
     BYTE bit25:1;
     BYTE bit26:1;
     BYTE bit27:1;
     BYTE bit28:1;
     BYTE bit29:1;
     BYTE bit30:1;
     BYTE bit31:1;
    };
  }uw2btWrk;

  switch(a_type)
  {
    case etdiQryRetry:
    {
      pWrk = &stQryRetryData;
      break;
    }
    case etdiLineCfg:
    {
      pWrk = &stLineCfgData;
      break;
    }
    case etdiAlarm:
    {
      pWrk = &stAlarmData;
      break;
    }
    case etdiLineStat:
    {
      pWrk = &stLineStatData;
      break;
    }
    default:
    {
      return false;
    }
  }
  //--- проверка
  iIdx = a_Addr - pWrk->wdStartPhAddr;
  if (iIdx < 0 || iIdx >=pWrk->wdItemCount)
    return false;
  //--- Присваиваем значение
  uw2btWrk.wdData = pWrk->pwdDataItem[iIdx];
  switch(a_idx)
  {
    case 0: *ap_btData = uw2btWrk.bit00; break;
    case 1: *ap_btData = uw2btWrk.bit01; break;
    case 2: *ap_btData = uw2btWrk.bit02; break;
    case 3: *ap_btData = uw2btWrk.bit03; break;
    case 4: *ap_btData = uw2btWrk.bit04; break;
    case 5: *ap_btData = uw2btWrk.bit05; break;
    case 6: *ap_btData = uw2btWrk.bit06; break;
    case 7: *ap_btData = uw2btWrk.bit07; break;
    case 8: *ap_btData = uw2btWrk.bit08; break;
    case 9: *ap_btData = uw2btWrk.bit09; break;
    case 10: *ap_btData = uw2btWrk.bit10; break;
    case 11: *ap_btData = uw2btWrk.bit11; break;
    case 12: *ap_btData = uw2btWrk.bit12; break;
    case 13: *ap_btData = uw2btWrk.bit13; break;
    case 14: *ap_btData = uw2btWrk.bit14; break;
    case 15: *ap_btData = uw2btWrk.bit15; break;
    case 16: *ap_btData = uw2btWrk.bit16; break;
    case 17: *ap_btData = uw2btWrk.bit17; break;
    case 18: *ap_btData = uw2btWrk.bit18; break;
    case 19: *ap_btData = uw2btWrk.bit19; break;
    case 20: *ap_btData = uw2btWrk.bit20; break;
    case 21: *ap_btData = uw2btWrk.bit21; break;
    case 22: *ap_btData = uw2btWrk.bit22; break;
    case 23: *ap_btData = uw2btWrk.bit23; break;
    case 24: *ap_btData = uw2btWrk.bit24; break;
    case 25: *ap_btData = uw2btWrk.bit25; break;
    case 26: *ap_btData = uw2btWrk.bit26; break;
    case 27: *ap_btData = uw2btWrk.bit27; break;
    case 28: *ap_btData = uw2btWrk.bit28; break;
    case 29: *ap_btData = uw2btWrk.bit29; break;
    case 30: *ap_btData = uw2btWrk.bit30; break;
    case 31: *ap_btData = uw2btWrk.bit31; break;
    default: return false;
  };
  return true;
}


bool TAp01mkObj::Word2TwoByte(WORD a_wdIn, BYTE *ap_btRes1, BYTE *ap_btRes2)
{
  struct DATA_INFO *pWrk;
  int iIdx;
  union
  {
    WORD wdData;
    struct
    {
     BYTE byte00:8;
     BYTE byte01:8;
    };
  }uw2cWrk;

  uw2cWrk.wdData = a_wdIn;

  *ap_btRes1 = uw2cWrk.byte00;
  *ap_btRes2 = uw2cWrk.byte01;

  return true;
}

bool TAp01mkObj::TwoByte2Word(BYTE a_btRes1, BYTE a_btRes2, WORD *ap_wdRes)
{
  struct DATA_INFO *pWrk;
  int iIdx;
  AnsiString astError;
  union
  {
    WORD wdData;
    struct
    {
     BYTE byte00:8;
     BYTE byte01:8;
    };
  }uw2cWrk;

  uw2cWrk.byte00 = a_btRes1;
  uw2cWrk.byte01 = a_btRes2;
//  astError.printf("Byte00: 0x%X Byte01: 0x%X Word: 0x%X", uw2cWrk.byte00, uw2cWrk.byte01, uw2cWrk.wdData);
//      Application->MessageBox(astError.c_str(), NULL, MB_OK);
  *ap_wdRes = uw2cWrk.wdData;

  return true;
}

bool TAp01mkObj::ReadCfgFromModule()
{
  int i;
  int iCount,iPart;
  //--- Читаем конфигурацию из модуля.
  int iWrRA, iCountRA;
  AnsiString astCaption;
  iWrRA = 1; iCountRA = stQryRetryData.wdItemCount + stLineCfgData.wdItemCount;

  #ifdef DEBUG_WRITE_LOG
    astLog.printf(" Start stQryRetryData");
    WriteLog("ReadCfgFromModule",astLog);
  #endif

  for(i=0; i<stQryRetryData.wdItemCount; i++)
  {
    astCaption.printf(" MB_RA: %d / %d ", iWrRA, iCountRA);
    //pfrmModParam->pnlStatModRA->Caption = astCaption;
    Application->ProcessMessages();

    if(!MBReadReg(stQryRetryData.wdStartPhAddr+i, stQryRetryData.pwdDataItem[i]))
    {
      #ifdef DEBUG_WRITE_LOG
        astLog.printf(" Error stQryRetryData i: %d",i);
        WriteLog("ReadCfgFromModule",astLog);
      #endif
      return false;
     }
    iWrRA++;
    //if (pfrmModParam->cbMBSleep->Checked)
    //  Sleep(300);
  }
  #ifdef DEBUG_WRITE_LOG
    astLog.printf(" stLineCfgData");
    WriteLog("ReadCfgFromModule",astLog);
  #endif
  iCount = stLineCfgData.wdItemCount;
  if (stLineCfgData.wdItemCount > MBREGCNT)
  {
    iPart = MBREGCNT;
  }
  else
  {
    iPart=stLineCfgData.wdItemCount;
  }
  i=0;
  while (iCount > 0)
  {
    astCaption.printf(" MB_RA: %d / %d ", iWrRA, iCountRA);
   // pfrmModParam->pnlStatModRA->Caption = astCaption;
    Application->ProcessMessages();

    if(!MBReadNReg(stLineCfgData.wdStartPhAddr+i, stLineCfgData.pwdDataItem[i],iPart))
    {
      #ifdef DEBUG_WRITE_LOG
        astLog.printf(" Error stLineCfgData i: %d",i);
        WriteLog("ReadCfgFromModule",astLog);
      #endif
      return false;
    }
    iWrRA+=iPart;
    i+=iPart;
    iCount -=iPart;

   // if (pfrmModParam->cbMBSleep->Checked)
    //  Sleep(300);
    if (iCount < iPart)
      iPart = iCount;
  }
  /*
  for(i=0; i<stLineCfgData.wdItemCount; i++)
  {
    astCaption.printf(" MB_RA: %d / %d ", iWrRA, iCountRA);
    pfrmModParam->pnlStatModRA->Caption = astCaption;
    Application->ProcessMessages();

    if(!MBReadReg(stLineCfgData.wdStartPhAddr+i, stLineCfgData.pwdDataItem[i]))
    {
      #ifdef DEBUG_WRITE_LOG
        astLog.printf(" Error stLineCfgData i: %d",i);
        WriteLog("ReadCfgFromModule",astLog);
      #endif
      return false;
    }
    iWrRA++;
    if (pfrmModParam->cbMBSleep->Checked)
      Sleep(300);
  }
   */
  #ifdef DEBUG_WRITE_LOG
    astLog.printf(" End Ok");
    WriteLog("ReadCfgFromModule",astLog);
  #endif
  return true;
}

bool TAp01mkObj::ReadLineCfgFromModule(int a_iLine)
{
  int i;
  WORD wdIDStartAddr, wdTempStartAddr;
  int iWrRA, iCountRA, iItemCount;
  AnsiString astCaption;
  iItemCount = 128;
  iWrRA = 1; iCountRA = iItemCount;

  #ifdef DEBUG_WRITE_LOG
    astLog.printf(" Start a_iLine: %d", a_iLine);
    WriteLog("ReadLineCfgFromModule",astLog);
  #endif

  switch(a_iLine)
  {
    case 0: wdIDStartAddr = 0x180; wdTempStartAddr = 0x380; break;
    case 1: wdIDStartAddr = 0x200; wdTempStartAddr = 0x3a0; break;
    case 2: wdIDStartAddr = 0x280; wdTempStartAddr = 0x3c0; break;
    case 3: wdIDStartAddr = 0x300; wdTempStartAddr = 0x3e0; break;
    default: wdIDStartAddr = 0x0; break;
  };

  for(i=0; i< 128; i++)
  {
    astCaption.printf(" MB_RA: %d / %d - %d", iWrRA, iCountRA, iMBPassPoll);
   // pfrmModParam->pnlStatModRA->Caption = astCaption;
    Application->ProcessMessages();

    if(!MBReadReg(wdIDStartAddr+i, stLineCfgData.pwdDataItem[wdIDStartAddr-stLineCfgData.wdStartPhAddr+i]))
    {
      #ifdef DEBUG_WRITE_LOG
        astLog.printf(" MBReadReg a_iLine: %d, i: %d", a_iLine, i);
        WriteLog("ReadLineCfgFromModule",astLog);
      #endif
      return false;
    }
    iWrRA++;

  //  if (pfrmModParam->cbMBSleep->Checked)
    //  Sleep(300);
  }
/*
  for(i=0; i< 32; i++)
  {
    ReadReg(stLineCfgData.wdStartPhAddr+wdTempStartAddr+i, stLineCfgData.pwdDataItem[wdTempStartAddr+i]);
    if (pfrmModParam->cbMBSleep->Checked)
      Sleep(300);
  }
  */
  #ifdef DEBUG_WRITE_LOG
    astLog.printf(" End ok ");
    WriteLog("ReadLineCfgFromModule",astLog);
  #endif
  return true;
}

bool TAp01mkObj::SetMicroLanModeInModule(bool ab_Mode)
{
  DWORD dwMode;
  #ifdef DEBUG_WRITE_LOG
    if (ab_Mode)
      astLog.printf(" Start ab_Mode == true");
    else
      astLog.printf(" Start ab_Mode == false");
    WriteLog("SetMicroLanModeInModule",astLog);
  #endif
  if (ab_Mode)
    dwMode = 0xFFFF;
  else
    dwMode = 0x0;

  if(!MBWriteReg(0x1019,dwMode))
    return false;
 // if (pfrmModParam->cbMBSleep->Checked)
   // Sleep(300);

  bMicrolanMode = ab_Mode;

  #ifdef DEBUG_WRITE_LOG
    astLog.printf(" End ok");
    WriteLog("SetMicroLanModeInModule",astLog);
  #endif

  return true;
}

bool TAp01mkObj::WriteCfgToModule()
{
  int i;
  int iCount,iPart;

  int iWrRA, iCountRA;
  AnsiString astCaption;
  iWrRA = 1; iCountRA = stQryRetryData.wdItemCount + stLineCfgData.wdItemCount;

  #ifdef DEBUG_WRITE_LOG
    astLog.printf(" Start stQryRetryData");
    WriteLog("WriteCfgToModule",astLog);
  #endif

  //--- Сохраняем конфигурацию в модуль
  for(i=0; i< stQryRetryData.wdItemCount; i++)
  {
//    pfrmModParam->ShowInStatModRA(iWrRA,iCountRA, iMBPassPoll);
    astCaption.printf(" MB_RA: %d / %d ", iWrRA, iCountRA);
   // pfrmModParam->pnlStatModRA->Caption = astCaption;
    Application->ProcessMessages();
   /////////////////////////////////////////
   /* if(!MBWriteReg(stQryRetryData.wdStartPhAddr+i, stQryRetryData.pwdDataItem[i]))
    {
      #ifdef DEBUG_WRITE_LOG
        astLog.printf(" Err Write: %d ", i);
        WriteLog("WriteCfgToModule",astLog);
      #endif
      return false;
    } */
    iWrRA++;
   /* if (pfrmModParam->cbMBSleep->Checked)
      Sleep(300);
  }  */
//////////////////////
  #ifdef DEBUG_WRITE_LOG
    astLog.printf(" Start stLineCfgData");
    WriteLog("WriteCfgToModule",astLog);
  #endif
  iCount = stLineCfgData.wdItemCount;
  if (stLineCfgData.wdItemCount > MBWRITEREGCNT)
  {
    iPart = MBWRITEREGCNT;
  }
  else
  {
    iPart=stLineCfgData.wdItemCount;
  }
  i=0;
  while (iCount > 0)
  {
    astCaption.printf(" MB_RA: %d / %d ", iWrRA, iCountRA);
  //  pfrmModParam->pnlStatModRA->Caption = astCaption;
    Application->ProcessMessages();

    if(!MBWriteNReg(stLineCfgData.wdStartPhAddr+i, &stLineCfgData.pwdDataItem[i],iPart))
    {
      #ifdef DEBUG_WRITE_LOG
        astLog.printf(" Error stLineCfgData i: %d",i);
        WriteLog("WriteCfgToModule",astLog);
      #endif
      return false;
    }
    iWrRA+=iPart;
    i+=iPart;
    iCount -=iPart;
////////////////////////
 /*   if (pfrmModParam->cbMBSleep->Checked)
      Sleep(300);  */
////////////////////////////////      
    if (iCount < iPart)
      iPart = iCount;
  }

/*
  for(i=0; i< stLineCfgData.wdItemCount; i++)
  {
    astCaption.printf(" MB_RA: %d / %d ", iWrRA, iCountRA);
    pfrmModParam->pnlStatModRA->Caption = astCaption;
    Application->ProcessMessages();
    if(!MBWriteReg(stLineCfgData.wdStartPhAddr+i, stLineCfgData.pwdDataItem[i]))
    {
      #ifdef DEBUG_WRITE_LOG
        astLog.printf(" Err Write: %d",i);
        WriteLog("WriteCfgToModule",astLog);
      #endif
      return false;
    }
    iWrRA++;
    if (pfrmModParam->cbMBSleep->Checked)
      Sleep(300);  */
  }

  #ifdef DEBUG_WRITE_LOG
    astLog.printf(" End ok");
    WriteLog("WriteCfgToModule",astLog);
  #endif

  return true;
}

bool TAp01mkObj::ReadIDSADTFromModuleAndSetBArr(int a_iLine)
{
  int i;
  WORD wdIDStatAddr, wdIDAlarmAddr, wdIDDeltaTAddr, wdSignalsRegStatus;
  AnsiString astRes, astStat, astAlarm, astDelta;
  wdSignalsRegStatus = 0x1018;

  #ifdef DEBUG_WRITE_LOG
    astLog.printf(" Start - Line: %d ", a_iLine);
    WriteLog("ReadIDSADTFromModuleAndSetBArr",astLog);
  #endif

  switch(a_iLine)
  {
    case 0: wdIDStatAddr = 0x1010; wdIDAlarmAddr = 0x160; wdIDDeltaTAddr = 0x168; break;
    case 1: wdIDStatAddr = 0x1012; wdIDAlarmAddr = 0x162; wdIDDeltaTAddr = 0x16A; break;
    case 2: wdIDStatAddr = 0x1014; wdIDAlarmAddr = 0x164; wdIDDeltaTAddr = 0x16C; break;
    case 3: wdIDStatAddr = 0x1016; wdIDAlarmAddr = 0x166; wdIDDeltaTAddr = 0x16E; break;
    default:
            #ifdef DEBUG_WRITE_LOG
              astLog.printf(" End error - Line: %d ", a_iLine);
              WriteLog("ReadIDSADTFromModuleAndSetBArr",astLog);
            #endif
              return false;

  };

  for (i=0; i<2; i++)
  {
    if (bIsIDReg[a_iLine][i] == true)
    {
      #ifdef DEBUG_WRITE_LOG
        astLog.printf(" status - Line: %d pass: %d", a_iLine, i);
        WriteLog("ReadIDSADTFromModuleAndSetBArr",astLog);
      #endif
      //--- читаем статус
      if(!MBReadReg(wdIDStatAddr+i, stLineStatData.pwdDataItem[wdIDStatAddr-stLineStatData.wdStartPhAddr+i]))
      {
        #ifdef DEBUG_WRITE_LOG
          astLog.printf(" End error #1 - Line: %d ", a_iLine);
          WriteLog("ReadIDSADTFromModuleAndSetBArr",astLog);
        #endif
        return false;
      }
    //  if (pfrmModParam->cbMBSleep->Checked)
      //  Sleep(300);

      //--- Если в регистре статуса есть хоть один датчик читаем тревогу и дельту
      #ifdef DEBUG_WRITE_LOG
        astLog.printf(" Alarm - Line: %d pass: %d", a_iLine, i);
        WriteLog("ReadIDSADTFromModuleAndSetBArr",astLog);
      #endif
//      if(stLineStatData.pwdDataItem[wdIDStatAddr-stLineStatData.wdStartPhAddr+i] > 0)
 //     {
        if(!MBReadReg(wdIDAlarmAddr+i, stAlarmData.pwdDataItem[wdIDAlarmAddr-stAlarmData.wdStartPhAddr+i]))
        {
          #ifdef DEBUG_WRITE_LOG
            astLog.printf(" End error #2 - Line: %d ", a_iLine);
            WriteLog("ReadIDSADTFromModuleAndSetBArr",astLog);
          #endif
          return false;
        }
       // if (pfrmModParam->cbMBSleep->Checked)
        //  Sleep(300);
        #ifdef DEBUG_WRITE_LOG
          astLog.printf(" Delta - Line: %d pass: %d", a_iLine, i);
          WriteLog("ReadIDSADTFromModuleAndSetBArr",astLog);
        #endif
        if(!MBReadReg(wdIDDeltaTAddr+i, stAlarmData.pwdDataItem[wdIDDeltaTAddr-stAlarmData.wdStartPhAddr+i]))
        {
          #ifdef DEBUG_WRITE_LOG
            astLog.printf(" End error #3 - Line: %d ", a_iLine);
            WriteLog("ReadIDSADTFromModuleAndSetBArr",astLog);
          #endif
          return false;
        }
        //if (pfrmModParam->cbMBSleep->Checked)
       //   Sleep(300);
      //}
    }
  }
  //---- Читаем регистр статуса сигнализатора
  #ifdef DEBUG_WRITE_LOG
    astLog.printf(" wdSignalsRegStatus - Line: %d ", a_iLine);
    WriteLog("ReadIDSADTFromModuleAndSetBArr",astLog);
  #endif

  if(!MBReadReg(wdSignalsRegStatus, stLineStatData.pwdDataItem[wdSignalsRegStatus-stLineStatData.wdStartPhAddr]))
    return false;
  //if (pfrmModParam->cbMBSleep->Checked)
  //  Sleep(300);
  //--- Устанавливаем bool archive
  for(int i=0; i< 16; i++)
  {
    //--- Если есть датчики 1-16
    if (bIsIDReg[a_iLine][0] == true)
    {
      //--- Статус
      if(stLineStatData.pwdDataItem[wdIDStatAddr-stLineStatData.wdStartPhAddr] &(1<<i))
        etpsStatID[a_iLine][i]= etpsTrue;
      else
        etpsStatID[a_iLine][i]= etpsFalse;
      //--- Тревога
      if(stAlarmData.pwdDataItem[wdIDAlarmAddr-stAlarmData.wdStartPhAddr] &(1<<i))
        etpsAlarmID[a_iLine][i]= etpsTrue;
      else
        etpsAlarmID[a_iLine][i]= etpsFalse;
      //--- Дельта
      if(stAlarmData.pwdDataItem[wdIDDeltaTAddr-stAlarmData.wdStartPhAddr] &(1<<i))
        etpsDeltaID[a_iLine][i]= etpsTrue;
      else
        etpsDeltaID[a_iLine][i]= etpsFalse;
    }

    //--- Если есть датчики 17-32
    if (bIsIDReg[a_iLine][1] == true)
    {
      //--- Статус
      if(stLineStatData.pwdDataItem[wdIDStatAddr-stLineStatData.wdStartPhAddr+1] &(1<<i))
        etpsStatID[a_iLine][i+16]= etpsTrue;
      else
        etpsStatID[a_iLine][i+16]= etpsFalse;
      //--- Тревога
      if(stAlarmData.pwdDataItem[wdIDAlarmAddr-stAlarmData.wdStartPhAddr+1] &(1<<i))
        etpsAlarmID[a_iLine][i+16]= etpsTrue;
      else
        etpsAlarmID[a_iLine][i+16]= etpsFalse;

      if(stAlarmData.pwdDataItem[wdIDDeltaTAddr-stAlarmData.wdStartPhAddr+1] &(1<<i))
        etpsDeltaID[a_iLine][i+16]= etpsTrue;
      else
        etpsDeltaID[a_iLine][i+16]= etpsFalse;
    }
    //--- Регистр статуса сигнализатора
    if(stLineStatData.pwdDataItem[wdSignalsRegStatus-stLineStatData.wdStartPhAddr] &(1<<i))
      etpsSignalRegStatus[i]= etpsTrue;
    else
      etpsSignalRegStatus[i]= etpsFalse;
  }
  #ifdef DEBUG_WRITE_LOG
    astLog.printf(" End - ok - Line: %d ", a_iLine);
    WriteLog("ReadIDSADTFromModuleAndSetBArr",astLog);
  #endif

  return true;
}

bool TAp01mkObj::ReadIDTempFromModule(int a_iLine, int a_IDNumb)
{
  WORD wdIDTempAddr;
  #ifdef DEBUG_WRITE_LOG
    astLog.printf(" Start - Line: %d a_IDNumb: %d", a_iLine, a_IDNumb);
    WriteLog("ReadIDTempFromModule",astLog);
  #endif
  switch(a_iLine)
  {
    case 0: wdIDTempAddr = 0x1020; break;
    case 1: wdIDTempAddr = 0x1040; break;
    case 2: wdIDTempAddr = 0x1060; break;
    case 3: wdIDTempAddr = 0x1080; break;
    default:
          #ifdef DEBUG_WRITE_LOG
            astLog.printf(" End error - Line: %d a_IDNumb: %d", a_iLine, a_IDNumb);
            WriteLog("ReadIDTempFromModule",astLog);
          #endif
            return false;
  };
  //--- Считываем значение
  if(!MBReadReg(wdIDTempAddr+a_IDNumb, stLineStatData.pwdDataItem[wdIDTempAddr-stLineStatData.wdStartPhAddr+a_IDNumb]))
  {
    #ifdef DEBUG_WRITE_LOG
      astLog.printf(" End false #1 - Line: %d a_IDNumb: %d", a_iLine, a_IDNumb);
      WriteLog("ReadIDTempFromModule",astLog);
    #endif
    return false;
  }
  //if (pfrmModParam->cbMBSleep->Checked)
    //Sleep(300);
  //--- Сохраняем значение
  iTempID[a_iLine][a_IDNumb] = stLineStatData.pwdDataItem[wdIDTempAddr-stLineStatData.wdStartPhAddr+a_IDNumb];
  etpsTemIDCorrect[a_iLine][a_IDNumb] = etpsTrue;

  #ifdef DEBUG_WRITE_LOG
    astLog.printf(" End true #2 - Line: %d a_IDNumb: %d", a_iLine, a_IDNumb);
    WriteLog("ReadIDTempFromModule",astLog);
  #endif
  return true;
}

bool  TAp01mkObj::SetCfgIDArr(int a_iLine)
{ //--- Формирование массива датчиков на шлейфе
  int iReg;
  WORD wdIDStartAddr;
  iReg = 0;
  #ifdef DEBUG_WRITE_LOG
    astLog.printf(" Start - Line: %d", a_iLine);
    WriteLog("SetCfgIDArr",astLog);
  #endif
  switch(a_iLine)
  {
    case 0: wdIDStartAddr = 0x180; break;
    case 1: wdIDStartAddr = 0x200; break;
    case 2: wdIDStartAddr = 0x280; break;
    case 3: wdIDStartAddr = 0x300; break;
    default:
              #ifdef DEBUG_WRITE_LOG
                astLog.printf(" End error - Line: %d", a_iLine);
                WriteLog("SetCfgIDArr",astLog);
              #endif
          return false;
  };
  iReg = 0;
  bIsIDReg[a_iLine][0] = false; bIsIDReg[a_iLine][1] = false;

  for (int i=0; i<32; i++)
  {
    etpsCfgID[a_iLine][i] = etpsFalse;
    for(int j=0; j < 4; j++)
    {
      if (stLineCfgData.pwdDataItem[wdIDStartAddr-stLineCfgData.wdStartPhAddr+i*4+j] > 0x0000 &&
          stLineCfgData.pwdDataItem[wdIDStartAddr-stLineCfgData.wdStartPhAddr+i*4+j] < 0xFFFF)
      {
        etpsCfgID[a_iLine][i] = etpsTrue;
/*        if (bIsIDReg[a_iLine][iReg] == false)
        {
          bIsIDReg[a_iLine][iReg] = true; //--- Устанавливаем доступность датчиков по регистрам
        }
        if (iReg == 0 && i==15)
          iReg = 1; */
        break;
      }
    }
    if (iReg == 0 && i>=15)
      iReg = 1;

    if (etpsCfgID[a_iLine][i] == etpsTrue)
    {
      if (bIsIDReg[a_iLine][iReg] == false)
      {
        bIsIDReg[a_iLine][iReg] = true; //--- Устанавливаем доступность датчиков по регистрам
      }
    }
  }
  #ifdef DEBUG_WRITE_LOG
    astLog.printf(" End ok - Line: %d", a_iLine);
    WriteLog("SetCfgIDArr",astLog);
  #endif
  return true;
}
bool TAp01mkObj::MBReadReg(USHORT adr, USHORT& value)
{
  int i;
  i=1;
  #ifdef DEBUG_WRITE_LOG
    WriteLog("MBReadReg"," Start");
  #endif
  while (i>0)
  {
    try
    {
      if (i == 6)
      {
        Sleep(300);
        #ifdef DEBUG_WRITE_LOG
          WriteLog("MBReadReg"," ModBus Busy");
        #endif
      }
      i=0;
      ReadReg(adr, value);

    }
    catch(ECommError &e)
    {
      if (e.HelpContext == 6)
      {
        i=6;
      }
      else
      {
        Application->MessageBoxA("MBRead", e.Message.c_str(),MB_OK|MB_ICONERROR);
        #ifdef DEBUG_WRITE_LOG
          WriteLog("MBReadReg"," End - error");
        #endif
        return false;
      }
    }
  }
  #ifdef DEBUG_WRITE_LOG
    WriteLog("MBReadReg"," End - Ok");
  #endif
  return true;
}

bool TAp01mkObj::MBReadNReg(USHORT adr, USHORT& value, USHORT num)
{
  int i;
  USHORT *tmp;
  tmp = &value;
  i=1;
  #ifdef DEBUG_WRITE_LOG
    WriteLog("MBReadReg"," Start");
  #endif
  while (i>0)
  {
    try
    {
      if (i == 6)
      {
        Sleep(300);
        #ifdef DEBUG_WRITE_LOG
          WriteLog("MBReadReg"," ModBus Busy");
        #endif
      }
      i=0;
      ReadRegs(adr,num,tmp);

    }
    catch(ECommError &e)
    {
      if (e.HelpContext == 6)
      {
        i=6;
      }
      else
      {
        Application->MessageBoxA("MBRead", e.Message.c_str(),MB_OK|MB_ICONERROR);
        #ifdef DEBUG_WRITE_LOG
          WriteLog("MBReadReg"," End - error");
        #endif
        return false;
      }
    }
  }
  #ifdef DEBUG_WRITE_LOG
    WriteLog("MBReadReg"," End - Ok");
  #endif
  return true;
}

bool TAp01mkObj::MBWriteReg (USHORT adr, USHORT value)
{
  int i;
  i=1;
  #ifdef DEBUG_WRITE_LOG
    WriteLog("MBWriteReg"," Start");
  #endif
  while (i>0)
  {
    try
    {
      if (i == 6)
      {
        Sleep(300);
        #ifdef DEBUG_WRITE_LOG
          WriteLog("MBWriteReg"," ModBus Busy");
        #endif
      }
      i=0;
      WriteReg(adr, value);

    }
    catch(ECommError &e)
    {
      if (e.HelpContext == 6)
      {
        i=6;
      }
      else
      {
        Application->MessageBoxA("MBWrite", e.Message.c_str(),MB_OK|MB_ICONERROR);
        #ifdef DEBUG_WRITE_LOG
          WriteLog("MBWriteReg"," End - error");
        #endif
        return false;
      }
    }
  }
  #ifdef DEBUG_WRITE_LOG
    WriteLog("MBWriteReg"," End - Ok");
  #endif
  return true;
}
bool TAp01mkObj::MBWriteNReg (USHORT adr, USHORT *pvalue, USHORT num)
{
  int i;
  i=1;
  #ifdef DEBUG_WRITE_LOG
    WriteLog("MBWriteReg"," Start");
  #endif
  while (i>0)
  {
    try
    {
      if (i == 6)
      {
        Sleep(300);
        #ifdef DEBUG_WRITE_LOG
          WriteLog("MBWriteReg"," ModBus Busy");
        #endif
      }
      i=0;
      WriteRegs(adr,num,pvalue);
    }
    catch(ECommError &e)
    {
      if (e.HelpContext == 6)
      {
        i=6;
      }
      else
      {
        Application->MessageBoxA("MBWrite", e.Message.c_str(),MB_OK|MB_ICONERROR);
        #ifdef DEBUG_WRITE_LOG
          WriteLog("MBWriteReg"," End - error");
        #endif
        return false;
      }
    }
  }
  #ifdef DEBUG_WRITE_LOG
    WriteLog("MBWriteReg"," End - Ok");
  #endif
  return true;
}

bool TAp01mkObj::ResetID(WORD a_wdVal)
{
  #ifdef DEBUG_WRITE_LOG
    WriteLog("ResetID"," Start");
  #endif
  if(!MBWriteReg(0x100F, a_wdVal))
    return false;
 // if (pfrmModParam->cbMBSleep->Checked)
 //   Sleep(300);
  #ifdef DEBUG_WRITE_LOG
    WriteLog("ResetID"," End");
  #endif
  return true;
}

bool TAp01mkObj::InitTPSArrays(int a_iMode)
{
  for (int i=0; i< 32; i++ )
  {
    for(int j=0; j<4; j++)
    {
      if (a_iMode == 0)
      {
         etpsCfgID[j][i] = etpsInit;
      }
      etpsStatID[j][i] = etpsInit;
      etpsAlarmID[j][i] = etpsInit;
      etpsDeltaID[j][i] = etpsInit;
      iTempID[j][i] = -1000;
      etpsTemIDCorrect[j][i] = etpsInit;

      if (i < 16)
        etpsSignalRegStatus[i] = etpsInit;
    }
  }

  return true;
}

bool TAp01mkObj::SetBGetStatMode(bool a_bMode)
{
  #ifdef DEBUG_WRITE_LOG
    if (a_bMode)
      WriteLog("SetBGetStatMode"," Start - a_bMode == true");
    else
      WriteLog("SetBGetStatMode"," Start - a_bMode == false");
  #endif

  if (a_bMode)
  { //--- Старт опроса
    iMBPassPoll = 0;
    pfrmModParam->timGetStatMode->Interval=300;
    pfrmModParam->timGetStatMode->Enabled = true;
  }
  else
  { //--- Стоп опроса
    pfrmModParam->timGetStatMode->Enabled = false;
  }

  bGetStatMode = a_bMode;
  pfrmModParam->SetPnlGetSost(bGetStatMode);
  #ifdef DEBUG_WRITE_LOG
    if (a_bMode)
      WriteLog("SetBGetStatMode"," End - a_bMode == true");
    else
      WriteLog("SetBGetStatMode"," End - a_bMode == false");
  #endif
  return true;
}


bool TAp01mkObj::GetBGetStatMode(void)
{
  #ifdef DEBUG_WRITE_LOG
    if (bGetStatMode)
      WriteLog("GetBGetStatMode","bGetStatMode == true");
    else
      WriteLog("GetBGetStatMode","bGetStatMode == false");
  #endif
  return bGetStatMode;
}

bool TAp01mkObj::ReadIDFromModuleToWDArr(int a_iLine, int a_IDNumb,WORD *a_pwdResArr)
{ //--- Считываем ID (4 word) и сохраняем кго в массиве из 4-WORD
 WORD wdIDAddr;
  #ifdef DEBUG_WRITE_LOG
    WriteLog("ReadIDFromModuleToWDArr","Start");
  #endif
  switch(a_iLine)
  {
    case 0: wdIDAddr = 0x0180; break;
    case 1: wdIDAddr = 0x0200; break;
    case 2: wdIDAddr = 0x0280; break;
    case 3: wdIDAddr = 0x0300; break;
    default: return false;
  };
  wdIDAddr += a_IDNumb*4;
  if(!MBReadNReg(wdIDAddr, a_pwdResArr[0],4))
      return false;
  //if (pfrmModParam->cbMBSleep->Checked)
   //   Sleep(300);
  /*
  for(int i=0; i<4; i++)
  {
    //--- Считываем значение
    if(!MBReadReg(wdIDAddr, wdWrk))
      return false;
    if (pfrmModParam->cbMBSleep->Checked)
      Sleep(300);
    a_pwdResArr[i] = wdWrk;
    wdIDAddr++;
  } */
  #ifdef DEBUG_WRITE_LOG
    WriteLog("ReadIDFromModuleToWDArr","End");
  #endif
  return true;
}

bool TAp01mkObj::SetBMicrolanMode(bool a_bMode)
{
  #ifdef DEBUG_WRITE_LOG
    if (a_bMode)
      WriteLog("SetBMicrolanMode"," Start - a_bMode == true");
    else
      WriteLog("SetBMicrolanMode"," Start - a_bMode == false");
  #endif
  if (!SetMicroLanModeInModule(a_bMode)) //--- Сначала командуем железяке
  {
    return false;
  }
  if (a_bMode)
  { //--- Старт опроса
    iMBPassPoll = 0;
    pfrmModParam->TimMicroLan->Interval=300;
    pfrmModParam->TimMicroLan->Enabled = true;
    for(int i=0; i<4; i++)
    {
      SetCfgIDArr(i);
      bCfgLineFull[i]=false;
    }
  }
  else
  { //--- Стоп опроса
    pfrmModParam->TimMicroLan->Enabled = false;
  }

  bMicrolanMode = a_bMode;

  pfrmModParam->SetPnlConfigMicrolan(bMicrolanMode);
  #ifdef DEBUG_WRITE_LOG
    if (a_bMode)
      WriteLog("SetBMicrolanMode"," End - a_bMode == true");
    else
      WriteLog("SetBMicrolanMode"," End - a_bMode == false");
  #endif
  return true;
}

bool TAp01mkObj::GetBMicrolanMode(void)
{
  #ifdef DEBUG_WRITE_LOG
    if (bMicrolanMode)
      WriteLog("GetBMicrolanMode","bMicrolanMode == true");
    else
      WriteLog("GetBMicrolanMode","bMicrolanMode == false");
  #endif
  return bMicrolanMode;
}

void TAp01mkObj::WriteLog(AnsiString a_astFunc, AnsiString a_astStr)
{
#ifdef DEBUG_WRITE_LOG
  FILE *fp;
  AnsiString ast2Write;
  if((fp=fopen("c:\\Log_gbg.upp","at"))==NULL)
    return;
  ast2Write = a_astFunc + " - " + a_astStr + "\n";
  fputs(ast2Write.c_str(), fp);
  fclose(fp);
#endif
}

