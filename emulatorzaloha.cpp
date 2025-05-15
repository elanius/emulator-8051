//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "emulator.h"
#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

#define first   (i + 1)
#define second  (i + 2)
TForm1 *Form1;

   int a = 0;
   int b = 0;
   int w = 0;
   int but[8] = {0, 0, 0, 0, 0, 0, 0, 0};
//   int k[8] = {0, 0, 0, 0, 0, 0, 0, 0};
//   int hex[4] = {0x01, 0x02, 0x04, 0x08};

typedef unsigned char byte;
typedef unsigned char REGISTRE;

C_Procesor Procesor_8051;

enum E_BIT_FLAGS
{
   E_BF_0 = 0x01,
   E_BF_1 = 0x02,
   E_BF_2 = 0x04,
   E_BF_3 = 0x08,
   E_BF_4 = 0x10,
   E_BF_5 = 0x20,
   E_BF_6 = 0x40,
   E_BF_7 = 0x80,
};

byte REGISTER_ACC = 0;

//REGISTER R0;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
   : TForm(Owner)
{
   Procesor_8051.init();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton1Click(TObject *Sender)
{
   Shape1->Brush->Color = clWhite;
   Shape2->Brush->Color = clWhite;
   Shape3->Brush->Color = clWhite;
   Shape4->Brush->Color = clWhite;
   Shape5->Brush->Color = clWhite;
   Shape6->Brush->Color = clWhite;
   Shape7->Brush->Color = clWhite;
   Shape8->Brush->Color = clWhite;


   for(int i = 0; i < RichEdit1->Lines->Count; i++)
   {
      str = RichEdit1->Lines->Strings[i];
      Label1->Caption = str;
      try
      {
//         a = str.ToInt();
      }
      catch(...)
      {
         Edit1->Text = "daco nebavi";
      }
   }

   a = 0;

   if (but[0])
      a |= E_BF_0;

   if (but[1])
      a |= E_BF_1;

   if (but[2])
      a |= 0x04;

   if (but[3])
      a |= 0x08;

   if (but[4])
      a |= 0x10;

   if (but[5])
      a |= 0x20;

   if (but[6])
      a |= 0x40;

   if (but[7])
      a |= 0x80;

   Label1->Caption = a;

//---------------------------------------------------------------------------
   w = a & 0x01;
   if (w)
      Shape1->Brush->Color = clLime;

   w = a & 0x02;
   if (w)
      Shape2->Brush->Color = clLime;

   w = a & 0x04;
   if (w)
      Shape3->Brush->Color = clLime;

   w = a & 0x08;
   if (w)
      Shape4->Brush->Color = clLime;

   w = a & 0x10;
   if (w)
      Shape5->Brush->Color = clLime;

   w = a & 0x20;
   if (w)
      Shape6->Brush->Color = clLime;

   w = a & 0x40;
   if (w)
      Shape7->Brush->Color = clLime;

   w = a & 0x80;
   if (w)
      Shape8->Brush->Color = clLime;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SpeedButton2Click(TObject *Sender)
{
   Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SPOnClick(TObject *Sender)
{

   int index = ((TSpeedButton *)Sender)->Tag;
   if (!but[index])
   {
      but[index] = 1;
      ((TSpeedButton *)Sender)->Caption = "1";
   }

   else if (but[index])
   {
      but[index] = 0;
      ((TSpeedButton *)Sender)->Caption = "0";
   }
}
//---------------------------------------------------------------------------

byte program[] = {0x00,0x10,0x34};


void __fastcall TForm1::SBRunClick(TObject *Sender)
{
   Procesor_8051.napal_program(program, sizeof(program), 0);
   Procesor_8051.start(0);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SBsaveClick(TObject *Sender)
{
   for(int i = 0; i < RichEdit1->Lines->Count; i++)
   {
      ProcesLine(RichEdit1->Lines->Strings[i]);
   }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ProcesLine(AnsiString &Line)
{
   AnsiString items[5];
   bool next = true;

   for(int i = 1, j = -1; i < Line.Length() + 1; i++)
   {
      if (Line[i] == ';' )
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

         items[j] += Line[i];
      }
   }

   ProcesItems(items);
}
//------------------------------------------------------------------------------
void __fastcall TForm1::ProcesItems(AnsiString Items[]/*, int NumOfItems*/)
{
   int i = 0;
   int maska = 0;
   int INTCISLO = 0;
   static AnsiString program_hex;

   if (Items[0][Items[0].Length()] == ':')
      i++;

   if (Items[i] == "NOP")                                 //--------NOP---------
      program_hex += 0x00;
   else if (Items[i] == "RR")                             //--------RR----------
   {
      if (Items[first] == "A")
         program_hex += 0x03;
   }
   else if (Items[i] == "INC")                            //--------INC---------
   {
      if (Items[first] == "A")
         program_hex += 0x04;
      else if (DIRECT(Items, first, INTCISLO))
      {
         program_hex += 0x05;
         program_hex += INTCISLO;
      }
      else if (INDIRECT(Items, first, maska))
         program_hex += (0x06 | maska);
      else if (RN(Items, first, maska))
         program_hex += (0x08 | maska);
   }
   else if (Items[i] == "RRC")                            //--------RRC---------
   {
      if (Items[first] == "A")
         program_hex += 0x13;
   }
   else if (Items[i] == "DEC")                            //--------DEC---------
   {
      if (Items[first] == "A")
         program_hex += 0x14;
      else if (DIRECT(Items, first, INTCISLO))
      {
         program_hex += 0x15;
         program_hex += INTCISLO;
      }
      else if (INDIRECT(Items, first, maska))
         program_hex += (0x16 | maska);
      else if (RN(Items, first, maska))
         program_hex += (0x18 | maska);
   }
   else if (Items[i] == "RL")                             //--------RL----------
   {
      if (Items[first] == "A")
         program_hex += 0x23;
   }
   else if (Items[i] == "ADD")                            //--------ADD---------
   {
      if (Items[first] == "A" && DATA(Items, second, INTCISLO))
      {
         program_hex += 0x24;
         program_hex += INTCISLO;
      }
      else if (Items[first] == "A" && DIRECT(Items, second, INTCISLO))
      {
         program_hex += 0x25;
         program_hex += INTCISLO;
      }
      else if (Items[first] == "A" && INDIRECT(Items, second, maska))
         program_hex += (0x26 | maska);
      else if (Items[first] == "A" && RN(Items, second, maska))
         program_hex += (0x28 | maska);
   }
   else if (Items[i] == "RLC")                            //--------RLC---------
   {
      if (Items[first] == "A")
         program_hex += 0x33;
   }
   else if (Items[i] == "ADDC")                           //--------ADDC--------
   {
      if (Items[first] == "A" && DATA(Items, second, INTCISLO))
      {
         program_hex += 0x34;
         program_hex += INTCISLO;
      }
      else if (Items[first] == "A" && DIRECT(Items, second, INTCISLO))
      {
         program_hex += 0x35;
         program_hex += INTCISLO;
      }
      else if (Items[first] == "A" && INDIRECT(Items, second, maska))
         program_hex += (0x36 | maska);
      else if (Items[first] == "A" && RN(Items, second, maska))
         program_hex += (0x38 | maska);
   }
   else if (Items[i] == "ORL")                            //--------ORL---------
   {
      if (DIRECT(Items, first, INTCISLO) && Items[first] == "A")
      {
         program_hex += 0x42;
         program_hex += INTCISLO;
      }
      else if (DIRECT(Items, first, INTCISLO) && DATA(Items, second, INTCISLO))
      {
         program_hex += 0x43;
         DIRECT(Items, first, INTCISLO);
         program_hex += INTCISLO;
         DATA(Items, second, INTCISLO);
         program_hex += INTCISLO;
      }
      else if (Items[first] == "A" && DATA(Items, second, INTCISLO))
      {
         program_hex += 0x44;
         program_hex += INTCISLO;
      }
      else if (Items[first] == "A" && DIRECT(Items, second, INTCISLO))
      {
         program_hex += 0x45;
         program_hex += INTCISLO;
      }
      else if (Items[first] == "A" && INDIRECT(Items, second, maska))
         program_hex += (0x46 | maska);
      else if (Items[first] == "A" && RN(Items, second, maska))
         program_hex += (0x48 | maska);
      else if (Items[first] == "C")                       //-----ORL_C_/BIT-----
      {
         if (Items[second][1] == '/')
         {
            Items[second][1] == '0';
            if (DIRECT(Items, second, INTCISLO))
            {                                             //---OTESTOVAT--------
               program_hex += 0xA0;
               program_hex += INTCISLO;
            }
         }
         else
         {
            if (DIRECT(Items, second, INTCISLO))          //-----ORL_C_BIT------
            {
               program_hex += 0x72;
               program_hex += INTCISLO;
            }
         }
      }
   }
   else if (Items[i] == "ANL")                            //--------ANL---------
   {
      if (DIRECT(Items, first, INTCISLO) && Items[first] == "A")
      {
         program_hex += 0x52;
         program_hex += INTCISLO;
      }
      else if (DIRECT(Items, first, INTCISLO) && DATA(Items, second, INTCISLO))
      {
         program_hex += 0x53;
         DIRECT(Items, first, INTCISLO);
         program_hex += INTCISLO;
         DATA(Items, second, INTCISLO);
         program_hex += INTCISLO;
      }
      else if (Items[first] == "A" && DATA(Items, second, INTCISLO))
      {
         program_hex += 0x54;
         program_hex += INTCISLO;
      }
      else if (Items[first] == "A" && DIRECT(Items, second, INTCISLO))
      {
         program_hex += 0x55;
         program_hex += INTCISLO;
      }
      else if (Items[first] == "A" && INDIRECT(Items, second, maska))
         program_hex += (0x56 | maska);
      else if (Items[first] == "A" && RN(Items, second, maska))
         program_hex += (0x58 | maska);
      else if (Items[first] == "C")                       //-----ANL_C_/BIT-----
      {
         if (Items[second][1] == '/')
         {
            Items[second][1] == '0';
            if (DIRECT(Items, second, INTCISLO))
            {                                             //---OTESTOVAT--------
               program_hex += 0xB0;
               program_hex += INTCISLO;
            }
         }
         else
         {
            if (DIRECT(Items, second, INTCISLO))          //-----ANL_C_BIT------
            {
               program_hex += 0x82;
               program_hex += INTCISLO;
            }
         }
      }
   }
   else if (Items[i] == "XRL")                            //--------XRL---------
   {
      if (DIRECT(Items, first, INTCISLO) && Items[first] == "A")
      {
         program_hex += 0x62;
         program_hex += INTCISLO;
      }
      else if (DIRECT(Items, first, INTCISLO) && DATA(Items, second, INTCISLO))
      {
         program_hex += 0x63;
         DIRECT(Items, first, INTCISLO);
         program_hex += INTCISLO;
         DATA(Items, second, INTCISLO);
         program_hex += INTCISLO;
      }
      else if (Items[first] == "A" && DATA(Items, second, INTCISLO))
      {
         program_hex += 0x64;
         program_hex += INTCISLO;
      }
      else if (Items[first] == "A" && DIRECT(Items, second, INTCISLO))
      {
         program_hex += 0x65;
         program_hex += INTCISLO;
      }
      else if (Items[first] == "A" && INDIRECT(Items, second, maska))
         program_hex += (0x66 | maska);
      else if (Items[first] == "A" && RN(Items, second, maska))
         program_hex += (0x68 | maska);
   }
   else if (Items[i] == "DIV")                             //--------DIV--------
   {
      if (Items[first] == "AB")
         program_hex += 0x84;
   }

   else if(Items[i] == "MOV")                              //--------MOV--------
   {
      if (Items[i + 1] == "A" && DATA(Items, second, INTCISLO))
      {
         Edit1->Text = "bavi";
         program_hex += 0x74;
         program_hex += INTCISLO;
         Lstr->Caption = INTCISLO;
      }
      else if (DIRECT(Items, first, INTCISLO) && DATA(Items, second, INTCISLO))
      {
         program_hex += 0x75;
         DIRECT(Items, first, INTCISLO);
         program_hex += INTCISLO;
         DATA(Items, second, INTCISLO);
         program_hex += INTCISLO;
      }
      else if (INDIRECT(Items, first, maska) && DATA(Items, second, INTCISLO))
      {
         INDIRECT(Items, first, maska);
         program_hex += (0x76 | maska);
         DATA(Items, second, INTCISLO);
         program_hex += INTCISLO;
      }
      else if (RN(Items, first, maska) && DATA(Items, second, INTCISLO))
      {
         RN(Items, first, maska);
         program_hex += (0x78 | maska);
         DATA(Items, second, INTCISLO);
         program_hex += INTCISLO;
      }
      else if (DIRECT(Items, first, INTCISLO) && DIRECT(Items, second, INTCISLO))
      {
         program_hex += 0x85;
         DIRECT(Items, first, INTCISLO);
         program_hex += INTCISLO;
         DIRECT(Items, second, INTCISLO);
         program_hex += INTCISLO;
      }
      else if (DIRECT(Items, first, INTCISLO) && INDIRECT(Items, second, maska))
      {
         INDIRECT(Items, second, maska);
         program_hex += (0x86 | maska);
         DIRECT(Items, first, INTCISLO);
         program_hex += INTCISLO;
      }
      else if (DIRECT(Items, first, INTCISLO) && RN(Items, second, maska))
      {
         RN(Items, second, maska);
         program_hex += (0x88 | maska);
         DIRECT(Items, first, INTCISLO);
         program_hex += INTCISLO;
      }
      else if (DIRECT(Items, first, INTCISLO) && Items[second] == "C")
      {
         program_hex = 0x92;
         program_hex = INTCISLO;
      }
      else if (Items[first] == "C" && DIRECT(Items, second, INTCISLO))
      {
         program_hex = 0xA2;
         program_hex = INTCISLO;
      }
      else if (INDIRECT(Items, first, maska) && DIRECT(Items, second, INTCISLO))
      {
         program_hex += (0xA6 | maska);
         program_hex += INTCISLO;
      }
      else if (RN(Items, first, maska) && DIRECT(Items, second, INTCISLO))
      {
         program_hex += (0xA8 | maska);
         program_hex += maska;
      }
      else if (Items[first] == "A" && DIRECT(Items, second, INTCISLO))
      {
         Edit1->Text = INTCISLO;
         program_hex += 0xE5;
         program_hex += INTCISLO;
      }
      else if (Items[first] == "A" && INDIRECT(Items, second, maska))
      {
         Lstr->Caption = maska;
         program_hex += (0xE6 | maska);
      }
      else if (Items[first] == "A" && RN(Items, second, maska))
      {
         Edit1->Text = "bavi";
         Lstr->Caption = maska;
         program_hex += (0xE8 | maska);
         Edit1->Text = program_hex;
      }
      else if (DIRECT(Items, first, INTCISLO) && Items[second] == "A")
      {
         program_hex += 0xF5;
         program_hex += INTCISLO;
      }
      else if (INDIRECT(Items, first, maska) && Items[second] == "A")
         program_hex += (0xF6 | maska);
      else if (RN(Items, first, maska) && Items[second] == "A")
         program_hex += (0xF8 | maska);
      else
         Edit1->Text = "nebavi";

   }
   else if (Items[i] == "SUBB")                            //--------SUBB-------
   {
      if (Items[first] == "A" && DATA(Items, second, INTCISLO))
      {
         program_hex += 0x94;
         program_hex += INTCISLO;
      }
      else if (Items[first] == "A" && DIRECT(Items, second, INTCISLO))
      {
         program_hex += 0x95;
         program_hex += INTCISLO;
      }
      else if (Items[first] == "A" && INDIRECT(Items, second, maska))
         program_hex += (0x96 | maska);
      else if (Items[first] == "A" && RN(Items, second, maska))
         program_hex += (0x98 | maska);
   }
   else if (Items[i] == "MUL")                             //--------MULL-------
   {
      if (Items[first] == "AB")
         program_hex += 0xA4;
   }
   else if (Items[i] == "CPL")                             //--------CPL--------
   {
      if (DIRECT(Items, first, INTCISLO))
      {
         program_hex += 0xB2;
         program_hex += INTCISLO;
      }
      else if (Items[first] == "C")
         program_hex += 0xB3;
      else if (Items[first] == "A")
         program_hex += 0xF4;
   }
   else if (Items[i] == "CJNE")                            //--------CJNE-------
   {                                                       //--Pridat-skok------
      if (Items[first] == "A" && DATA(Items, second, INTCISLO))
      {
         program_hex += 0xB4;
         program_hex += INTCISLO;
      }
      else if (Items[first] == "A" && DIRECT(Items, second, INTCISLO))
      {
         program_hex += 0xB5;
         program_hex += INTCISLO;
      }
      else if (Items[first] == "A" && INDIRECT(Items, second, maska))
         program_hex += (0xB6 | maska);
      else if (Items[first] == "A" && RN(Items, second, maska))
         program_hex += (0xB8 | maska);
   }
   else if (Items[i] == "CLR")                             //--------CLR--------
   {
      if (DIRECT(Items, first, INTCISLO))
      {
         program_hex += 0xC2;
         program_hex += INTCISLO;
      }
      else if (Items[first] == "C")
         program_hex += 0xC3;
      else if (Items[first] == "A")
         program_hex += 0xE4;
   }
   else if (Items[i] == "SWAP")                            //--------SWAP-------
   {
      if (Items[first] == "A")
         program_hex += 0xC4;
   }
   else if (Items[i] == "XCH")                             //--------XCH--------
   {
      if (Items[first] == "A" && DIRECT(Items, second, INTCISLO))
      {
         program_hex += 0xC5;
         program_hex += INTCISLO;
      }
      else if (Items[first] == "A" && INDIRECT(Items, second, maska))
         program_hex += (0xC6 | maska);
      else if (Items[first] == "A" && RN(Items, second, maska))
         program_hex += (0xC8 | maska);
   }
   else if (Items[i] == "SETB")                             //-------SETB-------
   {
      if (DIRECT(Items, first, INTCISLO))
      {
         program_hex += 0xD2;
         program_hex += INTCISLO;
      }
      else if (Items[first] == "C")
         program_hex += 0xD3;
   }
   else if (Items[i] == "XCHD")                             //-------XCHD-------
   {
      if (Items[first] == "A" && INDIRECT(Items, second, maska))
         program_hex += (0xD6 | maska);
   }
   else if (Items[i] == "DJNZ")                             //-------DJNZ-------
   {
      if (DIRECT(Items, first, INTCISLO))
      {
         program_hex += 0xD5;
         program_hex += INTCISLO;
         //program_hex += ADDRES;
      }
      else if (RN(Items, first, maska))
      {
         program_hex += (0xD8 | maska);
         //program_hex += ADDRES;
      }
   }
   else if (Items[i] == "MOVX")                             //-------MOVX-------
   {
      if (Items[first] == "A" && INDIRECT(Items, second, maska))
         program_hex += (0xE2 | maska);
      else if (Items[first] == "DPTR" && Items[second] == "A")
         program_hex += 0xF0;
      else if (INDIRECT(Items, first, maska) && Items[second] == "A")
         program_hex += (0xF2 | maska);
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
      else
         return -1;
      nasobok *= 10;
   }
   return IntCislo;
}

