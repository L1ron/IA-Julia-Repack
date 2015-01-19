#include "StdAfx.h"
#include "MarrySystem.h"

#include "User.h"
#include "Logger.h"
#include "ChatCommands.h"
#include "Configs.h"
#include "PCPoint.h"
#include "Prodef.h"
#include "Monster.h"
#include "Utilits.h"
#include "Query.h"
cMarry Marry;

//#TODO
// 1. Считывание конфигов 100%
// 2. Отчистка переменных от мусора 100%
// 3. Проверка пола 100%
// 4. Проверка свидетелей и забирание бабла 100%
// 5. Считывание из базы и занесение в переменную 100%
// 6. Команды для Женатых 100%
// 7. Бонусы женатым 100%
// 8. Свадьба 100%

void cMarry::ResetConfigs()
{
    Config.MarrySystemEnabled = 0;
    Config.MarryHomoSexual = 0;
    Config.MarryCostZen = 0;
    Config.MarryCostPCPoint = 0;
    Config.MarryCostWCoin = 0;
    Config.MarryMinLvl = 0;
    Config.IsMarry = 0;
    Config.MarryNpcNum = 0;
    Config.MarryTrace = 0;
    Config.MarryTraceLvl = 0;
    Config.MarryOnline = 0;
    Config.MarryExpBonus = 0;
    Config.NumWitnesses = 0;

    Config.IsDivorce = 0;
    Config.DivorceNpcNum = 0;
    Config.DivorceCostZen = 0;
    Config.DivorceCostPCPoint = 0;
    Config.DivorceCostWCoin = 0;
    Config.DivorceMinLvl = 0;

    Config.TakeItemsForMarry = 0;
//	Config.TakeItemsForDivorce = 0;

    for (int i=0; i < MAXMARRYITEM; i++)
    {
        Config.MarryItems[i].Num = 0;

        Config.MarryItems[i].Group = 0;

        Config.MarryItems[i].Type = 0;

        Config.MarryItems[i].Lvl = 0;

        Config.MarryItems[i].Luck = 0;

        Config.MarryItems[i].Skill = 0;

        Config.MarryItems[i].Opt = 0;

        Config.MarryItems[i].Exc = 0;

    }
}

