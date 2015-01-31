#include "StdAfx.h"
#include "Monster.h"
#include "User.h"
#include "DropSystem.h"
#include "Utilits.h"
#include "PCPoint.h"
#include "Configs.h"
#include "Logger.h"
#include "ChatCommands.h"
#include "MapSystem.h"
#include "DuelManager.h"
#include "MossGambler.h"
#include "Archer.h"
#include "Vip.h"
#include "HappyHour.h"
#include "PlayerSystem.h"
#include "MarrySystem.h"
#include "ResetSystem.h"
#include "Helpers.h"
#include "Quests.h"

cMonster Monster;

void __cdecl MonsterDie(LPOBJ lpObj, LPOBJ lpTargetObj)
{
    if(OBJECT_MAXRANGE(lpTargetObj->m_Index) == FALSE)
	{
        return;
	}

    if(OBJECT_MAXRANGE(lpObj->m_Index) == FALSE)
	{
        return;
	}

    PCPoint.RewardsPointsKillMob(lpTargetObj,lpObj,PCPOINT);
    PCPoint.RewardsPointsKillMob(lpTargetObj,lpObj,WCOIN);

    int Proc = 0;

    if( MapSystem.Maps[lpTargetObj->MapNumber].Drop )
    {
        Proc += MapSystem.Maps[lpObj->MapNumber].Drop;
    }

    int IsHappyHour = HappyHour.IsHappyHour(lpTargetObj->MapNumber);

    if(IsHappyHour)
    {
        Proc += HappyHour.HappyStruct[IsHappyHour].P_Drop;
    }

    Proc += PlayerSystem.GetBonus(lpTargetObj, b_DROP);

    if(Vip.Config.Enabled)
    {
        Proc += Vip.GetBonus(lpTargetObj, b_DROP);
    }

    lpObj->m_wItemDropRate += (lpObj->m_wItemDropRate*Proc)/100;

    if(lpObj->m_wItemDropRate > 100)
    {
        lpObj->m_wItemDropRate = 100;
    }

    gObjMonsterDieGiveItem(lpObj,lpTargetObj);
}

#ifdef _GS
void MonsterAddTick(void * lpParam)
{
    Sleep(15000);
    Monster.ReadMonsterAdd();
    _endthread();
}

int cMonster::SetBoxPosition(int TableNum, int mapnumber, int Axsx, int Axsy, int aw, int Axsh)
{
    _asm
    {
        mov edx, TableNum;
        push edx;
        mov edx, mapnumber;
        push edx;
        mov edx, Axsx;
        push edx;
        mov edx, Axsy;
        push edx;
        mov edx, aw;
        push edx;
        mov edx, Axsh;
        push edx;

        mov ecx, 0x7D800B0;
        mov edi, 0x004032F6;
        call edi;
    }
}

int cMonster::MonsterAddAndSpawn(int Mob, int Map, int Speed, int X1, int Y1, int X2, int Y2, int Dir)
{
    int MobCount = *(DWORD *)(MonsterCount);

    if((MobCount + 1) < MonsterCount)
    {
        MobCount++;
        *(DWORD *)(MonsterCount) = MobCount;
        *(WORD *)(12 * MobCount + MonsterReads) = Mob;
        *(BYTE *)(12 * MobCount + MonsterReads+2) = Map;
        *(BYTE *)(12 * MobCount + MonsterReads+3) = Speed;
        *(BYTE *)(12 * MobCount + MonsterReads+4) = X1;
        *(BYTE *)(12 * MobCount + MonsterReads+5) = Y1;
        *(BYTE *)(12 * MobCount + MonsterReads+6) = Dir;
        *(BYTE *)(12 * MobCount + MonsterReads+7) = X2;
        *(BYTE *)(12 * MobCount + MonsterReads+8) = Y2;

        int MobID = gObjAddMonster(*(BYTE *)(12 * MobCount + (MonsterReads+2)));

        if(MobID>=0)
        {
            int MobNr = *(WORD *)(12 * MobCount + MonsterReads);
            if(X1 != X2 || Y1 != Y2)
                SetBoxPosition(MobID, Map, X1, Y1, X2-X1, Y2-Y1);
            gObjSetPosMonster(MobID, MobCount);
            gObjSetMonster(MobID, MobNr);
        }

        return MobID;
    }
    else
    {
        MessageBox(NULL,"Maximo de atributos de monstros excedido!", "Monsters overflow", 0);

        return -1;
    }
}

