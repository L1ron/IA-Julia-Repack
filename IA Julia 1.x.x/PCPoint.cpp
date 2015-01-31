#include "PCPoint.h"
#include "Logger.h"
#include "Configs.h"
#include <Windows.h>
#include "ChatCommands.h"
#include "Query.h"
#include "Utilits.h"

cPCPoint PCPoint;

void cPCPoint::ResetConfig()
{
    Config.MaximumWCPoints		= 0;

    Config.WebEnabled			= 0;
    Config.MaximumWebPoints		= 0;
    Config.WebColumnFloat		= 0;

    Config.Enabled				= 0;

    Config.MaximumPCPoints		= 0;
    Config.AddPCPointsSec		= 0;
    Config.AddPCPointsCount		= 0;

    for (int i = 0; i < 3; i++)
    {
        AmountRecords[i] = 0;
    }

    for (int i = 0; i < MAX_PCMOB; i++)
    {
        PCShop[i].Index			= 0;
        PCShop[i].ID			= 0;
        PCShop[i].Level			= 0;
        PCShop[i].Opt			= 0;
        PCShop[i].Luck			= 0;
        PCShop[i].Skill			= 0;
        PCShop[i].Dur			= 0;
        PCShop[i].Exc			= 0;
        PCShop[i].Ancient		= 0;
        PCShop[i].NewOpt1		= 0;
        PCShop[i].NewOpt2		= 0;
        PCShop[i].NewOpt3		= 0;
        PCShop[i].NewOpt4		= 0;
        PCShop[i].NewOpt5		= 0;
        PCShop[i].Cost			= 0;

        PCMonsters[i].MobID		= 0;
        PCMonsters[i].PCPoints	= 0;

        WCoinMonsters[i].MobID	= 0;
        WCoinMonsters[i].WCoins	= 0;
    }
}

void cPCPoint::Load()
{
    ResetConfig();

    Config.MaximumWCPoints		= Configs.GetInt(0, 32000,					10000,	"WCoins",		"MaximumWCPoints",			IAJuliaPcPoints);

    Config.WebEnabled			= Configs.GetInt(0, 1,						0,		"WebPoints",	"Enabled",					IAJuliaPcPoints);
    if(Config.WebEnabled)
    {
        GetPrivateProfileString("WebPoints","WebTable","web_table",Config.WebTable,sizeof(Config.WebTable),IAJuliaPcPoints);
        GetPrivateProfileString("WebPoints","WebColumn","web_column",Config.WebColumn,sizeof(Config.WebColumn),IAJuliaPcPoints);
        Config.MaximumWebPoints	= Configs.GetInt(0, 32000,					10000,	"WebPoints",	"MaximumWebPoints",			IAJuliaPcPoints);
        Config.WebColumnFloat	= Configs.GetInt(0, 1,							0,	"WebPoints",	"WebColumnFloat",			IAJuliaPcPoints);
    }

    Config.Enabled				= Configs.GetInt(0, 1,						1,		"PCPoints",		"Enabled",					IAJuliaPcPoints);
    if (!Config.Enabled) return;

    Config.MaximumPCPoints		= Configs.GetInt(0, 32000,					10000,	"PCPoints",		"MaximumPCPoints",			IAJuliaPcPoints);
    Config.AddPCPointsSec		= Configs.GetInt(0, 6000000,				3600,	"PCPoints",		"AddPCPointsSec",			IAJuliaPcPoints);
    Config.AddPCPointsCount		= Configs.GetInt(0, Config.MaximumPCPoints,	10,		"PCPoints",		"AddPCPointsCount",			IAJuliaPcPoints);

    this->LoadConfigs();
}

