#ifndef PLAYERSYSTEM_H
#define PLAYERSYSTEM_H

#include "StdAfx.h"
#include "User.h"
#include "Prodef.h"

class cPlayerSystem
{
public:
    void ResetConfig();
    void Load();
    int GetBonus(LPOBJ gObj, eBonus Type);
    int Enabled;

    struct Conf
    {
        int Class[6];
        int First;
        int Second;
        int Third;
        int Zen;
        int Drop;
        int Exp;
    } Config[255];
    int ConfigNum;
};

extern cPlayerSystem PlayerSystem;

#endif