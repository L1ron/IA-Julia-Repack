#include "StdAfx.h"
#include "Configs.h"
#include "Helpers.h"
#include "Prodef.h"
#include "User.h"
#include "ChatCommands.h"
#include "Utilits.h"
#include "PCPoint.h"
#include "Monster.h"
#include "Query.h"
#include "ChatCommands.h"

cHelpers Helpers;
sHelperItens HelperItens[MaxItemsInBag];

void cHelpers::Load()
{
	Config.Enable = Configs.GetInt(0,1,1,"Helpers","Enable",IAJuliaHelpers);

	if(Config.Enable)
	{
		Config.UsePK			= Configs.GetInt(0,1,0,"Helpers","UsePK",IAJuliaHelpers);
		Config.PriceZen			= Configs.GetInt(0,2000000000,100000000,"Helpers","PriceZen",IAJuliaHelpers);
		Config.PricePCPoint		= Configs.GetInt(0,PCPoint.Config.MaximumPCPoints,10,"Helpers","PricePCPoint",IAJuliaHelpers);
		Config.PriceWCoin		= Configs.GetInt(0,PCPoint.Config.MaximumWCPoints,10,"Helpers","PriceWCoin",IAJuliaHelpers);
		Config.PriceWebPoint	= Configs.GetInt(0,PCPoint.Config.MaximumWebPoints,10,"Helpers","PriceWebPoint",IAJuliaHelpers);
		Config.UseTimes			= Configs.GetInt(0,65535,2,"Helpers","UseTimes",IAJuliaHelpers);

		if(Config.UseTimes > 0)
		{
			strcpy(Config.Table,(Configs.GetInt(0,1,1,"Helpers","HelperByAcc",IAJuliaHelpers) > 0) ? "MEMB_INFO" : "Character");

			GetPrivateProfileString("Helpers","HelperColumn","HelperUses",Config.Column,sizeof(Config.Column),IAJuliaHelpers);

			MuOnlineQuery.CheckColumn(Config.Column,Config.Table,"ALTER TABLE %s ADD [%s][int] DEFAULT (0) NOT NULL",Config.Table,Config.Column);
		}

		FILE *File;
		File = fopen(IAJuliaHelpers,"r");

		if(File == NULL)
		{
			Log.ConsoleOutPut(0,c_Red,t_NULL,"[û] [NPC Helper]\t%s nao encontrado, NPC Helper inativo.",IAJuliaHelpers);

			Config.Enable = 0;
		}
		else
		{
			int Flag = 0;
			char zBuffer[1024],C[12] = {0};

			while(!feof(File))
			{
				fgets(zBuffer,1024,File);

				if(Utilits.IsBadFileLine(zBuffer,Flag))
				{
					continue;
				}

				if(Flag == 1)
				{
					sscanf(zBuffer,"%d %d %d %d %d %d %d %d",&Type,&Index,&Level,&Duration,&Luck,&Skill,&Option,&Excellent);

					HelperItens[Itens].Grupo = this->Type;
					HelperItens[Itens].Index = this->Index;
					HelperItens[Itens].Level = this->Level;
					HelperItens[Itens].Durabilidade = this->Duration;
					HelperItens[Itens].Luck = this->Luck;
					HelperItens[Itens].Skill = this->Skill;
					HelperItens[Itens].Option = this->Option;
					HelperItens[Itens].Exelente = this->Excellent;

					Itens++;
				}
			}

			fclose(File);

			Log.ConsoleOutPut(1,c_Yellow,t_HELPERS,"[û] [NPC Helper]\t%d itens foram carregados.",Itens);
		}
	}
}

void cHelpers::Connect(LPOBJ gObj)
{
	if(Config.Enable)
	{
		AddTab[gObj->m_Index].HELPER_UsedTimes = 0;

		if(Config.UseTimes > 0)
		{
			MuOnlineQuery.ExecQuery
			(
				"SELECT %s FROM %s WHERE %s = '%s'",
				Config.Column,
				Config.Table,
				(Config.Table[0] = 'M') ? "memb___id" : "AccountID",
				gObj->AccountID
			);

			MuOnlineQuery.Fetch();
			AddTab[gObj->m_Index].HELPER_UsedTimes = MuOnlineQuery.GetAsInteger(Config.Column);
			MuOnlineQuery.Close();
		}
	}
}

