//---------------------------------------------------------------------------

#ifndef Unit3H
#define Unit3H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TAplic3 : public TForm
{
__published:	// IDE-managed Components
   TShape *Mot8;
   TShape *Mot7;
   TShape *Mot6;
   TShape *Mot5;
   TShape *Mot4;
   TShape *Mot3;
   TShape *Mot2;
   TShape *Mot1;
   TLabel *Label1;
   TShape *RedLed;
   TLabel *Label2;
   TLabel *Label3;
   TShape *KM_DA;
   TShape *KM_D;
   TShape *KM_BD;
   TShape *KM_B;
   TShape *KM_CB;
   TShape *KM_C;
   TShape *KM_AC;
   TShape *KM_A;
   TSpeedButton *Prepinac;
   TLabel *Label4;
   TLabel *Label5;
   TSpeedButton *SpeedButton2;
   TLabel *Label6;
   TShape *Shape18;
   TShape *Shape19;
   TEdit *Edit1;
   TEdit *Edit2;
   TEdit *Edit3;
   TEdit *Edit4;
   TLabel *Label8;
   TLabel *Label9;
   TLabel *Label10;
   TLabel *Label11;
   TEdit *Edit5;
   TLabel *Label12;
   TTimer *Timer1;
   TEdit *EditA;
   TLabel *Label13;
   TEdit *EditB;
   TLabel *Label14;
   TEdit *EditC;
   TLabel *Label15;
   TEdit *EditD;
   TLabel *Label16;
   TLabel *Label7;
   TLabel *Label17;
   TLabel *Label18;
   TLabel *Label19;
   TLabel *Label20;
   TLabel *Label21;
   TLabel *Label22;
   TLabel *Label23;
   TBevel *Bevel1;
   TBevel *Bevel2;
   TBevel *Bevel3;
   TBevel *Bevel4;
   TBevel *Bevel5;
   TBevel *Bevel6;
   void __fastcall PrepinacClick(TObject *Sender);
   void __fastcall Shape18MouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
   void __fastcall Shape19MouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
   void __fastcall SpeedButton2MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
   void __fastcall Timer1Timer(TObject *Sender);
   void __fastcall SpeedButton2MouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);

private:	// User declarations

   bool Applic3_modified;

   void __fastcall UpdateOutput();
   int  __fastcall PolohaZariadenia(AnsiString Edit);
   void __fastcall TocMotorcek(int);
   void __fastcall StopMotorcek(void);

   byte Applic3_port_in;
   byte Applic3_port_out;

public:		// User declarations

   void __fastcall WriteToPort_Applic3(byte _Value);
   byte __fastcall ReadFromPort_Applic3();

   void __fastcall Tick();
   void  __fastcall Restart(void);

   __fastcall TAplic3(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TAplic3 *Aplic3;
//---------------------------------------------------------------------------
#endif