void cMonster::ReadMonsterAdd()
{
    FILE* MonsterFile;

    if((MonsterFile = fopen( IAJuliaMobAdd, "r")) == NULL)
    {
        MessageBox(NULL,"Impossivel encontrar MonsterSpawn.ini","MonsterSpawn",0);

        return;
    }

    rewind(MonsterFile);
    char Buff[255];

    while(!feof(MonsterFile))
    {
        Buff[0] = 0;
        fgets (Buff, 255, MonsterFile);

        if(Buff[0] == '/' || Buff[0] == '#' || Buff[0] == ' ' || strlen(Buff) < 9)
        {
            continue;
        }

        int Mob, Count,	Map, Speed, X1, Y1,	X2,	Y2,	Dir;
        sscanf(Buff, "%d %d %d %d %d %d %d %d %d", &Mob, &Map, &Speed, &X1, &Y1, &X2, &Y2, &Dir, &Count);

        if(Mob == -1 ||	Count == -1 ||	Map == -1 ||	Speed == -1 ||	X1 == -1 || Y1 == -1 ||	X2 == -1 ||		Y2 == -1 /*||		Dir == -1 ||*/)
        {
			continue;
		}

        for(int i = 0; i < Count; i++)
        {
            MonsterAddAndSpawn(Mob, Map, Speed, X1, Y1, X2, Y2, Dir);
        }
    }

    fclose(MonsterFile);
}

int cMonster::GetPartyMemberCount(LPOBJ lpObj)
{
    _asm
    {
        mov edx, lpObj;
        push edx;
        mov ecx, 0x7757970;
        mov edi, 0x004D8110;
        call edi;
    }
}
#endif

#ifdef _GS_CS
int cMonster::GetPartyMemberCount(LPOBJ lpObj)
{
    _asm
    {
        mov edx, lpObj;
        push edx;
        mov ecx, 0x3C18178;
        mov edi, 0x004E94A0;
        call edi;
    }
}
#endif

//Monster Death Control
int MygEventMonsterItemDrop(BYTE *b_MonsterDataAddr,BYTE *a_gObjAddr)
{
    // Get mIndex, aIndex & Monster & Player Objects
    PBYTE a_aIndex = 0;
    PBYTE b_mIndex = 0;

    a_aIndex = (PBYTE)a_gObjAddr;
    b_mIndex = (PBYTE)b_MonsterDataAddr;

    WORD mIndex = 0;
    WORD aIndex = 0;

    memcpy(&mIndex,b_mIndex+0x00,sizeof(WORD));
    memcpy(&aIndex,a_aIndex+0x00,sizeof(WORD));

    if(aIndex < OBJECT_MIN || aIndex > OBJECT_MAX)
    {
        Log.ConsoleOutPut(0,c_Red,t_NULL,"[AntiHack] Erro de Objeto!");

        return 1;
    }

    OBJECTSTRUCT *mObj = (OBJECTSTRUCT*) OBJECT_POINTER (mIndex);
    OBJECTSTRUCT *pObj = (OBJECTSTRUCT*) OBJECT_POINTER (aIndex);

    int NewMoney = Utilits.gObjZenSingle(pObj,mObj,500,700);
    mObj->Money = (NewMoney/1000) * Configs.Zen.NormalZen;

    if(pObj->PartyNumber != -1)
    {
        int Count = Monster.GetPartyMemberCount(pObj);

        switch(Count)
        {
            case 2: // 2 Persons in Party
            {
                mObj->Money = (mObj->Money * Configs.Zen.ZenInParty) + (((mObj->Money * Configs.Zen.ZenInParty) / 100) * 5);
            
                break;
            }
            case 3: // 3 Persons in Party
            {
                mObj->Money = (mObj->Money * Configs.Zen.ZenInParty) + (((mObj->Money * Configs.Zen.ZenInParty) / 100) * 10);
            
                break;
            }
            case 4: // 4 Persons in Party
            {
                mObj->Money = (mObj->Money * Configs.Zen.ZenInParty) + (((mObj->Money * Configs.Zen.ZenInParty) / 100) * 15);
            
                break;
            }
            case 5: // 5 Persons in Party
            {
                mObj->Money = (mObj->Money * Configs.Zen.ZenInParty) + (((mObj->Money * Configs.Zen.ZenInParty) / 100) * 20);
                break;
            }
        }
    }

    int Proc = 0;

    //MapSystem Module Zen
    if(MapSystem.Enabled && MapSystem.Maps[pObj->MapNumber].Zen != 0)
    {
        Proc += MapSystem.Maps[mObj->MapNumber].Zen;
    }

    //VIP System
    if(Vip.Config.Enabled)
	{
        Proc += Vip.GetBonus(pObj, b_ZEN);
	}

    //HappyHour
    int IsHappyHour = HappyHour.IsHappyHour(mObj->MapNumber);

    if(IsHappyHour)
    {
        Proc += HappyHour.HappyStruct[IsHappyHour].P_Zen;
    }

    //Player System
    Proc += PlayerSystem.GetBonus(pObj, b_ZEN);

    // add zen
    mObj->Money += (mObj->Money * Proc) / 100;

    // Fix summoner ZEN drop for 3 prof (+180%)
    if (pObj->DbClass == 83)
	{
        mObj->Money += (int)floor(mObj->Money * 1.8);
	}

	// Quests System
	if(Quests.Config.Enable)
	{
		Quests.QuestMobDrop(pObj,mObj);
	}

    // Drop System
    if(DropSystem.DropItem(mObj,pObj))
    {
        return 1;
    }
    else // Default drop
    {
        int rValue = gEventMonsterItemDrop(b_MonsterDataAddr, a_gObjAddr);

        return rValue;
    }

    return 1;
}

