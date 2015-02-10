#ifndef _CalcCharacter_
#define _CalcCharacter_

#include "StdAfx.h"

struct ObjCalcCharacter_Struct
{
	// Dark Wizard
	short DW_AtackMinRight;
	short DW_AtackMaxRight;
	short DW_AtackMinLeft;
	short DW_AtackMaxLeft;
	short DW_AtackSpeed;
	short DW_MagicSpeed;
	short DW_SuccessfulBlocking;
	short DW_Defense;
	short DW_MagicDMGMin;
	short DW_MagicDMGMax;

	// Dark Knight
	short DK_AtackMinRight;
	short DK_AtackMaxRight;
	short DK_AtackMinLeft;
	short DK_AtackMaxLeft;
	short DK_AtackSpeed;
	short DK_MagicSpeed;
	short DK_SuccessfulBlocking;
	short DK_Defense;
	short DK_MagicDMGMin;
	short DK_MagicDMGMax;
	
	// Fairy Elf
	short ELF_AtackMinRight;
	short ELF_AtackMaxRight;
	short ELF_AtackMinLeft;
	short ELF_AtackMaxLeft;
	short ELF_AtackSpeed;
	short ELF_MagicSpeed;
	short ELF_SuccessfulBlocking;
	short ELF_Defense;
	short ELF_MagicDMGMin;
	short ELF_MagicDMGMax;
	
	// Magic Gladiator
	short MG_AtackMinRight;
	short MG_AtackMaxRight;
	short MG_AtackMinLeft;
	short MG_AtackMaxLeft;
	short MG_AtackSpeed;
	short MG_MagicSpeed;
	short MG_SuccessfulBlocking;
	short MG_Defense;
	short MG_MagicDMGMin;
	short MG_MagicDMGMax;

	// Dark Lord
	short DL_AtackMinRight;
	short DL_AtackMaxRight;
	short DL_AtackMinLeft;
	short DL_AtackMaxLeft;
	short DL_AtackSpeed;
	short DL_MagicSpeed;
	short DL_SuccessfulBlocking;
	short DL_Defense;
	short DL_MagicDMGMin;
	short DL_MagicDMGMax;
	
	// Summoner
	short SUM_AtackMinRight;
	short SUM_AtackMaxRight;
	short SUM_AtackMinLeft;
	short SUM_AtackMaxLeft;
	short SUM_AtackSpeed;
	short SUM_MagicSpeed;
	short SUM_SuccessfulBlocking;
	short SUM_Defense;
	short SUM_MagicDMGMin;
	short SUM_MagicDMGMax;
};

class cCalcCharacterExternClass
{
	public:
		void CalCharacterEx(int aIndex);
		void Init();

		int CalcCharacterEnabled;

		ObjCalcCharacter_Struct CalCharacterStruct;
};

extern cCalcCharacterExternClass CalcCharacterExternClass;

#endif