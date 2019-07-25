object frmIDWrkForm: TfrmIDWrkForm
  Left = 313
  Top = 285
  BorderStyle = bsDialog
  Caption = 'Изменение параметров'
  ClientHeight = 151
  ClientWidth = 261
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object gbIDAddr: TGroupBox
    Left = 8
    Top = 8
    Width = 225
    Height = 65
    Caption = ' Адрес датчика '
    TabOrder = 0
    Visible = False
    object Label1: TLabel
      Left = 352
      Top = 16
      Width = 33
      Height = 13
      Alignment = taCenter
      AutoSize = False
      Caption = '00'
    end
    object Label2: TLabel
      Left = 312
      Top = 16
      Width = 33
      Height = 13
      Alignment = taCenter
      AutoSize = False
      Caption = '01'
    end
    object Label3: TLabel
      Left = 256
      Top = 16
      Width = 33
      Height = 13
      Alignment = taCenter
      AutoSize = False
      Caption = '02'
    end
    object Label4: TLabel
      Left = 216
      Top = 16
      Width = 33
      Height = 13
      Alignment = taCenter
      AutoSize = False
      Caption = '03'
    end
    object Label5: TLabel
      Left = 152
      Top = 16
      Width = 33
      Height = 13
      Alignment = taCenter
      AutoSize = False
      Caption = '04'
    end
    object Label6: TLabel
      Left = 112
      Top = 16
      Width = 33
      Height = 13
      Alignment = taCenter
      AutoSize = False
      Caption = '05'
    end
    object Label7: TLabel
      Left = 56
      Top = 16
      Width = 33
      Height = 13
      Alignment = taCenter
      AutoSize = False
      Caption = '06'
    end
    object Label8: TLabel
      Left = 16
      Top = 16
      Width = 33
      Height = 13
      Alignment = taCenter
      AutoSize = False
      Caption = '07'
    end
    object edtAddr07: TEdit
      Left = 16
      Top = 32
      Width = 33
      Height = 21
      TabOrder = 0
    end
    object edtAddr06: TEdit
      Left = 56
      Top = 32
      Width = 33
      Height = 21
      TabOrder = 1
    end
    object edtAddr05: TEdit
      Left = 112
      Top = 32
      Width = 33
      Height = 21
      TabOrder = 2
    end
    object edtAddr04: TEdit
      Left = 152
      Top = 32
      Width = 33
      Height = 21
      TabOrder = 3
    end
    object edtAddr03: TEdit
      Left = 216
      Top = 32
      Width = 33
      Height = 21
      TabOrder = 4
    end
    object edtAddr02: TEdit
      Left = 256
      Top = 32
      Width = 33
      Height = 21
      TabOrder = 5
    end
    object edtAddr01: TEdit
      Left = 312
      Top = 32
      Width = 33
      Height = 21
      TabOrder = 6
    end
    object edtAddr00: TEdit
      Left = 352
      Top = 32
      Width = 33
      Height = 21
      TabOrder = 7
    end
  end
  object Panel1: TPanel
    Left = 8
    Top = 8
    Width = 241
    Height = 81
    TabOrder = 4
    object Label9: TLabel
      Left = 24
      Top = 8
      Width = 55
      Height = 13
      Caption = 'Желаемая'
    end
    object Label10: TLabel
      Left = 16
      Top = 24
      Width = 65
      Height = 13
      Caption = 'температура'
    end
    object Label11: TLabel
      Left = 120
      Top = 8
      Width = 110
      Height = 13
      Caption = 'Скорость нарастания'
    end
    object Label12: TLabel
      Left = 144
      Top = 24
      Width = 67
      Height = 13
      Caption = 'температуры'
    end
    object edtdT: TCSpinEdit
      Left = 144
      Top = 40
      Width = 57
      Height = 30
      TabStop = True
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      MaxValue = 10
      ParentColor = False
      ParentFont = False
      TabOrder = 0
    end
  end
  object btnSave: TButton
    Left = 24
    Top = 104
    Width = 75
    Height = 25
    Caption = 'Сохранить'
    TabOrder = 1
    OnClick = btnSaveClick
  end
  object btnCancel: TButton
    Left = 144
    Top = 104
    Width = 75
    Height = 25
    Caption = 'Отмена'
    TabOrder = 2
    OnClick = btnCancelClick
  end
  object edtTmax: TCSpinEdit
    Left = 32
    Top = 48
    Width = 57
    Height = 30
    TabStop = True
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    MaxValue = 85
    ParentColor = False
    ParentFont = False
    TabOrder = 3
  end
end