void cMarry::Init()
{
    ResetConfigs();

    Config.MarrySystemEnabled		= Configs.GetInt(0, 1,				1,		"MarrySystem",	"MarrySystemEnabled",			IAMarrySystem);
    if(!Config.MarrySystemEnabled)
        return;
    Config.MarryHomoSexual			= Configs.GetInt(0, 1,				1,		"MarrySystem",	"MarryHomoSexual",				IAMarrySystem);
    Config.MarryCostZen				= Configs.GetInt(0, 2000000000,		1000000,"MarrySystem",	"MarryCostZen",					IAMarrySystem);
    Config.MarryCostPCPoint			= Configs.GetInt(0, PCPoint.Config.MaximumPCPoints,0,		"MarrySystem",	"MarryCostPCPoint",				IAMarrySystem);
    Config.MarryCostWCoin			= Configs.GetInt(0, PCPoint.Config.MaximumWCPoints,0,		"MarrySystem",	"MarryCostWCoin",				IAMarrySystem);
    Config.MarryMinLvl				= Configs.GetInt(0, 400,			0,		"MarrySystem",	"MarryMinLvl",					IAMarrySystem);
    Config.MarryNpcNum				= Configs.GetInt(0, 20000,			379,	"MarrySystem",	"MarryNpcNum",					IAMarrySystem);
    Config.MarryTrace				= Configs.GetInt(0, 1,				1,		"MarrySystem",	"MarryTrace",					IAMarrySystem);
    Config.MarryOnline				= Configs.GetInt(0, 1,				1,		"MarrySystem",	"MarryOnline",					IAMarrySystem);
    Config.IsMarry					= Configs.GetInt(0, 1,				1,		"MarrySystem",	"IsMarry",						IAMarrySystem);
    Config.MarryTraceLvl			= Configs.GetInt(1, 400,	200,			"MarrySystem",	"MarryTraceLvlReq",				IAMarrySystem);
    Config.MarryExpBonus			= Configs.GetInt(0, 90000, 100,				"MarrySystem",	"MarryExpBonus",				IAMarrySystem);
    Config.NumWitnesses				= Configs.GetInt(0, 100,			2,		"MarrySystem",	"MarryNumWitnesses",			IAMarrySystem);

    Config.IsDivorce				= Configs.GetInt(0, 2,				1,		"MarrySystem",	"DivorceEnabled",				IAMarrySystem);
//	Config.DivorceNpcNum			= Configs.GetInt(0, 20000,			0,		"MarrySystem",	"DivorceNpcNum",			IAMarrySystem);

    Config.DivorceCostZen			= Configs.GetInt(0, 2000000000,		1000000,"MarrySystem",	"DivorceCostZen",				IAMarrySystem);
    Config.DivorceCostPCPoint		= Configs.GetInt(0, PCPoint.Config.MaximumPCPoints,0,		"MarrySystem",	"DivorceCostPCPoint",			IAMarrySystem);
    Config.DivorceCostWCoin			= Configs.GetInt(0, PCPoint.Config.MaximumWCPoints,0,		"MarrySystem",	"DivorceCostWCoin",				IAMarrySystem);
    Config.DivorceMinLvl			= Configs.GetInt(0, 400,			0,		"MarrySystem",	"DivorceMinLvl",				IAMarrySystem);

    Config.TakeItemsForMarry		= Configs.GetInt(0, 20,				2,		"MarrySystem",	"TakeItemsForMarry",			IAMarrySystem);

    char Items[40];
    if(Config.TakeItemsForMarry != 0)
    {
        for(int y = 0; y < Config.TakeItemsForMarry; y++)
        {
            wsprintf(Items, "Config.Item[%d].Num", y+1);
            Config.MarryItems[y].Num		= Configs.GetInt(0, 20, 1, "MarrySystem", Items, IAMarrySystem);

            wsprintf(Items, "Config.Item[%d].Index", y+1);
            Config.MarryItems[y].Group	= Configs.GetInt(0, 15, 0, "MarrySystem", Items, IAMarrySystem);

            wsprintf(Items, "Config.Item[%d].Type", y+1);
            Config.MarryItems[y].Type	= Configs.GetInt(0, 255, 0, "MarrySystem", Items, IAMarrySystem);

            wsprintf(Items, "Config.Item[%d].Lvl", y+1);
            Config.MarryItems[y].Lvl		= Configs.GetInt(0, 13, 0, "MarrySystem", Items, IAMarrySystem);

            wsprintf(Items, "Config.Item[%d].Luck", y+1);
            Config.MarryItems[y].Luck	= Configs.GetInt(0, 1, 0, "MarrySystem", Items, IAMarrySystem);

            wsprintf(Items, "Config.Item[%d].Skill", y+1);
            Config.MarryItems[y].Skill	= Configs.GetInt(0, 1, 0, "MarrySystem", Items, IAMarrySystem);

            wsprintf(Items, "Config.Item[%d].Opt", y+1);
            Config.MarryItems[y].Opt		= Configs.GetInt(0, 7, 0, "MarrySystem", Items, IAMarrySystem);

            wsprintf(Items, "Config.Item[%d].Exc", y+1);
            Config.MarryItems[y].Exc		= Configs.GetInt(0, 63, 0, "MarrySystem", Items, IAMarrySystem);
        }
    }
    Log.ConsoleOutPut(1, c_Yellow, t_Default, "[ы] [Marry System]\tLoaded");
}

