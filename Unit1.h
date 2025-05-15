//---------------------------------------------------------------------------
#ifndef _C_PROCESOR_H_
#define _C_PROCESOR_H_

typedef void __fastcall (__closure *Instrukcia)(void);

class C_Procesor
{
   int         m_OscPeriod;                  // Oscilator Period
   Instrukcia  instruction_set[256];

   byte        ROM[65536];                   // 64 kB memory (interna + externa)
   byte        RAM[256];

   word        PC;
   int         Rn_bank;

protected:
   void __fastcall NOP(void);
   void __fastcall AJMP(void);
   void __fastcall LJMP(void);
   void __fastcall RR_A(void);
   void __fastcall INC_A(void);
   void __fastcall INC_DIRECT(void);
   void __fastcall INC_INDIRECT(void);
   void __fastcall INC_RN(void);
   void __fastcall JBC(void);
   void __fastcall ACALL(void);
   void __fastcall LCALL(void);
   void __fastcall RRC_A(void);
   void __fastcall DEC_A(void);
   void __fastcall DEC_DIRECT(void);
   void __fastcall DEC_INDIRECT(void);
   void __fastcall DEC_RN(void);
   void __fastcall JB(void);
   void __fastcall RET(void);
   void __fastcall RL_A(void);
   void __fastcall ADD_A_DATA(void);
   void __fastcall ADD_A_DIRECT(void);
   void __fastcall ADD_A_INDIRECT(void);
   void __fastcall ADD_A_RN(void);
   void __fastcall JNB(void);
   void __fastcall RETI(void);
   void __fastcall RLC_A(void);
   void __fastcall ADDC_A_DATA(void);
   void __fastcall ADDC_A_DIRECT(void);
   void __fastcall ADDC_A_INDIRECT(void);
   void __fastcall ADDC_A_RN(void);
   void __fastcall JC(void);
   void __fastcall ORL_DIRECT_A(void);
   void __fastcall ORL_DIRECT_DATA(void);
   void __fastcall ORL_A_DATA(void);
   void __fastcall ORL_A_DIRECT(void);
   void __fastcall ORL_A_INDIRECT(void);
   void __fastcall ORL_A_RN(void);
   void __fastcall JNC(void);
   void __fastcall ANL_DIRECT_A(void);
   void __fastcall ANL_DIRECT_DATA(void);
   void __fastcall ANL_A_DATA(void);
   void __fastcall ANL_A_DIRECT(void);
   void __fastcall ANL_A_INDIRECT(void);
   void __fastcall ANL_A_RN(void);
   void __fastcall JZ(void);
   void __fastcall XRL_DIRECT_A(void);
   void __fastcall XRL_DIRECT_DATA(void);
   void __fastcall XRL_A_DATA(void);
   void __fastcall XRL_A_DIRECT(void);
   void __fastcall XRL_A_INDIRECT(void);
   void __fastcall XRL_A_RN(void);
   void __fastcall JNZ(void);
   void __fastcall ORL_C_BIT(void);
   void __fastcall MOV_A_DATA(void);
   void __fastcall MOV_DIRECT_DATA(void);
   void __fastcall MOV_INDIRECT_DATA(void);
   void __fastcall MOV_RN_DATA(void);
   void __fastcall SJMP(void);
   void __fastcall ANL_C_BIT(void);
   void __fastcall DIV_AB(void);
   void __fastcall MOV_DIRECT_DIRECT(void);
   void __fastcall MOV_DIRECT_INDIRECT(void);
   void __fastcall MOV_DIRECT_RN(void);
   void __fastcall MOV_BIT_C(void);
   void __fastcall SUBB_A_DATA(void);
   void __fastcall SUBB_A_DIRECT(void);
   void __fastcall SUBB_A_INDIRECT(void);
   void __fastcall SUBB_A_RN(void);
   void __fastcall ORL_C_NEG_BIT(void);
   void __fastcall MOV_C_BIT(void);
   void __fastcall MUL_AB(void);
   void __fastcall MOV_INDIREC_DIRECT(void);
   void __fastcall MOV_RN_DIRECT(void);
   void __fastcall ANL_C_NEG_BIT(void);
   void __fastcall CPL_BIT(void);
   void __fastcall CPL_C(void);
   void __fastcall CJNE_A_DATA(void);
   void __fastcall CJNE_A_DIRECT(void);
   void __fastcall CJNE_INDIRECT_DATA(void);
   void __fastcall CJNE_RN_DATA(void);
   void __fastcall PUSH(void);
   void __fastcall CLR_BIT(void);
   void __fastcall CLR_C(void);
   void __fastcall SWAP_A(void);
   void __fastcall XCH_A_DIRECT(void);
   void __fastcall XCH_A_INDIRECT(void);
   void __fastcall XCH_A_RN(void);
   void __fastcall POP(void);
   void __fastcall SETB_BIT(void);
   void __fastcall SETB_C(void);
   void __fastcall DJNZ_DIRECT_ADDRES(void);
   void __fastcall XCHD_A_INDIRECT(void);
   void __fastcall DJNZ_RN_ADDRES(void);
   void __fastcall CLR_A(void);
   void __fastcall MOV_A_DIRECT(void);
   void __fastcall MOV_A_INDIRECT(void);
   void __fastcall MOV_A_RN(void);
   void __fastcall CPL_A(void);
   void __fastcall MOV_DIRECT_A(void);
   void __fastcall MOV_INDIRECT_A(void);
   void __fastcall MOV_RN_A(void);

   void __fastcall MOV_DPTR_DATA(void);
   void __fastcall MOVX_DPTR_A(void);
   void __fastcall MOVX_A_DPTR(void);
   void __fastcall INC_DPTR(void);


  // bool __fastcall zisti_C(void);


public:
   byte __fastcall   GetPortP0() {  return RAM[0x80];  };
   byte __fastcall   GetPortP1() {  return RAM[0x90];  };
   byte __fastcall   GetPortP2() {  return RAM[0xA0];  };
   byte __fastcall   GetPortP3() {  return RAM[0xB0];  };

   void __fastcall   Tick();

   void __fastcall   napal_program(Byte _Program[], int size, int _StartAdrres);
   void __fastcall   start(int start_from);
   void              init();
   bool __fastcall   zisti_C(void);
   void __fastcall   Obnov_registre(void);
   void __fastcall   Restart(void);

   C_Procesor(){   };

   ~C_Procesor() {};
};
//---------------------------------------------------------------------------
extern C_Procesor *Procesor_8051;
//---------------------------------------------------------------------------
enum MASKA
{
   E_0_BIT = 0x01,
   E_1_BIT = 0x02,
   E_2_BIT = 0x04,
   E_3_BIT = 0x08,
   E_4_BIT = 0x10,
   E_5_BIT = 0x20,
   E_6_BIT = 0x40,
   E_7_BIT = 0x80,
};

//---------------------------------------------------------------------------
#endif _C_PROCESOR_H_

