// ================================================== //
// #			GameServer 1.00.90					# //
// #			Imagination Arts					# //
// #			Julia Project 1.1.x					# //
// ================================================== //
// #	http://imaginationarts.net/forum/			# //
// #	http://mu.raklion.ru/						# //
// ================================================== //

#include "StdAfx.h"
#include "TradeSystem.h"
#include "ChatCommands.h"
#include "Configs.h"
#include "Logger.h"
#include "Prodef.h"
#include "Utilits.h"

cTradeSystem TradeSystem;

void cTradeSystem::ResetConfig()
{
    EnabledTrade			= 0;
    TradeItemsCount	= 0;

    for (int i=0; i<255; i++)
    {
        TradeItems[i].Group		= 0;
        TradeItems[i].Index		= 0;
        TradeItems[i].Level		= 0;
        TradeItems[i].Skill		= 0;
        TradeItems[i].Luck		= 0;
        TradeItems[i].Opt		= 0;
        TradeItems[i].Exc		= 0;
        TradeItems[i].Anc		= 0;
    }
}

void cTradeSystem::Load()
{
    ResetConfig();
    EnabledTrade = Configs.GetInt(0,1,1,"TradeSystem","EnableTradeSystem",IAJuliaTradeSystem);
    EnabledWarehouse = Configs.GetInt(0,1,1,"TradeSystem","EnableWareHouse",IAJuliaTradeSystem);
    EnabledGround = Configs.GetInt(0,1,1,"TradeSystem","EnableGroundDrop",IAJuliaTradeSystem);
    EnabledPersonal = Configs.GetInt(0,1,1,"TradeSystem","EnablePersonalShop",IAJuliaTradeSystem);

    char Buff[256];
    int Flag = 0;
    TradeItemsCount = 0;
    WareHouseItemsCount = 0;
    GroudDropItemsCount = 0;
    PersonalShopItemsCount = 0;

    FILE *conf = fopen(IAJuliaTradeSystem,"r");

    if(conf == NULL)
    {
        EnabledTrade = 0;
        EnabledWarehouse = 0;
        EnabledGround = 0;
        EnabledPersonal = 0;
        Log.ConsoleOutPut(1, c_Red, t_Error, "[X] [Trade System]\tCan`t Find %s", IAJuliaTradeSystem);
        return;
    }

    while ( !feof(conf))
    {
        fgets(Buff,256,conf);

        if(Utilits.IsBadFileLine(Buff, Flag))
            continue;

        if (Flag == 1 && EnabledTrade)
        {
            int n[8];
            //	Group	Index	Level	Skill	Luck	Opt	Exc	Anc
            sscanf(Buff, "%d %d %d %d %d %d %d %d", &n[0], &n[1], &n[2], &n[3], &n[4], &n[5], &n[6], &n[7]);
            TradeItems[TradeItemsCount].Group	= n[0];
            TradeItems[TradeItemsCount].Index	= n[1];
            TradeItems[TradeItemsCount].Level	= n[2];
            TradeItems[TradeItemsCount].Skill	= n[3];
            TradeItems[TradeItemsCount].Luck	= n[4];
            TradeItems[TradeItemsCount].Opt		= n[5];
            TradeItems[TradeItemsCount].Exc		= n[6];
            TradeItems[TradeItemsCount].Anc		= n[7];

            TradeItemsCount++;
        }

        if (Flag == 2 && EnabledWarehouse)
        {
            int n[8];
            //	Group	Index	Level	Skill	Luck	Opt	Exc	Anc
            sscanf(Buff, "%d %d %d %d %d %d %d %d", &n[0], &n[1], &n[2], &n[3], &n[4], &n[5], &n[6], &n[7]);
            WareHouseItems[WareHouseItemsCount].Group	= n[0];
            WareHouseItems[WareHouseItemsCount].Index	= n[1];
            WareHouseItems[WareHouseItemsCount].Level	= n[2];
            WareHouseItems[WareHouseItemsCount].Skill	= n[3];
            WareHouseItems[WareHouseItemsCount].Luck	= n[4];
            WareHouseItems[WareHouseItemsCount].Opt		= n[5];
            WareHouseItems[WareHouseItemsCount].Exc		= n[6];
            WareHouseItems[WareHouseItemsCount].Anc		= n[7];

            WareHouseItemsCount++;
        }

        if (Flag == 3 && EnabledGround)
        {
            int n[8];
            //	Group	Index	Level	Skill	Luck	Opt	Exc	Anc
            sscanf(Buff, "%d %d %d %d %d %d %d %d", &n[0], &n[1], &n[2], &n[3], &n[4], &n[5], &n[6], &n[7]);
            GroudDropItems[GroudDropItemsCount].Group	= n[0];
            GroudDropItems[GroudDropItemsCount].Index	= n[1];
            GroudDropItems[GroudDropItemsCount].Level	= n[2];
            GroudDropItems[GroudDropItemsCount].Skill	= n[3];
            GroudDropItems[GroudDropItemsCount].Luck	= n[4];
            GroudDropItems[GroudDropItemsCount].Opt		= n[5];
            GroudDropItems[GroudDropItemsCount].Exc		= n[6];
            GroudDropItems[GroudDropItemsCount].Anc		= n[7];

            GroudDropItemsCount++;
        }

        if (Flag == 4 && EnabledPersonal)
        {
            int n[8];
            //	Group	Index	Level	Skill	Luck	Opt	Exc	Anc
            sscanf(Buff, "%d %d %d %d %d %d %d %d", &n[0], &n[1], &n[2], &n[3], &n[4], &n[5], &n[6], &n[7]);
            PersonalShopItems[PersonalShopItemsCount].Group	= n[0];
            PersonalShopItems[PersonalShopItemsCount].Index	= n[1];
            PersonalShopItems[PersonalShopItemsCount].Level	= n[2];
            PersonalShopItems[PersonalShopItemsCount].Skill	= n[3];
            PersonalShopItems[PersonalShopItemsCount].Luck	= n[4];
            PersonalShopItems[PersonalShopItemsCount].Opt	= n[5];
            PersonalShopItems[PersonalShopItemsCount].Exc	= n[6];
            PersonalShopItems[PersonalShopItemsCount].Anc	= n[7];

            PersonalShopItemsCount++;
        }
    }

    fclose(conf);

    Log.ConsoleOutPut(1, c_Magenta, t_Default, "[û] [Trade System]\tLoaded %d items." ,TradeItemsCount+WareHouseItemsCount+GroudDropItemsCount+PersonalShopItemsCount);
}