bool cMarry::CheckMarryCost(int aIndex, int tIndex, int Delete)
{
    OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);
    OBJECTSTRUCT *tObj = (OBJECTSTRUCT*)OBJECT_POINTER(tIndex);

    if(Config.MarryMinLvl > gObj->Level)
    {
        if(tObj == NULL)
            Chat.Message(1, gObj, "[Marriage] You don't have high lvl! Need %d more.", Config.MarryMinLvl - gObj->Level);	  //PRIVAT
        else
            Monster.NPCMessage(gObj->m_Index, tObj, "You don't have high lvl! Need %d more.", Config.MarryMinLvl - gObj->Level);

        return false;
    }
    if(Config.MarryCostZen > gObj->Money)
    {
        if(tObj == NULL)
            Chat.Message(1, gObj, "[Marriage] You don't have enough zen! Need %d more.", Config.MarryCostZen - gObj->Money);	  //PRIVAT
        else
            Monster.NPCMessage(gObj->m_Index, tObj, "You don't have enough zen! Need %d more.", Config.MarryCostZen - gObj->Money);

        return false;
    }
    if(Config.MarryCostPCPoint > AddTab[gObj->m_Index].PC_PlayerPoints)
    {
        if(tObj == NULL)
            Chat.Message(1, gObj, "[Marriage] You don't have enough PCPoints! Need %d more.", Config.MarryCostPCPoint - AddTab[gObj->m_Index].PC_PlayerPoints);	  //PRIVAT
        else
            Monster.NPCMessage(gObj->m_Index, tObj, "You don't have enough PCPoints! Need %d more.", Config.MarryCostPCPoint - AddTab[gObj->m_Index].PC_PlayerPoints);			  //PRIVAT

        return false;
    }
    if(Config.MarryCostWCoin > gObj->m_wCashPoint)
    {
        if(tObj == NULL)
            Chat.Message(1, gObj, "[Marriage] You don't have enough WCoins! Need %d more.", Config.MarryCostWCoin - gObj->m_wCashPoint);	  //PRIVAT
        else
            Monster.NPCMessage(gObj->m_Index, tObj, "You don't have enough WCoins! Need %d more.", Config.MarryCostWCoin - gObj->m_wCashPoint);			  //PRIVAT

        return false;
    }
    if(Config.TakeItemsForMarry > 0)
    {
        if(CheckMarryItem(aIndex) == false)
        {
            if(tObj == NULL)
                Chat.MessageLog(1, c_Red, t_RESET, gObj, "[Marriage] You don't have right items. Check it one more time.");
            else
                Monster.NPCMessageLog(c_Blue ,t_COMMANDS, gObj, tObj, "You don't have right items. Check it one more time.");

            return false;
        }
    }
    if(Config.NumWitnesses > 0)
    {
        int Num = 0;
        for(int i = OBJECT_MIN; i <= OBJECT_MAX; i++)
        {
            OBJECTSTRUCT *aObj = (OBJECTSTRUCT*)OBJECT_POINTER(i);
            if(aObj->Connected < 3) continue;
            if(gObj->MapNumber != aObj->MapNumber) continue;
            if(gObj->X <= aObj->X-10 || gObj->X >= aObj->X+10) continue;
            if(gObj->Y <= aObj->Y-10 || gObj->Y >= aObj->Y+10) continue;
            Num++;
        }
        if((Num - 2) < Config.NumWitnesses)
        {
            if(tObj == NULL)
                Chat.MessageLog(1, c_Red, t_RESET, gObj, "[Marriage] You don't have at least %d witnesses.", Config.NumWitnesses);
            else
                Monster.NPCMessageLog(c_Blue ,t_COMMANDS, gObj, tObj, "You don't have at least %d witnesses.", Config.NumWitnesses);

            return false;
        }
    }

    if(!Delete)return true; //если Delete == 0 то вовзвращать.

    if(Config.MarryCostZen > 0)
    {
        gObj->Money -= Config.MarryCostZen;
        GCMoneySend(gObj->m_Index, gObj->Money);
    }
    if(Config.MarryCostPCPoint > 0)
    {
        PCPoint.UpdatePoints(gObj,Config.MarryCostPCPoint,MINUS,PCPOINT);
        Chat.MessageLog(1, c_Blue, t_PCPOINT, gObj, "[Marriage] You payed %d PcPoints", Config.MarryCostPCPoint);
    }
    if(Config.MarryCostWCoin > 0)
    {
        PCPoint.UpdatePoints(gObj,Config.MarryCostWCoin,MINUS,WCOIN);
        Chat.MessageLog(1, c_Blue, t_PCPOINT, gObj,"[Marriage] You payed %d WCoin", Config.MarryCostWCoin);
    }


    if(Config.TakeItemsForMarry > 0)
    {
        for ( BYTE i = 0 ; i < 76 ; i ++ )
        {
            if(Config.MarrySerial[i])
            {
                gObjInventoryDeleteItem ( gObj->m_Index , i );
                GCInventoryItemDeleteSend ( gObj->m_Index , i  , 1 );
            }
        }
    }
    return true;
}

