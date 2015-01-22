#ifndef UTILITS_H
#define UTILITS_H

#include "User.h"

class cUtilits
{
	public:
		void HookThis(DWORD dwMyFuncOffset, DWORD dwJmpOffset);
		void SetNop(DWORD dwOffset, int Size);
		void SetRetn(DWORD dwOffset);
		void SetRRetn(DWORD dwOffset);
		void SetByte(DWORD dwOffset, BYTE btValue);

		int gObjIsConnected(int Index);

		int GetPlayerIndex(char *Name);
		int GenExcOpt(int amount);
		int TakeExcNum(int Exc);
		int gObjZenSingle(LPOBJ gObj,LPOBJ tObj, int dmg, int tot_dmg);
		int GetNumberByPercent(int Proc, int Min, int Max);

		char* GetMapName(int MapId);

		bool IsBadFileLine(char *FileLine, int &Flag);
		void SendEffect(LPOBJ gObj, BYTE btType);
		void TeleToStandart(int aIndex);

		//CTime GetDate(char* Text);
		//char* SetDate(CTime Time);
};

extern cUtilits Utilits;

#endif