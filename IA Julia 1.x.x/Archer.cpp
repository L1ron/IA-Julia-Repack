#include "Archer.h"
#include "StdAfx.h"
#include "Logger.h"
#include "Configs.h"
#include "ChatCommands.h"
#include "Utilits.h"
#include "PCPoint.h"

cGoldenArcher GoldenArcher;

enum
{
	INV_CHECK,
	INV_DEL
};

void cGoldenArcher::ResetConfig()
{
	ArcherItemsCount = 0;
    memset(&Config,0,sizeof(Config));
    memset(&ItemsPrize,0,sizeof(ItemsPrize));
}

void cGoldenArcher::Load()
{
    ResetConfig();
    Config.Enabled				= Configs.GetInt(0, 1, 1, "GoldenArcher", "ArcherEnabled", IAJuliaArcher);

    if(!Config.Enabled)
	{
        return;
	}

    Config.NeedRenaAmount	= Configs.GetInt(0, 250,							7,		"GoldenArcher", "RenasCount",		IAJuliaArcher);
    Config.WCoinsReward		= Configs.GetInt(0, PCPoint.Config.MaximumWCPoints,	1,		"GoldenArcher", "WCoinsReward",		IAJuliaArcher);
    Config.PCPointsReward	= Configs.GetInt(0, PCPoint.Config.MaximumPCPoints,	1,		"GoldenArcher", "PCPointsReward",	IAJuliaArcher);
    Config.ZenReward		= Configs.GetInt(0, 2000000000,						100000, "GoldenArcher", "ZenReward",		IAJuliaArcher);
    Config.ResetLimit		= Configs.GetInt(0, 32767,							5,		"GoldenArcher",	"ResetLimit",		IAJuliaArcher);

    FILE *file;
    file = fopen(IAJuliaArcher,"r");

    if (file == NULL)
    {
        Log.ConsoleOutPut(1, c_Red, t_Error, "[X] [Golden Archer]\tCan`t Find %s", IAJuliaArcher);
        Config.Enabled = 0;
        return;
    }

    char Buff[256];
    int Flag = 0;
    ArcherItemsCount = 0;

    while (!feof(file))
    {
        fgets(Buff,256,file);

        if(Utilits.IsBadFileLine(Buff, Flag))
            continue;

        if (Flag == 1)
        {
            int n[9];
            sscanf(Buff,"%d %d %d %d %d %d %d %d %d", &n[0], &n[1], &n[2], &n[3], &n[4], &n[5], &n[6], &n[7], &n[8]);

            ItemsPrize[ArcherItemsCount].Index		= n[0];
            ItemsPrize[ArcherItemsCount].ItemID		= n[1];
            ItemsPrize[ArcherItemsCount].RateItem	= n[2];
            ItemsPrize[ArcherItemsCount].MaxLvl		= n[3];
            ItemsPrize[ArcherItemsCount].RateSkill	= n[4];
            ItemsPrize[ArcherItemsCount].RateLuck	= n[5];
            ItemsPrize[ArcherItemsCount].MaxOpt		= n[6];
            ItemsPrize[ArcherItemsCount].RateExc	= n[7];
            ItemsPrize[ArcherItemsCount].MaxExcOpt	= n[8];

            ArcherItemsCount++;
        }
    }

    fclose(file);
    Log.ConsoleOutPut(1, c_Yellow, t_ARCHER, "[û] [Golden Archer]\tGolden Archer Items Loaded [%d]", ArcherItemsCount);
}