bool cMarry::CheckGender(int aIndex, int tIndex) //Returnes True if Gender check passed
{
    OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);
    OBJECTSTRUCT *tObj = (OBJECTSTRUCT*)OBJECT_POINTER(tIndex);

    if (tObj == NULL || gObj == NULL)
        return false;

    int aGender = MAN, tGender = MAN;
    switch(gObj->DbClass)
    {
    case 32:
    case 33:
    case 34:
    case 35:
        aGender = WOMAN;
        break;
    case 80:
    case 81:
    case 82:
    case 83:
        aGender = WOMAN;
        break;
    default:
        aGender = MAN;
    }

    switch(tObj->DbClass)
    {
    case 32:
    case 33:
    case 34:
    case 35:
        tGender = WOMAN;
        break;
    case 80:
    case 81:
    case 82:
    case 83:
        tGender = WOMAN;
        break;
    default:
        tGender = MAN;
    }

    if(tGender == aGender)
    {
        if(Config.MarryHomoSexual == 1)
        {
            if(tGender == MAN)
            {
                Chat.MessageAll(0, 0, gObj, "[Marriage] It would be gey wedding!");	  //AROUND

                if(tObj != NULL)
                {
                    Monster.NPCMessageNear(tObj, "It would be gey wedding!");	  //AROUND
                }

                return true;
            }
            else
            {
                Chat.MessageAll(0, 0, gObj, "[Marriage] It would be lesbian wedding!");	  //AROUND
                if(tObj != NULL)
                    Monster.NPCMessageNear(tObj, "It will be lesbian wedding!");	  //AROUND

                return true;
            }
        }
        else
        {
            Chat.MessageAll(0, 0, gObj, "[Marriage] We don't support untraditional weddings!!! Marriage canceled!!!");	  //AROUND
            if(tObj != NULL)
                Monster.NPCMessageNear(tObj, "We don't support untraditional weddings!!!");	  //AROUND
            return false;
        }
    }
    return true;
}


bool cMarry::CheckMarryItem(int Index)
{
    OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(Index);
    int NumItem	= Config.TakeItemsForMarry;
    int NumSpesItem;

    int Num_Items = 0;
    int m_NumSpesItem[20];
    int x_NumItem = 0;

    for(int xo = 0; xo < 76; xo++)
        Config.MarrySerial[xo] = false;

    for(int x = 0; x < NumItem; x++)
    {
        m_NumSpesItem[x] = 0;
        NumSpesItem = Config.MarryItems[x].Num;
        x_NumItem += NumSpesItem;
        Config.MarryItems[x].Index = (Config.MarryItems[x].Group * 512 + Config.MarryItems[x].Type);
        for(BYTE i = 12; i < 76 ; i ++ )
        {
            if(gObj->pInventory[i].m_Type == Config.MarryItems[x].Index &&
                    gObj->pInventory[i].m_Level == Config.MarryItems[x].Lvl &&
                    gObj->pInventory[i].m_Option2 == Config.MarryItems[x].Luck &&
                    gObj->pInventory[i].m_Option1 == Config.MarryItems[x].Skill &&
                    gObj->pInventory[i].m_Option3 == Config.MarryItems[x].Opt &&
                    gObj->pInventory[i].m_NewOption == Config.MarryItems[x].Exc &&
                    m_NumSpesItem[x] < NumSpesItem)
            {
                if(!Config.MarrySerial[i])
                {
                    CheckMarryItemSerial(Index,i);
                    m_NumSpesItem[x]++;
                    Num_Items++;
                }
            }
        }
    }
    if(Num_Items >= x_NumItem)
        return true;
    else
        return false;
}

