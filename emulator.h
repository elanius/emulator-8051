//---------------------------------------------------------------------------
#ifndef emulatorH
#define emulatorH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <ToolWin.hpp>
#include <ImgList.hpp>
#include <Menus.hpp>
#include <Dialogs.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
   TRichEdit *RichEdit1;
   TSpeedButton *SpeedButton2;
   TSpeedButton *SBsave;
   TMainMenu *MainMenu1;
   TMenuItem *file;
   TSpeedButton *SpeedButton11;
   TRichEdit *Hlasenia;
   TLabel *Label1;
   TLabel *Akumulator;
   TLabel *Label3;
   TLabel *Label4;
   TLabel *Label5;
   TLabel *Label6;
   TLabel *Label7;
   TLabel *Label8;
   TLabel *Label9;
   TLabel *Label10;
   TLabel *Register0;
   TLabel *Register1;
   TLabel *Register2;
   TLabel *Register3;
   TLabel *Register4;
   TLabel *Register5;
   TLabel *Register6;
   TLabel *Register7;
   TMenuItem *Modules;
   TMenuItem *Trenazer1;
   TMenuItem *Applic31;
   TMenuItem *Ulo1;
   TSaveDialog *SaveDialog1;
   TOpenDialog *OpenDialog1;
   TMenuItem *Naitaj1;
   TMenuItem *Nov1;
   TMenuItem *Exit1;
   TMenuItem *N1;
   TMenuItem *App5;
   TSpeedButton *Restart;
   TLabel *Label2;
   TLabel *Label11;
//    void __fastcall SpeedButton1Click(TObject *Sender);
    void __fastcall SpeedButton2Click(TObject *Sender);
//    void __fastcall SPOnClick(TObject *Sender);
   void __fastcall SBRunClick(TObject *Sender);
   void __fastcall SBsaveClick(TObject *Sender);
   void __fastcall FormShow(TObject *Sender);
   void __fastcall Trenazer1Click(TObject *Sender);
   void __fastcall Applic31Click(TObject *Sender);
   void __fastcall Ulo1Click(TObject *Sender);
   void __fastcall Naitaj1Click(TObject *Sender);
   void __fastcall Nov1Click(TObject *Sender);
   void __fastcall Exit1Click(TObject *Sender);
   void __fastcall App5Click(TObject *Sender);
   void __fastcall RestartClick(TObject *Sender);
   void __fastcall About1Click(TObject *Sender);


private:	// User declarations
   void __fastcall MyIdleHandler(TObject *Sender, bool &Done);

   void __fastcall ProcesLine(AnsiString &Line);
   void __fastcall Preprocesor(AnsiString Items[]);
   bool __fastcall RN(AnsiString Items[], int NumberItem, int &maska);
   bool __fastcall DIRECT(AnsiString Items[], int NumberItem, int &INTCISLO);
   bool __fastcall INDIRECT(AnsiString Items[], int NumberItem, int &maska);
   bool __fastcall DATA(AnsiString Items[], int NumberItem, int &INTCISLO);
   int __fastcall  Prevodnik(AnsiString Items[], int NumberItem, int dlzka);
   int __fastcall  BinPrevodnik(AnsiString Items[], int NumberItem, int dlzka);
   int __fastcall  DecPrevodnik(AnsiString Items[], int NumberItem, int dlzka);
   void __fastcall ProcesItems(AnsiString Items[]);
   bool __fastcall SKOK(AnsiString Items[], int NumberItem, int &INTCISLO, int index);
   void __fastcall Hlasenie_chyb(AnsiString Items[], int i);
   void __fastcall Hlasenie_chyb_navestia(void);
   void __fastcall Reset(void);
   bool __fastcall pouzite_navestia(int i);

   int               index_navestia;
   AnsiString        navestia[100][4];

   int               index;
   int               program_hex[4000];

   byte              strojovy_kod[4000];
   TRichEdit         *TempRE;

public:		// User declarations
   AnsiString str;
   __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
