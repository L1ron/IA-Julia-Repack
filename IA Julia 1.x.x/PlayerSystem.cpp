#include "StdAfx.h"
#include "PlayerSystem.h"
#include "Prodef.h"
#include "Logger.h"
#include "Configs.h"
#include "Utilits.h"

cPlayerSystem PlayerSystem;

void cPlayerSystem::ResetConfig()
{
    Enabled = 0;
    ConfigNum = 0;

    for(int i=0;i < 255;i++)
    {
        Config[i].Class[0]	= 0;
        Config[i].Class[1]	= 0;
        Config[i].Class[2]	= 0;
        Config[i].Class[3]	= 0;
        Config[i].Class[4]	= 0;
        Config[i].Class[5]	= 0;
        Config[i].First		= 0;
        Config[i].Second	= 0;
        Config[i].Third		= 0;
        Config[i].Zen		= 0;
        Config[i].Drop		= 0;
        Config[i].Exp		= 0;
    }
}

void cPlayerSystem::Load()
{
    ResetConfig();
    Enabled	= Configs.GetInt(0, 1, 1,"PlayerSystem","EnablePlayerSystem", IAJuliaPlayerSystem);

    if(Enabled) return;
    
    FILE *File;
    File = fopen(IAJuliaPlayerSystem, "r");

    if(File == NULL)
    {
        Enabled = 0;
        Log.ConsoleOutPut(1, c_Red, t_Error, "[X] [Player System]\tImpossivel abrir %s", IAJuliaPlayerSystem);

        return;
    }

    int Flag = -1;
    char Buff[256];
    ConfigNum = 0;

    while(!feof(File))
    {
        fgets(Buff,256,File);

        if(Utilits.IsBadFileLine(Buff,Flag))
        {
            continue;
        }

        if(Flag == 1)
        {
            int temp[12];
            sscanf(Buff, "%d %d %d %d %d %d %d %d %d %d %d %d", &temp[0], &temp[1], &temp[2], &temp[3], &temp[4], &temp[5], &temp[6], &temp[7], &temp[8], &temp[9], &temp[10], &temp[11]);

            Config[ConfigNum].Class[0]	= temp[0];
            Config[ConfigNum].Class[1]	= temp[1];
            Config[ConfigNum].Class[2]	= temp[2];
            Config[ConfigNum].Class[3]	= temp[3];
            Config[ConfigNum].Class[4]	= temp[4];
            Config[ConfigNum].Class[5]	= temp[5];
            Config[ConfigNum].First		= temp[6];
            Config[ConfigNum].Second	= temp[7];
            Config[ConfigNum].Third		= temp[8];
            Config[ConfigNum].Zen		= temp[9];
            Config[ConfigNum].Drop		= temp[10];
            Config[ConfigNum].Exp		= temp[11];

            ConfigNum++;
        }
    }

    fclose(File);

    Log.ConsoleOutPut(1, c_Magenta, t_DROP, "[û] [Player System]\tCarregado %s linhas." ,ConfigNum);
}

int cPlayerSystem::GetBonus(LPOBJ gObj, eBonus Type)
{
    if(Enabled == 0)
    {
        return 0;
    }

    int Result = 0;
    for(int i = 0; i < ConfigNum; i++)
    {
        if(Config[i].Class[gObj->Class] == 0)
        {
            continue;
        }

        if
		(
            (Config[i].First == 1 && gObj->ChangeUP == 0 && gObj->ChangeUP2 == 0) ||
            (Config[i].Second == 1 && gObj->ChangeUP == 1 && gObj->ChangeUP2 == 0) ||
            (Config[i].Third == 1 && gObj->ChangeUP == 1 && gObj->ChangeUP2 == 1)
        )
        {
            switch(Type)
            {
                case b_ZEN:
                {
                    Result += Config[i].Zen;

                    break;
                }
                case b_DROP:
                {
                    Result += Config[i].Drop;

                    break;
                }
                case b_EXP:
                {
                    Result += Config[i].Exp;

                    break;
                }
            }
        }
    }

    return Result;
}