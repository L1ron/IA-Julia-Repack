// ================================================== //
// #			GameServer 1.00.90					# //
// #			Imagination Arts					# //
// #			Julia Project 1.1.x					# //
// ================================================== //
// #	http://imaginationarts.net/forum/			# //
// #	http://mu.raklion.ru/						# //
//				coded by MaThreeX					  //
// ================================================== //

#ifndef MARRYSYSTEM_H
#define MARRYSYSTEM_H
#include "User.h"
#define MAXMARRYITEM 20
enum eGender {MAN, WOMAN};
class cMarry
{
public:
    cMarry();
    ~cMarry();


    void Init();
    void StartMarriage(int aIndex, int tIndex);
    void EndMarriageFalse(int Index);
    void EndMarriageTrue();

    bool NpcUse;
    //	int fIndex;
    LPOBJ NpcObj;
    LPOBJ gObj1, gObj2;
    /*For marry*/
    struct SItems
    {
        unsigned long Serial;
        int Group;
        short Index;
        int Type;
        int Lvl;
        int Skill;
        int Luck;
        int Opt;
        int Exc;
        int Num;
    };

    struct sMarry
    {
        int MarrySystemEnabled;
        int MarryHomoSexual;
        int MarryCostZen;
        int MarryCostPCPoint;
        int MarryCostWCoin;
        int MarryMinLvl;
        int MarryNpcNum;
        int MarryTrace;
        int MarryTraceLvl;
        int IsMarry;
        int MarryOnline;
        int MarryExpBonus;
        int NumWitnesses;

        int IsDivorce;
        int DivorceNpcNum;
        int DivorceCostZen;
        int DivorceCostPCPoint;
        int DivorceCostWCoin;
        int DivorceMinLvl;

        int TakeItemsForMarry;
        //	int TakeItemsForDivorce;

        SItems MarryItems[MAXMARRYITEM];
        //	SItems DivorceItems[MAXMARRYITEM];

        bool MarrySerial[76];
        //	bool DivorceSerial[76];

    } Config;
private:
    bool CheckGender(int aIndex, int tIndex);
    bool CheckMarryItem(int Index);
    void CheckMarryItemSerial(int Index, BYTE Serial);
    bool CheckMarryCost(int aIndex, int tIndex, int Delete);
    void ResetConfigs();


};
extern cMarry Marry;

#endif