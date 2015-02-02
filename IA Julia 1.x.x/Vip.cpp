#include "StdAfx.h"
#include "Vip.h"
#include "User.h"
#include "Configs.h"
#include "Query.h"
#include "ChatCommands.h"
#include "Logger.h"
#include "PCPoint.h"
#include "Utilits.h"
#include "MoveReq.h"

cVip Vip;

void cVip::ResetConfig()
{
    Config.Enabled = 0;
    Config.AllowRebuying = 0;
    Config.Column[0] = NULL;
    Config.ColumnDate[0] = NULL;
    Config.NumStates = 0;

    for (int i = 0; i < 20; i++)
    {
        Config.VIPState[i].VIPName[0] = NULL;
        Config.VIPState[i].EnabledCmd = 0;
        Config.VIPState[i].CostPCPoints = 0;
        Config.VIPState[i].CostWCoins = 0;
        Config.VIPState[i].CostWebPoints = 0;
        Config.VIPState[i].CostZen = 0;

        Config.VIPState[i].BonusExp = 0;
        Config.VIPState[i].BonusZen = 0;
        Config.VIPState[i].BonusDrop = 0;

        Config.VIPState[i].MinHours = 0;
        Config.VIPState[i].MaxHours = 0;
        Config.VIPState[i].EnableOnOff = 0;
    }
}

void cVip::Load()
{
    ResetConfig();
    Config.Enabled = Configs.GetInt(0,1,1,"VipSystem","EnableVip",IAJuliaVIP);

    if(!Config.Enabled)
	{
		return;
	}

	GetPrivateProfileString("VipSystem", "VIPTable", "Character", Config.Table, sizeof(Config.Table), IAJuliaVIP);
    GetPrivateProfileString("VipSystem", "VIPColumn", "VIP", Config.Column, sizeof(Config.Column), IAJuliaVIP);
    GetPrivateProfileString("VipSystem", "VIPColumnDate", "VIP_DATE", Config.ColumnDate, sizeof(Config.ColumnDate), IAJuliaVIP);

	MuOnlineQuery.CheckColumn(Config.Column, Config.Table, "ALTER TABLE %s ADD [%s][int] DEFAULT (0) NOT NULL", Config.Table, Config.Column);
    MuOnlineQuery.CheckColumn(Config.ColumnDate, Config.Table, "ALTER TABLE %s ADD [%s][int] DEFAULT (0) NOT NULL", Config.Table, Config.ColumnDate);
    MuOnlineQuery.CheckColumn("VIP_ONOFF", Config.Table, "ALTER TABLE %s ADD [VIP_ONOFF][int] DEFAULT (1) NOT NULL",Config.Table);

    Config.NumStates = Configs.GetInt(0, 10, 3, "VipSystem", "NumStates", IAJuliaVIP);
    Config.AllowRebuying = Configs.GetInt(0, 1, 0, "VipSystem", "AllowRebuying", IAJuliaVIP);

    char PState[10];

    for (int i = 1; i <= Config.NumStates; i++)
    {
        wsprintf(PState, "State%d", i);

        GetPrivateProfileString(PState, "VIPStateName", "bronze", Config.VIPState[i].VIPName, sizeof(Config.VIPState[i].VIPName), IAJuliaVIP);

        Config.VIPState[i].EnabledCmd = Configs.GetInt(0, 1, 1, PState, "AllowAutoBuy", IAJuliaVIP);
        Config.VIPState[i].CostPCPoints = Configs.GetInt(0, PCPoint.Config.MaximumPCPoints, 5, PState, "CostPCPoints", IAJuliaVIP);
        Config.VIPState[i].CostWCoins = Configs.GetInt(0, PCPoint.Config.MaximumWCPoints, 5, PState, "CostWCoins", IAJuliaVIP);
        Config.VIPState[i].CostWebPoints = Configs.GetInt(0, PCPoint.Config.MaximumWebPoints, 5, PState, "CostWebPoints", IAJuliaVIP);
        Config.VIPState[i].CostZen = Configs.GetInt(0, 2000000000, 5000, PState, "CostZen", IAJuliaVIP);

        Config.VIPState[i].BonusExp = Configs.GetInt(0, 9999, 5, PState, "BonusExp", IAJuliaVIP);
        Config.VIPState[i].BonusZen = Configs.GetInt(0, 9999, 5, PState, "BonusZen", IAJuliaVIP);
        Config.VIPState[i].BonusDrop = Configs.GetInt(0, 9999, 5, PState, "BonusDrop", IAJuliaVIP);

        Config.VIPState[i].MinHours = Configs.GetInt(0, 32000, 1, PState, "MinHours", IAJuliaVIP);
        Config.VIPState[i].MaxHours = Configs.GetInt(Config.VIPState[i].MinHours, 32000, 200, PState, "MaxHours", IAJuliaVIP);
        Config.VIPState[i].EnableOnOff = Configs.GetInt(0, 1, 1, PState, "EnableOnOff", IAJuliaVIP);
    }

    Log.ConsoleOutPut(1, c_Yellow, t_Default, "[û] [Vip System]\tStates Carregados.");
}

void cVip::Connect(LPOBJ gObj)
{
    if(Config.Enabled)
    {
        AddTab[gObj->m_Index].VIP_Sec = 0;

        if(AddTab[gObj->m_Index].VIP_Min > 0)
        {
            Chat.MessageLog(1, c_Red, t_VIP, gObj, "[VIP] Restam %d minutos do seu VIP.", AddTab[gObj->m_Index].VIP_Min);

            if (AddTab[gObj->m_Index].VIP_On)
            {
                Chat.MessageLog(1, c_Red, t_VIP, gObj, "[VIP] Seu VIP foi iniciado! Para pausar, use /vip off");
            }
            else
            {
                Chat.MessageLog(1, c_Red, t_VIP, gObj, "[VIP] Seu VIP foi pausado! Para iniciar, use /vip on");
            }
        }
    }
}