void cMarry::CheckMarryItemSerial(int Index, BYTE Serial)
{
    OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(Index);

    unsigned long Ser = gObj->pInventory[Serial].m_Number;
    for(BYTE i = 12; i < 76 ; i ++ )
        if(gObj->pInventory[i].m_Number == Ser)
            Config.MarrySerial[i] = true;
}
unsigned long __stdcall TickMarriage(int Index)
{
    LPOBJ nObj = Marry.NpcObj;
    LPOBJ kObj1 = Marry.gObj1;
    LPOBJ kObj2 = Marry.gObj2;
    Marry.NpcUse = true;
    OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(Index);

    int i;
    if(nObj == NULL)
        Chat.Message(1, gObj, "[Marriage] Write /yes or /no for answer. You have 30 secs.");
    else
    {
        Sleep(3000);
        if(!Marry.NpcUse) return 1;
        Monster.NPCMessage(Index, nObj, "Write /yes or /no for answer. You have 30 secs.");
    }

    for(i = 0; i < 150; i++)
    {
        Sleep(100);
        if(!Marry.NpcUse) return 1;
    }
    if(nObj == NULL)
        Chat.Message(1, gObj, "[Marriage] You have 15 secs more for answer...");
    else
        Monster.NPCMessage(Index, nObj, "You have 15 secs more for answer...");

    for(i = 0; i < 50; i++)
    {
        Sleep(100);
        if(!Marry.NpcUse) return 1;
    }
    if(nObj == NULL)
        Chat.Message(1, gObj, "[Marriage] You have 10 secs more for answer...");
    else
        Monster.NPCMessage(Index, nObj, "You have 10 secs more for answer...");

    for(i = 0; i < 50; i++)
    {
        Sleep(100);
        if(!Marry.NpcUse) return 1;
    }
    if(nObj == NULL)
        Chat.Message(1, gObj, "[Marriage] You have 5 secs more for answer...");
    else
        Monster.NPCMessage(Index, nObj, "You have 5 secs more for answer...");

    for(i = 0; i < 20; i++)
    {
        Sleep(100);
        if(!Marry.NpcUse) return 1;
    }
    if(nObj == NULL)
        Chat.Message(1, gObj, "[Marriage] You have 3 secs more for answer...");
    else
        Monster.NPCMessage(Index, nObj, "You have 3 secs more for answer...");

    for(i = 0; i < 10; i++)
    {
        Sleep(100);
        if(!Marry.NpcUse) return 1;
    }
    if(nObj == NULL)
        Chat.Message(1, gObj, "[Marriage] You have 2 secs more for answer...");
    else
        Monster.NPCMessage(Index, nObj, "You have 2 secs more for answer...");

    for(i = 0; i < 10; i++)
    {
        Sleep(100);
        if(!Marry.NpcUse) return 1;
    }
    if(nObj == NULL)
        Chat.Message(1, gObj, "[Marriage] You have 1 sec more for answer...");
    else
        Monster.NPCMessage(Index, nObj, "You have 1 sec more for answer...");

    for(i = 0; i < 10; i++)
    {
        Sleep(100);
        if(!Marry.NpcUse) return 1;
    }

    if(AddTab[Index].MarryType < 10)
        Marry.EndMarriageFalse(Index);
    return 1;
}

void cMarry::EndMarriageFalse(int Index)
{
    //LPOBJ gObj;
    OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(Index);
    if(AddTab[Index].MarryType == 1 || AddTab[Index].MarryType == 2)
    {
        Monster.NPCMessageNear(NpcObj, "%s don't answer me. Marriage canceled", gObj->Name);	//AROUND
    }
    if(AddTab[Index].MarryType == 0)
    {
        Monster.NPCMessage(Index, NpcObj, "You don't answer me. Marriage canceled");	//AROUND
    }

    AddTab[Index].MarryType = -1;

    if(gObj1 != NULL)
        AddTab[gObj1->m_Index].MarryType = -1;
    if(gObj2 != NULL)
        AddTab[gObj2->m_Index].MarryType = -1;

    NpcUse = false;
    //cMarry.fIndex = 0;
    gObj1 = NULL;
    gObj2 = NULL;
    NpcObj = NULL;
}