bool cTradeSystem::CheckTradeItem(LPOBJ gObj)
{
    if(!EnabledTrade)
        return false;

    for (int n=0; n<32; n++)
    {
        if (gObj->Trade[n].m_Type >= 0)
        {
            for(int i = 0; i < TradeItemsCount; i++)
            {
                if(TradeItems[i].Group != -1 && TradeItems[i].Index != -1)
                {
                    if(gObj->Trade[n].m_Type != ITEMGET(TradeItems[i].Group,TradeItems[i].Index))
                        continue;
                }
                if(TradeItems[i].Group == -1 && TradeItems[i].Index != -1)
                {
                    int Temp = (int)floor(gObj->Trade[n].m_Type/512.0f);
                    if(gObj->Trade[n].m_Type != ITEMGET(Temp, TradeItems[i].Index))
                    {
                        continue;
                    }
                }
                if(TradeItems[i].Group != -1 && TradeItems[i].Index == -1)
                {
                    if(gObj->Trade[n].m_Type < ITEMGET(TradeItems[i].Group, 0) ||
                            gObj->Trade[n].m_Type >= ITEMGET(TradeItems[i].Group+1, 0))
                        continue;
                }

                if(TradeItems[i].Level != -1 && gObj->Trade[n].m_Level < TradeItems[i].Level)
                    continue;

                if(TradeItems[i].Skill != -1 && gObj->Trade[n].m_Option1 != TradeItems[i].Skill)
                    continue;

                if(TradeItems[i].Luck != -1 && gObj->Trade[n].m_Option2 != TradeItems[i].Luck)
                    continue;

                if(TradeItems[i].Opt != -1 && gObj->Trade[n].m_Option3 < TradeItems[i].Opt)
                    continue;

                if(TradeItems[i].Exc != -1 && Utilits.TakeExcNum(gObj->Trade[n].m_NewOption) < TradeItems[i].Exc)
                    continue;

                if(TradeItems[i].Anc != -1 && gObj->Trade[n].m_SetOption < TradeItems[i].Anc)
                    continue;

                //# TODO Make MSG of what item can't be traded
                return true;
            }
        }
    }
    return false;
}

