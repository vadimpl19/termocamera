object ChanPars: TChanPars
  Left = 101
  Top = 42
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  Caption = 'Параметры модуля'
  ClientHeight = 385
  ClientWidth = 389
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
  object Label4: TLabel
    Left = 59
    Top = 223
    Width = 143
    Height = 16
    Caption = 'Защелкивать "Пожар"'
  end
  object Label5: TLabel
    Left = 55
    Top = 244
    Width = 145
    Height = 16
    Caption = 'Защелкивать один ПИ'
  end
  object sgModes: TStringGrid
    Left = 0
    Top = 114
    Width = 387
    Height = 109
    DefaultColWidth = 200
    DefaultRowHeight = 20
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goEditing, goAlwaysShowEditor]
    ScrollBars = ssNone
    TabOrder = 1
    OnSetEditText = sgSetEditText
    ColWidths = (
      200
      44
      48
      46
      40)
    RowHeights = (
      20
      20
      20
      20
      20)
  end
  object sgRange: TStringGrid
    Left = 0
    Top = 0
    Width = 387
    Height = 109
    DefaultColWidth = 200
    DefaultRowHeight = 20
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goEditing, goTabs, goAlwaysShowEditor]
    ScrollBars = ssNone
    TabOrder = 0
    OnSetEditText = sgSetEditText
    ColWidths = (
      200
      44
      48
      45
      42)
    RowHeights = (
      20
      20
      20
      20
      20)
  end
  object btRead: TButton
    Left = 7
    Top = 350
    Width = 93
    Height = 29
    Caption = 'Считать'
    TabOrder = 2
    OnClick = btReadClick
  end
  object btWrite: TButton
    Left = 145
    Top = 350
    Width = 93
    Height = 29
    Caption = 'Записать'
    TabOrder = 3
    OnClick = btWriteClick
  end
  object btDef: TButton
    Left = 278
    Top = 350
    Width = 104
    Height = 29
    Caption = 'По умолчанию'
    TabOrder = 4
    OnClick = btDefClick
  end
  object chbAll: TCheckBox
    Left = 159
    Top = 262
    Width = 218
    Height = 22
    Caption = 'Одинаково для всех каналов'
    TabOrder = 5
    OnClick = chbAllClick
  end
  object GroupBox1: TGroupBox
    Left = -1
    Top = 282
    Width = 386
    Height = 62
    Caption = 'Уставки '
    TabOrder = 6
    object Label3: TLabel
      Left = 133
      Top = 13
      Width = 152
      Height = 16
      Alignment = taRightJustify
      Caption = 'Число сбросов шлейфа'
    end
    object Label6: TLabel
      Left = 134
      Top = 37
      Width = 151
      Height = 16
      Alignment = taRightJustify
      Caption = 'Таймаут на опрос (сек)'
    end
    object edRep: TEdit
      Left = 288
      Top = 13
      Width = 50
      Height = 20
      AutoSize = False
      TabOrder = 0
    end
    object edTimeOut: TEdit
      Left = 288
      Top = 35
      Width = 50
      Height = 20
      AutoSize = False
      TabOrder = 1
    end
  end
  object chbFire1: TCheckBox
    Left = 216
    Top = 223
    Width = 16
    Height = 17
    TabOrder = 7
    OnClick = chbFireClick
  end
  object chbFire2: TCheckBox
    Left = 264
    Top = 223
    Width = 16
    Height = 17
    TabOrder = 8
    OnClick = chbFireClick
  end
  object chbFire3: TCheckBox
    Left = 311
    Top = 223
    Width = 16
    Height = 17
    TabOrder = 9
    OnClick = chbFireClick
  end
  object chbPI4: TCheckBox
    Tag = 4
    Left = 359
    Top = 244
    Width = 16
    Height = 17
    TabOrder = 10
    OnClick = chbPIClick
  end
  object chbPI1: TCheckBox
    Tag = 1
    Left = 216
    Top = 244
    Width = 16
    Height = 17
    TabOrder = 11
    OnClick = chbPIClick
  end
  object chbFire4: TCheckBox
    Left = 359
    Top = 223
    Width = 16
    Height = 17
    TabOrder = 12
    OnClick = chbFireClick
  end
  object chbPI3: TCheckBox
    Tag = 3
    Left = 311
    Top = 244
    Width = 16
    Height = 17
    TabOrder = 13
    OnClick = chbPIClick
  end
  object chbPI2: TCheckBox
    Tag = 2
    Left = 264
    Top = 244
    Width = 16
    Height = 17
    TabOrder = 14
    OnClick = chbPIClick
  end
end
