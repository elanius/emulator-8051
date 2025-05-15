//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Global.h"
#include "emulator.h"
#include "C_ExternalDevices.h"
#include "Unit1.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#define cur_instr()     ROM[PC]
#define first_param()   ROM[PC + 1]
#define second_param()  ROM[PC + 2]

#define rel_param(x)    ROM[PC + (x)]

#define GET_N           0x07

//PO P1 P2 P3 IP IE TMOD TCON THO TLO TH1 TL1 SCON SBUF

#define A               RAM[0xE0]
#define B               RAM[0xF0]
#define SP              RAM[0x81]
#define S_P             RAM[0x81]

#define PSW             RAM[0xD0]
#define R               (RAM     + 8 * Rn_bank)
#define R0              RAM[0x00 + 8 * Rn_bank]
#define R1              RAM[0x01 + 8 * Rn_bank]
#define R2              RAM[0x02 + 8 * Rn_bank]
#define R3              RAM[0x03 + 8 * Rn_bank]
#define R4              RAM[0x04 + 8 * Rn_bank]
#define R5              RAM[0x05 + 8 * Rn_bank]
#define R6              RAM[0x06 + 8 * Rn_bank]
#define R7              RAM[0x07 + 8 * Rn_bank]

#define DPL             RAM[0x82]
#define DPH             RAM[0x83]

#define SET_DPTR(a)     ((DPL = a),(DPH = (a >> 8)))
#define GET_DPTR()      ((DPH << 8) | DPL)

#define nastav_C_1()    PSW |= E_7_BIT
#define nastav_C_0()    PSW &= ~E_7_BIT

//---------------------------------------------------------------------------
C_Procesor *Procesor_8051;
//---------------------------------------------------------------------------

