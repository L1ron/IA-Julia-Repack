// ================================================== //
// #			GameServer 1.00.90					# //
// #			Imagination Arts					# //
// #			Julia Project 1.1.x					# //
// ================================================== //
// #	http://imaginationarts.net/forum/			# //
// #	http://mu.raklion.ru/						# //
// ================================================== //

#include "StdAfx.h"
#include "Territory.h"
#include "Prodef.h"
#include "Logger.h"
#include "Configs.h"
#include "PCPoint.h"
#include "Utilits.h"
#include "ChatCommands.h"
#include "Query.h"
#include "Vip.h"

cTerritory Territory;

void cTerritory::ResetConfig()
{
    Config.Enabled			= 0;
    Config.AllowRebuying	= 0;
    Config.NumOfTerritorys	= 0;

    for (int i=0; i<100; i++)
    {
        Config.Terr[i].Name[0]				= NULL;
        Config.Terr[i].CostPCPoint			= 0;
        Config.Terr[i].CostWCoin			= 0;
        Config.Terr[i].CostWebPoints		= 0;
        Config.Terr[i].CostZen				= 0;
        Config.Terr[i].MinLvl				= 0;
        Config.Terr[i].MinReset				= 0;
        Config.Terr[i].OnlyForVip			= 0;
        Config.Terr[i].OnlyForMasterLvl		= 0;
        Config.Terr[i].MaxPlayers			= 0;
        Config.Terr[i].MinHours				= 0;
        Config.Terr[i].MaxHours				= 0;
        Config.Terr[i].NumOfMaps			= 0;
        for (int j=0; j<100; j++)
        {
            Config.Terr[i].Map[j].MapNum	= 0;
            Config.Terr[i].Map[j].X1		= 0;
            Config.Terr[i].Map[j].X2		= 0;
            Config.Terr[i].Map[j].Y1		= 0;
            Config.Terr[i].Map[j].Y2		= 0;
        }
    }
}

void cTerritory::Load()
{
    ResetConfig();
    Config.Enabled			= Configs.GetInt(0, 1, 0,"TerritorySystem", "Enable", IAJuliaTerritorySystem);
    if(!Config.Enabled)return;

    Config.NumOfTerritorys	= Configs.GetInt(0, 100, 0, "TerritorySystem", "NumOfTerritorys", IAJuliaTerritorySystem);
    Config.AllowRebuying	= Configs.GetInt(0, 1,	1, "TerritorySystem", "AllowRebuying",	IAJuliaTerritorySystem);

    char PTerritory[12];
    for (int i = 1; i <= Config.NumOfTerritorys; i++)
    {
        wsprintf(PTerritory, "Territory%d", i);

        GetPrivateProfileString(PTerritory, "Name", "Golden", Config.Terr[i].Name, sizeof(Config.Terr[i].Name), IAJuliaTerritorySystem);

        Config.Terr[i].CostZen			= Configs.GetInt(0, 2000000000,						0, PTerritory, "CostZen",		IAJuliaTerritorySystem);

        Config.Terr[i].CostPCPoint		= Configs.GetInt(0,	PCPoint.Config.MaximumPCPoints,	0, PTerritory, "CostPCPoint",	IAJuliaTerritorySystem);
        Config.Terr[i].CostWCoin		= Configs.GetInt(0,	PCPoint.Config.MaximumWCPoints,	0, PTerritory, "CostWCoin",		IAJuliaTerritorySystem);
        if (PCPoint.Config.WebEnabled)
            Config.Terr[i].CostWebPoints	= Configs.GetInt(0, PCPoint.Config.MaximumWebPoints,0, PTerritory, "CostWebPoints",	IAJuliaTerritorySystem);

        Config.Terr[i].MinLvl			= Configs.GetInt(0, 400,							0, PTerritory, "MinLvl",		IAJuliaTerritorySystem);
        Config.Terr[i].MinReset			= Configs.GetInt(0, 32767,							0, PTerritory, "MinReset",		IAJuliaTerritorySystem);

        Config.Terr[i].OnlyForVip		= Configs.GetInt(0, 1,								0, PTerritory, "OnlyForVip",	IAJuliaTerritorySystem);
        Config.Terr[i].OnlyForMasterLvl	= Configs.GetInt(0, 1,								0, PTerritory, "OnlyForMasterLvl",IAJuliaTerritorySystem);

        Config.Terr[i].MaxPlayers		= Configs.GetInt(0, 32767,							0, PTerritory, "MaxPlayers",	IAJuliaTerritorySystem);

        Config.Terr[i].MinHours			= Configs.GetInt(0, 32767,							1, PTerritory, "MinHours",	IAJuliaTerritorySystem);
        Config.Terr[i].MaxHours			= Configs.GetInt(Config.Terr[i].MinHours, 32767,	200, PTerritory, "MaxHours",	IAJuliaTerritorySystem);
    }

    FILE *fp;
    fp = fopen(IAJuliaTerritorySystem, "r");

    if(fp == NULL)
    {
        Config.Enabled = 0;
        Log.ConsoleOutPut(1, c_Cyan, t_Default, "[Territory System] System not active. Config file not found: %s", IAJuliaTerritorySystem);
        return;
    }
    rewind(fp);

    char Buff[256];
    int Flag = 0;
    int Temp = 0;
    int TempFlag = Flag;

    while(!feof(fp))
    {
        fgets(Buff, 255, fp);

        if(Utilits.IsBadFileLine(Buff, Flag))
            continue;

        if(Flag > 0 && Flag <= Config.NumOfTerritorys)
        {
            int n[5];
            sscanf(Buff, "%d %d %d %d %d", &n[0], &n[1], &n[2], &n[3], &n[4]);
            Temp = Config.Terr[Flag].NumOfMaps;
            Config.Terr[Flag].Map[Temp].MapNum	= n[0];
            Config.Terr[Flag].Map[Temp].X1		= n[1];
            Config.Terr[Flag].Map[Temp].Y1		= n[2];
            Config.Terr[Flag].Map[Temp].X2		= n[3];
            Config.Terr[Flag].Map[Temp].Y2		= n[4];
            Config.Terr[Flag].NumOfMaps++;
        }

        TempFlag = Flag;
    }
    for (int i = 1; i <= Config.NumOfTerritorys; i++)
    {
        Log.ConsoleOutPut(1, c_Magenta, t_Default, "[ы] [TerritorySys]\tLoaded %d territory with %d maps.",i ,Config.Terr[i].NumOfMaps);
    }
    fclose(fp);
}