void cPCPoint::LoadConfigs()
{
    this->ChekingCallInitItemsInShop = false;

    FILE *file;
    file = fopen(IAJuliaPcPoints,"r");

    if (file == NULL)
    {
        Config.Enabled = 0;
        Log.ConsoleOutPut(1, c_Red, t_Error, "[X] [PC Point]\tCan`t Find %s", IAJuliaPcPoints);
        return;
    }

    char Buff[256];
    int Flag = 0;

    while (!feof(file))
    {
        fgets(Buff,256,file);

        if(Utilits.IsBadFileLine(Buff, Flag))
        {
            continue;
        }

        if(Flag == 1)
        {
            int i = AmountRecords[0];
            int n[15];
            sscanf(Buff,"%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", &n[0], &n[1], &n[2], &n[3], &n[4], &n[5], &n[6], &n[7], &n[8], &n[9], &n[10], &n[11], &n[12], &n[13], &n[14]);
            PCShop[i].Index		= n[0];
            PCShop[i].ID		= n[1];
            PCShop[i].Level		= n[2];
            PCShop[i].Opt		= n[3];
            PCShop[i].Luck		= n[4];
            PCShop[i].Skill		= n[5];
            PCShop[i].Dur		= n[6];
            PCShop[i].Exc		= n[7];
            PCShop[i].Ancient	= n[8];
            PCShop[i].NewOpt1	= n[9];
            PCShop[i].NewOpt2	= n[10];
            PCShop[i].NewOpt3	= n[11];
            PCShop[i].NewOpt4	= n[12];
            PCShop[i].NewOpt5	= n[13];
            PCShop[i].Cost		= n[14];
            AmountRecords[0]++;
        }

        if(Flag == 2)
        {
            int i = AmountRecords[1];
            int n[2];

            sscanf(Buff,"%d %d", &n[0], &n[1]);
            PCMonsters[i].MobID		= n[0];
            PCMonsters[i].PCPoints	= n[1];

            AmountRecords[1]++;
        }

        if (Flag == 3)
        {
            int i = AmountRecords[2];
            int n[2];

            sscanf(Buff,"%d %d", &n[0], &n[1]);
            WCoinMonsters[i].MobID	= n[0];
            WCoinMonsters[i].WCoins	= n[1];

            AmountRecords[2]++;
        }
    }
    fclose(file);
    Log.ConsoleOutPut(1, c_Cyan, t_PCPOINT, "[û] [PC Point]\tPC Shop Item Loaded [%d]", AmountRecords[0]);
    Log.ConsoleOutPut(1, c_Cyan, t_PCPOINT, "[û] [PC Point]\tTotal Monster Loaded [%d]", AmountRecords[1]);
    Log.ConsoleOutPut(1, c_Cyan, t_PCPOINT, "[û] [WCoin]\t\tTotal Monster Loaded [%d]", AmountRecords[2]);
}

void cPCPoint::Tick(LPOBJ gObj)
{
    if (PCPoint.Config.Enabled && PCPoint.Config.AddPCPointsSec > 0 && !AddTab[gObj->m_Index].OfflineTrade)
    {
        AddTab[gObj->m_Index].PC_OnlineTimer++;
        if (AddTab[gObj->m_Index].PC_OnlineTimer == PCPoint.Config.AddPCPointsSec)
        {
            AddTab[gObj->m_Index].PC_OnlineTimer = 0;
            PCPoint.UpdatePoints(gObj,PCPoint.Config.AddPCPointsCount,PLUS,PCPOINT);

            Chat.Message(1, gObj,"[PointShop] You earned %d Points for being online!", PCPoint.Config.AddPCPointsCount);
            Chat.Message(1, gObj,"[PointShop] You have been online %d Hours!", AddTab[gObj->m_Index].ON_Hour);
        }
    }
}

