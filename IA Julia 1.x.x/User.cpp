#include "StdAfx.h"
#include "User.h"
#include "Configs.h"
#include "GMSystem.h"
#include "ChatCommands.h"
#include "Logger.h"
#include "MapSystem.h"
#include "PCPoint.h"
#include "MossGambler.h"
#include "Query.h"
#include "DuelManager.h"
#include "Vip.h"
#include "HappyHour.h"
#include "PlayerSystem.h"
#include "Territory.h"
#include "Utilits.h"
#include "ResetSystem.h"
#include "MarrySystem.h"
#include "Helpers.h"
#include "Quests.h"

sAddTab AddTab[OBJECT_MAX];
cUser User;

bool cUser::CheckMaxPoints(BYTE type, OBJECTSTRUCT* lpObj)
{
	bool bResult = false;

	int MaxPoints = 32000;

	if(Configs.Enable65kStats >= 1)
	{
		MaxPoints = -536;
	}

	int Stats;

	switch (type)
	{
	case 0x00:
		Stats = lpObj->Strength;
		if(Configs.MaxStatsSystemEnable)
		{
			if(lpObj->Class == 0)
				MaxPoints = Configs.MaxDW_Strength;
			else if(lpObj->Class == 1)
				MaxPoints = Configs.MaxDK_Strength;
			else if(lpObj->Class == 2)
				MaxPoints = Configs.MaxELF_Strength;
			else if(lpObj->Class == 3)
				MaxPoints = Configs.MaxMG_Strength;
			else if(lpObj->Class == 4)
				MaxPoints = Configs.MaxDL_Strength;
			else if(lpObj->Class == 5)
				MaxPoints = Configs.MaxSUM_Strength;
		}
		break;
	case 0x01:
		Stats = lpObj->Dexterity;
		if(Configs.MaxStatsSystemEnable)
		{
			if(lpObj->Class == 0)
				MaxPoints = Configs.MaxDW_Agility;
			else if(lpObj->Class == 1)
				MaxPoints = Configs.MaxDK_Agility;
			else if(lpObj->Class == 2)
				MaxPoints = Configs.MaxELF_Agility;
			else if(lpObj->Class == 3)
				MaxPoints = Configs.MaxMG_Agility;
			else if(lpObj->Class == 4)
				MaxPoints = Configs.MaxDL_Agility;
			else if(lpObj->Class == 5)
				MaxPoints = Configs.MaxSUM_Agility;
		}
		break;
	case 0x02:
		Stats = lpObj->Vitality;
		if(Configs.MaxStatsSystemEnable)
		{
			if(lpObj->Class == 0)
				MaxPoints = Configs.MaxDW_Vitality;
			else if(lpObj->Class == 1)
				MaxPoints = Configs.MaxDK_Vitality;
			else if(lpObj->Class == 2)
				MaxPoints = Configs.MaxELF_Vitality;
			else if(lpObj->Class == 3)
				MaxPoints = Configs.MaxMG_Vitality;
			else if(lpObj->Class == 4)
				MaxPoints = Configs.MaxDL_Vitality;
			else if(lpObj->Class == 5)
				MaxPoints = Configs.MaxSUM_Vitality;
		}
		break;
	case 0x03:
		Stats = lpObj->Energy;
		if(Configs.MaxStatsSystemEnable)
		{
			if(lpObj->Class == 0)
				MaxPoints = Configs.MaxDW_Energy;
			else if(lpObj->Class == 1)
				MaxPoints = Configs.MaxDK_Energy;
			else if(lpObj->Class == 2)
				MaxPoints = Configs.MaxELF_Energy;
			else if(lpObj->Class == 3)
				MaxPoints = Configs.MaxMG_Energy;
			else if(lpObj->Class == 4)
				MaxPoints = Configs.MaxDL_Energy;
			else if(lpObj->Class == 5)
				MaxPoints = Configs.MaxSUM_Energy;
		}
		break;
	case 0x04:
		Stats = lpObj->Leadership;
		if(Configs.MaxStatsSystemEnable)
		{
			if(lpObj->Class == 4)
				MaxPoints = Configs.MaxDL_Command;
		}
		break;
	}

	if(MaxPoints > 32767)
	{
		MaxPoints = -32768 + (MaxPoints - 32767);
	}

	if((MaxPoints > 0) && (Stats >= MaxPoints || Stats < 0))
	{
		bResult = true;
	}
	else if((MaxPoints < 0) && (Stats < 0) && (Stats >= MaxPoints))
	{
		bResult = true;
	}

	return bResult;
}

