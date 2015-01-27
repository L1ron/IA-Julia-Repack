#ifdef _GS

#include "StdAfx.h"
#include "User.h"
#include "ChaosMachine.h"
#include "ChatCommands.h"
#include "Utilits.h"
#include "Configs.h"

CHAOSMACHINESTRUCT ChaosCfg;
ChaosMachineNew CM;

ChaosMachineNew::ChaosMachineNew()
{
	return;
}

ChaosMachineNew::~ChaosMachineNew()
{
	return;
}

void __declspec(naked) ChaosboxItemsRegardingEx() 
{
	_asm 
	{
		// Original
		CMP ECX, 0x180F;
		JE ItemAllowed;

		// Sekeuromikon Piece 1
		CMP ECX, 0x1C67;
		JE ItemAllowed;

		// Sekeuromikon Piece 2
		CMP ECX, 0x1C68;
		JE ItemAllowed;

		// Sekeuromikon Piece 3
		CMP ECX, 0x1C69;
		JE ItemAllowed;

		// Sekeuromikon Piece 4
		CMP ECX, 0x1C6A;
		JE ItemAllowed;

		// Sekeuromikon Piece 5
		CMP ECX, 0x1C6B;
		JE ItemAllowed;

		// Sekeuromikon Piece 6
		CMP ECX, 0x1C6C;
		JE ItemAllowed;

		// Silver Key			// 14*112
		CMP ECX, 0x1C70;
		JE ItemAllowed;

		// Sealed Box as Silver // 14*122
		CMP ECX, 0x1C7A;
		JE ItemAllowed;

		// Golden Key			// 14*113
		CMP ECX, 0x1C71;
		JE ItemAllowed;

		// Sealed Box as Gold	// 14*122
		CMP ECX, 0x1C79;
		JE ItemAllowed;

		MOV EDI, CHAOS_ADR_RETURN;
		JMP EDI;

		ItemAllowed:
			MOV EDI, CHAOS_ADR_ITEM_ALLOW;
			JMP EDI;
	}
}

void ChaosMachineNew::ChaosMachineLoadConfig()
{	
	ChaosCfg.DimensionBookSucces	= Configs.GetInt(0,100,30,"ChaosMachineMixes","DimensionBookSuccess",IAJuliaItems);
	ChaosCfg.DimensionBookPrice		= Configs.GetInt(0,2000000000,1000000,"ChaosMachineMixes","DimensionBookPrice",IAJuliaItems);

	ChaosCfg.Upgrade14Success		= Configs.GetInt(0,100,30,"ChaosMachineMixes","Upgrade14Success",IAJuliaItems);
	ChaosCfg.Upgrade14Price			= Configs.GetInt(0,2000000000,10000000,"ChaosMachineMixes","Upgrade14Price",IAJuliaItems);
		
	ChaosCfg.Upgrade15Success		= Configs.GetInt(0,100,30,"ChaosMachineMixes","Upgrade15Success",IAJuliaItems);
	ChaosCfg.Upgrade15Price			= Configs.GetInt(0,2000000000,12000000,"ChaosMachineMixes","Upgrade15Price",IAJuliaItems);

	ChaosCfg.GoldenSealedBoxSuccess	= Configs.GetInt(0,100,30,"ChaosMachineMixes","GoldenSealedBoxSuccess",IAJuliaItems);
	ChaosCfg.GoldenSealedBoxPrice	= Configs.GetInt(0,2000000000,5000000,"ChaosMachineMixes","GoldenSealedBoxPrice",IAJuliaItems);

	ChaosCfg.SilverSealedBoxSuccess	= Configs.GetInt(0,100,30,"ChaosMachineMixes","SilverSealedBoxSuccess",IAJuliaItems);
	ChaosCfg.SilverSealedBoxPrice	= Configs.GetInt(0,2000000000,5000000,"ChaosMachineMixes","SilverSealedBoxPrice",IAJuliaItems);
}

