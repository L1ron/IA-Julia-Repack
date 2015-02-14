#include "StdAfx.h"
#include "CalcCharacter.h"
#include "Logger.h"
#include "Utilits.h"

cCalcCharacterExternClass CalcCharacterExternClass;

void cCalcCharacterExternClass::CalCharacterEx(int aIndex)
{
	OBJECTSTRUCT * gObj = (OBJECTSTRUCT*) OBJECT_POINTER (aIndex);

	switch(gObj->Class)
	{
		case 0:
		{
			gObj->m_AttackDamageMinRight = (gObj->Strength / CalCharacterStruct.DW_AtackMinRight);
			gObj->m_AttackDamageMaxRight = (gObj->Strength / CalCharacterStruct.DW_AtackMaxRight);
			gObj->m_AttackDamageMinLeft = (gObj->Strength / CalCharacterStruct.DW_AtackMinLeft);
			gObj->m_AttackDamageMaxLeft = (gObj->Strength / CalCharacterStruct.DW_AtackMaxLeft);
			gObj->m_AttackSpeed = gObj->Dexterity / CalCharacterStruct.DW_AtackSpeed;
			gObj->m_MagicSpeed = gObj->Dexterity / CalCharacterStruct.DW_AtackSpeed;
			gObj->m_SuccessfulBlocking = gObj->Dexterity / CalCharacterStruct.DW_SuccessfulBlocking;
			gObj->m_Defense = gObj->Dexterity / CalCharacterStruct.DW_Defense;
			gObj->m_MagicDamageMin = (gObj->Energy / CalCharacterStruct.DW_MagicDMGMin);
			gObj->m_MagicDamageMax = (gObj->Energy / CalCharacterStruct.DW_MagicDMGMax);

			break;
		}
		case 1:
		{
			gObj->m_AttackDamageMinRight = (gObj->Strength / CalCharacterStruct.DK_AtackMinRight);
			gObj->m_AttackDamageMaxRight = (gObj->Strength / CalCharacterStruct.DK_AtackMaxRight);
			gObj->m_AttackDamageMinLeft = (gObj->Strength / CalCharacterStruct.DK_AtackMinLeft);
			gObj->m_AttackDamageMaxLeft = (gObj->Strength / CalCharacterStruct.DK_AtackMaxLeft);
			gObj->m_AttackSpeed = gObj->Dexterity / CalCharacterStruct.DK_AtackSpeed;
			gObj->m_MagicSpeed = gObj->Dexterity / CalCharacterStruct.DK_MagicSpeed;
			gObj->m_SuccessfulBlocking = gObj->Dexterity / CalCharacterStruct.DK_SuccessfulBlocking;
			gObj->m_Defense = gObj->Dexterity / CalCharacterStruct.DK_Defense;
			gObj->m_MagicDamageMin = (gObj->Energy / CalCharacterStruct.DK_MagicDMGMin);
			gObj->m_MagicDamageMax = (gObj->Energy / CalCharacterStruct.DK_MagicDMGMax);
			
			break;
		}
		case 2:
		{
			gObj->m_AttackDamageMinRight = (gObj->Strength / CalCharacterStruct.ELF_AtackMinRight);
			gObj->m_AttackDamageMaxRight = (gObj->Strength / CalCharacterStruct.ELF_AtackMaxRight);
			gObj->m_AttackDamageMinLeft = (gObj->Strength / CalCharacterStruct.ELF_AtackMinLeft);
			gObj->m_AttackDamageMaxLeft = (gObj->Strength / CalCharacterStruct.ELF_AtackMaxLeft);
			gObj->m_AttackSpeed = gObj->Dexterity / CalCharacterStruct.ELF_AtackSpeed;
			gObj->m_MagicSpeed = gObj->Dexterity / CalCharacterStruct.ELF_MagicSpeed;
			gObj->m_SuccessfulBlocking = gObj->Dexterity / CalCharacterStruct.ELF_SuccessfulBlocking;
			gObj->m_Defense = gObj->Dexterity/ CalCharacterStruct.ELF_Defense;
			gObj->m_MagicDamageMin = (gObj->Energy / CalCharacterStruct.ELF_MagicDMGMin);
			gObj->m_MagicDamageMax = (gObj->Energy / CalCharacterStruct.ELF_MagicDMGMax);
			
			break;
		}
		case 3:
		{
			gObj->m_AttackDamageMinRight = (gObj->Strength / CalCharacterStruct.MG_AtackMinRight)+(gObj->Energy/CalCharacterStruct.MG_AtackMinRight);
			gObj->m_AttackDamageMaxRight = (gObj->Strength / CalCharacterStruct.MG_AtackMaxRight)+(gObj->Energy/CalCharacterStruct.MG_AtackMaxRight);
			gObj->m_AttackDamageMinLeft = (gObj->Strength / CalCharacterStruct.MG_AtackMinLeft)+(gObj->Energy/CalCharacterStruct.MG_AtackMinLeft);
			gObj->m_AttackDamageMaxLeft = (gObj->Strength / CalCharacterStruct.MG_AtackMaxLeft)+(gObj->Energy/CalCharacterStruct.MG_AtackMaxLeft);
			gObj->m_AttackSpeed = gObj->Dexterity / CalCharacterStruct.MG_AtackSpeed;
			gObj->m_MagicSpeed = gObj->Dexterity / CalCharacterStruct.MG_MagicSpeed;
			gObj->m_SuccessfulBlocking = gObj->Dexterity / CalCharacterStruct.MG_SuccessfulBlocking;
			gObj->m_Defense = gObj->Dexterity/ CalCharacterStruct.MG_Defense;
			gObj->m_MagicDamageMin = (gObj->Energy / CalCharacterStruct.MG_MagicDMGMin);
			gObj->m_MagicDamageMax = (gObj->Energy / CalCharacterStruct.MG_MagicDMGMax);
			
			break;
		}
		case 4:		
		{
			gObj->m_AttackDamageMinRight =  ((gObj->Strength / CalCharacterStruct.DL_AtackMinRight) + (gObj->Energy / (CalCharacterStruct.DL_AtackMinRight*2)));
			gObj->m_AttackDamageMaxRight = ((gObj->Strength / CalCharacterStruct.DL_AtackMaxRight) + (gObj->Energy / (CalCharacterStruct.DL_AtackMaxRight*2)));
			gObj->m_AttackDamageMinLeft = ((gObj->Strength / CalCharacterStruct.DL_AtackMinLeft) + (gObj->Energy / (CalCharacterStruct.DL_AtackMinLeft*2)));
			gObj->m_AttackDamageMaxLeft = ((gObj->Strength / CalCharacterStruct.DL_AtackMaxLeft) + (gObj->Energy / (CalCharacterStruct.DL_AtackMaxLeft*2)));
			gObj->m_AttackSpeed = gObj->Dexterity / CalCharacterStruct.DL_AtackSpeed;
			gObj->m_MagicSpeed = gObj->Dexterity / CalCharacterStruct.DL_MagicSpeed;
			gObj->m_SuccessfulBlocking = gObj->Dexterity / CalCharacterStruct.DL_SuccessfulBlocking;
			gObj->m_Defense = gObj->Dexterity / CalCharacterStruct.DL_Defense;
			gObj->m_MagicDamageMin = (gObj->Energy / CalCharacterStruct.DL_MagicDMGMin);
			gObj->m_MagicDamageMax = (gObj->Energy / CalCharacterStruct.DL_MagicDMGMax);
			
			break;
		}
		case 5:
		{
			gObj->m_AttackDamageMinRight = ((gObj->Strength+gObj->Dexterity) / CalCharacterStruct.SUM_AtackMinRight);
			gObj->m_AttackDamageMaxRight = ((gObj->Strength+gObj->Dexterity) / CalCharacterStruct.SUM_AtackMaxRight);
			gObj->m_AttackDamageMinLeft = ((gObj->Strength+gObj->Dexterity) / CalCharacterStruct.SUM_AtackMinLeft);
			gObj->m_AttackDamageMaxLeft = ((gObj->Strength+gObj->Dexterity) / CalCharacterStruct.SUM_AtackMaxLeft);
			gObj->m_AttackSpeed = (gObj->Dexterity / CalCharacterStruct.SUM_AtackSpeed);
			gObj->m_MagicSpeed = (gObj->Dexterity / CalCharacterStruct.SUM_MagicSpeed);
			gObj->m_SuccessfulBlocking = (gObj->Dexterity / CalCharacterStruct.SUM_SuccessfulBlocking);
			gObj->m_Defense = (gObj->Dexterity / CalCharacterStruct.SUM_Defense);
			gObj->m_MagicDamageMin = (gObj->Energy / CalCharacterStruct.SUM_MagicDMGMin);
			gObj->m_MagicDamageMax = (gObj->Energy / CalCharacterStruct.SUM_MagicDMGMax);
			
			break;
		}
	}
}