bool cTradeSystem::CheckWarehouseItem( LPOBJ gObj, int Source )
{
    if(!EnabledWarehouse)
        return false;

    if (gObj->pInventory[Source].m_Type >= 0)
    {
        for(int i = 0; i < WareHouseItemsCount; i++)
        {
            if(WareHouseItems[i].Group != -1 && WareHouseItems[i].Index != -1)
            {
                if(gObj->pInventory[Source].m_Type != ITEMGET(WareHouseItems[i].Group,WareHouseItems[i].Index))
                    continue;
            }
            if(WareHouseItems[i].Group == -1 && WareHouseItems[i].Index != -1)
            {
                int Temp = (int)floor(gObj->pInventory[Source].m_Type/512.0f);
                if(gObj->pInventory[Source].m_Type != ITEMGET(Temp, WareHouseItems[i].Index))
                {
                    continue;
                }
            }
            if(WareHouseItems[i].Group != -1 && WareHouseItems[i].Index == -1)
            {
                if(gObj->pInventory[Source].m_Type < ITEMGET(WareHouseItems[i].Group, 0) ||
                        gObj->pInventory[Source].m_Type >= ITEMGET(WareHouseItems[i].Group+1, 0))
                    continue;
            }

            if(WareHouseItems[i].Level != -1 && gObj->pInventory[Source].m_Level < WareHouseItems[i].Level)
                continue;

            if(WareHouseItems[i].Skill != -1 && gObj->pInventory[Source].m_Option1 != WareHouseItems[i].Skill)
                continue;

            if(WareHouseItems[i].Luck != -1 && gObj->pInventory[Source].m_Option2 != WareHouseItems[i].Luck)
                continue;

            if(WareHouseItems[i].Opt != -1 && gObj->pInventory[Source].m_Option3 < WareHouseItems[i].Opt)
                continue;

            if(WareHouseItems[i].Exc != -1 && Utilits.TakeExcNum(gObj->pInventory[Source].m_NewOption) < WareHouseItems[i].Exc)
                continue;

            if(WareHouseItems[i].Anc != -1 && gObj->pInventory[Source].m_SetOption < WareHouseItems[i].Anc)
                continue;

            Chat.MessageLog(1, c_Red, t_TRADE, gObj, "[Warehouse] You can't move that item to Warehouse!");
            return true;
        }
    }
    return false;
}

bool cTradeSystem::CheckGroundDropItem( LPOBJ gObj, int Source )
{
    if(!EnabledGround)
        return false;

    if (gObj->pInventory[Source].m_Type >= 0)
    {
        for(int i = 0; i < GroudDropItemsCount; i++)
        {
            if(GroudDropItems[i].Group != -1 && GroudDropItems[i].Index != -1)
            {
                if(gObj->pInventory[Source].m_Type != ITEMGET(GroudDropItems[i].Group,GroudDropItems[i].Index))
                    continue;
            }
            if(GroudDropItems[i].Group == -1 && GroudDropItems[i].Index != -1)
            {
                int Temp = (int)floor(gObj->pInventory[Source].m_Type/512.0f);
                if(gObj->pInventory[Source].m_Type != ITEMGET(Temp, GroudDropItems[i].Index))
                {
                    continue;
                }
            }
            if(GroudDropItems[i].Group != -1 && GroudDropItems[i].Index == -1)
            {
                if(gObj->pInventory[Source].m_Type < ITEMGET(GroudDropItems[i].Group, 0) ||
                        gObj->pInventory[Source].m_Type >= ITEMGET(GroudDropItems[i].Group+1, 0))
                    continue;
            }

            if(GroudDropItems[i].Level != -1 && gObj->pInventory[Source].m_Level < GroudDropItems[i].Level)
                continue;

            if(GroudDropItems[i].Skill != -1 && gObj->pInventory[Source].m_Option1 != GroudDropItems[i].Skill)
                continue;

            if(GroudDropItems[i].Luck != -1 && gObj->pInventory[Source].m_Option2 != GroudDropItems[i].Luck)
                continue;

            if(GroudDropItems[i].Opt != -1 && gObj->pInventory[Source].m_Option3 < GroudDropItems[i].Opt)
                continue;

            if(GroudDropItems[i].Exc != -1 && Utilits.TakeExcNum(gObj->pInventory[Source].m_NewOption) < GroudDropItems[i].Exc)
                continue;

            if(GroudDropItems[i].Anc != -1 && gObj->pInventory[Source].m_SetOption < GroudDropItems[i].Anc)
                continue;

            Chat.MessageLog(1, c_Red, t_TRADE, gObj, "[GroundDrop] You can't drop that item to the ground!");
            return true;
        }
    }
    return false;
}

