object Trenazer: TTrenazer
  Left = 298
  Top = 359
  BorderStyle = bsToolWindow
  Caption = 'Trenažér'
  ClientHeight = 234
  ClientWidth = 406
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
  object Label1: TLabel
    Left = 184
    Top = 104
    Width = 152
    Height = 20
    Caption = 'Input port : FF00H'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label2: TLabel
    Left = 184
    Top = 8
    Width = 167
    Height = 20
    Caption = 'Output port : FF00H'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label3: TLabel
    Left = 296
    Top = 197
    Width = 6
    Height = 13
    Caption = '0'
  end
  object OutPort_FF00H_0: TShape
    Left = 296
    Top = 40
    Width = 17
    Height = 17
    Brush.Color = clMaroon
    Shape = stCircle
  end
  object OutPort_FF00H_1: TShape
    Left = 280
    Top = 40
    Width = 17
    Height = 17
    Brush.Color = clMaroon
    Shape = stCircle
  end
  object OutPort_FF00H_2: TShape
    Left = 264
    Top = 40
    Width = 17
    Height = 17
    Brush.Color = clMaroon
    Shape = stCircle
  end
  object OutPort_FF00H_3: TShape
    Left = 248
    Top = 40
    Width = 17
    Height = 17
    Brush.Color = clMaroon
    Shape = stCircle
  end
  object OutPort_FF00H_4: TShape
    Left = 232
    Top = 40
    Width = 17
    Height = 17
    Brush.Color = clMaroon
    Shape = stCircle
  end
  object OutPort_FF00H_5: TShape
    Left = 216
    Top = 40
    Width = 17
    Height = 17
    Brush.Color = clMaroon
    Shape = stCircle
  end
  object OutPort_FF00H_6: TShape
    Left = 200
    Top = 40
    Width = 17
    Height = 17
    Brush.Color = clMaroon
    Shape = stCircle
  end
  object OutPort_FF00H_7: TShape
    Left = 184
    Top = 40
    Width = 17
    Height = 17
    Brush.Color = clMaroon
    Shape = stCircle
  end
  object Label4: TLabel
    Left = 300
    Top = 58
    Width = 6
    Height = 13
    Caption = '0'
  end
  object Label5: TLabel
    Left = 284
    Top = 58
    Width = 6
    Height = 13
    Caption = '1'
  end
  object Label6: TLabel
    Left = 252
    Top = 58
    Width = 6
    Height = 13
    Caption = '3'
  end
  object Label7: TLabel
    Left = 236
    Top = 58
    Width = 6
    Height = 13
    Caption = '4'
  end
  object Label8: TLabel
    Left = 220
    Top = 58
    Width = 6
    Height = 13
    Caption = '5'
  end
  object Label9: TLabel
    Left = 204
    Top = 58
    Width = 6
    Height = 13
    Caption = '6'
  end
  object Label10: TLabel
    Left = 188
    Top = 58
    Width = 6
    Height = 13
    Caption = '7'
  end
  object Label11: TLabel
    Left = 268
    Top = 58
    Width = 6
    Height = 13
    Caption = '2'
  end
  object InPort_FF00H_0: TSpeedButton
    Left = 352
    Top = 136
    Width = 25
    Height = 25
    AllowAllUp = True
    GroupIndex = 1
    Caption = '0'
    OnClick = InPort_FF00H_Click
  end
  object InPort_FF00H_1: TSpeedButton
    Tag = 1
    Left = 328
    Top = 136
    Width = 25
    Height = 25
    AllowAllUp = True
    GroupIndex = 2
    Caption = '0'
    OnClick = InPort_FF00H_Click
  end
  object InPort_FF00H_2: TSpeedButton
    Tag = 2
    Left = 304
    Top = 136
    Width = 25
    Height = 25
    AllowAllUp = True
    GroupIndex = 3
    Caption = '0'
    OnClick = InPort_FF00H_Click
  end
  object InPort_FF00H_3: TSpeedButton
    Tag = 3
    Left = 280
    Top = 136
    Width = 25
    Height = 25
    AllowAllUp = True
    GroupIndex = 4
    Caption = '0'
    OnClick = InPort_FF00H_Click
  end
  object InPort_FF00H_4: TSpeedButton
    Tag = 4
    Left = 256
    Top = 136
    Width = 25
    Height = 25
    AllowAllUp = True
    GroupIndex = 5
    Caption = '0'
    OnClick = InPort_FF00H_Click
  end
  object InPort_FF00H_5: TSpeedButton
    Tag = 5
    Left = 232
    Top = 136
    Width = 25
    Height = 25
    AllowAllUp = True
    GroupIndex = 6
    Caption = '0'
    OnClick = InPort_FF00H_Click
  end
  object InPort_FF00H_6: TSpeedButton
    Tag = 6
    Left = 208
    Top = 136
    Width = 25
    Height = 25
    AllowAllUp = True
    GroupIndex = 7
    Caption = '0'
    OnClick = InPort_FF00H_Click
  end
  object InPort_FF00H_7: TSpeedButton
    Tag = 7
    Left = 184
    Top = 136
    Width = 25
    Height = 25
    AllowAllUp = True
    GroupIndex = 8
    Caption = '0'
    OnClick = InPort_FF00H_Click
  end
  object Label12: TLabel
    Left = 362
    Top = 164
    Width = 6
    Height = 13
    Caption = '0'
  end
  object Label13: TLabel
    Left = 338
    Top = 164
    Width = 6
    Height = 13
    Caption = '1'
  end
  object Label14: TLabel
    Left = 314
    Top = 164
    Width = 6
    Height = 13
    Caption = '2'
  end
  object Label15: TLabel
    Left = 291
    Top = 164
    Width = 6
    Height = 13
    Caption = '3'
  end
  object Label16: TLabel
    Left = 268
    Top = 164
    Width = 6
    Height = 13
    Caption = '4'
  end
  object Label17: TLabel
    Left = 242
    Top = 164
    Width = 6
    Height = 13
    Caption = '5'
  end
  object Label18: TLabel
    Left = 218
    Top = 164
    Width = 6
    Height = 13
    Caption = '6'
  end
  object Label19: TLabel
    Left = 194
    Top = 164
    Width = 6
    Height = 13
    Caption = '7'
  end
  object Label20: TLabel
    Left = 188
    Top = 197
    Width = 98
    Height = 13
    Caption = 'Hodnota prepínaèov'
  end
  object port1_0: TShape
    Left = 64
    Top = 168
    Width = 17
    Height = 17
    Brush.Color = clGreen
    Shape = stCircle
  end
  object port1_1: TShape
    Left = 64
    Top = 152
    Width = 17
    Height = 17
    Brush.Color = clGreen
    Shape = stCircle
  end
  object port1_2: TShape
    Left = 64
    Top = 136
    Width = 17
    Height = 17
    Brush.Color = clGreen
    Shape = stCircle
  end
  object port1_3: TShape
    Left = 64
    Top = 120
    Width = 17
    Height = 17
    Brush.Color = clGreen
    Shape = stCircle
  end
  object port1_4: TShape
    Left = 64
    Top = 104
    Width = 17
    Height = 17
    Brush.Color = clGreen
    Shape = stCircle
  end
  object port1_5: TShape
    Left = 64
    Top = 88
    Width = 17
    Height = 17
    Brush.Color = clGreen
    Shape = stCircle
  end
  object port1_6: TShape
    Left = 64
    Top = 72
    Width = 17
    Height = 17
    Brush.Color = clGreen
    Shape = stCircle
  end
  object port1_7: TShape
    Left = 64
    Top = 56
    Width = 17
    Height = 17
    Brush.Color = clGreen
    Shape = stCircle
  end
  object Label21: TLabel
    Left = 88
    Top = 170
    Width = 6
    Height = 13
    Caption = '0'
  end
  object Label22: TLabel
    Left = 88
    Top = 155
    Width = 6
    Height = 13
    Caption = '1'
  end
  object Label23: TLabel
    Left = 88
    Top = 123
    Width = 6
    Height = 13
    Caption = '3'
  end
  object Label24: TLabel
    Left = 88
    Top = 107
    Width = 6
    Height = 13
    Caption = '4'
  end
  object Label25: TLabel
    Left = 88
    Top = 91
    Width = 6
    Height = 13
    Caption = '5'
  end
  object Label26: TLabel
    Left = 88
    Top = 75
    Width = 6
    Height = 13
    Caption = '6'
  end
  object Label27: TLabel
    Left = 88
    Top = 59
    Width = 6
    Height = 13
    Caption = '7'
  end
  object Label28: TLabel
    Left = 88
    Top = 139
    Width = 6
    Height = 13
    Caption = '2'
  end
  object Label29: TLabel
    Left = 8
    Top = 8
    Width = 120
    Height = 20
    Caption = '8051 - Port P1'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Bevel1: TBevel
    Left = 161
    Top = 0
    Width = 7
    Height = 241
  end
  object Bevel2: TBevel
    Left = 168
    Top = 88
    Width = 249
    Height = 9
  end
end