void MyItemSerialCreateSend(int aIndex, BYTE MapNumber, BYTE x, BYTE y, int type, BYTE level, BYTE dur, BYTE Op1, BYTE Op2, BYTE Op3, int LootIndex, BYTE NewOption, BYTE SetOption)
{
#ifdef _GS
    if(Monster.GoldenDropFunc(aIndex, MapNumber, x, y, type, level, dur, Op1, Op2, Op3, LootIndex, NewOption, SetOption))
    {
        return;
    }
#endif

    ItemSerialCreateSend(aIndex, MapNumber, x, y, type, level, dur, Op1, Op2, Op3, LootIndex, NewOption, SetOption);
}

int GetRandomOpExe(int quantOptions)
{
    return Utilits.GenExcOpt(quantOptions);
}

char Messages1[1024];

void cMonster::NPCMessage(int IndexPlayer, LPOBJ mObj, char* Msg,...)
{
    Messages1[0] = 0;

    va_list pArguments1;
    va_start(pArguments1, Msg);
    vsprintf_s(Messages1, Msg, pArguments1);
    va_end(pArguments1);

    ChatTargetSend(mObj, Messages1, IndexPlayer);
}

void cMonster::NPCMessageLog(sColor LogColor, sLogType LogType, LPOBJ gObj, LPOBJ mObj, char* Msg,...)
{
    Messages1[0] = 0;

    va_list pArguments1;
    va_start(pArguments1, Msg);
    vsprintf_s(Messages1, Msg, pArguments1);
    va_end(pArguments1);

    ChatTargetSend(mObj,Messages1, gObj->m_Index);
    Log.ConsoleOutPut(1, LogColor, LogType, "[NPC] [%s]:\t%s", gObj->Name, Messages1);
}

void cMonster::NPCMessageNear(LPOBJ mObj, char* Msg,...)
{
    Messages1[0] = 0;

    va_list pArguments1;
    va_start(pArguments1, Msg);
    vsprintf_s(Messages1, Msg, pArguments1);
    va_end(pArguments1);

    for(int i = OBJECT_MIN; i <= OBJECT_MAX; i++)
    {
        OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(i);

        if(gObj->Connected < 3) continue;
		if(mObj->MapNumber != gObj->MapNumber) continue;
		if((mObj->X <= gObj->X-10) || (mObj->X >= gObj->X+10)) continue;
		if((mObj->Y <= gObj->Y-10) || (mObj->Y >= gObj->Y+10)) continue;

		ChatTargetSend(mObj, Messages1, i);
    }
}

