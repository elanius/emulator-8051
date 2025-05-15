//---------------------------------------------------------------------------

#ifndef Unit2H
#define Unit2H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TTrenazer : public TForm
{
__published:	// IDE-managed Components
   TLabel *Label1;
   TLabel *Label2;
   TLabel *Label3;
   TShape *OutPort_FF00H_0;
   TShape *OutPort_FF00H_1;
   TShape *OutPort_FF00H_2;
   TShape *OutPort_FF00H_3;
   TShape *OutPort_FF00H_4;
   TShape *OutPort_FF00H_5;
   TShape *OutPort_FF00H_6;
   TShape *OutPort_FF00H_7;
   TLabel *Label4;
   TLabel *Label5;
   TLabel *Label6;
   TLabel *Label7;
   TLabel *Label8;
   TLabel *Label9;
   TLabel *Label10;
   TLabel *Label11;
   TSpeedButton *InPort_FF00H_0;
   TSpeedButton *InPort_FF00H_1;
   TSpeedButton *InPort_FF00H_2;
   TSpeedButton *InPort_FF00H_3;
   TSpeedButton *InPort_FF00H_4;
   TSpeedButton *InPort_FF00H_5;
   TSpeedButton *InPort_FF00H_6;
   TSpeedButton *InPort_FF00H_7;
   TLabel *Label12;
   TLabel *Label13;
   TLabel *Label14;
   TLabel *Label15;
   TLabel *Label16;
   TLabel *Label17;
   TLabel *Label18;
   TLabel *Label19;
   TLabel *Label20;
   TShape *port1_0;
   TShape *port1_1;
   TShape *port1_2;
   TShape *port1_3;
   TShape *port1_4;
   TShape *port1_5;
   TShape *port1_6;
   TShape *port1_7;
   TLabel *Label21;
   TLabel *Label22;
   TLabel *Label23;
   TLabel *Label24;
   TLabel *Label25;
   TLabel *Label26;
   TLabel *Label27;
   TLabel *Label28;
   TLabel *Label29;
   TBevel *Bevel1;
   TBevel *Bevel2;
   void __fastcall InPort_FF00H_Click(TObject *Sender);

private:	// User declarations
   bool     port_FF00_out_modified;

   byte     port_FF00_in;
   byte     port_FF00_out;

   void __fastcall UpdateOutput();

public:		// User declarations
   void __fastcall UpdateGreenLeds(byte _Value);
   void __fastcall Tick();
   void __fastcall Restart(void);

   void __fastcall WriteToPort_FF00H(byte _Value);
   byte __fastcall ReadFromPort_FF00H();

   __fastcall TTrenazer(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTrenazer *Trenazer;
//---------------------------------------------------------------------------
#endif
