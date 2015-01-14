// ================================================== //
// #			GameServer 1.00.90					# //
// #			Imagination Arts					# //
// #			Julia Project 1.1.x					# //
// ================================================== //
// #	http://imaginationarts.net/forum/			# //
// #	http://mu.raklion.ru/						# //
// ================================================== //

#include "StdAfx.h"
#include "MapSystem.h"
#include "Prodef.h"
#include "Logger.h"
#include "Configs.h"
#include "Utilits.h"

cMapSystem MapSystem;


void cMapSystem::ResetConfig()
{
    Enabled = 0;
    for(int i = 0; i < 255; i++)
    {
        Maps[i].Drop	= 0;
        Maps[i].Exp		= 0;
        Maps[i].PVP		= 0;
        Maps[i].Zen		= 0;
    }
}

void cMapSystem::Load()
{
    ResetConfig();
    Enabled				= Configs.GetInt(0, 1, 1,"MapSystem", "EnableMapSystem", IAJuliaMapSystem);
    if(!MapSystem.Enabled)return;

    FILE *file;
    file = fopen(IAJuliaMapSystem, "r");

    if (file == NULL)
    {
        Enabled = 0;
        Log.ConsoleOutPut(1, c_Red, t_Error, "[X] [Map System]\tCan`t Find %s", IAJuliaMapSystem);
        return;
    }

    char Buff[256];
    int Flag = 0;

    while (!feof(file))
    {
        fgets(Buff,256,file);

        if(Utilits.IsBadFileLine(Buff, Flag))
            continue;

        if (Flag == 1)
        {
            int n[5];
            sscanf(Buff, "%d %d %d %d %d", &n[0], &n[1], &n[2], &n[3], &n[4]);
            Maps[n[0]].Zen		= n[1];
            Maps[n[0]].Drop		= n[2];
            Maps[n[0]].Exp		= n[3];
            Maps[n[0]].PVP		= n[4];
        }
    }
    fclose(file);
    Log.ConsoleOutPut(1, c_Cyan, t_Default, "[û] [Map System]\tMaps Loaded");
}