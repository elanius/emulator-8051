//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Global.h"
#include "Unit3.h"
#include "C_ExternalDevices.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAplic3 *Aplic3;
//---------------------------------------------------------------------------
__fastcall TAplic3::TAplic3(TComponent* Owner)
   : TForm(Owner)
{
   Applic3_modified = true;
   Applic3_port_in  = 0;
   Applic3_port_out = 0;

   EX_Devices->RegisterWriteCallback(0xFF5A, WriteToPort_Applic3);
   EX_Devices->RegisterReadCallback(0xFF5A, ReadFromPort_Applic3);
}
//---------------------------------------------------------------------------
void __fastcall TAplic3::WriteToPort_Applic3(byte _Value)
{
   Applic3_port_out = _Value;
   Applic3_modified = true;
}
byte __fastcall TAplic3::ReadFromPort_Applic3()
{
   return Applic3_port_in;
}
//---------------------------------------------------------------------------
void __fastcall TAplic3::Tick()
{
   if(Applic3_modified)
   {
      UpdateOutput();
      Applic3_modified = false;
   }
}
//---------------------------------------------------------------------------
void __fastcall TAplic3::UpdateOutput()
{

   RedLed->Brush->Color = (Applic3_port_out & (1 << PolohaZariadenia(Edit1->Text)))
      ? clRed : clMaroon;

   if (Applic3_port_out & (1 << PolohaZariadenia(EditA->Text)) &&
      Applic3_port_out & (1 << PolohaZariadenia(EditC->Text)))
   {
      KM_AC->Brush->Color = clYellow;
      KM_C->Brush->Color  = clWhite;
      KM_CB->Brush->Color = clWhite;
      KM_B->Brush->Color  = clWhite;
      KM_BD->Brush->Color = clWhite;
      KM_D->Brush->Color  = clWhite;
      KM_DA->Brush->Color = clWhite;
      KM_A->Brush->Color  = clWhite;
   }
   else if (Applic3_port_out & (1 << PolohaZariadenia(EditC->Text)) &&
      Applic3_port_out & (1 << PolohaZariadenia(EditB->Text)))
   {
      KM_AC->Brush->Color = clWhite;
      KM_C->Brush->Color  = clWhite;
      KM_CB->Brush->Color = clYellow;
      KM_B->Brush->Color  = clWhite;
      KM_BD->Brush->Color = clWhite;
      KM_D->Brush->Color  = clWhite;
      KM_DA->Brush->Color = clWhite;
      KM_A->Brush->Color  = clWhite;
   }
   else if (Applic3_port_out & (1 << PolohaZariadenia(EditB->Text)) &&
      Applic3_port_out & (1 << PolohaZariadenia(EditD->Text)))
   {
      KM_AC->Brush->Color = clWhite;
      KM_C->Brush->Color  = clWhite;
      KM_CB->Brush->Color = clWhite;
      KM_B->Brush->Color  = clWhite;
      KM_BD->Brush->Color = clYellow;
      KM_D->Brush->Color  = clWhite;
      KM_DA->Brush->Color = clWhite;
      KM_A->Brush->Color  = clWhite;
   }
   else if (Applic3_port_out & (1 << PolohaZariadenia(EditD->Text)) &&
      Applic3_port_out & (1 << PolohaZariadenia(EditA->Text)))
   {
      KM_AC->Brush->Color = clWhite;
      KM_C->Brush->Color  = clWhite;
      KM_CB->Brush->Color = clWhite;
      KM_B->Brush->Color  = clWhite;
      KM_BD->Brush->Color = clWhite;
      KM_D->Brush->Color  = clWhite;
      KM_DA->Brush->Color = clYellow;
      KM_A->Brush->Color  = clWhite;
   }
   else if (Applic3_port_out & (1 << PolohaZariadenia(EditA->Text)))
   {
      KM_AC->Brush->Color = clWhite;
      KM_C->Brush->Color  = clWhite;
      KM_CB->Brush->Color = clWhite;
      KM_B->Brush->Color  = clWhite;
      KM_BD->Brush->Color = clWhite;
      KM_D->Brush->Color  = clWhite;
      KM_DA->Brush->Color = clWhite;
      KM_A->Brush->Color  = clYellow;
   }
   else if (Applic3_port_out & (1 << PolohaZariadenia(EditC->Text)))
   {
      KM_AC->Brush->Color = clWhite;
      KM_C->Brush->Color  = clYellow;
      KM_CB->Brush->Color = clWhite;
      KM_B->Brush->Color  = clWhite;
      KM_BD->Brush->Color = clWhite;
      KM_D->Brush->Color  = clWhite;
      KM_DA->Brush->Color = clWhite;
      KM_A->Brush->Color  = clWhite;
   }
   else if (Applic3_port_out & (1 << PolohaZariadenia(EditB->Text)))
   {
      KM_AC->Brush->Color = clWhite;
      KM_C->Brush->Color  = clWhite;
      KM_CB->Brush->Color = clWhite;
      KM_B->Brush->Color  = clYellow;
      KM_BD->Brush->Color = clWhite;
      KM_D->Brush->Color  = clWhite;
      KM_DA->Brush->Color = clWhite;
      KM_A->Brush->Color  = clWhite;
   }
   else if (Applic3_port_out & (1 << PolohaZariadenia(EditD->Text)))
   {
      KM_AC->Brush->Color = clWhite;
      KM_C->Brush->Color  = clWhite;
      KM_CB->Brush->Color = clWhite;
      KM_B->Brush->Color  = clWhite;
      KM_BD->Brush->Color = clWhite;
      KM_D->Brush->Color  = clYellow;
      KM_DA->Brush->Color = clWhite;
      KM_A->Brush->Color  = clWhite;
   }

   if (Applic3_port_out & (1 << PolohaZariadenia(Edit5->Text)))
   {
      Timer1->Enabled = true;
   }
   else
   {
      Timer1->Enabled = false;
//      StopMotorcek();
   }

   if (PolohaZariadenia(Edit1->Text) == -1)
      Edit1->Color = clRed;
   else if (Edit1->Text == "")
      Edit1->Color = clAqua;
   else
      Edit1->Color = clWhite;

   if (PolohaZariadenia(Edit2->Text) == -1)
      Edit2->Color = clRed;
   else if (Edit2->Text == "")
      Edit2->Color = clAqua;
   else
      Edit2->Color = clWhite;

   if (PolohaZariadenia(Edit3->Text) == -1)
      Edit3->Color = clRed;
   else if (Edit3->Text == "")
      Edit3->Color = clAqua;
   else
      Edit3->Color = clWhite;

   if (PolohaZariadenia(Edit4->Text) == -1)
      Edit4->Color = clRed;
   else if (Edit4->Text == "")
      Edit4->Color = clAqua;
   else
      Edit4->Color = clWhite;

   if (PolohaZariadenia(Edit5->Text) == -1)
      Edit5->Color = clRed;
   else if (Edit5->Text == "")
      Edit5->Color = clAqua;
   else
      Edit5->Color = clWhite;

   if (PolohaZariadenia(EditA->Text) == -1)
      EditA->Color = clRed;
   else if (EditA->Text == "")
      EditA->Color = clAqua;
   else
      EditA->Color = clWhite;

   if (PolohaZariadenia(EditB->Text) == -1)
      EditB->Color = clRed;
   else if (EditB->Text == "")
      EditB->Color = clAqua;
   else
      EditB->Color = clWhite;

   if (PolohaZariadenia(EditC->Text) == -1)
      EditC->Color = clRed;
   else if (EditC->Text == "")
      EditC->Color = clAqua;
   else
      EditC->Color = clWhite;

   if (PolohaZariadenia(EditD->Text) == -1)
      EditD->Color = clRed;
   else if (EditD->Text == "")
      EditD->Color = clAqua;
   else
      EditD->Color = clWhite;

/*   Edit1->Color = PolohaZariadenia(Edit1->Text) == -1 ? clRed : clWindow;
   Edit2->Color = PolohaZariadenia(Edit2->Text) == -1 ? clRed : clWindow;
   Edit3->Color = PolohaZariadenia(Edit3->Text) == -1 ? clRed : clWindow;
   Edit4->Color = PolohaZariadenia(Edit4->Text) == -1 ? clRed : clWindow;
   Edit5->Color = PolohaZariadenia(Edit5->Text) == -1 ? clRed : clWindow;
   EditA->Color = PolohaZariadenia(EditA->Text) == -1 ? clRed : clWindow;
   EditB->Color = PolohaZariadenia(EditB->Text) == -1 ? clRed : clWindow;
   EditC->Color = PolohaZariadenia(EditC->Text) == -1 ? clRed : clWindow;
   EditD->Color = PolohaZariadenia(EditD->Text) == -1 ? clRed : clWindow;

   Edit1->Color = Edit1->Text == "" ? clAqua : clWindow;
   Edit2->Color = Edit2->Text == "" ? clAqua : clWindow;
   Edit3->Color = Edit3->Text == "" ? clAqua : clWindow;
   Edit4->Color = Edit4->Text == "" ? clAqua : clWindow;
   Edit5->Color = Edit5->Text == "" ? clAqua : clWindow;
   EditA->Color = EditA->Text == "" ? clAqua : clWindow;
   EditB->Color = EditB->Text == "" ? clAqua : clWindow;
   EditC->Color = EditC->Text == "" ? clAqua : clWindow;
   EditD->Color = EditD->Text == "" ? clAqua : clWindow;
                */
}