void C_Procesor::init()
{
   PC = 0xFFFF;
   Rn_bank = 0;
   S_P = 0x07;


   instruction_set[0x00] = &NOP;
   instruction_set[0x01] = &AJMP;
   instruction_set[0x02] = &LJMP;
   instruction_set[0x03] = &RR_A;
   instruction_set[0x04] = &INC_A;
   instruction_set[0x05] = &INC_DIRECT;
   instruction_set[0x06] = &INC_INDIRECT;
   instruction_set[0x07] = &INC_INDIRECT;
   instruction_set[0x08] = &INC_RN;
   instruction_set[0x09] = &INC_RN;
   instruction_set[0x0A] = &INC_RN;
   instruction_set[0x0B] = &INC_RN;
   instruction_set[0x0C] = &INC_RN;
   instruction_set[0x0D] = &INC_RN;
   instruction_set[0x0E] = &INC_RN;
   instruction_set[0x0F] = &INC_RN;
   instruction_set[0x10] = &JBC;
   instruction_set[0x11] = &ACALL;
   instruction_set[0x12] = &LCALL;
   instruction_set[0x13] = &RRC_A;
   instruction_set[0x14] = &DEC_A;
   instruction_set[0x15] = &DEC_DIRECT;
   instruction_set[0x16] = &DEC_INDIRECT;
   instruction_set[0x17] = &DEC_INDIRECT;
   instruction_set[0x18] = &DEC_RN;
   instruction_set[0x19] = &DEC_RN;
   instruction_set[0x1A] = &DEC_RN;
   instruction_set[0x1B] = &DEC_RN;
   instruction_set[0x1C] = &DEC_RN;
   instruction_set[0x1D] = &DEC_RN;
   instruction_set[0x1E] = &DEC_RN;
   instruction_set[0x1F] = &DEC_RN;
   instruction_set[0x20] = &JB;
   instruction_set[0x21] = &AJMP;
   instruction_set[0x22] = &RET; //N
   instruction_set[0x23] = &RL_A;
   instruction_set[0x24] = &ADD_A_DATA;
   instruction_set[0x25] = &ADD_A_DIRECT;
   instruction_set[0x26] = &ADD_A_INDIRECT;
   instruction_set[0x27] = &ADD_A_INDIRECT;
   instruction_set[0x28] = &ADD_A_RN;
   instruction_set[0x29] = &ADD_A_RN;
   instruction_set[0x2A] = &ADD_A_RN;
   instruction_set[0x2B] = &ADD_A_RN;
   instruction_set[0x2C] = &ADD_A_RN;
   instruction_set[0x2D] = &ADD_A_RN;
   instruction_set[0x2E] = &ADD_A_RN;
   instruction_set[0x2F] = &ADD_A_RN;
   instruction_set[0x30] = &JNB;
   instruction_set[0x31] = &ACALL;
   instruction_set[0x32] = &RETI;                      //N
   instruction_set[0x33] = &RLC_A;
   instruction_set[0x34] = &ADDC_A_DATA;
   instruction_set[0x35] = &ADDC_A_DIRECT;
   instruction_set[0x36] = &ADDC_A_INDIRECT;
   instruction_set[0x37] = &ADDC_A_INDIRECT;
   instruction_set[0x38] = &ADDC_A_RN;
   instruction_set[0x39] = &ADDC_A_RN;
   instruction_set[0x3A] = &ADDC_A_RN;
   instruction_set[0x3B] = &ADDC_A_RN;
   instruction_set[0x3C] = &ADDC_A_RN;
   instruction_set[0x3D] = &ADDC_A_RN;
   instruction_set[0x3E] = &ADDC_A_RN;
   instruction_set[0x3F] = &ADDC_A_RN;
   instruction_set[0x40] = &JC;
   instruction_set[0x41] = &AJMP;
   instruction_set[0x42] = &ORL_DIRECT_A;
   instruction_set[0x43] = &ORL_DIRECT_DATA;
   instruction_set[0x44] = &ORL_A_DATA;
   instruction_set[0x45] = &ORL_A_DIRECT;
   instruction_set[0x46] = &ORL_A_INDIRECT;
   instruction_set[0x47] = &ORL_A_INDIRECT;
   instruction_set[0x48] = &ORL_A_RN;
   instruction_set[0x49] = &ORL_A_RN;
   instruction_set[0x4A] = &ORL_A_RN;
   instruction_set[0x4B] = &ORL_A_RN;
   instruction_set[0x4C] = &ORL_A_RN;
   instruction_set[0x4D] = &ORL_A_RN;
   instruction_set[0x4E] = &ORL_A_RN;
   instruction_set[0x4F] = &ORL_A_RN;
   instruction_set[0x50] = &JNC;
   instruction_set[0x51] = &ACALL;
   instruction_set[0x52] = &ANL_DIRECT_A;
   instruction_set[0x53] = &ANL_DIRECT_DATA;
   instruction_set[0x54] = &ANL_A_DATA;
   instruction_set[0x55] = &ANL_A_DIRECT;
   instruction_set[0x56] = &ANL_A_INDIRECT;
   instruction_set[0x57] = &ANL_A_INDIRECT;
   instruction_set[0x58] = &ANL_A_RN;
   instruction_set[0x59] = &ANL_A_RN;
   instruction_set[0x5A] = &ANL_A_RN;
   instruction_set[0x5B] = &ANL_A_RN;
   instruction_set[0x5C] = &ANL_A_RN;
   instruction_set[0x5D] = &ANL_A_RN;
   instruction_set[0x5E] = &ANL_A_RN;
   instruction_set[0x5F] = &ANL_A_RN;
   instruction_set[0x60] = &JZ;
   instruction_set[0x61] = &AJMP;
   instruction_set[0x62] = &XRL_DIRECT_A;
   instruction_set[0x63] = &XRL_DIRECT_DATA;
   instruction_set[0x64] = &XRL_A_DATA;
   instruction_set[0x65] = &XRL_A_DIRECT;
   instruction_set[0x66] = &XRL_A_INDIRECT;
   instruction_set[0x67] = &XRL_A_INDIRECT;
   instruction_set[0x68] = &XRL_A_RN;
   instruction_set[0x69] = &XRL_A_RN;
   instruction_set[0x6A] = &XRL_A_RN;
   instruction_set[0x6B] = &XRL_A_RN;
   instruction_set[0x6C] = &XRL_A_RN;
   instruction_set[0x6D] = &XRL_A_RN;
   instruction_set[0x6E] = &XRL_A_RN;
   instruction_set[0x6F] = &XRL_A_RN;
   instruction_set[0x70] = &JNZ;
   instruction_set[0x71] = &ACALL;
   instruction_set[0x72] = &ORL_C_BIT;
  // instruction_set[0x73] = &JMP_@A_+_DPTR;
   instruction_set[0x74] = &MOV_A_DATA;
   instruction_set[0x75] = &MOV_DIRECT_DATA;
   instruction_set[0x76] = &MOV_INDIRECT_DATA;
   instruction_set[0x77] = &MOV_INDIRECT_DATA;
   instruction_set[0x78] = &MOV_RN_DATA;
   instruction_set[0x79] = &MOV_RN_DATA;
   instruction_set[0x7A] = &MOV_RN_DATA;
   instruction_set[0x7B] = &MOV_RN_DATA;
   instruction_set[0x7C] = &MOV_RN_DATA;
   instruction_set[0x7D] = &MOV_RN_DATA;
   instruction_set[0x7E] = &MOV_RN_DATA;
   instruction_set[0x7F] = &MOV_RN_DATA;
   instruction_set[0x80] = &SJMP;
   instruction_set[0x81] = &AJMP;
   instruction_set[0x82] = &ANL_C_BIT;
//   instruction_set[0x83] = &MOVC_A_,_@A_+_PC;
   instruction_set[0x84] = &DIV_AB;
   instruction_set[0x85] = &MOV_DIRECT_DIRECT;
   instruction_set[0x86] = &MOV_DIRECT_INDIRECT;
   instruction_set[0x87] = &MOV_DIRECT_INDIRECT;
   instruction_set[0x88] = &MOV_DIRECT_RN;
   instruction_set[0x89] = &MOV_DIRECT_RN;
   instruction_set[0x8A] = &MOV_DIRECT_RN;
   instruction_set[0x8B] = &MOV_DIRECT_RN;
   instruction_set[0x8C] = &MOV_DIRECT_RN;
   instruction_set[0x8D] = &MOV_DIRECT_RN;
   instruction_set[0x8E] = &MOV_DIRECT_RN;
   instruction_set[0x8F] = &MOV_DIRECT_RN;
   instruction_set[0x90] = &MOV_DPTR_DATA;
   instruction_set[0x91] = &ACALL;
   instruction_set[0x92] = &MOV_BIT_C;
//   instruction_set[0x93] = &MOVC_A,@A+DPTR;
   instruction_set[0x94] = &SUBB_A_DATA;
   instruction_set[0x95] = &SUBB_A_DIRECT;
   instruction_set[0x96] = &SUBB_A_INDIRECT;
   instruction_set[0x97] = &SUBB_A_INDIRECT;
   instruction_set[0x98] = &SUBB_A_RN;
   instruction_set[0x99] = &SUBB_A_RN;
   instruction_set[0x9A] = &SUBB_A_RN;
   instruction_set[0x9B] = &SUBB_A_RN;
   instruction_set[0x9C] = &SUBB_A_RN;
   instruction_set[0x9D] = &SUBB_A_RN;
   instruction_set[0x9E] = &SUBB_A_RN;
   instruction_set[0x9F] = &SUBB_A_RN;
   instruction_set[0xA0] = &ORL_C_NEG_BIT;
   instruction_set[0xA1] = &AJMP;
   instruction_set[0xA2] = &MOV_C_BIT;
   instruction_set[0xA3] = &INC_DPTR;
   instruction_set[0xA4] = &MUL_AB;
//   instruction_set[0xA5] = &RESERVE;   <<<<<<<<
   instruction_set[0xA6] = &MOV_INDIREC_DIRECT;
   instruction_set[0xA7] = &MOV_INDIREC_DIRECT;
   instruction_set[0xA8] = &MOV_RN_DIRECT;
   instruction_set[0xA9] = &MOV_RN_DIRECT;
   instruction_set[0xAA] = &MOV_RN_DIRECT;
   instruction_set[0xAB] = &MOV_RN_DIRECT;
   instruction_set[0xAC] = &MOV_RN_DIRECT;
   instruction_set[0xAD] = &MOV_RN_DIRECT;
   instruction_set[0xAE] = &MOV_RN_DIRECT;
   instruction_set[0xAF] = &MOV_RN_DIRECT;
   instruction_set[0xB0] = &ANL_C_NEG_BIT;
   instruction_set[0xB1] = &ACALL;
   instruction_set[0xB2] = &CPL_BIT;
   instruction_set[0xB3] = &CPL_C;
   instruction_set[0xB4] = &CJNE_A_DATA;
   instruction_set[0xB5] = &CJNE_A_DIRECT;
   instruction_set[0xB6] = &CJNE_INDIRECT_DATA;
   instruction_set[0xB7] = &CJNE_INDIRECT_DATA;
   instruction_set[0xB8] = &CJNE_RN_DATA;
   instruction_set[0xB9] = &CJNE_RN_DATA;
   instruction_set[0xBA] = &CJNE_RN_DATA;
   instruction_set[0xBB] = &CJNE_RN_DATA;
   instruction_set[0xBC] = &CJNE_RN_DATA;
   instruction_set[0xBD] = &CJNE_RN_DATA;
   instruction_set[0xBE] = &CJNE_RN_DATA;
   instruction_set[0xBF] = &CJNE_RN_DATA;
   instruction_set[0xC0] = &PUSH;
   instruction_set[0xC1] = &AJMP;
   instruction_set[0xC2] = &CLR_BIT;
   instruction_set[0xC3] = &CLR_C;
   instruction_set[0xC4] = &SWAP_A;
   instruction_set[0xC5] = &XCH_A_DIRECT;
   instruction_set[0xC6] = &XCH_A_INDIRECT;
   instruction_set[0xC7] = &XCH_A_INDIRECT;
   instruction_set[0xC8] = &XCH_A_RN;
   instruction_set[0xC9] = &XCH_A_RN;
   instruction_set[0xCA] = &XCH_A_RN;
   instruction_set[0xCB] = &XCH_A_RN;
   instruction_set[0xCC] = &XCH_A_RN;
   instruction_set[0xCD] = &XCH_A_RN;
   instruction_set[0xCE] = &XCH_A_RN;
   instruction_set[0xCF] = &XCH_A_RN;
   instruction_set[0xD0] = &POP;
   instruction_set[0xD1] = &ACALL;
   instruction_set[0xD2] = &SETB_BIT;
   instruction_set[0xD3] = &SETB_C;
// instruction_set[0xD4] = &DA_A;
   instruction_set[0xD5] = &DJNZ_DIRECT_ADDRES;
   instruction_set[0xD6] = &XCHD_A_INDIRECT;
   instruction_set[0xD7] = &XCHD_A_INDIRECT;
   instruction_set[0xD8] = &DJNZ_RN_ADDRES;
   instruction_set[0xD9] = &DJNZ_RN_ADDRES;
   instruction_set[0xDA] = &DJNZ_RN_ADDRES;
   instruction_set[0xDB] = &DJNZ_RN_ADDRES;
   instruction_set[0xDC] = &DJNZ_RN_ADDRES;
   instruction_set[0xDD] = &DJNZ_RN_ADDRES;
   instruction_set[0xDE] = &DJNZ_RN_ADDRES;
   instruction_set[0xDF] = &DJNZ_RN_ADDRES;
   instruction_set[0xE0] = &MOVX_A_DPTR;
   instruction_set[0xE1] = &AJMP;
//   instruction_set[0xE2] = &MOVX_A_INDIRECT;
//   instruction_set[0xE3] = &MOVX_A_INDIRECT;
   instruction_set[0xE4] = &CLR_A;
   instruction_set[0xE5] = &MOV_A_DIRECT;
   instruction_set[0xE6] = &MOV_A_INDIRECT;
   instruction_set[0xE7] = &MOV_A_INDIRECT;
   instruction_set[0xE8] = &MOV_A_RN;
   instruction_set[0xE9] = &MOV_A_RN;
   instruction_set[0xEA] = &MOV_A_RN;
   instruction_set[0xEB] = &MOV_A_RN;
   instruction_set[0xEC] = &MOV_A_RN;
   instruction_set[0xED] = &MOV_A_RN;
   instruction_set[0xEE] = &MOV_A_RN;
   instruction_set[0xEF] = &MOV_A_RN;
   instruction_set[0xF0] = &MOVX_DPTR_A;
   instruction_set[0xF1] = &ACALL;
//   instruction_set[0xF2] = &MOVX_INDIRECT_A;
//   instruction_set[0xF3] = &MOVX_INDIRECT_A;
   instruction_set[0xF4] = &CPL_A;
   instruction_set[0xF5] = &MOV_DIRECT_A;
   instruction_set[0xF6] = &MOV_INDIRECT_A;
   instruction_set[0xF7] = &MOV_INDIRECT_A;
   instruction_set[0xF8] = &MOV_RN_A;
   instruction_set[0xF9] = &MOV_RN_A;
   instruction_set[0xFA] = &MOV_RN_A;
   instruction_set[0xFB] = &MOV_RN_A;
   instruction_set[0xFC] = &MOV_RN_A;
   instruction_set[0xFD] = &MOV_RN_A;
   instruction_set[0xFE] = &MOV_RN_A;
   instruction_set[0xFF] = &MOV_RN_A;
}

