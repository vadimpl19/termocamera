object Calibr1: TCalibr1
  Left = 215
  Top = 176
  HorzScrollBar.Visible = False
  VertScrollBar.Visible = False
  AutoScroll = False
  BorderIcons = []
  Caption = 'Калибровка - шаг 1'
  ClientHeight = 65
  ClientWidth = 394
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -14
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Scaled = False
  OnClose = FormClose
  PixelsPerInch = 120
  TextHeight = 16
  object lbTip: TLabel
    Left = 0
    Top = 6
    Width = 337
    Height = 16
    AutoSize = False
    Caption = 'Отсоедините входа модуля'
  end
  object btCancel: TButton
    Left = 12
    Top = 28
    Width = 72
    Height = 31
    Caption = 'Отмена'
    ModalResult = 2
    TabOrder = 1
  end
  object btNext: TButton
    Left = 314
    Top = 28
    Width = 73
    Height = 31
    Caption = 'Далее >>'
    Default = True
    TabOrder = 0
    OnClick = btNextClick
  end
  object btPrev: TButton
    Left = 211
    Top = 28
    Width = 73
    Height = 31
    Caption = '<< Назад'
    TabOrder = 2
    Visible = False
    OnClick = btPrevClick
  end
  object edT: TEdit
    Left = 343
    Top = 4
    Width = 40
    Height = 18
    TabOrder = 3
    Visible = False
  end
end