void gObjLevelUpPointAddEx(BYTE type, OBJECTSTRUCT* lpObj)
{
	bool bError = false;

	if(User.CheckMaxPoints(type, lpObj))
	{
		bError = true;
	}

	if(bError == true)
	{
		BYTE cShowAddPointError[0x30] =
		{
			0xC1,0x30,0x0D,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
		};

		sprintf((char *)&cShowAddPointError[0x0D], "Error in Stats adding");
	}
	else
	{
		gObjLevelUpPointAdd(type, lpObj);
	}
}

void cUser::gObjCharacterWingsSetPreview(short ItemType, unsigned char *CharSet,int Type,OBJECTSTRUCT *lpObj)
{
	if(Type == GUARDIAN)
	{
		register unsigned char PreviewPet = 0;

		switch(ItemType)
		{
		case 0x1A50: //Panda
			PreviewPet = 224;
			break;

		case 0x1A43:
			PreviewPet = 0x80;
			break;

		case 0x1A41:
			PreviewPet = 0x40;
			break;

		case 0x1A40:
			PreviewPet = 0x20;
			break;

		case 0x1A7B: //Skeleton
			CharSet[5] -= 3;
			PreviewPet = 96; //112
			break;

		default:
			PreviewPet = 0;
			break;
		}

		CharSet[16] |= PreviewPet;
	}
}

void __stdcall gObjViewportPatchExecute(OBJECTSTRUCT *lpObj)
{
	if(lpObj->pInventory[GUARDIAN].m_Type != SLOT_EMPTY)
	{
		User.gObjCharacterWingsSetPreview(lpObj->pInventory[GUARDIAN].m_Type, lpObj->CharSet, GUARDIAN,lpObj);
	}
}

#define CS_SET_BOOTS1(x) ( ((x) & 0x1E0) >> 5 )
#define CS_SET_BOOTS2(x) ( ((x) & 0x10 ) >> 1 )
#define CS_SET_BOOTS3(x) ( ((x) & 0x0F ) << 4 )

//Fix Visual in Select Character
void __stdcall JGPGetCharInfoEx(int Loop, unsigned char *DSPacket, unsigned char *toClientPacket) {
	unsigned char ItemType = DSPacket[76 + (66 * Loop)]; //72 - Wings, 76 - Guardian
	register int nCol = (Loop * 34) + 38;
	register int CharSet5 = (Loop * 34) + 27; //CharSet[5]
	register int CharSet9 = (Loop * 34) + 31; //CharSet[9]
	register int CharSet10 = (Loop * 34) + 32; //CharSet[10]
	register int CharSet15 = (Loop * 34) + 37; //CharSet[15]
	register int CharSet17 = (Loop * 34) + 39; //CharSet[17]

	unsigned char Boots = DSPacket[68 + (66 * Loop)]; //Boots on Char
	unsigned char BootsLvl = DSPacket[69 + (66 * Loop)]; //Boots Level

	switch(ItemType)
	{
	case 0x50:
		toClientPacket[nCol] |= 224;
		break;
	case 0x7B:
		toClientPacket[CharSet5]  -= 3;
		toClientPacket[nCol] |= 96;

		break;
	}

	if(Boots == 255)
	{
		toClientPacket[CharSet5] |= CS_SET_BOOTS3(-1);
	}
}