void cCalcCharacterExternClass::Init()
{
	this->CalcCharacterEnabled								= GetPrivateProfileInt("CalcCharacter","CalcCharacterEnable",1,IACalcCharacter);

	if(this->CalcCharacterEnabled)
	{
		/*CALSSES DE DW SM GRM*/
		this->CalCharacterStruct.DW_AtackMinRight			= GetPrivateProfileInt("DarlWizard","DW_MinAtackRight",100,IACalcCharacter);
		this->CalCharacterStruct.DW_AtackMaxRight			= GetPrivateProfileInt("DarlWizard","DW_MaxAtackRight",50,IACalcCharacter);
		this->CalCharacterStruct.DW_AtackMinLeft			= GetPrivateProfileInt("DarlWizard","DW_MinAtackLeft",100,IACalcCharacter);
		this->CalCharacterStruct.DW_AtackMaxLeft			= GetPrivateProfileInt("DarlWizard","DW_MaxAtackLeft",50,IACalcCharacter);
		this->CalCharacterStruct.DW_AtackSpeed				= GetPrivateProfileInt("DarlWizard","DW_AtackSpeed",35,IACalcCharacter);
		this->CalCharacterStruct.DW_MagicSpeed				= GetPrivateProfileInt("DarlWizard","DW_MagicSpeed",30,IACalcCharacter);
		this->CalCharacterStruct.DW_SuccessfulBlocking		= GetPrivateProfileInt("DarlWizard","DW_SucessFullBlock",40,IACalcCharacter);
		this->CalCharacterStruct.DW_Defense					= GetPrivateProfileInt("DarlWizard","DW_Defense",12,IACalcCharacter);
		this->CalCharacterStruct.DW_MagicDMGMin				= GetPrivateProfileInt("DarlWizard","DW_MagicDmgMin",100,IACalcCharacter);
		this->CalCharacterStruct.DW_MagicDMGMax				= GetPrivateProfileInt("DarlWizard","DW_MagicDmgMax",80,IACalcCharacter);

		/*CLASSES DK BK BM*/
		this->CalCharacterStruct.DK_AtackMinRight			= GetPrivateProfileInt("DarkKnight","DK_MinAtackRight",100,IACalcCharacter);
		this->CalCharacterStruct.DK_AtackMaxRight			= GetPrivateProfileInt("DarkKnight","DK_MaxAtackRight",50,IACalcCharacter);
		this->CalCharacterStruct.DK_AtackMinLeft			= GetPrivateProfileInt("DarkKnight","DK_MinAtackLeft",100,IACalcCharacter);
		this->CalCharacterStruct.DK_AtackMaxLeft			= GetPrivateProfileInt("DarkKnight","DK_MaxAtackLeft",50,IACalcCharacter);
		this->CalCharacterStruct.DK_AtackSpeed				= GetPrivateProfileInt("DarkKnight","DK_AtackSpeed",35,IACalcCharacter);
		this->CalCharacterStruct.DK_MagicSpeed				= GetPrivateProfileInt("DarkKnight","DK_MagicSpeed",30,IACalcCharacter);
		this->CalCharacterStruct.DK_SuccessfulBlocking		= GetPrivateProfileInt("DarkKnight","DK_SucessFullBlock",40,IACalcCharacter);
		this->CalCharacterStruct.DK_Defense					= GetPrivateProfileInt("DarkKnight","DK_Defense",12,IACalcCharacter);
		this->CalCharacterStruct.DK_MagicDMGMin				= GetPrivateProfileInt("DarkKnight","DK_MagicDmgMin",100,IACalcCharacter);
		this->CalCharacterStruct.DK_MagicDMGMax				= GetPrivateProfileInt("DarkKnight","DK_MagicDmgMax",80,IACalcCharacter);

		/*CLASSES DE ELF ME HE*/
		this->CalCharacterStruct.ELF_AtackMinRight			= GetPrivateProfileInt("FairyElf","ELF_MinAtackRight",100,IACalcCharacter);
		this->CalCharacterStruct.ELF_AtackMaxRight			= GetPrivateProfileInt("FairyElf","ELF_MaxAtackRight",50,IACalcCharacter);
		this->CalCharacterStruct.ELF_AtackMinLeft			= GetPrivateProfileInt("FairyElf","ELF_MinAtackLeft",100,IACalcCharacter);
		this->CalCharacterStruct.ELF_AtackMaxLeft			= GetPrivateProfileInt("FairyElf","ELF_MaxAtackLeft",50,IACalcCharacter);
		this->CalCharacterStruct.ELF_AtackSpeed 			= GetPrivateProfileInt("FairyElf","ELF_AtackSpeed",35,IACalcCharacter);
		this->CalCharacterStruct.ELF_MagicSpeed 			= GetPrivateProfileInt("FairyElf","ELF_MagicSpeed",30,IACalcCharacter);
		this->CalCharacterStruct.ELF_SuccessfulBlocking		= GetPrivateProfileInt("FairyElf","ELF_SucessFullBlock",40,IACalcCharacter);
		this->CalCharacterStruct.ELF_Defense 				= GetPrivateProfileInt("FairyElf","ELF_Defense",12,IACalcCharacter);
		this->CalCharacterStruct.ELF_MagicDMGMin 			= GetPrivateProfileInt("FairyElf","ELF_MagicDmgMin",100,IACalcCharacter);
		this->CalCharacterStruct.ELF_MagicDMGMax 			= GetPrivateProfileInt("FairyElf","ELF_MagicDmgMax",80,IACalcCharacter);

		/*CLASSES DE MG E DM*/
		this->CalCharacterStruct.MG_AtackMinRight 			= GetPrivateProfileInt("MagicGladiator","MG_MinAtackRight",100,IACalcCharacter);
		this->CalCharacterStruct.MG_AtackMaxRight 			= GetPrivateProfileInt("MagicGladiator","MG_MaxAtackRight",50,IACalcCharacter);
		this->CalCharacterStruct.MG_AtackMinLeft 			= GetPrivateProfileInt("MagicGladiator","MG_MinAtackLeft",100,IACalcCharacter);
		this->CalCharacterStruct.MG_AtackMaxLeft 			= GetPrivateProfileInt("MagicGladiator","MG_MaxAtackLeft",50,IACalcCharacter);
		this->CalCharacterStruct.MG_AtackSpeed 				= GetPrivateProfileInt("MagicGladiator","MG_AtackSpeed",35,IACalcCharacter);
		this->CalCharacterStruct.MG_MagicSpeed 				= GetPrivateProfileInt("MagicGladiator","MG_MagicSpeed",30,IACalcCharacter);
		this->CalCharacterStruct.MG_SuccessfulBlocking 		= GetPrivateProfileInt("MagicGladiator","MG_SucessFullBlock",40,IACalcCharacter);
		this->CalCharacterStruct.MG_Defense 				= GetPrivateProfileInt("MagicGladiator","MG_Defense",12,IACalcCharacter);
		this->CalCharacterStruct.MG_MagicDMGMin 			= GetPrivateProfileInt("MagicGladiator","MG_MagicDmgMin",100,IACalcCharacter);
		this->CalCharacterStruct.MG_MagicDMGMax 			= GetPrivateProfileInt("MagicGladiator","MG_MagicDmgMax",80,IACalcCharacter);

		/*CLASSES DE DL E LE*/
		this->CalCharacterStruct.DL_AtackMinRight 			= GetPrivateProfileInt("DarkLord","DL_MinAtackRight",100,IACalcCharacter);
		this->CalCharacterStruct.DL_AtackMaxRight 			= GetPrivateProfileInt("DarkLord","DL_MaxAtackRight",50,IACalcCharacter);
		this->CalCharacterStruct.DL_AtackMinLeft 			= GetPrivateProfileInt("DarkLord","DL_MinAtackLeft",100,IACalcCharacter);
		this->CalCharacterStruct.DL_AtackMaxLeft 			= GetPrivateProfileInt("DarkLord","DL_MaxAtackLeft",50,IACalcCharacter);
		this->CalCharacterStruct.DL_AtackSpeed 				= GetPrivateProfileInt("DarkLord","DL_AtackSpeed",35,IACalcCharacter);
		this->CalCharacterStruct.DL_MagicSpeed 				= GetPrivateProfileInt("DarkLord","DL_MagicSpeed",30,IACalcCharacter);
		this->CalCharacterStruct.DL_SuccessfulBlocking		= GetPrivateProfileInt("DarkLord","DL_SucessFullBlock",40,IACalcCharacter);
		this->CalCharacterStruct.DL_Defense 				= GetPrivateProfileInt("DarkLord","DL_Defense",12,IACalcCharacter);
		this->CalCharacterStruct.DL_MagicDMGMin 			= GetPrivateProfileInt("DarkLord","DL_MagicDmgMin",100,IACalcCharacter);
		this->CalCharacterStruct.DL_MagicDMGMax 			= GetPrivateProfileInt("DarkLord","DL_MagicDmgMax",80,IACalcCharacter);

		/*CLASSES DE SUM BS E DMS*/
		this->CalCharacterStruct.SUM_AtackMinRight			= GetPrivateProfileInt("Summoner","SUM_MinAtackRight",100,IACalcCharacter);
		this->CalCharacterStruct.SUM_AtackMaxRight			= GetPrivateProfileInt("Summoner","SUM_MaxAtackRight",50,IACalcCharacter);
		this->CalCharacterStruct.SUM_AtackMinLeft			= GetPrivateProfileInt("Summoner","SUM_MinAtackLeft",100,IACalcCharacter);
		this->CalCharacterStruct.SUM_AtackMaxLeft 			= GetPrivateProfileInt("Summoner","SUM_MaxAtackLeft",50,IACalcCharacter);
		this->CalCharacterStruct.SUM_AtackSpeed 			= GetPrivateProfileInt("Summoner","SUM_AtackSpeed",35,IACalcCharacter);
		this->CalCharacterStruct.SUM_MagicSpeed 			= GetPrivateProfileInt("Summoner","SUM_MagicSpeed",30,IACalcCharacter);
		this->CalCharacterStruct.SUM_SuccessfulBlocking		= GetPrivateProfileInt("Summoner","SUM_SucessFullBlock",40,IACalcCharacter);
		this->CalCharacterStruct.SUM_Defense 				= GetPrivateProfileInt("Summoner","SUM_Defense",12,IACalcCharacter);
		this->CalCharacterStruct.SUM_MagicDMGMin 			= GetPrivateProfileInt("Summoner","SUM_MagicDmgMin",100,IACalcCharacter);
		this->CalCharacterStruct.SUM_MagicDMGMax 			= GetPrivateProfileInt("Summoner","SUM_MagicDmgMax",80,IACalcCharacter);

		Log.ConsoleOutPut(1,c_Green,t_Default,"[û] [CalcCharacter]\tIniciado.");
	}
}