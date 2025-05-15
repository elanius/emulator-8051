//---------------------------------------------------------------------------

#ifndef Unit4H
#define Unit4H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TApplic5 : public TForm
{
__published:	// IDE-managed Components
   TSpeedButton *KlavesaA;
   TSpeedButton *KlavesaB;
   TSpeedButton *KlavesaC;
   TSpeedButton *KlavesaD;
   TSpeedButton *KlavesaE;
   TSpeedButton *KlavesaF;
   TSpeedButton *KlavesaG;
   TSpeedButton *KlavesaH;
   TSpeedButton *KlavesaI;
   TSpeedButton *KlavesaJ;
   TSpeedButton *KlavesaK;
   TSpeedButton *KlavesaL;
   TSpeedButton *KlavesaM;
   TSpeedButton *KlavesaN;
   TSpeedButton *KlavesaO;
   TSpeedButton *KlavesaP;
   TLabel *Label1;
   TLabel *Label2;
   TLabel *Label3;
   TLabel *Label4;
   TLabel *Label5;
   TLabel *Label6;
   TLabel *Label7;
   TLabel *Label8;
   TLabel *Label9;
   TLabel *Label10;
   TLabel *Label11;
   TLabel *Label12;
   TLabel *Label13;
   TLabel *Label14;
   TLabel *Label15;
   TLabel *Label16;
   TLabel *Label17;
   TLabel *Label18;
   TLabel *Label19;
   TLabel *Label20;
   TLabel *Label21;
   TShape *Shape1;
   TShape *Shape2;
   TBevel *Bevel1;
   TLabel *Label22;
   TLabel *Segment0;
   TLabel *Segment1;
   TLabel *Segment2;
   TLabel *Segment3;
   TSpeedButton *SpeedButton1;
   void __fastcall Klavesnica_Click1(TObject *Sender);
   void __fastcall Klavesnica_Click2(TObject *Sender);
   void __fastcall SpeedButton1Click(TObject *Sender);
private:	// User declarations

   bool Applic5_modified;
   bool priznak;

   void __fastcall UpdateOutput();

   byte Applic5_port_in;
   byte Applic5_port_out;

   bool __fastcall Zisti_byt(int byt);
   void __fastcall Nastav_segment0(int seg);
   void __fastcall Nastav_segment1(int seg);
   void __fastcall Nastav_segment2(int seg);
   void __fastcall Nastav_segment3(int seg);

public:		// User declarations

   void __fastcall WriteToPort_Applic5(byte _Value);
   byte __fastcall ReadFromPort_Applic5();

   void __fastcall Tick();
   void __fastcall Restart(void);

   __fastcall TApplic5(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TApplic5 *Applic5;
//---------------------------------------------------------------------------
#endif
