#include "StdAfx.h"
#include "MoveReq.h"
#include "User.h"
#include "Utilits.h"
#include "Logger.h"

cMoveReq MoveReq;

void cMoveReq::ResetConfig()
{
    for(int i=0; i<255; i++)
    {
        MoveReqInfo[i].Index		= 0;
        MoveReqInfo[i].Zen			= 0;
        MoveReqInfo[i].Level		= 0;
        MoveReqInfo[i].Gate			= 0;
        MoveReqInfo[i].VIP			= 0;
        MoveReqInfo[i].MapName1[0]	= NULL;
        MoveReqInfo[i].MapName2[0]	= NULL;
        MoveReqInfo[i].MapNumber	= -1;
    }

    for(int i=0;i < 500;i++)
    {
        Gate[i].Index = 0;
        Gate[i].MapNumber = -1;
        Gate[i].VIP = 0;
    }

    Count = 0;
}

void cMoveReq::Load()
{
    ResetConfig();

    FILE *File;
    File = fopen(IAJuliaMoveReq, "r");

    if(File == NULL)
    {
        Log.ConsoleOutPut(1, c_Red, t_Error, "[X] [MoveReq]\tImpossivel encontrar %s.", IAJuliaMoveReq);
        return;
    }

    char Buff[256];
    int Flag = 0;
    Count = 0;

    while(!feof(File))
    {
        fgets(Buff,256,File);

        if(Utilits.IsBadFileLine(Buff, Flag))
        {
            continue;
        }

        if(Flag == 1)
        {
            int n[5];
            char Name[51] = { 0 };
            char Name2[51] = { 0 };
            sscanf(Buff, "%d \"%50[^\"]\" \"%50[^\"]\" %d %d %d %d", &n[0], &Name, &Name2, &n[1], &n[2], &n[3], &n[4]);

            MoveReqInfo[Count].Index		= n[0];
            strcpy(MoveReqInfo[Count].MapName1, Name);
            strcpy(MoveReqInfo[Count].MapName2, Name2);
            MoveReqInfo[Count].Zen			= n[1];
            MoveReqInfo[Count].Level		= n[2];
            MoveReqInfo[Count].Gate			= n[3];
            MoveReqInfo[Count].VIP			= n[4];
            Count++;
        }
    }

    fclose(File);
    Log.ConsoleOutPut(1, c_Cyan, t_Default, "[û] [MoveReq]\t%d Mapas carregados.", Count);

    File = fopen("..\\data\\Gate.txt","r");

    if(File == NULL)
    {
        Log.ConsoleOutPut(1, c_Red, t_Error, "[X] [MoveReq]\tImpossivel ler \\data\\Gate.txt");

        return;
    }

    Flag = 1;
    int Count2 = 0;

    while (!feof(File))
    {
        fgets(Buff,256,File);

        if(Utilits.IsBadFileLine(Buff, Flag))
            continue;

        if (Flag == 1)
        {
            int n[3];
            sscanf(Buff, "%d %d %d", &n[0], &n[1], &n[2]);

            Gate[Count2].Index = n[0];
            Gate[Count2].MapNumber = n[2];

            Count2++;
        }
    }

    fclose(File);
    Log.ConsoleOutPut(1, c_Cyan, t_Default, "[û] [MoveReq]\t%d Gates Carregados.", Count2);

    for(int i=0; i <= Count; i++)
    {
        if (MoveReqInfo[i].Index <= 0 || !MoveReqInfo[i].VIP)
        {
            continue;
        }

        int VIPMap = -1;

        for (int j=0; j<=Count2; j++)
        {
            if (Gate[j].Index <= 0)
            {
                continue;
            }

            if(VIPMap == -1)
            {
                if(MoveReqInfo[i].Gate == Gate[j].Index)
                {
                    VIPMap = Gate[j].MapNumber;

                    Log.ConsoleOutPut(1, c_Red, t_TEST, "Gate[%d].Map = %d", j, VIPMap);
                }
            }
            if(VIPMap != -1)
            {
                if (Gate[j].MapNumber == VIPMap)
                {
                    Gate[j].VIP = 1;
                }
            }
        }

        if (VIPMap != -1)
        {
            MoveReqInfo[i].MapNumber = VIPMap;

            Log.ConsoleOutPut(1, c_Red, t_TEST, "MoveReqInfo[%d].MapNumber = %d", i, VIPMap);
        }
    }
}

int cMoveReq::GetMapVip(int MapIndex)
{
    for(int i = 0; i <= MoveReq.Count; i++)
    {
        if (!MoveReqInfo[i].VIP)
            continue;

        if (MoveReqInfo[i].MapNumber == MapIndex)
            return MoveReqInfo[i].VIP;
    }

    return -1;
}