void ChaosMachineNew::ChaosboxCombinationEx(int aIndex, unsigned char mixid) 
{
	OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);

	switch(mixid)
	{
		//============
		// Secromicon
		//============
		case CHAOS_TYPE_EMPIRE_GUARDIAN_BOOK:
		{
			if(!ChaosboxCanExecute(aIndex, CHAOS_TYPE_EMPIRE_GUARDIAN_BOOK))
			{
				break;
			}
			else
			{
				if(Utilits.RandomSucess(100) <= ChaosCfg.DimensionBookSucces)
				{
					CItem CBItem;
					CBItem.m_Type		= 0x1C6D;
					CBItem.m_Durability = 255.0;
					ChaosboxSuccess(&CBItem, aIndex, CHAOS_TYPE_EMPIRE_GUARDIAN_BOOK);

					Chat.MessageLog(1, c_Blue, t_NULL, gObj, SuccededMessage);
				
					gObj->Money = gObj->Money - ChaosCfg.DimensionBookPrice;
					GCMoneySend(aIndex, gObj->Money);

					return;
				}
				else
				{
					ChaosboxFailure(aIndex, CHAOS_TYPE_EMPIRE_GUARDIAN_BOOK);

					Chat.MessageLog(1, c_Red, t_NULL, gObj, FailtureMessage);

					return;
				}
			}
			break;
		}
		//============
		// +14 Upgrade
		//============
		case CHAOS_TYPE_UPGRADE_14:
		{
			if(!ChaosboxCanExecute(aIndex, CHAOS_TYPE_UPGRADE_14))
			{
				break;
			}
			else
			{
				int pChaosNum = 0;

				for(int i=0;i < 31;i++)
				{
					if(gObj->pChaosBox[i].m_Type != -1 && gObj->pChaosBox[i].m_Type != 0x1C0D && gObj->pChaosBox[i].m_Type != 0x1C0E && gObj->pChaosBox[i].m_Type != 0x180F)
					{
						pChaosNum = i;
					}
				}

				if(gObj->pChaosBox[pChaosNum].m_Option2 != 0)
				{
						ChaosCfg.Upgrade14Success += 25;
				}

				if(gObj->pChaosBox[pChaosNum].m_NewOption != 0)
				{
						ChaosCfg.Upgrade14Success += 10;
				}

				if(Utilits.RandomSucess(100) <= ChaosCfg.Upgrade14Success)
				{	
					CItem CBItem;

					CBItem = gObj->pChaosBox[pChaosNum];
					CBItem.m_Level		= 14;
					float NewDurability = (CBItem.m_Durability-32) +((CBItem.m_Level*2)+11);
					CBItem.m_Durability = NewDurability;
				
					ChaosboxSuccess(&CBItem, aIndex, CHAOS_TYPE_UPGRADE_14);

					Chat.MessageLog(1, c_Blue, t_NULL, gObj, SuccededMessage);

					gObj->Money = gObj->Money - ChaosCfg.Upgrade14Price;
					GCMoneySend(aIndex, gObj->Money);

					return;
				}
				else
				{
					ChaosboxFailure(aIndex, CHAOS_TYPE_UPGRADE_14);

					Chat.MessageLog(1, c_Red, t_NULL, gObj, FailtureMessage);

					return;
				}
				return;
			}
			break;
		}
		//============
		// +15 Upgrade
		//============	
		case CHAOS_TYPE_UPGRADE_15:
		{
			if(!ChaosboxCanExecute(aIndex, CHAOS_TYPE_UPGRADE_15))
			{
				break;
			}
			else
			{
				int pChaosNum = 0;
				for(int i=0;i<31;i++)
				{
					if(gObj->pChaosBox[i].m_Type != -1 && gObj->pChaosBox[i].m_Type != 0x1C0D && gObj->pChaosBox[i].m_Type != 0x1C0E && gObj->pChaosBox[i].m_Type != 0x180F)
					{
						pChaosNum = i;
					}
				}
				if(gObj->pChaosBox[pChaosNum].m_Option2 != 0)
				{
						ChaosCfg.Upgrade15Success += 25;
				}
				if(gObj->pChaosBox[pChaosNum].m_NewOption != 0)
				{
						ChaosCfg.Upgrade15Success += 10;
				}

				if(Utilits.RandomSucess(100) <= ChaosCfg.Upgrade15Success)
				{	
				
					CItem CBItem;

					CBItem = gObj->pChaosBox[pChaosNum];
					CBItem.m_Level		= 15;
					float NewDurability = (CBItem.m_Durability-39) +((CBItem.m_Level*2)+17);
					CBItem.m_Durability = NewDurability;
				
					ChaosboxSuccess(&CBItem, aIndex, CHAOS_TYPE_UPGRADE_15);

					Chat.MessageLog(1, c_Blue, t_NULL, gObj, SuccededMessage);

					gObj->Money = gObj->Money - ChaosCfg.Upgrade15Price;
					GCMoneySend(aIndex, gObj->Money);
					return;
				}
				else 
				{
					ChaosboxFailure(aIndex, CHAOS_TYPE_UPGRADE_15);

					Chat.MessageLog(1, c_Red, t_NULL, gObj, FailtureMessage);

					return;
				}
			}
			break;
		}
		//============
		// Sealed Box
		//============
		case CHAOS_TYPE_SEALED_BOX:
		{
			if(!ChaosboxCanExecute(aIndex, CHAOS_TYPE_SEALED_BOX))
			{
				if(Utilits.RandomSucess(100) <= ChaosCfg.GoldenSealedBoxSuccess)
				{
					CItem CBItem;
					CBItem.m_Type		= 0x1C7B; // Golden Box
					CBItem.m_Durability = 255.0;
					ChaosboxSuccess(&CBItem, aIndex,  CHAOS_TYPE_SEALED_BOX);
					Chat.MessageLog(1, c_Blue, t_NULL, gObj, SuccededMessage);
					gObj->Money = gObj->Money - ChaosCfg.GoldenSealedBoxPrice;
					GCMoneySend(aIndex, gObj->Money);
				}
				else
				{
					ChaosboxFailure(aIndex,CHAOS_TYPE_SEALED_BOX);
				}

				Chat.MessageLog(1, c_Red, t_NULL, gObj, FailtureMessage);

				return;
			} 
			else
			{
				if(Utilits.RandomSucess(100) <= ChaosCfg.SilverSealedBoxSuccess)
				{
					CItem CBItem;
					CBItem.m_Type = 0x1C7C; // Silver Box
					CBItem.m_Durability = 255.0;
					ChaosboxSuccess(&CBItem, aIndex,  CHAOS_TYPE_SEALED_BOX);
					Chat.MessageLog(1, c_Blue, t_NULL, gObj, SuccededMessage);
					gObj->Money = gObj->Money - ChaosCfg.SilverSealedBoxPrice;
					GCMoneySend(aIndex, gObj->Money);

					return;
				}
				else
				{
					ChaosboxFailure(aIndex,CHAOS_TYPE_SEALED_BOX);
					Chat.MessageLog(1, c_Red, t_NULL, gObj, FailtureMessage);

					return;
				}
			}

			break;
		}
	}
}

