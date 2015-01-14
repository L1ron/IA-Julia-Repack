#ifndef MONSTER_H
#define MONSTER_H

#include "StdAfx.h"
#include "User.h"
#include "Logger.h"

#ifdef _GS
void MonsterAddTick(void * lpParam);
#endif

void MyItemSerialCreateSend(int aIndex, BYTE MapNumber, BYTE x, BYTE y, int type, BYTE level, BYTE dur, BYTE Op1, BYTE Op2, BYTE Op3, int LootIndex, BYTE NewOption, BYTE SetOption);
int MygEventMonsterItemDrop(BYTE *b_MonsterDataAddr,BYTE *a_gObjAddr);
int GetRandomOpExe(int quantOptions);
void __cdecl MonsterDie(LPOBJ lpObjOfMonster, LPOBJ lpObjOfPlayer);

class cMonster
{
	public:
#ifdef _GS
		void ReadMonsterAdd();
		int MonsterAddAndSpawn(int Mob, int Map, int Speed, int X1, int Y1, int X2, int Y2, int Dir);
		int SetBoxPosition(int TableNum, int mapnumber, int ax, int ay, int aw, int ah);
		void LoadGolden();
		bool GoldenDropFunc(int aIndex, BYTE MapNumber, BYTE x, BYTE y, int type, BYTE level, BYTE dur, BYTE Op1, BYTE Op2, BYTE Op3, int LootIndex, BYTE NewOption, BYTE SetOption);
#endif
		void LoadPkClear();
		bool NPCTalkEx(LPOBJ gObj, int NpcId);
		void NPCMessage(int IndexPlayer, LPOBJ mObj, char* Msg,...);
		void NPCMessageLog(sColor LogColor, sLogType LogType, LPOBJ gObj, LPOBJ mObj, char* Msg,...);
		void NPCMessageNear(LPOBJ mObj, char* Msg,...);
		int GetPartyMemberCount(LPOBJ lpObj);

		struct sPkClear
		{
			int Enabled;
			int NpcId;
			int OnlyForGm;
			int Type;
			DWORD PriceZen;
			DWORD PriceZenForAll;
			int PricePcPoints;
			int PricePcPointsForAll;
			int PriceWCoins;
			int PriceWCoinsForAll;
			int PriceWebPoints;
			int PriceWebPointsForAll;
			int LevelReq;
		};

		sPkClear ClearNpc;
		sPkClear ClearCommand;

#ifdef _GS
		struct sItemDrop
		{
			int Index;
			int ID;
			int Level;
			int Option;
			int Luck;
			int Skill;
			int Dur;
			int Exc;
			int Anc;
		};

		struct sGoldenDrop
		{
			sItemDrop Items[20];
			int NumItems;
		} GoldenDrop[20];
		int EnableGoldenDrop;
#endif

	private:
		void PkClear(LPOBJ gObj, LPOBJ NpcObj);
};

extern cMonster Monster;

#define OBJ_MAXMONSTER 7400
#endif