void __fastcall C_Procesor::Tick()
{
   if(PC == 0x2003 || PC == 0xFFFF)
      return;

   instruction_set[cur_instr()]();  //Jednoducho povedané sa zavolá ta funkcia,
                                    //ktorej adresa je v poli instruction_set s
   static int pocet = 0;            //indexom, ktorı sa rovná hodnote inštrukcii
   if (pocet++ == 1000)
   {
      Obnov_registre();
      pocet = 0;
   }
}

void __fastcall C_Procesor::start(int start_from)
{
   PC = start_from;
}


void __fastcall C_Procesor::napal_program(Byte _Program[], int size, int _StartAdrres)
{
   memcpy(&ROM[_StartAdrres], _Program, size);
}

//----------------------INSTRUKCNA-SADA----------------------------------------
void __fastcall C_Procesor::NOP(void)
{
   PC++;
   m_OscPeriod = 12;
}
void __fastcall C_Procesor::AJMP(void)
{
   word addres = 0;
   addres = ROM[PC];
   addres <<= 3;
   addres &= 0xFF00;
   addres |= first_param();
   addres &= 0x07FF;

   PC+=2;
   PC &= 0xf800;
   PC |= addres;
   m_OscPeriod = 24;

/*   word addres = ROM[PC];
   addres <<= 8;
   addres |= first_param();
   addres &= 0xE0FF;
   PC += 2;
   PC &= 0xF800;
   PC |= addres;    */
}
void __fastcall C_Procesor::LJMP(void)
{
   word addres = 0;
   addres |= first_param();
   addres <<= 8;
   addres |= second_param();
   PC = addres;
   m_OscPeriod = 24;
}
void __fastcall C_Procesor::RR_A(void)
{
   bool jeden_bit;
   jeden_bit = (A & E_0_BIT);
   A >>= 1;

   if(jeden_bit)
      A |= E_7_BIT;
   else
      A &= ~E_7_BIT;


   PC++;
   m_OscPeriod = 12;
}
void __fastcall C_Procesor::INC_A(void)
{
   A++;
   PC++;
   m_OscPeriod = 12;

}
void __fastcall C_Procesor::INC_DIRECT(void)
{
   int direct = first_param();
   RAM[direct]++;
   PC += 2;
   m_OscPeriod = 12;

}
void __fastcall C_Procesor::INC_INDIRECT(void)
{
   if(cur_instr() & E_0_BIT)
      RAM[R1]++;
   else
      RAM[R0]++;

   PC++;
   m_OscPeriod = 12;
}
void __fastcall C_Procesor::INC_RN(void)
{
   int n = cur_instr() & GET_N;
   R[n]++;
   PC++;
   m_OscPeriod = 12;
}
void __fastcall C_Procesor::JBC(void)
{
   PC += 3;
//   if (first_param() >= 0x80)
   if (rel_param(-2) >= 0x80)
   {
//      byte byte_addres = (first_param() & 0xF8);
//      byte bit_addres  = (first_param() & 0x07);
      byte byte_addres = (rel_param(-2) & 0xF8);
      byte bit_addres  = (rel_param(-2) & 0x07);
      byte cislo = 1 << bit_addres;
      byte _byte = RAM[byte_addres];
      _byte &= cislo;

      if (_byte)
      {
         RAM[byte_addres] &= ~cislo;
         //PC += second_param();
         PC += ((signed char)rel_param(-1));
      }
   }
   else
   {
//      byte byte_addres = (first_param() >> 3) + 0x20;
//      byte bit_addres  = (first_param() & 0x07);
      byte byte_addres = (rel_param(-2) >> 3) + 0x20;
      byte bit_addres  = (rel_param(-2) & 0x07);
      byte cislo = 1 << bit_addres;
      byte _byte = RAM[byte_addres];
      _byte &= cislo;

      if (_byte)
      {
         RAM[byte_addres] &= ~cislo;
         //PC += second_param();
         PC += ((signed char)rel_param(-1));
      }
   }
   m_OscPeriod = 24;
}
void __fastcall C_Procesor::ACALL(void)
{
   PC += 2;
   word _pc = PC;
   word page_addres = 0;
   S_P++;
   RAM[S_P] = _pc & 0x00FF;
   S_P++;
   _pc = PC;
   RAM[S_P] = _pc >> 8;
   page_addres = rel_param(-2) & 0xE0;
   page_addres << 3;
   page_addres |= rel_param(-1);
   PC |= page_addres;
   m_OscPeriod = 24;
}
void __fastcall C_Procesor::LCALL(void)
{
   PC += 3;
   word _pc = PC;
   word addres = 0;
   S_P++;
   RAM[S_P] = _pc & 0x00FF;
   S_P++;
   _pc = PC;
   RAM[S_P] = _pc >> 8;
   addres |= rel_param(-2);
   addres << 8;
   addres |= rel_param(-1);
   PC = addres;
   m_OscPeriod = 24;
}
void __fastcall C_Procesor::RRC_A(void)
{
   bool jeden_bit_C = RAM[0xD0] & E_7_BIT;
   word  pom = A;
   A >>= 1;

   if (jeden_bit_C)
      A |= E_7_BIT;
   else
      A &= ~E_7_BIT;

   jeden_bit_C = pom & E_0_BIT;
   if (jeden_bit_C)
      RAM[0xD0] |= E_7_BIT;
   else
      RAM[0xD0] &= ~E_7_BIT;
   PC++;
   m_OscPeriod = 12;
}
void __fastcall C_Procesor::DEC_A(void)
{
   A--;
   PC++;
   m_OscPeriod = 12;
}
void __fastcall C_Procesor::DEC_DIRECT(void)
{
   int direct = first_param();
   RAM[direct]--;
   PC += 2;
   m_OscPeriod = 12;

}
void __fastcall C_Procesor::DEC_INDIRECT(void)
{
   if(cur_instr() & E_0_BIT)
      RAM[R1]--;
   else
      RAM[R0]--;

   PC++;
   m_OscPeriod = 12;
}
void __fastcall C_Procesor::DEC_RN(void)
{
   int n = cur_instr() & GET_N;
   R[n]--;
   PC++;
   m_OscPeriod = 12;
}
void __fastcall C_Procesor::JB(void)
{
   PC += 3;
//   if(first_param() >= 0x80)
   if(rel_param(-2) >= 0x80)
   {
//      byte byte_addres = (first_param() & 0xF8);
//      byte bit_addres  = (first_param() & 0x07);
      byte byte_addres = (rel_param(-2) & 0xF8);
      byte bit_addres  = (rel_param(-2) & 0x07);
      byte cislo = 1 << bit_addres;
      if (RAM[byte_addres] & cislo)
         //PC += second_param();
         PC += ((signed char)rel_param(-1));
   }
   else
   {
//      byte byte_addres = (first_param() >> 3) + 0x20;
//      byte bit_addres  = (first_param() & 0x07);
      byte byte_addres = (rel_param(-2) >> 3) + 0x20;
      byte bit_addres  = (rel_param(-2) & 0x07);
      byte cislo = 1 << bit_addres;
      if (RAM[byte_addres] & cislo)
         //PC += second_param();
         PC += ((signed char)rel_param(-1));
   }
   m_OscPeriod = 12;
}
void __fastcall C_Procesor::RET(void)
{
   PC = RAM[S_P] << 8;
   S_P--;
   PC |= RAM[S_P];
   S_P--;
   m_OscPeriod = 24;
}
void __fastcall C_Procesor::RL_A(void)
{
   bool jeden_bit;
   jeden_bit = (A & E_7_BIT);
   A <<= 1;

   if(jeden_bit)
      A |= E_0_BIT;
   else
      A &= ~E_0_BIT;


   PC++;
   m_OscPeriod = 12;

}
void __fastcall C_Procesor::ADD_A_DATA(void)
{
   A += first_param();
   PC += 2;
   m_OscPeriod = 12;
}
void __fastcall C_Procesor::ADD_A_DIRECT(void)
{
   A += RAM[first_param()];
   PC += 2;
   m_OscPeriod = 12;
}
void __fastcall C_Procesor::ADD_A_INDIRECT(void)
{
   if (cur_instr() & E_0_BIT)
      A += RAM[R1];
   else
      A += RAM[R0];

   PC++;
   m_OscPeriod = 12;
}
void __fastcall C_Procesor::ADD_A_RN(void)
{
   int n = cur_instr() & GET_N;
   A += R[n];
   PC++;
   m_OscPeriod = 12;
}
void __fastcall C_Procesor::JNB(void)
{
   PC += 3;
//   if(first_param() >= 0x80)
   if(rel_param(-2) >= 0x80)
   {
//      byte byte_addres = (first_param() & 0xF8);
//      byte bit_addres  = (first_param() & 0x07);
      byte byte_addres = (rel_param(-2) & 0xF8);
      byte bit_addres  = (rel_param(-2) & 0x07);
      byte cislo = 1 << bit_addres;
      if (!(RAM[byte_addres] & cislo))
//         PC += second_param();
         PC += ((signed char)rel_param(-1));
   }
   else
   {
//      byte byte_addres = (first_param() >> 3) + 0x20;
//      byte bit_addres  = (first_param() & 0x07);
      byte byte_addres = (rel_param(-2) >> 3) + 0x20;
      byte bit_addres  = (rel_param(-2) & 0x07);
      byte cislo = 1 << bit_addres;
      if (!(RAM[byte_addres] & cislo))
//         PC += second_param();
         PC += ((signed char)rel_param(-1));
   }
   m_OscPeriod = 12;
}
void __fastcall C_Procesor::RETI(void)
{
   PC = RAM[SP] << 8;
   S_P--;
   PC |= RAM[SP];                            //zmenit SP na S_P
   S_P--;
   m_OscPeriod = 24;
}
void __fastcall C_Procesor::RLC_A(void)
{
   bool jeden_bit_C = RAM[0xD0] & E_7_BIT;
   word  pom = A;
   A <<= 1;

   if (jeden_bit_C)
      A |= E_0_BIT;
   else
      A &= ~E_0_BIT;

   jeden_bit_C = pom & E_7_BIT;
   if (jeden_bit_C)
      RAM[0xD0] |= E_7_BIT;
   else
      RAM[0xD0] &= ~E_7_BIT;
   PC++;
   m_OscPeriod = 12;
}
//-----------------------ADDC-A-?-----------------------
void __fastcall C_Procesor::ADDC_A_DATA(void)
{
   bool _C = zisti_C();
   A += _C + first_param();
   PC += 2;
   m_OscPeriod = 12;
}
void __fastcall C_Procesor::ADDC_A_DIRECT(void)
{
   bool _C = zisti_C();
   A += _C + RAM[first_param()];
   PC += 2;
   m_OscPeriod = 12;
}
void __fastcall C_Procesor::ADDC_A_INDIRECT(void)
{
   bool _C = zisti_C();
   if (cur_instr() & E_0_BIT)
      A += _C + RAM[R1];
   else
      A += _C + RAM[R0];

   PC++;
   m_OscPeriod = 12;
}
void __fastcall C_Procesor::ADDC_A_RN(void)
{
   bool _C = zisti_C();
   int n = cur_instr() & GET_N;
   A += _C + R[n];
   PC++;
   m_OscPeriod = 12;
}
void __fastcall C_Procesor::JC(void)
{
   PC += 2;
   if (zisti_C())
      //PC += first_param();
      PC += ((signed char)rel_param(-1));
   m_OscPeriod = 24;
}