void FireworkOnTheScreen(LPOBJ gObj)
{
	PMSG_SERVERCMD ServerCmd;
	PHeadSubSetB((LPBYTE)&ServerCmd, 0xF3, 0x40, sizeof(ServerCmd));
	ServerCmd.CmdType = 0;
	for(int x = 0; x < 10; x+=2)
	{
		for(int y = 0; y < 10; y+=2)
		{
			ServerCmd.X = gObj->X + x - 5;
			ServerCmd.Y = gObj->Y + y - 5;
			MsgSendV2(gObj, (LPBYTE)&ServerCmd, sizeof(ServerCmd));
			DataSend(gObj->m_Index, (LPBYTE)&ServerCmd, sizeof(ServerCmd));
		}
	}
}

void GCKillPlayerExpSendHook(int aIndex, int TargetIndex, long exp, int AttackDamage, int MSBFlag)
{
	if(aIndex < OBJECT_MIN || aIndex > OBJECT_MAX)
	{
		return;
	}

	OBJECTSTRUCT * lpObj = (OBJECTSTRUCT*) OBJECT_POINTER (aIndex);
	int Proc = 0;

	if(lpObj->pInventory[8].m_Type == 0x1A50) // Panda
	{
		Proc += Configs.Panda.PetPandaExpirence;
	}

	if(lpObj->pInventory[10].m_Type == 0x1A4C || lpObj->pInventory[11].m_Type == 0x1A4C) // Panda Ring
	{
		Proc += Configs.Panda.PandaRingExpirence;
	}

	//VIPSystem	Exp
	if(Vip.Config.Enabled)
	{
		Proc += Vip.GetBonus(lpObj, b_EXP);
	}

	//MapSystem Exp
	if(MapSystem.Enabled && MapSystem.Maps[lpObj->MapNumber].Exp != 0)
	{
		Proc += MapSystem.Maps[lpObj->MapNumber].Exp;
	}

	//HappyHour Exp
	int IsHappyHour = HappyHour.IsHappyHour(lpObj->MapNumber);

	if(IsHappyHour)
	{
		Proc += HappyHour.HappyStruct[IsHappyHour].P_Exp;
	}

	//Player System
	if(PlayerSystem.Enabled)
	{
		Proc +=  PlayerSystem.GetBonus(lpObj, b_EXP);
	}

	int Index = Utilits.GetPlayerIndex(AddTab[lpObj->m_Index].MarryName);

	if(Marry.Config.MarryExpBonus > 0 && Index != -1)
	{
		Proc += Marry.Config.MarryExpBonus;
	}
	
	long NewExp		= exp + ((exp * Proc) / 100);
	lpObj->Experience		+= NewExp;

	GCKillPlayerExpSend(aIndex , TargetIndex , NewExp, AttackDamage , MSBFlag);
}

void MyObjCalCharacter(int aIndex)
{
	OBJECTSTRUCT * lpObj = (OBJECTSTRUCT*) OBJECT_POINTER (aIndex);

	gObjCalCharacter(aIndex);

	if(lpObj->pInventory[8].m_Type == 0x1A50) //Panda
	{
		lpObj->m_Defense				+= Configs.Panda.PetPandaDefense;
		lpObj->m_AttackDamageMinLeft	+= Configs.Panda.PetPandaAttackDamageMinLeft;
		lpObj->m_AttackDamageMaxLeft	+= Configs.Panda.PetPandaAttackDamageMaxLeft;
		lpObj->m_AttackDamageMinRight	+= Configs.Panda.PetPandaAttackDamageMinRight;
		lpObj->m_AttackDamageMaxRight	+= Configs.Panda.PetPandaAttackDamageMaxRight;
		lpObj->m_MagicDamageMin			+= Configs.Panda.PetPandaMagicDamageMin;
		lpObj->m_MagicDamageMax			+= Configs.Panda.PetPandaMagicDamageMax;
		lpObj->m_MagicSpeed				+= Configs.Panda.PetPandaMagicSpeed;
		lpObj->m_AttackSpeed			+= Configs.Panda.PetPandaAttackSpeed;
	}

	if(lpObj->pInventory[10].m_Type == 0x1A4C || lpObj->pInventory[11].m_Type == 0x1A4C) // Panda Ring
	{
		lpObj->m_Defense				+= Configs.Panda.PandaRingDefense;
		lpObj->m_AttackDamageMinLeft	+= Configs.Panda.PandaRingAttackDamageMinLeft;
		lpObj->m_AttackDamageMaxLeft	+= Configs.Panda.PandaRingAttackDamageMaxLeft;
		lpObj->m_AttackDamageMinRight	+= Configs.Panda.PandaRingAttackDamageMinRight;
		lpObj->m_AttackDamageMaxRight	+= Configs.Panda.PandaRingAttackDamageMaxRight;
		lpObj->m_MagicDamageMin			+= Configs.Panda.PandaRingMagicDamageMin;
		lpObj->m_MagicDamageMax			+= Configs.Panda.PandaRingMagicDamageMax;
		lpObj->m_MagicSpeed				+= Configs.Panda.PandaRingMagicSpeed;
		lpObj->m_AttackSpeed			+= Configs.Panda.PandaRingAttackSpeed;
	}
}

