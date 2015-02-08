#ifndef HELPERS_H
#define HELPERS_H

#include "User.h"

class cHelpers
{
	public:
		void Load();
        void Connect(LPOBJ gObj);

		void HelperEllenClick(LPOBJ gObj, LPOBJ gObjNPC);
		void HelperLukeClick(LPOBJ gObj, LPOBJ gObjNPC);
		void HelperLeoClick(LPOBJ gObj, LPOBJ gObjNPC);

        void CheckConditions(LPOBJ gObj, LPOBJ gObjNPC);
        void GenerateItem(int aIndex);

		struct
		{
			int Enable;
            int UsePK;
            int PriceZen;
            int PricePCPoint;
            int PriceWCoin;
			int PriceWebPoint;
            int UseTimes;
            char Table[25];
            char Column[25];

		} Config;

        int Itens;

	    int Type,Index,Level,Option,Luck,Skill,Duration,Excellent;
};

extern cHelpers Helpers;

#define MaxItemsInBag 1000

struct sHelperItens
{
	BYTE Grupo;
	BYTE Index;
	BYTE Level;
	BYTE Durabilidade;
	BYTE Luck;
	BYTE Skill;
	BYTE Option;
	BYTE Exelente;
};

#endif
