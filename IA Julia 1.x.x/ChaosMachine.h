#ifdef _GS
#ifndef CHAOS_MACHINE_H
#define CHAOS_MACHINE_H

#include "StdAfx.H"

typedef struct CHAOS_MACHINE
{
	int DimensionBookSucces;
	int DimensionBookPrice;
	int Upgrade14Success;
	int Upgrade14Price;
	int Upgrade15Success;
	int Upgrade15Price;
	int SilverSealedBoxSuccess;
	int SilverSealedBoxPrice;
	int GoldenSealedBoxSuccess;
	int GoldenSealedBoxPrice;
	int PandaPetSuccess;
	int PandaPetPrice;
	int SkeletonPetSuccess;
	int SkeletonPetPrice;
} CHAOSMACHINESTRUCT;

extern CHAOSMACHINESTRUCT ChaosCfg;

struct PMSG_C1C3HEAD
{
	unsigned char head;
	unsigned char len;
	unsigned char type;
};

struct PMSG_CHAOSBOX_RESULT
{
	PMSG_C1C3HEAD	head;
	unsigned char	info[7];
};

enum CHAOS_TYPE 
{
  CHAOS_TYPE_DEFAULT									= 0x01,
  CHAOS_TYPE_DEVILSQUARE								= 0x02,
  CHAOS_TYPE_UPGRADE_10									= 0x03,
  CHAOS_TYPE_UPGRADE_11									= 0x04,
  CHAOS_TYPE_UPGRADE_12									= 0x16,
  CHAOS_TYPE_UPGRADE_13									= 0x17,
  CHAOS_TYPE_DINORANT									= 0x05,
  CHAOS_TYPE_FRUIT										= 0x06,
  CHAOS_TYPE_SECOND_WING								= 0x07,
  CHAOS_TYPE_BLOODCATLE									= 0x08,
  CHAOS_TYPE_FIRST_WING									= 0x0B,
  CHAOS_TYPE_SETITEM									= 0x0C,
  CHAOS_TYPE_DARKHORSE									= 0x0D,
  CHAOS_TYPE_DARKSPIRIT									= 0x0E,
  CHAOS_TYPE_CLOAK										= 0x18,
  CHAOS_TYPE_BLESS_POTION								= 0x0F,
  CHAOS_TYPE_SOUL_POTION								= 0x10,
  CHAOS_TYPE_LIFE_STONE									= 0x11,
  CHAOS_TYPE_HT_BOX										= 0x14,
  CHAOS_TYPE_FENRIR_01									= 0x19,
  CHAOS_TYPE_FENRIR_02									= 0x1A,
  CHAOS_TYPE_FENRIR_03									= 0x1B,
  CHAOS_TYPE_FENRIR_04									= 0x1C,
  CHAOS_TYPE_COMPOUNDPOTION_LV1							= 0x1E,
  CHAOS_TYPE_COMPOUNTPOTION_LV2							= 0x1F,
  CHAOS_TYPE_COMPOUNTPOTION_LV3							= 0x20,
  CHAOS_TYPE_JEWELOFHARMONY_PURITY						= 0x21,
  CHAOS_TYPE_JEWELOFHARMONY_MIX_SMELTINGITEM			= 0x22,
  CHAOS_TYPE_JEWELOFHARMONY_RESTORE_ITEM				= 0x23,
  CHAOS_TYPE_380_OPTIONITEM								= 0x24,
  CHAOS_TYPE_OLD_PAPER									= 0x25,
  CHAOS_TYPE_CONDOR_FEATHER								= 0x26,
  CHAOS_TYPE_THIRD_WING									= 0x27,
  CHAOS_TYPE_EMPIRE_GUARDIAN_BOOK						= 0x2E,
  CHAOS_TYPE_SEALED_BOX									= 0x2F,
  CHAOS_TYPE_UPGRADE_14									= 0x31,
  CHAOS_TYPE_UPGRADE_15									= 0x32
};

void ChaosboxItemsRegardingEx();

#define FailtureMessage		"Chaos combination has failed."
#define	SuccededMessage		"Chaos combination has succeeded."
#define LowMoneyMessage		"You don't have enough money to execute the combination."

class ChaosMachineNew
{
	public:
		ChaosMachineNew();
		virtual ~ChaosMachineNew();

		void ChaosboxCombinationEx(int aIndex, unsigned char mixid);
		void ChaosboxSuccess(CItem *prize, int aIndex, CHAOS_TYPE mixid);
		void ChaosboxFailure(int aIndex, CHAOS_TYPE mixid);
		bool ChaosboxCanExecute(int aIndex, CHAOS_TYPE mixid);
		void ChaosMachineLoadConfig();
};

extern ChaosMachineNew CM;

#endif
#endif