//Wait 2 miliseconds for update
void TradeSystem__Cancel(void * lpParam)
{
	Sleep(200);
	for(int i=OBJECT_MIN; i<OBJECT_MAX; i++)
	{
		OBJECTSTRUCT * gObj = (OBJECTSTRUCT*)OBJECT_POINTER(i);
		if(gObj->Connected == PLAYER_PLAYING)
		{
			if(gObj->pInventory[RING_01].m_Type == 0x1A7A || gObj->pInventory[RING_02].m_Type == 0x1A7A) //Skeleton Ring
			{
				gObj->m_Change = 14;

				gObjViewportListProtocolCreate(gObj);
			}
		}
	}

	_endthread();
}

bool cUser::CharacterCreate(PMSG_CHARCREATE* lpMsg, int aIndex)
{
	bool bResult = false;

	for(int i = 0; i < sizeof(lpMsg->Name); i++)
	{
		if(!isalnum(lpMsg->Name[i]) && lpMsg->Name[i] != ' ' && lpMsg->Name[i] != NULL)
		{
			bResult = true;
		}
	}

	return bResult;
}

bool cUser::GuildMasterInfoSave(int aIndex,PMSG_GUILDINFOSAVE* lpMsg)
{
	bool bResult = false;
	for(int i = 0; i < sizeof(lpMsg->GuildName); i++)
	{
		if(!isalnum(lpMsg->GuildName[i]) && lpMsg->GuildName[i] != ' ' && lpMsg->GuildName[i] != NULL)
		{
			bResult = true;

		}
	}
	if(bResult)
	{
		PMSG_GUILDCREATED_RESULT pMsg;

		PHeadSetB((LPBYTE)&pMsg, 0x56, sizeof(pMsg));
		pMsg.Result = 5;

		DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
	}

	return bResult;
}
void GCEquipmentSendHook(int aIndex)
{
	OBJECTSTRUCT * gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);

	GCEquipmentSend(aIndex);

	//Fix Double Pets on trade cancel/ok/success
	if(gObj->pInventory[8].m_Type != SLOT_EMPTY)
	{
		if(gObj->pInventory[8].m_Type == 0x1A50 || gObj->pInventory[8].m_Type == 0x1A7B)
		{
			CItem OldItem;
			OldItem = gObj->pInventory[8];
			gObj->pInventory[8].m_Type = -1;

			gObjMakePreviewCharSet(aIndex);
			GCItemListSend(aIndex);
			gObjViewportListProtocolCreate(gObj);

			gObj->pInventory[8] = OldItem;

			gObjMakePreviewCharSet(aIndex);
			GCItemListSend(aIndex);
			gObjViewportListProtocolCreate(gObj);
		}
	}

	if(gObj->pInventory[RING_01].m_Type == 0x1A7A || gObj->pInventory[RING_02].m_Type == 0x1A7A) //Skeleton Ring
	{
		_beginthread(TradeSystem__Cancel, 0, NULL);
	}
}