void cVip::Tick(LPOBJ gObj)
{
    int MapVip = MoveReq.GetMapVip(gObj->MapNumber);

    if (MapVip > 0 && !GmSystem.IsAdmin(gObj->Name))
    {
        if (AddTab[gObj->m_Index].VIP_Type < MapVip)
        {
            Chat.MessageLog(1, c_Red, t_TERRITORY, gObj, "[VIP] Voce nao tem acesso ao mapa %s.", Utilits.GetMapName(gObj->MapNumber));

            if(AddTab[gObj->m_Index].VIP_X == 0 && AddTab[gObj->m_Index].VIP_Y == 0)
            {
                Utilits.TeleToStandart(gObj->m_Index);
            }
            else
            {
                gObjTeleport(gObj->m_Index, AddTab[gObj->m_Index].VIP_Map, AddTab[gObj->m_Index].VIP_X, AddTab[gObj->m_Index].VIP_Y);
            }
        }
    }
    else
    {
        AddTab[gObj->m_Index].TERR_Map = gObj->MapNumber;
        AddTab[gObj->m_Index].TERR_X = gObj->X;
        AddTab[gObj->m_Index].TERR_Y = gObj->Y;
    }

    if (AddTab[gObj->m_Index].VIP_Type > 0 && Config.Enabled)
    {
        if (AddTab[gObj->m_Index].VIP_On == 0)
		{
            return;
		}

        AddTab[gObj->m_Index].VIP_Sec++;

        if(AddTab[gObj->m_Index].VIP_Sec >= 60)
        {
            AddTab[gObj->m_Index].VIP_Min--;
            AddTab[gObj->m_Index].VIP_Sec = 0;

            if(CheckVipTime(AddTab[gObj->m_Index].VIP_Min))
            {
                Chat.MessageLog(1, c_Red, t_VIP, gObj, "[VIP] Restam %d minutos do seu VIP.", AddTab[gObj->m_Index].VIP_Min);
            }

            if(AddTab[gObj->m_Index].VIP_Min > 0)
            {
                MuOnlineQuery.ExecQuery("UPDATE %s SET %s = (%s - 1) WHERE %s = '%s'", Config.Table, Config.ColumnDate, Config.ColumnDate, (Config.Table[0] = 'M') ? "memb___id" : "AccountID", gObj->AccountID);
                MuOnlineQuery.Fetch();
                MuOnlineQuery.Close();
                MuOnlineQuery.ExecQuery("SELECT %s, %s FROM %s WHERE %s = '%s'", Config.Column, Config.ColumnDate, Config.Table, (Config.Table[0] = 'M') ? "memb___id" : "AccountID", gObj->AccountID);
                MuOnlineQuery.Fetch();
                AddTab[gObj->m_Index].VIP_Type = MuOnlineQuery.GetAsInteger(Config.Column);
                AddTab[gObj->m_Index].VIP_Min = MuOnlineQuery.GetAsInteger(Config.ColumnDate);
                MuOnlineQuery.Close();
            }
            else
            {
                Chat.MessageLog(1, c_Red, t_VIP, gObj, "[VIP] Seu VIP acabou!");
                
				AddTab[gObj->m_Index].VIP_Type = 0;
                AddTab[gObj->m_Index].VIP_Min = 0;
               
				MuOnlineQuery.ExecQuery("UPDATE %s SET %s = 0, %s = 0 WHERE %s = '%s'", Config.Table, Config.Column, Config.ColumnDate,(Config.Table[0] = 'M') ? "memb___id" : "AccountID", gObj->AccountID);
                MuOnlineQuery.Fetch();
                MuOnlineQuery.Close();

                MuOnlineQuery.ExecQuery("SELECT %s, %s FROM %s WHERE %s = '%s'", Config.Column, Config.ColumnDate, Config.Table, (Config.Table[0] = 'M') ? "memb___id" : "AccountID", gObj->AccountID);
                MuOnlineQuery.Fetch();
                AddTab[gObj->m_Index].VIP_Type = MuOnlineQuery.GetAsInteger(Config.Column);
                AddTab[gObj->m_Index].VIP_Min = MuOnlineQuery.GetAsInteger(Config.ColumnDate);
                MuOnlineQuery.Close();
            }
        }
    }
}

bool cVip::CheckVipTime(int TimeInMin)
{
    switch(TimeInMin)
    {
		case 1: case 2:
		case 3: case 5:
		case 15: case 30:
		case 60: case 120:
		case 340: case 680:
		{
			return true;
		}
    }

    return false;
}

int cVip::GetBonus(LPOBJ gObj, eBonus Type)
{
    int VIPInfo = AddTab[gObj->m_Index].VIP_Type;

    if (VIPInfo < 0 || VIPInfo > Config.NumStates)
	{
        return 0;
	}

    if (AddTab[gObj->m_Index].VIP_On == 0)
	{
        return 0;
	}

    switch (Type)
    {
		case b_EXP:
		{
			return Config.VIPState[VIPInfo].BonusExp;
		}
		case b_DROP:
		{
			return Config.VIPState[VIPInfo].BonusDrop;
		}
		case b_ZEN:
		{
			return Config.VIPState[VIPInfo].BonusZen;
		}
    }

    return 0;
}