bool cMonster::NPCTalkEx(LPOBJ gObj, int NpcId)
{
    bool bResult = false;

    if(OBJECT_MAXRANGE(NpcId) == FALSE)
	{
        return false;
	}

    if(OBJECT_MAXRANGE(gObj->m_Index) == FALSE)
	{
        return false;
	}

    OBJECTSTRUCT *gObjNPC = (OBJECTSTRUCT*)OBJECT_POINTER(NpcId);

    if ((gObjNPC->Class == ClearNpc.NpcId) && (ClearNpc.Enabled))
    {
        PkClear(gObj, gObjNPC);

        bResult = true;
    }

    if((gObjNPC->Class == 236) && (GoldenArcher.Config.Enabled))
    {
        GoldenArcher.GoldenArcherClick(gObj);

        bResult = true;
    }

	if(gObjNPC->Class == 414)
	{
		Helpers.HelperEllenClick(gObj,gObjNPC);

		bResult = true;
	}

	if(gObjNPC->Class == 371)
    {
        Helpers.HelperLeoClick(gObj,gObjNPC);

        bResult = true;
    }

    if(gObjNPC->Class == 258)
    {
        Helpers.HelperLukeClick(gObj,gObjNPC);

        bResult = true;
    }

	if(gObjNPC->Class == Quests.Config.QuestNPCID)
	{
		Quests.QuestNPCClick(gObj,gObjNPC);

		bResult = true;
	}

    if((gObjNPC->Class == Marry.Config.MarryNpcNum) && !AddTab[gObj->m_Index].IsMarried)
    {
        Marry.StartMarriage(gObj->m_Index, gObjNPC->m_Index);

        bResult = true;
    }
    
    // Achar um NPC para o /reset
	/*if((ResetSystem.RConf.ResetNPC > 0) && (gObjNPC->Class == ResetSystem.RConf.ResetNPC))
	{
		NPCMessageLog(c_Blue,t_COMMANDS,gObj,gObjNPC,"Nao estou de servico, volte mais tarde.");

		bResult = true;
	}*/

	/* Adicionar falas dos ajudantes de papai noel */

	if(gObjNPC->Class == 241) // NPC Guild
    {
        if(AddTab[gObj->m_Index].Resets < Configs.GuildRes)
        {
            Chat.Message(1,gObj,"Voce precisa ter %d resets",Configs.GuildRes);

            bResult = true;
        }

        if(gObj->Level < Configs.GuildLevel)
        {
            Chat.Message(1,gObj,"Voce precisa estar no level %d.",Configs.GuildLevel);

            bResult = true;
        }
    }
#ifdef _GS
    if((gObjNPC->Class == 479) && DuelSystem.Config.Enabled)
    {
        PMSG_SEND_WINDOW aSend;

        aSend.uHead			 = 0xC3;
        aSend.uSize			 = 0x04;
        aSend.uPacketType	 = 0x30;
        aSend.uNum			 = 0x21;
        gObj->m_IfState.use  = 479;
        gObj->m_IfState.type = 20;

        DataSend(gObj->m_Index, (BYTE*)&aSend, 4);
        DuelSystem.SendDuelStatus(gObj);

        bResult = true;
    }

	if((gObjNPC->Class == 492) && Moss.Config.Enable)
	{
		if(Moss.Opened == FALSE)
		{
			Chat.Message(1,gObj,"[Moss The Gambler] Nao estou de servico, volte mais tarde.");

			bResult = true;
		}
        else
        {
		    if((gObj->m_PK_Level > 3) && !Moss.Config.UsePK)
            {
                Chat.Message(1,gObj,"[Moss The Gambler] Nao farei negocios com PK's!!");

                bResult = true;
            }
            else
		    {
		        BYTE Send2[6] = {0xC3,0x06,0x30,0x00,0x27,0x00};
		        BYTE Send[71] =
		        {
			        0xC2,0x00,71,0x31,0x00,5,0x00,71,0x00,0x01,0x00,0x00,13*16,
			        0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0x02,72,0x00,0x01,0x00,0x00,13*16,
			        0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0x04,73,0x00,0x01,0x00,0x00,13*16,
			        0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0x18,74,0x00,0x01,0x00,0x00,13*16,
			        0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0x06,75,0x00,0x01,0x00,0x00,13*16,
			        0x00,0xFF,0xFF,0xFF,0xFF,0xFF
		        };
		
		        DataSend(gObj->m_Index,Send2,6);
		        DataSend(gObj->m_Index,Send,71);
		
		        gObj->TargetShopNumber = 492;
		        gObj->m_IfState.use    = 1;
		        gObj->m_IfState.type   = 3;

                bResult = true;
		    }
        }
	}
#endif
    return bResult;
}

