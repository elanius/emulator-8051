//---------------------------------------------------------------------------
#ifndef C_ExternalDevicesH
#define C_ExternalDevicesH

#include <map>

//---------------------------------------------------------------------------
typedef void __fastcall (__closure *WriteCallback)(byte _Value);
typedef byte __fastcall (__closure *ReadCallback)();

//---------------------------------------------------------------------------
class C_ExternalDevices
{
private:

   std::map<int, ReadCallback>   Read_Ports;
   std::map<int, WriteCallback>  Write_Ports;

protected:
public:
   C_ExternalDevices();
   ~C_ExternalDevices();

   byte GetDataFrom(word _Port);
   void SetDataTo(word _Port, byte _Value);

   void RegisterWriteCallback(word _Port, WriteCallback _Callback);
   void RegisterReadCallback(word _Port, ReadCallback _Callback);
};

extern C_ExternalDevices *EX_Devices;



//---------------------------------------------------------------------------
#endif
