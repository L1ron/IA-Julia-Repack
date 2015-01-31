#include "StdAfx.h"
#include "ChatCommands.h"
#include "Configs.h"
#include "User.h"
#include "Utilits.h"
#include "Logger.h"
#include "PCPoint.h"
#include "MoveReq.h"
#include "DropSystem.h"
#include "Monster.h"
#include "MapSystem.h"
#include "Query.h"
#include "WZEventDrop.h"
#include "Vip.h"
#include "Territory.h"
#include "OffTrade.h"
#include "ResetSystem.h"
#include "MarrySystem.h"

cChat Chat;
CRITICAL_SECTION Chat_Crit;

cChat::cChat()
{
	InitializeCriticalSection(&Chat_Crit);
}

cChat::~cChat()
{
	/**/
}

void cChat::LoadChatCommands()
{
	GetPrivateProfileString("Strings", "COMMAND_GG", "/gg", COMMAND_GG, sizeof(COMMAND_GG), IAJuliaChatCommands);
	GetPrivateProfileString("Strings", "COMMAND_VOSKL", "!", COMMAND_VOSKL, sizeof(COMMAND_VOSKL), IAJuliaChatCommands);
	GetPrivateProfileString("Strings", "COMMAND_TRACE", "/trace", COMMAND_TRACE, sizeof(COMMAND_TRACE), IAJuliaChatCommands);
	GetPrivateProfileString("Strings", "COMMAND_DISCONNECT", "/disconnect", COMMAND_DISCONNECT, sizeof(COMMAND_DISCONNECT), IAJuliaChatCommands);
	GetPrivateProfileString("Strings", "COMMAND_TRACK", "/track", COMMAND_TRACK, sizeof(COMMAND_TRACK), IAJuliaChatCommands);
	GetPrivateProfileString("Strings", "COMMAND_MOVE", "/move", COMMAND_MOVE, sizeof(COMMAND_MOVE), IAJuliaChatCommands);
	GetPrivateProfileString("Strings", "COMMAND_WARP", "/warp", COMMAND_WARP, sizeof(COMMAND_WARP), IAJuliaChatCommands);
	GetPrivateProfileString("Strings", "COMMAND_LEVEL", "/level", COMMAND_LEVEL, sizeof(COMMAND_LEVEL), IAJuliaChatCommands);
	GetPrivateProfileString("Strings", "COMMAND_POST", "/post", COMMAND_POST, sizeof(COMMAND_POST), IAJuliaChatCommands);
	GetPrivateProfileString("Strings", "COMMAND_BAN_POST", "/banpost", COMMAND_BAN_POST, sizeof(COMMAND_BAN_POST), IAJuliaChatCommands);
	GetPrivateProfileString("Strings", "COMMAND_BAN_CHAR", "/banchar", COMMAND_BAN_CHAR, sizeof(COMMAND_BAN_CHAR), IAJuliaChatCommands);
	GetPrivateProfileString("Strings", "COMMAND_BAN_ACC", "/banacc", COMMAND_BAN_ACC, sizeof(COMMAND_BAN_ACC), IAJuliaChatCommands);
	GetPrivateProfileString("Strings", "COMMAND_UNBAN_POST", "/unbanpost", COMMAND_UNBAN_POST, sizeof(COMMAND_UNBAN_POST), IAJuliaChatCommands);
	GetPrivateProfileString("Strings", "COMMAND_UNBAN_CHAR", "/unbanchar", COMMAND_UNBAN_CHAR, sizeof(COMMAND_UNBAN_CHAR), IAJuliaChatCommands);
	GetPrivateProfileString("Strings", "COMMAND_UNBAN_ACC", "/unbanacc", COMMAND_UNBAN_ACC, sizeof(COMMAND_UNBAN_ACC), IAJuliaChatCommands);
	GetPrivateProfileString("Strings", "COMMAND_TIME", "/time", COMMAND_TIME, sizeof(COMMAND_TIME), IAJuliaChatCommands);
	GetPrivateProfileString("Strings", "COMMAND_SET_CHAR", "/setchar", COMMAND_SET_CHAR, sizeof(COMMAND_SET_CHAR), IAJuliaChatCommands);
	GetPrivateProfileString("Strings", "COMMAND_SET_PK", "/setpk", COMMAND_SET_PK, sizeof(COMMAND_SET_PK), IAJuliaChatCommands);
	GetPrivateProfileString("Strings", "COMMAND_SET_ZEN", "/setzen", COMMAND_SET_ZEN, sizeof(COMMAND_SET_ZEN), IAJuliaChatCommands);
	GetPrivateProfileString("Strings", "COMMAND_SKIN", "/skin", COMMAND_SKIN, sizeof(COMMAND_SKIN), IAJuliaChatCommands);
	GetPrivateProfileString("Strings", "COMMAND_DROP", "/drop", COMMAND_DROP, sizeof(COMMAND_DROP), IAJuliaChatCommands);
	GetPrivateProfileString("Strings", "COMMAND_GMOVE", "/gmove", COMMAND_GMOVE, sizeof(COMMAND_GMOVE), IAJuliaChatCommands);
	GetPrivateProfileString("Strings", "COMMAND_ONLINE", "/online", COMMAND_ONLINE, sizeof(COMMAND_ONLINE), IAJuliaChatCommands);
	GetPrivateProfileString("Strings", "COMMAND_STATUS", "/status", COMMAND_STATUS, sizeof(COMMAND_STATUS), IAJuliaChatCommands);
	GetPrivateProfileString("Strings", "COMMAND_RELOAD", "/reload", COMMAND_RELOAD, sizeof(COMMAND_RELOAD), IAJuliaChatCommands);
	GetPrivateProfileString("Strings", "COMMAND_PKCLEAR", "/pkclear", COMMAND_PKCLEAR, sizeof(COMMAND_PKCLEAR), IAJuliaChatCommands);
	GetPrivateProfileString("Strings", "COMMAND_ADD_STR", "/str", COMMAND_ADD_STR, sizeof(COMMAND_ADD_STR), IAJuliaChatCommands);
	GetPrivateProfileString("Strings", "COMMAND_ADD_AGI", "/agi", COMMAND_ADD_AGI, sizeof(COMMAND_ADD_AGI), IAJuliaChatCommands);
	GetPrivateProfileString("Strings", "COMMAND_ADD_VIT", "/vit", COMMAND_ADD_VIT, sizeof(COMMAND_ADD_VIT), IAJuliaChatCommands);
	GetPrivateProfileString("Strings", "COMMAND_ADD_ENE", "/ene", COMMAND_ADD_ENE, sizeof(COMMAND_ADD_ENE), IAJuliaChatCommands);
	GetPrivateProfileString("Strings", "COMMAND_ADD_CMD", "/cmd", COMMAND_ADD_CMD, sizeof(COMMAND_ADD_CMD), IAJuliaChatCommands);
	GetPrivateProfileString("Strings", "COMMAND_WARE", "/ware", COMMAND_WARE, sizeof(COMMAND_WARE), IAJuliaChatCommands);
	GetPrivateProfileString("Strings", "COMMAND_MOBADD", "/mobadd", COMMAND_MOBADD, sizeof(COMMAND_MOBADD), IAJuliaChatCommands);
	GetPrivateProfileString("Strings", "COMMAND_SETDROP", "/setdrop", COMMAND_SETDROP, sizeof(COMMAND_SETDROP), IAJuliaChatCommands);
	GetPrivateProfileString("Strings", "COMMAND_CHECK", "/check", COMMAND_CHECK, sizeof(COMMAND_CHECK), IAJuliaChatCommands);
	GetPrivateProfileString("Strings", "COMMAND_VIPBUY", "/vipbuy", COMMAND_VIPBUY, sizeof(COMMAND_VIPBUY), IAJuliaChatCommands);
	GetPrivateProfileString("Strings", "COMMAND_VIPCHECK", "/vipcheck", COMMAND_VIPCHECK, sizeof(COMMAND_VIPCHECK), IAJuliaChatCommands);
	GetPrivateProfileString("Strings", "COMMAND_VIPLIST", "/viplist", COMMAND_VIPLIST, sizeof(COMMAND_VIPLIST), IAJuliaChatCommands);
	GetPrivateProfileString("Strings", "COMMAND_TERRCHECK", "/terrcheck", COMMAND_TERRCHECK, sizeof(COMMAND_TERRCHECK), IAJuliaChatCommands);
	GetPrivateProfileString("Strings", "COMMAND_TERRBUY", "/terrbuy", COMMAND_TERRBUY, sizeof(COMMAND_TERRBUY), IAJuliaChatCommands);
	GetPrivateProfileString("Strings", "COMMAND_VIP_ON", "/vip on", COMMAND_VIP_ON, sizeof(COMMAND_VIP_ON), IAJuliaChatCommands);
	GetPrivateProfileString("Strings", "COMMAND_VIP_OFF", "/vip off", COMMAND_VIP_OFF, sizeof(COMMAND_VIP_OFF), IAJuliaChatCommands);
	GetPrivateProfileString("Strings", "COMMAND_AT", "@", COMMAND_AT, sizeof(COMMAND_AT), IAJuliaChatCommands);
	GetPrivateProfileString("Strings", "COMMAND_ENABLE_CHAT", "/enablechat", COMMAND_ENABLE_CHAT, sizeof(COMMAND_ENABLE_CHAT), IAJuliaChatCommands);
	GetPrivateProfileString("Strings", "COMMAND_DISABLE_CHAT", "/disablechat", COMMAND_DISABLE_CHAT, sizeof(COMMAND_DISABLE_CHAT), IAJuliaChatCommands);
	GetPrivateProfileString("Strings", "COMMAND_WCOIN_PCOINT", "/wcoin-pcpoint", COMMAND_WCOIN_PCOINT, sizeof(COMMAND_WCOIN_PCOINT), IAJuliaChatCommands);
	GetPrivateProfileString("Strings", "COMMAND_WCOIN_WEBPOINT", "/wcoin-webpoint", COMMAND_WCOIN_WEBPOINT, sizeof(COMMAND_WCOIN_WEBPOINT), IAJuliaChatCommands);
	GetPrivateProfileString("Strings", "COMMAND_WCOIN_ZEN", "/wcoin-zen", COMMAND_WCOIN_ZEN, sizeof(COMMAND_WCOIN_ZEN), IAJuliaChatCommands);
	GetPrivateProfileString("Strings", "COMMAND_WEBPOINT_WCOIN", "/webpoint-wcoin", COMMAND_WEBPOINT_WCOIN, sizeof(COMMAND_WEBPOINT_WCOIN), IAJuliaChatCommands);
	GetPrivateProfileString("Strings", "COMMAND_WEBPOINT_PCPOINT", "/webpoint-pcpoint", COMMAND_WEBPOINT_PCPOINT, sizeof(COMMAND_WEBPOINT_PCPOINT), IAJuliaChatCommands);
	GetPrivateProfileString("Strings", "COMMAND_WEBPOINT_ZEN", "/webpoint-zen", COMMAND_WEBPOINT_ZEN, sizeof(COMMAND_WEBPOINT_ZEN), IAJuliaChatCommands);
	GetPrivateProfileString("Strings", "COMMAND_PCPOINT_ZEN", "/pcpoint-zen", COMMAND_PCPOINT_ZEN, sizeof(COMMAND_PCPOINT_ZEN), IAJuliaChatCommands);
	GetPrivateProfileString("Strings", "COMMAND_PCPOINT_WCOIN", "/pcpoint-wcoin", COMMAND_PCPOINT_WCOIN, sizeof(COMMAND_PCPOINT_WCOIN), IAJuliaChatCommands);
	GetPrivateProfileString("Strings", "COMMAND_PCPOINT_WEBPOINT", "/pcpoint-webpoint", COMMAND_PCPOINT_WEBPOINT, sizeof(COMMAND_PCPOINT_WEBPOINT), IAJuliaChatCommands);
	GetPrivateProfileString("Strings", "COMMAND_ZEN_WCOIN", "/zen-wcoin", COMMAND_ZEN_WCOIN, sizeof(COMMAND_ZEN_WCOIN), IAJuliaChatCommands);
	GetPrivateProfileString("Strings", "COMMAND_ZEN_PCPOINT", "/zen-pcpoint", COMMAND_ZEN_PCPOINT, sizeof(COMMAND_ZEN_PCPOINT), IAJuliaChatCommands);
	GetPrivateProfileString("Strings", "COMMAND_ZEN_WEBPOINT", "/zen-webpoint", COMMAND_ZEN_WEBPOINT, sizeof(COMMAND_ZEN_WEBPOINT), IAJuliaChatCommands);
	GetPrivateProfileString("Strings", "COMMAND_GUILD_POST", "@>", COMMAND_GUILD_POST, sizeof(COMMAND_GUILD_POST), IAJuliaChatCommands); 
	GetPrivateProfileString("Strings", "COMMAND_OFFTRADE", "/offtrade", COMMAND_OFFTRADE, sizeof(COMMAND_OFFTRADE), IAJuliaChatCommands);
	GetPrivateProfileString("Strings", "COMMAND_RESET", "/reset", COMMAND_RESET, sizeof(COMMAND_RESET), IAJuliaChatCommands);
	GetPrivateProfileString("Strings", "COMMAND_EVO", "/evo", COMMAND_EVO, sizeof(COMMAND_EVO), IAJuliaChatCommands);
	GetPrivateProfileString("Strings", "COMMAND_ZEN", "/zen", COMMAND_ZEN, sizeof(COMMAND_ZEN), IAJuliaChatCommands);
	GetPrivateProfileString("Strings", "COMMAND_CLEAR", "/clear", COMMAND_CLEAR, sizeof(COMMAND_CLEAR), IAJuliaChatCommands);
	GetPrivateProfileString("Strings", "COMMAND_ISMARRY", "/ismarry", COMMAND_ISMARRY, sizeof(COMMAND_ISMARRY), IAJuliaChatCommands);
	GetPrivateProfileString("Strings", "COMMAND_MARRY_ONLINE", "/ismarry", COMMAND_MARRY_ONLINE, sizeof(COMMAND_MARRY_ONLINE), IAJuliaChatCommands);
	GetPrivateProfileString("Strings", "COMMAND_MARRY_TRACE", "/marrytrace", COMMAND_MARRY_TRACE, sizeof(COMMAND_MARRY_TRACE), IAJuliaChatCommands);
	GetPrivateProfileString("Strings", "COMMAND_DIVORCE", "/divorce", COMMAND_DIVORCE, sizeof(COMMAND_DIVORCE), IAJuliaChatCommands);
	GetPrivateProfileString("Strings", "COMMAND_YES", "/sim", COMMAND_YES, sizeof(COMMAND_YES), IAJuliaChatCommands);
	GetPrivateProfileString("Strings", "COMMAND_NO", "/nao", COMMAND_NO, sizeof(COMMAND_NO), IAJuliaChatCommands);
}

char Messages[1024];

void cChat::AntiInject(char* message)
{
	for(UINT i = 0; i <= strlen(message); i++)
	{
		if(message[i] == '\'')
		{
			message[i] = ' ';
		}
	}
}

bool cChat::WisperChat(LPOBJ gObj, PMSG_CHATDATA_WHISPER* lpMsg)
{
	/*
	gObj			- object struct of sender
	lpMsg->id		- nickname of receiver
	lpMsg->chatmsg	- msg
	*/

	AntiInject(lpMsg->chatmsg);

	char TempName[10];
	memcpy(TempName, lpMsg->id, sizeof(TempName));
	int Index = Utilits.GetPlayerIndex(TempName);

	if(!memcmp(lpMsg->chatmsg, COMMAND_AT, strlen(COMMAND_AT)) || !memcmp(lpMsg->chatmsg, "@@", strlen("@@")) || !memcmp(lpMsg->chatmsg, "~", strlen("~")))
	{
		PMSG_CHATDATA pMsg = {0};

		pMsg.h.set((LPBYTE)&pMsg, 0x00, sizeof(pMsg));
		memcpy(pMsg.chatid, lpMsg->id, sizeof(pMsg.chatid));
		memcpy(pMsg.chatmsg, lpMsg->chatmsg, sizeof(pMsg.chatmsg));

		PChatProc(&pMsg, gObj->m_Index);

		return true;
	}

	MuOnlineQuery.ExecQuery("SELECT BanChat FROM Character WHERE Name = '%s'", gObj->Name);
	MuOnlineQuery.Fetch();
	int BanChat = MuOnlineQuery.GetAsInteger("BanChat");
	MuOnlineQuery.Close();

	if(BanChat)
	{
		gObj->Penalty |= 2;
		Chat.MessageLog(1, c_Blue, t_BAN, gObj, "[BanChat] Seu chat foi banido!");

		return true;
	}
	else
	{
		gObj->Penalty &= ~2;
	}

	if (Index != -1)
	{
		PrivateLog(gObj, TempName, lpMsg, true);
	}
	else
	{
		PrivateLog(gObj, TempName, lpMsg, false);
	}

	return true;
}