#pragma warning(disable: 4018 4244)
void cPCPoint::CreatePacketShop()
{
    int PacketSize = 0;
    int PacketFlag = 0;
    int Size       = 0;

    BYTE Packet1[11] =
	{
		0xC1, 0x05, 0xD0, 0x06, 0x00, 0xC2, 0x00, 0x36, 0x31,
		HIBYTE(AmountRecords[0]),
		LOBYTE(AmountRecords[0])
	};

    BYTE Packet2[4680];

    for(int i = 0; i < AmountRecords[0]; i++)
    {
        BYTE ItemInfo[13];

		ItemInfo[0] = PCShop[i].SlotX;
        ItemInfo[1] = PCShop[i].Reward & 0xFF;
        ItemInfo[2] = (PCShop[i].Level * 8) | (PCShop[i].Skill * 128) | (PCShop[i].Luck * 4) | (PCShop[i].Opt & 3);
        ItemInfo[3] = PCShop[i].Dur;
        ItemInfo[4] = (PCShop[i].Reward & 0x100) >> 1;

        if(PCShop[i].Opt > 3)
		{
			ItemInfo[4]  |= 0x40;
		}

        ItemInfo[4] |= PCShop[i].Exc;
        ItemInfo[5] = PCShop[i].Ancient;
        ItemInfo[6] = (PCShop[i].Reward & 0x1E00 ) >> 5;
        ItemInfo[7] = PCShop[i].NewOpt1;
        ItemInfo[8] = PCShop[i].NewOpt2;
        ItemInfo[9] = PCShop[i].NewOpt3;
        ItemInfo[10] = PCShop[i].NewOpt4;
        ItemInfo[11] = PCShop[i].NewOpt5;
        ItemInfo[12] = PCShop[i].Cost;

        PacketSize = (sizeof(ItemInfo) * (i + 1));
        memcpy(&Packet2[PacketFlag], ItemInfo, sizeof(ItemInfo)); // #check
        PacketFlag = PacketSize;
    }

    Size = (sizeof(Packet1) + PacketSize);
    memcpy(&PCPointPacket, Packet1, sizeof(Packet1));
    memcpy(&PCPointPacket[sizeof(Packet1)], Packet2, sizeof(Packet1) + PacketSize);
    PCPointPacket[6]    = HIBYTE(Size);
    PCPointPacket[7]    = LOBYTE(Size);
   
	this->PacketSizes = (sizeof(Packet1) + PacketSize);
}


void cPCPoint::InitItemShop()
{
    this->ChekingCallInitItemsInShop = true;

    for (int i = 0; i < 15; i++)
        for (int j = 0; j < 8; j++)
            this->ArrayFiledItems[i][j] = false;

    for (int k = 0; k <  AmountRecords[0]; k++)
    {
        PCShop[k].Reward = PCShop[k].Index * 512 + PCShop[k].ID;
        if (PCShop[k].Dur == 0) PCShop[k].Dur = ItemGetDurability(PCShop[k].Reward,PCShop[k].Level,PCShop[k].Exc,0);
        GSItemGetSize(PCShop[k].Reward,PCShop[k].X,PCShop[k].Y);
        PCShop[k].SlotX = this->gObjCalcItems(PCShop[k].X,PCShop[k].Y);
    }
    this->CreatePacketShop();
}

void cPCPoint::OpenShop(int Index)
{
    OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(Index);
    if (this->ChekingCallInitItemsInShop == false)
        this->InitItemShop();
    DataSend(Index,this->PCPointPacket,this->PacketSizes);
    Chat.Message(1, gObj,"");
}

int cPCPoint::gObjCalcItems(int X, int Y)
{
    for (int i = 0; i < 15; i++)
        for (int j = 0; j < 8; j++)
            if (ArrayFiledItems[i][j] == false)
            {
                bool bFlag = true;

                for (short kX = 0; kX < X; kX++)
                    for(short kY = 0; kY < Y; kY++)
                        if ( i + kY > 14 || j + kX > 7 || ArrayFiledItems[i+kY][j+kX])
                            bFlag = false;

                if (bFlag)
                {
                    for (short kX = 0; kX < X; kX++)
                        for(short kY = 0; kY < Y; kY++)
                            ArrayFiledItems[i+kY][j+kX] = true;
                    return i*8 + j;
                }
            }
    return -1;
}