bool cTradeSystem::CheckPersonalShopItem( LPOBJ gObj, int Source )
{
    if(!EnabledPersonal)
        return false;

    if (gObj->pInventory[Source].m_Type >= 0)
    {
        for(int i = 0; i < PersonalShopItemsCount; i++)
        {
            if(PersonalShopItems[i].Group != -1 && PersonalShopItems[i].Index != -1)
            {
                if(gObj->pInventory[Source].m_Type != ITEMGET(PersonalShopItems[i].Group,PersonalShopItems[i].Index))
                    continue;
            }
            if(PersonalShopItems[i].Group == -1 && PersonalShopItems[i].Index != -1)
            {
                int Temp = (int)floor(gObj->pInventory[Source].m_Type/512.0f);
                if(gObj->pInventory[Source].m_Type != ITEMGET(Temp, PersonalShopItems[i].Index))
                {
                    continue;
                }
            }
            if(PersonalShopItems[i].Group != -1 && PersonalShopItems[i].Index == -1)
            {
                if(gObj->pInventory[Source].m_Type < ITEMGET(PersonalShopItems[i].Group, 0) ||
                        gObj->pInventory[Source].m_Type >= ITEMGET(PersonalShopItems[i].Group+1, 0))
                    continue;
            }

            if(PersonalShopItems[i].Level != -1 && gObj->pInventory[Source].m_Level < PersonalShopItems[i].Level)
                continue;

            if(PersonalShopItems[i].Skill != -1 && gObj->pInventory[Source].m_Option1 != PersonalShopItems[i].Skill)
                continue;

            if(PersonalShopItems[i].Luck != -1 && gObj->pInventory[Source].m_Option2 != PersonalShopItems[i].Luck)
                continue;

            if(PersonalShopItems[i].Opt != -1 && gObj->pInventory[Source].m_Option3 < PersonalShopItems[i].Opt)
                continue;

            if(PersonalShopItems[i].Exc != -1 && Utilits.TakeExcNum(gObj->pInventory[Source].m_NewOption) < PersonalShopItems[i].Exc)
                continue;

            if(PersonalShopItems[i].Anc != -1 && gObj->pInventory[Source].m_SetOption < PersonalShopItems[i].Anc)
                continue;

            Chat.MessageLog(1, c_Red, t_TRADE, gObj, "[PersonalStore] You can't move that item to PersonalStore!");
            return true;
        }
    }
    return false;
}

#define MAIN_INVENTORY_SIZE 76
#define INVENTORY_SIZE 108
#define WAREHOUSE_SIZE 120
#define TRADE_BOX_SIZE 32
#define CHAOS_BOX_SIZE 32