bool cChat::ChatDataSend(LPOBJ gObj, PMSG_CHATDATA * lpChat)
{
	/*
	gObj			- Object Struct of sender
	lpMsg->id		- Id do sender
	lpMsg->chatmsg	- String recebida
	*/

	AntiInject(lpChat->chatmsg);

	bool bResult = false;

	if (!memcmp(lpChat->chatmsg, COMMAND_GG, strlen(COMMAND_GG)))
	{
		bResult = GgCommand(gObj, lpChat->chatmsg + strlen(COMMAND_GG));
	}

	if (!memcmp(lpChat->chatmsg, COMMAND_VOSKL, strlen(COMMAND_VOSKL)))
	{
		bResult = VosklCommand(gObj, lpChat->chatmsg + strlen(COMMAND_VOSKL));
	}

	if (!memcmp(lpChat->chatmsg, COMMAND_MOVE, strlen(COMMAND_MOVE)))
	{
		bResult = MoveCommand(gObj, lpChat->chatmsg + strlen(COMMAND_MOVE));
	}

	if (!memcmp(lpChat->chatmsg, COMMAND_WARP, strlen(COMMAND_WARP)))
	{
		bResult = MoveCommand(gObj, lpChat->chatmsg + strlen(COMMAND_WARP));
	}

	if (!memcmp(lpChat->chatmsg, COMMAND_LEVEL, strlen(COMMAND_LEVEL)))
	{
		bResult = LevelCommand(gObj);
	}

	if (!memcmp(lpChat->chatmsg, COMMAND_POST, strlen(COMMAND_POST)))
	{
		bResult = PostCommand(gObj, lpChat->chatmsg + strlen(COMMAND_POST));
	}

	if (!memcmp(lpChat->chatmsg, COMMAND_TIME, strlen(COMMAND_TIME)))
	{
		bResult = TimeCommand(gObj);
	}

	if (!memcmp(lpChat->chatmsg, COMMAND_SET_CHAR, strlen(COMMAND_SET_CHAR)))
	{
		bResult = SetCharCommand(gObj, lpChat->chatmsg + strlen(COMMAND_SET_CHAR), gObj->m_Index);
	}

	if (!memcmp(lpChat->chatmsg, COMMAND_SET_PK, strlen(COMMAND_SET_PK)))
	{
		bResult = SetPKCommand(gObj, lpChat->chatmsg + strlen(COMMAND_SET_PK), gObj->m_Index);
	}

	if (!memcmp(lpChat->chatmsg, COMMAND_SET_ZEN, strlen(COMMAND_SET_ZEN)))
	{
		bResult = SetZenCommand(gObj, lpChat->chatmsg + strlen(COMMAND_SET_ZEN), gObj->m_Index);
	}

	if (!memcmp(lpChat->chatmsg, COMMAND_CLEAR, strlen(COMMAND_CLEAR)))
	{
		bResult = ClearInvCommand(gObj);
	}

	if (!memcmp(lpChat->chatmsg, COMMAND_SKIN, strlen(COMMAND_SKIN)))
	{
		bResult = SkinCommand(gObj, lpChat->chatmsg + strlen(COMMAND_SKIN), gObj->m_Index);
	}

	if (!memcmp(lpChat->chatmsg, COMMAND_DROP, strlen(COMMAND_DROP)))
	{
		bResult = DropCommand(gObj, lpChat->chatmsg + strlen(COMMAND_DROP), gObj->m_Index);
	}

	if (!memcmp(lpChat->chatmsg, COMMAND_GMOVE, strlen(COMMAND_GMOVE)))
	{
		bResult = GmoveCommand(gObj, lpChat->chatmsg + strlen(COMMAND_GMOVE), gObj->m_Index);
	}

	if (!memcmp(lpChat->chatmsg, COMMAND_ONLINE, strlen(COMMAND_ONLINE)))
	{
		bResult = OnlineCommand(gObj, lpChat->chatmsg + strlen(COMMAND_ONLINE));
	}

	if (!memcmp(lpChat->chatmsg, COMMAND_RELOAD, strlen(COMMAND_RELOAD)))
	{
		bResult = ReloadCommand(gObj, lpChat->chatmsg + strlen(COMMAND_RELOAD));
	}

	if (!memcmp(lpChat->chatmsg, COMMAND_PKCLEAR, strlen(COMMAND_PKCLEAR)))
	{
		bResult = PKClearCommand(gObj, lpChat->chatmsg + strlen(COMMAND_PKCLEAR), gObj->m_Index);
	}

	if (!memcmp(lpChat->chatmsg, COMMAND_ADD_STR, strlen(COMMAND_ADD_STR)))
	{
		bResult = AddCommands(gObj, lpChat->chatmsg + strlen(COMMAND_ADD_STR), 0);
	}

	if (!memcmp(lpChat->chatmsg, COMMAND_ADD_AGI, strlen(COMMAND_ADD_AGI)))
	{
		bResult = AddCommands(gObj, lpChat->chatmsg + strlen(COMMAND_ADD_AGI), 1);
	}

	if (!memcmp(lpChat->chatmsg, COMMAND_ADD_VIT, strlen(COMMAND_ADD_VIT)))
	{
		bResult = AddCommands(gObj, lpChat->chatmsg + strlen(COMMAND_ADD_VIT), 2);
	}

	if (!memcmp(lpChat->chatmsg, COMMAND_ADD_ENE, strlen(COMMAND_ADD_ENE)))
	{
		bResult = AddCommands(gObj, lpChat->chatmsg + strlen(COMMAND_ADD_ENE), 3);
	}

	if (!memcmp(lpChat->chatmsg, COMMAND_ADD_CMD, strlen(COMMAND_ADD_CMD)))
	{
		bResult = AddCommands(gObj, lpChat->chatmsg + strlen(COMMAND_ADD_CMD), 4);
	}

	if (!memcmp(lpChat->chatmsg, COMMAND_WARE, strlen(COMMAND_WARE)))
	{
		bResult = WareCommand(gObj, lpChat->chatmsg + strlen(COMMAND_WARE));
	}

	if (!memcmp(lpChat->chatmsg, COMMAND_MOBADD, strlen(COMMAND_MOBADD)))
	{
		bResult = AddMobCommand(gObj, lpChat->chatmsg + strlen(COMMAND_MOBADD));
	}

	if (!memcmp(lpChat->chatmsg, COMMAND_SETDROP, strlen(COMMAND_SETDROP)))
	{
		bResult = SetDropCommand(gObj, lpChat->chatmsg + strlen(COMMAND_SETDROP), gObj->m_Index);
	}

	if (!memcmp(lpChat->chatmsg, COMMAND_CHECK, strlen(COMMAND_CHECK)))
	{
		bResult = CheckCommand(gObj, lpChat->chatmsg + strlen(COMMAND_CHECK));
	}

	if (!memcmp(lpChat->chatmsg, COMMAND_VIPBUY, strlen(COMMAND_VIPBUY)))
	{
		bResult = BuyVIPCommand(gObj, lpChat->chatmsg + strlen(COMMAND_VIPBUY));
	}

	if (!memcmp(lpChat->chatmsg, COMMAND_VIPCHECK, strlen(COMMAND_VIPCHECK)))
	{
		bResult = CheckVIPCommand(gObj, lpChat->chatmsg + strlen(COMMAND_VIPCHECK));
	}

	if (!memcmp(lpChat->chatmsg, COMMAND_VIPLIST, strlen(COMMAND_VIPLIST)))
	{
		bResult = VIPListCommand(gObj, lpChat->chatmsg + strlen(COMMAND_VIPLIST));
	}

	if (!memcmp(lpChat->chatmsg, COMMAND_TERRCHECK, strlen(COMMAND_TERRCHECK)))
	{
		bResult = CheckTerritoryCommand(gObj, lpChat->chatmsg + strlen(COMMAND_TERRCHECK));
	}

	if (!memcmp(lpChat->chatmsg, COMMAND_TERRBUY, strlen(COMMAND_TERRBUY)))
	{
		bResult = BuyTerritoryCommand(gObj, lpChat->chatmsg + strlen(COMMAND_TERRBUY));
	}

	if (!memcmp(lpChat->chatmsg, COMMAND_VIP_ON, strlen(COMMAND_VIP_ON)))
	{
		bResult = VipOnCommand(gObj);
	}

	if (!memcmp(lpChat->chatmsg, COMMAND_VIP_OFF, strlen(COMMAND_VIP_OFF)))
	{
		bResult = VipOffCommand(gObj);
	}

	if (!memcmp(lpChat->chatmsg, COMMAND_WCOIN_PCOINT, strlen(COMMAND_WCOIN_PCOINT)))
	{
		bResult = ExchangeCommands(gObj, (char*)lpChat->chatmsg + strlen(COMMAND_WCOIN_PCOINT), 1);
	}

	if (!memcmp(lpChat->chatmsg, COMMAND_WCOIN_WEBPOINT, strlen(COMMAND_WCOIN_WEBPOINT)))
	{
		bResult = ExchangeCommands(gObj, (char*)lpChat->chatmsg + strlen(COMMAND_WCOIN_WEBPOINT), 2);
	}

	if (!memcmp(lpChat->chatmsg, COMMAND_WCOIN_ZEN, strlen(COMMAND_WCOIN_ZEN)))
	{
		bResult = ExchangeCommands(gObj, (char*)lpChat->chatmsg + strlen(COMMAND_WCOIN_ZEN), 3);
	}

	if (!memcmp(lpChat->chatmsg, COMMAND_WEBPOINT_WCOIN, strlen(COMMAND_WEBPOINT_WCOIN)))
	{
		bResult = ExchangeCommands(gObj, (char*)lpChat->chatmsg + strlen(COMMAND_WEBPOINT_WCOIN), 4);
	}

	if (!memcmp(lpChat->chatmsg, COMMAND_WEBPOINT_PCPOINT, strlen(COMMAND_WEBPOINT_PCPOINT)))
	{
		bResult = ExchangeCommands(gObj, (char*)lpChat->chatmsg + strlen(COMMAND_WEBPOINT_PCPOINT), 5);
	}

	if (!memcmp(lpChat->chatmsg, COMMAND_WEBPOINT_ZEN, strlen(COMMAND_WEBPOINT_ZEN)))
	{
		bResult = ExchangeCommands(gObj, (char*)lpChat->chatmsg + strlen(COMMAND_WEBPOINT_ZEN), 6);
	}

	if (!memcmp(lpChat->chatmsg, COMMAND_PCPOINT_ZEN, strlen(COMMAND_PCPOINT_ZEN)))
	{
		bResult = ExchangeCommands(gObj, (char*)lpChat->chatmsg + strlen(COMMAND_PCPOINT_ZEN), 7);
	}

	if (!memcmp(lpChat->chatmsg, COMMAND_PCPOINT_WCOIN, strlen(COMMAND_PCPOINT_WCOIN)))
	{
		bResult = ExchangeCommands(gObj, (char*)lpChat->chatmsg + strlen(COMMAND_PCPOINT_WCOIN), 8);
	}

	if (!memcmp(lpChat->chatmsg, COMMAND_PCPOINT_WEBPOINT, strlen(COMMAND_PCPOINT_WEBPOINT)))
	{
		bResult = ExchangeCommands(gObj, (char*)lpChat->chatmsg + strlen(COMMAND_PCPOINT_WEBPOINT), 9);
	}

	if (!memcmp(lpChat->chatmsg, COMMAND_ZEN_WCOIN, strlen(COMMAND_ZEN_WCOIN)))
	{
		bResult = ExchangeCommands(gObj, (char*)lpChat->chatmsg + strlen(COMMAND_ZEN_WCOIN), 10);
	}

	if (!memcmp(lpChat->chatmsg, COMMAND_ZEN_PCPOINT, strlen(COMMAND_ZEN_PCPOINT)))
	{
		bResult = ExchangeCommands(gObj, (char*)lpChat->chatmsg + strlen(COMMAND_ZEN_PCPOINT), 11);
	}

	if (!memcmp(lpChat->chatmsg, COMMAND_ZEN_WEBPOINT, strlen(COMMAND_ZEN_WEBPOINT)))
	{
		bResult = ExchangeCommands(gObj, (char*)lpChat->chatmsg + strlen(COMMAND_ZEN_WEBPOINT), 12);
	}

	if (!memcmp(lpChat->chatmsg, COMMAND_GUILD_POST, strlen(COMMAND_GUILD_POST)))
	{
		bResult = GuildPost(gObj, lpChat->chatmsg + strlen(COMMAND_GUILD_POST));
	}

	if (!memcmp(lpChat->chatmsg, COMMAND_OFFTRADE, strlen(COMMAND_OFFTRADE)))
	{
		bResult = OffTradeCommand(gObj);
	}

	if(!memcmp(lpChat->chatmsg, COMMAND_RESET, strlen(COMMAND_RESET)))
	{
		bResult = ResetCommand(gObj);
	}

	if(!memcmp(lpChat->chatmsg, COMMAND_EVO, strlen(COMMAND_EVO)))
	{
		bResult = EvoCommand(gObj);
	}

	if(!memcmp(lpChat->chatmsg, COMMAND_ZEN, strlen(COMMAND_ZEN)))
	{
		bResult = ZenCommand(gObj,lpChat->chatmsg + strlen(COMMAND_ZEN));
	}

	/*
	if (!memcmp(lpChat->chatmsg, COMMAND_SET_ZEN, strlen(COMMAND_SET_ZEN)))
	{
	bResult = SetZenCommand(gObj, lpChat->chatmsg + strlen(COMMAND_SET_ZEN), gObj->m_Index);
	}
	*/

	if (!memcmp(lpChat->chatmsg, COMMAND_ISMARRY, strlen(COMMAND_ISMARRY)))
	{
		bResult = IsMarryCommand(gObj, lpChat->chatmsg + strlen(COMMAND_ISMARRY));
	}

	if (!memcmp(lpChat->chatmsg, COMMAND_MARRY_ONLINE, strlen(COMMAND_MARRY_ONLINE)))
	{
		bResult = MarryOnlineCommand(gObj);
	}

	if (!memcmp(lpChat->chatmsg, COMMAND_MARRY_TRACE, strlen(COMMAND_MARRY_TRACE)))
	{
		bResult = MarryTraceCommand(gObj);
	}

	if (!memcmp(lpChat->chatmsg, COMMAND_DIVORCE, strlen(COMMAND_DIVORCE)))
	{
		bResult = MarryDivorce(gObj);
	}

	if (!memcmp(lpChat->chatmsg, COMMAND_YES, strlen(COMMAND_YES)))
	{
		bResult = YesCommand(gObj);
	}

	if (!memcmp(lpChat->chatmsg, COMMAND_NO, strlen(COMMAND_NO)))
	{
		bResult = NoCommand(gObj);
	}

	MuOnlineQuery.ExecQuery("SELECT BanChat FROM Character WHERE Name = '%s'", gObj->Name);
	MuOnlineQuery.Fetch();
	int BanChat = MuOnlineQuery.GetAsInteger("BanChat");
	MuOnlineQuery.Close();

	if (BanChat)
	{
		gObj->Penalty |= 2;
		Chat.MessageLog(1, c_Blue, t_BAN, gObj, "[BanChat] Your chat is banned!");

		return true;
	}
	else
	{
		gObj->Penalty &= ~2;
	}

	MassLog(gObj, lpChat->chatmsg);

	return bResult;
}

void cChat::MsgSrv(LPOBJ gObj, char *Message, int Type)
{
	if (gObj != nullptr)
	{
		BYTE *Packet = (BYTE*)malloc(200);

		if (Packet != nullptr)
		{
			memset(Packet,0x00,200);
			*Packet = 0xC1;

			if (Type)
			{
				*(Packet + 2) = 0x02;
			}
			else
			{
				*(Packet + 2) = 0x00;
			}

			memcpy((Packet + 3), gObj->Name, strlen(gObj->Name));
			memcpy((Packet + 13), Message, strlen(Message));
			int Len = (strlen(Message) + 0x13);
			*(Packet + 1) = Len;
			DataSendAll(Packet, Len);
			free(Packet);
		}
	}
}

void cChat::PrivateLog(LPOBJ gObj, char *Name, PMSG_CHATDATA_WHISPER* lpMsg, bool Success)
{
	SYSTEMTIME t;
	GetLocalTime(&t);
	char currdate[11] = {0};
	sprintf(currdate, "%02d:%02d:%02d", t.wHour, t.wMinute, t.wSecond);

	char Msg[512] = { 0 };;
	char Suc;

	if (Success)
	{
		Suc = '>';
	}
	else
	{
		Suc = 'X';
	}

	sprintf(Msg, "[%10s] [%10s -%c %10s]:\t%59s\n", currdate, gObj->Name, Suc, Name, lpMsg->chatmsg);
	Log.ConsoleOutPut(1, c_Green, t_COMMANDS, "[Private] [%s -%c %s]: %s", gObj->Name, Suc, Name, lpMsg->chatmsg);

	char Date[55];
	sprintf(Date, "..\\IA Julia\\ChatLogs\\%02d-%02d-%02d\\", t.wDay, t.wMonth, t.wYear);
	CreateDirectory(Date, NULL);

	char ChatLog[55];
	sprintf(ChatLog, "..\\IA Julia\\ChatLogs\\%02d-%02d-%02d\\PrivateChatLogs.log", t.wDay, t.wMonth, t.wYear);
	Log.SaveFile(ChatLog, Msg);
}

void cChat::MassLog(LPOBJ gObj, char* Message)
{
	char Type[20];
	char Msg2[512];

	if (!memcmp(Message, "@@", strlen("@@")))
	{
		strcpy(Type, "Guild Aliance");
		strcpy(Msg2, Message + strlen("@@"));
	}
	else if (!memcmp(Message, COMMAND_AT, strlen(COMMAND_AT)))
	{
		strcpy(Type, "Guild");
		strcpy(Msg2, Message + strlen(COMMAND_AT));
	}
	else if (!memcmp(Message, COMMAND_POST, strlen(COMMAND_POST)))
	{
		strcpy(Type, "Post");
		strcpy(Msg2, Message + strlen(COMMAND_POST));
	}
	else if (!memcmp(Message, "~", strlen("~")))
	{
		strcpy(Type, "Party");
		strcpy(Msg2, Message + strlen("~"));
	}
	else if (!memcmp(Message, COMMAND_MOVE, strlen(COMMAND_MOVE)))
	{
		strcpy(Type, "Move");
		strcpy(Msg2, Message + strlen(COMMAND_MOVE));
	}
	else if (!memcmp(Message, COMMAND_WARP, strlen(COMMAND_WARP)))
	{
		strcpy(Type, "Move");
		strcpy(Msg2, Message + strlen(COMMAND_WARP));
	}
	else
	{
		strcpy(Type, "Chat");
		strcpy(Msg2, Message);
	}

	SYSTEMTIME t;
	GetLocalTime(&t);
	char currdate[11] = { 0 };
	sprintf(currdate, "%02d:%02d:%02d", t.wHour, t.wMinute, t.wSecond);
	char Msg[564];
	sprintf(Msg, "[%s] [%s:%s] [%s]\t%s\n", currdate, gObj->AccountID, gObj->Name, Type, Msg2);

	char Date[55];
	sprintf(Date, "..\\IA Julia\\ChatLogs\\%02d-%02d-%02d\\", t.wDay, t.wMonth, t.wYear);
	CreateDirectory(Date, NULL);

	char ChatLog[55];
	sprintf(ChatLog, "..\\IA Julia\\ChatLogs\\%02d-%02d-%02d\\ChatLogs.log", t.wDay, t.wMonth, t.wYear);
	Log.SaveFile(ChatLog, Msg);
}

void cChat::MessageLog(int Type, sColor LogColor, sLogType LogType, LPOBJ gObj, char *Msg, ...)
{
	Messages[0] = 0;
	char Temp[255];

	strcpy(Temp,Msg);
	va_list pArguments1;
	va_start(pArguments1, Msg);
	vsprintf_s(Messages, Temp, pArguments1);
	va_end(pArguments1);
	GCServerMsgStringSend(Messages, gObj->m_Index, Type);

	// Type = 1 - Mensagems em bloco
	// Type = 0 - Dourado

	if (Type)
	{
		Log.ConsoleOutPut(1, LogColor, LogType, "[%s:%s]: %s", gObj->AccountID, gObj->Name, Messages);
	}
	else
	{
		Log.ConsoleOutPut(1, LogColor, LogType, "[GoldMessage] %s", Messages);
	}
}

void cChat::Message(int Type, LPOBJ gObj, char *Msg, ...)
{
	Messages[0] = 0;
	char Temp[255];

	strcpy(Temp,Msg);
	va_list pArguments1;
	va_start(pArguments1, Msg);
	vsprintf_s(Messages, Temp, pArguments1);
	va_end(pArguments1);
	GCServerMsgStringSend(Messages, gObj->m_Index, Type);

	// Type = 1 - Mensagems em bloco
	// Type = 0 - Dourado
}

void cChat::MessageAllLog(int Type, int Type2, sColor LogColor, sLogType LogType, LPOBJ gObj, char *Msg, ...)
{
	Messages[0] = 0;
	char Temp[255];

	strcpy(Temp,Msg);
	va_list pArguments1;
	va_start(pArguments1, Msg);
	vsprintf_s(Messages, Temp, pArguments1);
	va_end(pArguments1);

	if(Type == 2)
	{
		MsgSrv(gObj, Messages, Type2);
	}
	else
	{
		for (int i = OBJECT_MIN; i <= OBJECT_MAX; i++)
		{
			OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(i);

			if (gObj->Connected < PLAYER_PLAYING)
			{
				continue;
			}

			GCServerMsgStringSend(Messages, i, Type);
		}
	}

	if (Type)
	{
		Log.ConsoleOutPut(1, LogColor, LogType, "[%s:%s]: %s", gObj->AccountID, gObj->Name, Messages);
	}
	else
	{
		Log.ConsoleOutPut(1, LogColor, LogType, "[%s:%s][GoldMessage] %s", gObj->AccountID, gObj->Name, Messages);
	}
}

void cChat::MessageAll(int Type, int Type2, LPOBJ gObj, char *Msg, ...)
{
	Messages[0] = 0;
	char Temp[255];

	strcpy(Temp,Msg);
	va_list pArguments1;
	va_start(pArguments1, Msg);
	vsprintf_s(Messages, Temp, pArguments1);
	va_end(pArguments1);

	if (Type == 2)
	{
		MsgSrv(gObj, Messages, Type2);
	}
	else
	{
		for (int i = OBJECT_MIN; i <= OBJECT_MAX; i++)
		{
			OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(i);
			if (gObj->Connected < PLAYER_PLAYING)	continue;
			GCServerMsgStringSend(Messages, i, Type);
		}
	}
}