void ChaosMachineNew::ChaosboxSuccess(CItem *prize, int aIndex, CHAOS_TYPE mixid) 
{	
	OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);

	ChaosBoxInit(gObj);
	gObj->pChaosBox[0] = *prize;
	GCUserChaosBoxSend(gObj, 0);
}

void ChaosMachineNew::ChaosboxFailure(int aIndex, CHAOS_TYPE mixid) 
{
	OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);

	ChaosBoxInit(gObj);
	GCUserChaosBoxSend(gObj, 0);

	PMSG_CHAOSBOX_RESULT Msg = {0xC1, 0x0A, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	DataSend(aIndex, (unsigned char*)&Msg, 10);
}

bool ChaosMachineNew::ChaosboxCanExecute(int aIndex, CHAOS_TYPE mixid) 
{
	OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);

	//==============
	// Secromicon
	//==============
	if (mixid == CHAOS_TYPE_EMPIRE_GUARDIAN_BOOK)
	{
		if(Utilits.gObjGetItemCountInChaosbox(aIndex, 0x1C67) > 0 && Utilits.gObjGetItemCountInChaosbox(aIndex, 0x1C68) > 0 && Utilits.gObjGetItemCountInChaosbox(aIndex, 0x1C69) > 0 && Utilits.gObjGetItemCountInChaosbox(aIndex, 0x1C6A) > 0 && Utilits.gObjGetItemCountInChaosbox(aIndex, 0x1C6B) > 0 && Utilits.gObjGetItemCountInChaosbox(aIndex, 0x1C6C) > 0)
		{
			if(gObj->Money >= ChaosCfg.DimensionBookPrice)
			{
				return true;
			}
		}
		else
		{
			Chat.MessageLog(1, c_Red, t_NULL, gObj, LowMoneyMessage);

			return false;
		}
	}
	//==============
	// +14 Upgrade
	//==============
	if(mixid == CHAOS_TYPE_UPGRADE_14)
	{
		if(Utilits.gObjGetItemCountInChaosbox(aIndex, 0x1C0E) == 5 && Utilits.gObjGetItemCountInChaosbox(aIndex, 0x1C0D) == 5 && Utilits.gObjGetItemCountInChaosbox(aIndex, 0x180F) > 0)
		{
			if(gObj->Money >= ChaosCfg.Upgrade14Price)
			{
				return true;
			}
		}
		else
		{
			Chat.MessageLog(1, c_Red, t_NULL, gObj, LowMoneyMessage);

			return false;
		}
	}
	//============
	// +15 Upgrade
	//============
	if (mixid == CHAOS_TYPE_UPGRADE_15)
	{
		if(Utilits.gObjGetItemCountInChaosbox(aIndex, 0x1C0E) == 6 && Utilits.gObjGetItemCountInChaosbox(aIndex, 0x1C0D) == 6 && Utilits.gObjGetItemCountInChaosbox(aIndex, 0x180F) > 0)
		{
			if(gObj->Money >= ChaosCfg.Upgrade15Price)

			return true;
		}
		else
		{
			Chat.MessageLog(1, c_Red, t_NULL, gObj, LowMoneyMessage);

			return false;
		}
	}
	//============
	// Sealed Box
	//============
	if (mixid == CHAOS_TYPE_SEALED_BOX)
	{
		if(Utilits.gObjGetItemCountInChaosbox(aIndex,0x1C70) == 1 && (Utilits.gObjGetItemCountInChaosbox(aIndex,0x1C7A) == 1))
		{
			if(gObj->Money >= ChaosCfg.GoldenSealedBoxPrice || gObj->Money >= ChaosCfg.SilverSealedBoxPrice)

			return true;
		}
		else
		{
			Chat.MessageLog(1, c_Red, t_NULL, gObj, LowMoneyMessage);

			Chat.MessageLog(1, c_Red, t_NULL, gObj, LowMoneyMessage);

			return false;
		}
	}

	return false;
}

#endif