void cPCPoint::BuyItem(int Index,int Position)
{
    int IndexItem = -1;

    for(int i = 0; i < AmountRecords[0]; i++)
        if (Position == PCShop[i].SlotX ) IndexItem = i;

    OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(Index);

    if(IndexItem != -1)
    {
        if (PCShop[IndexItem].Cost <= AddTab[gObj->m_Index].PC_PlayerPoints)
        {
            if ( GSCheckInventoryEmptySpace(gObj,PCShop[IndexItem].Y,PCShop[IndexItem].X) != 0 )
            {

                ItemSerialCreateSend(gObj->m_Index,236,0,0,PCShop[IndexItem].Reward,PCShop[IndexItem].Level,PCShop[IndexItem].Dur,PCShop[IndexItem].Skill,PCShop[IndexItem].Luck,PCShop[IndexItem].Opt,-1,PCShop[IndexItem].Exc,PCShop[IndexItem].Ancient);

                Log.ConsoleOutPut(1, c_Cyan, t_PCPOINT, "[%s:%s] [PointShop]\tBuy Item [%d %d] Cost [%d]",gObj->AccountID, gObj->Name, PCShop[IndexItem].Index, PCShop[IndexItem].ID, PCShop[IndexItem].Cost);
                this->UpdatePoints(gObj,PCShop[IndexItem].Cost,MINUS,PCPOINT);
            }
            else
                Chat.Message(1, gObj,"[PointShop] Your inventory is full !");
        }
        else
            Chat.Message(1, gObj,"[PointShop] Can`t buy, need %d more PCPoints!", PCShop[IndexItem].Cost - AddTab[gObj->m_Index].PC_PlayerPoints);
    }
}

void cPCPoint::InitPCPointForPlayer(LPOBJ gObj, int AmountPoints )
{
    if (AmountPoints > Config.MaximumPCPoints) AmountPoints = Config.MaximumPCPoints;
    AddTab[gObj->m_Index].PC_PlayerPoints = AmountPoints;

    BYTE Packet[8] = {0xC1, 0x08 , 0xD0 , 0x04 , LOBYTE(AmountPoints), HIBYTE(AmountPoints),
                      LOBYTE(Config.MaximumPCPoints), HIBYTE(Config.MaximumPCPoints)
                     };

    DataSend(gObj->m_Index, (PBYTE)Packet, Packet[1]);
}

