#include "ResetSystem.h"
#include "Logger.h"
#include "Configs.h"
#include "ChatCommands.h"
#include "Monster.h"
#include "Query.h"
#include "PCPoint.h"
#include "Utilits.h"

RSystem ResetSystem;

#define MAX_STATS 100

char Character[11];

void RSystem::Init()
{
	RConf.IsResetSystem = Configs.GetInt(0, 1, 1, "Customs", "EnableResetSystem", IAResetSystem);

	if(!RConf.IsResetSystem)
	{
		Log.ConsoleOutPut(1, c_Grey, t_RESET,"[X] [Reset System]\tInativo.");

		return;
	}

	RConf.MaximumReset	= Configs.GetInt(0,65535,50,"Customs","MaximumResets",IAResetSystem);
	RConf.ResetNPC		= Configs.GetInt(0,500,371,"Customs","ResetNPCID",IAResetSystem);

	NumStates =  Configs.GetInt(0, 20, 2, "Customs", "NumStates", IAResetSystem);

	char PState[10];
	char Items[20];

	Worked = 0;

	for(int i = 0; i < NumStates; i++)
	{
		wsprintf(PState, "State%d",i + 1);

		if(i > 0)
		{
			State[i].MaxRes =  Configs.GetInt(State[i - 1].MaxRes + 1, 32000, State[i-1].MaxRes + 5, PState, "MaxResets", IAResetSystem);
		}
		else
		{
			State[i].MaxRes =  Configs.GetInt(-1, 32000, 5, PState, "MaxResets", IAResetSystem);
			Log.ConsoleOutPut(1, c_Red, t_RESET, "[û] [Reset System]\t[%d] MaxResets = %d",i+1,State[i].MaxRes);
		}

		if(i > 0)
		{
			if(State[i-1].MaxRes >= State[i].MaxRes)
			{
				Log.ConsoleOutPut(1, c_Red, t_RESET, "[X] [Reset System]\tErro no MaxResets do State %d. E menor que o anterior. Funciona apemas com o %d primeiro State.",i+1,i);
				OffStates(i);

				return;
			}
			else
			{
				State[i].Work = true;

				Worked++;
			}
		}
		else
		{
			State[i].Work = true;

			Worked++;
		}

		State[i].Need.Zen		= Configs.GetInt(0, 2000000000, 100000, PState, "Need.Zen", IAResetSystem);

		State[i].Need.LvlDK		= Configs.GetInt(0, 400, 400, PState, "Need.LvlDK", IAResetSystem);
		State[i].Need.LvlDW		= Configs.GetInt(0, 400, 400, PState, "Need.LvlDW", IAResetSystem);
		State[i].Need.LvlDL		= Configs.GetInt(0, 400, 400, PState, "Need.LvlDL", IAResetSystem);
		State[i].Need.LvlSUM	= Configs.GetInt(0, 400, 400, PState, "Need.LvlSUM", IAResetSystem);
		State[i].Need.LvlELF	= Configs.GetInt(0, 400, 400, PState, "Need.LvlELF", IAResetSystem);
		State[i].Need.LvlMG		= Configs.GetInt(0, 400, 400, PState, "Need.LvlMG", IAResetSystem);

		State[i].Need.PcPoint	= Configs.GetInt(0, PCPoint.Config.MaximumPCPoints, 0, PState, "Need.PcPoint", IAResetSystem);
		State[i].Need.WCoin		= Configs.GetInt(0, PCPoint.Config.MaximumWCPoints, 0, PState, "Need.WCoin", IAResetSystem);

		State[i].Need.NumItems	= Configs.GetInt(0, 20, 0, PState, "Need.NumItems", IAResetSystem);

		State[i].Clear.Invent	= Configs.GetInt(0, 1, 1, PState, "Clear.Inventire", IAResetSystem);
		State[i].Clear.Points	= Configs.GetInt(0, 1, 1, PState, "Clear.Points", IAResetSystem);
		State[i].Clear.Command	= Configs.GetInt(0, 1, 1, PState, "Clear.Command", IAResetSystem);
		State[i].Clear.Quest	= Configs.GetInt(0, 1, 1, PState, "Clear.Quests", IAResetSystem);
		State[i].Clear.Skills	= Configs.GetInt(0, 1, 1, PState, "Clear.Skills", IAResetSystem);
		State[i].Clear.PcPoint	= Configs.GetInt(0, 1, 0, PState, "Clear.PcPoint", IAResetSystem);
		State[i].Clear.WCoin	= Configs.GetInt(0, 1, 0, PState, "Clear.WCoin", IAResetSystem);
		State[i].Clear.Zen		= Configs.GetInt(0, 1, 0, PState, "Clear.Zen", IAResetSystem);

		State[i].Add.Formula	= Configs.GetInt(0, 2, 1, PState, "Add.Formula", IAResetSystem);

		if(State[i].Add.Formula!=0)
		{
			State[i].Add.PointsDK	= Configs.GetInt(0, 32000, 200, PState, "Add.PointsDK", IAResetSystem);
			State[i].Add.PointsDW	= Configs.GetInt(0, 32000, 200, PState, "Add.PointsDW", IAResetSystem);
			State[i].Add.PointsDL	= Configs.GetInt(0, 32000, 200, PState, "Add.PointsDL", IAResetSystem);
			State[i].Add.PointsMG	= Configs.GetInt(0, 32000, 200, PState, "Add.PointsMG", IAResetSystem);
			State[i].Add.PointsSUM	= Configs.GetInt(0, 32000, 200, PState, "Add.PointsSUM", IAResetSystem);
			State[i].Add.PointsELF	= Configs.GetInt(0, 32000, 200, PState, "Add.PointsELF", IAResetSystem);
		}

		State[i].Add.PcPoint	= Configs.GetInt(0,  PCPoint.Config.MaximumPCPoints, 20, PState, "Add.PcPoint", IAResetSystem);
		State[i].Add.WCoin		= Configs.GetInt(0, PCPoint.Config.MaximumPCPoints, 20, PState, "Add.WCoin", IAResetSystem);

		if(State[i].Need.NumItems != 0)
		{
			for(int y = 0; y < State[i].Need.NumItems; y++)
			{
				wsprintf(Items, "Need.Item[%d].Num", y+1);
				State[i].Need.Items[y].Num		= Configs.GetInt(0, 20, 1, PState, Items, IAResetSystem);

				wsprintf(Items, "Need.Item[%d].Index", y+1);
				State[i].Need.Items[y].Group	= Configs.GetInt(0, 15, 0, PState, Items, IAResetSystem);

				wsprintf(Items, "Need.Item[%d].Type", y+1);
				State[i].Need.Items[y].Type		= Configs.GetInt(0, 255, 0, PState, Items, IAResetSystem);

				wsprintf(Items, "Need.Item[%d].Lvl", y+1);
				State[i].Need.Items[y].Lvl		= Configs.GetInt(0, 13, 0, PState, Items, IAResetSystem);

				wsprintf(Items, "Need.Item[%d].Luck", y+1);
				State[i].Need.Items[y].Luck		= Configs.GetInt(0, 1, 0, PState, Items, IAResetSystem);

				wsprintf(Items, "Need.Item[%d].Skill", y+1);
				State[i].Need.Items[y].Skill	= Configs.GetInt(0, 1, 0, PState, Items, IAResetSystem);

				wsprintf(Items, "Need.Item[%d].Opt", y+1);
				State[i].Need.Items[y].Opt		= Configs.GetInt(0, 7, 0, PState, Items, IAResetSystem);

				wsprintf(Items, "Need.Item[%d].Exc", y+1);
				State[i].Need.Items[y].Exc		= Configs.GetInt(0, 63, 0, PState, Items, IAResetSystem);
			}
		}
	}

	Log.ConsoleOutPut(1, c_Green, t_RESET, "[û] [Reset System]\tIniciado: %d estados de %d estao ativos.",Worked ,NumStates);
}

