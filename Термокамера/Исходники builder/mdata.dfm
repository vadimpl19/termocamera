object ModData: TModData
  Left = 144
  Top = 68
  BorderStyle = bsDialog
  Caption = '������ ������'
  ClientHeight = 260
  ClientWidth = 451
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
  object GroupBox2: TGroupBox
    Left = 0
    Top = 108
    Width = 448
    Height = 123
    Caption = '��������� ������'
    TabOrder = 3
    object GroupBox3: TGroupBox
      Left = 2
      Top = 18
      Width = 247
      Height = 102
      Caption = '�������������� ����������'
      TabOrder = 0
      object lbSt0: TLabel
        Left = 8
        Top = 15
        Width = 210
        Height = 16
        Caption = '������� ���������� �� � �����'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clGray
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object lbSt1: TLabel
        Left = 8
        Top = 32
        Width = 49
        Height = 16
        Caption = '������'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clGray
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object lbSt2: TLabel
        Left = 8
        Top = 48
        Width = 170
        Height = 16
        Caption = '����������� ���� �����'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clGray
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object lbSt3: TLabel
        Left = 8
        Top = 65
        Width = 153
        Height = 16
        Caption = '������ �� ����������'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clGray
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object lbSt4: TLabel
        Left = 8
        Top = 81
        Width = 201
        Height = 16
        Caption = '���������� ���������� �� ��'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clRed
        Font.Height = -15
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
      end
    end
  end
  object GroupBox1: TGroupBox
    Left = 0
    Top = -1
    Width = 362
    Height = 109
    Caption = '��������� �������'
    TabOrder = 2
    object Label2: TLabel
      Left = 4
      Top = 27
      Width = 27
      Height = 16
      Caption = '��1'
    end
    object Label3: TLabel
      Left = 4
      Top = 47
      Width = 27
      Height = 16
      Caption = '��2'
    end
    object Label4: TLabel
      Left = 4
      Top = 66
      Width = 27
      Height = 16
      Caption = '��3'
    end
    object Label5: TLabel
      Left = 4
      Top = 86
      Width = 27
      Height = 16
      Caption = '��4'
    end
    object lbWire1: TLabel
      Left = 38
      Top = 27
      Width = 187
      Height = 16
      Caption = '��������� ����� ������ ��'
    end
    object lbWire2: TLabel
      Left = 38
      Top = 47
      Width = 138
      Height = 16
      Caption = '�������� ���������'
    end
    object lbWire3: TLabel
      Left = 38
      Top = 66
      Width = 122
      Height = 16
      Caption = '�������� ���� ��'
    end
    object lbWire4: TLabel
      Left = 38
      Top = 86
      Width = 159
      Height = 16
      Caption = '���������� ����������'
    end
    object lbCurrent1: TLabel
      Left = 231
      Top = 27
      Width = 65
      Height = 16
      Caption = '���: 40 ��'
    end
    object lbCurrent2: TLabel
      Left = 231
      Top = 47
      Width = 65
      Height = 16
      Caption = '���: 55 ��'
    end
    object lbCurrent3: TLabel
      Left = 231
      Top = 66
      Width = 65
      Height = 16
      Caption = '���: 30 ��'
    end
    object lbCurrent4: TLabel
      Left = 231
      Top = 86
      Width = 58
      Height = 16
      Caption = '���: 1 ��'
    end
    object btRes1: TButton
      Left = 310
      Top = 26
      Width = 47
      Height = 21
      Caption = '�����'
      TabOrder = 0
      TabStop = False
      OnClick = btResClick
    end
    object btRes2: TButton
      Tag = 1
      Left = 310
      Top = 45
      Width = 47
      Height = 21
      Caption = '�����'
      TabOrder = 1
      TabStop = False
      OnClick = btResClick
    end
    object btRes3: TButton
      Tag = 2
      Left = 310
      Top = 65
      Width = 47
      Height = 21
      Caption = '�����'
      TabOrder = 2
      TabStop = False
      OnClick = btResClick
    end
    object btRes4: TButton
      Tag = 3
      Left = 310
      Top = 85
      Width = 47
      Height = 21
      Caption = '�����'
      TabOrder = 3
      TabStop = False
      OnClick = btResClick
    end
  end
  object CheckBox1: TCheckBox
    Left = 131
    Top = 237
    Width = 203
    Height = 21
    TabStop = False
    Caption = '��������� ������������'
    TabOrder = 0
    OnClick = CheckBox1Click
  end
  object btRead: TButton
    Left = 19
    Top = 236
    Width = 92
    Height = 22
    Caption = '�������'
    Default = True
    TabOrder = 1
    OnClick = tmReadTimer
  end
  object GroupBox5: TGroupBox
    Left = 361
    Top = -1
    Width = 88
    Height = 109
    Caption = '�������'
    ParentShowHint = False
    ShowHint = True
    TabOrder = 4
    object Label8: TLabel
      Left = 3
      Top = 14
      Width = 43
      Height = 16
      Caption = '�����'
    end
    object Label9: TLabel
      Left = 52
      Top = 14
      Width = 30
      Height = 16
      Caption = '1 ��'
    end
    object chbLatch2: TCheckBox
      Left = 20
      Top = 48
      Width = 16
      Height = 17
      Hint = '������������ ��������� "�����"'
      Enabled = False
      TabOrder = 0
    end
    object chbLatch3: TCheckBox
      Left = 20
      Top = 68
      Width = 16
      Height = 17
      Hint = '������������ ��������� "�����"'
      Enabled = False
      TabOrder = 1
    end
    object chbLatch4: TCheckBox
      Left = 20
      Top = 87
      Width = 16
      Height = 17
      Hint = '������������ ��������� "�����"'
      Enabled = False
      TabOrder = 2
    end
    object chbLatch1: TCheckBox
      Left = 20
      Top = 29
      Width = 16
      Height = 17
      Hint = '������������ ��������� "�����"'
      Color = clBtnFace
      Enabled = False
      ParentColor = False
      TabOrder = 3
    end
    object chbPI1: TCheckBox
      Left = 60
      Top = 29
      Width = 16
      Height = 17
      Hint = '����������� ��������� 1 ��'
      Color = clBtnFace
      Enabled = False
      ParentColor = False
      TabOrder = 4
    end
    object chbPI2: TCheckBox
      Left = 60
      Top = 48
      Width = 16
      Height = 17
      Hint = '����������� ��������� 1 ��'
      Enabled = False
      TabOrder = 5
    end
    object chbPI3: TCheckBox
      Left = 60
      Top = 68
      Width = 16
      Height = 17
      Hint = '����������� ��������� 1 ��'
      Enabled = False
      TabOrder = 6
    end
    object chbPI4: TCheckBox
      Left = 60
      Top = 87
      Width = 16
      Height = 17
      Hint = '����������� ��������� 1 ��'
      Enabled = False
      TabOrder = 7
    end
  end
  object tmRead: TTimer
    Enabled = False
    OnTimer = tmReadTimer
    Left = 336
    Top = 191
  end
end