void cUser::RingSkin(LPOBJ gObj)
{
	if(gObj->pInventory[RING_01].m_Type == 0x1A4C && gObj->m_Change != 503 || gObj->pInventory[RING_02].m_Type == 0x1A4C && gObj->m_Change != 503)
	{
		gObj->m_Change = 503;
		gObjViewportListProtocolCreate(gObj);
	}
}

void cUser::CheckRingSend(LPOBJ gObj, unsigned char* aSend)
{
	if(aSend[4] == RING_01 || aSend[4] == RING_02)
	{
		if(gObj->pInventory[RING_01].m_Type == 0x1A4C && gObj->m_Change != 503 || gObj->pInventory[RING_02].m_Type == 0x1A4C && gObj->m_Change != 503)
		{
			gObj->m_Change = 503;
			gObjViewportListProtocolCreate(gObj);
		}
	}
}

void cUser::CheckRing(LPOBJ gObj, LPBYTE aRecv)
{
	if
	(
		(aRecv[4] == RING_01 && gObj->pInventory[RING_02].m_Type != 0x1A4C) ||
		(aRecv[4] == RING_02 && gObj->pInventory[RING_01].m_Type != 0x1A4C)
	)
	{
		if(gObj->m_Change == 503)
		{
			gObj->m_Change = -1;
			gObjViewportListProtocolCreate(gObj);
		}
	}
}

bool cUser::CGPartyRequestRecv(PMSG_PARTYREQUEST * lpMsg, int aIndex)
{
	int number =  MAKE_NUMBERW(lpMsg->NumberH, lpMsg->NumberL);
	OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);
	OBJECTSTRUCT *pObj = (OBJECTSTRUCT*)OBJECT_POINTER(number);

	if ( number < 0 || number > OBJECT_MAX-1)
	{
		return false;
	}

	if(!Utilits.gObjIsConnected(number))
	{
		return false;
	}

	if(gObj->Level > pObj->Level && gObj->Level - pObj->Level >= Configs.PartyGapLvl)
	{
		Chat.MessageLog(1, c_Red, t_Default, gObj, "[Party] You can't stay with %s in party! %s needs %d more lvl.", pObj->Name, pObj->Name, gObj->Level-Configs.PartyGapLvl - pObj->Level);
		
		return true;
	}

	if(gObj->Level < pObj->Level && pObj->Level - gObj->Level >= Configs.PartyGapLvl)
	{
		Chat.MessageLog(1, c_Red, t_Default, gObj, "[Party] You can't stay with %s in party! You need %d more lvl.", pObj->Name, pObj->Level - Configs.PartyGapLvl - gObj->Level);
		
		return true;
	}
	return false;
}

void cUser::CheckTeleport(LPOBJ gObj)
{
	if
	(
		(gObj->MapNumber == 9) ||
		(gObj->MapNumber >= 11 && gObj->MapNumber <= 29) ||
		(gObj->MapNumber == 32) ||
		(gObj->MapNumber == 36) ||
		(gObj->MapNumber >= 41 && gObj->MapNumber <= 50) ||
		(gObj->MapNumber == 52) ||
		(gObj->MapNumber == 53) ||
		(gObj->MapNumber == 58) ||
		(gObj->MapNumber == 62)
	)
	{
		Utilits.TeleToStandart(gObj->m_Index);
	}

#ifdef _GS
	if(gObj->MapNumber == 30 || gObj->MapNumber == 31 || gObj->MapNumber == 34)
		Utilits.TeleToStandart(gObj->m_Index);
#endif
}