void cMonster::LoadPkClear()
{
    /* PK Clear */
    ClearCommand.Enabled = Configs.GetInt(0, 1, 1, "PkClear", "PkClearEnabled", IAJuliaCmd);

    if(ClearCommand.Enabled)
    {
        ClearCommand.OnlyForGm				= Configs.GetInt(0, 1, 0, "PkClear", "PkClearOnlyForGm", IAJuliaCmd);
        ClearCommand.Type					= Configs.GetInt(0, 2, 1, "PkClear", "PKClearType", IAJuliaCmd);
        ClearCommand.PriceZen				= Configs.GetInt(0, 2000000000, 100000, "PkClear", "PkClearPriceZen", IAJuliaCmd);
        ClearCommand.PriceZenForAll			= Configs.GetInt(0, 2000000000, 1000000, "PkClear", "PkClearPriceZenForAll", IAJuliaCmd);
        ClearCommand.LevelReq				= Configs.GetInt(0, Configs.Commands.MaxLvl,100, "PkClear",	"PkClearLevelReq", IAJuliaCmd);
        ClearCommand.PricePcPoints			= Configs.GetInt(0, PCPoint.Config.MaximumPCPoints,	20,	"PkClear", "PkClearPricePcPoints", IAJuliaCmd);
        ClearCommand.PricePcPointsForAll	= Configs.GetInt(0, PCPoint.Config.MaximumPCPoints,	200, "PkClear", "PkClearPricePcPointsForAll", IAJuliaCmd);
        ClearCommand.PriceWCoins			= Configs.GetInt(0, PCPoint.Config.MaximumWCPoints,	2, "PkClear", "PkClearPriceWCoins", IAJuliaCmd);
        ClearCommand.PriceWCoinsForAll		= Configs.GetInt(0, PCPoint.Config.MaximumWCPoints,	20, "PkClear", "PkClearPriceWCoinsForAll", IAJuliaCmd);

        if (PCPoint.Config.WebEnabled)
        {
            ClearCommand.PriceWebPoints			= Configs.GetInt(0, PCPoint.Config.MaximumWebPoints, 2, "PkClear", "PkClearGuardPriceWebPoints",	IAJuliaCmd);
            ClearCommand.PriceWebPointsForAll	= Configs.GetInt(0, PCPoint.Config.MaximumWebPoints, 20, "PkClear", "PkClearGuardPriceWebPointsForAll",IAJuliaCmd);
        }
    }

    ClearNpc.Enabled = Configs.GetInt(0, 1, 1, "PkClearGuard", "LoadPkGuard", IAJuliaPkClear);

    if(ClearNpc.Enabled)
    {
        ClearNpc.NpcId					= Configs.GetInt(0, 32000,		249,	"PkClearGuard",	"PkClearGuardId",				IAJuliaPkClear);
        ClearNpc.Type					= Configs.GetInt(0, 2,			1,		"PkClearGuard",	"PKClearGuardType",				IAJuliaPkClear);
        ClearNpc.PriceZen				= Configs.GetInt(0, 2000000000,	100000,	"PkClearGuard",	"PkClearGuardPriceZen",			IAJuliaPkClear);
        ClearNpc.PriceZenForAll			= Configs.GetInt(0, 2000000000,	1000000,"PkClearGuard",	"PkClearGuardPriceZenForAll",	IAJuliaPkClear);
        ClearNpc.LevelReq				= Configs.GetInt(0, 400,		100,	"PkClearGuard",	"PkClearGuardLevelReq",			IAJuliaPkClear);
        ClearNpc.PricePcPoints			= Configs.GetInt(0, PCPoint.Config.MaximumPCPoints,	20,		"PkClearGuard",		"PkClearGuardPricePcPoints",		IAJuliaPkClear);
        ClearNpc.PricePcPointsForAll	= Configs.GetInt(0, PCPoint.Config.MaximumPCPoints,	200,	"PkClearGuard",		"PkClearGuardPricePcPointsForAll",	IAJuliaPkClear);
        ClearNpc.PriceWCoins			= Configs.GetInt(0, PCPoint.Config.MaximumWCPoints,	2,		"PkClearGuard",		"PkClearGuardPriceWCoins",			IAJuliaPkClear);
        ClearNpc.PriceWCoinsForAll		= Configs.GetInt(0, PCPoint.Config.MaximumWCPoints,	20,		"PkClearGuard",		"PkClearGuardPriceWCoinsForAll",	IAJuliaPkClear);

        if (PCPoint.Config.WebEnabled)
        {
            ClearNpc.PriceWebPoints			= Configs.GetInt(0, PCPoint.Config.MaximumWebPoints,2,		"PkClearGuard",		"PkClearGuardPriceWebPoints",		IAJuliaPkClear);
            ClearNpc.PriceWebPointsForAll	= Configs.GetInt(0, PCPoint.Config.MaximumWebPoints,20,		"PkClearGuard",		"PkClearGuardPriceWebPointsForAll",	IAJuliaPkClear);
        }
    }
}