unsigned long __stdcall FireMarriage()
{
    LPOBJ nObj = Marry.NpcObj;
    LPOBJ kObj1 = Marry.gObj1;
    LPOBJ kObj2 = Marry.gObj2;

    PMSG_SERVERCMD ServerCmd;
    PHeadSubSetB((LPBYTE)&ServerCmd, 0xF3, 0x40, sizeof(ServerCmd));
    ServerCmd.CmdType = 0;
    for(int y = 0; y < 2; y++)
    {

        ServerCmd.X = (BYTE)kObj1->X;
        ServerCmd.Y = (BYTE)kObj1->Y;
        DataSend(kObj1->m_Index, (LPBYTE)&ServerCmd, sizeof(ServerCmd));
        MsgSendV2(kObj1, (LPBYTE)&ServerCmd, sizeof(ServerCmd));

        ServerCmd.X = (BYTE)kObj2->X;
        ServerCmd.Y = (BYTE)kObj2->Y;
        DataSend(kObj2->m_Index, (LPBYTE)&ServerCmd, sizeof(ServerCmd));
        MsgSendV2(kObj2, (LPBYTE)&ServerCmd, sizeof(ServerCmd));
    }

    Sleep(3000);

    FireworkOnTheScreen(kObj1);

    Sleep(1000);

    Monster.NPCMessageNear(nObj, "Congratulations with the wedding %s and %s!", kObj1->Name, kObj2->Name);
    Chat.MessageAllLog(0, 0, c_Green, t_Default, kObj1, "[Marriage] Congratulations with the wedding %s and %s!", kObj1->Name, kObj2->Name);

    strcpy(AddTab[Marry.gObj1->m_Index].MarryName, Marry.gObj2->Name);
    strcpy(AddTab[Marry.gObj2->m_Index].MarryName, Marry.gObj1->Name);
    AddTab[Marry.gObj1->m_Index].IsMarried = 1;
    AddTab[Marry.gObj2->m_Index].IsMarried = 1;

    MuOnlineQuery.ExecQuery("UPDATE Character SET IsMarried = 1 WHERE Name = '%s'", Marry.gObj1->Name);
    MuOnlineQuery.Fetch();
    MuOnlineQuery.Close();

    MuOnlineQuery.ExecQuery("UPDATE Character SET IsMarried = 1 WHERE Name = '%s'", Marry.gObj2->Name);
    MuOnlineQuery.Fetch();
    MuOnlineQuery.Close();

    MuOnlineQuery.ExecQuery("UPDATE Character SET MarryName = '%s' WHERE Name = '%s'",Marry.gObj2->Name, Marry.gObj1->Name);
    MuOnlineQuery.Fetch();
    MuOnlineQuery.Close();

    MuOnlineQuery.ExecQuery("UPDATE Character SET MarryName = '%s' WHERE Name = '%s'",Marry.gObj1->Name, Marry.gObj2->Name);
    MuOnlineQuery.Fetch();
    MuOnlineQuery.Close();

    Marry.NpcUse = false;
    //Marry.fIndex = 0;
    Marry.gObj1 = NULL;
    Marry.gObj2 = NULL;
    Marry.NpcObj = NULL;

    return 1;
}
void cMarry::EndMarriageTrue()
{
    DWORD ThreadID;
    HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)FireMarriage, NULL, 0, &ThreadID);

    if ( hThread == 0 )
    {
        Log.ConsoleOutPut(0, c_Red, t_NULL,"CreateThread() failed with error %d", GetLastError());
        return;
    }

    CloseHandle(hThread);
}