//--------------------------ORL-----------------
void __fastcall C_Procesor::ORL_DIRECT_A(void)
{
   RAM[first_param()] |= A;
   PC += 2;
   m_OscPeriod = 12;
}
void __fastcall C_Procesor::ORL_DIRECT_DATA(void)
{
   RAM[first_param()] |= second_param();
   PC += 3;
   m_OscPeriod = 24;
}
void __fastcall C_Procesor::ORL_A_DATA(void)
{
   A |= first_param();
   PC += 2;
   m_OscPeriod = 12;
}
void __fastcall C_Procesor::ORL_A_DIRECT(void)
{
   A |= RAM[first_param()];
   PC += 2;
   m_OscPeriod = 12;
}
void __fastcall C_Procesor::ORL_A_INDIRECT(void)
{
   if (cur_instr() & E_0_BIT)
      A |= RAM[R1];
   else
      A |= RAM[R0];

   PC++;
   m_OscPeriod = 12;
}
void __fastcall C_Procesor::ORL_A_RN(void)
{
   int n = cur_instr() & GET_N;
   A |= R[n];
   PC++;
   m_OscPeriod = 12;
}
void __fastcall C_Procesor::JNC(void)
{
   PC += 2;
   if (zisti_C() == 0)
      //PC += first_param();
      PC += ((signed char)rel_param(-1));
   m_OscPeriod = 24;
}
void __fastcall C_Procesor::ANL_DIRECT_A(void)
{
   RAM[first_param()] &= A;
   PC += 2;
   m_OscPeriod = 12;
}
void __fastcall C_Procesor::ANL_DIRECT_DATA(void)
{
   RAM[first_param()] &= second_param();
   PC += 3;
   m_OscPeriod = 24;
}
void __fastcall C_Procesor::ANL_A_DATA(void)
{
   A &= first_param();
   PC += 2;
   m_OscPeriod = 12;
}
void __fastcall C_Procesor::ANL_A_DIRECT(void)
{
   A &= RAM[first_param()];
   PC += 2;
   m_OscPeriod = 12;
}
void __fastcall C_Procesor::ANL_A_INDIRECT(void)
{
   if (cur_instr() & E_0_BIT)
      A &= RAM[R1];
   else
      A &= RAM[R0];

   PC++;
   m_OscPeriod = 12;
}
void __fastcall C_Procesor::ANL_A_RN(void)
{
   int n = cur_instr() & GET_N;
   A &= R[n];
   PC++;
   m_OscPeriod = 12;
}
void __fastcall C_Procesor::JZ(void)
{
   PC += 2;
   if (A == 0)
      //PC += first_param();
      PC += ((signed char)rel_param(-1));
   m_OscPeriod = 24;
}
//------------------XRL------------------------------
void __fastcall C_Procesor::XRL_DIRECT_A(void)
{
   RAM[first_param()] ^= A;
   PC += 2;
   m_OscPeriod = 12;
}
void __fastcall C_Procesor::XRL_DIRECT_DATA(void)
{
   RAM[first_param()] ^= second_param();
   PC += 3;
   m_OscPeriod = 24;
}
void __fastcall C_Procesor::XRL_A_DATA(void)
{
   A ^= first_param();
   PC += 2;
   m_OscPeriod = 12;
}
void __fastcall C_Procesor::XRL_A_DIRECT(void)
{
   A ^= RAM[first_param()];
   PC += 2;
   m_OscPeriod = 12;

}
void __fastcall C_Procesor::XRL_A_INDIRECT(void)
{
   if (cur_instr() & E_0_BIT)
      A ^= RAM[R1];
   else
      A ^= RAM[R0];

   PC++;
   m_OscPeriod = 12;

}
void __fastcall C_Procesor::XRL_A_RN(void)
{
   int n = cur_instr() & GET_N;
   A ^= R[n];
   PC++;
   m_OscPeriod = 12;
}
void __fastcall C_Procesor::JNZ(void)
{
   PC += 2;
   if (A != 0)
      //PC += first_param();
      PC += ((signed char)rel_param(-1));
   m_OscPeriod = 24;
}
void __fastcall C_Procesor::ORL_C_BIT(void)
{
   bool bit;
   if(first_param() >= 0x80)
   {
      byte byte_addres = (first_param() & 0xF8);
      byte bit_addres  = (first_param() & 0x07);
      byte cislo = 1 << bit_addres;
      if (RAM[byte_addres] & cislo)
         bit = 1;
      else
         bit = 0;
   }
   else
   {
      byte byte_addres = (first_param() >> 3) + 0x20;
      byte bit_addres  = (first_param() & 0x07);
      byte cislo = 1 << bit_addres;
      if (RAM[byte_addres] & cislo)
         bit = 1;
      else
         bit = 0;
   }
   if (bit)
      RAM[0xD0] |= E_7_BIT;
   PC += 2;
   m_OscPeriod = 24;
}
//-------------------MOV_?_DATA--------------------------
void __fastcall C_Procesor::MOV_A_DATA(void)
{
   A = first_param();
   PC += 2;
   m_OscPeriod = 12;
}
void __fastcall C_Procesor::MOV_DIRECT_DATA(void)
{
   RAM[first_param()] = second_param();
   PC += 3;
   m_OscPeriod = 24;
}
void __fastcall C_Procesor::MOV_INDIRECT_DATA(void)
{
   if (cur_instr() & E_0_BIT)
      RAM[R1] = first_param();
   else
      RAM[R0] = first_param();

   PC += 2;
   m_OscPeriod = 12;
}
void __fastcall C_Procesor::MOV_RN_DATA(void)
{
   int n = cur_instr() & GET_N;
   R[n] = first_param();
   PC += 2;
   m_OscPeriod = 12;

}
void __fastcall C_Procesor::SJMP(void)                          //-----SJMP-----
{
   //PC += 2;
   //PC += -7;

//   byte value1 = first_param();
//   char value2 = (signed char)value1;

   PC += (2 +  (signed char)first_param());
   m_OscPeriod = 24;
}
void __fastcall C_Procesor::ANL_C_BIT(void)
{
   bool bit;
   if(first_param() >= 0x80)
   {
      byte byte_addres = (first_param() & 0xF8);
      byte bit_addres  = (first_param() & 0x07);
      byte cislo = 1 << bit_addres;
      if (RAM[byte_addres] & cislo)
         bit = 1;
      else
         bit = 0;
   }
   else
   {
      byte byte_addres = (first_param() >> 3) + 0x20;
      byte bit_addres  = (first_param() & 0x07);
      byte cislo = 1 << bit_addres;
      if (RAM[byte_addres] & cislo)
         bit = 1;
      else
         bit = 0;
   }
   if (!bit)
      RAM[0xD0] &= ~E_7_BIT;

   PC += 2;
   m_OscPeriod = 24;

}
void __fastcall C_Procesor::DIV_AB(void)
{
   int cel = (int )A / (int )B;
   int zvis = (int )A % (int )B;
   A = cel;
   B = zvis;
   PC++;
   m_OscPeriod = 48;

}
void __fastcall C_Procesor::MOV_DIRECT_DIRECT(void)
{
   RAM[second_param()] = RAM[first_param()];
   PC += 3;
   m_OscPeriod = 24;
}
void __fastcall C_Procesor::MOV_DIRECT_INDIRECT(void)
{
   if (cur_instr() & E_0_BIT)
      RAM[first_param()] = RAM[R1];
   else
      RAM[first_param()] = RAM[R0];

   PC += 2;
   m_OscPeriod = 24;
}

