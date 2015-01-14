// ================================================== //
// #			GameServer 1.00.90					# //
// #			Imagination Arts					# //
// #			Julia Project 1.1.x					# //
// ================================================== //
// #	http://imaginationarts.net/forum/			# //
// #	http://mu.raklion.ru/						# //
// ================================================== //

#ifndef VIP_H
#define VIP_H

#include "StdAfx.h"
#include "User.h"
#include "Prodef.h"

class cVip
{
public:
    void ResetConfig();
    void Load();
    void Connect(LPOBJ gObj);
    void Tick(LPOBJ gObj);
    int GetBonus(LPOBJ gObj, eBonus Type);

    struct cConfig
    {
        int NumStates;
        int Enabled;
        char Column[25];
        char ColumnDate[25];
        int AllowRebuying;

        struct cVIPState
        {
            char VIPName[12];
            int EnabledCmd;

            DWORD CostZen;
            int CostPCPoints;
            int CostWCoins;
            int CostWebPoints;

            int BonusExp;
            int BonusZen;
            int BonusDrop;

            int MinHours;
            int MaxHours;

            int EnableOnOff;
        };
        cVIPState VIPState[20];

    } Config;
    bool CheckVipTime(int TimeInMin);
};
extern cVip Vip;

#endif