bool cChat::CheckCommand
(
	LPOBJ gObj,
	int lConfig,
	cGmSystem::Commands Command,
	int NeedZen,
	int NeedPcPoint,
	int NeedWCoin,
	int NeedWebPoints,
	int NeedLvl,
	int Filled,
	int CheckPlayer,
	char *CommandName,
	char *CommandUsage, char *Msg
)
{
	bool bResult = false;

	int spaces = 0;
	const unsigned int slen = strlen(Msg);

	for(unsigned int i = 0; i < slen;i++)
	{
		if((Msg[i] == ' ') && (Msg[i - 1] != ' '))
		{
			spaces++;
		}
	}

	if(lConfig == 0)
	{
		MessageLog(1, c_Red, t_COMMANDS, gObj, "[%s] Funcao inativa.", CommandName);

		return true;
	}

	if (!GmSystem.IsCommand(Command, gObj->Name))
	{
		MessageLog(1, c_Red, t_COMMANDS, gObj, "[%s] Voce nao pode usar esse comando.", CommandName);

		return true;
	}

	if((Filled > 0) && ((Filled > spaces) || (((slen < 1) || (slen == 1)) && (Msg[0] == ' '))))
	{
		MessageLog(1, c_Red, t_COMMANDS, gObj, "[%s] Uso: %s", CommandName, CommandUsage);

		return true;
	}

	if (NeedLvl > 0 && gObj->Level < NeedLvl)
	{
		MessageLog(1, c_Red, t_COMMANDS, gObj, "[%s] Voce nao possui level suficiente.", CommandName);

		bResult = true;
	}

	if (NeedZen > 0 && NeedZen > gObj->Money)
	{
		MessageLog(1, c_Red, t_COMMANDS, gObj, "[%s] Voce nao possui zen suficiente.", CommandName);

		bResult = true;
	}

	if (PCPoint.Config.Enabled && NeedPcPoint > 0 && NeedPcPoint > AddTab[gObj->m_Index].PC_PlayerPoints)
	{
		MessageLog(1, c_Red, t_COMMANDS, gObj, "[%s] Voce precisa de mais %d PcPoints.", CommandName, NeedPcPoint - AddTab[gObj->m_Index].PC_PlayerPoints);

		bResult = true;
	}

	if (PCPoint.Config.Enabled && NeedWCoin > 0 && NeedWCoin > gObj->m_wCashPoint)
	{
		MessageLog(1, c_Red, t_COMMANDS, gObj, "[%s] Voce precisa de mais %d WCoins.", CommandName, NeedWCoin - gObj->m_wCashPoint);

		bResult = true;
	}

	if (PCPoint.Config.WebEnabled && NeedWebPoints > 0)
	{
		if(PCPoint.Config.WebColumnFloat && (NeedWebPoints > AddTab[gObj->m_Index].WEB_Points_Float))
		{
			MessageLog(1, c_Red, t_COMMANDS, gObj, "[%s] Voce precisa de mais %.2f WebPoints.", CommandName,NeedWebPoints - AddTab[gObj->m_Index].WEB_Points_Float);

			bResult = true;
		}

		if (!PCPoint.Config.WebColumnFloat && (NeedWebPoints > AddTab[gObj->m_Index].WEB_Points))
		{
			MessageLog(1, c_Red, t_COMMANDS, gObj, "[%s] Voce precisa de mais %d WebPoints.", CommandName,NeedWebPoints - AddTab[gObj->m_Index].WEB_Points);

			bResult = true;
		}
	}

	if(CheckPlayer != 0)
	{
		if(CheckPlayer == -1)
		{
			MessageLog(1, c_Red, t_COMMANDS, gObj, "[%s] Player nao encontrado!", CommandName);

			bResult = true;
		}
	}

	return bResult;
}

void cChat::TakeCommand(LPOBJ gObj, int NeedZen, int NeedPcPoint, int NeedWCoin, int NeedWebPoints, char *CommandName)
{
	if (NeedZen > 0)
	{
		gObj->Money -= NeedZen;
		GCMoneySend(gObj->m_Index, gObj->Money);
	}

	if (PCPoint.Config.Enabled && NeedPcPoint > 0)
	{
		PCPoint.UpdatePoints(gObj, NeedPcPoint, MINUS, PCPOINT);
		Chat.MessageLog(1, c_Blue, t_PCPOINT, gObj, "[%s] Voce pagou %d PcPoints", CommandName, NeedPcPoint);
	}

	if (PCPoint.Config.Enabled && NeedWCoin > 0)
	{
		PCPoint.UpdatePoints(gObj, NeedWCoin, MINUS, WCOIN);
		Chat.MessageLog(1, c_Blue, t_PCPOINT, gObj, "[%s] Voce pagou %d WCoin", CommandName, NeedWCoin);
	}

	if(PCPoint.Config.WebEnabled && NeedWebPoints > 0)
	{
		PCPoint.UpdatePoints(gObj, NeedWebPoints, MINUS, WEBPOINTS);

		Chat.MessageLog(1,c_Blue,t_PCPOINT,gObj,"[%s] Voce pagou %df WebPoints",CommandName,NeedWebPoints);
	}
}

bool cChat::GgCommand(LPOBJ gObj, char *Msg)
{
	if (CheckCommand(gObj, Configs.Commands.IsGg, GmSystem.cGg, 0, 0, 0, 0, 0, 1, 0, "GG", "/gg <msg>", Msg))
	{
		return true;
	}

	Log.CheckProcent(Msg);
	MessageAll(0, 0, gObj, "[%s]: %s", gObj->Name,Msg); // Protejer aqui seria bom :D

	Log.ConsoleOutPut(0, c_Green, t_GM, "[GG] %s: %s", gObj->Name, Msg);

	return true;
}

bool cChat::VosklCommand(LPOBJ gObj, char *Msg)
{
	if (CheckCommand(gObj, 1, GmSystem.cVoskl, 0, 0, 0, 0, 0, 1, 0, COMMAND_VOSKL, "! <msg>", Msg))
	{
		return true;
	}

	Log.CheckProcent(Msg);
	MessageAll(0, 0, gObj, Msg); // Protejer aqui seria bom :D

	Log.ConsoleOutPut(0, c_Green, t_GM, "[!] %s: %s", gObj->Name, Msg);

	return true;
}

bool cChat::TraceCommand(LPOBJ gObj, int Index)
{
	if (CheckCommand(gObj, 1, GmSystem.cTrace, 0, 0, 0, 0, 0, 0, Index, "Trace", "[Name] /trace", ""))
	{
		return true;
	}

	OBJECTSTRUCT *tObj = (OBJECTSTRUCT*)OBJECT_POINTER(Index);

	gObjTeleport(gObj->m_Index, tObj->MapNumber, (int)tObj->X, (int)tObj->Y);
	MessageLog(1, c_Green, t_GM, gObj, "[Trace] You successfully traced to %s", tObj->Name);

	if (GmSystem.IsAdmin(gObj->Name) == 1)
	{
		MessageLog(1, c_Green, t_GM, tObj, "[Trace] [Admin] %s traced to you", gObj->Name);
	}
	else if (GmSystem.IsAdmin(gObj->Name) == 2)
	{
		MessageLog(1, c_Green, t_GM, tObj, "[Trace] [GM] %s traced to you", gObj->Name);
	}

	return true;
}

bool cChat::SummonCommand(LPOBJ gObj, int Index)
{
	if (CheckCommand(gObj, 1, GmSystem.cTrace, 0, 0, 0, 0, 0, 0, Index, "Track", "[Name] /track", ""))
	{
		return true;
	}

	OBJECTSTRUCT *tObj = (OBJECTSTRUCT*)OBJECT_POINTER(Index);

	gObjTeleport(tObj->m_Index, gObj->MapNumber, (int)gObj->X, (int)gObj->Y);
	MessageLog(1, c_Green, t_GM, gObj, "[Track] You successfully summoned %s", tObj->Name);

	if (GmSystem.IsAdmin(gObj->Name) == 1)
	{
		MessageLog(1, c_Green, t_GM, tObj, "[Track] You was summoned to [Admin] %s", gObj->Name);
	}
	else if (GmSystem.IsAdmin(gObj->Name) == 2)
	{
		MessageLog(1, c_Green, t_GM, tObj, "[Track] You was summoned to [GM] %s", gObj->Name);
	}

	return true;
}

bool cChat::DiskCommand(LPOBJ gObj, int Index)
{
	if (CheckCommand(gObj, 1, GmSystem.cDisconnect, 0, 0, 0, 0, 0, 0, Index, "DC", "[Name] /disconnect", ""))
	{
		return true;
	}

	OBJECTSTRUCT *tObj = (OBJECTSTRUCT*)OBJECT_POINTER(Index);
	MessageLog(1, c_Green, t_GM, gObj, "[Disconnect] %s foi desconectado.", tObj->Name);

	if(GmSystem.IsAdmin(gObj->Name) == 1)
	{
		MessageLog(1, c_Green, t_GM, tObj, "[Disconnect] Voce foi desconectado por [Admin] %s", gObj->Name);
	}
	else if(GmSystem.IsAdmin(gObj->Name) == 2)
	{
		MessageLog(1, c_Green, t_GM, tObj, "[Disconnect] Voce foi desconectado por [GM] %s", gObj->Name);
	}

	CloseClient(Index);

	return true;
}

bool cChat::MoveCommand(LPOBJ gObj, char *Msg)
{
	char MapName[50] = {0};
	sscanf(Msg, "%49s", MapName);

	int Index = -1;

	for (int i = 0; i <= MoveReq.Count; i++)
	{
		if (!_strcmpi(MapName, MoveReq.MoveReqInfo[i].MapName1) || !_strcmpi(MapName, MoveReq.MoveReqInfo[i].MapName2))
		{
			Index = i;

			break;
		}
	}

	if (Index != -1)
	{
		DWORD CurrentZen;
		CurrentZen = (DWORD)gObj->Money;

		if (CurrentZen < (DWORD)MoveReq.MoveReqInfo[Index].Zen)
		{
			return true;
		}

		DWORD ZenDec = CurrentZen - (DWORD)MoveReq.MoveReqInfo[Index].Zen;

		if (!strcmp(MoveReq.MoveReqInfo[Index].MapName1, "Atlans"))
		{
			if (gObj->pInventory[8].m_Type == ITEMGET(13, 2) || gObj->pInventory[8].m_Type == ITEMGET(13, 3))
			{
				MessageLog(1, c_Red, t_COMMANDS, gObj, "[Move] Impossivel ir a Atlans com esse Pet.");

				return true;
			}
		}

		if(gObj->m_PK_Level >= 5)
		{
			MessageLog(1, c_Red, t_COMMANDS, gObj, "[Move] Fonomans nao podem se mover.");

			return true;
		}

		if (!GmSystem.IsAdmin(gObj->Name))
		{
			if (AddTab[gObj->m_Index].VIP_Type < MoveReq.MoveReqInfo[Index].VIP)
			{
				MessageLog(1, c_Red, t_COMMANDS, gObj, "[Move] Esse mapa e somente para VIPs.");

				return true;
			}

			if (!AddTab[gObj->m_Index].VIP_On && MoveReq.MoveReqInfo[Index].VIP)
			{
				MessageLog(1, c_Red, t_COMMANDS, gObj, "[Move] Ative seu VIP e tente novamente.");

				return true;
			}
		}

		int TempLvl = MoveReq.MoveReqInfo[Index].Level;

		if (gObj->Class == 4 || gObj->Class == 3)
		{
			if (gObj->Level < TempLvl - ceil(TempLvl / 100.0f * 34))
			{
				MessageLog(1, c_Red, t_COMMANDS, gObj, "[Move] Level insuficiente!");
				return true;
			}
		}
		else
		{
			if(gObj->Level < TempLvl)
			{
				MessageLog(1, c_Red, t_COMMANDS, gObj, "[Move] Level insuficiente!");
				return true;
			}
		}

		gObj->Money = ZenDec;
		GCMoneySend(gObj->m_Index, ZenDec);
		gObjMoveGate(gObj->m_Index, MoveReq.MoveReqInfo[Index].Gate);

		return true;
	}
	else
	{
		MessageLog(1, c_Red, t_COMMANDS, gObj, "[Move] Esse mapa nao existe.");

		return true;
	}
}

bool cChat::PostCommand(LPOBJ gObj, char *Msg)
{
	if (CheckCommand(gObj, Configs.Commands.IsPost, GmSystem.NONE, Configs.Commands.PostPriceZen, Configs.Commands.PostPricePCPoint, Configs.Commands.PostPriceWCoin, Configs.Commands.PostPriceWebPoint, Configs.Commands.PostLvl, 1, 0, "Post", "/post <msg>", Msg))
	{
		return true;
	}

	MuOnlineQuery.ExecQuery("SELECT BanPost, BanChat FROM Character WHERE Name = '%s'", gObj->Name);
	MuOnlineQuery.Fetch();

	int Banned = MuOnlineQuery.GetAsInteger("BanPost");
	int BanChat = MuOnlineQuery.GetAsInteger("BanChat");

	MuOnlineQuery.Close();

	if(BanChat)
	{
		MessageLog(1, c_Red, t_COMMANDS, gObj, "[BanChat] Seu chat foi banido!");

		return true;
	}

	if(Banned > 0)
	{
		MessageLog(1, c_Red, t_COMMANDS, gObj, "[ANTI-FLOOD] Seu post foi banido!");

		return true;
	}

	time_t Seconds = time(NULL);

	if(Seconds - Configs.Commands.PostDelay < AddTab[gObj->m_Index].POST_Delay)
	{
		MessageLog(1, c_Red, t_COMMANDS, gObj, "[ANTI-FLOOD] Aguarde %lds para re-postar.",Configs.Commands.PostDelay - (Seconds - AddTab[gObj->m_Index].POST_Delay));

		return true;
	}

	if(!GmSystem.IsAdmin(gObj->Name))
	{
		AddTab[gObj->m_Index].POST_Delay = Seconds;
	}

	TakeCommand(gObj, Configs.Commands.PostPriceZen, Configs.Commands.PostPricePCPoint, Configs.Commands.PostPriceWCoin, Configs.Commands.PostPriceWebPoint, "Post");

	switch (Configs.Commands.PostColor)
	{
		case 0: case 1:
		{
			MessageAll(2, 1, gObj, "[POST] %s", Msg);

			break;
		}
		case 2:
		{
			MessageAll(2, 0, gObj, "@[POST] %s", Msg);

			break;
		}
		case 3:
		{
			MessageAll(2, 0, gObj, "~[POST] %s", Msg);

			break;
		}
	}

	Log.ConsoleOutPut(0, c_Green, t_POST, "[POST] %s: %s", gObj->Name, Msg);

	return true;
}

bool cChat::BanPostCommand(LPOBJ gObj, char *Msg, int Index)
{
	if (CheckCommand(gObj, Configs.Commands.IsBanPost, GmSystem.cBanPost, 0, 0, 0, 0, 0, 0, Index, "BanPost", "[Name] /banpost", ""))
	{
		return true;
	}

	OBJECTSTRUCT *tObj = (OBJECTSTRUCT*)OBJECT_POINTER(Index);

	MuOnlineQuery.ExecQuery("SELECT BanPost FROM Character WHERE Name = '%s'", tObj->Name);
	MuOnlineQuery.Fetch();
	int Banned = MuOnlineQuery.GetAsInteger("BanPost");
	MuOnlineQuery.Close();

	if (Banned)
	{
		MessageLog(1, c_Red, t_BAN, gObj, "[BanPost] %s Already Banned", tObj->Name);
	}
	else
	{
		MuOnlineQuery.ExecQuery("UPDATE Character SET BanPost = 1 WHERE Name = '%s'", tObj->Name);
		MuOnlineQuery.Fetch();
		MuOnlineQuery.Close();

		MessageLog(1, c_Red, t_BAN, gObj, "[BanPost] %s post banned.", tObj->Name);
		MessageLog(1, c_Red, t_BAN, tObj, "[BanPost] Your post was banned by %s.", gObj->Name);
	}

	return true;
}

bool cChat::UnBanPostCommand(LPOBJ gObj, int Index)
{
	if (CheckCommand(gObj, Configs.Commands.IsBanPost, GmSystem.cBanPost, 0, 0, 0, 0, 0, 0, Index, "UnBanPost", "[Name] /unbanpost", ""))
	{
		return true;
	}

	OBJECTSTRUCT *tObj = (OBJECTSTRUCT*)OBJECT_POINTER(Index);

	MuOnlineQuery.ExecQuery("SELECT BanPost FROM Character WHERE Name = '%s'", tObj->Name);
	MuOnlineQuery.Fetch();
	int Banned = MuOnlineQuery.GetAsInteger("BanPost");
	MuOnlineQuery.Close();

	if (Banned == 0)
	{
		MessageLog(1, c_Red, t_BAN, gObj, "[BanPost] %s's post is not banned", tObj->Name);

		return true;
	}
	else
	{
		MessageLog(1, c_Red, t_BAN, gObj, "[BanPost] %s's post sucsessfuly UnBanned!", tObj->Name);
		MessageLog(1, c_Red, t_BAN, tObj, "[BanPost] Your post sucsessfuly UnBanned by %s!", gObj->Name);
	}

	MuOnlineQuery.ExecQuery("UPDATE Character SET BanPost = 0 WHERE Name = '%s'", tObj->Name);
	MuOnlineQuery.Fetch();
	MuOnlineQuery.Close();

	return true;
}

bool cChat::BanCharCommand(LPOBJ gObj, char *Msg, int Index)
{
	if (CheckCommand(gObj, Configs.Commands.IsBanChar, GmSystem.cBanPlayer, 0, 0, 0, 0, 0, 0, Index, "BanChar", "[Name] /banchar", ""))
		return true;

	OBJECTSTRUCT *tObj = (OBJECTSTRUCT*)OBJECT_POINTER(Index);

	MuOnlineQuery.ExecQuery("SELECT CtlCode FROM Character WHERE Name = '%s'", tObj->Name);
	MuOnlineQuery.Fetch();
	int Banned = MuOnlineQuery.GetAsInteger("CtlCode");
	MuOnlineQuery.Close();

	if (Banned == 1)
	{
		MessageLog(1, c_Red, t_BAN, gObj, "[BanChar] %s is already banned", tObj->Name);
		return true;
	}
	else
	{
		MuOnlineQuery.ExecQuery("UPDATE Character SET CtlCode = 1 WHERE Name = '%s'", tObj->Name);
		MuOnlineQuery.Fetch();
		MuOnlineQuery.Close();

		MessageLog(1, c_Red, t_BAN, gObj, "[BanChar] %s banned till.", tObj->Name);
		MessageLog(1, c_Red, t_BAN, tObj, "[BanChar] Your character was banned by %s.", gObj->Name);
	}

	CloseClient(Index);
	return true;
}

bool cChat::BanAccCommand(LPOBJ gObj, char *Msg, int Index)
{
	if (CheckCommand(gObj, Configs.Commands.IsBanAcc, GmSystem.cBanPlayer, 0, 0, 0, 0, 0, 0, Index, "BanAcc", "[Name] /banacc", ""))
		return true;

	OBJECTSTRUCT *tObj = (OBJECTSTRUCT*)OBJECT_POINTER(Index);

	MessageLog(1, c_Red, t_BAN, gObj, "[BanAcc] %s banned,", tObj->Name);
	MessageLog(1, c_Red, t_BAN, tObj, "[BanAcc] Your character was banned by %s.", gObj->Name);

	Me_MuOnlineQuery.ExecQuery("UPDATE MEMB_INFO SET bloc_code = 1 WHERE memb___id = '%s'", tObj->AccountID);
	Me_MuOnlineQuery.Fetch();
	Me_MuOnlineQuery.Close();

	CloseClient(Index);
	return true;
}

bool cChat::UnBanCharCommand(LPOBJ gObj, char* Target)
{
	if (CheckCommand(gObj, Configs.Commands.IsBanChar, GmSystem.cBanPlayer, 0, 0, 0, 0, 0, 0, 0, "UnBanChar", "[Name] /unbanchar", ""))
		return true;

	MuOnlineQuery.ExecQuery("SELECT CtlCode FROM Character WHERE Name = '%s'", Target);
	MuOnlineQuery.Fetch();
	int Banned = MuOnlineQuery.GetAsInteger("CtlCode");
	MuOnlineQuery.Close();

	if (Banned == 0)
	{
		MessageLog(1, c_Red, t_BAN, gObj, "[UnBanChar] %s is not baned", Target);
		return true;
	}
	else
	{
		MuOnlineQuery.ExecQuery("UPDATE Character SET CtlCode = 0 WHERE Name = '%s'", Target);
		MuOnlineQuery.Fetch();
		MuOnlineQuery.Close();
		MessageLog(1, c_Red, t_BAN, gObj, "[UnBanChar] %s UnBaned", Target);
	}
	return true;
}