void __fastcall C_Procesor::MOV_DIRECT_RN(void)
{
   int n = cur_instr() & GET_N;
      RAM[first_param()] = R[n];
}
void __fastcall C_Procesor::MOV_BIT_C(void)
{
   bool _C = zisti_C();
   if(first_param() >= 0x80)
   {
      byte byte_addres = (first_param() & 0xF8);
      byte bit_addres  = (first_param() & 0x07);
      byte cislo = 1 << bit_addres;
      if (_C)
         RAM[byte_addres] |= cislo;
      else
         RAM[byte_addres] &= ~cislo;
   }
   else
   {
      byte byte_addres = (first_param() >> 3) + 0x20;
      byte bit_addres  = (first_param() & 0x07);
      byte cislo = 1 << bit_addres;
      if (_C)
         RAM[byte_addres] |= cislo;
      else
         RAM[byte_addres] &= ~cislo;
   }
   PC += 2;
   m_OscPeriod = 24;
}
void __fastcall C_Procesor::SUBB_A_DATA(void)
{
   bool _C = zisti_C();
   word  pom = A;
   A = A - (_C) - first_param();
   if (pom < (_C + first_param()))
      nastav_C_1();
   PC += 2;
   m_OscPeriod = 12;
}
void __fastcall C_Procesor::SUBB_A_DIRECT(void)
{
   bool _C = zisti_C();
   word  pom = A;
   A -= _C - RAM[first_param()];
   if (pom < (_C + RAM[first_param()]))
      nastav_C_1();
   PC += 2;
   m_OscPeriod = 12;

}
void __fastcall C_Procesor::SUBB_A_INDIRECT(void)
{
   bool _C = zisti_C();
   word  pom = A;
   if (cur_instr() & E_0_BIT)
   {
      A -= _C - RAM[R1];
      if (pom < (_C + RAM[R1]))
         nastav_C_1();
   }
   else
   {
      A -= _C - RAM[R0];
      if (pom < (_C + RAM[R0]))
         nastav_C_1();
   }

   PC++;
   m_OscPeriod = 12;

}
void __fastcall C_Procesor::SUBB_A_RN(void)
{
   bool _C = zisti_C();
   word  pom = A;
   int n = cur_instr() & GET_N;
   A -= _C - R[n];
   if (pom < (_C + RAM[n]))
      nastav_C_1();
   PC++;
   m_OscPeriod = 12;
}
void __fastcall C_Procesor::ORL_C_NEG_BIT(void)
{
   bool bit;
   if(first_param() >= 0x80)
   {
      byte byte_addres = (first_param() & 0xF8);
      byte bit_addres  = (first_param() & 0x07);
      byte cislo = 1 << bit_addres;
      if (RAM[byte_addres] & cislo)
         bit = 0;
      else
         bit = 1;
   }
   else
   {
      byte byte_addres = (first_param() >> 3) + 0x20;
      byte bit_addres  = (first_param() & 0x07);
      byte cislo = 1 << bit_addres;
      if (RAM[byte_addres] & cislo)
         bit = 0;
      else
         bit = 1;
   }
   if (bit)
      RAM[0xD0] |= E_7_BIT;
   PC += 2;
   m_OscPeriod = 24;
}
void __fastcall C_Procesor::MOV_C_BIT(void)
{
   if(first_param() >= 0x80)
   {
      byte byte_addres = (first_param() & 0xF8);
      byte bit_addres  = (first_param() & 0x07);
      byte cislo = 1 << bit_addres;
      if (cislo & RAM[byte_addres])
         RAM[0xD0] |= E_7_BIT;
      else
         RAM[0xD0] &= ~E_7_BIT;
   }
   else
   {
      byte byte_addres = (first_param() >> 3) + 0x20;
      byte bit_addres  = (first_param() & 0x07);
      byte cislo = 1 << bit_addres;
      if (cislo & RAM[byte_addres])
         RAM[0xD0] |= E_7_BIT;
      else
         RAM[0xD0] &= ~E_7_BIT;
   }
   PC += 2;
   m_OscPeriod = 12;
}
void __fastcall C_Procesor::MUL_AB(void)  //NASTAV OV!!!
{
   long vysledok = A * B;
   A = 0;
   A |= vysledok;
   vysledok >> 8;
   B = 0;
   B |= vysledok;
   PC++;
   m_OscPeriod = 48;
}
void __fastcall C_Procesor::MOV_INDIREC_DIRECT(void)
{
   if (cur_instr() & E_0_BIT)
      RAM[R1] = RAM[first_param()];
   else
      RAM[R0] = RAM[first_param()];
   PC += 2;
   m_OscPeriod = 24;
}
void __fastcall C_Procesor::MOV_RN_DIRECT(void)
{
   int n = cur_instr() & GET_N;
   R[n] = RAM[first_param()];
   PC += 2;
   m_OscPeriod = 24;
}
void __fastcall C_Procesor::ANL_C_NEG_BIT(void)
{
   bool bit;
   if(first_param() >= 0x80)
   {
      byte byte_addres = (first_param() & 0xF8);
      byte bit_addres  = (first_param() & 0x07);
      byte cislo = 1 << bit_addres;
      if (RAM[byte_addres] & cislo)
         bit = 0;
      else
         bit = 1;
   }
   else
   {
      byte byte_addres = (first_param() >> 3) + 0x20;
      byte bit_addres  = (first_param() & 0x07);
      byte cislo = 1 << bit_addres;
      if (RAM[byte_addres] & cislo)
         bit = 0;
      else
         bit = 1;
   }
   if (!bit)
      RAM[0xD0] &= ~E_7_BIT;

   PC += 2;
   m_OscPeriod = 24;
}
void __fastcall C_Procesor::CPL_BIT(void)
{
   if(first_param() >= 0x80)
   {
      byte byte_addres = (first_param() & 0xF8);
      byte bit_addres  = (first_param() & 0x07);
      byte cislo = 1 << bit_addres;
      if (RAM[byte_addres] & cislo)
         RAM[byte_addres] &= ~cislo;
      else
         RAM[byte_addres] |= cislo;
   }
   else
   {
      byte byte_addres = (first_param() >> 3) + 0x20;
      byte bit_addres  = (first_param() & 0x07);
      byte cislo = 1 << bit_addres;
      if (RAM[byte_addres] & cislo)
         RAM[byte_addres] &= ~cislo;
      else
         RAM[byte_addres] |= cislo;
   }
   PC += 2;
   m_OscPeriod = 12;
}
void __fastcall C_Procesor::CPL_C(void)
{
   bool _C = zisti_C();
   if (_C)
      RAM[0xD0] &= ~E_7_BIT;
   else
      RAM[0xD0] |= E_7_BIT;
   PC++;
   m_OscPeriod = 12;

}
void __fastcall C_Procesor::CJNE_A_DATA(void)
{
   PC += 3;
   if (A == rel_param(-2))
      //PC += second_param();
      PC += ((signed char)rel_param(-1));
   if (A < rel_param(-2))
      nastav_C_1();
   else
      nastav_C_0();
   m_OscPeriod = 24;
}
void __fastcall C_Procesor::CJNE_A_DIRECT(void)
{
   PC += 3;
   if (A == RAM[rel_param(-2)])
      //PC += second_param();
      PC += ((signed char)rel_param(-1));
   if (A < RAM[rel_param(-1)])
      nastav_C_1();
   else
      nastav_C_0();
   m_OscPeriod = 24;
}
void __fastcall C_Procesor::CJNE_INDIRECT_DATA(void)
{
   PC += 3;
   if (rel_param(-3) & E_0_BIT)
   {
      if (R1 == RAM[rel_param(-2)])
         //PC += second_param();
         PC += ((signed char)rel_param(-1));
      if (R1 < RAM[rel_param(-2)])
         nastav_C_1();
      else
         nastav_C_0();
   }
   else
   {
      if (R0 == RAM[rel_param(-2)])
         //PC += second_param();
         PC += ((signed char)rel_param(-1));
      if (R0 < RAM[rel_param(-1)])
         nastav_C_1();
      else
         nastav_C_0();
   }
   m_OscPeriod = 24;

}
void __fastcall C_Procesor::CJNE_RN_DATA(void)
{
   int n = cur_instr() & GET_N;
   PC += 3;
      if (R[n] != rel_param(-2))
         //PC += second_param();
         PC += ((signed char)rel_param(-1));
      if (R[n] < RAM[rel_param(-2)])
         nastav_C_1();
      else
         nastav_C_0();
   m_OscPeriod = 24;
}
void __fastcall C_Procesor::PUSH(void)
{
   SP++;
   RAM[SP] = first_param();;                 // zmen SP
   PC += 2;
   m_OscPeriod = 24;
}
void __fastcall C_Procesor::CLR_BIT(void)
{
   if(first_param() >= 0x80)
   {
      byte byte_addres = (first_param() & 0xF8);
      byte bit_addres  = (first_param() & 0x07);
      byte cislo = 1 << bit_addres;
      RAM[byte_addres] &= ~cislo;
   }
   else
   {
      byte byte_addres = (first_param() >> 3) + 0x20;
      byte bit_addres  = (first_param() & 0x07);
      byte cislo = 1 << bit_addres;
      RAM[byte_addres] &= ~cislo;
   }
   PC += 2;
   m_OscPeriod = 12;
}