void __fastcall TAplic3::PrepinacClick(TObject *Sender)
{

   if (Prepinac->Down)
   {
      Applic3_port_in |= (1 << PolohaZariadenia(Edit2->Text));
      Prepinac->Caption = "1";
   }
   else
   {
      Applic3_port_in &= ~(1 << PolohaZariadenia(Edit2->Text));
      Prepinac->Caption = "0";
   }
}
//---------------------------------------------------------------------------
void __fastcall TAplic3::SpeedButton2MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
   Applic3_port_in |= (1 << PolohaZariadenia(Edit3->Text));
}
//---------------------------------------------------------------------------
void __fastcall TAplic3::SpeedButton2MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
   Applic3_port_in &= ~(1 << PolohaZariadenia(Edit3->Text));
}
//---------------------------------------------------------------------------

void __fastcall TAplic3::Shape18MouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
   Applic3_port_in |= (1 << PolohaZariadenia(Edit4->Text));
   Shape18->Brush->Color = clOlive;
}
//---------------------------------------------------------------------------



void __fastcall TAplic3::Shape19MouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
   Applic3_port_in &= ~(1 << PolohaZariadenia(Edit4->Text));
   Shape18->Brush->Color = clYellow;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
int  __fastcall TAplic3::PolohaZariadenia(AnsiString Edit)
{
   int poloha = 0;
   if (Edit >= '0' && Edit <= '7' && Edit.Length() == 1)
   {
      poloha = Edit.ToInt();
      //Label7->Caption = poloha;
   }
   else if (Edit == "")
   {
      poloha = 8;
   }
   else
      poloha = -1;
   return poloha;
}
//---------------------------------------------------------------------------
void  __fastcall TAplic3::TocMotorcek(int krok)
{
   switch (krok)
   {
   case 1 : Mot8->Brush->Color = clWhite;
            Mot1->Brush->Color = clRed; break;

   case 2 : Mot1->Brush->Color = clWhite;
            Mot2->Brush->Color = clRed; break;

   case 3 : Mot2->Brush->Color = clWhite;
            Mot3->Brush->Color = clRed; break;

   case 4 : Mot3->Brush->Color = clWhite;
            Mot4->Brush->Color = clRed; break;

   case 5 : Mot4->Brush->Color = clWhite;
            Mot5->Brush->Color = clRed; break;

   case 6 : Mot5->Brush->Color = clWhite;
            Mot6->Brush->Color = clRed; break;

   case 7 : Mot6->Brush->Color = clWhite;
            Mot7->Brush->Color = clRed; break;

   case 8 : Mot7->Brush->Color = clWhite;
            Mot8->Brush->Color = clRed; break;
   }
}
//---------------------------------------------------------------------------
void  __fastcall TAplic3::StopMotorcek(void)
{
   Mot1->Brush->Color = clWhite;
   Mot2->Brush->Color = clWhite;
   Mot3->Brush->Color = clWhite;
   Mot4->Brush->Color = clWhite;
   Mot5->Brush->Color = clWhite;
   Mot6->Brush->Color = clWhite;
   Mot7->Brush->Color = clWhite;
   Mot8->Brush->Color = clWhite;
}