void cUser::PlayerConnect(LPOBJ gObj)
{
	RingSkin(gObj);
	CheckTeleport(gObj);

	MuOnlineQuery.ExecQuery("SELECT PCPoint, DuelWins, DuelLoses, Territory_Type, Territory_Time,IsMarried,MarryName, %s FROM Character WHERE Name = '%s'", ResetSystem.RConf.ResetColumn, gObj->Name);
	MuOnlineQuery.Fetch();
	int PcPoints					= MuOnlineQuery.GetAsInteger("PCPoint");
	int DuelWins					= MuOnlineQuery.GetAsInteger("DuelWins");
	int DuelLoses					= MuOnlineQuery.GetAsInteger("DuelLoses");
	AddTab[gObj->m_Index].Resets	= MuOnlineQuery.GetAsInteger(ResetSystem.RConf.ResetColumn);
	AddTab[gObj->m_Index].TERR_Type	= MuOnlineQuery.GetAsInteger("Territory_Type");
	AddTab[gObj->m_Index].TERR_Min	= MuOnlineQuery.GetAsInteger("Territory_Time");
	AddTab[gObj->m_Index].IsMarried	= MuOnlineQuery.GetAsInteger("IsMarried");
	MuOnlineQuery.GetAsString("MarryName", AddTab[gObj->m_Index].MarryName);
	MuOnlineQuery.Close();

	LoginMsg(gObj);

	if(ResetCheck(gObj))
	{
		return;
	}

	if(Vip.Config.Enabled)
	{
		Me_MuOnlineQuery.ExecQuery("SELECT %s, %s, VIP_ONOFF FROM MEMB_INFO WHERE memb___id = '%s'", Vip.Config.Column, Vip.Config.ColumnDate, gObj->AccountID);
		Me_MuOnlineQuery.Fetch();
		AddTab[gObj->m_Index].VIP_Type	= Me_MuOnlineQuery.GetAsInteger(Vip.Config.Column);
		AddTab[gObj->m_Index].VIP_Min	= Me_MuOnlineQuery.GetAsInteger(Vip.Config.ColumnDate);
		AddTab[gObj->m_Index].VIP_On	= Me_MuOnlineQuery.GetAsInteger("VIP_ONOFF");
		Me_MuOnlineQuery.Close();
	}

	Me_MuOnlineQuery.ExecQuery("SELECT CSPoints FROM MEMB_INFO WHERE memb___id = '%s'", gObj->AccountID);
	Me_MuOnlineQuery.Fetch();
	gObj->m_wCashPoint = (unsigned short)Me_MuOnlineQuery.GetAsInteger("CSPoints");
	Me_MuOnlineQuery.Close();

	PCPoint.InitPCPointForPlayer(gObj, PcPoints);

	if(PCPoint.Config.WebEnabled)
	{
		MuOnlineQuery.ExecQuery("SELECT %s FROM %s WHERE memb___id = '%s'",PCPoint.Config.WebColumn ,PCPoint.Config.WebTable , gObj->AccountID);
		MuOnlineQuery.Fetch();

		if(PCPoint.Config.WebColumnFloat)
		{
			AddTab[gObj->m_Index].WEB_Points_Float	= MuOnlineQuery.GetAsFloat(PCPoint.Config.WebColumn);
		}
		else
		{
			AddTab[gObj->m_Index].WEB_Points		= MuOnlineQuery.GetAsInteger(PCPoint.Config.WebColumn);
		}

		MuOnlineQuery.Close();
	}

	// Warehouse check
	MuOnlineQuery.ExecQuery("SELECT UsedSlot FROM warehouse WHERE AccountID = '%s'", gObj->AccountID);
	MuOnlineQuery.Fetch();
	int UsedSlot = MuOnlineQuery.GetAsInteger("UsedSlot");
	MuOnlineQuery.Close();

	if((UsedSlot < 1 || UsedSlot > Configs.Commands.NumberOfVaults) && Configs.Commands.IsMultyVault)
	{
		bool Result = false;
		char szTemp[128];

		for(int i=1; i<=Configs.Commands.NumberOfVaults; i++)
		{
			byte Temp[1920];
			wsprintf(szTemp, "SELECT Items%02d FROM warehouse WHERE AccountID='%s'", i, gObj->AccountID);

			if ( MuOnlineQuery.GetAsBinary(szTemp, Temp) > 0 )
			{
				Result = true;
			}

			MuOnlineQuery.Close();
		}

		if(!Result)
		{
			MuOnlineQuery.ExecQuery("UPDATE warehouse SET Items01 = Items, UsedSlot = 1 WHERE AccountID = '%s'", gObj->AccountID);
			MuOnlineQuery.Fetch();
			MuOnlineQuery.Close();
		}
	}

	AddTab[gObj->m_Index].ON_Min			= 0;
	AddTab[gObj->m_Index].ON_Sek			= 0;
	AddTab[gObj->m_Index].ON_Hour			= 0;
	AddTab[gObj->m_Index].PC_OnlineTimer	= 0;
	AddTab[gObj->m_Index].ADD_Type			= -1;
	AddTab[gObj->m_Index].ADD_Value			= 0;
	AddTab[gObj->m_Index].TERR_TypeOnMap	= -1;
	AddTab[gObj->m_Index].TERR_Map			= 0;
	AddTab[gObj->m_Index].TERR_X			= 0;
	AddTab[gObj->m_Index].TERR_Y			= 0;
	AddTab[gObj->m_Index].VIP_Map			= 0;
	AddTab[gObj->m_Index].VIP_X				= 0;
	AddTab[gObj->m_Index].VIP_Y				= 0;
	AddTab[gObj->m_Index].OfflineTrade		= false;

	CTime ct = CTime::GetCurrentTime();
	AddTab[gObj->m_Index].POST_BanSignal	= false;
	AddTab[gObj->m_Index].POST_BanTime		= ct;
	AddTab[gObj->m_Index].CHAT_BanSignal	= false;
	AddTab[gObj->m_Index].CHAT_BanTime		= ct;
	AddTab[gObj->m_Index].MarryType = -1;

#ifdef _GS
	if(DuelSystem.Config.Enabled)
	{
		if(DuelSystem.Config.Ranking)
		{
			DuelSystem.DuelSetInfo(gObj, DuelWins, DuelLoses);
		}

		if((!DuelSystem.IsOnDuel(gObj->m_Index)) && gObj->MapNumber == 64)
		{
			gObjMoveGate(gObj->m_Index, DuelSystem.Config.DuelGate);
			Log.ConsoleOutPut(1, c_Blue ,t_Duel, "[Duel System][%s][%s]\tSpawn on duel map after duel is not allowed", gObj->AccountID, gObj->Name);
		}

		DuelSystem.UserDuelInfoReset(gObj);
	}
#endif
	Vip.Connect(gObj);
	Territory.Connect(gObj);
	Helpers.Connect(gObj);
	Quests.Connect(gObj);
}