void __fastcall C_Procesor::CLR_C(void)
{
   nastav_C_0();
   PC++;
   m_OscPeriod = 12;
}
void __fastcall C_Procesor::SWAP_A(void)
{
   byte A1 = A;
   byte A2 = A;
   A1 >> 4;
   A2 << 4;
   A = A1 | A2;
   PC++;
   m_OscPeriod = 12;
}
void __fastcall C_Procesor::XCH_A_DIRECT(void)
{
   byte pom = A;
   A = RAM[first_param()];
   RAM[first_param()] = pom;
   PC += 2;
   m_OscPeriod = 12;
}
void __fastcall C_Procesor::XCH_A_INDIRECT(void)
{
   byte pom = A;
   if (cur_instr() & E_0_BIT)
   {
      A = RAM[R1];
      RAM[R1] = pom;
   }
   else
   {
      A = RAM[R0];
      RAM[R0] = pom;
   }
   PC++;
   m_OscPeriod = 12;
}
void __fastcall C_Procesor::XCH_A_RN(void)
{
   int n = cur_instr() & GET_N;
   byte pom = A;
   A = R[n];
   R[n] = pom;
   PC++;
   m_OscPeriod = 12;
}
void __fastcall C_Procesor::POP(void)
{
   RAM[first_param()] = RAM[SP];
   SP--;                                               //zmen SP
   PC += 2;
   m_OscPeriod = 12;
}
void __fastcall C_Procesor::SETB_BIT(void)
{
   if(first_param() >= 0x80)
   {
      byte byte_addres = (first_param() & 0xF8);
      byte bit_addres  = (first_param() & 0x07);
      byte cislo = 1 << bit_addres;
      RAM[byte_addres] |= cislo;
   }
   else
   {
      byte byte_addres = (first_param() >> 3) + 0x20;
      byte bit_addres  = (first_param() & 0x07);
      byte cislo = 1 << bit_addres;
      RAM[byte_addres] |= cislo;
   }
   PC += 2;
   m_OscPeriod = 12;
}
void __fastcall C_Procesor::SETB_C(void)
{
   nastav_C_1();
   PC++;
   m_OscPeriod = 12;
}
void __fastcall C_Procesor::DJNZ_DIRECT_ADDRES(void)
{
   PC +=3;
   //RAM[first_param()]--;
   RAM[rel_param(-2)]--;
   if (RAM[rel_param(-2)] != 0)
      //PC += second_param();
      PC += ((signed char)rel_param(-1));
   m_OscPeriod = 24;
}
void __fastcall C_Procesor::XCHD_A_INDIRECT(void)
{
   if (cur_instr() & E_0_BIT)
   {
      byte A_0_3 = A & 0x0F;
      byte REG_0_3 = RAM[R1] & 0x0F;
      A &= 0xF0;
      RAM[R1] &= 0xF0;
      A |= REG_0_3;
      RAM[R1] |= A_0_3;
   }
   else
   {
      byte A_0_3 = A & 0x0F;
      byte REG_0_3 = RAM[R0] & 0x0F;
      A &= 0xF0;
      RAM[R0] &= 0xF0;
      A |= REG_0_3;
      RAM[R0] |= A_0_3;
   }
   PC++;
   m_OscPeriod = 12;
}
void __fastcall C_Procesor::DJNZ_RN_ADDRES(void)
{
   int n = cur_instr() & GET_N;
   PC += 2;
   R[n]--;                              // nesmie sa dekrementovat do zaporu
   if (R[n] != 0)
      PC += ((signed char)rel_param(-1));
//      PC += rel_param(-1);
   m_OscPeriod = 24;
}
void __fastcall C_Procesor::CLR_A(void)
{
   A = 0;
   PC++;
   m_OscPeriod = 12;
}
void __fastcall C_Procesor::MOV_A_DIRECT(void)
{
   A = RAM[first_param()];
   PC += 2;
   m_OscPeriod = 12;
}
void __fastcall C_Procesor::MOV_A_INDIRECT(void)
{
   if (cur_instr() & E_0_BIT)
      A = RAM[R1];
   else
      A = RAM[R0];
   PC++;
   m_OscPeriod = 12;
}
void __fastcall C_Procesor::MOV_A_RN(void)
{
   int n = cur_instr() & GET_N;
   A = R[n];
   PC++;
   m_OscPeriod = 12;
}
void __fastcall C_Procesor::CPL_A(void)
{
   A = ~A;
   PC++;
   m_OscPeriod = 12;
}
void __fastcall C_Procesor::MOV_DIRECT_A(void)
{
   RAM[first_param()] = A;
   PC += 2;
   m_OscPeriod = 12;
}
void __fastcall C_Procesor::MOV_INDIRECT_A(void)
{
   if (cur_instr() & E_0_BIT)
      RAM[R1] = A;
   else
      RAM[R0] = A;
   PC++;
   m_OscPeriod = 12;
}
void __fastcall C_Procesor::MOV_RN_A(void)
{
   int n = cur_instr() &GET_N;
   R[n] = A;
   PC++;
   m_OscPeriod = 12;
}