void RSystem::OffStates(int i)
{
	for(int x = i; x < MAX_STATS; x++)
	{
		State[x].Work = false;
	}
}

void RSystem::Reset(LPOBJ gObj)
{
	if(!RConf.IsResetSystem)
	{
		Chat.MessageLog(1, c_Blue, t_COMMANDS, gObj, "[ResetSystem] Comando inativo!");

		return;
	}

	int NumState = CheckState(gObj->m_Index);

	if(NumState == -1)
	{
		Chat.MessageLog(1, c_Red, t_RESET, gObj, "[Reset System] Inativo.");

		return;
	}

	if(NumState == -2)
	{
		Chat.MessageLog(1, c_Red, t_RESET, gObj, "[Reset System] Voce ja esta no limite de resets, impossivel continuar.");

		return;
	}

	if(!State[NumState].Work)
	{
		return;
	}

	int m_NeedLvl = CheckRole(gObj->DbClass, NumState, NeedLvl);

	if(m_NeedLvl > gObj->Level)
	{
		Chat.MessageLog(1, c_Red, t_RESET, gObj, "[Reset System] Seu level %d (Faltam %d leveis)!", gObj->Level,(m_NeedLvl - gObj->Level));

		return;
	}

	if(State[NumState].Need.Zen > 0)
	{
		if(gObj->Money < State[NumState].Need.Zen)
		{
			Chat.MessageLog(1, c_Red, t_RESET, gObj, "[Reset System] Voce precisa de %d zens! (Faltam %d zens)", State[NumState].Need.Zen, (State[NumState].Need.Zen - gObj->Money));

			return;
		}
	}

	if(State[NumState].Need.PcPoint > 0)
	{
		if(AddTab[gObj->m_Index].PC_PlayerPoints < State[NumState].Need.PcPoint)
		{
			Chat.MessageLog(1,c_Red, t_RESET, gObj, "[Reset System] You don't have %d PcPoints. Need %d more PcPoints. Now you have only %d PcPoints.", State[NumState].Need.PcPoint, State[NumState].Need.PcPoint-AddTab[gObj->m_Index].PC_PlayerPoints, AddTab[gObj->m_Index].PC_PlayerPoints);

			return;
		}
	}

	if(State[NumState].Need.WCoin > 0)
	{
		if(gObj->m_wCashPoint < State[NumState].Need.WCoin)
		{
			Chat.MessageLog(1, c_Red, t_RESET, gObj, "[Reset System] You don't have %d WCoin. Need %d more WCoin. Now you have only %d WCoin.", State[NumState].Need.WCoin, State[NumState].Need.WCoin-gObj->m_wCashPoint, gObj->m_wCashPoint);

			return;
		}
	}

	if(State[NumState].Need.NumItems > 0)
	{
		if(CheckItem(gObj, NumState) == false)
		{
			Chat.MessageLog(1, c_Red, t_RESET, gObj, "[Reset System] Voce nao tem os intens necessarios.");

			return;
		}
	}

	if(State[NumState].Need.Zen > 0)
	{
		gObj->Money -= State[NumState].Need.Zen;
		GCMoneySend(gObj->m_Index, gObj->Money);
	}

	gObj->Level = 1;
	gObj->Experience = 0;

	if(State[NumState].Need.WCoin > 0)
	{
		gObj->m_wCashPoint -= State[NumState].Need.WCoin;
		Me_MuOnlineQuery.ExecQuery("UPDATE MEMB_INFO SET CSPoints = CSPoints - %d WHERE memb___id = '%s'", State[NumState].Need.WCoin, gObj->AccountID);
		Me_MuOnlineQuery.Fetch();
		Me_MuOnlineQuery.Close();
	}

	if(State[NumState].Need.PcPoint > 0)
	{
		PCPoint.UpdatePoints(gObj,State[NumState].Need.PcPoint,MINUS,PCPOINT);
		MuOnlineQuery.ExecQuery("UPDATE Character SET PCPoint = PCPoint - %d WHERE Name= '%s'", State[NumState].Need.PcPoint, gObj->Name);
		MuOnlineQuery.Fetch();
		MuOnlineQuery.Close();
	}

	if(State[NumState].Clear.Invent)
	{
		for ( BYTE i = 0 ; i < 76 ; i ++ )
		{
			gObjInventoryDeleteItem ( gObj->m_Index , i );
			GCInventoryItemDeleteSend ( gObj->m_Index , i  , 1 );
		}
	}
	else
	{
		if(State[NumState].Need.NumItems > 0)
		{
			for(BYTE i = 0; i < 76;i ++)
			{
				if(State[NumState].Serial[i])
				{
					gObjInventoryDeleteItem ( gObj->m_Index , i );
					GCInventoryItemDeleteSend ( gObj->m_Index , i  , 1 );
				}
			}

		}
	}

	if(State[NumState].Clear.Points)
	{
		gObj->Strength = GetStartPoints(gObj->DbClass, Strength);
		gObj->Dexterity = GetStartPoints(gObj->DbClass, Dexterity);
		gObj->Vitality = GetStartPoints(gObj->DbClass, Vitality);
		gObj->Energy = GetStartPoints(gObj->DbClass, Energy);
	}

	if(State[NumState].Clear.Command)
	{
		gObj->Leadership = GetStartPoints(gObj->DbClass, Leadership);
	}

	if(State[NumState].Clear.PcPoint)
	{
		PCPoint.UpdatePoints(gObj,AddTab[gObj->m_Index].PC_PlayerPoints,MINUS,PCPOINT);
		MuOnlineQuery.ExecQuery("UPDATE Character SET PCPoint = 0 WHERE Name= '%s'", gObj->Name);
		MuOnlineQuery.Fetch();
		MuOnlineQuery.Close();
	}

	if(State[NumState].Clear.WCoin)
	{
		gObj->m_wCashPoint = 0;
		Me_MuOnlineQuery.ExecQuery("UPDATE MEMB_INFO SET CSPoints = 0 WHERE memb___id = '%s'", gObj->AccountID);
		Me_MuOnlineQuery.Fetch();
		Me_MuOnlineQuery.Close();
	}

	if(State[NumState].Clear.Zen)
	{
		gObj->Money = 0;
		GCMoneySend(gObj->m_Index, 0);
	}

	if(State[NumState].Add.PcPoint > 0)
	{
		PCPoint.UpdatePoints(gObj,State[NumState].Add.PcPoint,PLUS,PCPOINT);
		MuOnlineQuery.ExecQuery("UPDATE Character SET PCPoint = PCPoint + %d WHERE Name = '%s'",  State[NumState].Add.PcPoint, gObj->Name);
		MuOnlineQuery.Fetch();
		MuOnlineQuery.Close();
	}

	if(State[NumState].Add.WCoin > 0)
	{
		gObj->m_wCashPoint += State[NumState].Add.WCoin;
		Me_MuOnlineQuery.ExecQuery("UPDATE MEMB_INFO SET CSPoints = CSPoints + %d WHERE memb___id = '%s'", State[NumState].Add.WCoin, gObj->AccountID);
		Me_MuOnlineQuery.Fetch();
		Me_MuOnlineQuery.Close();
	}

	if(State[NumState].Add.Formula != 0)
	{
		gObj->LevelUpPoint = GetPoints(gObj, NumState, State[NumState].Add.Formula, gObj->LevelUpPoint);
	}

	switch(gObj->DbClass)
	{
		case 32: case 33: case 35:
		{
			// Noria (Todas classes Elf)
			gObjTeleport(gObj->m_Index,3,172,115);

			break;
		}
		case 80: case 81: case 83:
		{
			// Elbeland (Todas Classes Summoner)
			gObjTeleport(gObj->m_Index,51,52,225);

			break;
		}
		default:
		{
			// Lorencia (Todas Classes BK, MG, DL)
			gObjTeleport(gObj->m_Index,0,141,132);

			break;
		}
	}

	GCLevelUpMsgSend(gObj->m_Index,0);		// Warning shits :D
	gObjCalCharacter(Utilits.GetPlayerIndex(gObj->Name));

	/*
		Efeito Skill (Novo)
		GCMagicAttackNumberSend(gObj,72,gObj->m_Index,1);
	*/

	AddTab[gObj->m_Index].Resets++;

	MuOnlineQuery.ExecQuery("UPDATE Character SET %s = %s + 1 WHERE Name = '%s'",  RConf.ResetColumn, RConf.ResetColumn, gObj->Name);
	MuOnlineQuery.Fetch();
	MuOnlineQuery.Close();

	if(State[NumState].Clear.Skills)
	{
		DWORD ThreadID;
		HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ClearSkills, (void*)gObj->Name, 0, &ThreadID);

		if ( hThread == 0 )
		{
			Log.ConsoleOutPut(0, c_Red, t_NULL,"CreateThread() failed with error %d", GetLastError());

			return;
		}

		CloseHandle(hThread);
	}

	if(State[NumState].Clear.Quest)
	{
		DWORD ThreadID;
		HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ClearQuest, (void*)gObj->Name, 0, &ThreadID);

		if ( hThread == 0 )
		{
			Log.ConsoleOutPut(0, c_Red, t_NULL,"CreateThread() failed with error %d", GetLastError());

			return;
		}

		CloseHandle(hThread);
	}

}