void cMonster::PkClear(LPOBJ gObj, LPOBJ NpcObj)
{
    if(gObj->m_PK_Level < 4)
    {
        NPCMessageLog(c_Blue,t_COMMANDS,gObj,NpcObj, "Voce e um bom Player, que Muren o abencoe!");

        return;
    }

    int PriceZen, PricePcPoint, PriceWCoin, PriceWebPoints;

    switch(ClearNpc.Type)
    {
    case 1:
        PriceZen = (ClearNpc.PriceZen * gObj->m_PK_Count);
        PricePcPoint = (ClearNpc.PricePcPoints * gObj->m_PK_Count);
        PriceWCoin = (ClearNpc.PriceWCoins * gObj->m_PK_Count);
        PriceWebPoints = (ClearNpc.PriceWebPoints * gObj->m_PK_Count);
        break;
    case 2:
         PriceZen = ClearNpc.PriceZenForAll;
        PricePcPoint = ClearNpc.PricePcPointsForAll;
        PriceWCoin = ClearNpc.PriceWCoinsForAll;
        PriceWebPoints = ClearNpc.PriceWebPointsForAll;
        break;
    case 0:
        PriceZen = 0;
        PricePcPoint = 0;
        PriceWCoin = 0;
        PriceWebPoints = 0;
        break;
    }

    if(gObj->Money < PriceZen)
    {
        NPCMessageLog( c_Blue ,t_COMMANDS, gObj, NpcObj, "You don't have enough Zen, you need %d more!", PriceZen - gObj->Money);
        return;
    }

    if(gObj->m_wCashPoint < PriceWCoin)
    {
        NPCMessageLog( c_Blue ,t_COMMANDS, gObj, NpcObj, "You don't have enough WCoin, you need %d more!", PriceWCoin - gObj->m_wCashPoint);
        return;
    }

    if(AddTab[gObj->m_Index].PC_PlayerPoints < PricePcPoint)
    {
        NPCMessageLog( c_Blue ,t_COMMANDS, gObj, NpcObj, "You don't have enough PcPoint, you need %d more!", PricePcPoint - AddTab[gObj->m_Index].PC_PlayerPoints);
        return;
    }

    if(!PCPoint.Config.WebEnabled)
	{
        PriceWebPoints = 0;
	}

    if(PCPoint.Config.WebColumnFloat)
    {
        if(AddTab[gObj->m_Index].WEB_Points_Float < PriceWebPoints)
        {
            NPCMessageLog( c_Blue ,t_COMMANDS, gObj, NpcObj, "You don't have enough WebPoints, you need %.2f more!", PriceWebPoints - AddTab[gObj->m_Index].WEB_Points_Float);
            return;
        }
    }
    else
    {
        if(AddTab[gObj->m_Index].WEB_Points < PriceWebPoints)
        {
            NPCMessageLog( c_Blue ,t_COMMANDS, gObj, NpcObj, "You don't have enough WebPoints, you need %d more!", PriceWebPoints - AddTab[gObj->m_Index].WEB_Points);
            return;
        }
    }

    if (PriceWebPoints > 0)
    {
        PCPoint.UpdatePoints(gObj,WEBPOINTS,MINUS,PCPOINT);
        Chat.MessageLog(1, c_Blue, t_PCPOINT, gObj,"[Guard] You pay %d WebPoints", PriceWebPoints);
    }

    if (PricePcPoint > 0)
    {
        PCPoint.UpdatePoints(gObj,PricePcPoint,MINUS,PCPOINT);
        Chat.MessageLog(1, c_Blue, t_PCPOINT, gObj,"[Guard] You pay %d PcPoints", PricePcPoint);
    }

    if (PriceWCoin > 0)
    {
        PCPoint.UpdatePoints(gObj,PriceWCoin,MINUS,WCOIN);
        Chat.MessageLog(1, c_Blue, t_PCPOINT, gObj,"[Guard] You pay %d WCoin", PriceWCoin);
    }

    if (PriceZen > 0)
    {
        gObj->Money -= PriceZen;
        GCMoneySend (gObj->m_Index, gObj->Money);
        Chat.MessageLog(1, c_Blue ,t_PCPOINT, gObj, "[Guard] You pay %d Zen", PriceZen);
    }

    NPCMessageLog( c_Blue ,t_COMMANDS, gObj, NpcObj,"Cleaned %d kills. Don't tell anyone!", gObj->m_PK_Count);

    gObj->m_PK_Level = 3;
    gObj->m_PK_Count = 0;

    GCPkLevelSend (gObj->m_Index,3);
}

