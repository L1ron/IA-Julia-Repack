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
        char COMMAND_ISMARRY[25];
        char COMMAND_MARRY_ONLINE[25];
        char COMMAND_MARRY_TRACE[25];
        char COMMAND_DIVORCE[25];
        char COMMAND_YES[25];
        char COMMAND_NO[25];
};

extern cChat Chat;

/*
#define COMMAND_GG					"/gg"
#define COMMAND_VOSKL				"!"
#define COMMAND_TRACE				"/trace"
#define COMMAND_DISCONNECT			"/disconnect"
#define COMMAND_TRACK				"/track"
#define COMMAND_MOVE				"/move"
#define COMMAND_WARP				"/warp"
#define COMMAND_LEVEL				"/level"
#define COMMAND_POST				"/post"
#define COMMAND_BAN_POST			"/banpost"
#define COMMAND_BAN_CHAR			"/banchar"
#define COMMAND_BAN_ACC				"/banacc"
#define COMMAND_UNBAN_POST			"/unbanpost"
#define COMMAND_UNBAN_CHAR			"/unbanchar"
#define COMMAND_UNBAN_ACC			"/unbanacc"
#define COMMAND_TIME				"/time"
#define COMMAND_SET_CHAR			"/setchar"
#define COMMAND_SET_PK				"/setpk"
#define COMMAND_SET_ZEN				"/setzen"
#define COMMAND_SKIN				"/skin"
#define COMMAND_DROP				"/drop"
#define COMMAND_GMOVE				"/gmove"
#define COMMAND_ONLINE				"/online"
#define COMMAND_STATUS				"/status"
#define COMMAND_RELOAD				"/reload"
#define COMMAND_PKCLEAR				"/pkclear"
#define COMMAND_ADD_STR				"/str"
#define COMMAND_ADD_AGI				"/agi"
#define COMMAND_ADD_VIT				"/vit"
#define COMMAND_ADD_ENE				"/ene"
#define COMMAND_ADD_CMD				"/cmd"
#define COMMAND_WARE				"/ware"
#define COMMAND_MOBADD				"/mobadd"
#define COMMAND_SETDROP				"/setdrop"
#define COMMAND_CHECK				"/check"
#define COMMAND_VIPBUY				"/vipbuy"
#define COMMAND_VIPCHECK			"/vipcheck"
#define COMMAND_VIPLIST				"/viplist"
#define COMMAND_TERRCHECK			"/terrcheck"
#define COMMAND_TERRBUY				"/terrbuy"
#define COMMAND_VIP_ON				"/vip on"
#define COMMAND_VIP_OFF				"/vip off"
#define COMMAND_AT					"@"
#define COMMAND_ENABLE_CHAT			"/enablechat"
#define COMMAND_DISABLE_CHAT		"/disablechat"
#define COMMAND_WCOIN_PCOINT		"/wcoin-pcpoint"
#define COMMAND_WCOIN_WEBPOINT		"/wcoin-webpoint"
#define COMMAND_WCOIN_ZEN			"/wcoin-zen"
#define COMMAND_WEBPOINT_WCOIN		"/webpoint-wcoin"
#define COMMAND_WEBPOINT_PCPOINT	"/webpoint-pcpoint"
#define COMMAND_WEBPOINT_ZEN		"/webpoint-zen"
#define COMMAND_PCPOINT_ZEN			"/pcpoint-zen"
#define COMMAND_PCPOINT_WCOIN		"/pcpoint-wcoin"
#define COMMAND_PCPOINT_WEBPOINT	"/pcpoint-webpoint"
#define COMMAND_ZEN_WCOIN			"/zen-wcoin"
#define COMMAND_ZEN_PCPOINT			"/zen-pcpoint"
#define COMMAND_ZEN_WEBPOINT		"/zen-webpoint"
#define COMMAND_GUILD_POST 			"@>"
#define COMMAND_OFFTRADE			"/offtrade"
#define COMMAND_RESET				"/reset"
#define COMMAND_EVO					"/evo"
#define COMMAND_ISMARRY				"/ismarry"
#define COMMAND_MARRY_ONLINE		"/marryonline"
#define COMMAND_MARRY_TRACE			"/marrytrace"
#define COMMAND_DIVORCE				"/divorce"
#define COMMAND_YES					"/sim"
#define COMMAND_NO					"/nao"
*/
#endif