void cHelpers::HelperEllenClick(LPOBJ gObj, LPOBJ gObjNPC)
{
	if(Config.Enable)
	{
		CheckConditions(gObj, gObjNPC);
	}
	else
	{
		Monster.NPCMessageLog(c_Blue,t_HELPERS,gObj,gObjNPC,"Nao estou de servico, volte mais tarde.");
	}
}

void cHelpers::HelperLukeClick(LPOBJ gObj, LPOBJ gObjNPC)
{
	if(Config.Enable)
	{
		CheckConditions(gObj, gObjNPC);
	}
	else
	{
		Monster.NPCMessageLog(c_Blue,t_HELPERS,gObj,gObjNPC,"Nao estou de servico, volte mais tarde.");
	}
}

void cHelpers::HelperLeoClick(LPOBJ gObj, LPOBJ gObjNPC)
{
	if(Config.Enable)
	{
		CheckConditions(gObj, gObjNPC);
	}
	else
	{
		Monster.NPCMessageLog(c_Blue,t_HELPERS,gObj,gObjNPC,"Nao estou de servico, volte mais tarde.");
	}
}

void cHelpers::CheckConditions(LPOBJ gObj,LPOBJ gObjNPC)
{
	if(Chat.CheckCommand(gObj, Config.Enable, GmSystem.NONE, Config.PriceZen, Config.PricePCPoint, Config.PriceWCoin, 0, 0, 0, 0,gObjNPC->Name,"",""))
	{
		return;
	}

	if(AddTab[gObj->m_Index].HELPER_UsedTimes >= Config.UseTimes)
	{
		Monster.NPCMessageLog(c_Red,t_HELPERS,gObj,gObjNPC,"Voce ja teve sua ajuda.");

		return;
	}

	if(gObj->m_PK_Level > 3)
	{
		Monster.NPCMessageLog(c_Red,t_HELPERS,gObj,gObjNPC,"Nao farei negocios com PKs!.");
		
		return;
	}

	Chat.TakeCommand(gObj,Config.PriceZen,Config.PricePCPoint, Config.PriceWCoin,Config.PriceWebPoint,gObjNPC->Name);

	if(Config.UseTimes > 0)
	{
		AddTab[gObj->m_Index].HELPER_UsedTimes++;

		if(Config.Table[0] = 'M')// Fixar!
		{
			Me_MuOnlineQuery.ExecQuery
			(
				"UPDATE %s SET %s = %s + 1 WHERE %s = '%s'",
				Config.Table,
				Config.Column,
				Config.Column,
				(Config.Table[0] = 'M') ? "memb___id" : "AccountID",
				gObj->AccountID
			);
		}
		else
		{
			MuOnlineQuery.ExecQuery
			(
				"UPDATE %s SET %s = %s + 1 WHERE %s = '%s'",
				Config.Table,
				Config.Column,
				Config.Column,
				(Config.Table[0] = 'M') ? "memb___id" : "AccountID",
				gObj->AccountID
			);
		}

		MuOnlineQuery.Fetch();
		MuOnlineQuery.Close();
	}

	this->GenerateItem(gObj->m_Index);
	Monster.NPCMessageLog(c_Blue,t_HELPERS,gObj,gObjNPC,"Boa sorte em sua jornada!");
}

void cHelpers::GenerateItem(int aIndex)
{
	int i = rand() % Itens;

	int exelent;
	int exelentrand;

	exelent = HelperItens[i].Exelente;

	if(exelent == 0)
	{
		exelentrand = 0;
	}
	else
	{
		exelentrand = rand() % exelent;
	}

	OBJECTSTRUCT * gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);
	DWORD Premio = HelperItens[i].Grupo*512+HelperItens[i].Index;

	ItemSerialCreateSend
	(
		gObj->m_Index,
		gObj->MapNumber,
		(BYTE)gObj->X,
		(BYTE)gObj->Y,
		Premio,
		HelperItens[i].Level,
		HelperItens[i].Durabilidade,
		HelperItens[i].Luck,
		HelperItens[i].Skill,
		HelperItens[i].Option,
		gObj->m_Index,
		exelentrand,
		0
	);
}