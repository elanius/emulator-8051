//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Global.h"
#include "Unit4.h"
#include "C_ExternalDevices.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TApplic5 *Applic5;
//---------------------------------------------------------------------------
__fastcall TApplic5::TApplic5(TComponent* Owner)
   : TForm(Owner)
{
   Applic5_modified = false;               //predtin bolo    true
   Applic5_port_in  = 0;
   Applic5_port_out = 0;


   EX_Devices->RegisterWriteCallback(0xFF59, WriteToPort_Applic5);
   EX_Devices->RegisterReadCallback(0xFF59, ReadFromPort_Applic5);

}
//---------------------------------------------------------------------------
void __fastcall TApplic5::WriteToPort_Applic5(byte _Value)
{
   Applic5_port_out = _Value;
   Applic5_modified = true;
}
byte __fastcall TApplic5::ReadFromPort_Applic5()
{
   return Applic5_port_in;
}
//---------------------------------------------------------------------------
void __fastcall TApplic5::Tick()
{
   if(Applic5_modified)
   {
      UpdateOutput();
      Applic5_modified = false;
   }
}
//---------------------------------------------------------------------------
void __fastcall TApplic5::Klavesnica_Click1(TObject *Sender)
{
   if ((Applic5_port_out | ~E_BF_7) == ~E_BF_7)
   {
      int index = ((TSpeedButton *)Sender)->Tag;

      if (index <= 7)
      {
         if (((TSpeedButton *)Sender)->Down)
         {
            Applic5_port_in |= (1 << index);
         }
         else
         {
            Applic5_port_in &= ~(1 << index);
         }
      }
   }
}
//---------------------------------------------------------------------------
void __fastcall TApplic5::Klavesnica_Click2(TObject *Sender)
{
   if ((Applic5_port_out | ~E_BF_6) == ~E_BF_6)
   {
      Shape2->Brush->Color = clLime;
      int index = ((TSpeedButton *)Sender)->Tag;
      if (index >= 8)
      {
         if (((TSpeedButton *)Sender)->Down)
            Applic5_port_in |= (1 << (index - 8));

         else
            Applic5_port_in &= ~(1 << (index - 8));
      }
   }
}
//---------------------------------------------------------------------------
void __fastcall TApplic5::UpdateOutput()
{
   Shape1->Brush->Color = ((Applic5_port_out | ~E_BF_7) == ~E_BF_7)
      ? clLime : clRed;
   Shape2->Brush->Color = ((Applic5_port_out | ~E_BF_6) == ~E_BF_6)
      ? clLime : clRed;
   if (!Zisti_byt(5) && !Zisti_byt(4))
   {
//      Segment0 = new TLabel(this);
//      Nastav_segment(Segment0);  //     Tobject  *o2 = new TObject();

      Nastav_segment0(Applic5_port_out & 0x0F);
   }
   else if (!Zisti_byt(5) && Zisti_byt(4))
      Nastav_segment1(Applic5_port_out & 0x0F);

   else if (Zisti_byt(5) && !Zisti_byt(4))
      Nastav_segment2(Applic5_port_out & 0x0F);

   else if (Zisti_byt(5) && Zisti_byt(4))
      Nastav_segment3(Applic5_port_out & 0x0F);
}
bool __fastcall TApplic5::Zisti_byt(int byt)
{
   if ((Applic5_port_out >> byt) & 0x01)
      return true;
   else
      return false;
}
//---------------------------------------------------------------------------
void __fastcall TApplic5::Nastav_segment0(int seg)
{
   switch (seg)
   {
      case 0 : Segment0->Caption = "0"; break;
      case 1 : Segment0->Caption = "1"; break;
      case 2 : Segment0->Caption = "2"; break;
      case 3 : Segment0->Caption = "3"; break;
      case 4 : Segment0->Caption = "4"; break;
      case 5 : Segment0->Caption = "5"; break;
      case 6 : Segment0->Caption = "6"; break;
      case 7 : Segment0->Caption = "7"; break;
      case 8 : Segment0->Caption = "8"; break;
      case 9 : Segment0->Caption = "9"; break;
      default : Segment0->Caption = "_"; break;
   }
   if (!priznak)
   {
      Segment1->Caption = "_";
      Segment2->Caption = "_";
      Segment3->Caption = "_";
   }
}
void __fastcall TApplic5::Nastav_segment1(int seg)
{
   switch (seg)
   {
      case 0 : Segment1->Caption = "0"; break;
      case 1 : Segment1->Caption = "1"; break;
      case 2 : Segment1->Caption = "2"; break;
      case 3 : Segment1->Caption = "3"; break;
      case 4 : Segment1->Caption = "4"; break;
      case 5 : Segment1->Caption = "5"; break;
      case 6 : Segment1->Caption = "6"; break;
      case 7 : Segment1->Caption = "7"; break;
      case 8 : Segment1->Caption = "8"; break;
      case 9 : Segment1->Caption = "9"; break;
      default : Segment1->Caption = "_"; break;
   }
   if (!priznak)
   {
      Segment0->Caption = "_";
      Segment2->Caption = "_";
      Segment3->Caption = "_";
   }
}
void __fastcall TApplic5::Nastav_segment2(int seg)
{
   switch (seg)
   {
      case 0 : Segment2->Caption = "0"; break;
      case 1 : Segment2->Caption = "1"; break;
      case 2 : Segment2->Caption = "2"; break;
      case 3 : Segment2->Caption = "3"; break;
      case 4 : Segment2->Caption = "4"; break;
      case 5 : Segment2->Caption = "5"; break;
      case 6 : Segment2->Caption = "6"; break;
      case 7 : Segment2->Caption = "7"; break;
      case 8 : Segment2->Caption = "8"; break;
      case 9 : Segment2->Caption = "9"; break;
      default : Segment2->Caption = "_"; break;
   }
   if (!priznak)
   {
      Segment0->Caption = "_";
      Segment1->Caption = "_";
      Segment3->Caption = "_";
   }

}
void __fastcall TApplic5::Nastav_segment3(int seg)
{
   switch (seg)
   {
      case 0 : Segment3->Caption = "0"; break;
      case 1 : Segment3->Caption = "1"; break;
      case 2 : Segment3->Caption = "2"; break;
      case 3 : Segment3->Caption = "3"; break;
      case 4 : Segment3->Caption = "4"; break;
      case 5 : Segment3->Caption = "5"; break;
      case 6 : Segment3->Caption = "6"; break;
      case 7 : Segment3->Caption = "7"; break;
      case 8 : Segment3->Caption = "8"; break;
      case 9 : Segment3->Caption = "9"; break;
      default : Segment3->Caption = "_"; break;
   }
   if (!priznak)
   {
      Segment0->Caption = "_";
      Segment1->Caption = "_";
      Segment2->Caption = "_";
   }
}
//---------------------------------------------------------------------------
void __fastcall TApplic5::Restart(void)
{
   Applic5->Shape1->Brush->Color = clWhite;
   Applic5->Shape2->Brush->Color = clWhite;

   Applic5->Segment0->Caption = "_";
   Applic5->Segment1->Caption = "_";
   Applic5->Segment2->Caption = "_";
   Applic5->Segment3->Caption = "_";

   //Applic5_port_in  = 0;
   //Applic5_port_out = 0;
}
//---------------------------------------------------------------------------
void __fastcall TApplic5::SpeedButton1Click(TObject *Sender)
{
   if (SpeedButton1->Down)
   {
      SpeedButton1->Caption = "ADV";
      priznak = true;
   }
   else
   {
      SpeedButton1->Caption = "Klasic";
      priznak = false;
   }
}
//---------------------------------------------------------------------------