BYTE gObjInventoryMoveItemEx(int aIndex, BYTE source, BYTE target, int& durSsend, int& durTsend, BYTE sFlag, BYTE tFlag, LPBYTE siteminfo)
{
    CItem * sitem;
    CItem * titem;

    int bPersonalShopTrans = 0;
    int bSourceIsPShop = 0;

    OBJECTSTRUCT *lpObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);
    if(sFlag == 2 || tFlag == 2)
    {
        if(lpObj->m_IfState.type != 6)
            return -1;

        if(lpObj->m_IfState.state == 0)
            return -1;
    }

    //sw1
    switch(sFlag) // Item that we move
    {
    case 0:	// from Inventory
        if(source > (MAIN_INVENTORY_SIZE - 1)) // source - coord where moved from
            return -1;

        if(lpObj->pInventory[source].m_Type < 0)
            return -1;

        sitem = &lpObj->pInventory[source];
        break;
    case 2: // from Warehouse
        if(source > (WAREHOUSE_SIZE-1))
            return -1;

        if(lpObj->pWarehouse[source].m_Type < 0)
            return -1;

        sitem = &lpObj->pWarehouse[source];
        break;
    case 3:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14: // from ChaosBox
        if(source > (WAREHOUSE_SIZE-1))
            return -1;

        if(lpObj->pChaosBox[source].m_Type < 0)
            return -1;

        sitem = &lpObj->pChaosBox[source];

        break;
    case 4: // from Personal Shop
        if(lpObj->m_bPShopOpen == 1)
            return -1;

        if(source < MAIN_INVENTORY_SIZE || source > (INVENTORY_SIZE - 1))
            return -1;

        if(lpObj->pInventory[source].m_Type < 0)
            return -1;

        sitem = &lpObj->pInventory[source];

        break;
    default:
        return -1;
    }

    //sw2
    switch(tFlag)
    {
    case 0: // to inventory
        if(target > (MAIN_INVENTORY_SIZE - 1))
            return -1;

        titem = &lpObj->pInventory[target];
        break;
    case 2: // to warehouse
        if(target > (WAREHOUSE_SIZE - 1))
            return -1;

        if(sFlag == 0 && TradeSystem.EnabledWarehouse)
        {
            if(TradeSystem.CheckWarehouseItem(lpObj, source))
                return -1;
        }
        titem = &lpObj->pWarehouse[target];
        break;
    case 3:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14: // to chaos machine
        if(target > (CHAOS_BOX_SIZE -1))
            return -1;

        titem = &lpObj->pChaosBox[target];

        break;
    case 4:	// to Personal Shop

        if(lpObj->m_bPShopOpen == 1)
            return -1;

        if(sFlag == 0 && TradeSystem.EnabledPersonal)
        {
            if(TradeSystem.CheckPersonalShopItem(lpObj, source))
                return -1;
        }

        if(target < MAIN_INVENTORY_SIZE || target > (INVENTORY_SIZE - 1))
            return -1;

        titem = &lpObj->pInventory[target];

        break;
    default:
        return -1;
    }

    return gObjInventoryMoveItem(aIndex, source, target, durSsend, durTsend, sFlag, tFlag, siteminfo);
}

BOOL CGItemDropRequestEx(PMSG_ITEMTHROW * lpMsg, int aIndex, BOOL drop_type)
{
    OBJECTSTRUCT *lpObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);

    if ( lpObj->m_IfState.use != 0 )
    {
        if ( lpObj->m_IfState.type != 3 )
        {
            return FALSE;
        }
    }

    if ( lpObj->CloseType != -1 )
    {
        return FALSE;
    }

    if ( lpObj->m_bMapSvrMoveQuit == true )
    {
        return FALSE;
    }

    if ( lpObj->pTransaction == 1 )
    {
        return FALSE;
    }

    if ( lpMsg->Ipos == 0xFF )
    {
        return FALSE;
    }

    if ( lpMsg->Ipos > MAIN_INVENTORY_SIZE-1)
    {
        return FALSE;
    }
#ifdef _GS_CS
    if(lpObj->pInventory[lpMsg->Ipos].m_Type == ITEMGET(14,28)) //LOST MAP in GSCS
    {
        return FALSE;
    }
#endif
    if(TradeSystem.CheckGroundDropItem(lpObj, lpMsg->Ipos))
    {
        return FALSE;
    }

    return CGItemDropRequest(lpMsg, aIndex, drop_type);
}