bool cChat::UnBanAccCommand(LPOBJ gObj, char* Target)
{
	if (CheckCommand(gObj, Configs.Commands.IsBanAcc, GmSystem.cBanPlayer, 0, 0, 0, 0, 0, 0, 0, "UnBanAcc", "[Name] /unbanacc", ""))
	{
		return true;
	}

	Me_MuOnlineQuery.ExecQuery("SELECT bloc_code FROM MEMB_INFO WHERE memb___id = '%s'", Target);
	Me_MuOnlineQuery.Fetch();
	int Banned = Me_MuOnlineQuery.GetAsInteger("bloc_code");
	Me_MuOnlineQuery.Close();

	if (Banned == 0)
	{
		MessageLog(1, c_Red, t_BAN, gObj, "[UnBanAcc] %s is not baned", Target);
		return true;
	}
	else
	{
		Me_MuOnlineQuery.ExecQuery("UPDATE MEMB_INFO SET bloc_code = 0 WHERE memb___id = '%s'", Target);
		Me_MuOnlineQuery.Fetch();
		Me_MuOnlineQuery.Close();
		MessageLog(1, c_Red, t_BAN, gObj, "[UnBanAcc] %s UnBaned", Target);
	}

	return true;
}

bool cChat::TimeCommand(LPOBJ gObj)
{
	if (CheckCommand(gObj, Configs.Commands.IsTime, GmSystem.NONE, 0, 0, 0, 0, 0, 0, 0, "Time", COMMAND_TIME, ""))
	{
		return true;
	}

	SYSTEMTIME t;
	GetLocalTime(&t);
	MessageLog(1, c_Blue, t_COMMANDS, gObj, "Server Time & Date: %02d:%02d:%02d %02d-%02d-%02d.", t.wHour, t.wMinute, t.wSecond, t.wDay, t.wMonth, t.wYear);
	return true;
}

bool cChat::LevelCommand(LPOBJ gObj)
{
	MessageLog(1, c_Red, t_GM, gObj, "Level: %d, Master Level: %d", gObj->Level, gObj->MLevel);

	return true;
}

bool cChat::DropCommand(LPOBJ gObj,char *Msg,int Index)
{
	if(CheckCommand(gObj,Configs.Commands.IsDrop,GmSystem.cDrop,0,0,0,0,0,3,Index,"Drop", "[Name] /drop <Quant> <Tipo> <Id> <Lvl> <Skill> <Luck> <Opt> <Exc> <Anc>",Msg))
	{
		return true;
	}

	int ItemArray[10] = {0};

	sscanf
	(
		Msg,
		"%d %d %d %d %d %d %d %d %d",
		&ItemArray[0], // Count
		&ItemArray[1], // Type
		&ItemArray[2], // Index
		&ItemArray[3], // Level
		&ItemArray[4], // Skill
		&ItemArray[5], // Luck
		&ItemArray[6], // Opt
		&ItemArray[7], // Exc
		&ItemArray[8]  // Ancient
	);

	int Item = ItemArray[1] * 512 + ItemArray[2];

	if((ItemArray[0] < 0) || (ItemArray[0] > 20))
	{
		ItemArray[0] = 1;
	}

	if
	(
		ItemArray[2] < 0 ||
		(ItemArray[1] < 0 || ItemArray[1] > 15) ||
		(ItemArray[3] < 0 || ItemArray[3] > 13) ||
		(ItemArray[6] < 0 || ItemArray[6] > 7) ||
		(ItemArray[5] < 0 || ItemArray[5] > 1) ||
		(ItemArray[4] < 0 || ItemArray[4] > 1) ||
		(ItemArray[7] < 0 || ItemArray[7] > 63) ||
		(ItemArray[8] < 0 || ItemArray[8] > 40)
	)
	{
		MessageLog(1,c_Red,t_GM,gObj,"[Drop] Uso: /drop <Quant> <Tipo> <Id> <Lvl> <Skill> <Luck> <Opt> <Exc> <Anc>");

		return true;
	}
	else
	{
		OBJECTSTRUCT *tObj = (OBJECTSTRUCT*)OBJECT_POINTER(Index);

		do
		{
			ItemSerialCreateSend(Index,tObj->MapNumber,(int)tObj->X,(int)tObj->Y,Item,ItemArray[3],0,ItemArray[4],ItemArray[5],ItemArray[6],Index,ItemArray[7],ItemArray[8]);
		}
		while(--ItemArray[0]);

		if(tObj == gObj)
		{
			MessageLog(1, c_Green, t_GM, gObj, "[Drop] %d Itens cridos %d %d %d %d %d %d %d %d", ItemArray[0],ItemArray[1],ItemArray[2], ItemArray[3], ItemArray[4], ItemArray[5], ItemArray[6], ItemArray[7], ItemArray[8]);
		}
		else
		{
			Message(1, gObj, "[Drop] Voce ganhou %d de %s!", gObj->Name, ItemArray[0]);
			MessageLog(1, c_Green, t_GM, gObj, "[Drop] %d Itens cridos para %s %d %d %d %d %d %d %d %d", ItemArray[0],tObj->Name,ItemArray[1],ItemArray[2], ItemArray[3], ItemArray[4], ItemArray[5], ItemArray[6], ItemArray[7], ItemArray[8]);
		}
	}

	return true;
}

bool cChat::SetCharCommand(LPOBJ gObj, char* Msg, int Index)
{
	if (CheckCommand(gObj, Configs.Commands.IsSetChar, GmSystem.cSetZen, 0, 0, 0, 0, 0, 1, Index, "SetChar", "[Name] /setchar <Zen> <PCPnt> <WCoins> <AddPnt> <lvl> <Prof>", Msg))
	{
		return true;
	}

	DWORD Zen = 0;
	int PCPnt = 0, WCoin = 0, AddPnt = 0, Lvl = 0, Prof = 0;

	sscanf(Msg, "%d %d %d %d %d %d", &Zen, &PCPnt, &WCoin, &AddPnt, &Lvl, &Prof);

	if (Zen > 2000000000)
	{
		MessageLog(1, c_Red, t_GM, gObj, "[SetChar] Zen can't be less than 0 and more than 2000000000!");
		return true;
	}

	if (PCPnt < 0 || PCPnt > PCPoint.Config.MaximumPCPoints)
	{
		MessageLog(1, c_Red, t_GM, gObj, "[SetChar] PCPnt can't be less than 0 and more than %d!", PCPoint.Config.MaximumPCPoints);
		return true;
	}

	if (WCoin < 0 || WCoin > PCPoint.Config.MaximumWCPoints)
	{
		MessageLog(1, c_Red, t_GM, gObj, "[SetChar] WCoin can't be less than 0 and more than %d!", PCPoint.Config.MaximumWCPoints);
		return true;
	}

	int MaximumAddPnt;

	if (Configs.Enable65kStats == 0)
	{
		MaximumAddPnt = 32000;
	}
	else
	{
		MaximumAddPnt = 65000;
	}

	if (AddPnt < 0 || AddPnt > MaximumAddPnt)
	{
		MessageLog(1, c_Red, t_GM, gObj, "[SetChar] AddPnt can't be less than 0 and more than %d!", MaximumAddPnt);

		return true;
	}

	if (Lvl < 0 || Lvl > Configs.Commands.MaxLvl)
	{
		MessageLog(1, c_Red, t_GM, gObj, "[SetChar] Lvl can't be less than 0 and more than %d!", Configs.Commands.MaxLvl);
		return true;
	}

	if (Prof < 0 || Prof > 3)
	{
		MessageLog(1, c_Red, t_GM, gObj, "[SetChar] Lvl can't be less than 0 and more than 3!");
		return true;
	}

	OBJECTSTRUCT *tObj = (OBJECTSTRUCT*)OBJECT_POINTER(Index);

	if (Zen > 0)
	{
		tObj->Money = Zen;
		GCMoneySend(tObj->m_Index, Zen);
	}

	if (PCPnt > 0)
	{
		PCPoint.UpdatePoints(tObj, PCPnt, PLUS, PCPOINT);
	}

	if (WCoin > 0)
	{
		PCPoint.UpdatePoints(tObj, WCoin, PLUS, WCOIN);
	}

	if(AddPnt > 0)
	{
		tObj->LevelUpPoint += AddPnt;
	}

	if (Lvl > 0)
	{
		tObj->Level = Lvl;
	}

	if (Prof > 0)
	{
		switch (Prof)
		{
		case 0:
			{
			}
			break;
		case 1:
			{
				if (gObj->DbClass <= 3)
					gObj->DbClass = 0;
				else if (gObj->DbClass >= 16 && gObj->DbClass <= 19)
					gObj->DbClass = 16;
				else if (gObj->DbClass >= 32 && gObj->DbClass <= 35)
					gObj->DbClass = 32;
				else if (gObj->DbClass >= 48 && gObj->DbClass <= 50)
					gObj->DbClass = 48;
				else if (gObj->DbClass >= 64 && gObj->DbClass <= 66)
					gObj->DbClass = 64;
				else if (gObj->DbClass >= 80 && gObj->DbClass < 83)
					gObj->DbClass = 80;
			}
			break;
		case 2:
			{
				if (gObj->DbClass <= 3)
					gObj->DbClass = 1;
				else if (gObj->DbClass >= 16 && gObj->DbClass <= 19)
					gObj->DbClass = 17;
				else if (gObj->DbClass >= 32 && gObj->DbClass <= 35)
					gObj->DbClass = 33;
				else if (gObj->DbClass >= 80 && gObj->DbClass < 83)
					gObj->DbClass = 81;
			}
			break;
		case 3:
			{
				if (gObj->DbClass <= 3)
					gObj->DbClass = 3;
				else if (gObj->DbClass >= 16 && gObj->DbClass <= 19)
					gObj->DbClass = 19;
				else if (gObj->DbClass >= 32 && gObj->DbClass <= 35)
					gObj->DbClass = 35;
				else if (gObj->DbClass >= 48 && gObj->DbClass <= 50)
					gObj->DbClass = 50;
				else if (gObj->DbClass >= 64 && gObj->DbClass <= 66)
					gObj->DbClass = 66;
				else if (gObj->DbClass >= 80 && gObj->DbClass < 83)
					gObj->DbClass = 83;
			}
			break;
		}
	}

	if (gObj == tObj)
	{
		if (AddPnt > 0 || Prof > 0 || Lvl > 0)
			MessageLog(1, c_Red, t_GM, tObj, "[SetChar] Your character was edited, you must relogin!");
		else
			MessageLog(1, c_Red, t_GM, tObj, "[SetChar] Your character was edited!");
	}
	else
	{
		MessageLog(1, c_Red, t_GM, gObj, "[SetChar] You successfully changed %s character.", tObj->Name);
		if (AddPnt > 0 || Prof > 0 || Lvl > 0)
			MessageLog(1, c_Red, t_GM, tObj, "[SetChar] Your character was edited by %s, you must relogin!", gObj->Name);
		else
			MessageLog(1, c_Red, t_GM, tObj, "[SetChar] Your character was edited by %s!", gObj->Name);
	}
	return true;
}

bool cChat::OnlineCommand(LPOBJ gObj, char *Msg)
{
	if (CheckCommand(gObj, Configs.Commands.IsOnline, GmSystem.NONE, 0, 0, 0, 0, 0, 0, 0, "Online", COMMAND_ONLINE, Msg))
	{
		return true;
	}

	MessageLog(1,c_Blue,t_COMMANDS,gObj,"[ONLINE]: %d Player(s), %d GM(s)",(Log.Online_All - Log.Online_Gms),Log.Online_Gms);

	return true;
}

bool cChat::SetPKCommand(LPOBJ gObj, char *Msg, int Index)
{
	if (CheckCommand(gObj, Configs.Commands.IsSetPK, GmSystem.cSetPK, 0, 0, 0, 0, 0, 1, Index, "SetPK", "[Name] /setpk <pklvl>", Msg))
	{
		return true;
	}

	int SetLevel;
	sscanf(Msg, "%d", &SetLevel);

	if (SetLevel < 0 || SetLevel > 100)
	{
		MessageLog(1, c_Red, t_GM, gObj, "[SetPK] PK lvl can't be less than 0 and more than 100!");
		return true;
	}

	OBJECTSTRUCT *tObj = (OBJECTSTRUCT*)OBJECT_POINTER(Index);

	tObj->m_PK_Level = SetLevel;
	if (SetLevel >= 3)
		tObj->m_PK_Count = SetLevel - 3;
	GCPkLevelSend(tObj->m_Index, SetLevel);

	if (gObj == tObj)
		MessageLog(1, c_Red, t_GM, tObj, "[SetPK] Your pk was changed to %d.", SetLevel);
	else
	{
		MessageLog(1, c_Red, t_GM, gObj, "[SetPK] You successfully changed %s pk to %d.", tObj->Name, SetLevel);
		MessageLog(1, c_Red, t_GM, tObj, "[SetPK] Your pk was changed to %d by %s.", SetLevel, gObj->Name);
	}
	return true;
}

bool cChat::ReloadCommand(LPOBJ gObj, char *Msg)
{
	if (CheckCommand(gObj, Configs.Commands.IsReload, GmSystem.cReload, 0, 0, 0, 0, 0, 1, 0, "Reload", "/reload <number>", Msg))
		return true;

	int NumberReload;
	sscanf(Msg, "%d", &NumberReload);

	switch (NumberReload)
	{
	case 0:
		{
			Configs.LoadAll();
			MoveReq.Load();
			ResetSystem.Init();
			MessageLog(1, c_Blue, t_COMMANDS, gObj, "[Reload] Data, Reset & MoveReq Reloaded.");
			break;
		}
	case 1:
		{
			GameMonsterAllCloseAndReload();
#ifdef _GS
			Monster.ReadMonsterAdd();
#endif
			MessageLog(1, c_Blue, t_COMMANDS, gObj, "[Reload] Monsters Reloaded.");
			break;
		}
	case 2:
		{
			pShopDataLoad();
			PCPoint.Load();
			MessageLog(1, c_Blue, t_COMMANDS, gObj, "[Reload] Shops & PCPoints Reloaded.");
			break;
		}
	case 3:
		{
			if (GmSystem.Config.IsGMSystem)
			{
				GmSystem.Load();
				MessageLog(1, c_Blue, t_COMMANDS, gObj, "[Reload] GMSystem Reloaded.");
			}
			else
				Message(1, gObj, "[Reload] GMSystem is disabled");
			break;
		}
	case 4:
		{
			DropSystem.Load();
#ifdef _GS
			DropEvent.updateBC();	// reload BC drop config
			DropEvent.updateIT();	// reload IT drop config
			DropEvent.updateWW();	// reload WW drop config
			DropEvent.updateCC();	// reload CC drop config
#endif
			MessageLog(1, c_Blue, t_COMMANDS, gObj, "[Reload] Item Drop Settings Reloaded.");
			break;
		}
	case 6:
		{
			Configs.LoadAll();
			GameMonsterAllCloseAndReload();
			pShopDataLoad();
			DropSystem.Load();
#ifdef _GS
			Monster.ReadMonsterAdd();
			DropEvent.updateBC();	// reload BC drop config
			DropEvent.updateIT();	// reload IT drop config
			DropEvent.updateWW();	// reload WW drop config
			DropEvent.updateCC();	// reload CC drop config
			ResetSystem.Init();
#endif
			MessageLog(1, c_Blue, t_COMMANDS, gObj, "[Reload] All Options Reloaded.");
			break;
		}
	default:
		{
			MessageLog(1, c_Red, t_GM, gObj, "[Reload] Usage: /reload <Number>.");
			break;
		}
	}
	return true;
}

bool cChat::StatusCommand(LPOBJ gObj, char *Msg, int Index)
{
	if (CheckCommand(gObj, Configs.Commands.IsStatus, GmSystem.cStatus, 0, 0, 0, 0, 0, 0, Index, "Status", "[Name] /status", Msg))
		return true;

	OBJECTSTRUCT *tObj = (OBJECTSTRUCT*)OBJECT_POINTER(Index);

	MessageLog(0, c_Green, t_GM, gObj, "IP Address: %s", tObj->Ip_addr);
	MessageLog(0, c_Green, t_GM, gObj, "Account: %s | Character: %s", tObj->AccountID, tObj->Name);
	MessageLog(0, c_Green, t_GM, gObj, "Level: %d | Zen: %d", tObj->Level, tObj->Money);
	MessageLog(0, c_Green, t_GM, gObj, "Map: %s (%d)(%d,%d)", Utilits.GetMapName(tObj->MapNumber), tObj->MapNumber, tObj->X, tObj->Y);

	if (AddTab[tObj->m_Index].IsMarried)
		MessageLog(0, c_Green, t_GM, gObj, "Married on %s | Resets: %d", AddTab[tObj->m_Index].MarryName, AddTab[tObj->m_Index].Resets);
	else
		MessageLog(0, c_Green, t_GM, gObj, "Not married | Resets: %d", AddTab[tObj->m_Index].Resets);

	MessageLog(1, c_Green, t_GM, gObj, "[Status][GM] %s get your status!", gObj->Name);
	return true;
}

bool cChat::SkinCommand(LPOBJ gObj, char *Msg, int Index)
{
	if (CheckCommand(gObj, Configs.Commands.SkinEnabled, GmSystem.cSkin, 0, 0, 0, 0, 0, 1, Index, "Skin", "[Name] /skin <num>", Msg))
	{
		return true;
	}

	int NumSkin = 0;

	sscanf(Msg, "%d", &NumSkin);

	OBJECTSTRUCT *tObj = (OBJECTSTRUCT*)OBJECT_POINTER(Index);

	tObj->m_Change = NumSkin;
	gObjViewportListProtocolCreate(tObj);

	if (tObj == gObj)
	{
		MessageLog(1, c_Red, t_GM, tObj, "[Skin] Your Skin was changed.");
	}
	else
	{
		MessageLog(1, c_Red, t_GM, gObj, "[Skin] You successfully change %s Skin.", tObj->Name);
		MessageLog(1, c_Red, t_GM, tObj, "[Skin] Your Skin was changed by %s.", gObj->Name);
	}

	return true;
}

