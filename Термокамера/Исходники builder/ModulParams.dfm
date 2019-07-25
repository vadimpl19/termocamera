object ModPars: TModPars
  Left = 385
  Top = 247
  HorzScrollBar.Visible = False
  VertScrollBar.Visible = False
  ActiveControl = edAdress
  BorderStyle = bsDialog
  Caption = 'Служебные параметры модуля'
  ClientHeight = 261
  ClientWidth = 399
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -14
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Scaled = False
  PixelsPerInch = 96
  TextHeight = 16
  object gbModbPars: TGroupBox
    Left = 136
    Top = 2
    Width = 260
    Height = 127
    Anchors = [akTop, akRight]
    Caption = 'Параметры Modbus'
    TabOrder = 0
    object Label1: TLabel
      Left = 122
      Top = 20
      Width = 40
      Height = 16
      Caption = 'Адрес'
    end
    object Label2: TLabel
      Left = 101
      Top = 58
      Width = 61
      Height = 16
      Caption = 'Скорость'
    end
    object Label3: TLabel
      Left = 108
      Top = 96
      Width = 56
      Height = 16
      Caption = 'Паритет'
    end
    object cbSpeed: TComboBox
      Left = 173
      Top = 53
      Width = 80
      Height = 24
      Style = csDropDownList
      ItemHeight = 16
      TabOrder = 1
      Items.Strings = (
        '2400'
        '4800'
        '9600'
        '19200'
        '57600'
        '115200')
    end
    object cbParity: TComboBox
      Left = 173
      Top = 91
      Width = 80
      Height = 24
      Style = csDropDownList
      ItemHeight = 16
      TabOrder = 2
      Items.Strings = (
        'None'
        'Odd'
        'Even')
    end
    object edAdress: TMaskEdit
      Left = 173
      Top = 15
      Width = 80
      Height = 24
      AutoSize = False
      EditMask = '!999;1; '
      MaxLength = 3
      TabOrder = 0
      Text = '   '
    end
  end
  object gbPassport: TGroupBox
    Left = 136
    Top = 128
    Width = 260
    Height = 130
    Anchors = [akTop, akRight]
    Caption = 'Паспорт'
    TabOrder = 1
    object Label4: TLabel
      Left = 58
      Top = 20
      Width = 76
      Height = 16
      Caption = 'Тип модуля'
    end
    object Label5: TLabel
      Left = 64
      Top = 48
      Width = 70
      Height = 16
      Caption = 'Рег. номер'
    end
    object Label6: TLabel
      Left = 7
      Top = 106
      Width = 127
      Height = 16
      Caption = 'Дата изготовления'
    end
    object Label8: TLabel
      Left = 64
      Top = 78
      Width = 70
      Height = 16
      Alignment = taRightJustify
      Caption = 'Версия ПО'
    end
    object edName: TEdit
      Left = 141
      Top = 15
      Width = 112
      Height = 24
      TabStop = False
      AutoSize = False
      Color = clSilver
      Enabled = False
      ReadOnly = True
      TabOrder = 0
    end
    object edManuf: TMaskEdit
      Left = 141
      Top = 101
      Width = 112
      Height = 24
      AutoSize = False
      EditMask = '!99/99/00;1; '
      MaxLength = 8
      TabOrder = 2
      Text = '  .  .  '
    end
    object edNumber: TEdit
      Left = 199
      Top = 43
      Width = 54
      Height = 24
      AutoSize = False
      TabOrder = 1
    end
    object edVer: TEdit
      Left = 141
      Top = 73
      Width = 112
      Height = 24
      AutoSize = False
      Color = clSilver
      Enabled = False
      TabOrder = 3
    end
    object cbAlpha: TComboBox
      Left = 141
      Top = 43
      Width = 47
      Height = 24
      Style = csDropDownList
      ItemHeight = 16
      TabOrder = 4
      Items.Strings = (
        'A'
        'B'
        'C'
        'D'
        'E'
        'F'
        'G'
        'H'
        'I'
        'J'
        'K'
        'L'
        'M'
        'N'
        'O'
        'P'
        'Q'
        'R'
        'S'
        'T'
        'U'
        'V'
        'W'
        'X'
        'Y'
        'Z')
    end
  end
  object GroupBox3: TGroupBox
    Left = -1
    Top = 2
    Width = 131
    Height = 256
    Anchors = [akTop, akRight, akBottom]
    TabOrder = 2
    object btWrite: TButton
      Left = 15
      Top = 25
      Width = 107
      Height = 30
      Caption = 'Записать'
      Default = True
      TabOrder = 0
      OnClick = btWriteClick
    end
    object btRead: TButton
      Left = 15
      Top = 79
      Width = 107
      Height = 31
      Caption = 'Прочитать'
      TabOrder = 1
      OnClick = btReadClick
    end
    object btDef: TButton
      Left = 15
      Top = 133
      Width = 107
      Height = 31
      Caption = 'По умолчанию'
      TabOrder = 2
      OnClick = btDefClick
    end
  end
end
