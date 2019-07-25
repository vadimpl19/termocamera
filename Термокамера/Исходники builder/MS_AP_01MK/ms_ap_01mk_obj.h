#ifndef TAP01MK_OBJ
#define TAP01MK_OBJ
#include "ms_ap_01mk.h"
#include <stdio.h>
#include "func.h"
enum enTypeDataInfo {etdiQryRetry=0, etdiLineCfg=1, etdiBase=2, etdiAlarm=3,etdiLineStat=4, etdiTempVal=5};
enum enTPStat {etpsFalse = 0, etpsTrue =1, etpsInit=2};
class TForm1;
class TfrmModuleParamForm;
class TAp01mkObj
{
private:
  struct DATA_INFO stQryRetryData;
  struct DATA_INFO stLineCfgData;
  struct DATA_INFO stAlarmData;
  struct DATA_INFO stLineStatData;

  bool bAp01mkMode;

  TForm1 *pfrmMainForm;
  TfrmModuleParamForm *pfrmModParam;
  void InitDataInfo(WORD *pa_Data, WORD a_Len);
  bool bGetStatMode;
  bool bMicrolanMode;
public:
  bool bIsCfg;
  bool bCfgChanged;
  bool bIsIDReg[4][2];
  AnsiString astLog;
  enTPStat etpsCfgID[4][32]; //--- Датчики в конфигурации на шлейфе.
  enTPStat etpsStatID[4][32]; //--- Статус датчиков на шлейфе.
  enTPStat etpsAlarmID[4][32]; //--- Тревога по температуре датчиков на шлейфе.
  enTPStat etpsDeltaID[4][32]; //--- Тревога по delte датчиков на шлейфе.
  enTPStat etpsSignalRegStatus[16]; //--- Регистр статуса сигнализатора.
  int iTempID[4][32];        //--- Значение температуры
  bool bCfgLineFull[4];     //--- Статус заполненности шлейфав датчиками.
  enTPStat etpsTemIDCorrect[4][32];
  int iMBPassPoll;
  int iCurrTempID;
  TAp01mkObj(TForm1 *a_pfrnIn);
  ~TAp01mkObj();
  void SetWrkMode(bool a_bMode);
  void SwitchWrkMode(void);
  bool GetWrkMode(void);
  void SetModParamForm(TfrmModuleParamForm *a_pfrmIn);
  bool SaveCfgToFile(AnsiString a_astFileName);
  bool LoadCfgFromFile(AnsiString a_astFileName);
  bool InitToEmptyCfg();
  //--- Работа с модулем
  bool WriteCfgToModule();
  bool ReadCfgFromModule();
  bool ReadLineCfgFromModule(int a_iLine);
  bool MBReadReg(USHORT adr, USHORT& value);
  bool MBReadNReg(USHORT adr, USHORT& value, USHORT num);
  bool MBWriteReg(USHORT adr, USHORT value);
  bool MBWriteNReg (USHORT adr, USHORT *pvalue, USHORT num);
  bool ResetID(WORD a_wdVal);
  //=====================================
  bool SetWordDataInfo(enTypeDataInfo a_type, WORD a_Addr, WORD a_wdData);
  bool SetByteDataInfo(enTypeDataInfo a_type, WORD a_Addr, BYTE a_btData, int a_idx);
  bool SetBitDataInfo(enTypeDataInfo a_type, WORD a_Addr, BYTE a_btData, int a_idx);
  bool GetWordDataInfo(enTypeDataInfo a_type, WORD a_Addr, WORD *ap_wdData);
  bool GetByteDataInfo(enTypeDataInfo a_type, WORD a_Addr, BYTE *ap_btData, int a_idx);
  bool GetBitDataInfo(enTypeDataInfo a_type, WORD a_Addr, BYTE *ap_btData, int a_idx);
  bool Word2TwoByte(WORD a_wdIn, BYTE *ap_btRes1, BYTE *ap_btRes2);
  bool TwoByte2Word(BYTE a_btRes1, BYTE a_btRes2, WORD *ap_wdRes);
  bool WordToBoolArray(WORD a_wdVal, int iOff, bool *ab_ResArr);
  //--- Работа с массивами
  bool SetCfgIDArr(int a_iLine);
  bool InitTPSArrays(int a_iMode); //--- 0-Очищаем все, 1-Все кроме CfgID
  //=====================================
  //---- Ф-ции периодического опроса состояния и температуры
  bool ReadIDSADTFromModuleAndSetBArr(int a_iLine); //--- Чтение регистров status, alarm, delta temp
  bool ReadIDTempFromModule(int a_iLine, int a_IDNumb); //--- Чтение температуры
  bool SetBGetStatMode(bool a_bMode);
  bool GetBGetStatMode(void);
  //--- Ф-ции конфигурирования микролан
  bool ReadIDFromModuleToWDArr(int a_iLine, int a_IDNumb,WORD *a_pwdResArr);
  bool SetBMicrolanMode(bool a_bMode);
  bool GetBMicrolanMode(void);
  bool SetMicroLanModeInModule(bool ab_Mode);
  //--- Тестовые ф-ции
  void WriteLog(AnsiString a_astFunc, AnsiString a_astStr);
};
#endif