void cPCPoint::UpdatePoints(LPOBJ gObj,int CountPoints,eModeUpdate Mode,eTypePoint Type)
{
    char ModeType;

    if (Type == WEBPOINTS)
    {
        if(!Config.WebEnabled)
            return;
        if(gObj->Connected < PLAYER_PLAYING)
        {
            Log.ConsoleOutPut(0, c_Red, t_SQL, "[%d] [SQL] Error\tWebPoints UPDATE (Player not playing!)", gObj->m_Index);
            return;
        }
        if (Config.WebColumnFloat)
        {
            if (Mode == PLUS && (AddTab[gObj->m_Index].WEB_Points_Float + CountPoints > PCPoint.Config.MaximumPCPoints ||
                                 AddTab[gObj->m_Index].WEB_Points_Float + CountPoints <= 0 ))
            {
                Chat.Message(1, gObj,"[WebPoints] You have maximum WebPoints");
                return;
            }
        }
        else
        {
            if (Mode == PLUS && (AddTab[gObj->m_Index].WEB_Points + CountPoints > PCPoint.Config.MaximumPCPoints ||
                                 AddTab[gObj->m_Index].WEB_Points + CountPoints <= 0 ))
            {
                Chat.Message(1, gObj,"[WebPoints] You have maximum WebPoints");
                return;
            }
        }
    }

    if (Type == PCPOINT)
    {
        if(gObj->Connected < PLAYER_PLAYING)
        {
            Log.ConsoleOutPut(0, c_Red, t_SQL, "[%d] [SQL] Error\tPcPoint UPDATE (Player not playing!)", gObj->m_Index);
            return;
        }
        if (Mode == PLUS && (AddTab[gObj->m_Index].PC_PlayerPoints + CountPoints > PCPoint.Config.MaximumPCPoints ||
                             AddTab[gObj->m_Index].PC_PlayerPoints + CountPoints <= 0 ))
        {
            Chat.Message(1, gObj,"[PCPoint] You have maximum PCPoints");
            return;
        }
    }

    if (Type ==  WCOIN )
    {
        if(gObj->Connected < PLAYER_LOGGED)
        {
            Log.ConsoleOutPut(0, c_Red, t_SQL, "[%d] [SQL] Error\tWCoin UPDATE (Player not logged!)", gObj->m_Index);
            return;
        }
        if (Mode == PLUS && (gObj->m_wCashPoint + CountPoints > PCPoint.Config.MaximumWCPoints ||
                             gObj->m_wCashPoint + CountPoints <= 0))
        {
            Chat.Message(1, gObj,"[WCoins] You have maximum WCoins");
            return;
        }
    }

    switch(Mode)
    {
		case PLUS:
		{
			ModeType = '+';

			break;
		}
		case MINUS:
		{
			ModeType = '-';

			break;
		}
    }

    if (Type == PCPOINT)
    {
        MuOnlineQuery.ExecQuery("UPDATE Character SET PCPoint = (PCPoint %c %d) WHERE Name = '%s'", ModeType, CountPoints, gObj->Name);
        MuOnlineQuery.Fetch();
        MuOnlineQuery.Close();

        MuOnlineQuery.ExecQuery("SELECT PCPoint FROM Character WHERE Name = '%s'", gObj->Name);
        MuOnlineQuery.Fetch();
        AddTab[gObj->m_Index].PC_PlayerPoints = MuOnlineQuery.GetAsInteger("PCPoint");
        MuOnlineQuery.Close();

		BYTE Packet[8] =
		{
			0xC1, 0x08 , 0xD0 , 0x04 ,
			LOBYTE(AddTab[gObj->m_Index].PC_PlayerPoints),
			HIBYTE(AddTab[gObj->m_Index].PC_PlayerPoints),
			LOBYTE(Config.MaximumPCPoints),
			HIBYTE(Config.MaximumPCPoints)
		};

        DataSend(gObj->m_Index, (PBYTE)Packet, Packet[1]);
    }

    if (Type == WCOIN)
    {
        Me_MuOnlineQuery.ExecQuery("UPDATE MEMB_INFO SET CSPoints = (CSPoints %c %d) WHERE memb___id = '%s'", ModeType, CountPoints, gObj->AccountID);
        Me_MuOnlineQuery.Fetch();
        Me_MuOnlineQuery.Close();

        Me_MuOnlineQuery.ExecQuery("SELECT CSPoints FROM MEMB_INFO WHERE memb___id = '%s'", gObj->AccountID);
        Me_MuOnlineQuery.Fetch();
        gObj->m_wCashPoint = Me_MuOnlineQuery.GetAsInteger("CSPoints");
        Me_MuOnlineQuery.Close();
    }

    if (Type == WEBPOINTS)
    {
        MuOnlineQuery.ExecQuery("UPDATE %s SET %s = (%s %c %d) WHERE memb___id = '%s'", Config.WebTable, Config.WebColumn, Config.WebColumn, ModeType, CountPoints, gObj->AccountID);
        MuOnlineQuery.Fetch();
        MuOnlineQuery.Close();

        MuOnlineQuery.ExecQuery("SELECT %s FROM %s WHERE memb___id = '%s'",PCPoint.Config.WebColumn ,PCPoint.Config.WebTable , gObj->AccountID);
        MuOnlineQuery.Fetch();

        if(PCPoint.Config.WebColumnFloat)
            AddTab[gObj->m_Index].WEB_Points_Float	= MuOnlineQuery.GetAsFloat(PCPoint.Config.WebColumn);
        else
            AddTab[gObj->m_Index].WEB_Points		= MuOnlineQuery.GetAsInteger(PCPoint.Config.WebColumn);

        MuOnlineQuery.Close();
    }
}

void cPCPoint::RewardsPointsKillMob(LPOBJ gObj,LPOBJ mObj,eTypePoint Type)
{
    switch (Type)
    {
		case PCPOINT:
		{
			for (int i = 0; i < AmountRecords[1]; i++)
			{
				if ( PCMonsters[i].MobID == mObj->Class )
				{
					this->UpdatePoints(gObj,PCMonsters[i].PCPoints,PLUS,Type);
					Chat.Message(1, gObj,"[PCPoint] You earned %d PCPoints",PCMonsters[i].PCPoints);
					
					return;
				}
			}

			return;
		}
		case WCOIN:
		{
			for (int i = 0; i < AmountRecords[2]; i++)
			{
				if ( WCoinMonsters[i].MobID == mObj->Class )
				{
					this->UpdatePoints(gObj,WCoinMonsters[i].WCoins,PLUS,Type);
					Chat.Message(1, gObj,"[WCoin] You earned %d WCoins",WCoinMonsters[i].WCoins);

					return;
				}
			}

			return;
		}
    }
}
