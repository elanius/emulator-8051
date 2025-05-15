object Aplic3: TAplic3
  Left = 318
  Top = 346
  BorderStyle = bsToolWindow
  Caption = 'Applic3'
  ClientHeight = 236
  ClientWidth = 455
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poDefault
  Visible = True
  PixelsPerInch = 96
  TextHeight = 13
  object Shape19: TShape
    Left = 364
    Top = 44
    Width = 39
    Height = 39
    Brush.Color = clBtnFace
    OnMouseMove = Shape19MouseMove
  end
  object Mot8: TShape
    Tag = 7
    Left = 24
    Top = 136
    Width = 17
    Height = 17
    Shape = stCircle
  end
  object Mot7: TShape
    Tag = 6
    Left = 16
    Top = 160
    Width = 17
    Height = 17
    Shape = stCircle
  end
  object Mot6: TShape
    Tag = 5
    Left = 24
    Top = 184
    Width = 17
    Height = 17
    Shape = stCircle
  end
  object Mot5: TShape
    Tag = 4
    Left = 48
    Top = 192
    Width = 17
    Height = 17
    Shape = stCircle
  end
  object Mot4: TShape
    Tag = 3
    Left = 72
    Top = 184
    Width = 17
    Height = 17
    Shape = stCircle
  end
  object Mot3: TShape
    Tag = 2
    Left = 80
    Top = 160
    Width = 17
    Height = 17
    Shape = stCircle
  end
  object Mot2: TShape
    Tag = 1
    Left = 72
    Top = 136
    Width = 17
    Height = 17
    Shape = stCircle
  end
  object Mot1: TShape
    Left = 48
    Top = 128
    Width = 17
    Height = 17
    Shape = stCircle
  end
  object Label1: TLabel
    Left = 8
    Top = 96
    Width = 105
    Height = 20
    Caption = 'JS Motorèek'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object RedLed: TShape
    Left = 40
    Top = 52
    Width = 17
    Height = 17
    Brush.Color = clMaroon
    Enabled = False
    Shape = stCircle
  end
  object Label2: TLabel
    Left = 8
    Top = 24
    Width = 88
    Height = 20
    Caption = 'LED APL3'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label3: TLabel
    Left = 144
    Top = 96
    Width = 149
    Height = 20
    Caption = 'Krokový Motorèek'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object KM_DA: TShape
    Left = 176
    Top = 136
    Width = 17
    Height = 17
    Shape = stCircle
  end
  object KM_D: TShape
    Left = 168
    Top = 160
    Width = 17
    Height = 17
    Shape = stCircle
  end
  object KM_BD: TShape
    Left = 176
    Top = 184
    Width = 17
    Height = 17
    Shape = stCircle
  end
  object KM_B: TShape
    Left = 200
    Top = 192
    Width = 17
    Height = 17
    Shape = stCircle
  end
  object KM_CB: TShape
    Left = 224
    Top = 184
    Width = 17
    Height = 17
    Shape = stCircle
  end
  object KM_C: TShape
    Left = 232
    Top = 160
    Width = 17
    Height = 17
    Shape = stCircle
  end
  object KM_AC: TShape
    Left = 224
    Top = 136
    Width = 17
    Height = 17
    Shape = stCircle
  end
  object KM_A: TShape
    Left = 200
    Top = 128
    Width = 17
    Height = 17
    Shape = stCircle
  end
  object Prepinac: TSpeedButton
    Left = 136
    Top = 48
    Width = 23
    Height = 22
    AllowAllUp = True
    GroupIndex = 1
    Caption = '0'
    OnClick = PrepinacClick
  end
  object Label4: TLabel
    Left = 112
    Top = 24
    Width = 75
    Height = 20
    Caption = 'Prepinaè'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label5: TLabel
    Left = 224
    Top = 24
    Width = 67
    Height = 20
    Caption = 'Tlaèidlo'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object SpeedButton2: TSpeedButton
    Left = 248
    Top = 48
    Width = 23
    Height = 22
    OnMouseDown = SpeedButton2MouseDown
    OnMouseUp = SpeedButton2MouseUp
  end
  object Label6: TLabel
    Left = 328
    Top = 24
    Width = 103
    Height = 20
    Caption = 'Foto snímaè'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Shape18: TShape
    Left = 376
    Top = 55
    Width = 17
    Height = 17
    Brush.Color = clYellow
    Shape = stCircle
    OnMouseMove = Shape18MouseMove
  end
  object Label8: TLabel
    Left = 56
    Top = 64
    Width = 15
    Height = 20
    Caption = 'Q'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label9: TLabel
    Left = 160
    Top = 64
    Width = 11
    Height = 20
    Caption = 'J'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label10: TLabel
    Left = 272
    Top = 64
    Width = 11
    Height = 20
    Caption = 'J'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label11: TLabel
    Left = 408
    Top = 64
    Width = 11
    Height = 20
    Caption = 'J'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label12: TLabel
    Left = 80
    Top = 208
    Width = 15
    Height = 20
    Caption = 'Q'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label13: TLabel
    Left = 272
    Top = 128
    Width = 15
    Height = 20
    Caption = 'Q'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label14: TLabel
    Left = 272
    Top = 152
    Width = 15
    Height = 20
    Caption = 'Q'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label15: TLabel
    Left = 272
    Top = 176
    Width = 15
    Height = 20
    Caption = 'Q'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label16: TLabel
    Left = 272
    Top = 200
    Width = 15
    Height = 20
    Caption = 'Q'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label7: TLabel
    Left = 205
    Top = 115
    Width = 7
    Height = 13
    Caption = 'A'
  end
  object Label17: TLabel
    Left = 253
    Top = 163
    Width = 7
    Height = 13
    Caption = 'C'
  end
  object Label18: TLabel
    Left = 157
    Top = 163
    Width = 8
    Height = 13
    Caption = 'D'
  end
  object Label19: TLabel
    Left = 205
    Top = 211
    Width = 7
    Height = 13
    Caption = 'B'
  end
  object Label20: TLabel
    Left = 317
    Top = 131
    Width = 7
    Height = 13
    Caption = 'A'
  end
  object Label21: TLabel
    Left = 317
    Top = 155
    Width = 7
    Height = 13
    Caption = 'B'
  end
  object Label22: TLabel
    Left = 317
    Top = 179
    Width = 7
    Height = 13
    Caption = 'C'
  end
  object Label23: TLabel
    Left = 317
    Top = 203
    Width = 8
    Height = 13
    Caption = 'D'
  end
  object Bevel1: TBevel
    Left = 102
    Top = -6
    Width = 7
    Height = 95
  end
  object Bevel2: TBevel
    Left = 211
    Top = -6
    Width = 7
    Height = 95
  end
  object Bevel3: TBevel
    Left = 317
    Top = -6
    Width = 7
    Height = 95
  end
  object Bevel4: TBevel
    Left = 1
    Top = 90
    Width = 456
    Height = 7
  end
  object Bevel5: TBevel
    Left = 128
    Top = 98
    Width = 7
    Height = 135
  end
  object Bevel6: TBevel
    Left = 336
    Top = 99
    Width = 7
    Height = 135
  end
  object Edit1: TEdit
    Left = 72
    Top = 64
    Width = 25
    Height = 21
    Color = clAqua
    TabOrder = 0
  end
  object Edit2: TEdit
    Left = 176
    Top = 64
    Width = 25
    Height = 21
    Color = clAqua
    TabOrder = 1
  end
  object Edit3: TEdit
    Left = 288
    Top = 64
    Width = 25
    Height = 21
    Color = clAqua
    TabOrder = 2
  end
  object Edit4: TEdit
    Left = 424
    Top = 64
    Width = 25
    Height = 21
    Color = clAqua
    TabOrder = 3
  end
  object Edit5: TEdit
    Left = 96
    Top = 208
    Width = 25
    Height = 21
    Color = clAqua
    TabOrder = 4
  end
  object EditA: TEdit
    Left = 288
    Top = 128
    Width = 25
    Height = 21
    Color = clAqua
    TabOrder = 5
  end
  object EditB: TEdit
    Left = 288
    Top = 152
    Width = 25
    Height = 21
    Color = clAqua
    TabOrder = 6
  end
  object EditC: TEdit
    Left = 288
    Top = 176
    Width = 25
    Height = 21
    Color = clAqua
    TabOrder = 7
  end
  object EditD: TEdit
    Left = 288
    Top = 200
    Width = 25
    Height = 21
    Color = clAqua
    TabOrder = 8
  end
  object Timer1: TTimer
    Enabled = False
    Interval = 100
    OnTimer = Timer1Timer
    Left = 424
    Top = 200
  end
end
