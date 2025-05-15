//---------------------------------------------------------------------------

#pragma hdrstop

#include "Global.h"
#include "emulator.h"
#include "C_ExternalDevices.h"
#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"
#include "Unit4.h"
#include "Unit5.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

#define first   (i + 1)
#define second  (i + 2)
#define third   (i + 3)
TForm1 *Form1;
//---------------------------------------------------------------------------
void __fastcall TForm1::MyIdleHandler(TObject *Sender, bool &Done)
{
   Procesor_8051->Tick();
   Trenazer->Tick();
   Aplic3->Tick();
   Applic5->Tick();
   Done = false;
}

__fastcall TForm1::TForm1(TComponent* Owner)
   : TForm(Owner)
{
   Application->OnIdle = MyIdleHandler;

   index_navestia = 0;
   index = 0;

   EX_Devices = new C_ExternalDevices();
   TempRE = new TRichEdit(this);

   Procesor_8051 = new C_Procesor();
   Procesor_8051->init();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SpeedButton2Click(TObject *Sender)
{
   Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RestartClick(TObject *Sender)
{
   Hlasenia->Lines->Clear();
   Reset();

   for (int i = 0; i <= 99; i++)
      for ( int j = 0; j <= 3; j++)
         navestia[i][j] = NULL;

   index_navestia = 0;


   for (int i = 0; i <= 4000; i++)
      program_hex[i] = 0;
   index = 0;

   for (int i = 0; i <= 4000; i++)
      strojovy_kod[i] = program_hex[i];

   Procesor_8051->napal_program(strojovy_kod, sizeof(strojovy_kod), 0);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SBRunClick(TObject *Sender)
{
   Procesor_8051->napal_program(strojovy_kod, sizeof(strojovy_kod), 0);
   Procesor_8051->start(0);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SBsaveClick(TObject *Sender)
{
   Hlasenia->Lines->Clear();

   for (int i = 0; i <= 99; i++)
      for ( int j = 0; j <= 3; j++)
         navestia[i][j] = NULL;

   index_navestia = 0;


   for (int i = 0; i <= 4000; i++)
      program_hex[i] = 0;
   index = 0;


   for (int i = 0; i < RichEdit1->Lines->Count; i++)
         ProcesLine(RichEdit1->Lines->Strings[i]);

   Hlasenie_chyb_navestia();

   for (int i = 0; i <= 4000; i++)
      strojovy_kod[i] = program_hex[i];
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ProcesLine(AnsiString &Line)
{
   AnsiString items[5];
   bool next = true;

   for(int i = 1, j = -1; i < Line.Length() + 1; i++)
   {
      if (Line[i] == ';')
         break;

      if (Line[i] == ' ' || Line[i] == '\t' || Line[i] == ',')
      {
         next = true;
         continue;
      }
      else
      {
         if(next)
         {
            j++;
            next = false;
         }

         items[j] += (char)toupper(Line[i]);
      }
   }
   ProcesItems(items);
}
//------------------------------------------------------------------------------
void __fastcall TForm1::Preprocesor(AnsiString Items[])
{

}
//------------------------------------------------------------------------------
void __fastcall TForm1::ProcesItems(AnsiString Items[]/*, int NumOfItems*/)
{
   int i = 0;
   int maska = 0;
   int INTCISLO = 0;
   int pom = 0;
   AnsiString finta_na_NULL;

   for (int p = 0; p <= 5; p++)
   {
      if (Items[p] == "P1")
         Items[p] = "90H";
      else if (Items[p] == "FO")
         Items[p] == "D5H";
      else if (Items[p] == "ACC.0")
         Items[p] = "E0H";
      else if (Items[p] == "ACC.1")
         Items[p] = "E1H";
      else if (Items[p] == "ACC.2")
         Items[p] = "E2H";
      else if (Items[p] == "ACC.3")
         Items[p] = "E3H";
      else if (Items[p] == "ACC.4")
         Items[p] = "E4H";
      else if (Items[p] == "ACC.5")
         Items[p] = "E5H";
      else if (Items[p] == "ACC.6")
         Items[p] = "E6H";
      else if (Items[p] == "ACC.7")
         Items[p] = "E7H";
   }


znova:

   if (Items[i] == "")
   {
      // preskoci tento item
   }
   else if (Items[i] == "ORG")
   {
      // preskoci tento item
   }
   else if (Items[i] == "NOP")                            //--------NOP---------
   {
      program_hex[index] = 0x00;
      index++;
   }
   else if (Items[i] == "AJMP")                           //--------AJMP--------
   {
      INTCISLO = -3;
      if (SKOK(Items, first, INTCISLO, index))
      {
         if (INTCISLO > 255)
         {
            pom = INTCISLO;
            pom &= 0xE000;
            program_hex[index++] = (0x01 | pom);
            program_hex[index++] = (INTCISLO & 0x00FF);
         }
         else
         {
            program_hex[index++] = 0x01;
            program_hex[index++] = INTCISLO;
         }
      }
   }
   else if (Items[i] == "LJMP")                           //--------LJMP--------
   {
      INTCISLO = -2;
      if (DIRECT(Items, first, INTCISLO))
      {
         program_hex[index++] = 0x02;
         program_hex[index++] = (INTCISLO >> 8);
         program_hex[index++] = (INTCISLO & 0x00FF);
         //INTCISLO = -2;
      }

      else if (SKOK(Items, first, INTCISLO, index))
      {
         program_hex[index] = 0x02;
         index++;
         if (INTCISLO > 255)
         {
            pom = INTCISLO;
            pom >> 8;
            program_hex[index] = pom;
            index++;
            program_hex[index] = (INTCISLO & 0x00FF);
            index++;
         }
         else
         {
            program_hex[index] = 0;
            index++;
            program_hex[index] = INTCISLO;
            index++;
         }
      }
   }
   else if (Items[i] == "RR")                             //--------RR----------
   {
      if (Items[first] == "A")
         program_hex[index++] = 0x03;
      else
         Hlasenie_chyb(Items, i);
   }
   else if (Items[i] == "INC")                            //--------INC---------
   {
      if (Items[first] == "A")
      {
         program_hex[index] = 0x04;
         index++;
      }
      else if (DIRECT(Items, first, INTCISLO))
      {
         program_hex[index] = 0x05;
         index++;
         program_hex[index] = INTCISLO;
         index++;
      }
      else if (INDIRECT(Items, first, maska))
      {
         program_hex[index] = (0x06 | maska);
         index++;
      }
      else if (RN(Items, first, maska))
      {
         program_hex[index] = (0x08 | maska);
         index++;
      }
      else
         Hlasenie_chyb(Items, i);
   }                                                      //--------JBC---------
   else if (Items[i] == "JBC")
   {
      if (DIRECT(Items, first, INTCISLO))
      {
         program_hex[index] = 0x10;
         index++;
         DIRECT(Items, first, INTCISLO);
         program_hex[index] = INTCISLO;
         index++;
         SKOK(Items, second, INTCISLO, index+1);
         if (INTCISLO >= 0)
         {
         program_hex[index] = 256 - ((index+1) - INTCISLO);
            index++;
         }
         else   //dopredu
         {
            program_hex[index] = INTCISLO;
            index++;
         }

      }
      else
         Hlasenie_chyb(Items, i);
   }
   else if (Items[i] == "ACALL")                           //-------ACALL-------
   {
      INTCISLO = -3;
      if (SKOK(Items, first, INTCISLO, index))
      {
         if (INTCISLO > 255)
         {
            pom = INTCISLO;
            pom &= 0xE000;
            program_hex[index++] = (0x11 | pom);
            program_hex[index++] = (INTCISLO & 0x00FF);
         }
         else
         {
            program_hex[index++] = 0x11;
            program_hex[index++] = INTCISLO;
         }
      }
   }
   else if (Items[i] == "LCALL")                          //--------LCALL-------
   {
      INTCISLO = -2;
      if (SKOK(Items, first, INTCISLO, index))
      {
         program_hex[index] = 0x12;
         index++;
         if (INTCISLO > 255)
         {
            pom = INTCISLO;
            pom >> 8;
            program_hex[index] = pom;
            index++;
            program_hex[index] = (INTCISLO & 0x00FF);
            index++;
         }
         else
         {
            program_hex[index] = 0;
            index++;
            program_hex[index] = INTCISLO;
            index++;
         }
      }
   }
   else if (Items[i] == "RRC")                            //--------RRC---------
   {
      if (Items[first] == "A")
      {
         program_hex[index] = 0x13;
         index++;
      }
      else
         Hlasenie_chyb(Items, i);
   }
   else if (Items[i] == "DEC")                            //--------DEC---------
   {
      if (Items[first] == "A")
      {
         program_hex[index] = 0x14;
         index++;
      }
      else if (DIRECT(Items, first, INTCISLO))
      {
         program_hex[index] = 0x15;
         index++;
         program_hex[index] = INTCISLO;
         index++;
      }
      else if (INDIRECT(Items, first, maska))
      {
         program_hex[index] = (0x16 | maska);
         index++;
      }
      else if (RN(Items, first, maska))
      {
         program_hex[index] = (0x18 | maska);
         index++;
      }
      else
         Hlasenie_chyb(Items, i);
   }
   else if (Items[i] == "JB")                             //--------JB----------
   {
      if (DIRECT(Items, first, INTCISLO))
      {
         program_hex[index] = 0x20;
         index++;
         DIRECT(Items, first, INTCISLO);
         program_hex[index] = INTCISLO;
         index++;
         SKOK(Items, second, INTCISLO, index+1);
         if (INTCISLO >= 0)
         {
            program_hex[index] = 256 - ((index+1) - INTCISLO);
            index++;
         }
         else     //dopredu
         {
            program_hex[index] = INTCISLO;             // PRIPOCITAT 2 RESPEKTIVE ODCITAT
            index++;                                   // ALEBO VYNECHAT PO PRVY KRAT SKOK
         }                                             // ABY SA ZAPISAL PRAVY INDEX
      }
      else
         Hlasenie_chyb(Items, i);
   }
   else if (Items[i] == "RL")                             //--------RL----------
   {
      if (Items[first] == "A")
      {
         program_hex[index] = 0x23;
         index++;
      }
      else
      {
         Hlasenie_chyb(Items, i);
      }
   }
   else if (Items[i] == "ADD")                            //--------ADD---------
   {
      if (Items[first] == "A" && DATA(Items, second, INTCISLO))
      {
         program_hex[index] = 0x24;
         index++;
         program_hex[index] = INTCISLO;
         index++;
      }
      else if (Items[first] == "A" && DIRECT(Items, second, INTCISLO))
      {
         program_hex[index] = 0x25;
         index++;
         program_hex[index] = INTCISLO;
         index++;
      }
      else if (Items[first] == "A" && INDIRECT(Items, second, maska))
      {
         program_hex[index] = (0x26 | maska);
         index++;
      }
      else if (Items[first] == "A" && RN(Items, second, maska))
      {
         program_hex[index] = (0x28 | maska);
         index++;
      }
      else
         Hlasenie_chyb(Items, i);
   }
   else if (Items[i] == "JNB")                            //---------JNB--------
   {
      if (DIRECT(Items, first, INTCISLO))
      {
         program_hex[index] = 0x30;
         index++;
         DIRECT(Items, first, INTCISLO);
         program_hex[index] = INTCISLO;
         index++;
         SKOK(Items, second, INTCISLO, index+1);
         if (INTCISLO >= 0)
         {
            program_hex[index] = 256 - ((index+1) - INTCISLO);
            index++;
         }
         else     //dopredu
         {
            program_hex[index] = INTCISLO;
            index++;
         }
      }
      else
         Hlasenie_chyb(Items, i);
   }
   else if (Items[i] == "RETI")                           //--------RETI--------
   {
      program_hex[index] = 0x32;
      index++;
   }
   else if (Items[i] == "RET")                            //--------RET---------
   {
      program_hex[index] = 0x22;
      index++;
   }
   else if (Items[i] == "RLC")                            //--------RLC---------
   {
      if (Items[first] == "A")
      {
         program_hex[index] = 0x33;
         index++;
      }
      else
         Hlasenie_chyb(Items, i);
   }
   else if (Items[i] == "ADDC")                           //--------ADDC--------
   {
      if (Items[first] == "A" && DATA(Items, second, INTCISLO))
      {
         program_hex[index] = 0x34;
         index++;
         program_hex[index] = INTCISLO;
         index++;
      }
      else if (Items[first] == "A" && DIRECT(Items, second, INTCISLO))
      {
         program_hex[index] = 0x35;
         index++;
         program_hex[index] = INTCISLO;
         index++;
      }
      else if (Items[first] == "A" && INDIRECT(Items, second, maska))
      {
         program_hex[index] = (0x36 | maska);
         index++;
      }
      else if (Items[first] == "A" && RN(Items, second, maska))
      {
         program_hex[index] = (0x38 | maska);
         index++;
      }
      else
         Hlasenie_chyb(Items, i);
   }
   else if (Items[i] == "JC")                             //--------JC----------
   {
      program_hex[index] = 0x40;
      index++;
      SKOK(Items, first, INTCISLO, index+1);
      if (INTCISLO >= 0)
      {
         program_hex[index] = 256 - ((index+1) - INTCISLO);
         index++;
      }
      else     //dopredu
      {
         program_hex[index] = INTCISLO;
         index++;
      }
   }
   else if (Items[i] == "JNC")                            //--------JNC---------
   {
      program_hex[index] = 0x50;
      index++;
      SKOK(Items, first, INTCISLO, index+1);
      if (INTCISLO >= 0)
      {
         program_hex[index] = 256 - ((index+1) - INTCISLO);
         index++;
      }
      else     //dopredu
      {
         program_hex[index] = INTCISLO;
         index++;
      }

   }
   else if (Items[i] == "JZ")                             //--------JZ----------
   {
      program_hex[index] = 0x60;
      index++;
      SKOK(Items, first, INTCISLO, index+1);
      if (INTCISLO >= 0)
      {
         program_hex[index] = 256 - ((index+1) - INTCISLO);
         index++;
      }
      else     //dopredu
      {
          program_hex[index] = INTCISLO;
         index++;
      }

   }
   else if (Items[i] == "JNZ")                             //-------JNZ---------
   {
      program_hex[index] = 0x70;
      index++;
      SKOK(Items, first, INTCISLO, index+1);
      if (INTCISLO >= 0)
      {
         program_hex[index] = 256 - ((index+1) - INTCISLO);
         index++;
      }
      else     //dopredu
      {
          program_hex[index] = INTCISLO;
         index++;
      }

   }
   else if (Items[i] == "SJMP")                             //------SJMP--------
   {
      program_hex[index] = 0x80;
      index++;                                              //2 SKOKY DO PREDU
      SKOK(Items, first, INTCISLO, index);
      if (INTCISLO >= 0)
      {
         program_hex[index] = 256 - ((index+1) - INTCISLO);
         index++;
      }
      else     //dopredu
      {
         program_hex[index] = INTCISLO;
         index++;
      }
   }
   else if (Items[i] == "ORL")                            //--------ORL---------
   {
      if (DIRECT(Items, first, INTCISLO) && Items[first] == "A")
      {
         program_hex[index] = 0x42;
         index++;
         program_hex[index] = INTCISLO;
         index++;
      }
      else if (DIRECT(Items, first, INTCISLO) && DATA(Items, second, INTCISLO))
      {
         program_hex[index] = 0x43;
         index++;
         DIRECT(Items, first, INTCISLO);
         program_hex[index] = INTCISLO;
         index++;
         DATA(Items, second, INTCISLO);
         program_hex[index] = INTCISLO;
         index++;
      }
      else if (Items[first] == "A" && DATA(Items, second, INTCISLO))
      {
         program_hex[index] = 0x44;
         index++;
         program_hex[index] = INTCISLO;
         index++;
      }
      else if (Items[first] == "A" && DIRECT(Items, second, INTCISLO))
      {
         program_hex[index] = 0x45;
         index++;
         program_hex[index] = INTCISLO;
         index++;
      }
      else if (Items[first] == "A" && INDIRECT(Items, second, maska))
      {
         program_hex[index] = (0x46 | maska);
         index++;
      }
      else if (Items[first] == "A" && RN(Items, second, maska))
      {
         program_hex[index] = (0x48 | maska);
         index++;
      }
      else if (Items[first] == "C")                       //-----ORL_C_/BIT-----
      {
         if (Items[second][1] == '/')
         {
            Items[second][1] == '0';
            if (DIRECT(Items, second, INTCISLO))
            {
               program_hex[index] = 0xA0;
               index++;
               program_hex[index] = INTCISLO;
               index++;
            }
         }
         else
         {
            if (DIRECT(Items, second, INTCISLO))          //-----ORL_C_BIT------
            {
               program_hex[index] = 0x72;
               index++;
               program_hex[index] = INTCISLO;
               index++;
            }
         }
      }
      else
         Hlasenie_chyb(Items, i);
   }
   else if (Items[i] == "ANL")                            //--------ANL---------
   {
      if (DIRECT(Items, first, INTCISLO) && Items[first] == "A")
      {
         program_hex[index] = 0x52;
         index++;
         program_hex[index] = INTCISLO;
         index++;
      }
      else if (DIRECT(Items, first, INTCISLO) && DATA(Items, second, INTCISLO))
      {
         program_hex[index] = 0x53;
         index++;
         DIRECT(Items, first, INTCISLO);
         program_hex[index] = INTCISLO;
         index++;
         DATA(Items, second, INTCISLO);
         program_hex[index] = INTCISLO;
         index++;
      }
      else if (Items[first] == "A" && DATA(Items, second, INTCISLO))
      {
         program_hex[index] = 0x54;
         index++;
         program_hex[index] = INTCISLO;
         index++;
      }
      else if (Items[first] == "A" && DIRECT(Items, second, INTCISLO))
      {
         program_hex[index] = 0x55;
         index++;
         program_hex[index] = INTCISLO;
         index++;
      }
      else if (Items[first] == "A" && INDIRECT(Items, second, maska))
      {
         program_hex[index] = (0x56 | maska);
         index++;
      }
      else if (Items[first] == "A" && RN(Items, second, maska))
      {
         program_hex[index] = (0x58 | maska);
         index++;
      }
      else if (Items[first] == "C")                       //-----ANL_C_/BIT-----
      {
         if (Items[second][1] == '/')
         {
            Items[second][1] == '0';
            if (DIRECT(Items, second, INTCISLO))
            {
               program_hex[index] = 0xB0;
               index++;
               program_hex[index] = INTCISLO;
               index++;
            }
         }
         else
         {
            if (DIRECT(Items, second, INTCISLO))          //-----ANL_C_BIT------
            {
               program_hex[index] = 0x82;
               index++;
               program_hex[index] = INTCISLO;
               index++;
            }
         }
      }
      else
         Hlasenie_chyb(Items, i);
   }
   else if (Items[i] == "XRL")                            //--------XRL---------
   {
      if (DIRECT(Items, first, INTCISLO) && Items[first] == "A")
      {
         program_hex[index] = 0x62;
         index++;
         program_hex[index] = INTCISLO;
         index++;
      }
      else if (DIRECT(Items, first, INTCISLO) && DATA(Items, second, INTCISLO))
      {
         program_hex[index] = 0x63;
         index++;
         DIRECT(Items, first, INTCISLO);
         program_hex[index] = INTCISLO;
         index++;
         DATA(Items, second, INTCISLO);
         program_hex[index] = INTCISLO;
         index++;
      }
      else if (Items[first] == "A" && DATA(Items, second, INTCISLO))
      {
         program_hex[index] = 0x64;
         index++;
         program_hex[index] = INTCISLO;
         index++;
      }
      else if (Items[first] == "A" && DIRECT(Items, second, INTCISLO))
      {
         program_hex[index] = 0x65;
         index++;
         program_hex[index] = INTCISLO;
         index++;
      }
      else if (Items[first] == "A" && INDIRECT(Items, second, maska))
      {
         program_hex[index] = (0x66 | maska);
         index++;
      }
      else if (Items[first] == "A" && RN(Items, second, maska))
      {
         program_hex[index] = (0x68 | maska);
         index++;
      }
      else
         Hlasenie_chyb(Items, i);
   }
   else if (Items[i] == "JMP")                             //--------JMP--------
   {
      if (Items[second] == "@A+DPTR")
      {
         program_hex[index] = 0x73;
         index++;
      }
      else
         Hlasenie_chyb(Items, i);
   }
   else if (Items[i] == "MOVC")                            //--------MOVC-------
   {
      if (Items[first] == "A" && Items[second] == "@A+PC")
      {
         program_hex[index] == 0x83;
         index++;
      }
      else if (Items[first] == "A" && Items[second] == "@A+DPTR")
      {
         program_hex[index] == 0x93;
         index++;
      }
      else
         Hlasenie_chyb(Items, i);
   }
   else if (Items[i] == "DIV")                             //--------DIV--------
   {
      if (Items[first] == "AB")
      {
         program_hex[index] = 0x84;
         index++;
      }
      else
         Hlasenie_chyb(Items, i);
   }
   else if(Items[i] == "MOV")                              //--------MOV--------
   {
      if (Items[first] == "A" && DATA(Items, second, INTCISLO))
      {
         //Edit1->Text = "bavi";
         program_hex[index] = 0x74;
         index++;
         program_hex[index] = INTCISLO;
         index++;
      }
      else if (DIRECT(Items, first, INTCISLO) && DATA(Items, second, INTCISLO))
      {
         program_hex[index] = 0x75;
         index++;
         DIRECT(Items, first, INTCISLO);
         program_hex[index] = INTCISLO;
         index++;
         DATA(Items, second, INTCISLO);
         program_hex[index] = INTCISLO;
         index++;
      }
      else if (INDIRECT(Items, first, maska) && DATA(Items, second, INTCISLO))
      {
         INDIRECT(Items, first, maska);
         program_hex[index] = (0x76 | maska);
         index++;
         DATA(Items, second, INTCISLO);
         program_hex[index] = INTCISLO;
         index++;
      }
      else if (RN(Items, first, maska) && DATA(Items, second, INTCISLO))
      {
         RN(Items, first, maska);
         program_hex[index] = (0x78 | maska);
         index++;
         DATA(Items, second, INTCISLO);
         program_hex[index] = INTCISLO;
         index++;
      }
      else if (DIRECT(Items, first, INTCISLO) && DIRECT(Items, second, INTCISLO))
      {
         program_hex[index] = 0x85;
         index++;
         DIRECT(Items, first, INTCISLO);
         program_hex[index] = INTCISLO;
         index++;
         DIRECT(Items, second, INTCISLO);
         program_hex[index] = INTCISLO;
         index++;
      }
      else if (DIRECT(Items, first, INTCISLO) && INDIRECT(Items, second, maska))
      {
         INDIRECT(Items, second, maska);
         program_hex[index] = (0x86 | maska);
         index++;
         DIRECT(Items, first, INTCISLO);
         program_hex[index] = INTCISLO;
         index++;
      }
      else if (DIRECT(Items, first, INTCISLO) && RN(Items, second, maska))
      {
         RN(Items, second, maska);
         program_hex[index] = (0x88 | maska);
         index++;
         DIRECT(Items, first, INTCISLO);
         program_hex[index] = INTCISLO;
         index++;
      }
      else if (DIRECT(Items, first, INTCISLO) && Items[second] == "C")
      {
         program_hex[index] = 0x92;
         index++;
         program_hex[index] = INTCISLO;
         index++;
      }
      else if (Items[first] == "C" && DIRECT(Items, second, INTCISLO))
      {
         program_hex[index] = 0xA2;
         index++;
         program_hex[index] = INTCISLO;
         index++;
      }
      else if (INDIRECT(Items, first, maska) && DIRECT(Items, second, INTCISLO))
      {
         program_hex[index] = (0xA6 | maska);
         index++;
         program_hex[index] = INTCISLO;
         index++;
      }
      else if (RN(Items, first, maska) && DIRECT(Items, second, INTCISLO))
      {
         program_hex[index] = (0xA8 | maska);
         index++;
         program_hex[index] = maska;
         index++;
      }
      else if (Items[first] == "A" && DIRECT(Items, second, INTCISLO))
      {
         program_hex[index] = 0xE5;
         index++;
         program_hex[index] = INTCISLO;
         index++;
      }
      else if (Items[first] == "A" && INDIRECT(Items, second, maska))
      {
         program_hex[index] = (0xE6 | maska);
         index++;
      }
      else if (Items[first] == "A" && RN(Items, second, maska))
      {
        // Edit1->Text = "bavi";
         program_hex[index] = (0xE8 | maska);
         index++;
      }
      else if (DIRECT(Items, first, INTCISLO) && Items[second] == "A")
      {
         program_hex[index] = 0xF5;
         index++;
         program_hex[index] = INTCISLO;
         index++;
      }
      else if (INDIRECT(Items, first, maska) && Items[second] == "A")
      {
         program_hex[index] = (0xF6 | maska);
         index++;
      }
      else if (RN(Items, first, maska) && Items[second] == "A")
      {
         program_hex[index] = (0xF8 | maska);
         index++;
      }
      else if (Items[first] == "DPTR" && DATA(Items, second, INTCISLO))
      {
         program_hex[index++] = 0x90;
         program_hex[index++] = (byte)(INTCISLO >> 8);
         DATA(Items, second, INTCISLO);
         program_hex[index++] = INTCISLO & 0x00FF;
      }
      else
         Hlasenie_chyb(Items, i);
   }
   else if (Items[i] == "SUBB")                            //--------SUBB-------
   {
      if (Items[first] == "A" && DATA(Items, second, INTCISLO))
      {
         program_hex[index] = 0x94;
         index++;
         program_hex[index] = INTCISLO;
         index++;
      }
      else if (Items[first] == "A" && DIRECT(Items, second, INTCISLO))
      {
         program_hex[index] = 0x95;
         index++;
         program_hex[index] = INTCISLO;
         index++;
      }
      else if (Items[first] == "A" && INDIRECT(Items, second, maska))
      {
         program_hex[index] = (0x96 | maska);
         index++;
      }
      else if (Items[first] == "A" && RN(Items, second, maska))
      {
         program_hex[index] = (0x98 | maska);
         index++;
      }
      else
         Hlasenie_chyb(Items, i);
   }
   else if (Items[i] == "MUL")                             //--------MULL-------
   {
      if (Items[first] == "AB")
      {
         program_hex[index] = 0xA4;
         index++;
      }
      else
         Hlasenie_chyb(Items, i);
   }
   else if (Items[i] == "CPL")                             //--------CPL--------
   {
      if (DIRECT(Items, first, INTCISLO))
      {
         program_hex[index] = 0xB2;
         index++;
         program_hex[index] = INTCISLO;
         index++;
      }
      else if (Items[first] == "C")
      {
         program_hex[index] = 0xB3;
         index++;
      }
      else if (Items[first] == "A")
      {
         program_hex[index] = 0xF4;
         index++;
      }
      else
         Hlasenie_chyb(Items, i);
   }
   else if (Items[i] == "CJNE")                            //--------CJNE-------
   {
      if (Items[first] == "A" && DATA(Items, second, INTCISLO))
      {
         program_hex[index] = 0xB4;
         index++;
         program_hex[index] = INTCISLO;
         index++;
         SKOK(Items, third, INTCISLO, index+1);
         if (INTCISLO >= 0)
         {
            program_hex[index] = 256 - ((index+1) - INTCISLO);
            index++;
         }
         else     //dopredu
         {
            program_hex[index] = INTCISLO;
            index++;
         }
      }
      else if (Items[first] == "A" && DIRECT(Items, second, INTCISLO))
      {
         program_hex[index] = 0xB5;
         index++;
         program_hex[index] = INTCISLO;
         index++;
         SKOK(Items, third, INTCISLO, index+1);
         if (INTCISLO >= 0)
         {
         program_hex[index] = 256 - ((index+1) - INTCISLO);
            index++;
         }
         else     //dopredu
         {
            program_hex[index] = INTCISLO;
            index++;
         }
      }
      else if (INDIRECT(Items, first, maska) && DATA(Items, second, INTCISLO))
      {
         program_hex[index] = (0xB6 | maska);
         index++;
         program_hex[index] = INTCISLO;
         index++;
         SKOK(Items, third, INTCISLO, index+1);
         if (INTCISLO >= 0)
         {
            program_hex[index] = 256 - ((index+1) - INTCISLO);
            index++;
         }
         else     //dopredu
         {
            program_hex[index] = INTCISLO;
            index++;
         }
      }
      else if (RN(Items, first, maska) && DATA(Items, second, INTCISLO))
      {
         program_hex[index] = (0xB8 | maska);
         index++;
         program_hex[index] = INTCISLO;
         index++;
         SKOK(Items, third, INTCISLO, index+1);
         if (INTCISLO >= 0)
         {
            program_hex[index] = 256 - ((index+1) - INTCISLO);
            index++;
         }
         else     //dopredu
         {
            program_hex[index] = INTCISLO;
            index++;
         }
      }
      else
         Hlasenie_chyb(Items, i);
   }
   else if (Items[i] == "PUSH")                            //--------PUSH-------
   {
      if (DIRECT(Items, first, INTCISLO))
      {
         program_hex[index] = 0xC0;
         index++;
         program_hex[index] = INTCISLO;
         index++;
      }
      else
         Hlasenie_chyb(Items, i);
   }
   else if (Items[i] == "POP")
   {
      if (DIRECT(Items, first, INTCISLO))
      {
         program_hex[index] = 0xD0;
         index++;
         program_hex[index] = INTCISLO;
         index++;
      }
      else
         Hlasenie_chyb(Items, i);
   }
   else if (Items[i] == "CLR")                             //--------CLR--------
   {
      if (DIRECT(Items, first, INTCISLO))
      {
         program_hex[index] = 0xC2;
         index++;
         program_hex[index] = INTCISLO;
         index++;
      }
      else if (Items[first] == "C")
      {
         program_hex[index] = 0xC3;
         index++;
      }
      else if (Items[first] == "A")
      {
         program_hex[index] = 0xE4;
         index++;
      }
      else
         Hlasenie_chyb(Items, i);
   }
   else if (Items[i] == "SWAP")                            //--------SWAP-------
   {
      if (Items[first] == "A")
      {
         program_hex[index] = 0xC4;
         index++;
      }
      else
         Hlasenie_chyb(Items, i);
   }
   else if (Items[i] == "XCH")                             //--------XCH--------
   {
      if (Items[first] == "A" && DIRECT(Items, second, INTCISLO))
      {
         program_hex[index] = 0xC5;
         index++;
         program_hex[index] = INTCISLO;
         index++;
      }
      else if (Items[first] == "A" && INDIRECT(Items, second, maska))
      {
         program_hex[index] = (0xC6 | maska);
         index++;
      }
      else if (Items[first] == "A" && RN(Items, second, maska))
      {
         program_hex[index] = (0xC8 | maska);
         index++;
      }
      else
         Hlasenie_chyb(Items, i);
   }
   else if (Items[i] == "SETB")                             //-------SETB-------
   {
      if (DIRECT(Items, first, INTCISLO))
      {
         program_hex[index] = 0xD2;
         index++;
         program_hex[index] = INTCISLO;
         index++;
      }
      else if (Items[first] == "C")
      {
         program_hex[index] = 0xD3;
         index++;
      }
      else
         Hlasenie_chyb(Items, i);
   }
   else if (Items[i] == "XCHD")                             //-------XCHD-------
   {
      if (Items[first] == "A" && INDIRECT(Items, second, maska))
      {
         program_hex[index] = (0xD6 | maska);
         index++;
      }
      else
         Hlasenie_chyb(Items, i);
   }
   else if (Items[i] == "DJNZ")                             //-------DJNZ-------
   {
      if (DIRECT(Items, first, INTCISLO))
      {
         program_hex[index] = 0xD5;
         index++;
         program_hex[index] = INTCISLO;
         index++;
         SKOK(Items, second, INTCISLO, index+1);
         if (INTCISLO >= 0)
         {
            program_hex[index] = 256 - ((index+1) - INTCISLO);
            index++;
         }
         else     //dopredu
         {
            program_hex[index] = INTCISLO;
            index++;
         }
      }
      else if (RN(Items, first, maska))
      {
         program_hex[index] = (0xD8 | maska);
         index++;
         SKOK(Items, second, INTCISLO, index+1);
         if (INTCISLO >= 0)
         {
            program_hex[index] = 256 - ((index+1) - INTCISLO);
            index++;
         }
         else     //dopredu
         {
            program_hex[index] = INTCISLO;
            index++;
         }
      }
      else
         Hlasenie_chyb(Items, i);
   }
   else if (Items[i] == "MOVX")                             //-------MOVX-------
   {
      if (Items[first] == "A" && Items[second] == "@DPTR")
         program_hex[index++] = 0xE0;

      else if (Items[first] == "A" && INDIRECT(Items, second, maska))
      {
         program_hex[index] = (0xE2 | maska);
         index++;
      }
      else if (Items[first] == "@DPTR" && Items[second] == "A")
      {
         program_hex[index] = 0xF0;
         index++;
      }
      else if (INDIRECT(Items, first, maska) && Items[second] == "A")
      {

         program_hex[index] = (0xF2 | maska);
         index++;
      }
      else
         Hlasenie_chyb(Items, i);
   }
   else
   {
      if (i == 0)
      {
         for (int j = 0; j <= index_navestia; j++)      //skus dat iba "<"
         {
ine_navestie:
            if (navestia[j][0] == Items[i])
            {
               AnsiString pom[2];
               int pom2;
               pom[1] = navestia[j][1];
               pom2 = DecPrevodnik(pom, 1, pom[1].Length());
               for (int e = 0; e <= index; e++)
               {
                  if (program_hex[e] == pom2)
                  {
                  navestia[j][3] = 1;       //navestie bolo pouzite
                     if (navestia[j][2] == -2)      // LJMP LCALL
                     {
                        program_hex[e-1] = (index >> 8);
                        program_hex[e] = (index & 0x00FF);
                        navestia[j][1] = index;
                     }

                     if (navestia[j][2] == -3)      // AJMP ACALL
                     {
                        int pomp = index;
                        program_hex[e] = (index & 0x00FF);
                        pomp &= 0x0E000;
                        pomp = pomp >> 8;
                        program_hex[e-1] |= pomp;
                        navestia[j][1] = index;
                     }

                     if (navestia[j][2] == -1)
                     {
                        program_hex[e] = index - ((pom2*(-1))-10);
                        navestia[j][1] = index - ((pom2*(-1))-10);
                     }

                     for (int k = 0; k <= index; k++)
                        if (program_hex[k] < 0)
                        {
                           j++;
                           goto ine_navestie;

                        }
                     i++;
                     goto znova;
                  }
               }
            }
         }
         navestia[index_navestia][0] = Items[i];
         navestia[index_navestia][1] = index;
         index_navestia++;
         i++;
         goto znova;
      }
      if (i == 1)
      {
         navestia[index_navestia][0] = Items[i];
         navestia[index_navestia++][3] = 2;
      }
   }
}
//------------------------FUNKCIE-----------------------------------------------
//--------------------------RN--------------------------------------------------
bool __fastcall TForm1::RN(AnsiString Items[], int NumberItem, int &maska)
{
   if (Items[NumberItem] == "R0")
   {
      maska = 0x00;
      return true;
   }
   else if (Items[NumberItem] == "R1")
   {
      maska = 0x01;
      return true;
   }
   else if (Items[NumberItem] == "R2")
   {
      maska = 0x02;
      return true;
   }
   else if (Items[NumberItem] == "R3")
   {
      maska = 0x03;
      return true;
   }
   else if (Items[NumberItem] == "R4")
   {
      maska = 0x04;
      return true;
   }
   else if (Items[NumberItem] == "R5")
   {
      maska = 0x05;
      return true;
   }
   else if (Items[NumberItem] == "R6")
   {
      maska = 0x06;
      return true;
   }
   else if (Items[NumberItem] == "R7")
   {
      maska = 0x07;
      return true;
   }
   else
      return false;
}
//--------------------------------DATA------------------------------------------
bool __fastcall TForm1::DATA(AnsiString Items[], int NumberItem, int &INTCISLO)
{
   int dlzka;
   dlzka = Items[NumberItem].Length();
   if (Items[NumberItem][1] == '#')
   {
      Items[NumberItem][1] = '0';
      if (Items[NumberItem][dlzka] == 'H')
      {
         INTCISLO = Prevodnik(Items, NumberItem, dlzka);
         if (INTCISLO == -1)
            return false;

         Items[NumberItem][1] = '#';
         return true;
      }
      else if (Items[NumberItem][dlzka] == 'B')
      {
         INTCISLO = BinPrevodnik(Items, NumberItem, dlzka);
         if (INTCISLO == -1)
            return false;

         Items[NumberItem][1] = '#';
         return true;
      }
      else
      {
         INTCISLO = DecPrevodnik(Items, NumberItem, dlzka);
         if (INTCISLO == -1)
            return false;

         Items[NumberItem][1] = '#';
         return true;
      }
   }
   else
      return false;
}
//--------------------------------DIRECT----------------------------------------
bool __fastcall TForm1::DIRECT(AnsiString Items[], int NumberItem, int &INTCISLO)
{
   int dlzka;

   dlzka = Items[NumberItem].Length();
   if (dlzka == 0)   return false;
   if (Items[NumberItem] == "H" || Items[NumberItem] == "B")
      return false;

   if (Items[NumberItem][dlzka] == 'H')
   {
      INTCISLO = Prevodnik(Items, NumberItem, dlzka);
      if (INTCISLO == -1)
         return false;

      return true;
   }
   else if (Items[NumberItem][dlzka] == 'B')
   {
      INTCISLO = BinPrevodnik(Items, NumberItem, dlzka);
      if (INTCISLO == -1)
         return false;

      return true;
   }
   else
   {
      INTCISLO = DecPrevodnik(Items, NumberItem, dlzka);
      if (INTCISLO == -1)
         return false;

      return true;
   }
}
//--------------------------------INDIRECT--------------------------------------
bool __fastcall TForm1::INDIRECT(AnsiString Items[], int NumberItem, int &maska)
{
   if (Items[NumberItem] == "@R1")
   {
      maska = 0x01;
      return true;
   }
   else if (Items[NumberItem] == "@R0")
   {
      maska = 0x00;
      return true;
   }
   else
      return false;

}
//------------------------------HexPrevodnik------------------------------------
int __fastcall TForm1::Prevodnik(AnsiString Items[], int NumberItem, int dlzka)
{
   int nasobok = 1;
   int IntCislo = 0;

   for (int i = 1; i <= (dlzka-1); i++)
   {
      if (Items[NumberItem][dlzka - i] == '0')
         IntCislo += 0;
      else if (Items[NumberItem][dlzka - i] == '1')
         IntCislo += 1 * nasobok;
      else if (Items[NumberItem][dlzka - i] == '2')
         IntCislo += 2 * nasobok;
      else if (Items[NumberItem][dlzka - i] == '3')
         IntCislo += 3 * nasobok;
      else if (Items[NumberItem][dlzka - i] == '4')
         IntCislo += 4 * nasobok;
      else if (Items[NumberItem][dlzka - i] == '5')
         IntCislo += 5 * nasobok;
      else if (Items[NumberItem][dlzka - i] == '6')
         IntCislo += 6 * nasobok;
      else if (Items[NumberItem][dlzka - i] == '7')
         IntCislo += 7 * nasobok;
      else if (Items[NumberItem][dlzka - i] == '8')
         IntCislo += 8 * nasobok;
      else if (Items[NumberItem][dlzka - i] == '9')
         IntCislo += 9 * nasobok;
      else if (Items[NumberItem][dlzka - i] == 'A')
         IntCislo += 10 * nasobok;
      else if (Items[NumberItem][dlzka - i] == 'B')
         IntCislo += 11 * nasobok;
      else if (Items[NumberItem][dlzka - i] == 'C')
         IntCislo += 12 * nasobok;
      else if (Items[NumberItem][dlzka - i] == 'D')
         IntCislo += 13 * nasobok;
      else if (Items[NumberItem][dlzka - i] == 'E')
         IntCislo += 14 * nasobok;
      else if (Items[NumberItem][dlzka - i] == 'F')
         IntCislo += 15 * nasobok;
      else
        return -1;
      nasobok *= 16;
   }
   return IntCislo;
}
//-----------------------------BinPrevodnik-------------------------------------
int __fastcall TForm1::BinPrevodnik(AnsiString Items[], int NumberItem, int dlzka)
{
   int nasobok = 1;
   int IntCislo = 0;

   for (int i = 1; i <= (dlzka-1); i++)
   {
      if (Items[NumberItem][dlzka - i] == '0')
         IntCislo += 0;
      else if (Items[NumberItem][dlzka - i] == '1')
         IntCislo += 1 * nasobok;
      else
         return -1;
      nasobok *= 2;
   }
   return IntCislo;
}
//----------------------------------DecPrevodnik--------------------------------
int __fastcall TForm1::DecPrevodnik(AnsiString Items[], int NumberItem, int dlzka)
{
   int nasobok = 1;
   int IntCislo = 0;

   for (int i = 0; i <= (dlzka-1); i++)
   {
      if (Items[NumberItem][dlzka - i] == '0')
         IntCislo += 0;
      else if (Items[NumberItem][dlzka - i] == '1')
          IntCislo += 1 * nasobok;
      else if (Items[NumberItem][dlzka - i] == '2')
          IntCislo += 2 * nasobok;
      else if (Items[NumberItem][dlzka - i] == '3')
         IntCislo += 3 * nasobok;
      else if (Items[NumberItem][dlzka - i] == '4')
         IntCislo += 4 * nasobok;
      else if (Items[NumberItem][dlzka - i] == '5')
         IntCislo += 5 * nasobok;
      else if (Items[NumberItem][dlzka - i] == '6')
         IntCislo += 6 * nasobok;
      else if (Items[NumberItem][dlzka - i] == '7')
         IntCislo += 7 * nasobok;
      else if (Items[NumberItem][dlzka - i] == '8')
         IntCislo += 8 * nasobok;
      else if (Items[NumberItem][dlzka - i] == '9')
         IntCislo += 9 * nasobok;
      else if (Items[NumberItem][dlzka - i] == '-')
         IntCislo *= (-1);
      else
         return -1;
      nasobok *= 10;
   }
   return IntCislo;
}
//------------------------------------SKOK--------------------------------------
bool __fastcall TForm1::SKOK(AnsiString Items[], int NumberItem, int &INTCISLO, int index)
{
   AnsiString pom[2];
   //static int n = 301;

   for (int i = 0; i <= index_navestia; i++)
   {
      if (navestia[i][0] == Items[NumberItem])
      {
         pom[1] = navestia[i][1];
         if (pom[1][1] == '-')
            continue;
         INTCISLO = DecPrevodnik(pom, 1, pom[1].Length());
         navestia[i][3] = 1;
         return true;
      }
   }
   navestia[index_navestia][0] = Items[NumberItem];
   navestia[index_navestia][1] = (index + 10)*(-1);
   navestia[index_navestia][2] = -1;


   if (INTCISLO == -2)
      navestia[index_navestia][2] = -2;

   if (INTCISLO == -3)
      navestia[index_navestia][2] = -3;

   index_navestia++;
   INTCISLO = (index + 10)*(-1);
   return true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormShow(TObject *Sender)
{
   Trenazer->Show();
   Trenazer->Visible = false;
   Trenazer->Top = 10;
   Trenazer->Left = 10;
   Applic5->Show();
   Applic5->Visible = false;
   Applic5->Top = 40;
   Applic5->Left = 425;
   Aplic3->Show();
   Aplic3->Visible = false;
   Aplic3->Top = 10;
   Aplic3->Left = 425;
   About->Show();
   About->Visible = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Trenazer1Click(TObject *Sender)
{
   Trenazer->Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Applic31Click(TObject *Sender)
{
   Aplic3->Visible = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::App5Click(TObject *Sender)
{
   Applic5->Visible = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::About1Click(TObject *Sender)
{
   About->Visible = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Hlasenie_chyb(AnsiString Items[], int i)
{
   AnsiString chyba;

   chyba += "Chyba v inštrukcií:   ";
   chyba += Items[i];
   chyba += "   ";
   chyba += Items[first];
   chyba += "   ";
   chyba += Items[second];
   chyba += "     Nespravný parameter";
   Hlasenia->Lines->Add(chyba);
}

void __fastcall TForm1::Hlasenie_chyb_navestia(void)
{
   AnsiString chyba;
   for (int i = 0; i <= 99; i++)
   {
      chyba = "";
      if (navestia[i][1][1] == '-')
      {
         navestia[i][3] = 1;          // aby sa neovplyvnovali cybove hlasenia
         chyba += "Nezname navestie:   ";
         chyba += navestia[i][0];
         Hlasenia->Lines->Add(chyba);
      }
   }
   for (int i = 0; i < index_navestia; i++)
   {
      chyba = "";
      if ((navestia[i][3] == 0 && pouzite_navestia(i)) || navestia[i][3] == 2)
      {
         if (navestia[i][3] == 2 && navestia[i-1][3] == 0)
            continue;
         chyba += "Neznama inštrukcia:   ";
         chyba += navestia[i][0];
         Hlasenia->Lines->Add(chyba);
      }
   }
}
//---------------------------------------------------------------------------
bool __fastcall TForm1::pouzite_navestia(int i)
{
   for (int l = i - 1; l >= 0; l--)
   {
      if (navestia[i][0] == navestia[l][0] && navestia[l][3] == 1)
      {
         navestia[i][3] = 1;
         return false;
      }
   }
   return true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Ulo1Click(TObject *Sender)
{
   if (SaveDialog1->Execute())
      RichEdit1->Lines->SaveToFile(SaveDialog1->FileName);
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Naitaj1Click(TObject *Sender)
{
   if (OpenDialog1->Execute())
   {
      RichEdit1->Lines->LoadFromFile(OpenDialog1->FileName);
   }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Nov1Click(TObject *Sender)
{
   RichEdit1->Lines->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Exit1Click(TObject *Sender)
{
   Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Reset(void)
{
   Procesor_8051->Restart();
   Trenazer->Restart();
   Aplic3->Restart();
   Applic5->Restart();
}

