#include "StdAfx.h"
#include "Configs.h"

#ifdef _GS
#include "MossGambler.h"
#include "Prodef.h"
#include "User.h"
#include "ChatCommands.h"
#include "Utilits.h"
#include "PCPoint.h"
#include "Monster.h"

cMoss Moss;

enum
{
    OPT_LEVEL,
    OPT_SKILL,
    OPT_LUCK,
    OPT_ADD,
    OPT_EXC,
    OPT_ANC
};

struct PMSG_BUYRESULT
{
    PBMSG_HEAD h;	    // C1:32
    BYTE Result;	    // 3
    BYTE ItemInfo[12];	// 4
};

void MossBuyDelay(void *lparam)
{
    Moss.Delay = true;
    Sleep(1500);
    Moss.Delay = false;
    _endthread();
}

void cMoss::DataSendMoss(int Index)
{
    PMSG_BUYRESULT pRez;
    pRez.h.c=0xC1;
    pRez.h.headcode=0x32;
    pRez.h.size=16;
    DataSend(Index,(LPBYTE)&pRez,pRez.h.size);
}

void cMoss::Load()
{
    Config.Enable		= Configs.GetInt(0,1,0,"Moss","EnableMoss",IAJuliaMossGambler);

    if(Config.Enable)
    {
        Config.EnableTimer		= Configs.GetInt(0,1,0,"Moss","EnableTimer",IAJuliaMossGambler);
        Config.UsePK			= Configs.GetInt(0,1,0,"Moss","UsePK",IAJuliaMossGambler);

        Config.PriceZen			= Configs.GetInt(0,2000000000,100000000,"Moss","PriceZen",IAJuliaMossGambler);
        Config.PricePCPoint		= Configs.GetInt(0,PCPoint.Config.MaximumPCPoints,10,"Moss","PricePCPoint",IAJuliaMossGambler);
        Config.PriceWCoin		= Configs.GetInt(0,PCPoint.Config.MaximumWCPoints,10,"Moss","PriceWCoin",IAJuliaMossGambler);

        Config.RandExc			= Configs.GetInt(0,100,50,"Random","RandExc",IAJuliaMossGambler);
        Config.MaxExcOpt		= Configs.GetInt(0,100,6,"Random","MaxExcOpt",IAJuliaMossGambler);

        Config.RandLevel		= Configs.GetInt(0,100,85,"Random","RandLevel",IAJuliaMossGambler);
        Config.MaxLevel			= Configs.GetInt(0,100,13,"Random","MaxLevel",IAJuliaMossGambler);

        Config.RandOptAdd		= Configs.GetInt(0,100,85,"Random","RandOptAdd",IAJuliaMossGambler);
        Config.MaxOptAdd		= Configs.GetInt(0,100,7,"Random","MaxOptAdd",IAJuliaMossGambler);

        Config.RandLuck			= Configs.GetInt(0,100,50,"Random","RandLuck",IAJuliaMossGambler);
        Config.RandSkill		= Configs.GetInt(0,100,50,"Random","RandSkill",IAJuliaMossGambler);
        Config.RandAncient		= Configs.GetInt(0,100,20,"Random","RandAncient",IAJuliaMossGambler);

        Moss.LoadItemInfo();

        if(Config.EnableTimer)
        {
            this->LoadTimeConfig();
        }
        else
        {
            this->Opened = TRUE;
        }
    }
}

void cMoss::LoadItemInfo()
{
    FILE *File;
    File = fopen("..\\Data\\Lang\\Kor\\Item(Kor).txt","r");

    if(File == NULL)
    {
        Config.Enable = 0;
        Log.ConsoleOutPut(0,c_Red,t_NULL,"[Moss The Gambler] Item.txt nao encontrado, Moss The Gambler inativo.");
    }
    else
    {
        int Group = 0,j = 0;
        char zBuffer[1024],C[12] = {0};

        while(!feof(File))
        {
            fgets(zBuffer,1024,File);

            if(!strncmp(zBuffer,"//",2) || !strncmp(zBuffer,"end",3) || (zBuffer[0] == 0xA)) continue;

            sprintf(C,"%d",Group);

            if(!strncmp(zBuffer,C,strlen(C)))
            {
                Group++;

                if(Group > 6) break;

                j = 0;

                continue;
            }

            if(Group > 0)
            {
                sscanf(zBuffer,"%d",&ItemInfo[Group-1][j].Index);
                OrderItems[Group-1] = ++j;
            }
        }

        fclose(File);
        Log.ConsoleOutPut(1,c_Yellow,t_NULL,"[û] [Moss Gambler]\tIniciado.");
    }
}