unsigned long __stdcall ClearSkills(char Temp[11])
{
	char Name[11];
	strcpy(Name, Temp);
	Sleep(4500);

	MuOnlineQuery.ExecQuery("UPDATE Character SET MagicList = NULL WHERE Name = '%s'", Name);
	MuOnlineQuery.Fetch();
	MuOnlineQuery.Close();

	return 1;
}

unsigned long __stdcall ClearQuest(char Temp[11])
{
	char Name[11];
	strcpy(Name, Temp);
	Sleep(4000);
	MuOnlineQuery.ExecQuery("UPDATE Character SET Quest = NULL WHERE Name = '%s'", Name);
	MuOnlineQuery.Fetch();
	MuOnlineQuery.Close();


	MuOnlineQuery.ExecQuery("SELECT Class FROM Character WHERE Name = '%s'", Name);
	MuOnlineQuery.Fetch();
	int Class = MuOnlineQuery.GetAsInteger("Class");
	MuOnlineQuery.Close();

	int NewClass;
	switch (Class)
	{
		case 0:
		case 1:
		case 2:
		case 3:
		{
			NewClass = 0;
			break;
		}
		case 16:
		case 17:
		case 18:
		case 19:
		{
			NewClass = 16;
			break;
		}
		case 32:
		case 33:
		case 34:
		case 35:
		{
			NewClass = 32;
			break;
		}
		case 48:
		case 49:
		case 50:
		{
			NewClass = 48;
			break;
		}
		case 64:
		case 65:
		case 66:
		{
			NewClass = 64;
			break;
		}
		case 80:
		case 81:
		case 82:
		case 83:
		{
			NewClass = 80;
			break;
		}
	}

	MuOnlineQuery.ExecQuery("UPDATE Character SET Class = %d WHERE Name = '%s'", NewClass, Name);
	MuOnlineQuery.Fetch();
	MuOnlineQuery.Close();

	return 1;
}