void cMarry::StartMarriage(int aIndex, int tIndex)
{
    OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex); //Объект игрока
    OBJECTSTRUCT *nObj = (OBJECTSTRUCT*)OBJECT_POINTER(tIndex); //Объект NPC

    //Проверка валидности Обжа
    if ( (aIndex < 0 || aIndex > OBJECT_MAX-1) && (tIndex < 0 || tIndex > OBJECT_MAX-1)) //Входит ли он в границы
	{
        return;
	}

    if(!Utilits.gObjIsConnected(aIndex)) //Является ли ОБЖ игроком
	{
        return;
	}

    if(AddTab[gObj->m_Index].IsMarried == 0 && AddTab[gObj->m_Index].MarryType == -1 && gObj1 == NULL && gObj2 == NULL)
    {
        if(!CheckMarryCost(aIndex, tIndex, 0)) return;

        if(nObj == NULL)
		{
            Chat.Message(1, gObj, "[Marriage] Do you really want to marry?");	  //PRIVAT
		}
        else
		{
            Monster.NPCMessage(gObj->m_Index, nObj, "Do you really want to marry?");			  //PRIVAT
		}

        NpcObj = nObj;
        AddTab[gObj->m_Index].MarryType = 0;

        gObj1 = gObj;
        DWORD ThreadID;
        HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)TickMarriage, (void*)gObj->m_Index, 0, &ThreadID);

        if ( hThread == 0 )
        {
            Log.ConsoleOutPut(0, c_Red, t_NULL,"CreateThread() failed with error %d", GetLastError());
            return;
        }

        CloseHandle(hThread);
    }
    else if(AddTab[gObj->m_Index].IsMarried == 0 && gObj2 != NULL && gObj1 == gObj)
    {
        if(!CheckMarryCost(aIndex, tIndex, 1))
        {
            AddTab[gObj->m_Index].MarryType = -1;
            if(gObj1 != NULL)
                AddTab[gObj1->m_Index].MarryType = -1;
            if(gObj2 != NULL)
                AddTab[gObj2->m_Index].MarryType = -1;

            NpcUse = false;
            //cMarry.fIndex = 0;
            gObj1 = NULL;
            gObj2 = NULL;
            NpcObj = NULL;
            return;
        }

        Chat.MessageAll(0, 0, gObj, "[Marriage] %s, do you really want to marry on %s?",gObj->Name , gObj2->Name);	//AROUND
        if(nObj != NULL)
            Monster.NPCMessageNear(nObj, "%s, do you really want to marry on %s?",gObj->Name , gObj2->Name);	//AROUND
        NpcObj = nObj;
        AddTab[gObj->m_Index].MarryType = 1;

        DWORD ThreadID;
        HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)TickMarriage, (void*)gObj->m_Index, 0, &ThreadID);

        if ( hThread == 0 )
        {
            Log.ConsoleOutPut(0, c_Red, t_NULL,"CreateThread() failed with error %d", GetLastError());
            return;
        }

        CloseHandle(hThread);
    }
    else if(AddTab[gObj->m_Index].IsMarried == 0 && gObj1 != NULL && AddTab[gObj->m_Index].MarryType == -1)
    {
        if(!CheckGender(aIndex, tIndex))
        {
            AddTab[gObj->m_Index].MarryType = -1;
            if(gObj1 != NULL)
                AddTab[gObj1->m_Index].MarryType = -1;
            if(gObj2 != NULL)
                AddTab[gObj2->m_Index].MarryType = -1;

            NpcUse = false;
            //cMarry.fIndex = 0;
            gObj1 = NULL;
            gObj2 = NULL;
            NpcObj = NULL;
            return;
        }

        Chat.MessageAll(0, 0, gObj, "[Marriage] %s, do you really want to marry on %s?",gObj->Name , gObj1->Name);	  //AROUND
        if(nObj != NULL)
            Monster.NPCMessageNear(nObj, "%s, do you really want to marry on %s?",gObj->Name , gObj1->Name);	  //AROUND
        NpcObj = nObj;
        AddTab[gObj->m_Index].MarryType = 2;

        gObj2 = gObj;
        DWORD ThreadID;
        HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)TickMarriage, (void*)gObj->m_Index, 0, &ThreadID);

        if ( hThread == 0 )
        {
            Log.ConsoleOutPut(0, c_Red, t_NULL,"CreateThread() failed with error %d", GetLastError());
            return;
        }

        CloseHandle(hThread);
    }
}