void cMoss::LoadTimeConfig()
{
    FILE *File;
    File = fopen(IAJuliaEventTime,"r");

    if(File == NULL)
    {
        Log.ConsoleOutPut(0,c_Red,t_NULL,"[û] [Moss The Gambler]\tImpossivel abrir EventTime.dat, timer desativado.");

        Config.EnableTimer = 0;
    }
    else
    {
        char zBuffer[1024];
        bool bFlag = false;
        int j = 0;

        while (!feof(File))
        {
            fgets(zBuffer,1024,File);

            if(!strncmp(zBuffer,"//",2) || zBuffer[0] == 0xA || !strncmp(zBuffer,"end",3)) continue;

            if(!strncmp(zBuffer,"0",1))
            {
                bFlag = true;

                continue;
            }

            if(bFlag)
            {
                int indexEvent,closeHour,closeMin;
                sscanf(zBuffer,"%d %d %d %d",&indexEvent,&Timer[j].hour,&Timer[j].minute,&Timer[j].delay);

                if(indexEvent != 1)
                {
                    break;
                }

                closeMin = Timer[j].minute + Timer[j].delay;
                closeHour = Timer[j].hour;

                while (closeMin >= 60)
                {
                    closeMin -=60;
                    closeHour++;
                }

                Timer[j].closehour = closeHour;
                Timer[j].closemin = closeMin;
                j++;
            }
        }

        this->AmountTimers = j;
        this->Opened = FALSE;

        fclose(File);
    }
}

void cMoss::CheckTime()
{
    if(Config.Enable && Config.EnableTimer)
    {
        CTime t = CTime::GetCurrentTime();

        short hour,min;

        min = t.GetMinute();
        hour = t.GetHour();

        if(this->Opened == FALSE)
	    {
            this->Disappear();
	    }

        if (t.GetSecond() == 0)
        {
            for (int i=0; i<AmountTimers; i++)
            {
                for (int j=1; j<6; j++)
                {
                    int BeforeOpenMin, BeforeOpenHour;
                    BeforeOpenMin = Timer[i].minute - j;
                    BeforeOpenHour = Timer[i].hour;

                    if (BeforeOpenMin < 0 ) {
                        BeforeOpenMin += 60;
                        BeforeOpenHour --;
                    }

                    if(hour == BeforeOpenHour && min == BeforeOpenMin)
                    {
                        Chat.MessageAll(0,0,NULL,"Moss The Gambler will arrive after %d minute(s)",j);

                        break;
                    }
                }

                if (hour == Timer[i].hour && min == Timer[i].minute)
                {
                    Chat.MessageAll(0,0,NULL,"Moss The Gambler is arrived!");

                    this->Spawn();
                    this->Opened = TRUE;
                }

                if (hour == Timer[i].closehour && min == Timer[i].closemin)
                {
                    Chat.MessageAll(0,0,NULL,"Moss The Gambler is closed!");

                    this->Disappear();
                    this->Opened = FALSE;
                }
            }
        }
    }
}

BOOL cMoss::GetStatusMoss()
{
    return this->Opened;
}

void cMoss::Spawn()
{
    Monster.MonsterAddAndSpawn(492,51,0,22,225,22,225,2);
}

void cMoss::Disappear()
{
    for(int i = 0; i < OBJ_MAXMONSTER;i++)
    {
        OBJECTSTRUCT *mObj = (OBJECTSTRUCT*)OBJECT_POINTER(i);

        if(mObj == NULL)
        {
            return;
        }

        if(mObj->Class == 492)
        {
            gObjDel(i);
        }
    }

    int MobCount = *(DWORD *)(MonsterCount);

    MobCount--;
}

