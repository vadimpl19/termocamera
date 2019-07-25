object Form1: TForm1
  Left = 319
  Top = 206
  HorzScrollBar.Visible = False
  VertScrollBar.Visible = False
  BorderIcons = [biSystemMenu]
  BorderStyle = bsToolWindow
  Caption = 'Выбор режима'
  ClientHeight = 19
  ClientWidth = 266
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  Position = poDesktopCenter
  Scaled = False
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object StatusBar1: TStatusBar
    Left = 0
    Top = 0
    Width = 266
    Height = 19
    Panels = <
      item
        Width = 50
      end>
    SimplePanel = False
  end
  object MainMenu1: TMainMenu
    Left = 160
    Top = 65520
    object miModPar: TMenuItem
      Caption = '     Работа      '
      OnClick = miModParClick
    end
    object miComPar: TMenuItem
      Caption = '  Настройки порта '
      OnClick = miComParClick
    end
    object A1: TMenuItem
      Caption = '    About     '
      OnClick = A1Click
    end
  end
end