bool cChat::GmoveCommand(LPOBJ gObj, char *Msg, int Index)
{
	if (CheckCommand(gObj, Configs.Commands.IsGmove, GmSystem.cGmove, 0, 0, 0, 0, 0, 3, Index, "Gmove", "[Name] /gmove <map> <x> <y>", Msg))
		return true;

	char Map[250] = { 0 };
	int x, y;

	sscanf(Msg, "%249s %d %d", &Map, &x, &y);
	LPOBJ tObj = (OBJECTSTRUCT*)OBJECT_POINTER(Index);

	int RMap;
	if (_strcmpi(Map, "0") == 0 || _strcmpi(Map, "Lorencia") == 0) RMap = 0;
	else if (_strcmpi(Map, "1") == 0 || _strcmpi(Map, "Dungeon") == 0) RMap = 1;
	else if (_strcmpi(Map, "2") == 0 || _strcmpi(Map, "Devias") == 0) RMap = 2;
	else if (_strcmpi(Map, "3") == 0 || _strcmpi(Map, "Noria") == 0) RMap = 3;
	else if (_strcmpi(Map, "4") == 0 || _strcmpi(Map, "Losttower") == 0) RMap = 4;
	else if (_strcmpi(Map, "6") == 0 || _strcmpi(Map, "Stadium") == 0 || _strcmpi(Map, "Arena") == 0) RMap = 6;
	else if (_strcmpi(Map, "7") == 0 || _strcmpi(Map, "Atlans") == 0) RMap = 7;
	else if (_strcmpi(Map, "8") == 0 || _strcmpi(Map, "Tarkan") == 0) RMap = 8;
	else if (_strcmpi(Map, "10") == 0 || _strcmpi(Map, "Icarus") == 0) RMap = 10;
	else if (_strcmpi(Map, "24") == 0 || _strcmpi(Map, "kalima1") == 0) RMap = 24;
	else if (_strcmpi(Map, "25") == 0 || _strcmpi(Map, "kalima2") == 0) RMap = 25;
	else if (_strcmpi(Map, "26") == 0 || _strcmpi(Map, "kalima3") == 0) RMap = 26;
	else if (_strcmpi(Map, "27") == 0 || _strcmpi(Map, "kalima4") == 0) RMap = 27;
	else if (_strcmpi(Map, "28") == 0 || _strcmpi(Map, "kalima5") == 0) RMap = 28;
	else if (_strcmpi(Map, "29") == 0 || _strcmpi(Map, "kalima6") == 0) RMap = 29;
	else if (_strcmpi(Map, "30") == 0 || _strcmpi(Map, "valleyofloren") == 0) RMap = 30;
	else if (_strcmpi(Map, "31") == 0 || _strcmpi(Map, "landoftrial") == 0 || _strcmpi(Map, "landsoftrial") == 0) RMap = 31;
	else if (_strcmpi(Map, "11") == 0 || _strcmpi(Map, "bc1") == 0) RMap = 11;
	else if (_strcmpi(Map, "12") == 0 || _strcmpi(Map, "bc2") == 0) RMap = 12;
	else if (_strcmpi(Map, "13") == 0 || _strcmpi(Map, "bc3") == 0) RMap = 13;
	else if (_strcmpi(Map, "14") == 0 || _strcmpi(Map, "bc4") == 0) RMap = 14;
	else if (_strcmpi(Map, "15") == 0 || _strcmpi(Map, "bc5") == 0) RMap = 15;
	else if (_strcmpi(Map, "16") == 0 || _strcmpi(Map, "bc6") == 0) RMap = 16;
	else if (_strcmpi(Map, "17") == 0 || _strcmpi(Map, "bc7") == 0) RMap = 17;
	else if (_strcmpi(Map, "52") == 0 || _strcmpi(Map, "bc8") == 0) RMap = 52;
	else if (_strcmpi(Map, "18") == 0 || _strcmpi(Map, "cc1") == 0) RMap = 18;
	else if (_strcmpi(Map, "19") == 0 || _strcmpi(Map, "cc2") == 0) RMap = 19;
	else if (_strcmpi(Map, "20") == 0 || _strcmpi(Map, "cc3") == 0) RMap = 20;
	else if (_strcmpi(Map, "21") == 0 || _strcmpi(Map, "cc4") == 0) RMap = 21;
	else if (_strcmpi(Map, "22") == 0 || _strcmpi(Map, "cc5") == 0) RMap = 22;
	else if (_strcmpi(Map, "23") == 0 || _strcmpi(Map, "cc6") == 0) RMap = 23;
	else if (_strcmpi(Map, "53") == 0 || _strcmpi(Map, "cc7") == 0) RMap = 53;
	else if (_strcmpi(Map, "33") == 0 || _strcmpi(Map, "aida") == 0) RMap = 33;
	else if (_strcmpi(Map, "34") == 0 || _strcmpi(Map, "crywolf") == 0) RMap = 34;
	else if (_strcmpi(Map, "36") == 0 || _strcmpi(Map, "kalima7") == 0) RMap = 36;
	else if (_strcmpi(Map, "37") == 0 || _strcmpi(Map, "kanturu") == 0) RMap = 37;
	else if (_strcmpi(Map, "38") == 0 || _strcmpi(Map, "kanturutruins") == 0 || _strcmpi(Map, "kantrutruins") == 0) RMap = 38;
	else if (_strcmpi(Map, "39") == 0 || _strcmpi(Map, "kantrutower") == 0 || _strcmpi(Map, "kanturutower") == 0) RMap = 39;
	else if (_strcmpi(Map, "40") == 0 || _strcmpi(Map, "silent") == 0) RMap = 40;
	else if (_strcmpi(Map, "41") == 0 || _strcmpi(Map, "balgasbarrack") == 0) RMap = 41;
	else if (_strcmpi(Map, "42") == 0 || _strcmpi(Map, "balgasrefuge") == 0) RMap = 42;
	else if (_strcmpi(Map, "50") == 0 || _strcmpi(Map, "ilusion6") == 0) RMap = 50;
	else if (_strcmpi(Map, "51") == 0 || _strcmpi(Map, "elbeland") == 0) RMap = 51;
	else if (_strcmpi(Map, "56") == 0 || _strcmpi(Map, "swampofcalmness") == 0 || _strcmpi(Map, "calmness") == 0) RMap = 56;
	else if (_strcmpi(Map, "57") == 0 || _strcmpi(Map, "raklion") == 0) RMap = 57;
	else if (_strcmpi(Map, "58") == 0 || _strcmpi(Map, "raklionboss") == 0) RMap = 58;
	else if (_strcmpi(Map, "62") == 0 || _strcmpi(Map, "santatown") == 0 || _strcmpi(Map, "santa") == 0) RMap = 62;
	else if (_strcmpi(Map, "63") == 0 || _strcmpi(Map, "vulcanus") == 0) RMap = 63;
	else if (_strcmpi(Map, "64") == 0 || _strcmpi(Map, "coliseum") == 0) RMap = 64;
	else
	{
		MessageLog(1, c_Red, t_GM, gObj, "[GMove] Such map doesn't exist!");
		return true;
	}
	if (x > 255 || y > 255 || x < 0 || y < 0)
	{
		MessageLog(1, c_Red, t_GM, gObj, "[GMove] Such coords doesn't exist!");
		return true;
	}
	gObjTeleport(tObj->m_Index, RMap, x, y);
	if (tObj == gObj)
		MessageLog(1, c_Green, t_GM, gObj, "[GMove] You successfully moved to %s %d %d!", Map, x, y);
	else
	{
		MessageLog(1, c_Green, t_GM, gObj, "[GMove] You successfully move %s to %s %d %d!", tObj->Name, Map, x, y);
		MessageLog(1, c_Green, t_GM, tObj, "[GMove] You successfully moved to %s %d %d by %s!", Map, x, y, gObj->Name);
	}
	return true;
}

bool cChat::PKClearCommand(LPOBJ gObj, char *Msg, int Index)
{
	if (CheckCommand(gObj, Monster.ClearCommand.Enabled, GmSystem.NONE, 0, 0, 0, 0, 0, 0, Index, "PKClear", COMMAND_PKCLEAR, Msg))
	{
		return true;
	}

	if (GmSystem.IsCommand(GmSystem.cPkClear, gObj->Name))
	{
		OBJECTSTRUCT *tObj = (OBJECTSTRUCT*)OBJECT_POINTER(Index);

		if (tObj->m_PK_Level <= 3)
		{
			MessageLog(1, c_Blue, t_COMMANDS, gObj, "[PkClear] %s nao esta PK!", tObj->Name);
			return true;
		}

		tObj->m_PK_Level = 3;
		tObj->m_PK_Count = 0;
		GCPkLevelSend(tObj->m_Index, 3);

		if (tObj == gObj)
		{
			MessageLog(1, c_Red, t_GM, tObj, "[PkClear] Voce nao esta mais PK.");
		}
		else
		{
			MessageLog(1, c_Red, t_GM, gObj, "[PkClear] Voce limpou o PK de %s.", tObj->Name);
			MessageLog(1, c_Red, t_GM, tObj, "[PkClear] Seu status PK foi limpo por %s.", gObj->Name);
		}
	}
	else if (!Monster.ClearCommand.OnlyForGm)
	{
		int PriceZen;
		int PricePcPoint;
		int PriceWCoin;
		int PriceWebPoint;

		switch (Monster.ClearCommand.Type)
		{
		case 1:
			{
				PriceZen = (Monster.ClearCommand.PriceZen * gObj->m_PK_Count);
				PricePcPoint = (Monster.ClearCommand.PricePcPoints * gObj->m_PK_Count);
				PriceWCoin = (Monster.ClearCommand.PriceWCoins * gObj->m_PK_Count);
				PriceWebPoint = (Monster.ClearCommand.PriceWebPoints * gObj->m_PK_Count);

				break;
			}
		case 2:
			{
				PriceZen = Monster.ClearCommand.PriceZenForAll;
				PricePcPoint = Monster.ClearCommand.PricePcPointsForAll;
				PriceWCoin = Monster.ClearCommand.PriceWCoinsForAll;
				PriceWebPoint = Monster.ClearCommand.PriceWebPointsForAll;

				break;
			}
		case 0:
			{
				PriceZen = 0;
				PricePcPoint = 0;
				PriceWCoin = 0;
				PriceWebPoint = 0;

				break;
			}
		}

		if (gObj->m_PK_Level <= 3)
		{
			MessageLog(1, c_Blue, t_COMMANDS, gObj, "[PkClear] Voce nao esta PK!");

			return true;
		}

		if (CheckCommand(gObj, Monster.ClearCommand.Enabled, GmSystem.NONE, PriceZen, PricePcPoint, PriceWCoin, PriceWebPoint, Monster.ClearCommand.LevelReq, 0, 0, "PKClear", COMMAND_PKCLEAR, Msg))
		{
			return true;
		}

		TakeCommand(gObj, PriceZen, PricePcPoint, PriceWCoin, PriceWebPoint, "PKClear");
		gObj->m_PK_Level = 3;
		gObj->m_PK_Count = 0;
		GCPkLevelSend(gObj->m_Index, 3);
		MessageLog(1, c_Blue, t_COMMANDS, gObj, "[PkClear] Seu PK foi limpo!");
	}

	return true;
}