void cGoldenArcher::GoldenArcherClick(LPOBJ gObj)
{
    MaxRateItem = 0;

    if(AddTab[gObj->m_Index].Resets > Config.ResetLimit)
    {
        Chat.Message(1, gObj,"[Golden Archer] You are strong now and don't need my help.");

        return;
    }

    unsigned short *CurrentRena = (unsigned short*)&gObj->m_Quest[29];

    if (*CurrentRena > Config.NeedRenaAmount )
	{
        *CurrentRena = 0;
	}

    if (!this->ChekingRena(gObj,INV_CHECK))
    {
        Chat.Message(1, gObj,"[Golden Archer] Your haven't Rena's in Inventory. Search Rena's and come back to me.");

        return;
    }

    ++*CurrentRena;
    this->ChekingRena(gObj,INV_DEL);

    if (*CurrentRena < Config.NeedRenaAmount )
    {
        Chat.Message(1, gObj,"[Golden Archer] Your Rena accepted. You have %d Rena's, for reward need %d more",*CurrentRena,Config.NeedRenaAmount - *CurrentRena);
    }

    if (*CurrentRena == Config.NeedRenaAmount)
    {
        if(ArcherItemsCount > 0)
        {
            int ArrayItemsIndex[MAX_ITEM_PRIZE];
            int g = -1;

            short RandValue = rand()%100 + 1;
            if (RandValue > MaxRateItem) RandValue = MaxRateItem;

            for (int i = 0; i < ArcherItemsCount; i++)
			{
                if (RandValue <= ItemsPrize[i].RateItem)
				{
                    ArrayItemsIndex[++g] = i;
				}
			}

            RandValue = rand()% (g + 1);
            int PrizeIndex = ArrayItemsIndex[RandValue];

            int Level,Skill,Luck,Opt,Exc;

            Level = rand()%(ItemsPrize[PrizeIndex].MaxLvl + 1);
            Opt   = rand()%(ItemsPrize[PrizeIndex].MaxOpt + 1);

            Skill = rand() % 100 + 1 < ItemsPrize[PrizeIndex].RateSkill ? Skill = 1 : Skill = 0;
            Luck  = rand() % 100 + 1 < ItemsPrize[PrizeIndex].RateLuck  ? Luck = 1  : Luck = 0;
            Exc   = rand() % 100 + 1 < ItemsPrize[PrizeIndex].RateExc   ? Exc = Utilits.GenExcOpt(rand()%(ItemsPrize[PrizeIndex].MaxExcOpt + 1)) : Exc = 0;

            *CurrentRena = 0;
            Chat.Message(1, gObj,"[Golden Archer] Thank you for renas! Take my rewards for you.");
            Log.ConsoleOutPut(1,c_Magenta,t_ARCHER,"[Golden Archer] Drop\t%d %d %d %d %d %d %d 0",ItemsPrize[PrizeIndex].Index,ItemsPrize[PrizeIndex].ItemID,Level,Skill,Luck,Opt,Exc);

            int Item = ITEMGET(ItemsPrize[PrizeIndex].Index,ItemsPrize[PrizeIndex].ItemID);
            ItemSerialCreateSend(gObj->m_Index,gObj->MapNumber,(BYTE)gObj->X,(BYTE)gObj->Y,Item,Level,0,Skill,Luck,Opt,gObj->m_Index,Exc,0);
        }

        if (Config.ZenReward > 0)
        {
            int UpdateZen = gObj->Money + Config.ZenReward;

            if (UpdateZen > 2000000000)
                UpdateZen = 2000000000;
            gObj->Money = UpdateZen;
            GCMoneySend(gObj->m_Index,UpdateZen);
            Chat.Message(1, gObj,"[Golden Archer] Added Zen:%d", Config.ZenReward);
        }

        if (Config.WCoinsReward > 0)
        {
            PCPoint.UpdatePoints(gObj,Config.WCoinsReward,PLUS,WCOIN);
            Chat.Message(1, gObj,"[Golden Archer] Added Coins:%d", Config.WCoinsReward);
        }

        if (Config.PCPointsReward > 0)
        {
            PCPoint.UpdatePoints(gObj,Config.PCPointsReward,PLUS,PCPOINT);
            Chat.Message(1, gObj,"[Golden Archer] Added PCPoints:%d", Config.PCPointsReward);
        }
    }
}

bool cGoldenArcher::ChekingRena(LPOBJ gObj,int Mode)
{
    for (BYTE i = 12; i<76; i++ )
    {
        if((gObj->pInventory[i].m_Type == 0x01C15) && (gObj->pInventory[i].m_Level == 0))
        {
            switch (Mode)
            {
				case INV_CHECK:
				{
					return true;
				}
				case INV_DEL:
				{
					gObjInventoryDeleteItem( gObj->m_Index , i );
					GCInventoryItemDeleteSend( gObj->m_Index , i  , 1 );

					return true;
				}
            }
        }
    }

    return false;
}