#ifndef JEWELS_H
#define JEWELS_H

#define MAX_ITEM_INFO 12
#include "StdAfx.h"
#include "User.h"

class cJewels
{
public:
    void ResetConfig();
    void Load();
    void DeleteItem(int aIndex, int Slot);
    int AddExcOpt(int exc, int maxopt , int success);
    void IdentifyJewel(PMSG_USE_ITEM_RECV * lpmsg, int aIndex);
    bool Verification(int Opt1, int Opt2,int MinOpt1, int MinOpt2, int MaxOpt1 , int MaxOpt2,int Success1, int Success2, CItem* ProtochItem);
    void Successfully(int Opt1 , int Opt2 , int MaxOpt1 , int MaxOpt2, int Success1 , int Success2 , CItem* ProtochItem);
    void Fail(int Opt1, int Opt2 , int Fail1, int Fail2 , int FailOpt1, int FailOpt2, CItem* ProtochItem);
private:
    struct JewelConf
    {
        int id;
        int rate;
        int opt1;
        int opt2;
        int minopt1;
        int minopt2;
        int maxopt1;
        int maxopt2;
        int fail1;
        int fail2;
        int failopt1;
        int failopt2;
        int successfully1;
        int successfully2;
    };

    int AmountJewel;
    JewelConf ArrayJewelConf[255];
    int RATE;
};

extern cJewels Jewels;

#endif