//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Global.h"
#include "Unit2.h"
#include "Unit1.h"
#include "C_ExternalDevices.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TTrenazer *Trenazer;
//---------------------------------------------------------------------------
__fastcall TTrenazer::TTrenazer(TComponent* Owner)
   : TForm(Owner)
{
   port_FF00_out_modified = true;
   port_FF00_in  = 0;
   port_FF00_out = 0;
   Label3->Caption = "00H";

   EX_Devices->RegisterWriteCallback(0xFF00, WriteToPort_FF00H);
   EX_Devices->RegisterReadCallback(0xFF00, ReadFromPort_FF00H);
}
//---------------------------------------------------------------------------
void __fastcall TTrenazer::WriteToPort_FF00H(byte _Value)
{
   port_FF00_out = _Value;
   port_FF00_out_modified = true;
}

byte __fastcall TTrenazer::ReadFromPort_FF00H()
{
   return port_FF00_in;
}
//---------------------------------------------------------------------------
void __fastcall TTrenazer::InPort_FF00H_Click(TObject *Sender)
{
   int index = ((TSpeedButton *)Sender)->Tag;
   if(((TSpeedButton *)Sender)->Down)
   {
      port_FF00_in |= (1 << index);
      ((TSpeedButton *)Sender)->Caption = "1";
   }
   else
   {
      port_FF00_in &= ~(1 << index);
      ((TSpeedButton *)Sender)->Caption = "0";          
   }
   AnsiString pom;
   pom.sprintf("%02XH", port_FF00_in);

   Label3->Caption = pom;//sprintf("%x", port_FF00_in);
}
//---------------------------------------------------------------------------
void __fastcall TTrenazer::UpdateOutput()
{
   OutPort_FF00H_0->Brush->Color = (port_FF00_out & E_BF_0) ? clRed : clMaroon;
   OutPort_FF00H_1->Brush->Color = (port_FF00_out & E_BF_1) ? clRed : clMaroon;
   OutPort_FF00H_2->Brush->Color = (port_FF00_out & E_BF_2) ? clRed : clMaroon;
   OutPort_FF00H_3->Brush->Color = (port_FF00_out & E_BF_3) ? clRed : clMaroon;
   OutPort_FF00H_4->Brush->Color = (port_FF00_out & E_BF_4) ? clRed : clMaroon;
   OutPort_FF00H_5->Brush->Color = (port_FF00_out & E_BF_5) ? clRed : clMaroon;
   OutPort_FF00H_6->Brush->Color = (port_FF00_out & E_BF_6) ? clRed : clMaroon;
   OutPort_FF00H_7->Brush->Color = (port_FF00_out & E_BF_7) ? clRed : clMaroon;
}

void __fastcall TTrenazer::UpdateGreenLeds(byte _Value)
{
   port1_0->Brush->Color = (_Value & E_BF_0) ? clLime : clGreen;
   port1_1->Brush->Color = (_Value & E_BF_1) ? clLime : clGreen;
   port1_2->Brush->Color = (_Value & E_BF_2) ? clLime : clGreen;
   port1_3->Brush->Color = (_Value & E_BF_3) ? clLime : clGreen;
   port1_4->Brush->Color = (_Value & E_BF_4) ? clLime : clGreen;
   port1_5->Brush->Color = (_Value & E_BF_5) ? clLime : clGreen;
   port1_6->Brush->Color = (_Value & E_BF_6) ? clLime : clGreen;
   port1_7->Brush->Color = (_Value & E_BF_7) ? clLime : clGreen;
}

void __fastcall TTrenazer::Tick()
{
   if(port_FF00_out_modified)
   {
      UpdateOutput();
      port_FF00_out_modified = false;
   }
   UpdateGreenLeds(Procesor_8051->GetPortP1());
}
void __fastcall TTrenazer::Restart(void)
{
   Trenazer->port1_0->Brush->Color = clGreen;
   Trenazer->port1_1->Brush->Color = clGreen;
   Trenazer->port1_2->Brush->Color = clGreen;
   Trenazer->port1_3->Brush->Color = clGreen;
   Trenazer->port1_4->Brush->Color = clGreen;
   Trenazer->port1_5->Brush->Color = clGreen;
   Trenazer->port1_6->Brush->Color = clGreen;
   Trenazer->port1_7->Brush->Color = clGreen;

   Trenazer->OutPort_FF00H_0->Brush->Color = clMaroon;
   Trenazer->OutPort_FF00H_1->Brush->Color = clMaroon;
   Trenazer->OutPort_FF00H_2->Brush->Color = clMaroon;
   Trenazer->OutPort_FF00H_3->Brush->Color = clMaroon;
   Trenazer->OutPort_FF00H_4->Brush->Color = clMaroon;
   Trenazer->OutPort_FF00H_5->Brush->Color = clMaroon;
   Trenazer->OutPort_FF00H_6->Brush->Color = clMaroon;
   Trenazer->OutPort_FF00H_7->Brush->Color = clMaroon;
}