long int RSystem::GetPoints(LPOBJ gObj, int NumState, int Formula, int StartPoint)
{
	if(Formula == 1)
	{
		StartPoint = StartPoint + CheckRole(gObj->DbClass, NumState, Points);
	}
	else if(Formula == 2)
	{
		StartPoint = (AddTab[gObj->m_Index].Resets + 1) * CheckRole(gObj->DbClass, NumState, Points);
	}

	return StartPoint;
}

int RSystem::GetStartPoints(unsigned char Class, ForPoints Points)
{
	switch (Class)
	{
		case 0:
		case 1:
		case 2:
		case 3:
		{
			if(Points == Strength) return 18;
			if(Points == Dexterity) return 18;
			if(Points == Vitality) return 15;
			if(Points == Energy) return 30;

			break;
		}
		case 16:
		case 17:
		case 18:
		case 19:
		{
			if(Points == Strength) return 28;
			if(Points == Dexterity) return 20;
			if(Points == Vitality) return 25;
			if(Points == Energy) return 10;

			break;
		}
		case 32:
		case 33:
		case 34:
		case 35:
		{
			if(Points == Strength) return 22;
			if(Points == Dexterity) return 25;
			if(Points == Vitality) return 20;
			if(Points == Energy) return 15;

			break;
		}
		case 48:
		case 49:
		case 50:
		{
			if(Points == Strength) return 26;
			if(Points == Dexterity) return 26;
			if(Points == Vitality) return 26;
			if(Points == Energy) return 26;

			break;
		}
		case 64:
		case 65:
		case 66:
		{
			if(Points == Strength) return 26;
			if(Points == Dexterity) return 20;
			if(Points == Vitality) return 20;
			if(Points == Energy) return 15;
			if(Points == Leadership) return 25;

			break;
		}
		case 80:
		case 81:
		case 82:
		case 83:
		{
			if(Points == Strength) return 21;
			if(Points == Dexterity) return 21;
			if(Points == Vitality) return 18;
			if(Points == Energy) return 23;

			break;
		}
	}

	return 0;
}

