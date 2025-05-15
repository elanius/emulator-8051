//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Global.h"
#include "C_ExternalDevices.h"


//---------------------------------------------------------------------------
#pragma package(smart_init)
C_ExternalDevices *EX_Devices;

//---------------------------------------------------------------------------
C_ExternalDevices::C_ExternalDevices()
{}
C_ExternalDevices::~C_ExternalDevices()
{
   Read_Ports.clear();
   Write_Ports.clear();
}


byte C_ExternalDevices::GetDataFrom(word _Port)
{
   return Read_Ports[_Port]();
}

void C_ExternalDevices::SetDataTo(word _Port, byte _Value)
{
   Write_Ports[_Port](_Value);
}


void C_ExternalDevices::RegisterWriteCallback(word _Port, WriteCallback _Callback)
{
   Write_Ports.insert(std::make_pair(_Port, _Callback));
}

void C_ExternalDevices::RegisterReadCallback(word _Port, ReadCallback _Callback)
{
   Read_Ports.insert(std::make_pair(_Port, _Callback));
}

//---------------------------------------------------------------------------

