object Password: TPassword
  Left = 194
  Top = 107
  ActiveControl = edPass
  BorderIcons = []
  BorderStyle = bsDialog
  Caption = 'Ввод пароля'
  ClientHeight = 99
  ClientWidth = 153
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
    Left = 4
    Top = 4
    Width = 142
    Height = 13
    Caption = 'Без пароля паспорт модуля'
  end
  object Label2: TLabel
    Left = 3
    Top = 22
    Width = 145
    Height = 13
    Caption = 'доступен только для чтения!'
  end
  object edPass: TEdit
    Left = 20
    Top = 40
    Width = 105
    Height = 21
    PasswordChar = '*'
    TabOrder = 0
  end
  object btOK: TButton
    Left = 38
    Top = 68
    Width = 75
    Height = 25
    Caption = 'ОК'
    Default = True
    TabOrder = 1
    OnClick = btOKClick
  end
end