void __fastcall C_Procesor::MOV_DPTR_DATA(void)
{
/* incrementacia DPTR
   if(DPL != 0xFF)
   {
      DPL++;
   }
   else if(DPH != 0xFF)
   {
      DPL = 0;
      DPH++;
   }
   else
   {
      DPL = DPH = 0;
   }
*/
   DPH = first_param();
   DPL = second_param();
   PC += 3;
   m_OscPeriod = 24;
}

void __fastcall C_Procesor::MOVX_DPTR_A(void)
{
   EX_Devices->SetDataTo(GET_DPTR(),A);
   PC++;
   m_OscPeriod = 24;
}


void __fastcall C_Procesor::MOVX_A_DPTR(void)
{
   A = EX_Devices->GetDataFrom(GET_DPTR());
   PC++;
   m_OscPeriod = 24;
}
void __fastcall C_Procesor::INC_DPTR(void)
{
//   incrementacia DPTR
   if(DPL != 0xFF)
   {
      DPL++;
   }
   else if(DPH != 0xFF)
   {
      DPL = 0;
      DPH++;
   }
   else
   {
      DPL = DPH = 0;
   }
}


bool __fastcall C_Procesor::zisti_C(void)
{
   return (PSW & E_7_BIT);
}
void __fastcall C_Procesor::Obnov_registre(void)
{
   AnsiString pamet;                    // ak to nepojde odstran celu metodu

   pamet.sprintf("%02XH", A);
   Form1->Akumulator->Caption = pamet;

   pamet.sprintf("%02XH", R[0]);
   Form1->Register0->Caption = pamet;

   pamet.sprintf("%02XH", R[1]);
   Form1->Register1->Caption = pamet;

   pamet.sprintf("%02XH", R[2]);
   Form1->Register2->Caption = pamet;

   pamet.sprintf("%02XH", R[3]);
   Form1->Register3->Caption = pamet;

   pamet.sprintf("%02XH", R[4]);
   Form1->Register4->Caption = pamet;

   pamet.sprintf("%02XH", R[5]);
   Form1->Register5->Caption = pamet;

   pamet.sprintf("%02XH", R[6]);
   Form1->Register6->Caption = pamet;

   pamet.sprintf("%02XH", R[7]);
   Form1->Register7->Caption = pamet;
}
void __fastcall C_Procesor::Restart(void)
{
   RAM[0x90] = 0;
   A = 0;
   R[0] = 0;
   R[1] = 0;
   R[2] = 0;
   R[3] = 0;
   R[4] = 0;
   R[5] = 0;
   R[6] = 0;
   R[7] = 0;
}