void __fastcall TAplic3::Timer1Timer(TObject *Sender)
{
   static int krok = 1;

   TocMotorcek(krok);

   if (++krok == 9)
      krok = 1;
}
void  __fastcall TAplic3::Restart(void)
{
   Timer1->Enabled = false;
   
   Aplic3->RedLed->Brush->Color = clMaroon;
   Aplic3->Mot1->Brush->Color = clWhite;
   Aplic3->Mot2->Brush->Color = clWhite;
   Aplic3->Mot3->Brush->Color = clWhite;
   Aplic3->Mot4->Brush->Color = clWhite;
   Aplic3->Mot5->Brush->Color = clWhite;
   Aplic3->Mot6->Brush->Color = clWhite;
   Aplic3->Mot7->Brush->Color = clWhite;
   Aplic3->Mot8->Brush->Color = clWhite;

   Aplic3->KM_A->Brush->Color  = clWhite;
   Aplic3->KM_AC->Brush->Color = clWhite;
   Aplic3->KM_C->Brush->Color  = clWhite;
   Aplic3->KM_CB->Brush->Color = clWhite;
   Aplic3->KM_B->Brush->Color  = clWhite;
   Aplic3->KM_BD->Brush->Color = clWhite;
   Aplic3->KM_D->Brush->Color  = clWhite;
   Aplic3->KM_DA->Brush->Color = clWhite;

}
//---------------------------------------------------------------------------