#pragma warning(disable: 4018 4244)
bool cChat::AddCommands(LPOBJ gObj, char *Msg, int Type)
{
	char StatsUsage[12];

	switch(Type)
	{
		case 0:
		{
			strcpy(StatsUsage,"/str <num>");

			break;
		}
		case 1:
		{
			strcpy(StatsUsage,"/agi <num>");

			break;
		}
		case 2:
		{
			strcpy(StatsUsage,"/vit <num>");

			break;
		}
		case 3:
		{
			strcpy(StatsUsage,"/ene <num>");

			break;
		}
		case 4:
		{
			if(gObj->Class != 4)
			{
				MessageLog(1, c_Red, t_COMMANDS, gObj, "[AddStats] Voce nao e um Dark Lord!!!");

				return true;
			}

			strcpy(StatsUsage,"/cmd <num>");

			break;
		}
	}

	if
	(
		CheckCommand
		(
			gObj,
			Configs.Commands.AddPointEnabled,
			GmSystem.NONE,
			Configs.Commands.AddPriceZen,
			Configs.Commands.AddPricePCPoint,
			Configs.Commands.AddPriceWCoin,
			Configs.Commands.AddPriceWebPoints,
			Configs.Commands.AddPointLevelReq,
			1,
			0,
			"AddStats",
			StatsUsage,
			Msg
		)
	)
	{
		return true;
	}

	int Points;
	sscanf(Msg,"%d",&Points);

	if(Configs.Commands.MaxAddedStats > 0 && Configs.Commands.MaxAddedStats <= Points)
	{
		MessageLog(1, c_Red, t_COMMANDS, gObj, "[AddStats] Voce nao pode adicionar mais do que %d pontos!", Configs.Commands.MaxAddedStats);

		return true;
	}

	int MaxPoints = 32000;

	if(Configs.Enable65kStats)
	{
		MaxPoints = -536;
	}

	int Stats = 0;
	bool bResult = false;

	switch(Type)
	{
		case 0x00:
		{
			Stats = gObj->Strength;

			if(Configs.MaxStatsSystemEnable)
			{
				if (gObj->Class == 0)
					MaxPoints = Configs.MaxDW_Strength;
				else if (gObj->Class == 1)
					MaxPoints = Configs.MaxDK_Strength;
				else if (gObj->Class == 2)
					MaxPoints = Configs.MaxELF_Strength;
				else if (gObj->Class == 3)
					MaxPoints = Configs.MaxMG_Strength;
				else if (gObj->Class == 4)
					MaxPoints = Configs.MaxDL_Strength;
				else if (gObj->Class == 5)
					MaxPoints = Configs.MaxSUM_Strength;
			}

			break;
		}
		case 0x01:
		{
			Stats = gObj->Dexterity;

			if (Configs.MaxStatsSystemEnable)
			{
				if (gObj->Class == 0)
					MaxPoints = Configs.MaxDW_Agility;
				else if (gObj->Class == 1)
					MaxPoints = Configs.MaxDK_Agility;
				else if (gObj->Class == 2)
					MaxPoints = Configs.MaxELF_Agility;
				else if (gObj->Class == 3)
					MaxPoints = Configs.MaxMG_Agility;
				else if (gObj->Class == 4)
					MaxPoints = Configs.MaxDL_Agility;
				else if (gObj->Class == 5)
					MaxPoints = Configs.MaxSUM_Agility;
			}

			break;
		}
		case 0x02:
		{
			Stats = gObj->Vitality;

			if (Configs.MaxStatsSystemEnable)
			{
				if (gObj->Class == 0)
					MaxPoints = Configs.MaxDW_Vitality;
				else if (gObj->Class == 1)
					MaxPoints = Configs.MaxDK_Vitality;
				else if (gObj->Class == 2)
					MaxPoints = Configs.MaxELF_Vitality;
				else if (gObj->Class == 3)
					MaxPoints = Configs.MaxMG_Vitality;
				else if (gObj->Class == 4)
					MaxPoints = Configs.MaxDL_Vitality;
				else if (gObj->Class == 5)
					MaxPoints = Configs.MaxSUM_Vitality;
			}

			break;
		}
		case 0x03:
		{
			Stats = gObj->Energy;

			if (Configs.MaxStatsSystemEnable)
			{
				if (gObj->Class == 0)
					MaxPoints = Configs.MaxDW_Energy;
				else if (gObj->Class == 1)
					MaxPoints = Configs.MaxDK_Energy;
				else if (gObj->Class == 2)
					MaxPoints = Configs.MaxELF_Energy;
				else if (gObj->Class == 3)
					MaxPoints = Configs.MaxMG_Energy;
				else if (gObj->Class == 4)
					MaxPoints = Configs.MaxDL_Energy;
				else if (gObj->Class == 5)
					MaxPoints = Configs.MaxSUM_Energy;
			}

			break;
		}
		case 0x04:
		{
			Stats = gObj->Leadership;

			if(Configs.MaxStatsSystemEnable)
			{
				if (gObj->Class == 4)
				{
					MaxPoints = Configs.MaxDL_Command;
				}
			}

			break;
		}
	}

	int MaxPointsTemp = MaxPoints;

	if (MaxPoints > 32767)
	{
		MaxPoints = -32768 + (MaxPoints - 32767);
	}

	if (((MaxPoints > 0) && (Stats >= MaxPoints || Stats < 0)) || ((MaxPoints < 0) && (Stats < 0) && (Stats >= MaxPoints)))
	{
		MessageLog(1, c_Red, t_COMMANDS, gObj, "[AddStats] Voce ja esta full nesse stats!");

		return true;
	}

	int StatsTemp = Stats;
	Stats += Points;

	if(gObj->LevelUpPoint < Points)
	{
		MessageLog(1, c_Red, t_COMMANDS, gObj, "[AddStats] Pontos insuficientes, necessario mais %d pontos.", Points - gObj->LevelUpPoint);

		return true;
	}

	if (((MaxPoints > 0) && (Stats > MaxPoints || Stats < 0)) || ((MaxPoints < 0) && (Stats < 0) && (Stats > MaxPoints)))
	{
		MessageLog(1, c_Red, t_COMMANDS, gObj, "[AddStats] Voce nao pode adicionar mais do que %d pontos nesse stats!", MaxPoints - StatsTemp);

		return true;
	}

	TakeCommand(gObj, Configs.Commands.AddPriceZen, Configs.Commands.AddPricePCPoint, Configs.Commands.AddPriceWCoin, Configs.Commands.AddPriceWebPoints,"AddStats");

	// Efeito Gelo (3) :D
	if(Configs.Commands.AddPointEffect > 0)
	{
		Utilits.SendEffect(gObj,3);
	}

	int aIndex = Utilits.GetPlayerIndex(gObj->Name);

	switch (Type)
	{
		case 0x00:
		{
			PMSG_STAT_UPDATE pMsg;
			PHeadSetB((LPBYTE)&pMsg, 0x2C, sizeof(PMSG_STAT_UPDATE));

			pMsg.result = 0;
			pMsg.btFruitType = 3;
			pMsg.btStatValue = Points;
			gObj->Strength += Points;
			gObj->LevelUpPoint -= Points;

			DataSend(gObj->m_Index,(LPBYTE)&pMsg, pMsg.h.size);
			gObjCalCharacter(aIndex);
			GCReFillSend(gObj->m_Index, gObj->MaxLife + gObj->AddLife, 0xFE, 0, gObj->iMaxShield + gObj->iAddShield);
			gObjSetBP(aIndex);
			GCManaSend(gObj->m_Index, gObj->MaxMana + gObj->AddMana, 0xFE, 0, gObj->MaxBP + gObj->AddBP);
			GCLevelUpMsgSend(gObj->m_Index, 0);

			return true;
		}
		case 0x01:
		{
			PMSG_STAT_UPDATE pMsg;
			PHeadSetB((LPBYTE)&pMsg, 0x2C, sizeof(PMSG_STAT_UPDATE));

			pMsg.result = 0;
			pMsg.btFruitType = 2;
			pMsg.btStatValue = Points;
			gObj->Dexterity += Points;
			gObj->LevelUpPoint -= Points;

			DataSend(gObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
			gObjCalCharacter(aIndex);
			GCReFillSend(gObj->m_Index, gObj->MaxLife + gObj->AddLife, 0xFE, 0, gObj->iMaxShield + gObj->iAddShield);
			gObjSetBP(aIndex);
			GCManaSend(gObj->m_Index, gObj->MaxMana + gObj->AddMana, 0xFE, 0, gObj->MaxBP + gObj->AddBP);
			GCLevelUpMsgSend(gObj->m_Index, 0);

			return true;
		}
		case 0x02:
		{
			PMSG_STAT_UPDATE pMsg;

			PHeadSetB((LPBYTE)&pMsg, 0x2C, sizeof(PMSG_STAT_UPDATE));
			pMsg.result = 0;
			pMsg.btFruitType = 1;
			pMsg.btStatValue = Points;
			gObj->Vitality += Points;
			gObj->LevelUpPoint -= Points;
			gObj->MaxLife += gObj->VitalityToLife * Points;

			DataSend(gObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
			gObjCalCharacter(aIndex);
			GCReFillSend(gObj->m_Index, gObj->MaxLife + gObj->AddLife, 0xFE, 0, gObj->iMaxShield + gObj->iAddShield);
			gObjSetBP(aIndex);
			GCManaSend(gObj->m_Index, gObj->MaxMana + gObj->AddMana, 0xFE, 0, gObj->MaxBP + gObj->AddBP);
			GCLevelUpMsgSend(gObj->m_Index, 0);

			return true;
		}
		case 0x03:
		{
			PMSG_STAT_UPDATE pMsg;

			PHeadSetB((LPBYTE)&pMsg, 0x2C, sizeof(PMSG_STAT_UPDATE));
			pMsg.result = 0;
			pMsg.btFruitType = 0;
			pMsg.btStatValue = Points;
			gObj->Energy += Points;
			gObj->LevelUpPoint -= Points;
			gObj->MaxMana += gObj->EnergyToMana * Points;
			DataSend(gObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);

			gObjCalCharacter(aIndex);
			GCReFillSend(gObj->m_Index, gObj->MaxLife + gObj->AddLife, 0xFE, 0, gObj->iMaxShield + gObj->iAddShield);
			gObjSetBP(aIndex);
			GCManaSend(gObj->m_Index, gObj->MaxMana + gObj->AddMana, 0xFE, 0, gObj->MaxBP + gObj->AddBP);
			GCLevelUpMsgSend(gObj->m_Index, 0);

			return true;
		}
		case 0x04:
		{
			PMSG_STAT_UPDATE pMsg;

			PHeadSetB((LPBYTE)&pMsg, 0x2C, sizeof(PMSG_STAT_UPDATE));
			pMsg.result = 0;
			pMsg.btFruitType = 4;
			pMsg.btStatValue = Points;
			gObj->Leadership += Points;
			gObj->LevelUpPoint -= Points;

			DataSend(gObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
			gObjCalCharacter(aIndex);
			GCReFillSend(gObj->m_Index, gObj->MaxLife + gObj->AddLife, 0xFE, 0, gObj->iMaxShield + gObj->iAddShield);
			gObjSetBP(aIndex);
			GCManaSend(gObj->m_Index, gObj->MaxMana + gObj->AddMana, 0xFE, 0, gObj->MaxBP + gObj->AddBP);
			GCLevelUpMsgSend(gObj->m_Index, 0);

			return true;
		}
	}

	return true;
}

bool cChat::WareCommand(LPOBJ gObj, char *Msg)
{
	if(CheckCommand(gObj, Configs.Commands.IsMultyVault, GmSystem.NONE, Configs.Commands.ZenForChange, Configs.Commands.PcPointForChange, Configs.Commands.WCoinForChange, Configs.Commands.WebPointsForChange, 0, 1, 0, "Ware", "/ware <num>", Msg))
	{
		return true;
	}

	if (gObj->WarehouseSave != 0)
	{
		MessageLog(1, c_Red, t_COMMANDS, gObj, "[Ware] Feche seu bau antes!");

		return true;
	}

	int WantSlot;
	sscanf(Msg, "%d", &WantSlot);

	MuOnlineQuery.ExecQuery("SELECT UsedSlot FROM warehouse WHERE AccountID = '%s'", gObj->AccountID);
	MuOnlineQuery.Fetch();
	int UsedSlot = MuOnlineQuery.GetAsInteger("UsedSlot");
	MuOnlineQuery.Close();

	if(UsedSlot == NULL)
	{
		MuOnlineQuery.ExecQuery("UPDATE warehouse SET Items01 = Items, UsedSlot = 1 WHERE AccountID = '%s'", gObj->AccountID);
		MuOnlineQuery.Fetch();
		MuOnlineQuery.Close();
	}

	if (UsedSlot == -1 || UsedSlot == 0)
	{
		MessageLog(1, c_Red, t_COMMANDS, gObj, "[Ware] Command is broken, relog and try again!");

		return true;
	}

	if (WantSlot < 1 || WantSlot > Configs.Commands.NumberOfVaults)
	{
		MessageLog(1, c_Red, t_COMMANDS, gObj, "[Ware] You can use from 1 to %d vaults!", Configs.Commands.NumberOfVaults);

		return true;
	}

	if (UsedSlot == WantSlot)
	{
		MessageLog(1, c_Red, t_COMMANDS, gObj, "[Ware] You need to chose other vault number!");

		return true;
	}

	TakeCommand(gObj, Configs.Commands.ZenForChange, Configs.Commands.PcPointForChange, Configs.Commands.WCoinForChange, Configs.Commands.WebPointsForChange, "Ware");

	MuOnlineQuery.ExecQuery("UPDATE warehouse SET Items%02d = Items, Items = Items%02d, UsedSlot = %d WHERE AccountID = '%s'", UsedSlot, WantSlot, WantSlot, gObj->AccountID);
	MuOnlineQuery.Fetch();
	MuOnlineQuery.Close();

	MessageLog(1, c_Red, t_COMMANDS, gObj, "[Ware] You successfully change vault from %d to %d!", UsedSlot, WantSlot);
	return true;
}

bool cChat::AddMobCommand(LPOBJ gObj, char *Msg)
{
#ifdef _GS
	if(CheckCommand(gObj, 1, GmSystem.cSetZen, 0, 0, 0, 0, 0, 1, 0, "AddMob", "/mobadd <mobid> <count> <speed> <distance> <map> <x> <y>", Msg))
		return true;

	int Mob;
	int Map = gObj->MapNumber;
	int Speed = 10;
	int X1 = (int)gObj->X, X2 = (int)gObj->X;
	int Y1 = (int)gObj->Y, Y2 = (int)gObj->Y;
	int Dir = -1;
	int Count = 1;
	int Distance = 0;

	sscanf(Msg, "%d %d %d %d %d %d %d", &Mob, &Count, &Speed, &Distance, &Map, &X1, &Y1);

	FILE* AddMobFile;

	if((AddMobFile = fopen( IAJuliaMobAdd, "a+")) == NULL)
	{
		MessageBox(NULL, "Cant Find MonsterSpawn.ini", "Error", 0);
	}
	else
	{
		//ID, Count, Speed, Distance, Map, X, Y
		//Mob,Map,Speed,x1,y1,x2,y2,dir,count
		//17	9	30	119	80	150	115	-1	35 // Cyclops
		if(Count == 1)
		{
			Dir = gObj->Dir;
		}

		if(Distance > 0)
		{
			X1 -= Distance;
			Y1 -= Distance;
			X2 += Distance;
			Y2 += Distance;
		}

		fprintf(AddMobFile, "\n%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d", Mob, Map, Speed, X1, Y1, X2, Y2, Dir, Count);
		fclose(AddMobFile);
	}

	for(int i = 0; i < Count; i++)
	{
		Monster.MonsterAddAndSpawn(Mob, Map, Speed, X1, Y1, X2, Y2, Dir);
	}

	MessageLog(1, c_Red, t_COMMANDS, gObj, "[AddMob] %d Mob Successfully spawned (Map: %d, X: %d, Y: %d, MobID: %d)", Count,Map,X1,Y1, Mob);
#endif
	return true;
}

bool cChat::SetDropCommand(LPOBJ gObj, char *Msg, int Index)
{
	if (CheckCommand(gObj, Configs.Commands.IsDrop, GmSystem.cDrop, 0, 0, 0, 0, 0, 1, Index, "SetDrop", "[Name] /setdrop <ItemIndex> <ItemLvl> <ItemLuck> <ItemOpt> <ItemExc> <ItemAnc>", Msg))
	{
		return true;
	}

	int ItemIndex = 0;
	int ItemLevel = 0;
	int ItemLuck = 0;
	int ItemOpt = 0;
	int ItemExc = 0;
	int ItemAncient = 0;
	int ItemMin = 7;

	sscanf(Msg, "%d %d %d %d %d %d", &ItemIndex, &ItemLevel, &ItemLuck, &ItemOpt, &ItemExc, &ItemAncient);

	if(ItemIndex < 0 || (ItemLevel<0 || ItemLevel > 13) || (ItemOpt < 0 || ItemOpt > 7) || (ItemLuck < 0 || ItemLuck > 1) || (ItemExc < 0 || ItemExc > 63) || (ItemAncient < 0 || ItemAncient > 40))
	{
		MessageLog(1, c_Red, t_GM, gObj, "[SetDrop] Uso: /setdrop <ItemIndex> <ItemLvl> <ItemLuck> <ItemOpt> <ItemExc> <ItemAnc>");

		return true;
	}

	OBJECTSTRUCT *gUbj = (OBJECTSTRUCT*)OBJECT_POINTER(Index);

	for (int i = ItemMin; i < 12; i++)
	{
		int Item = i * 512 + ItemIndex;
		int Rand1 = rand() % 3;
		int Rand2 = rand() % 3;
		ItemSerialCreateSend(gUbj->m_Index, gUbj->MapNumber, (int)gUbj->X + Rand1, (int)gUbj->Y + Rand2, Item, ItemLevel, 0, 0, ItemLuck, ItemOpt, gUbj->m_Index, ItemExc, ItemAncient);
	}

	if (gObj == gUbj)
	{
		MessageLog(1, c_Red, t_GM, gObj, "[SetDrop] Item Created %d %d %d %d %d %d - Success", ItemIndex, ItemLevel, ItemLuck, ItemOpt, ItemExc, ItemAncient);
	}
	else
	{
		MessageLog(1, c_Red, t_GM, gObj, "[SetDrop] Items Created to %s %d %d %d %d %d %d - Success", gUbj->Name, ItemIndex, ItemLevel, ItemLuck, ItemOpt, ItemExc, ItemAncient);
		Message(1, gUbj, "[SetDrop] You lucked by %s with items! Take them faster!", gObj->Name);
	}

	return true;
}

bool cChat::CheckCommand(LPOBJ gObj, char *Msg)
{
	if (PCPoint.Config.WebEnabled)
	{
		if(PCPoint.Config.WebColumnFloat)
		{
			MessageLog(1, c_Red, t_GM, gObj, "[Check] PCPoints: %d, WCoins %d, WebPoints %.2f", AddTab[gObj->m_Index].PC_PlayerPoints, gObj->m_wCashPoint, AddTab[gObj->m_Index].WEB_Points_Float);
		}
		else
		{
			MessageLog(1, c_Red, t_GM, gObj, "[Check] PCPoints: %d, WCoins %d, WebPoints %d", AddTab[gObj->m_Index].PC_PlayerPoints, gObj->m_wCashPoint, AddTab[gObj->m_Index].WEB_Points);
		}
	}
	else
	{
		MessageLog(1, c_Red, t_GM, gObj, "[Check] PCPoints: %d, WCoins %d", AddTab[gObj->m_Index].PC_PlayerPoints, gObj->m_wCashPoint);
	}

	return true;
}

bool cChat::CheckVIPCommand(LPOBJ gObj, char *Msg)
{
	if (CheckCommand(gObj, Vip.Config.Enabled, GmSystem.NONE, 0, 0, 0, 0, 0, 0, 0, "VipCheck", COMMAND_VIPCHECK, Msg))
	{
		return true;
	}

	if(AddTab[gObj->m_Index].VIP_Type > 0)
	{
		MessageLog(1, c_Red, t_VIP, gObj, "[VIP] You have %d min(s) left.", AddTab[gObj->m_Index].VIP_Min);
	}
	else
	{
		MessageLog(1, c_Red, t_VIP, gObj, "[VIP] You haven't bought VIP yet.");
	}

	return true;
}

bool cChat::CheckTerritoryCommand(LPOBJ gObj, char *Msg)
{
	if (CheckCommand(gObj, Territory.Config.Enabled, GmSystem.NONE, 0, 0, 0, 0, 0, 0, 0, "TerritoryCheck", COMMAND_TERRCHECK, Msg))
	{
		return true;
	}

	if (AddTab[gObj->m_Index].TERR_Type > 0)
	{
		MessageLog(1, c_Red, t_TERRITORY, gObj, "[Territory] You have %d min(s) left of %s territory.", AddTab[gObj->m_Index].TERR_Min, Territory.Config.Terr[AddTab[gObj->m_Index].TERR_Type].Name);
	}
	else
	{
		MessageLog(1, c_Red, t_TERRITORY, gObj, "[Territory] You haven't bought any territory.");
	}

	return true;
}

bool cChat::BuyTerritoryCommand(LPOBJ gObj, char *Msg)
{
	if (CheckCommand(gObj, Territory.Config.Enabled, GmSystem.NONE, 0, 0, 0, 0, 0, 1, 0, "Territory", "/terrbuy <territory> <hours>", Msg))
	{
		return true;
	}

	int Terr = 0, Hours = 1;
	char tName[11] = { 0 };
	sscanf(Msg, "%10s %d", &tName, &Hours);

	for (int i = 1; i <= Territory.Config.NumOfTerritorys; i++)
	{
		if (!_strcmpi(tName, Territory.Config.Terr[i].Name))
		{
			Terr = i;
			break;
		}
	}

	if (Terr < 1 || Terr > Territory.Config.NumOfTerritorys)
	{
		MessageLog(1, c_Red, t_TERRITORY, gObj, "[Territory] There is no such territory name.");
		return true;
	}

	if (AddTab[gObj->m_Index].TERR_Type > 0 || AddTab[gObj->m_Index].TERR_Min > 0)
	{
		if (Territory.Config.AllowRebuying)
		{
			if (AddTab[gObj->m_Index].TERR_Type != Terr)
			{
				MessageLog(1, c_Red, t_TERRITORY, gObj, "[Territory] You have already %s territory, can't buy another.", Territory.Config.Terr[AddTab[gObj->m_Index].TERR_Type].Name);
				return true;
			}
		}
		else
		{
			MessageLog(1, c_Red, t_TERRITORY, gObj, "[Territory] You have already bought Territory.");
			return true;
		}
	}

	if (Hours < Territory.Config.Terr[Terr].MinHours || Hours > Territory.Config.Terr[Terr].MaxHours)
	{
		MessageLog(1, c_Red, t_TERRITORY, gObj, "[Territory] You can't buy less then %d and more than %d hours.", Territory.Config.Terr[Terr].MinHours, Territory.Config.Terr[Terr].MaxHours);
		return true;
	}

	if (Territory.CheckPlayer(Terr) >= Territory.Config.Terr[Terr].MaxPlayers)
	{
		MessageLog(1, c_Red, t_TERRITORY, gObj, "[Territory] You are too late, this territory are bought.");
		return true;
	}

	if (Territory.Config.Terr[Terr].OnlyForMasterLvl && gObj->ChangeUP2 == 0)
	{
		MessageLog(1, c_Red, t_TERRITORY, gObj, "[Territory] You aren't Master to buy territory.");
		return true;
	}

	if (Territory.Config.Terr[Terr].MinReset > AddTab[gObj->m_Index].Resets)
	{
		MessageLog(1, c_Red, t_TERRITORY, gObj, "[Territory] You are low reset to buy territory.");
		return true;
	}

	if (CheckCommand(gObj, Territory.Config.Enabled, GmSystem.NONE, Territory.Config.Terr[Terr].CostZen * Hours,
		Territory.Config.Terr[Terr].CostPCPoint * Hours, Territory.Config.Terr[Terr].CostWCoin * Hours, Territory.Config.Terr[Terr].CostWebPoints * Hours, Territory.Config.Terr[Terr].MinLvl, 1, 0, "Territory", "/terrbuy <territory> <hours>", Msg))
		return true;

	TakeCommand(gObj, Territory.Config.Terr[Terr].CostZen * Hours, Territory.Config.Terr[Terr].CostPCPoint * Hours,
		Territory.Config.Terr[Terr].CostWCoin * Hours, Territory.Config.Terr[Terr].CostWebPoints * Hours, "Territory");

	MuOnlineQuery.ExecQuery("UPDATE Character SET Territory_Time = (Territory_Time + %d), Territory_Type = %d WHERE Name = '%s'", Hours * 60, Terr, gObj->Name);
	MuOnlineQuery.Fetch();
	MuOnlineQuery.Close();

	AddTab[gObj->m_Index].TERR_Min += Hours * 60;
	AddTab[gObj->m_Index].TERR_Type = Terr;

	MessageLog(1, c_Red, t_TERRITORY, gObj, "[Territory] Successfully bought %s territory for %d Hour(s)", Territory.Config.Terr[Terr].Name, Hours);
	return true;
}

bool cChat::VIPListCommand(LPOBJ gObj, char *Msg)
{
	if (CheckCommand(gObj, Vip.Config.Enabled, GmSystem.NONE, 0, 0, 0, 0, 0, 0, 0, "VipList", COMMAND_VIPLIST, Msg))
		return true;

	for (int i = 1; i <= Vip.Config.NumStates; i++)
	{
		MessageLog(1, c_Red, t_VIP, gObj, "[VipList] %s - %d PCPnt, %d WCn, %d Zen, %d hours min, %d - max",
			Vip.Config.VIPState[i].VIPName, Vip.Config.VIPState[i].CostPCPoints,
			Vip.Config.VIPState[i].CostWCoins, Vip.Config.VIPState[i].CostZen,
			Vip.Config.VIPState[i].MinHours, Vip.Config.VIPState[i].MaxHours);
	}
	return true;
}

bool cChat::BuyVIPCommand(LPOBJ gObj, char *Msg)
{
	if (CheckCommand(gObj, Vip.Config.Enabled, GmSystem.NONE, 0, 0, 0, 0, 0, 1, 0, "VIPBuy", "/vipbuy <state> <hours>", Msg))
		return true;

	int Hours = 1;
	char State[255] = { 0 };
	sscanf(Msg, "%254s %d", &State, &Hours);

	int RealState = -1;
	for (int i = 1; i <= Vip.Config.NumStates; i++)
	{
		if (!_strcmpi(State, Vip.Config.VIPState[i].VIPName))
		{
			RealState = i;
			break;
		}
	}

	if (AddTab[gObj->m_Index].VIP_Type > 0 || AddTab[gObj->m_Index].VIP_Min > 0)
	{
		if (Vip.Config.AllowRebuying)
		{
			if (AddTab[gObj->m_Index].VIP_Type != RealState)
			{
				MessageLog(1, c_Red, t_VIP, gObj, "[VIPBuy] You can't buy another type of vip.");
				return true;
			}
		}
		else
		{
			MessageLog(1, c_Red, t_VIP, gObj, "[VIPBuy] You have already bought VIP.");
			return true;
		}
	}

	if (RealState == -1)
	{
		MessageLog(1, c_Red, t_VIP, gObj, "[VIP] There are no such vip status.");
		return true;
	}
	if (!Vip.Config.VIPState[RealState].EnabledCmd)
	{
		MessageLog(1, c_Red, t_VIP, gObj, "[VIP] You can't buy %s vip status.", Vip.Config.VIPState[RealState].VIPName);
		return true;
	}
	if (Hours < Vip.Config.VIPState[RealState].MinHours || Hours > Vip.Config.VIPState[RealState].MaxHours)
	{
		MessageLog(1, c_Red, t_VIP, gObj, "[VIP] You can't buy less then %d and more than %d hours.", Vip.Config.VIPState[RealState].MinHours, Vip.Config.VIPState[RealState].MaxHours);
		return true;
	}

	if (CheckCommand(gObj, Vip.Config.VIPState[RealState].EnabledCmd, GmSystem.NONE, Vip.Config.VIPState[RealState].CostZen * Hours,
		Vip.Config.VIPState[RealState].CostPCPoints * Hours, Vip.Config.VIPState[RealState].CostWCoins * Hours, Vip.Config.VIPState[RealState].CostWebPoints * Hours, 0, 1, 0, "VIPBuy", "/vipbuy <state> <hours>", Msg))
		return true;

	TakeCommand(gObj, Vip.Config.VIPState[RealState].CostZen * Hours, Vip.Config.VIPState[RealState].CostPCPoints * Hours,
		Vip.Config.VIPState[RealState].CostWCoins * Hours, Vip.Config.VIPState[RealState].CostWebPoints * Hours, "BuyVIP");

	MuOnlineQuery.ExecQuery("UPDATE %s SET %s = (%s + %d), %s = %d WHERE Name = '%s'", Vip.Config.Table, Vip.Config.ColumnDate, Vip.Config.ColumnDate, Hours * 60, Vip.Config.Column, RealState, gObj->Name);
	MuOnlineQuery.Fetch();
	MuOnlineQuery.Close();

	AddTab[gObj->m_Index].VIP_Min += Hours * 60;
	AddTab[gObj->m_Index].VIP_Type = RealState;

	MessageLog(1, c_Red, t_VIP, gObj, "[VIPBuy] Successfully bought %s for %d Hour(s)", Vip.Config.VIPState[RealState].VIPName, Hours);
	MessageLog(1, c_Red, t_VIP, gObj, "[VIPBuy] Your VIP status starts right now!");
	return true;
}

bool cChat::GuildPost(LPOBJ gObj, char *Msg)
{
	if (gObj->GuildStatus == 128 || gObj->GuildStatus == 64)
	{
		GDGuildNoticeSave(gObj->GuildName, Msg);
	}
	else
	{
		MessageLog(1, c_Red, t_Default, gObj, "You aren't guild master or assistant");
	}

	return true;
}

bool cChat::SetZenCommand(LPOBJ gObj, char* Msg, int Index)
{
	if(CheckCommand(gObj, Configs.Commands.IsSetZen, GmSystem.cSetZen, 0, 0, 0, 0, 0, 1, Index, "SetZen", "[Name] /setzen <Zen>", Msg))
	{
		return true;
	}

	DWORD Zen = 0;

	sscanf(Msg, "%d", &Zen);

	if(Zen <= 0 || Zen > 2000000000)
	{
		MessageLog(1, c_Red, t_GM, gObj, "[SetZen] Nao pode ser menor do que 1 e mais do que 2000000000!");

		return true;
	}

	OBJECTSTRUCT *tObj = (OBJECTSTRUCT*)OBJECT_POINTER(Index);

	tObj->Money = Zen;
	GCMoneySend(tObj->m_Index, Zen);

	if (gObj == tObj)
	{
		MessageLog(1, c_Red, t_GM, tObj, "[SetZen] Zen adiquirido!");
	}
	else
	{
		MessageLog(1, c_Red, t_GM, gObj, "[SetZen] Voce alterou o zen do char %s com sucesso.", tObj->Name);
		MessageLog(1, c_Red, t_GM, tObj, "[SetZen] O seu Zen foi alterado por %s!", gObj->Name);
	}

	return true;
}

bool cChat::VipOnCommand(LPOBJ gObj)
{
	if (CheckCommand(gObj, Vip.Config.Enabled, GmSystem.NONE, 0, 0, 0, 0, 0, 0, 0, "VipON", COMMAND_VIP_ON, ""))
	{
		return true;
	}

	if (AddTab[gObj->m_Index].VIP_Type <= 0)
	{
		MessageLog(1, c_Red, t_VIP, gObj, "[VipOn] You don't have vip status.");

		return true;
	}

	if (AddTab[gObj->m_Index].VIP_Min <= 0)
	{
		MessageLog(1, c_Red, t_VIP, gObj, "[VipOn] Your vip status ended.");

		return true;
	}

	if (AddTab[gObj->m_Index].VIP_On)
	{
		MessageLog(1, c_Red, t_VIP, gObj, "[VipOn] Your vip time is ticking.");

		return true;
	}

	int i = AddTab[gObj->m_Index].VIP_Type;

	if (Vip.Config.VIPState[i].EnableOnOff == 0)
	{
		MessageLog(1, c_Red, t_VIP, gObj, "[VipOn] Your can't use Vip On with this VIP type.");

		return true;
	}

	MuOnlineQuery.ExecQuery("UPDATE %s SET VIP_ONOFF = 1 WHERE Name = '%s'", Vip.Config.Table, gObj->Name);
	MuOnlineQuery.Fetch();
	MuOnlineQuery.Close();

	AddTab[gObj->m_Index].VIP_On = 1;

	MessageLog(1, c_Red, t_VIP, gObj, "[VipOn] Your %s vip starts right now!", Vip.Config.VIPState[i].VIPName);
	MessageLog(1, c_Red, t_VIP, gObj, "[VipOn] You have left %d mins!", AddTab[gObj->m_Index].VIP_Min);

	return true;
}

bool cChat::VipOffCommand(LPOBJ gObj)
{
	if (CheckCommand(gObj, Vip.Config.Enabled, GmSystem.NONE, 0, 0, 0, 0, 0, 0, 0, "VipOff", COMMAND_VIP_OFF, ""))
		return true;

	if (AddTab[gObj->m_Index].VIP_Type <= 0)
	{
		MessageLog(1, c_Red, t_VIP, gObj, "[VipOff] You don't have vip status.");
		return true;
	}

	if (AddTab[gObj->m_Index].VIP_Min <= 0)
	{
		MessageLog(1, c_Red, t_VIP, gObj, "[VipOff] Your vip status ended.");
		return true;
	}

	if (AddTab[gObj->m_Index].VIP_On == 0)
	{
		MessageLog(1, c_Red, t_VIP, gObj, "[VipOff] Your vip is disabled.");
		return true;
	}

	if (MoveReq.GetMapVip(gObj->MapNumber) > 0)
	{
		MessageLog(1, c_Red, t_VIP, gObj, "[VipOff] You can't vip off on VIP map!");
		return true;
	}

	int i = AddTab[gObj->m_Index].VIP_Type;

	if (Vip.Config.VIPState[i].EnableOnOff == 0)
	{
		MessageLog(1, c_Red, t_VIP, gObj, "[VipOff] Your can't use Vip Off with this VIP type.");
		return true;
	}

	MuOnlineQuery.ExecQuery("UPDATE %s SET VIP_ONOFF = 0 WHERE Name = '%s'", Vip.Config.Table, gObj->Name);
	MuOnlineQuery.Fetch();
	MuOnlineQuery.Close();

	AddTab[gObj->m_Index].VIP_On = 0;

	MessageLog(1, c_Red, t_VIP, gObj, "[VipOff] Your %s vip stoped!", Vip.Config.VIPState[i].VIPName);

	return true;
}

bool cChat::DisableChatCommand(LPOBJ gObj, char *Msg, int Index)
{
	if (CheckCommand(gObj, 1, GmSystem.cDisableChat, 0, 0, 0, 0, 0, 0, Index, "DisableChat", "[Name] /disablechat", Msg))
	{
		return true;
	}

	OBJECTSTRUCT *tObj = (OBJECTSTRUCT*)OBJECT_POINTER(Index);

	MuOnlineQuery.ExecQuery("UPDATE Character SET BanChat = 1 WHERE Name = '%s'", tObj->Name);
	MuOnlineQuery.Fetch();
	MuOnlineQuery.Close();

	tObj->Penalty |= 2;

	MessageLog(1, c_Red, t_BAN, gObj, "[DisableChat] %s chat banido.", tObj->Name);
	MessageLog(1, c_Red, t_BAN, tObj, "[DisableChat] O seu chat foi desativado por %s.", gObj->Name);

	return true;
}

bool cChat::EnableChatCommand(LPOBJ gObj, int Index)
{
	if (CheckCommand(gObj, 1, GmSystem.cDisableChat, 0, 0, 0, 0, 0, 0, Index, "EnableChat", "[Name] /enablechat", ""))
		return true;

	OBJECTSTRUCT *tObj = (OBJECTSTRUCT*)OBJECT_POINTER(Index);

	MuOnlineQuery.ExecQuery("UPDATE Character SET BanChat = 0 WHERE Name = '%s'", tObj->Name);
	MuOnlineQuery.Fetch();
	MuOnlineQuery.Close();

	tObj->Penalty &= ~2;

	MessageLog(1, c_Red, t_BAN, gObj, "[EnableChat] %s chat liberado.", tObj->Name);
	MessageLog(1, c_Red, t_BAN, tObj, "[EnableChat] O seu chat foi ativado por %s!", gObj->Name);

	return true;
}

bool cChat::OffTradeCommand(LPOBJ gObj)
{
#ifdef _GS
	if(CheckCommand(gObj, OfflineTrade.Configs.Enabled, GmSystem.NONE, OfflineTrade.Configs.PriceZen, 0, 0, 0, OfflineTrade.Configs.LevelReq, 0, 0, "OffTrade", "/off", ""))
	{
		return true;
	}

	if(gObj->m_bPShopOpen == false)
	{
		MessageLog(1, c_Red, t_COMMANDS, gObj, "[OffTrade] Abra o Personal SHOP antes.");

		return false;
	}

	if(gObj->MapNumber != 0)
	{
		MessageLog(1, c_Red, t_COMMANDS, gObj, "[OffTrade] Voce so pode usar o Offtrade em Lorencia.");
		return false;
	}

	TakeCommand(gObj,  OfflineTrade.Configs.PriceZen, 0, 0, 0, "OffTrade");
	OfflineTrade.CreateOfflineStore(gObj->m_Index);
#endif
	return true;
}

void ExchangeHighToLow(LPOBJ gObj, int Type, int Buy, char*KindOfSell, char*KindOfBuy, int SellKind, int BuyKind, int ConfigBuy, int MaxBuy)
{
	if (Buy % ConfigBuy != 0)
	{
		if (Buy > ConfigBuy)
		{
			DWORD Min = Buy - (Buy % ConfigBuy);
			DWORD Max = Min + ConfigBuy;
			Chat.MessageLog(1, c_Red, t_NULL, gObj, "[Exchanger] You write not right value. Write %d or %d.", Min, Max);
			return;
		}
		else
		{
			Chat.MessageLog(1, c_Red, t_NULL, gObj, "[Exchanger] You write not right value. Write %d.", ConfigBuy);

			return;
		}
	}

	int NeededToSell = (Buy / ConfigBuy);
	if (SellKind < NeededToSell)
	{
		Chat.MessageLog(1, c_Red, t_NULL, gObj, "[Exchanger] You don't have enough %s. %d more need.", KindOfSell, NeededToSell - SellKind);

		return;
	}
	if (BuyKind + Buy > MaxBuy)
	{
		Chat.MessageLog(1, c_Red, t_NULL, gObj, "[Exchanger] You can't buy more %s.", KindOfBuy);

		return;
	}

	DWORD ConfigTax = Configs.Commands.ExchangeTax;
	float temp = (float)(Buy / 100)*ConfigTax;
	DWORD Tax = ceil(temp);

	DWORD Sell = Buy / ConfigBuy;
	DWORD Final = Buy - Tax;

	switch (Type)
	{
	case 1:
		{
			PCPoint.UpdatePoints(gObj, Final, PLUS, PCPOINT);
			PCPoint.UpdatePoints(gObj, Sell, MINUS, WCOIN);

			break;
		}
	case 2:
		{
			PCPoint.UpdatePoints(gObj, Final, PLUS, WEBPOINTS);
			PCPoint.UpdatePoints(gObj, Sell, MINUS, WCOIN);

			break;
		}
	case 3:
		{

			gObj->Money += Final;
			GCMoneySend(gObj->m_Index, gObj->Money);
			PCPoint.UpdatePoints(gObj, Sell, MINUS, WCOIN);

			break;
		}
	case 5:
		{
			PCPoint.UpdatePoints(gObj, Final, PLUS, PCPOINT);
			PCPoint.UpdatePoints(gObj, Sell, MINUS, WEBPOINTS);

			break;
		}
	case 6:
		{
			gObj->Money += Final;
			GCMoneySend(gObj->m_Index, gObj->Money);
			PCPoint.UpdatePoints(gObj, Sell, MINUS, WEBPOINTS);

			break;
		}
	case 7:
		{
			gObj->Money += Final;
			GCMoneySend(gObj->m_Index, gObj->Money);
			PCPoint.UpdatePoints(gObj, Sell, MINUS, PCPOINT);

			break;
		}
	}

	Chat.MessageLog(1, c_Yellow, t_NULL, gObj, "[Exchanger] You buy %d %s for %d %s! Thx you!", Final, KindOfBuy, Sell, KindOfSell);
}

void ExchangeLowToHigh(LPOBJ gObj, int Type, int Buy, char*KindOfSell, char*KindOfBuy, int SellKind, int BuyKind, int ConfigBuy, int MaxBuy)
{
	int NeededToSell = (Buy * ConfigBuy);

	if (SellKind < NeededToSell)
	{
		Chat.MessageLog(1, c_Red, t_NULL, gObj, "[Exchanger] You don't have enough %s. %d more need.", KindOfSell, NeededToSell - SellKind);
		return;
	}

	if (BuyKind + Buy > MaxBuy)
	{
		Chat.MessageLog(1, c_Red, t_NULL, gObj, "[Exchanger] You can't buy more %s.", KindOfBuy);
		return;
	}

	DWORD ConfigTax = Configs.Commands.ExchangeTax;
	DWORD Tax = ((NeededToSell / 100)*ConfigTax);
	DWORD Final = NeededToSell + Tax;

	if (Final >= 2000000000 || Final <= 0)
	{
		Chat.MessageLog(1, c_Red, t_NULL, gObj, "[Exchanger] To more, to exchange.", KindOfBuy);
		return;
	}

	switch (Type)
	{
	case 4:
		{
			PCPoint.UpdatePoints(gObj, Buy, PLUS, WCOIN);
			PCPoint.UpdatePoints(gObj, Final, MINUS, WEBPOINTS);

			break;
		}
	case 8:
		{
			PCPoint.UpdatePoints(gObj, Buy, PLUS, WCOIN);
			PCPoint.UpdatePoints(gObj, Final, MINUS, PCPOINT);

			break;
		}
	case 9:
		{
			PCPoint.UpdatePoints(gObj, Buy, PLUS, WEBPOINTS);
			PCPoint.UpdatePoints(gObj, Final, MINUS, PCPOINT);

			break;
		}
	case 10:
		{
			PCPoint.UpdatePoints(gObj, Buy, PLUS, WCOIN);
			gObj->Money -= Final;
			GCMoneySend(gObj->m_Index, gObj->Money);

			break;
		}
	case 11:
		{
			PCPoint.UpdatePoints(gObj, Buy, PLUS, PCPOINT);
			gObj->Money -= Final;
			GCMoneySend(gObj->m_Index, gObj->Money);

			break;
		}
	case 12:
		{
			PCPoint.UpdatePoints(gObj, Buy, PLUS, WEBPOINTS);
			gObj->Money -= Final;
			GCMoneySend(gObj->m_Index, gObj->Money);

			break;
		}
	}

	Chat.MessageLog(1, c_Yellow, t_NULL, gObj, "[Exchanger] You buy %d %s for %d %s! Thx you!", Buy, KindOfBuy, Final, KindOfSell);
}

bool cChat::ExchangeCommands(LPOBJ gObj, char *Msg, int Type)
{
	if (!Configs.Commands.ExchangeCommands)
	{
		MessageLog(1, c_Red, t_COMMANDS, gObj, "[Exchanger] Funcao temporariamente inativa.");

		return true;
	}

	switch (Type)
	{
	case 1:// wcoin-pcpoint >
		{
			if(CheckCommand(gObj, Configs.Commands.ExchangeWcPp, GmSystem.NONE, 0, 0, 0, 0, Configs.Commands.ExchangeMinLvl, 1, 0, "Exchanger", "/wcoin-pcpoint <num>", Msg))
			{
				return true;
			}

			DWORD Buy;
			int SellKind = gObj->m_wCashPoint;
			int BuyKind = AddTab[gObj->m_Index].PC_PlayerPoints;
			sscanf(Msg, "%d", &Buy);

			DWORD ConfigBuy = Configs.Commands.WCoin_PcPoint;
			DWORD MaxBuy = PCPoint.Config.MaximumPCPoints;

			char KindOfSell[] = "WCoin";
			char KindOfBuy[] = "PCPoints";

			ExchangeHighToLow(gObj, Type, Buy, KindOfSell, KindOfBuy, SellKind, BuyKind, ConfigBuy, MaxBuy);

			return true;
		}
		break;
	case 2: // wcoin-webpoint >
		{
			if (CheckCommand(gObj, Configs.Commands.ExchangeWcWp, GmSystem.NONE, 0, 0, 0, 0, Configs.Commands.ExchangeMinLvl, 1, 0, "Exchanger", "/wcoin-webpoint <num>", Msg))
			{
				return true;
			}

			DWORD Buy;
			int SellKind = gObj->m_wCashPoint;
			int BuyKind;

			if (PCPoint.Config.WebColumnFloat)
			{
				BuyKind = (int)ceil(AddTab[gObj->m_Index].WEB_Points_Float);
			}
			else
			{
				BuyKind = AddTab[gObj->m_Index].WEB_Points;
			}

			sscanf(Msg, "%d", &Buy);

			DWORD ConfigBuy = Configs.Commands.WCoin_WebPoint;
			DWORD MaxBuy = PCPoint.Config.MaximumWebPoints;

			char KindOfSell[] = "WCoin";
			char KindOfBuy[] = "WebPoints";

			ExchangeHighToLow(gObj, Type, Buy, KindOfSell, KindOfBuy, SellKind, BuyKind, ConfigBuy, MaxBuy);

			return true;
		}
		break;
	case 3: // wcoin-zen >
		{
			if (CheckCommand(gObj, Configs.Commands.ExchangeWcZen, GmSystem.NONE, 0, 0, 0, 0, Configs.Commands.ExchangeMinLvl, 1, 0, "Exchanger", "/wcoin-zen <num>", Msg))
				return true;

			DWORD Buy;
			int SellKind = gObj->m_wCashPoint;
			int BuyKind = gObj->Money;
			sscanf(Msg, "%d", &Buy);

			DWORD ConfigBuy = Configs.Commands.WCoin_Zen;
			DWORD MaxBuy = 2000000000;

			char KindOfSell[] = "WCoin";
			char KindOfBuy[] = "Zen";

			ExchangeHighToLow(gObj, Type, Buy, KindOfSell, KindOfBuy, SellKind, BuyKind, ConfigBuy, MaxBuy);

			return true;
		}
		break;
	case 4: // webpoint-wcoin <
		{
			if (CheckCommand(gObj, Configs.Commands.ExchangeWpWc, GmSystem.NONE, 0, 0, 0, 0, Configs.Commands.ExchangeMinLvl, 1, 0, "Exchanger", "/webpoint-wcoin <num>", Msg))
				return true;

			DWORD Buy;
			int SellKind;

			if (PCPoint.Config.WebColumnFloat)
			{
				SellKind = (int)ceil(AddTab[gObj->m_Index].WEB_Points_Float);
			}
			else
			{
				SellKind = AddTab[gObj->m_Index].WEB_Points;
			}

			int BuyKind = gObj->m_wCashPoint;
			sscanf(Msg, "%d", &Buy);

			DWORD ConfigBuy = Configs.Commands.WCoin_WebPoint;
			DWORD MaxBuy = PCPoint.Config.MaximumWCPoints;

			char KindOfSell[] = "WebPoints";
			char KindOfBuy[] = "WCoin";

			ExchangeLowToHigh(gObj, Type, Buy, KindOfSell, KindOfBuy, SellKind, BuyKind, ConfigBuy, MaxBuy);

			return true;
		}
		break;
	case 5: // webpoint-pcpoint >
		{
			if (CheckCommand(gObj, Configs.Commands.ExchangeWpPp, GmSystem.NONE, 0, 0, 0, 0, Configs.Commands.ExchangeMinLvl, 1, 0, "Exchanger", "/webpoint-pcpoint <num>", Msg))
				return true;

			DWORD Buy;
			int SellKind;

			if (PCPoint.Config.WebColumnFloat)
				SellKind = (int)ceil(AddTab[gObj->m_Index].WEB_Points_Float);
			else
				SellKind = AddTab[gObj->m_Index].WEB_Points;

			int BuyKind = AddTab[gObj->m_Index].PC_PlayerPoints;
			sscanf(Msg, "%d", &Buy);

			DWORD ConfigBuy = Configs.Commands.WebPoint_PcPoint;
			DWORD MaxBuy = PCPoint.Config.MaximumPCPoints;

			char KindOfSell[] = "WebPoints";
			char KindOfBuy[] = "PCPoints";

			ExchangeHighToLow(gObj, Type, Buy, KindOfSell, KindOfBuy, SellKind, BuyKind, ConfigBuy, MaxBuy);

			return true;
		}
		break;
	case 6: // webpoint-zen >
		{
			if(CheckCommand(gObj, Configs.Commands.ExchangeWpZen, GmSystem.NONE, 0, 0, 0, 0, Configs.Commands.ExchangeMinLvl, 1, 0, "Exchanger", "/webpoint-zen <num>", Msg))
			{
				return true;
			}

			DWORD Buy;
			int SellKind;

			if (PCPoint.Config.WebColumnFloat)
			{
				SellKind = (int)ceil(AddTab[gObj->m_Index].WEB_Points_Float);
			}
			else
			{
				SellKind = AddTab[gObj->m_Index].WEB_Points;
			}

			int BuyKind = gObj->Money;
			sscanf(Msg, "%d", &Buy);

			DWORD ConfigBuy = Configs.Commands.WebPoint_Zen;
			DWORD MaxBuy = 2000000000;

			char KindOfSell[] = "WebPoints";
			char KindOfBuy[] = "Zen";

			ExchangeHighToLow(gObj, Type, Buy, KindOfSell, KindOfBuy, SellKind, BuyKind, ConfigBuy, MaxBuy);

			return true;
		}
		break;
	case 7: // pcpoint-zen >
		{
			if (CheckCommand(gObj, Configs.Commands.ExchangePpZen, GmSystem.NONE, 0, 0, 0, 0, Configs.Commands.ExchangeMinLvl, 1, 0, "Exchanger", "/pcpoint-zen <num>", Msg))
			{
				return true;
			}

			DWORD Buy;
			int SellKind = AddTab[gObj->m_Index].PC_PlayerPoints;
			int BuyKind = gObj->Money;
			sscanf(Msg, "%d", &Buy);

			DWORD ConfigBuy = Configs.Commands.PcPoint_Zen;
			DWORD MaxBuy = 2000000000;

			char KindOfSell[] = "PcPoints";
			char KindOfBuy[] = "Zen";

			ExchangeHighToLow(gObj, Type, Buy, KindOfSell, KindOfBuy, SellKind, BuyKind, ConfigBuy, MaxBuy);

			return true;
		}
		break;
	case 8: // pcpoint-wcoin <
		{
			if (CheckCommand(gObj, Configs.Commands.ExchangePpWc, GmSystem.NONE, 0, 0, 0, 0, Configs.Commands.ExchangeMinLvl, 1, 0, "Exchanger", "/pcpoint-wcoin <num>", Msg))
				return true;

			DWORD Buy;
			int SellKind = AddTab[gObj->m_Index].PC_PlayerPoints;
			int BuyKind = gObj->m_wCashPoint;
			sscanf(Msg, "%d", &Buy);

			DWORD ConfigBuy = Configs.Commands.WCoin_PcPoint;
			DWORD MaxBuy = PCPoint.Config.MaximumWCPoints;

			char KindOfSell[] = "PcPoints";
			char KindOfBuy[] = "WCoin";

			ExchangeLowToHigh(gObj, Type, Buy, KindOfSell, KindOfBuy, SellKind, BuyKind, ConfigBuy, MaxBuy);

			return true;
		}
		break;
	case 9: // pcpoint-webpoint <
		{
			if (CheckCommand(gObj, Configs.Commands.ExchangePpWp, GmSystem.NONE, 0, 0, 0, 0, Configs.Commands.ExchangeMinLvl, 1, 0, "Exchanger", "/pcpoint-webpoint <num>", Msg))
				return true;

			DWORD Buy;
			int SellKind = AddTab[gObj->m_Index].PC_PlayerPoints;
			int BuyKind;

			if (PCPoint.Config.WebColumnFloat)
				BuyKind = (int)ceil(AddTab[gObj->m_Index].WEB_Points_Float);
			else
				BuyKind = AddTab[gObj->m_Index].WEB_Points;

			sscanf(Msg, "%d", &Buy);

			DWORD ConfigBuy = Configs.Commands.WebPoint_PcPoint;
			DWORD MaxBuy = PCPoint.Config.MaximumWebPoints;

			char KindOfSell[] = "PcPoints";
			char KindOfBuy[] = "WebPoints";

			ExchangeLowToHigh(gObj, Type, Buy, KindOfSell, KindOfBuy, SellKind, BuyKind, ConfigBuy, MaxBuy);

			return true;
		}
		break;
	case 10: // zen-wcoin <
		{
			if (CheckCommand(gObj, Configs.Commands.ExchangeZenWc, GmSystem.NONE, 0, 0, 0, 0, Configs.Commands.ExchangeMinLvl, 1, 0, "Exchanger", "/zen-wcoin <num>", Msg))
				return true;

			DWORD Buy;
			int SellKind = gObj->Money;
			int BuyKind = gObj->m_wCashPoint;
			sscanf(Msg, "%d", &Buy);

			DWORD ConfigBuy = Configs.Commands.WCoin_Zen;
			DWORD MaxBuy = PCPoint.Config.MaximumWCPoints;

			char KindOfSell[] = "Zen";
			char KindOfBuy[] = "WCoin";

			ExchangeLowToHigh(gObj, Type, Buy, KindOfSell, KindOfBuy, SellKind, BuyKind, ConfigBuy, MaxBuy);
			return true;
		}
		break;
	case 11: // zen-pcpoint <
		{
			if (CheckCommand(gObj, Configs.Commands.ExchangeZenPp, GmSystem.NONE, 0, 0, 0, 0, Configs.Commands.ExchangeMinLvl, 1, 0, "Exchanger", "/zen-pcpoint <num>", Msg))
				return true;

			DWORD Buy;
			int SellKind = gObj->Money;
			int BuyKind = AddTab[gObj->m_Index].PC_PlayerPoints;
			sscanf(Msg, "%d", &Buy);

			DWORD ConfigBuy = Configs.Commands.PcPoint_Zen;
			DWORD MaxBuy = PCPoint.Config.MaximumPCPoints;

			char KindOfSell[] = "Zen";
			char KindOfBuy[] = "PcPoints";

			ExchangeLowToHigh(gObj, Type, Buy, KindOfSell, KindOfBuy, SellKind, BuyKind, ConfigBuy, MaxBuy);
			return true;
		}
		break;
	case 12: // zen-webpoint <
		{
			if(CheckCommand(gObj, Configs.Commands.ExchangeZenWp, GmSystem.NONE, 0, 0, 0, 0, Configs.Commands.ExchangeMinLvl, 1, 0, "Exchanger", "/zen-webpoint <num>", Msg))
			{
				return true;
			}

			DWORD Buy;
			int SellKind = gObj->Money;
			int BuyKind;

			if (PCPoint.Config.WebColumnFloat)
			{
				BuyKind = (int)ceil(AddTab[gObj->m_Index].WEB_Points_Float);
			}
			else
			{
				BuyKind = AddTab[gObj->m_Index].WEB_Points;
			}

			sscanf(Msg,"%d",&Buy);

			DWORD ConfigBuy = Configs.Commands.WebPoint_Zen;
			DWORD MaxBuy = PCPoint.Config.MaximumWebPoints;

			char KindOfSell[] = "Zen";
			char KindOfBuy[] = "WebPoints";

			ExchangeLowToHigh(gObj, Type, Buy, KindOfSell, KindOfBuy, SellKind, BuyKind, ConfigBuy, MaxBuy);

			return true;
		}
		break;
	}
	return true;
}

bool cChat::ResetCommand(LPOBJ gObj)
{
	ResetSystem.Reset(gObj);

	return true;
}

bool cChat::EvoCommand(LPOBJ gObj)
{
	if(CheckCommand(gObj, Configs.Commands.EvoCommandEnabled, GmSystem.NONE, Configs.Commands.EvoPriceZen,  Configs.Commands.EvoPricePcPoint, Configs.Commands.EvoPriceWCoin, Configs.Commands.EvoPriceWebPoint, Configs.Commands.EvoLevelReq, 0, 0, "Evo", COMMAND_EVO,""))
	{
		return true;
	}

	if((gObj->DbClass == 1) || (gObj->DbClass == 17) || (gObj->DbClass == 33) || (gObj->DbClass == 48) || (gObj->DbClass == 64) || (gObj->DbClass == 81))
	{	
		TakeCommand(gObj, Configs.Commands.EvoPriceZen, Configs.Commands.EvoPricePcPoint, Configs.Commands.EvoPriceWCoin, Configs.Commands.EvoPriceWebPoint,"Evo");

		gObj->DbClass += 2;
		BYTE btClass = (gObj->Class * 32) + 24;
		GCSendQuestPrize(gObj->m_Index, 204, btClass);
		gObjCalCharacter(Utilits.GetPlayerIndex(gObj->Name));
		GCLevelUpMsgSend(gObj->m_Index,0);

		Chat.MessageLog(1, c_Blue, t_COMMANDS, gObj,"[Evo] Parabens! Voce completou a terceira quest.");
	}
	else if((gObj->DbClass == 3) || (gObj->DbClass == 19) || (gObj->DbClass == 35) || (gObj->DbClass == 50) || (gObj->DbClass == 66) || (gObj->DbClass == 83))
	{
		Chat.MessageLog(1, c_Red, t_COMMANDS, gObj,"[Evo] Desculpe, voce ja e um mestre.");
	}
	else
	{
		Chat.MessageLog(1, c_Red, t_COMMANDS, gObj,"[Evo] Voce precisa ter a segunda quest.");
	}

	return true;
}

bool cChat::ZenCommand(LPOBJ gObj,char *Msg)
{
	if
	(
		CheckCommand
		(
			gObj,
			Configs.Commands.ZenCommandEnabled,
			GmSystem.NONE,
			0,
			Configs.Commands.ZenPricePcPoint,
			Configs.Commands.ZenPriceWCoin,
			Configs.Commands.ZenPriceWebPoint,
			Configs.Commands.ZenLevelReq,
			1,
			0,
			"Zen",
			"/zen <quantia>",
			Msg
		)
	)	
	{
		return true;
	}
	else
	{
		int Buffer = atoi(Msg);

		if(Buffer > 0)
		{
			if(((gObj->Money + Buffer) >= 2000000000) || (gObj->Money < 0) || (Buffer >= 2000000000))
			{
				MessageLog(1, c_Red, t_COMMANDS, gObj, "[Zen] Impossivel carregar mais do que 2000000000 zens.");
			}
			else
			{
				gObj->Money += Buffer;
				GCMoneySend(gObj->m_Index,gObj->Money);

				TakeCommand(gObj,0,Configs.Commands.ZenPricePcPoint,Configs.Commands.ZenPriceWCoin,Configs.Commands.ZenPriceWebPoint,"Zen");
			}
		}
		else
		{
			MessageLog(1, c_Red, t_COMMANDS, gObj, "[Zen] Desculpe, valor fora do padrao.");
		}
	}

	return true;
}

bool cChat::ClearInvCommand(LPOBJ gObj)
{
	if
	(
		CheckCommand
		(
			gObj,
			Configs.Commands.ClearCommandEnabled,
			GmSystem.NONE,
			Configs.Commands.ClearZenReq,
			Configs.Commands.ClearPricePcPoint,
			Configs.Commands.ClearPriceWCoin,
			Configs.Commands.ClearPriceWebPoint,
			Configs.Commands.ClearLevelReq,
			0,
			0,
			"Clear Intventory",
			"/clear",
			""
		)
	)	
	{
		return true;
	}
	else
	{
		TakeCommand(gObj,Configs.Commands.ClearZenReq,Configs.Commands.ClearPricePcPoint,Configs.Commands.ClearPriceWCoin,Configs.Commands.ClearPriceWebPoint,"Clear");

		/*
			i = 0 Limpar TUDO!
			i = 12 Limpar somente inventario e deixar SET, Armas, Pendantes, Pet e Asa
		*/

		for(BYTE i = 12; i < 76;i ++)
		{
			gObjInventoryDeleteItem(gObj->m_Index,i);
			GCInventoryItemDeleteSend(gObj->m_Index,i,1);
		}

		Chat.MessageLog(1, c_Blue, t_COMMANDS, gObj,"[Clear] Voce limpou seu inventario!");
	}

	return true;
}

bool cChat::IsMarryCommand(LPOBJ gObj, char *Msg)
{
	if(CheckCommand(gObj, Marry.Config.IsMarry, GmSystem.NONE, 0, 0, 0, 0, 0, 1, 0, "Marry", "/ismarry <name>", Msg))
	{
		return true;
	}

	char Target[11];
	sscanf(Msg, "%10s", &Target);
	int Index = Utilits.GetPlayerIndex(Target);

	if (Index == -1)
	{
		MessageLog(1, c_Blue, t_COMMANDS, gObj, "[Marry] Player's offline or doesn't exist!!!");

		return false;
	}

	OBJECTSTRUCT *tObj = (OBJECTSTRUCT*)OBJECT_POINTER(Index);

	if (AddTab[tObj->m_Index].IsMarried == 1)
	{
		MessageLog(1, c_Blue, t_COMMANDS, gObj, "[Marry] %s is married on %s!!!", tObj->Name, AddTab[tObj->m_Index].MarryName);
	}
	else
	{
		MessageLog(1, c_Blue, t_COMMANDS, gObj, "[Marry] %s is not married!!!", tObj->Name);
	}

	return true;
}
bool cChat::MarryOnlineCommand(LPOBJ gObj)
{
	if (CheckCommand(gObj, Marry.Config.MarryOnline, GmSystem.NONE, 0, 0, 0, 0, 0, 0, 0, "Marry", COMMAND_MARRY_ONLINE, ""))
	{
		return true;
	}

	if (AddTab[gObj->m_Index].IsMarried == 0)
	{
		MessageLog(1, c_Red, t_COMMANDS, gObj, "[Marry] You are not married!");

		return false;
	}

	if (Utilits.GetPlayerIndex(AddTab[gObj->m_Index].MarryName) == -1)
	{
		MessageLog(1, c_Blue, t_COMMANDS, gObj, "[Marry] %s is offline", AddTab[gObj->m_Index].MarryName);
	}
	else
	{
		MessageLog(1, c_Blue, t_COMMANDS, gObj, "[Marry] %s is now online!", AddTab[gObj->m_Index].MarryName);
	}

	return true;
}
bool cChat::MarryTraceCommand(LPOBJ gObj)
{
	if (CheckCommand(gObj, Marry.Config.MarryTrace, GmSystem.NONE, 0, 0, 0, 0, Marry.Config.MarryTraceLvl, 0, 0, "Marry", COMMAND_MARRY_TRACE, ""))
	{
		return true;
	}

	int Index = Utilits.GetPlayerIndex(AddTab[gObj->m_Index].MarryName);

	if (AddTab[gObj->m_Index].IsMarried == 0 || Index == -1)
	{
		MessageLog(1, c_Red, t_COMMANDS, gObj, "[Marry] You are not married or your marriage is offline!");

		return false;
	}

	OBJECTSTRUCT *tObj = (OBJECTSTRUCT*)OBJECT_POINTER(Index);

	if((tObj->MapNumber >= 11 && tObj->MapNumber <= 17) || tObj->MapNumber == 52 || (tObj->MapNumber >= 18 && tObj->MapNumber <= 23) || tObj->MapNumber == 53 || tObj->MapNumber == 9 || tObj->MapNumber == 32 || (tObj->MapNumber >= 45 && tObj->MapNumber <= 50))
	{
		MessageLog(1, c_Red, t_COMMANDS, gObj, "[Marry] Your marriage is inside event map, you cannot teleport");

		return false;
	}

	MessageLog(1, c_Red, t_COMMANDS, gObj, "[Marry] You successfully moved to %s!", tObj->Name);
	MessageLog(1, c_Red, t_COMMANDS, tObj, "[Marry] %s successfully moved to you!", gObj->Name);
	gObjTeleport(gObj->m_Index, tObj->MapNumber, (int)tObj->X, (int)tObj->Y);

	return true;
}
bool cChat::MarryDivorce(LPOBJ gObj)
{
	if (CheckCommand(gObj, Marry.Config.IsDivorce, GmSystem.NONE, Marry.Config.DivorceCostZen,Marry.Config.DivorceCostPCPoint, Marry.Config.DivorceCostWCoin, 0, Marry.Config.DivorceMinLvl, 0, 0, "Divorce", COMMAND_DIVORCE, ""))
	{
		return true;
	}

	if (AddTab[gObj->m_Index].IsMarried == 0)
	{
		MessageLog(1, c_Red, t_COMMANDS, gObj, "[Divorce] You are not married!");

		return false;
	}

	int Index = Utilits.GetPlayerIndex(AddTab[gObj->m_Index].MarryName);

	if (Index == -1)
	{
		MessageLog(1, c_Red, t_COMMANDS, gObj, "[Divorce] Your ex. marriage is offline.");
	}

	OBJECTSTRUCT *tObj = (OBJECTSTRUCT*)OBJECT_POINTER(Index);

	MuOnlineQuery.ExecQuery("UPDATE Character SET IsMarried=0, MarryName = '' WHERE Name = '%s'", gObj->Name);
	MuOnlineQuery.Fetch();
	MuOnlineQuery.Close();

	MuOnlineQuery.ExecQuery("UPDATE Character SET IsMarried=0, MarryName = '' WHERE Name = '%s'", AddTab[gObj->m_Index].MarryName);
	MuOnlineQuery.Fetch();
	MuOnlineQuery.Close();

	AddTab[gObj->m_Index].IsMarried = 0;

	if (Utilits.GetPlayerIndex(AddTab[gObj->m_Index].MarryName) != -1)
	{
		AddTab[tObj->m_Index].IsMarried = 0;
	}

	TakeCommand(gObj, Marry.Config.DivorceCostZen, Marry.Config.DivorceCostPCPoint, Marry.Config.DivorceCostWCoin, 0, "Divorce");

	MessageLog(1, c_Red, t_COMMANDS, gObj, "[Marry] You are divorced!");

	if (Utilits.GetPlayerIndex(AddTab[gObj->m_Index].MarryName) != -1)
	{
		MessageLog(1, c_Red, t_COMMANDS, tObj, "[Marry] You divorced with %s!", gObj->Name);
	}

	return true;
}

bool cChat::YesCommand(LPOBJ gObj)
{
	if(!Marry.NpcUse)
	{
		return true;
	}

	int TypeMarry = -1;

	if(AddTab[gObj->m_Index].MarryType != -1)
	{
		TypeMarry = AddTab[gObj->m_Index].MarryType;
	}

	switch(TypeMarry)
	{
		case 0:
		{
			Chat.MessageAllLog(0,0,c_Green,t_Default,gObj,"Casamento em Devias!");

			Marry.NpcUse = false;

			break;
		}
		default:
		{
			Chat.MessageAllLog(0,0,c_Green,t_Default, gObj,"[%s] %s!",gObj->Name,COMMAND_YES);
			AddTab[gObj->m_Index].MarryType = 3;

			if(AddTab[Marry.gObj1->m_Index].MarryType == 3 && AddTab[Marry.gObj2->m_Index].MarryType == 3)
			{
				Marry.EndMarriageTrue();	//RUN THEARD
			}

			Marry.NpcUse = false;

			break;
		}
	}

	return true;
}

bool cChat::NoCommand(LPOBJ gObj)
{
	if(!Marry.NpcUse)
	{
		return true;
	}

	int TypeMarry = -1;

	if(AddTab[gObj->m_Index].MarryType != -1)
	{
		TypeMarry = AddTab[gObj->m_Index].MarryType;
	}

	LPOBJ nObj = Marry.NpcObj;

	switch(TypeMarry)
	{
		case 0:
		{
			if(nObj == NULL)
			{
				Chat.Message(1,gObj,"Voce cancelou o casamento");
			}
			else
			{
				// Private
				Monster.NPCMessage(gObj->m_Index,nObj, "Voce cancelou o casamento");
			}

			if(Marry.gObj1 != NULL)
			{
				AddTab[Marry.gObj1->m_Index].MarryType = -1;
			}

			if(Marry.gObj2 != NULL)
			{
				AddTab[Marry.gObj2->m_Index].MarryType = -1;
			}

			Marry.NpcUse = false;

			Marry.gObj1 = NULL;
			Marry.gObj2 = NULL;
			Marry.NpcObj = NULL;

			break;
		}
		default:
		{
			Chat.MessageAllLog(0, 0, c_Green, t_Default, gObj, "[%s] %s!", gObj->Name,COMMAND_NO);

			Monster.NPCMessageNear(nObj, "O casamento foi cancelado por %s!", gObj->Name);

			Chat.MessageAllLog(0, 0, c_Green, t_Default, gObj, "[Marriage] Casamento cancelado por %s!", gObj->Name);

			if(Marry.gObj1 != NULL)
			{
				AddTab[Marry.gObj1->m_Index].MarryType = -1;
			}

			if(Marry.gObj2 != NULL)
			{
				AddTab[Marry.gObj2->m_Index].MarryType = -1;
			}

			Marry.NpcUse = false;

			Marry.gObj1 = NULL;
			Marry.gObj2 = NULL;
			Marry.NpcObj = NULL;

			break;
		}
	}

	return true;
}