void cUser::LoginMsg(LPOBJ gObj)
{
	Chat.Message(0,gObj,Configs.ConnectNotice);

	if(Configs.ConnectInfo == 1)
	{
		SYSTEMTIME t;
		GetLocalTime(&t);

		Chat.Message(1,gObj,"Online: %d Player(s), %d GM(s)",(Log.Online_All - Log.Online_Gms), Log.Online_Gms);
		Chat.Message(1,gObj,"Hora e data: %02d:%02d:%02d (%02d-%02d-%04d)", t.wHour, t.wMinute, t.wSecond, t.wDay, t.wMonth, t.wYear);
	}

	if (AddTab[gObj->m_Index].IsMarried)
	{
		OBJECTSTRUCT *tObj = (OBJECTSTRUCT*)OBJECT_POINTER(Utilits.GetPlayerIndex(AddTab[gObj->m_Index].MarryName));
		
		if(AddTab[gObj->m_Index].MarryName[0] != '\0')
		{
			if(Utilits.gObjIsConnected(Utilits.GetPlayerIndex(AddTab[gObj->m_Index].MarryName)))
			{
				Chat.Message(1, gObj, "[Marry] You are married, %s is now online!", AddTab[gObj->m_Index].MarryName);
				Chat.Message(1, tObj, "[Marry] %s getting online!", gObj->Name);
			}
			else
			{
				Chat.Message(1, gObj, "[Marry] You are married, %s is now offline!", AddTab[gObj->m_Index].MarryName);
			}
		}
	}

	switch(GmSystem.IsAdmin(gObj->Name))
	{
		case 1:
		{
			Chat.MessageAllLog(0, 0, c_Green, t_GM, gObj, "[Admin] %s conectado!", gObj->Name);

			break;
		}
		case 2:
		{
			Chat.MessageAllLog(0, 0, c_Green, t_GM, gObj, "[GM] %s conectado!", gObj->Name);

			break;
		}
	}
}

