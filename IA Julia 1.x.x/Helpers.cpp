#include "StdAfx.h"
#include "Protocol.h"
#include "Logger.h"
#include "Configs.h"
#include "Monster.h"
#include "ChatCommands.h"
#include "Helpers.h"

cHelpers Helpers;

void cHelpers::Load()
{
    Config.EnableEllen = Configs.GetInt(0,1,1, "HelperEllen", "EnableEllen", IAJuliaHelpers);

	if(Config.EnableEllen)
	{
        /* Carregar linhas Helper Ellen */
	}

	 Config.EnableEllen = Configs.GetInt(0,1,1, "HelperLuke", "EnableLuke", IAJuliaHelpers);

	if(Config.EnableLuke)
	{
        /* Carregar linhas Helper Luke */
	}
	
    Config.EnableEllen = Configs.GetInt(0,1,1, "HelperLeo", "EnableLeo", IAJuliaHelpers);

	if(Config.EnableEllen)
	{
        /* Carregar linhas Helper Leo */
	}
}

void cHelpers::HelperEllenClick(LPOBJ gObj, LPOBJ gObjNPC)
{
	if(Config.EnableEllen)
	{
		Monster.NPCMessageLog(c_Blue,t_COMMANDS,gObj,gObjNPC,"Ola! Em que posso ajudar?");
	}
	else
	{
		Monster.NPCMessageLog(c_Blue,t_COMMANDS,gObj,gObjNPC,"Nao estou de servico, volte mais tarde.");
	}
}

void cHelpers::HelperLukeClick(LPOBJ gObj, LPOBJ gObjNPC)
{
	if(!Config.EnableLuke)
	{
		Monster.NPCMessageLog(c_Blue,t_COMMANDS,gObj,gObjNPC,"Ola! Em que posso ajudar?");
	}
	else
	{
		Monster.NPCMessageLog(c_Blue,t_COMMANDS,gObj,gObjNPC,"Nao estou de servico, volte mais tarde.");
	}
}

void cHelpers::HelperLeoClick(LPOBJ gObj, LPOBJ gObjNPC)
{
	if(Config.EnableLeo)
	{
		Monster.NPCMessageLog(c_Blue,t_COMMANDS,gObj,gObjNPC,"Ola! Em que posso ajudar?");
	}
	else
	{
		Monster.NPCMessageLog(c_Blue,t_COMMANDS,gObj,gObjNPC,"Nao estou de servico, volte mais tarde.");
	}
}