#ifdef _GS
void cMonster::LoadGolden()
{
    for(int i = 0;i < 20;i++)
    {
        GoldenDrop[i].NumItems = 0;

        for(int j = 0;j < 20;j++)
        {
            GoldenDrop[i].Items[j].Index	= 0;
            GoldenDrop[i].Items[j].ID		= 0;
            GoldenDrop[i].Items[j].Level	= 0;
            GoldenDrop[i].Items[j].Option	= 0;
            GoldenDrop[i].Items[j].Luck		= 0;
            GoldenDrop[i].Items[j].Skill	= 0;
            GoldenDrop[i].Items[j].Dur		= 0;
            GoldenDrop[i].Items[j].Exc		= 0;
            GoldenDrop[i].Items[j].Anc		= 0;
        }
    }

    EnableGoldenDrop	= Configs.GetInt(0, 1, 1,"GoldenDrop", "Enable", IAJuliaGoldenDrop);

    if(!EnableGoldenDrop)
	{
		return;
	}

    FILE *file;
    file = fopen(IAJuliaGoldenDrop, "r");

    if (file == NULL)
    {
        EnableGoldenDrop = 0;
        Log.ConsoleOutPut(1, c_Red, t_Error, "[X] [Golden Drop]\tCan`t Find %s", IAJuliaGoldenDrop);
        return;
    }

    char Buff[256];
    int Flag = 0;

    while (!feof(file))
    {
        fgets(Buff,256,file);

        if(Utilits.IsBadFileLine(Buff, Flag))
            continue;

        if (Flag == 1)
        {
            int n[10];
            sscanf(Buff, "%d %d %d %d %d %d %d %d %d %d", &n[0], &n[1], &n[2], &n[3], &n[4], &n[5], &n[6], &n[7], &n[8], &n[9]);

            int IDMob = -1;
            switch (n[0])
            {
            case 44:
                    IDMob = 0;
                break;
            case 43:
                    IDMob = 1;
                break;
            case 78:
                    IDMob = 2;
                break;
            case 53:
                    IDMob = 3;
                break;
            case 54:
                    IDMob = 4;
                break;
            case 79:
                    IDMob = 5;
                break;
            case 80:
                    IDMob = 6;
                break;
            case 81:
                    IDMob = 7;
                break;
            case 82:
                    IDMob = 8;
                break;
            case 83:
                    IDMob = 9;
                break;
            case 493:
                    IDMob = 10;
                break;
            case 494:
                    IDMob = 11;
                break;
            case 495:
                    IDMob = 12;
                break;
            case 496:
                    IDMob = 13;
                break;
            case 497:
                    IDMob = 14;
                break;
            case 498:
                    IDMob = 15;
                break;
            case 499:
                    IDMob = 16;
                break;
            case 500:
                    IDMob = 17;
                break;
            case 501:
                    IDMob = 18;
                break;
            case 502:
                    IDMob = 19;
                break;
            }

            if (IDMob == -1)
                continue;

            int Num = GoldenDrop[IDMob].NumItems;

            if (Num < 0 || Num > 19)
                continue;

            GoldenDrop[IDMob].Items[Num].Index	= n[1];
            GoldenDrop[IDMob].Items[Num].ID		= n[2];
            GoldenDrop[IDMob].Items[Num].Level	= n[3];
            GoldenDrop[IDMob].Items[Num].Option	= n[4];
            GoldenDrop[IDMob].Items[Num].Luck	= n[5];
            GoldenDrop[IDMob].Items[Num].Skill	= n[6];
            GoldenDrop[IDMob].Items[Num].Dur	= n[7];
            GoldenDrop[IDMob].Items[Num].Exc	= n[8];
            GoldenDrop[IDMob].Items[Num].Anc	= n[9];
            GoldenDrop[IDMob].NumItems++;
        }
    }
    fclose(file);
    Log.ConsoleOutPut(1, c_Cyan, t_Default, "[û] [Golden Drop]\tDrop Loaded");
}

