#include "Stdafx.h"
#include "AntiAFK.h"
#include "ChatCommands.h"
#include "User.h"
#include "Configs.h"
#include "Utilits.h"

cAntiAFK AntiAFK;

void cAntiAFK::ResetConfig()
{
	Config.Enabled	= 0;
	Config.Time		= 0;
	Config.Warnings = 0;

	ArrayMap[0] = NULL;
}

void cAntiAFK::Load()
{
	ResetConfig();
	Config.Enabled	= Configs.GetInt(0, 1,		1,	 "AntiAFK", "AntiAFKEnabled",	IAJuliaAntiAFK);

	if(!Config.Enabled)
	{
		return;
	}

	Config.Time		= Configs.GetInt(0, 32000,	300, "AntiAFK", "AntiAFKTimer",		IAJuliaAntiAFK);
	Config.Warnings	= Configs.GetInt(0, 5,		3,	 "AntiAFK",	"AntiAFKWarnings",	IAJuliaAntiAFK);

	FILE *file;

	file = fopen(IAJuliaAntiAFK,"r");

	if(file == NULL)
	{
		Config.Enabled = 0;
		Log.ConsoleOutPut(1,c_Red,t_Error,"[X] [AntiAFK]\tImpossivel abrir %s",IAJuliaAntiAFK);

		return;
	}

	char Buff[256];
	int Flag = 0;

	while(!feof(file))
	{
		fgets(Buff,256,file);

		if(Utilits.IsBadFileLine(Buff, Flag))
		{
			continue;
		}

		if(Flag == 1)
		{
			int n[2];
			sscanf(Buff,"%d %d",&n[0],&n[1]);
			ArrayMap[n[0]] = n[1];
		}
	}

	fclose(file);
	Log.ConsoleOutPut(1, c_Magenta, t_Default, "[û] [AntiAFK]\tMapas carregados.");
}

void cAntiAFK::Tick(LPOBJ gObj)
{
	if(Config.Enabled == 0)
	{
		return;
	}

	int Index = gObj->m_Index;
	AddTab[Index].AFK_Timer++;

	if ( ArrayMap[gObj->MapNumber] == 0 )
	{
		AddTab[Index].AFK_Timer = 0;
	}

	if(gObj->MapNumber != AddTab[Index].AFK_MapNumber || (gObj->MapNumber > 60 && gObj->MapNumber < 65))
	{
		AddTab[Index].AFK_MapNumber = gObj->MapNumber;
		AddTab[Index].AFK_Timer = 0;
		AddTab[Index].AFK_Temp = gObj->m_TotalAttackCount;
	}
	if(gObj->X != AddTab[Index].AFK_X)
	{
		AddTab[Index].AFK_X = gObj->X;
		AddTab[Index].AFK_Timer = 0;
		AddTab[Index].AFK_Temp = gObj->m_TotalAttackCount;

	}
	if(gObj->Y != AddTab[Index].AFK_Y)
	{
		AddTab[Index].AFK_Y = gObj->Y;
		AddTab[Index].AFK_Timer = 0;
		AddTab[Index].AFK_Temp = gObj->m_TotalAttackCount;
	}

	if
	(
		(gObj->m_TotalAttackCount != AddTab[Index].AFK_Temp) &&
		(AddTab[Index].AFK_Timer >= Config.Time) &&
		(AddTab[Index].AFK_Warnings != Config.Warnings)
	)
	{
		AddTab[Index].AFK_Timer = 0;
		AddTab[Index].AFK_Temp = gObj->m_TotalAttackCount;
		AddTab[Index].AFK_Y = gObj->Y;
		AddTab[Index].AFK_X = gObj->X;
		AddTab[Index].AFK_MapNumber = gObj->MapNumber;
		AddTab[Index].AFK_Warnings++;

		Chat.MessageLog(1, c_Red, t_Default, gObj,"[AntiAfk][%s] Numero do aviso atual: %d",gObj->Name,AddTab[Index].AFK_Warnings);
	}

	if(gObj->m_TotalAttackCount != AddTab[Index].AFK_Temp && AddTab[Index].AFK_Timer >= Config.Time)
	{
		AddTab[Index].AFK_Timer = 0;
		AddTab[Index].AFK_Temp = gObj->m_TotalAttackCount;
		AddTab[Index].AFK_Y = gObj->Y;
		AddTab[Index].AFK_X = gObj->X;
		AddTab[Index].AFK_Warnings = 0;
		AddTab[Index].AFK_MapNumber = gObj->MapNumber;

		Chat.MessageLog(1, c_Red, t_Default, gObj, "[AntiAfk] Voce foi movido para uma zona segura!");
		Utilits.TeleToStandart(Index);
	}
}