int cTerritory::CheckTerritory(LPOBJ gObj)
{
    for (int i = 1; i <= Config.NumOfTerritorys; i++)
    {
        for (int j = 0; j < Config.Terr[i].NumOfMaps; j++)
        {
            if (Config.Terr[i].Map[j].MapNum == gObj->MapNumber &&
                    (Config.Terr[i].Map[j].X1 < gObj->X && Config.Terr[i].Map[j].X2 > gObj->X) &&
                    (Config.Terr[i].Map[j].Y1 < gObj->Y && Config.Terr[i].Map[j].Y2 > gObj->Y))
            {
                return i;
            }
        }
    }
    return -1;
}

int cTerritory::CheckTerritory(int MapNumber, int X, int Y)
{
    for (int i = 1; i <= Config.NumOfTerritorys; i++)
    {
        for (int j = 0; j < Config.Terr[i].NumOfMaps; j ++)
        {
            if (Config.Terr[i].Map[j].MapNum == MapNumber && (Config.Terr[i].Map[j].X1 < X && Config.Terr[i].Map[j].X2 > X) && (Config.Terr[i].Map[j].Y1 < Y && Config.Terr[i].Map[j].Y2 > Y))
            {
                return i;
            }
        }
    }
    return -1;
}
void cTerritory::Tick(LPOBJ gObj)
{
    if (!Config.Enabled)
        return;

    int Terr = CheckTerritory(gObj);
    int TempTimeGo = AddTab[gObj->m_Index].TERR_TimeGo;

    if(AddTab[gObj->m_Index].TERR_Type > 0 && Terr > 0)
    {
        AddTab[gObj->m_Index].TERR_Sec++;
        AddTab[gObj->m_Index].TERR_TimeGo = 1;
        if(AddTab[gObj->m_Index].TERR_Sec >= 60)
        {
            AddTab[gObj->m_Index].TERR_Min--;
            AddTab[gObj->m_Index].TERR_Sec = 0;

            if(Vip.CheckVipTime(AddTab[gObj->m_Index].TERR_Min))
            {
                Chat.MessageLog(1, c_Red, t_TERRITORY, gObj, "[Territory] You have %d more minutes of %s territory", AddTab[gObj->m_Index].TERR_Min, Territory.Config.Terr[AddTab[gObj->m_Index].TERR_Type].Name);
            }
            if(AddTab[gObj->m_Index].TERR_Min <= 0)
            {
                Chat.MessageLog(1, c_Red, t_TERRITORY, gObj, "[Territory] Your territory time is over! You are normal player again.");
                AddTab[gObj->m_Index].TERR_Type = 0;
                AddTab[gObj->m_Index].TERR_Min = 0;
                MuOnlineQuery.ExecQuery("UPDATE Character SET Territory_Type = 0, Territory_Time = 0 WHERE Name = '%s'", gObj->Name);
                MuOnlineQuery.Fetch();
                MuOnlineQuery.Close();
                MuOnlineQuery.ExecQuery("SELECT Territory_Type, Territory_Time FROM Character WHERE Name = '%s'", gObj->Name);
                MuOnlineQuery.Fetch();
                AddTab[gObj->m_Index].TERR_Type = MuOnlineQuery.GetAsInteger("Territory_Type");
                AddTab[gObj->m_Index].TERR_Min = MuOnlineQuery.GetAsInteger("Territory_Time");
                MuOnlineQuery.Close();
            }
            else
            {
                MuOnlineQuery.ExecQuery("UPDATE Character SET Territory_Time = (Territory_Time - 1) WHERE Name = '%s'", gObj->Name);
                MuOnlineQuery.Fetch();
                MuOnlineQuery.Close();
                MuOnlineQuery.ExecQuery("SELECT Territory_Type, Territory_Time FROM Character WHERE Name = '%s'", gObj->Name);
                MuOnlineQuery.Fetch();
                AddTab[gObj->m_Index].TERR_Type = MuOnlineQuery.GetAsInteger("Territory_Type");
                AddTab[gObj->m_Index].TERR_Min = MuOnlineQuery.GetAsInteger("Territory_Time");
                MuOnlineQuery.Close();
            }
        }
    }
    else
        AddTab[gObj->m_Index].TERR_TimeGo = 0;

    if(AddTab[gObj->m_Index].TERR_TimeGo != TempTimeGo && (AddTab[gObj->m_Index].TERR_TypeOnMap == AddTab[gObj->m_Index].TERR_Type || Terr == AddTab[gObj->m_Index].TERR_Type))
    {
        if(AddTab[gObj->m_Index].TERR_TimeGo == 1)
            Chat.MessageLog(1, c_Green, t_TERRITORY, gObj, "[Territory] You enter on %s territory. Timer started on %d min.",Territory.Config.Terr[AddTab[gObj->m_Index].TERR_Type].Name,AddTab[gObj->m_Index].TERR_Min);
        else
            Chat.MessageLog(1, c_Green, t_TERRITORY, gObj, "[Territory] You go out of %s territory. Timer stoped on %d min.",Territory.Config.Terr[AddTab[gObj->m_Index].TERR_Type].Name,AddTab[gObj->m_Index].TERR_Min);
    }

    AddTab[gObj->m_Index].TERR_TypeOnMap = Terr;
    if (Terr > 0)
    {
        if(AddTab[gObj->m_Index].TERR_Type != Terr)
        {
            if(AddTab[gObj->m_Index].TERR_X == 0 && AddTab[gObj->m_Index].TERR_Y == 0)
                Utilits.TeleToStandart(gObj->m_Index);
            else
                gObjTeleport(gObj->m_Index, AddTab[gObj->m_Index].TERR_Map, AddTab[gObj->m_Index].TERR_X, AddTab[gObj->m_Index].TERR_Y);
            Chat.MessageLog(1, c_Red, t_TERRITORY, gObj, "[Territory] You don't have access to enter %s territory.",Territory.Config.Terr[Terr].Name);
        }
    }
    else if (Terr == -1)
    {
        AddTab[gObj->m_Index].TERR_Map	= gObj->MapNumber;
        AddTab[gObj->m_Index].TERR_X	= gObj->X;
        AddTab[gObj->m_Index].TERR_Y	= gObj->Y;
    }
}

