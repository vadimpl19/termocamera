object ParCOM: TParCOM
  Left = 194
  Top = 107
  HorzScrollBar.Visible = False
  VertScrollBar.Visible = False
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  Caption = 'Параметры порта'
  ClientHeight = 203
  ClientWidth = 244
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 40
    Top = 12
    Width = 25
    Height = 13
    Caption = 'Порт'
  end
  object Label2: TLabel
    Left = 17
    Top = 41
    Width = 48
    Height = 13
    Caption = 'Скорость'
  end
  object Label3: TLabel
    Left = 17
    Top = 70
    Width = 48
    Height = 13
    Caption = 'Четность'
  end
  object Label4: TLabel
    Left = 34
    Top = 100
    Width = 31
    Height = 13
    Alignment = taRightJustify
    Caption = 'Адрес'
  end
  object btOk: TButton
    Left = 158
    Top = 8
    Width = 83
    Height = 25
    Caption = 'OK'
    Default = True
    TabOrder = 0
    OnClick = btOkClick
  end
  object btCancel: TButton
    Left = 158
    Top = 41
    Width = 83
    Height = 25
    Caption = 'Отмена'
    ModalResult = 2
    TabOrder = 1
  end
  object cbPort: TComboBox
    Left = 78
    Top = 8
    Width = 75
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    TabOrder = 2
    Items.Strings = (
      'COM1'
      'COM2'
      'COM3'
      'COM4'
      'COM5'
      'COM6')
  end
  object cbSpeed: TComboBox
    Left = 78
    Top = 37
    Width = 75
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    TabOrder = 3
    Items.Strings = (
      '2400'
      '4800'
      '9600'
      '19200'
      '57600'
      '115200')
  end
  object cbParity: TComboBox
    Left = 78
    Top = 66
    Width = 73
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    TabOrder = 4
    Items.Strings = (
      'None'
      'Odd'
      'Even')
  end
  object edAddress: TEdit
    Left = 78
    Top = 96
    Width = 73
    Height = 21
    TabOrder = 5
  end
  object Button1: TButton
    Left = 158
    Top = 90
    Width = 83
    Height = 25
    Caption = 'По умолчанию'
    TabOrder = 6
    OnClick = Button1Click
  end
  object GroupBox1: TGroupBox
    Left = -1
    Top = 120
    Width = 244
    Height = 77
    TabOrder = 7
    object Label6: TLabel
      Left = 59
      Top = 7
      Width = 86
      Height = 13
      Caption = 'Серийный номер'
    end
    object edNumber: TEdit
      Left = 91
      Top = 20
      Width = 105
      Height = 21
      TabOrder = 0
    end
    object btAuto: TButton
      Left = 71
      Top = 47
      Width = 93
      Height = 25
      Caption = 'Автоматически'
      TabOrder = 1
      OnClick = btAutoClick
    end
    object cbSerNumAlpha: TComboBox
      Left = 51
      Top = 21
      Width = 33
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 2
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
end