BOOL gObjGameClose_Func(int aIndex)
{
	OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);

	switch(GmSystem.IsAdmin(gObj->Name))
	{
	case 1:
		{
			Chat.MessageAllLog(0, 0, c_Green, t_GM, gObj, "[Admin] %s saiu do servidor!", gObj->Name);

			break;
		}
	case 2:
		{
			Chat.MessageAllLog(0, 0, c_Green, t_GM, gObj, "[GM] %s saiu do servidor!", gObj->Name);

			break;
		}
	}

	BOOL rValue = gObjGameClose(aIndex);

	return rValue;
}

void GSItemDurRepaire( LPOBJ lpObj, CItem * DurItem, int pos, int RequestPos )
{
	PMSG_ITEMDURREPAIR_RESULT pResult;

	PHeadSetB((LPBYTE)&pResult, 0x34, sizeof(pResult));
	int itemtype = DurItem->m_Type;

	if(itemtype == ITEMGET(13,76) || itemtype == ITEMGET(13,80) || itemtype == ITEMGET(13,67))
	{
		pResult.Money = 0;
		DataSend(lpObj->m_Index, (LPBYTE)&pResult, pResult.h.size);

		return;
	}

	ItemDurRepaire(lpObj, DurItem, pos, RequestPos);
}

void cUser::OnlineTimeTick(LPOBJ gObj)
{
	AddTab[gObj->m_Index].ON_Sek++;

	if(AddTab[gObj->m_Index].ON_Sek >= 60)
	{
		AddTab[gObj->m_Index].ON_Sek = 0;
		AddTab[gObj->m_Index].ON_Min++;
	}

	if(AddTab[gObj->m_Index].ON_Min >= 60)
	{
		AddTab[gObj->m_Index].ON_Min = 0;
		AddTab[gObj->m_Index].ON_Hour++;
		Me_MuOnlineQuery.ExecQuery("UPDATE MEMB_STAT SET OnlineHours = (OnlineHours + 1) WHERE memb___id = '%s'", gObj->AccountID);
		Me_MuOnlineQuery.Fetch();
		Me_MuOnlineQuery.Close();
	}
}

bool cUser::ResetCheck(LPOBJ gObj)
{
	if (!ResetSystem.RConf.IsResetSystem)
	{
		return false;
	}

	if(AddTab[gObj->m_Index].Resets > ResetSystem.RConf.MaximumReset)
	{
		Chat.MessageLog(0, c_Yellow, t_COMMANDS, gObj, "[Login] Seus resets (%d) estao no limite para esse servidor (%d)!", AddTab[gObj->m_Index].Resets,ResetSystem.RConf.MaximumReset);
		CloseClient(gObj->m_Index);

		return true;
	}

	return false;
}

BOOL _gObjCheckTeleportArea(int aIndex, BYTE X, BYTE Y)
{
	BOOL bResult = gObjCheckTeleportArea(aIndex, X, Y);

	if(!bResult)
	{
		return FALSE;
	}
	OBJECTSTRUCT * lpObj = (OBJECTSTRUCT *)OBJECT_POINTER(aIndex);
	int iReturn	= Territory.CheckTerritory(lpObj->MapNumber, X, Y);
	sAddTab * lpInfo = &AddTab[lpObj->m_Index];

	if(iReturn > 0)
	{
		if(lpInfo->TERR_Type != iReturn)
		{
			Chat.MessageLog(1, c_Red, t_TERRITORY, lpObj, "[Territory] Voce nao tem acesso ao territorio %s.", Territory.Config.Terr[iReturn].Name);

			return FALSE;
		}
	}

	return bResult;
}
