#include "StdAfx.h"
#include "Socket.h"
#include "Prodef.h"
#include "Logger.h"
#include "Utilits.h"

cSocket Socket;

void cSocket::ResetConfig()
{
    for(int i=0; i<255; i++)
    {
        Items[i].Index = 26;
        Items[i].Type = 0;
    }
}
void cSocket::Load()
{
    ResetConfig();
    FILE *file;

    file = fopen(IAJuliaSocket,"r");

    if(file == NULL)
    {
        Log.ConsoleOutPut(1,c_Red,t_Error,"[X] [SocketSystem]\tImpossivel abrir %s",IAJuliaSocket);
        
		return;
    }

    char Buff[256];
    int Flag = 0;
    Count = 0;

    while(!feof(file))
    {
        fgets(Buff,256,file);

        if(Utilits.IsBadFileLine(Buff, Flag))
		{
            continue;
		}

        if(Flag == 1)
        {
            int n[5];

            sscanf(Buff, "%d %d", &n[0], &n[1]);
            Items[Count].Type		= n[0];
            Items[Count].Index		= n[1];
            Count++;
        }
    }

    fclose(file);
    Log.ConsoleOutPut(1, c_Magenta, t_Default, "[+] [SocketSystem]\tItens carregados");
}

BYTE CheckItemType(int iItemNumber)
{
    for (int i=0; i <= Socket.Count; i++)
    {
        if(ITEMGET(Socket.Items[i].Type,Socket.Items[i].Index) == iItemNumber)
		{
			return TRUE;
		}
    }

    return FALSE;
}