bool RSystem::CheckItem(LPOBJ gObj, int NumState)
{
	int NumItem	= State[NumState].Need.NumItems;
	int NumSpesItem;

	int Num_Items = 0;
	int m_NumSpesItem[20];
	int x_NumItem = 0;

	for(int xo = 0; xo < 76; xo++)
	{
		State[NumState].Serial[xo] = false;
	}

	for(int x = 0; x < NumItem; x++)
	{
		m_NumSpesItem[x] = 0;
		NumSpesItem = State[NumState].Need.Items[x].Num;
		x_NumItem += NumSpesItem;
		State[NumState].Need.Items[x].Index = (State[NumState].Need.Items[x].Group * 512 + State[NumState].Need.Items[x].Type);

		for(BYTE i = 12; i < 76 ; i ++ )
		{
			if
			(
				gObj->pInventory[i].m_Type == State[NumState].Need.Items[x].Index &&
				gObj->pInventory[i].m_Level == State[NumState].Need.Items[x].Lvl &&
				gObj->pInventory[i].m_Option2 == State[NumState].Need.Items[x].Luck &&
				gObj->pInventory[i].m_Option1 == State[NumState].Need.Items[x].Skill &&
				gObj->pInventory[i].m_Option3 == State[NumState].Need.Items[x].Opt &&
				gObj->pInventory[i].m_NewOption == State[NumState].Need.Items[x].Exc &&
				m_NumSpesItem[x] < NumSpesItem
			)
			{
				if(!State[NumState].Serial[i])
				{
					CheckItemSerial(gObj,NumState,i);
					m_NumSpesItem[x]++;
					Num_Items++;
				}
			}
		}
	}

	if(Num_Items >= x_NumItem)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void RSystem::CheckItemSerial(LPOBJ gObj, int NumState, BYTE Serial)
{
	unsigned long Ser = gObj->pInventory[Serial].m_Number;

	for(BYTE i = 12; i < 76 ; i ++ )
	{
		if(gObj->pInventory[i].m_Number == Ser)
		{
			State[NumState].Serial[i] = true;
		}
	}
}

int RSystem::CheckRole(unsigned char Class,int NumState, ForRole Role)
{
	switch (Class)
	{
		case 0: case 1: case 2: case 3:
		{
			if(Role == NeedLvl)
			{
				return State[NumState].Need.LvlDW;
			}
			else if(Role == Points)
			{
				return State[NumState].Add.PointsDW;
			}

			break;
		}
		case 16: case 17: case 18: case 19:
		{
			if(Role == NeedLvl)
			{
				return State[NumState].Need.LvlDK;
			}
			else if(Role == Points)
			{
				return State[NumState].Add.PointsDK;
			}

			break;
		}
		case 32: case 33: case 34: case 35:
		{
			if(Role == NeedLvl)
			{
				return State[NumState].Need.LvlELF;
			}
			else if(Role == Points)
			{
				return State[NumState].Add.PointsELF;
			}

			break;
		}
		case 48: case 49: case 50:
		{
			if(Role == NeedLvl)
			{
				return State[NumState].Need.LvlMG;
			}
			else if(Role == Points)
			{
				return State[NumState].Add.PointsMG;
			}

			break;
		}
		case 64: case 65: case 66:
		{
			if(Role == NeedLvl)
			{
				return State[NumState].Need.LvlDL;
			}
			else if(Role == Points)
			{
				return State[NumState].Add.PointsDL;
			}

			break;
		}
		case 80: case 81: case 82: case 83:
		{
			if(Role == NeedLvl)
			{
				return State[NumState].Need.LvlSUM;
			}
			else if(Role == Points)
			{
				return State[NumState].Add.PointsSUM;
			}

			break;
		}
	}

	return 0;
}

int RSystem::CheckState(DWORD Index)
{
	for(int i = 0; i < NumStates; i++)
	{
		if(State[i].Work)
		{
			if(State[i].MaxRes == -1)
			{
				return i;
			}
			else if(State[i].MaxRes >= AddTab[Index].Resets)
			{
				return i;
			}
			else if(i == Worked -1)
			{
				return -2;
			}
		}
	}

	return -1;
}

extern RSystem ResetSystem;