void cTerritory::Connect(LPOBJ gObj)
{
    if(Config.Enabled)
    {
        AddTab[gObj->m_Index].TERR_Sec = 0; // Обнуление секунд при входе
        if(AddTab[gObj->m_Index].TERR_Min > 0)
        {
            Chat.MessageLog(1, c_Red, t_TERRITORY, gObj, "[Territory] Left %d minutes of %s territory.", AddTab[gObj->m_Index].TERR_Min, Territory.Config.Terr[AddTab[gObj->m_Index].TERR_Type].Name);
        }
    }
}

int cTerritory::CheckPlayer(int Terr)
{
    int Result = 0;
    for (int i=OBJECT_MIN; i<=OBJECT_MAX; i++)
    {
        OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(i);

        if (!gObj || gObj->Connected != PLAYER_PLAYING)
            continue;

        for (int j = 0; j < Config.Terr[Terr].NumOfMaps; j++)
        {
            if (Config.Terr[Terr].Map[j].MapNum == gObj->MapNumber &&
                    (Config.Terr[Terr].Map[j].X1 < gObj->X && Config.Terr[Terr].Map[j].X2 > gObj->X) &&
                    (Config.Terr[Terr].Map[j].Y1 < gObj->Y && Config.Terr[Terr].Map[j].Y2 > gObj->Y))
            {
                Result++;
            }
        }
    }
    return Result;
}