bool cMonster::GoldenDropFunc( int aIndex, BYTE MapNumber, BYTE x, BYTE y, int type, BYTE level, BYTE dur, BYTE Op1, BYTE Op2, BYTE Op3, int LootIndex, BYTE NewOption, BYTE SetOption )
{
    if (!EnableGoldenDrop)
        return false;

    OBJECTSTRUCT *mObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);

    int IDMob = -1;

    switch(mObj->Class)
    {
		case 44:
		{
			IDMob = 0;

			break;
		}
		case 43:
		{
			IDMob = 1;

			break;
		}
		case 78:
		{
			IDMob = 2;

			break;
		}
		case 53:
		{
			IDMob = 3;

			break;
		}
		case 54:
		{
			IDMob = 4;

			break;
		}
		case 79:
		{
			IDMob = 5;

			break;
		}
		case 80:
		{
			IDMob = 6;

			break;
		}
		case 81:
		{
			IDMob = 7;

			break;
		}
		case 82:
		{
			IDMob = 8;

			break;
		}
		case 83:
		{
			IDMob = 9;
			break;
		}
		case 493:
		{
			IDMob = 10;

			break;
		}
		case 494:
		{
			IDMob = 11;

			break;
		}
		case 495:
		{
			IDMob = 12;

			break;
		}
		case 496:
		{
			IDMob = 13;

			break;
		}
		case 497:
		{
			IDMob = 14;

			break;
		}
		case 498:
		{
			IDMob = 15;

			break;
		}
		case 499:
		{
			IDMob = 16;

			break;
		}
		case 500:
		{
			IDMob = 17;

			break;
		}
		case 501:
		{
			IDMob = 18;

			break;
		}
		case 502:
		{
			IDMob = 19;

			break;
		}
    }

    if(IDMob == -1)
	{
        return false;
	}

    if (AddTab[mObj->m_Index].TEMP_Golden_Drop)
        return true;

    if (GoldenDrop[IDMob].NumItems > 0 && GoldenDrop[IDMob].NumItems < 20)
    {
        for (int i=0; i<GoldenDrop[IDMob].NumItems; i++)
        {
            if (GoldenDrop[IDMob].Items[i].Index == -1)
                continue;
            sItemDrop it = GoldenDrop[IDMob].Items[i];

            ItemSerialCreateSend(aIndex, MapNumber, x, y, ITEMGET(it.Index,it.ID), it.Level, it.Dur, it.Skill, it.Luck, it.Option, LootIndex, it.Exc, it.Anc);
        }

        AddTab[mObj->m_Index].TEMP_Golden_Drop = true;
        return true;
    }
    return false;
}
#endif