BOOL cMoss::BuyItem(int aIndex, unsigned char * aRecv)
{
    OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);

    if(gObj->TargetShopNumber != 492)
    {
        return FALSE;
    }

    if(Moss.GetStatusMoss() == FALSE)
    {
        Chat.Message(1, gObj,"[Moss The Gambler] Nao estou vendendo itens agora.");

        return TRUE;
    }

    if(this->Delay == true)
    {
        Chat.Message(1, gObj,"[Moss The Gambler] Aguarde 1.5s para comprar novamente.");

        return TRUE;
    }

    if(gObj->Money < Config.PriceZen)
    {
        Chat.Message(1, gObj,"[Moss The Gambler] Voce nao tem zen suficiente.");

        return TRUE;
    }

    if(AddTab[gObj->m_Index].PC_PlayerPoints < Config.PricePCPoint)
    {
        Chat.Message(1, gObj,"[Moss The Gambler] Voce nao tem PCPoint suficiente.");

        return TRUE;
    }

    if(gObj->m_wCashPoint < Config.PriceWCoin)
    {
        Chat.Message(1, gObj,"[Moss The Gambler] Voce nao tem WCoin suficiente.");

        return TRUE;
    }

    switch(aRecv[3])
    {
        case 0:
        {
            BuyType = 0;

            break;
        }
        case 2:
        {
            BuyType = rand() % 2 + 1;

            if (BuyType == 2)
            {
                BuyType = 3;
            }

            break;
        }
        case 4:
        {
            BuyType = 2;
            
            break;
        }
        case 6:
        {
            BuyType = 4;

            break;
        }
        case 24:
        {
            BuyType = 5;

            break;
        }
        default:
        {
            break;
        }
    }

    int Index       = rand()%OrderItems[BuyType];
    int Type        = ITEMGET(BuyType,ItemInfo[BuyType][Index].Index);
    int Level	    = RandValue(OPT_LEVEL);
    int Option1	    = RandValue(OPT_SKILL);
    int Option2	    = RandValue(OPT_LUCK);
    int Option3	    = RandValue(OPT_ADD);
    int NewOption   = RandValue(OPT_EXC);
    int SetOption   = RandValue(OPT_ANC);

    int X,Y;
    GSItemGetSize(Type,X,Y);

    if(GSCheckInventoryEmptySpace(gObj,Y,X) == 0)
    {
        Chat.Message(1, gObj,"[Moss The Gambler] Seu inventario esta cheio.");

        return TRUE;
    }

    int Dur = ItemGetDurability(Type,Level,NewOption,SetOption);
    ItemSerialCreateSend(gObj->m_Index,236,0,0,Type,Level,Dur,Option1,Option2,Option3,0,NewOption,SetOption);

    Log.ConsoleOutPut(0, c_Red,t_NULL,"[Moss The Gambler] %s Recebeu [%d] %d %d %d %d %d %d",gObj->Name,Type,Level,Option1,Option2,Option3,NewOption,SetOption);

    if(NewOption > 0)
    {
        Chat.Message(1, gObj,"[Moss The Gambler] Parabens, voce recebeu um item valioso!");
    }

    if(Config.PriceZen > 0)
    {
        gObj->Money -= Config.PriceZen;
        GCMoneySend(gObj->m_Index,gObj->Money);
    }

    if(Config.PricePCPoint > 0)
    {
        PCPoint.UpdatePoints(gObj,Config.PricePCPoint,MINUS,PCPOINT);
    }
    
    if(Config.PriceWCoin > 0)
    {   
        PCPoint.UpdatePoints(gObj,Config.PriceWCoin  ,MINUS,WCOIN);
    }

    _beginthread(MossBuyDelay,0,0);

    return TRUE;
}

int cMoss::RandValue(int IndexOption)
{
    int rValue = 0;

    switch(IndexOption)
    {
        case OPT_LEVEL:
        {
            rValue = rand()%100+1;
            rValue > Config.RandLevel ?	rValue =  0 : rValue =  rand()%(Config.MaxLevel + 1);

            break;
        }
        case OPT_SKILL:
        {
            rValue = rand()%100+1;
            rValue > Config.RandSkill ? rValue =  0 : rValue =  1;

            break;
        }
        case OPT_LUCK:
        {
            rValue = rand()%100+1;
            rValue > Config.RandLuck ? rValue =  0 : rValue =  1;

            break;
        }
        case OPT_ADD:
        {
            rValue = rand()%100+1;
            rValue > Config.RandOptAdd ? rValue =  0 : rValue =  rand()%(Config.MaxOptAdd + 1);

            break;
        }
        case OPT_EXC:
        {
            rValue = rand()%100+1;
            rValue > Config.RandExc ? rValue =  0 : rValue =  Utilits.GenExcOpt(rand()%(Config.MaxExcOpt + 1));

            break;
        }
        case OPT_ANC:
        {
            rValue = rand()%100+1;
            rValue > Config.RandAncient ? rValue =  0 : rValue =  10;

            break;
        }
    }

    return rValue;
}

#endif