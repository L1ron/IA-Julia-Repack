#ifndef CHAT_H
#define CHAT_H

#include "Logger.h"
#include "User.h"
#include "GMSystem.h"
#include "Prodef.h"

class cChat
{
	public:
		cChat();
		~cChat();
		
		void LoadChatCommands();
		bool WisperChat(LPOBJ gObj, PMSG_CHATDATA_WHISPER* lpMsg);
		bool ChatDataSend(LPOBJ gObj, PMSG_CHATDATA * lpChat);
		void MessageLog(int Type, sColor LogColor, sLogType LogType, LPOBJ gObj, char* Msg,...);
		void Message(int Type, LPOBJ gObj, char* Msg,...);
		void MessageAllLog(int Type, int Type2, sColor LogColor, sLogType LogType, LPOBJ gObj, char* Msg,...);
		void MessageAll(int Type, int Type2, LPOBJ gObj, char* Msg,...);

		char COMMAND_YES[25];
		char COMMAND_NO[25];

	private:
		void AntiInject(char* message);

		bool CheckCommand
		(
			LPOBJ gObj,
			int Config,cGmSystem::Commands Command,
			int NeedZen,int NeedPcPoint,
			int NeedWCoin,
			int NeedWebPoints,
			int NeedLvl,
			int Filled,
			int CheckPlayer,
			char *CommandName,
			char *CommandUsage,
			char *Msg
		);

		void TakeCommand(LPOBJ gObj, int NeedZen, int NeedPcPoint, int NeedWCoin, int NeedWebPoints, char *CommandName);
		void PrivateLog(LPOBJ gObj, char *Name, PMSG_CHATDATA_WHISPER* lpMsg, bool Success);
		void MassLog(LPOBJ gObj, char* Message);
		void MsgSrv(LPOBJ gObj,char* Message, int Type2);
		bool GgCommand(LPOBJ gObj, char* Msg);
		bool VosklCommand(LPOBJ gObj, char* Msg);
		bool MoveCommand(LPOBJ gObj, char *Msg);
		bool PostCommand(LPOBJ gObj, char *Msg);
		bool TimeCommand(LPOBJ gObj);
		bool ReloadCommand(LPOBJ gObj, char *Msg);
		bool OnlineCommand(LPOBJ gObj, char *Msg);
		bool LevelCommand(LPOBJ gObj);
		bool WareCommand(LPOBJ gObj, char *Msg);
		bool CheckCommand(LPOBJ gObj, char *Msg);
		bool AddCommands(LPOBJ gObj, char *Msg, int Type);
		bool AddMobCommand(LPOBJ gObj, char *Msg);
		bool CheckVIPCommand(LPOBJ gObj, char *Msg);
		bool BuyVIPCommand(LPOBJ gObj, char *Msg);
		bool VIPListCommand(LPOBJ gObj, char *Msg);
		bool CheckTerritoryCommand(LPOBJ gObj, char *Msg);
		bool BuyTerritoryCommand(LPOBJ gObj, char *Msg);
		bool GuildPost(LPOBJ gObj, char *Msg);
		bool Core(LPOBJ gObj, char *Msg);

		bool TraceCommand(LPOBJ gObj, int Index);
		bool DiskCommand(LPOBJ gObj, int Index);
		bool SummonCommand(LPOBJ gObj, int Index);

		bool BanPostCommand(LPOBJ gObj, char *Msg, int Index);
		bool UnBanPostCommand(LPOBJ gObj, int Index);
		bool BanAccCommand(LPOBJ gObj, char *Msg, int Index);
		bool UnBanAccCommand(LPOBJ gObj, char *Msg);
		bool BanCharCommand(LPOBJ gObj, char *Msg, int Index);
		bool UnBanCharCommand(LPOBJ gObj, char *Msg);

		bool SetCharCommand(LPOBJ gObj, char* Msg, int Index);
		bool SetPKCommand(LPOBJ gObj, char *Msg, int Index);
		bool SkinCommand(LPOBJ gObj, char *Msg, int Index);
		bool DropCommand(LPOBJ gObj, char *Msg, int Index);
		bool GmoveCommand(LPOBJ gObj, char *Msg, int Index);
		bool StatusCommand(LPOBJ gObj, char *Msg, int Index);
		bool PKClearCommand(LPOBJ gObj, char *Msg, int Index);
		bool SetDropCommand(LPOBJ gObj, char *Msg, int Index);
		bool SetZenCommand(LPOBJ gObj, char *Msg, int Index);

