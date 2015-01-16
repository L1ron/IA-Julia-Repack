#pragma once

#ifndef USER_H
#define USER_H

#include "StdAfx.h"
#include "Configs.h"
#include "Prodef.h"

typedef	struct sAddTab
{
    /////////////
    // PLAYERS //
    /////////////

    //Add Stats
    int		ADD_Type;
    DWORD	ADD_Value;

    //Post Delay
    int		POST_Delay;

    CTime	POST_BanTime;
    bool	POST_BanSignal;

    CTime	CHAT_BanTime;
    bool	CHAT_BanSignal;

    //Marriage
    int	IsMarried;
    char MarryName[11];
    int MarryType;

    //Anti AFK
    int		AFK_Timer;
    int		AFK_MapNumber;
    int		AFK_X;
    int		AFK_Y;
    int		AFK_Warnings;
    DWORD	AFK_Temp;

    //VIP System
    int		VIP_Type;
    int		VIP_Min;
    int		VIP_Sec;
    int		VIP_On;
    int		VIP_Map;
    int		VIP_X;
    int		VIP_Y;

    //Duel System
    BYTE	DUEL_Room;
    int		DUEL_Wins;
    int		DUEL_Lose;
    int		DUEL_AllDuels;
    int		DUEL_DuelLimit;
    int		DUEL_SpecVisible;

    //PCPoints
    int		PC_InfoMod;
    int		PC_InfoReceived;
    int		PC_PlayerPoints;
    int		PC_OnlineTimer;
    //int		PC_POINT_TEST;

    //Web Points
    int		WEB_Points;
    float	WEB_Points_Float;

    //Online
    int		ON_Min;
    int		ON_Sek;
    int		ON_Hour;

    //Other
    int		Resets;
    int		UsedSlot;

    //TerritorySystem
    int		TERR_TypeOnMap;
    int		TERR_Map;
    int		TERR_X;
    int		TERR_Y;
    int		TERR_Type;
    int		TERR_TimeGo;
    int		TERR_Min;
    int		TERR_Sec;

    //OffTrade
    bool    OfflineTrade;
    bool    CloseSetCheck;

    //Helper
    int     HELPER_UsedTimes; 

    LPBYTE aRecv;

    //////////////
    // MONSTERS //
    //////////////

    bool	TEMP_Golden_Drop;
} sAddTab;

typedef OBJECTSTRUCT * LPOBJ;
extern sAddTab AddTab[OBJECT_MAX];
//extern OBJECTSTRUCT gObj[OBJECT_MAX];
// #	FIXES	# //
void __stdcall gObjViewportPatchExecute(OBJECTSTRUCT *gObj);
void __stdcall JGPGetCharInfoEx(int Loop, unsigned char *DSPacket, unsigned char *toClientPacket);
// # ---------- # //

// # Hook in GS # //
void gObjLevelUpPointAddEx(BYTE type, OBJECTSTRUCT* lpObj);
BOOL gObjGameClose_Func(int aIndex);
void GCKillPlayerExpSendHook(int aIndex, int TargetIndex, long exp, int AttackDamage, int MSBFlag);
void MyObjCalCharacter(int aIndex);
void FireworkOnTheScreen(LPOBJ gObj);
void GCEquipmentSendHook(int aIndex);
void GSItemDurRepaire(LPOBJ lpObj, CItem * DurItem, int pos, int RequestPos);
BOOL _gObjCheckTeleportArea(int aIndex, BYTE X, BYTE Y);
// # ---------- # //

// #	TICK	# //
void TradeSystem__Cancel(void * lpParam);
// # ---------- # //

class cUser
{
public:
    void OnlineTimeTick(LPOBJ gObj);
    void PlayerConnect(LPOBJ gObj);
    void CheckRingSend(LPOBJ gObj, LPBYTE aRecv);
    void CheckRing(LPOBJ gObj, LPBYTE aRecv);
    void RingSkin(LPOBJ gObj);
    bool CGPartyRequestRecv(PMSG_PARTYREQUEST * lpMsg, int aIndex);
    bool CharacterCreate(PMSG_CHARCREATE* lpMsg, int aIndex);
    bool GuildMasterInfoSave(int aIndex,PMSG_GUILDINFOSAVE* lpMsg);
    void gObjCharacterWingsSetPreview(short ItemType, unsigned char *CharSet,int Type,OBJECTSTRUCT *lpObj);
    bool CheckMaxPoints(BYTE type, OBJECTSTRUCT* lpObj);
private:
    void CheckTeleport(LPOBJ gObj);
    void LoginMsg(LPOBJ gObj);
    bool ResetCheck(LPOBJ gObj);
};
extern cUser User;

#endif