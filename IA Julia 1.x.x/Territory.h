// ================================================== //
// #			GameServer 1.00.90					# //
// #			Imagination Arts					# //
// #			Julia Project 1.1.x					# //
// ================================================== //
// #	http://imaginationarts.net/forum/			# //
// #	http://mu.raklion.ru/						# //
// ================================================== //

#include "User.h"

#ifndef TERRITORY_H
#define TERRITORY_H

class cTerritory
{
public:
    void ResetConfig();
    void Load();
    void Tick(LPOBJ gObj);
    int CheckTerritory(LPOBJ gObj);
    int CheckTerritory(int MapNumber, int X, int Y);
    void Connect(LPOBJ gObj);
    int CheckPlayer(int Terr);
    struct sMap
    {
        int MapNum;
        int X1;
        int X2;
        int Y1;
        int Y2;
    };

    struct sTerr
    {
        char Name[12];
        int CostPCPoint;
        int CostWCoin;
        int CostWebPoints;
        int CostZen;
        int MinLvl;
        int MinReset;
        int OnlyForVip;
        int OnlyForMasterLvl;
        int MaxPlayers;
        int MinHours;
        int MaxHours;
        int NumOfMaps;
        sMap Map[100];
    };

    struct sConfig
    {
        int Enabled;
        int NumOfTerritorys;
        int AllowRebuying;
        sTerr Terr[100];
    } Config;

};

extern cTerritory Territory;

#endif