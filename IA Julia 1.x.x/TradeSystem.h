#ifndef TradeSystem_h
#define TradeSystem_h

#include "User.h"

BYTE gObjInventoryMoveItemEx(int aIndex, BYTE source, BYTE target, int& durSsend, int& durTsend, BYTE sFlag, BYTE tFlag, LPBYTE siteminfo);
BOOL CGItemDropRequestEx(PMSG_ITEMTHROW * lpMsg, int aIndex, BOOL drop_type);

class cTradeSystem
{
public:
    void ResetConfig();
    void Load();
    bool CheckTradeItem(LPOBJ gObj);
    bool CheckWarehouseItem(LPOBJ gObj, int Source);
    bool CheckGroundDropItem(LPOBJ gObj, int Source);
    bool CheckPersonalShopItem(LPOBJ gObj, int Source);

    int EnabledTrade, EnabledWarehouse, EnabledGround, EnabledPersonal;
    int TradeItemsCount, WareHouseItemsCount, GroudDropItemsCount, PersonalShopItemsCount;

    struct sTradeItems
    {
        int Group;
        int Index;
        int Level;
        int Skill;
        int Luck;
        int Opt;
        int Exc;
        int Anc;
    } TradeItems[255], WareHouseItems[255], GroudDropItems[255], PersonalShopItems[255];
};

extern cTradeSystem TradeSystem;

#endif