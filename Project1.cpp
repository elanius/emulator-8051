//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("Project1.res");
USEFORM("emulator.cpp", Form1);
USEUNIT("Unit1.cpp");
USEFORM("Unit2.cpp", Trenazer);
USEFORM("Unit3.cpp", Aplic3);
USEUNIT("C_ExternalDevices.cpp");
USEFORM("Unit4.cpp", Applic5);
USEFORM("Unit5.cpp", About);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
   try
   {
      Application->Initialize();
      Application->CreateForm(__classid(TForm1), &Form1);
       Application->CreateForm(__classid(TTrenazer), &Trenazer);
       Application->CreateForm(__classid(TAplic3), &Aplic3);
       Application->CreateForm(__classid(TApplic5), &Applic5);
       Application->CreateForm(__classid(TAbout), &About);
       Application->Run();
   }
   catch (Exception &exception)
   {
      Application->ShowException(&exception);
   }
   return 0;
}
//---------------------------------------------------------------------------