		bool DisableChatCommand(LPOBJ gObj, char *Msg, int Index);
		bool EnableChatCommand(LPOBJ gObj, int Index);

		bool VipOnCommand(LPOBJ gObj);
		bool VipOffCommand(LPOBJ gObj);

		bool OffTradeCommand(LPOBJ gObj);
		bool ResetCommand(LPOBJ gObj);
		bool EvoCommand(LPOBJ gObj);
		bool ZenCommand(LPOBJ gOBj,char *Msg);
		bool ClearInvCommand(LPOBJ gOBj);
		bool ExchangeCommands(LPOBJ gObj, char *Msg, int Type);

		bool IsMarryCommand(LPOBJ gObj, char *Msg);
		bool MarryOnlineCommand(LPOBJ gObj);
		bool MarryTraceCommand(LPOBJ gObj);
		bool MarryDivorce(LPOBJ gObj);

		bool YesCommand(LPOBJ gObj);
		bool NoCommand(LPOBJ gObj);

		char COMMAND_GG[25];
		char COMMAND_VOSKL[25];
		char COMMAND_TRACE[25];
		char COMMAND_DISCONNECT[25];
		char COMMAND_TRACK[25];
		char COMMAND_MOVE[25];
		char COMMAND_WARP[25];
		char COMMAND_LEVEL[25];
		char COMMAND_POST[25];
		char COMMAND_BAN_POST[25];
		char COMMAND_BAN_CHAR[25];
		char COMMAND_BAN_ACC[25];
		char COMMAND_UNBAN_POST[25];
		char COMMAND_UNBAN_CHAR[25];
		char COMMAND_UNBAN_ACC[25];
		char COMMAND_TIME[25];
		char COMMAND_SET_CHAR[25];
		char COMMAND_SET_PK[25];
		char COMMAND_SET_ZEN[25];
		char COMMAND_SKIN[25];
		char COMMAND_DROP[25];
		char COMMAND_GMOVE[25];
		char COMMAND_ONLINE[25];
		char COMMAND_STATUS[25];
		char COMMAND_RELOAD[25];
		char COMMAND_PKCLEAR[25];
		char COMMAND_ADD_STR[25];
		char COMMAND_ADD_AGI[25];
		char COMMAND_ADD_VIT[25];
		char COMMAND_ADD_ENE[25];
		char COMMAND_ADD_CMD[25];
		char COMMAND_WARE[25];
		char COMMAND_MOBADD[25];
		char COMMAND_SETDROP[25];
		char COMMAND_CHECK[25];
		char COMMAND_VIPBUY[25];
		char COMMAND_VIPCHECK[25];
		char COMMAND_VIPLIST[25];
		char COMMAND_TERRCHECK[25];
		char COMMAND_TERRBUY[25];
		char COMMAND_VIP_ON[25];
		char COMMAND_VIP_OFF[25];
		char COMMAND_AT[25];
		char COMMAND_ENABLE_CHAT[25];
		char COMMAND_DISABLE_CHAT[25];
		char COMMAND_WCOIN_PCOINT[25];
		char COMMAND_WCOIN_WEBPOINT[25];
		char COMMAND_WCOIN_ZEN[25];
		char COMMAND_WEBPOINT_WCOIN[25];
		char COMMAND_WEBPOINT_PCPOINT[25];
		char COMMAND_WEBPOINT_ZEN[25];
		char COMMAND_PCPOINT_ZEN[25];
		char COMMAND_PCPOINT_WCOIN[25];
		char COMMAND_PCPOINT_WEBPOINT[25];
		char COMMAND_ZEN_WCOIN[25];
		char COMMAND_ZEN_PCPOINT[25];
		char COMMAND_ZEN_WEBPOINT[25];
		char COMMAND_GUILD_POST[25]; 
		char COMMAND_OFFTRADE[25];
		char COMMAND_RESET[25];
		char COMMAND_EVO[25];
		char COMMAND_ZEN[25];
		char COMMAND_CLEAR[25];
		char COMMAND_ISMARRY[25];
		char COMMAND_MARRY_ONLINE[25];
		char COMMAND_MARRY_TRACE[25];
		char COMMAND_DIVORCE[25];
};

extern cChat Chat;

#endif