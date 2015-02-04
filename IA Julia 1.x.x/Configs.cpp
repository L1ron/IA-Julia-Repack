#include "StdAfx.h"
#include "Configs.h"
#include "Logger.h"
#include "ChatCommands.h"
#include "GMSystem.h"
#include "AntiAFK.h"
#include "News.h"
#include "DropSystem.h"
#include "Archer.h"
#include "PCPoint.h"
#include "MossGambler.h"
#include "MapSystem.h"
#include "Query.h"
#include "WZEventDrop.h"
#include "MoveReq.h"
#include "DuelManager.h"
#include "Vip.h"
#include "Monster.h"
#include "HappyHour.h"
#include "PlayerSystem.h"
#include "TradeSystem.h"
#include "Territory.h"
#include "Jewels.h"
#include "OffTrade.h"
#include "ResetSystem.h"
#include "MarrySystem.h"
#include "Prodef.h"
#include "Helpers.h"
#include "Quests.h"

cConfigs Configs;

void cConfigs::LoadAll()
{
	LoadConfigsInGS();
	PCPoint.Load();
	GmSystem.Load();
	News.Load();
	AntiAFK.Load();
	GoldenArcher.Load();
	Helpers.Load();
	Quests.Load();
	Vip.Load();
	Monster.LoadPkClear();
	DropSystem.Load();
	MapSystem.Load();
	MoveReq.Load();
	ZenFixes();
	LoadNotice();
	LoadCommands();
	Chat.LoadChatCommands();
	Misc();
	HappyHour.Load();
	PlayerSystem.Load();
	TradeSystem.Load();
	Territory.Load();
	MaxStats();
	Jewels.Load();
	LoadPets();
	CalcCharacter();
#ifdef _GS
	DuelSystem.Load();
	Moss.Load();
	DropEvent.Init();
	Monster.LoadGolden();
#endif
	Marry.Init();
}

void cConfigs::CalcCharacter()
{
//============================= Fairy_Elf ============================================
	*(unsigned char*)AttackDamageMin_Bow_StrDexDiv_Elf1 = GetPrivateProfileInt("Fairy_Elf", "DamageMin_Bow_StrDexDiv", 7, IACalcCharacter);
	*(unsigned char*)AttackDamageMin_Bow_StrDexDiv_Elf2 = GetPrivateProfileInt("Fairy_Elf", "DamageMin_Bow_StrDexDiv_2", 7, IACalcCharacter);
	*(unsigned char*)AttackDamageMax_Bow_StrDexDiv_Elf1 = GetPrivateProfileInt("Fairy_Elf", "DamageMax_Bow_StrDexDiv", 4, IACalcCharacter);
	*(unsigned char*)AttackDamageMax_Bow_StrDexDiv_Elf2 = GetPrivateProfileInt("Fairy_Elf", "DamageMax_Bow_StrDexDiv_2", 4, IACalcCharacter);

	//NOBOW
	*(unsigned char*)AttackDamageMin_NoBow_DexDiv_Elf1 = GetPrivateProfileInt("Fairy_Elf", "DamageMin_NoBow_DexDiv", 7, IACalcCharacter);
	*(unsigned char*)AttackDamageMin_NoBow_DexDiv_Elf2 = GetPrivateProfileInt("Fairy_Elf", "DamageMin_NoBow_DexDiv_2", 7, IACalcCharacter);
	*(unsigned char*)AttackDamageMin_NoBow_StrDiv_Elf1 = GetPrivateProfileInt("Fairy_Elf", "DamageMin_NoBow_StrDiv", 14, IACalcCharacter);
	*(unsigned char*)AttackDamageMin_NoBow_StrDiv_Elf2 = GetPrivateProfileInt("Fairy_Elf", "DamageMin_NoBow_StrDiv_2", 14, IACalcCharacter);
	*(unsigned char*)AttackDamageMax_NoBow_DexDiv_Elf1 = GetPrivateProfileInt("Fairy_Elf", "DamageMax_NoBow_DexDiv", 4, IACalcCharacter);
	*(unsigned char*)AttackDamageMax_NoBow_DexDiv_Elf2 = GetPrivateProfileInt("Fairy_Elf", "DamageMax_NoBow_DexDiv_2", 4, IACalcCharacter);
	*(unsigned char*)AttackDamageMin_DexStrDiv_Elf1 = GetPrivateProfileInt("Fairy_Elf", "DamageMin_DexStrDiv", 7, IACalcCharacter);
	*(unsigned char*)AttackDamageMin_DexStrDiv_Elf2 = GetPrivateProfileInt("Fairy_Elf", "DamageMin_DexStrDiv_2", 7, IACalcCharacter);
	*(unsigned char*)AttackDamageMax_DexStrDiv_Elf1 = GetPrivateProfileInt("Fairy_Elf", "DamageMax_DexStrDiv", 4, IACalcCharacter);
	*(unsigned char*)AttackDamageMax_DexStrDiv_Elf2 = GetPrivateProfileInt("Fairy_Elf", "DamageMax_DexStrDiv_2", 4, IACalcCharacter);

	//============================= Dark_Knight ============================================
	*(unsigned char*)AttackDamageMin_StrDiv_DK1 = GetPrivateProfileInt("Dark_Knight", "DamageMin_StrDiv", 6, IACalcCharacter);
	*(unsigned char*)AttackDamageMin_StrDiv_DK2 = GetPrivateProfileInt("Dark_Knight", "DamageMin_StrDiv_2", 6, IACalcCharacter);
	*(unsigned char*)AttackDamageMax_StrDiv_DK1 = GetPrivateProfileInt("Dark_Knight", "DamageMax_StrDiv", 4, IACalcCharacter);
	*(unsigned char*)AttackDamageMax_StrDiv_DK2 = GetPrivateProfileInt("Dark_Knight", "DamageMax_StrDiv_2", 4, IACalcCharacter);

	//============================= Magic_Gladiator ============================================
	*(unsigned char*)AttackDamageMin_StrDiv_MG1 = GetPrivateProfileInt("Magic_Gladiator", "DamageMin_StrDiv", 6, IACalcCharacter);
	*(unsigned char*)AttackDamageMin_StrDiv_MG2 = GetPrivateProfileInt("Magic_Gladiator", "DamageMin_StrDiv_2", 6, IACalcCharacter);
	*(unsigned char*)AttackDamageMax_StrDiv_MG1 = GetPrivateProfileInt("Magic_Gladiator", "DamageMax_StrDiv", 4, IACalcCharacter);
	*(unsigned char*)AttackDamageMax_StrDiv_MG2 = GetPrivateProfileInt("Magic_Gladiator", "DamageMax_StrDiv_2", 4, IACalcCharacter);
	*(unsigned char*)AttackDamageMin_EneDiv_MG1 = GetPrivateProfileInt("Magic_Gladiator", "DamageMin_EneDiv", 12, IACalcCharacter);
	*(unsigned char*)AttackDamageMin_EneDiv_MG2 = GetPrivateProfileInt("Magic_Gladiator", "DamageMin_EneDiv_2", 12, IACalcCharacter);
	*(unsigned char*)AttackDamageMax_EneDiv_MG1 = GetPrivateProfileInt("Magic_Gladiator", "DamageMax_EneDiv", 8, IACalcCharacter);
	*(unsigned char*)AttackDamageMax_EneDiv_MG2 = GetPrivateProfileInt("Magic_Gladiator", "DamageMax_EneDiv_2", 8, IACalcCharacter);

	//============================= Dark_Lord ============================================
	*(unsigned char*)AttackDamageMin_StrDiv_DL1 = GetPrivateProfileInt("Dark_Lord", "DamageMin_StrDiv", 7, IACalcCharacter);
	*(unsigned char*)AttackDamageMin_StrDiv_DL2 = GetPrivateProfileInt("Dark_Lord", "DamageMin_StrDiv_2", 7, IACalcCharacter);
	*(unsigned char*)AttackDamageMin_EneDiv_DL1 = GetPrivateProfileInt("Dark_Lord", "DamageMin_EneDiv", 14, IACalcCharacter);
	*(unsigned char*)AttackDamageMin_EneDiv_DL2 = GetPrivateProfileInt("Dark_Lord", "DamageMin_EneDiv_2", 14, IACalcCharacter);
	*(unsigned char*)AttackDamageMax_StrDiv_DL1 = GetPrivateProfileInt("Dark_Lord", "DamageMax_StrDiv", 5, IACalcCharacter);
	*(unsigned char*)AttackDamageMax_StrDiv_DL2 = GetPrivateProfileInt("Dark_Lord", "DamageMax_StrDiv_2", 5, IACalcCharacter);
	*(unsigned char*)AttackDamageMax_EneDiv_DL1 = GetPrivateProfileInt("Dark_Lord", "DamageMax_EneDiv", 10, IACalcCharacter);
	*(unsigned char*)AttackDamageMax_EneDiv_DL2 = GetPrivateProfileInt("Dark_Lord", "DamageMax_EneDiv_2", 10, IACalcCharacter);

	//============================= Summoner ============================================
	*(unsigned char*)AttackDamageMin_StrDiv_SUM1 = GetPrivateProfileInt("Summoner", "DamageMin_StrDiv", 7, IACalcCharacter);
	*(unsigned char*)AttackDamageMin_StrDiv_SUM2 = GetPrivateProfileInt("Summoner", "DamageMin_StrDiv_2", 7, IACalcCharacter);
	*(unsigned char*)AttackDamageMax_StrDiv_SUM1 = GetPrivateProfileInt("Summoner", "DamageMax_StrDiv", 4, IACalcCharacter);
	*(unsigned char*)AttackDamageMax_StrDiv_SUM2 = GetPrivateProfileInt("Summoner", "DamageMax_StrDiv_2", 4, IACalcCharacter);

	//============================= Dark_Wizard ============================================
	*(unsigned char*)AttackDamageMin_StrDiv_DW1 = GetPrivateProfileInt("Dark_Wizard", "DamageMin_StrDiv", 6, IACalcCharacter);
	*(unsigned char*)AttackDamageMin_StrDiv_DW2 = GetPrivateProfileInt("Dark_Wizard", "DamageMin_StrDiv_2", 6, IACalcCharacter);
	*(unsigned char*)AttackDamageMax_StrDiv_DW1 = GetPrivateProfileInt("Dark_Wizard", "DamageMax_StrDiv", 4, IACalcCharacter);
	*(unsigned char*)AttackDamageMax_StrDiv_DW2 = GetPrivateProfileInt("Dark_Wizard", "DamageMax_StrDiv_2", 4, IACalcCharacter);

	//============================= AtackSpeed ============================================
	*(unsigned char*)AttackSpeed_Elf1 = GetPrivateProfileInt("AttackSpeed", "AttackSpeed__Elf", 50, IACalcCharacter);
	*(unsigned char*)AttackSpeed_DK_MG1 = GetPrivateProfileInt("AttackSpeed", "AttackSpeed__DK_MG", 15, IACalcCharacter);
	*(unsigned char*)AttackSpeed_DL1 = GetPrivateProfileInt("AttackSpeed", "AttackSpeed__DL", 10, IACalcCharacter);
	*(unsigned char*)AttackSpeed_Sum1 = GetPrivateProfileInt("AttackSpeed", "AttackSpeed__SUM", 20, IACalcCharacter);
	*(unsigned char*)AttackSpeed_DW1 = GetPrivateProfileInt("AttackSpeed", "AttackSpeed__DW", 20, IACalcCharacter);

	//============================= MagicSpeed ============================================
	*(unsigned char*)AttackSpeed_Elf2 = GetPrivateProfileInt("MagicSpeed", "MagicSpeed__Elf", 50, IACalcCharacter);
	*(unsigned char*)AttackSpeed_DK_MG2 = GetPrivateProfileInt("MagicSpeed", "MagicSpeed__DK_MG", 20, IACalcCharacter);
	*(unsigned char*)AttackSpeed_DL2 = GetPrivateProfileInt("MagicSpeed", "MagicSpeed__DL", 10, IACalcCharacter);
	*(unsigned char*)AttackSpeed_Sum2 = GetPrivateProfileInt("MagicSpeed", "MagicSpeed__SUM", 20, IACalcCharacter);
	*(unsigned char*)AttackSpeed_DW2 = GetPrivateProfileInt("MagicSpeed", "MagicSpeed__DW", 10, IACalcCharacter);

	//============================= SuccessfulBlocking ============================================
	*(unsigned char*)SuccessfulBlocking_Elf = GetPrivateProfileInt("SuccessfulBlocking", "SuccessfulBlocking__Elf", 4, IACalcCharacter);
	*(unsigned char*)SuccessfulBlocking_DW_DK_MG = GetPrivateProfileInt("SuccessfulBlocking", "SuccessfulBlocking__DW_DK_MG", 7, IACalcCharacter);
	*(unsigned char*)SuccessfulBlocking_DL = GetPrivateProfileInt("SuccessfulBlocking", "SuccessfulBlocking__DL", 4, IACalcCharacter);
	*(unsigned char*)SuccessfulBlocking_Sum = GetPrivateProfileInt("SuccessfulBlocking", "SuccessfulBlocking__SUM", 3, IACalcCharacter);

	//============================= Defense ============================================
	*(unsigned char*)Defense_Elf = GetPrivateProfileInt("Defense", "Defense__Elf", 10, IACalcCharacter);
	*(unsigned char*)Defense_DK = GetPrivateProfileInt("Defense", "Defense__DK", 3, IACalcCharacter);
	*(unsigned char*)Defense_DL = GetPrivateProfileInt("Defense", "Defense__DL", 7, IACalcCharacter);
	*(unsigned char*)Defense_Sum = GetPrivateProfileInt("Defense", "Defense__SUM", 3, IACalcCharacter);
	*(unsigned char*)Defense_DW_MG = GetPrivateProfileInt("Defense", "Defense__DW_MG", 4, IACalcCharacter);

	Log.ConsoleOutPut(1,c_Green,t_Default,"[û] [CalcCharacter]\tCarregado.");
}

void cConfigs::MaxStats()
{
	int MaxPoints = 32000;
	if (Enable65kStats > 0)MaxPoints = 65000;

	MaxStatsSystemEnable = GetInt(0, 1, 0, "MaximumStats", "Enabled", IAJuliaMaximum);

	if(!MaxStatsSystemEnable)
	{
		return;
	}

	MaxDL_Strength = GetInt(0, MaxPoints, 32000, "MaximumStats", "MaxDL_Strength", IAJuliaMaximum);
	MaxDL_Agility = GetInt(0, MaxPoints, 32000, "MaximumStats", "MaxDL_Agility", IAJuliaMaximum);
	MaxDL_Vitality = GetInt(0, MaxPoints, 32000, "MaximumStats", "MaxDL_Vitality", IAJuliaMaximum);
	MaxDL_Energy = GetInt(0, MaxPoints, 32000, "MaximumStats", "MaxDL_Energy", IAJuliaMaximum);
	MaxDL_Command = GetInt(0, MaxPoints, 32000, "MaximumStats", "MaxDL_Command", IAJuliaMaximum);

	MaxDK_Strength = GetInt(0, MaxPoints, 32000, "MaximumStats", "MaxDK_Strength", IAJuliaMaximum);
	MaxDK_Agility = GetInt(0, MaxPoints, 32000, "MaximumStats", "MaxDK_Agility", IAJuliaMaximum);
	MaxDK_Vitality = GetInt(0, MaxPoints, 32000, "MaximumStats", "MaxDK_Vitality", IAJuliaMaximum);
	MaxDK_Energy = GetInt(0, MaxPoints, 32000, "MaximumStats", "MaxDK_Energy", IAJuliaMaximum);

	MaxDW_Strength = GetInt(0, MaxPoints, 32000, "MaximumStats", "MaxDW_Strength", IAJuliaMaximum);
	MaxDW_Agility = GetInt(0, MaxPoints, 32000, "MaximumStats", "MaxDW_Agility", IAJuliaMaximum);
	MaxDW_Vitality = GetInt(0, MaxPoints, 32000, "MaximumStats", "MaxDW_Vitality", IAJuliaMaximum);
	MaxDW_Energy = GetInt(0, MaxPoints, 32000, "MaximumStats", "MaxDW_Energy", IAJuliaMaximum);

	MaxELF_Strength = GetInt(0, MaxPoints, 32000, "MaximumStats", "MaxELF_Strength", IAJuliaMaximum);
	MaxELF_Agility = GetInt(0, MaxPoints, 32000, "MaximumStats", "MaxELF_Agility", IAJuliaMaximum);
	MaxELF_Vitality = GetInt(0, MaxPoints, 32000, "MaximumStats", "MaxELF_Vitality", IAJuliaMaximum);
	MaxELF_Energy = GetInt(0, MaxPoints, 32000, "MaximumStats", "MaxELF_Energy", IAJuliaMaximum);

	MaxSUM_Strength = GetInt(0, MaxPoints, 32000, "MaximumStats", "MaxSUM_Strength", IAJuliaMaximum);
	MaxSUM_Agility = GetInt(0, MaxPoints, 32000, "MaximumStats", "MaxSUM_Agility", IAJuliaMaximum);
	MaxSUM_Vitality = GetInt(0, MaxPoints, 32000, "MaximumStats", "MaxSUM_Vitality", IAJuliaMaximum);
	MaxSUM_Energy = GetInt(0, MaxPoints, 32000, "MaximumStats", "MaxSUM_Energy", IAJuliaMaximum);

	MaxMG_Strength = GetInt(0, MaxPoints, 32000, "MaximumStats", "MaxMG_Strength", IAJuliaMaximum);
	MaxMG_Agility = GetInt(0, MaxPoints, 32000, "MaximumStats", "MaxMG_Agility", IAJuliaMaximum);
	MaxMG_Vitality = GetInt(0, MaxPoints, 32000, "MaximumStats", "MaxMG_Vitality", IAJuliaMaximum);
	MaxMG_Energy = GetInt(0, MaxPoints, 32000, "MaximumStats", "MaxMG_Energy", IAJuliaMaximum);

	Log.ConsoleOutPut(1, c_Magenta, t_Default, "[û] [MaxStats]\tIniciado.");
}

void cConfigs::ZenFixes()
{
	Zen.NormalZen = GetInt(0, 65535, 20, "ZenSettings", "ZenDrop", IAJuliaCommon);
	Zen.ZenInParty = GetInt(0, 65535, 20, "ZenSettings", "ZenPartyDrop", IAJuliaCommon);
}

void cConfigs::LoadPets()
{
	Panda.PetPandaDefense = GetInt(0, 1000, 10, "Panda", "PetPandaDefense", IAJuliaPets);
	Panda.PetPandaAttackDamageMinLeft = GetInt(0, 1000, 10, "Panda", "PetPandaAttackDamageMinLeft", IAJuliaPets);
	Panda.PetPandaAttackDamageMaxLeft = GetInt(0, 1000, 10, "Panda", "PetPandaAttackDamageMaxLeft", IAJuliaPets);
	Panda.PetPandaAttackDamageMinRight = GetInt(0, 1000, 10, "Panda", "PetPandaAttackDamageMinRight", IAJuliaPets);
	Panda.PetPandaAttackDamageMaxRight = GetInt(0, 1000, 10, "Panda", "PetPandaAttackDamageMaxRight", IAJuliaPets);
	Panda.PetPandaMagicDamageMin = GetInt(0, 1000, 10, "Panda", "PetPandaMagicDamageMin", IAJuliaPets);
	Panda.PetPandaMagicDamageMax = GetInt(0, 1000, 10, "Panda", "PetPandaMagicDamageMax", IAJuliaPets);
	Panda.PetPandaMagicSpeed = GetInt(0, 1000, 10, "Panda", "PetPandaMagicSpeed", IAJuliaPets);
	Panda.PetPandaAttackSpeed = GetInt(0, 1000, 10, "Panda", "PetPandaAttackSpeed", IAJuliaPets);

	Panda.PandaRingDefense = GetInt(0, 1000, 10, "PandaRing", "PandaRingDefense", IAJuliaPets);
	Panda.PandaRingAttackDamageMinLeft = GetInt(0, 1000, 10, "PandaRing", "PandaRingAttackDamageMinLeft", IAJuliaPets);
	Panda.PandaRingAttackDamageMaxLeft = GetInt(0, 1000, 10, "PandaRing", "PandaRingAttackDamageMaxLeft", IAJuliaPets);
	Panda.PandaRingAttackDamageMinRight = GetInt(0, 1000, 10, "PandaRing", "PandaRingAttackDamageMinRight", IAJuliaPets);
	Panda.PandaRingAttackDamageMaxRight = GetInt(0, 1000, 10, "PandaRing", "PandaRingAttackDamageMaxRight", IAJuliaPets);
	Panda.PandaRingMagicDamageMin = GetInt(0, 1000, 10, "PandaRing", "PandaRingMagicDamageMin", IAJuliaPets);
	Panda.PandaRingMagicDamageMax = GetInt(0, 1000, 10, "PandaRing", "PandaRingMagicDamageMax", IAJuliaPets);
	Panda.PandaRingMagicSpeed = GetInt(0, 1000, 10, "PandaRing", "PandaRingMagicSpeed", IAJuliaPets);
	Panda.PandaRingAttackSpeed = GetInt(0, 1000, 10, "PandaRing", "PandaRingAttackSpeed", IAJuliaPets);

	Panda.PetPandaExpirence = GetInt(0, 10000, 100, "Panda", "PetPandaExpirence", IAJuliaPets);
	Panda.PandaRingExpirence = GetInt(0, 10000, 100, "PandaRing", "PandaRingExpirence", IAJuliaPets);
}

void cConfigs::LoadNotice()
{
	ConnectInfo = GetInt(0,1,1,"Connect","ConnectInfo", IAJuliaGS);
	GetPrivateProfileString("Connect","ConnectNotice","Powered by IA Julia 1.1.x",ConnectNotice, sizeof(ConnectNotice), IAJuliaGS);
	Log.CheckProcent(ConnectNotice);
}

void cConfigs::LoadConfigsInGS()
{
#ifdef _GS
	DWORD *LoreGuard = (DWORD*)GUARD_SAY;

	char Lore[25];
	GetPrivateProfileString("Connect","GuardSay","Nao enche :P",Lore,sizeof(Lore),IAJuliaGS);
	memset(&LoreGuard[0],0,sizeof(Lore));
	memcpy(&LoreGuard[0],Lore,strlen(Lore));
#endif

	DWORD dword;
	BYTE byte;

	dword = GetInt(300, 1000, 400, "LevelSettings", "MaxLevel", IAJuliaCommon);
	*(unsigned int*)GS_MAX_LEVEL1 = dword;
	*(unsigned int*)GS_MAX_LEVEL2 = dword;
	*(unsigned int*)GS_MAX_LEVEL3 = dword;
	*(unsigned int*)GS_MAX_LEVEL4 = dword;
	*(unsigned int*)GS_MAX_LEVEL5 = dword;
	Commands.MaxLvl = dword;

	*(unsigned int*)GS_NOEXP_LEVEL = GetInt(401, 1001, 401, "LevelSettings", "MaxXPLevel", IAJuliaCommon);
	*(unsigned int*)GS_MAX_MASTERLEVEL = GetInt(1, 400, 200, "LevelSettings", "MaxMasterLevel", IAJuliaCommon);

	dword = GetInt(0, 360, 120, "ItemDropRates", "LootingTime", IAJuliaItems);
	*(unsigned int*)GS_ITEM_TIME1 = 1000 * dword;
	*(unsigned int*)GS_ITEM_TIME2 = 1000 * dword;

	*(unsigned int*)GS_TRANSFORMATIONRING1 = GetInt(0, 600, 2, "TransformationRings", "TransformRing1", IAJuliaItems);
	*(unsigned int*)GS_TRANSFORMATIONRING2 = GetInt(0, 600, 7, "TransformationRings", "TransformRing2", IAJuliaItems);
	*(unsigned int*)GS_TRANSFORMATIONRING3 = GetInt(0, 600, 14, "TransformationRings", "TransformRing3", IAJuliaItems);
	*(unsigned int*)GS_TRANSFORMATIONRING4 = GetInt(0, 600, 8, "TransformationRings", "TransformRing4", IAJuliaItems);
	*(unsigned int*)GS_TRANSFORMATIONRING5 = GetInt(0, 600, 9, "TransformationRings", "TransformRing5", IAJuliaItems);
	*(unsigned int*)GS_TRANSFORMATIONRING6 = GetInt(0, 600, 41, "TransformationRings", "TransformRing6", IAJuliaItems);

	*(unsigned char*)GS_SUMMONORB1 = GetChar(0, 600, 26, "SummonOrbs", "OrbSummon1", IAJuliaItems);
	*(unsigned char*)GS_SUMMONORB2 = GetChar(0, 600, 32, "SummonOrbs", "OrbSummon2", IAJuliaItems);
	*(unsigned char*)GS_SUMMONORB3 = GetChar(0, 600, 21, "SummonOrbs", "OrbSummon3", IAJuliaItems);
	*(unsigned char*)GS_SUMMONORB4 = GetChar(0, 600, 20, "SummonOrbs", "OrbSummon4", IAJuliaItems);
	*(unsigned char*)GS_SUMMONORB5 = GetChar(0, 600, 10, "SummonOrbs", "OrbSummon5", IAJuliaItems);
	*(unsigned char*)GS_SUMMONORB6 = GetChar(0, 600, 150, "SummonOrbs", "OrbSummon6", IAJuliaItems);
	*(unsigned char*)GS_SUMMONORB7 = GetChar(0, 600, 151, "SummonOrbs", "OrbSummon7", IAJuliaItems);

	*(unsigned int*)GS_BLESS_PRICE = GetInt(0, 2000000000, 6000000, "JewelPrices", "JewelOfBlessPrice", IAJuliaItems);
	*(unsigned int*)GS_SOUL_PRICE = GetInt(0, 2000000000, 9000000, "JewelPrices", "JewelOfSoulPrice", IAJuliaItems);
	*(unsigned int*)GS_CHAOS_PRICE = GetInt(0, 2000000000, 810000, "JewelPrices", "JewelOfChaosPrice", IAJuliaItems);
	*(unsigned int*)GS_LIFE_PRICE = GetInt(0, 2000000000, 45000000, "JewelPrices", "JewelOfLifePrice", IAJuliaItems);
	*(unsigned int*)GS_CREATION_PRICE = GetInt(0, 2000000000, 36000000, "JewelPrices", "JewelOfCreationPrice", IAJuliaItems);
	*(unsigned int*)GS_GUARDIAN_PRICE = GetInt(0, 2000000000, 60000000, "JewelPrices", "JewelOfGuardianPrice", IAJuliaItems);
	*(unsigned int*)GS_FRUITS_PRICE = GetInt(0, 2000000000, 33000000, "JewelPrices", "FruitPrice", IAJuliaItems);
	*(unsigned int*)GS_MONARCH_PRICE = GetInt(0, 2000000000, 750000, "JewelPrices", "CrestOfMonarchPrice", IAJuliaItems);
	*(unsigned int*)GS_FEATHER_PRICE = GetInt(0, 2000000000, 180000, "JewelPrices", "LochsFeatherPrice", IAJuliaItems);
	*(unsigned int*)GS_BLESSPOT_PRICE = GetInt(0, 2000000000, 900000, "JewelPrices", "PotionOfBlessPrice", IAJuliaItems);
	*(unsigned int*)GS_SOULPOT_PRICE = GetInt(0, 2000000000, 450000, "JewelPrices", "PotionOfSoulPrice", IAJuliaItems);
#ifdef _GS
	*(unsigned char*) SELUPAN_ITEM_COUNT = GetChar(0,20,10,"Selupan","DropCountItems",IAJuliaEvents);

	*(unsigned int*) GS_KUNDUN_ANC_PERCT = GetInt(0,10000,25,"Kundun","KundunDropAncRate",IAJuliaItems);
	*(unsigned char*) GS_KUNDUN_ITEM_NUMB = GetChar(0,20,3,"Kundun","KundunDropItemCount",IAJuliaItems);

	*(unsigned char*) GS_CCPLAYER = GetChar(0,20,2,"ChaosCastle","ChaosCastleMinPlayers",IAJuliaEvents);
	*(unsigned char*) GS_ITPLAYER = GetChar(0,20,4,"IllusionTemple","ItMinPlayers",IAJuliaEvents);
#endif
	*(unsigned char*)GS_GUILDALLIANCE = GetChar(0, 50, 20, "Guild", "GuildAllianceMinPlayers", IAJuliaCommon);
	*(unsigned char*)GS_GUILDALLIANCE2 = GetChar(0, 20, 5, "Guild", "GuildAllianceMaxGuilds", IAJuliaCommon);

	*(unsigned char*)GS_PKBugLimitFix1 = GetChar(0, 1000, 20, "PKOptions", "PKKillLimit", IAJuliaCommon);
	*(unsigned char*)GS_PKBugLimitFix2 = GetChar(0, 1000, 20, "PKOptions", "PKKillLimit", IAJuliaCommon);
	*(unsigned char*)GS_PKBugLimitFix3 = GetChar(0, 1000, 20, "PKOptions", "PKKillLimit", IAJuliaCommon);

	*(unsigned int*)GS_UDP_PORT = GetInt(0, 99999, 60006, "Connect", "UDP-Port", IAJuliaGS);

	*(unsigned char*)GS_SOUL_RATE_NORMAL = GetChar(0, 100, 60, "JewelRates", "SoulSuccessRateNormal", IAJuliaItems);
	*(unsigned char*)GS_SOUL_RATE_SPECIAL = GetChar(0, 100, 50, "JewelRates", "SoulSuccessRateSpecial", IAJuliaItems);
	*(unsigned char*)GS_SOUL_RATE_SOCKET = GetChar(0, 100, 40, "JewelRates", "SoulSuccessRateSocket", IAJuliaItems);
	*(unsigned char*)GS_SOUL_LUCK_ADD = GetChar(0, 100, 20, "JewelRates", "SoulSuccessRateLuck", IAJuliaItems);
	*(unsigned char*)GS_JOL_FAIL_RATE = GetChar(0, 100, 50, "JewelRates", "LifeFailRate", IAJuliaItems);

	byte = GetChar(0, 100, 60, "ChaosMachineMixes", "ChaosMix10Rate", IAJuliaItems);
	*(unsigned char*)GS_CM_MIX_10_NORMAL = byte;
	*(unsigned char*)GS_CM_MIX_10_SPECIAL = byte;
	*(unsigned char*)GS_CM_MIX_10_SOCKET = byte;
	byte = GetChar(0, 100, 50, "ChaosMachineMixes", "ChaosMix11_12Rate", IAJuliaItems);
	*(unsigned char*)GS_CM_MIX_11_12_NORMAL = byte;
	*(unsigned char*)GS_CM_MIX_11_12_SPECIAL = byte;
	*(unsigned char*)GS_CM_MIX_11_12_SOCKET = byte;
	byte = GetChar(0, 100, 40, "ChaosMachineMixes", "ChaosMix13Rate", IAJuliaItems);
	*(unsigned char*)GS_CM_MIX_13_NORMAL = byte;
	*(unsigned char*)GS_CM_MIX_13_SPECIAL = byte;
	*(unsigned char*)GS_CM_MIX_13_SOCKET = byte;
	byte = GetChar(0, 100, 75, "ChaosMachineMixes", "ChaosMixWithLuck", IAJuliaItems);
	*(unsigned char*)GS_CM_MIX_10_LUCK = byte;
	*(unsigned char*)GS_CM_MIX_11_13_LUCK = byte;
	*(unsigned char*)GS_CM_MIX_LUCK_ADD = GetChar(0, 100, 20, "ChaosMachineMixes", "ChaosMixRateIncreaseWithLuck", IAJuliaItems);
	*(unsigned char*)DEFAULTMIXRATE = GetChar(0, 100, 45, "ChaosMachineMixes", "ChaosMixDefaultRate", IAJuliaItems);
	*(unsigned char*)GS_WINGLVL1MIX = GetChar(0, 100, 90, "ChaosMachineMixes", "WingMixLvl1SuccessRate", IAJuliaItems);
	*(unsigned char*)GS_WINGLVL2MIX = GetChar(0, 100, 90, "ChaosMachineMixes", "WingMixLvl2SuccessRate", IAJuliaItems);
	byte = GetChar(0, 100, 60, "ChaosMachineMixes", "CondorMixSuccessRate", IAJuliaItems);
	*(unsigned char *)GS_WINGLVL3MIX11 = byte;
	*(unsigned char *)GS_WINGLVL3MIX12 = byte;
	byte = GetChar(0, 100, 40, "ChaosMachineMixes", "WingMixLvl3SuccessRate", IAJuliaItems);
	*(unsigned char *)GS_WINGLVL3MIX21 = byte;
	*(unsigned char *)GS_WINGLVL3MIX22 = byte;

	*(unsigned char*)GS_SETITEMMIX1 = GetChar(0, 100, 80, "ChaosMachineMixes", "380LevelMixSuccessRate", IAJuliaItems);
	*(unsigned char*)GS_SETITEMMIX2 = GetChar(0, 100, 80, "ChaosMachineMixes", "380LevelMixSuccessRate", IAJuliaItems);
	*(unsigned int*)GS_DINO_MIX = GetInt(0, 100, 70, "ChaosMachineMixes", "DinorantMixSuccessRate", IAJuliaItems);

	*(unsigned int*)GS_DARK_HORSE = GetInt(0, 100, 60, "DLPets", "DarkHorseMixSuccessRate", IAJuliaItems);
	*(unsigned int*)GS_DARK_HORSE_PRICE = GetInt(0, 2000000000, 5000000, "DLPets", "DarkHorseMixPrice", IAJuliaItems);
	*(unsigned int*)GS_DARK_SPIRIT = GetInt(0, 100, 60, "DLPets", "DarkSpiritMixSuccessRate", IAJuliaItems);
	*(unsigned int*)GS_DARK_SPIRIT_PRICE = GetInt(0, 2000000000, 1000000, "DLPets", "DarkSpiritMixPrice", IAJuliaItems);

	//Percentage for EXERate 0 - 100%
	int EXERate = GetInt(0, 100, 10, "ItemDropRates", "ExcDropRate", IAJuliaItems);
	*(unsigned int*)GS_EXC_DROP_RATE = 2000 - (20 * EXERate);
	//
	*(unsigned int*)GS_EXC_SKILL_RATE = GetInt(0, 100, 100, "ItemDropRates", "ExcSkillDropRate", IAJuliaItems);
	*(unsigned int*)GS_EXC_LUCK_RATE = GetInt(0, 100, 1, "ItemDropRates", "ExcLuckDropRate", IAJuliaItems);
	*(unsigned int*)GS_SKILL_RATE = GetInt(0, 100, 6, "ItemDropRates", "NormalSkillDropRate", IAJuliaItems);
	*(unsigned int*)GS_LUCK_RATE = GetInt(0, 100, 4, "ItemDropRates", "NormalLuckDropRate", IAJuliaItems);
	*(unsigned char*)GS_ANCREWARD_SKILL_RATE = GetChar(0, 100, 6, "ItemDropRates", "AncientRewardSkillDropRate", IAJuliaItems);
	*(unsigned char*)GS_ANCREWARD_LUCK_RATE = GetChar(0, 100, 4, "ItemDropRates", "AncientRewardLuckDropRate", IAJuliaItems);
	*(unsigned char*)GS_ANCRANDOM_SKILL_RATE = GetChar(0, 100, 6, "ItemDropRates", "AncientRandomSkillDropRate", IAJuliaItems);
	*(unsigned char*)GS_ANCRANDOM_LUCK_RATE = GetChar(0, 100, 4, "ItemDropRates", "AncientRandomLuckDropRate", IAJuliaItems);

	byte = GetChar(0, 20, 7, "LevelUpPoints", "LevelUpPointsForDl", IAJuliaCommon);
	*(unsigned char*)GS_LVL_UP_DL1 = byte;
	*(unsigned char*)GS_LVL_UP_DL2 = byte;
	*(unsigned char*)GS_LVL_UP_DL3 = byte;
	*(unsigned char*)GS_LVL_UP_DL4 = byte;
	*(unsigned char*)GS_LVL_UP_DL5 = byte;

	byte = GetChar(0, 20, 7, "LevelUpPoints", "LevelUpPointsForMg", IAJuliaCommon);
	*(unsigned char*)GS_LVL_UP_MG1 = byte;
	*(unsigned char*)GS_LVL_UP_MG2 = byte;
	*(unsigned char*)GS_LVL_UP_MG3 = byte;
	*(unsigned char*)GS_LVL_UP_MG4 = byte;
	*(unsigned char*)GS_LVL_UP_MG5 = byte;

	byte = GetChar(0, 20, 5, "LevelUpPoints", "LevelUpPointsForDkElfDwSum", IAJuliaCommon);
	*(unsigned char*)GS_LVL_UP_NORMAL1 = byte;
	*(unsigned char*)GS_LVL_UP_NORMAL2 = byte;
	*(unsigned char*)GS_LVL_UP_NORMAL3 = byte;
	*(unsigned char*)GS_LVL_UP_NORMAL4 = byte;
	*(unsigned char*)GS_LVL_UP_NORMAL5 = byte;

	byte = GetChar(0, 5, 1, "LevelUpPoints", "ExtraPointsAfterMarlonQuest", IAJuliaCommon);
	*(unsigned char*)GS_LVL_UP_QUEST1 = byte;
	*(unsigned char*)GS_LVL_UP_QUEST2 = byte;
	*(unsigned char*)GS_LVL_UP_QUEST3 = byte;
	*(unsigned char*)GS_LVL_UP_QUEST4 = byte;
	*(unsigned char*)GS_LVL_UP_QUEST5 = byte;

	*(unsigned char*)GS_ML_POINTS = GetChar(0, 20, 1, "LevelUpPoints", "MasterlvlPoints", IAJuliaCommon);

	*(unsigned int *)GS_TWISTINGSLASH_USELV = GetInt(0, 5000, 80, "SkillLevel", "TwistingSlashMinLevel", IAJuliaSkills);
	*(unsigned int *)GS_RAGEFULBLOW_USELV = GetInt(0, 5000, 170, "SkillLevel", "RagefulBlowMinLevel", IAJuliaSkills);
	*(unsigned int *)GS_DEATHSTAB_USELV = GetInt(0, 5000, 160, "SkillLevel", "DeathStabMinLevel", IAJuliaSkills);
	*(unsigned int *)GS_IMPALE_USELV = GetInt(0, 5000, 25, "SkillLevel", "ImapleMinLevel", IAJuliaSkills);
	*(unsigned int *)GS_INNERSTRENGTH_USELV = GetInt(0, 5000, 120, "SkillLevel", "GreaterFortitudeMinLevel", IAJuliaSkills);
	*(unsigned int *)GS_PENETRATION_USELV = GetInt(0, 5000, 130, "SkillLevel", "PenetrationMinLevel", IAJuliaSkills);

	*(unsigned int *)GS_MSNORMAL01 = GetInt(0, 10000, 32, "ManaShield", "ManaShieldAgiNormal", IAJuliaSkills);
	*(unsigned int *)GS_MSNORMAL02 = GetInt(0, 10000, 200, "ManaShield", "ManaShieldEneNormal", IAJuliaSkills);
	*(unsigned int *)GS_MSMASTER01 = GetInt(0, 10000, 32, "ManaShield", "ManaShieldAgiMaster", IAJuliaSkills);
	*(unsigned int *)GS_MSMASTER02 = GetInt(0, 10000, 200, "ManaShield", "ManaShieldEneMaster", IAJuliaSkills);

	*(unsigned int *)NormalManaShieldTime1 = GetInt(0, 10000, 40, "ManaShield", "ManaShieldTime", IAJuliaSkills);
	*(unsigned int *)MasterManaShieldTime2 = GetInt(0, 10000, 40, "ManaShield", "ManaShieldTimeMaster", IAJuliaSkills);

	dword = GetInt(0, 5000, 150, "GreatFortitude", "GreatFortitudeVitNormal", IAJuliaSkills);
	*(unsigned int *)NormalGreatForitiuteVit01 = dword;
	*(unsigned int *)NormalGreatForitiuteVit02 = dword;
	*(unsigned int *)NormalGreatForitiuteVit03 = dword;
	*(unsigned int *)GS_GFNORMAL02 = GetInt(0, 5000, 100, "GreatFortitude", "GreatFortitudeEneNormal", IAJuliaSkills);

	dword = GetInt(0, 5000, 150, "GreatFortitude", "GreatFortitudeVitMaster", IAJuliaSkills);
	*(unsigned int *)MasterGreatForitiuteVit01 = dword;
	*(unsigned int *)MasterGreatForitiuteVit02 = dword;
	*(unsigned int *)MasterGreatForitiuteVit03 = dword;
	*(unsigned int *)GS_GFMASTER02 = GetInt(0, 5000, 100, "GreatFortitude", "GreatFortitudeEneMaster", IAJuliaSkills);

	*(unsigned int *)NormalGreatForitiuteTime = GetInt(0, 10000, 10, "GreatFortitude", "GreatFortitudeTime", IAJuliaSkills);
	*(unsigned int *)MasterGreatForitiuteTime = GetInt(0, 10000, 10, "GreatFortitude", "GreatFortitudeMaster", IAJuliaSkills);

	*(unsigned int*)GS_BERSERKER_DIV1 = GetInt(0, 5000, 20, "Berserker", "BerserkerDiv1", IAJuliaSkills);
	*(unsigned int*)GS_BERSERKER_DIV2 = GetInt(0, 5000, 30, "Berserker", "BerserkerDiv2", IAJuliaSkills);
	*(unsigned int*)GS_BERSERKER_DIV3 = GetInt(0, 5000, 60, "Berserker", "BerserkerDiv3", IAJuliaSkills);
	*(unsigned int*)GS_DAMAGEREF_DIV1 = GetInt(0, 5000, 42, "DamageRef", "DamageRefDiv1", IAJuliaSkills);
	*(unsigned int*)GS_DAMAGEREF_DIV2 = GetInt(0, 5000, 25, "DamageRef", "DamageRefDiv2", IAJuliaSkills);

	*(unsigned int*)GS_CRITICALDMG_COMMAND = GetInt(0, 5000, 25, "CriticalDmg", "CriticalDmgLeaderShip", IAJuliaSkills);
	*(unsigned int*)GS_CRITICALDMG_ENERGY = GetInt(0, 5000, 30, "CriticalDmg", "CriticalDmgEnergy", IAJuliaSkills);
	*(unsigned int*)GS_CRITICALDMG_TIME = GetInt(0, 5000, 10, "CriticalDmg", "CriticalDmgTime", IAJuliaSkills);

	*(unsigned int*)MaxZen = GetInt(0, 2000000000, 2000000000, "MaximumZen", "MaxZenInBag", IAJuliaCommon);

	dword = GetInt(0, 2000000000, 1000000000, "MaximumZen", "MaxZenInVault", IAJuliaCommon);
	*(unsigned int*)MaxZen1 = dword;
	*(unsigned int*)MaxZen2 = dword;
	*(unsigned int*)MaxZen3 = dword;

	*(unsigned int *)GS_PARTYEXP_2_NORMAL = GetInt(0, 5000, 160, "PartyExp", "NormalParty2Exp", IAJuliaCommon);
	*(unsigned int *)GS_PARTYEXP_3_NORMAL = GetInt(0, 5000, 180, "PartyExp", "NormalParty3Exp", IAJuliaCommon);
	*(unsigned int *)GS_PARTYEXP_4_NORMAL = GetInt(0, 5000, 200, "PartyExp", "NormalParty4Exp", IAJuliaCommon);
	*(unsigned int *)GS_PARTYEXP_5_NORMAL = GetInt(0, 5000, 220, "PartyExp", "NormalParty5Exp", IAJuliaCommon);
	*(unsigned int *)GS_PARTYEXP_3_SET = GetInt(0, 5000, 230, "PartyExp", "SetParty3Exp", IAJuliaCommon);
	*(unsigned int *)GS_PARTYEXP_4_SET = GetInt(0, 5000, 270, "PartyExp", "SetParty4Exp", IAJuliaCommon);
	*(unsigned int *)GS_PARTYEXP_5_SET = GetInt(0, 5000, 300, "PartyExp", "SetParty5Exp", IAJuliaCommon);
#ifdef _GS
	*(unsigned int*) GS_DS_PARTYEXP_2 = GetInt(0,5000,160,"DevilSquare","DevilSquarePartyExp2Players",IAJuliaEvents);
	*(unsigned int*) GS_DS_PARTYEXP_3 = GetInt(0,5000,180,"DevilSquare","DevilSquarePartyExp3Players",IAJuliaEvents);
	*(unsigned int*) GS_DS_PARTYEXP_4 = GetInt(0,5000,200,"DevilSquare","DevilSquarePartyExp4Players",IAJuliaEvents);
	*(unsigned int*) GS_DS_PARTYEXP_5 = GetInt(0,5000,220,"DevilSquare","DevilSquarePartyExp5Players",IAJuliaEvents);
	*(unsigned int*) GS_DS_PARTYDIFFEXP_3 = GetInt(0,5000,230,"DevilSquare","DevilSquareSetPartyExp3Players",IAJuliaEvents);
	*(unsigned int*) GS_DS_PARTYDIFFEXP_4 = GetInt(0,5000,270,"DevilSquare","DevilSquareSetPartyExp4Players",IAJuliaEvents);
	*(unsigned int*) GS_DS_PARTYDIFFEXP_5 = GetInt(0,5000,300,"DevilSquare","DevilSquareSetPartyExp5Players",IAJuliaEvents);
#endif
#ifdef _GS_CS
	*(unsigned int*)GSCS_LOT_MAXPRICE = GetInt(0, 1000000000, 300000, "CastleSiege", "CSLandOfTrialMaxPayment", IAJuliaEvents);
	*(unsigned char*)GSCS_LORDMIX_MAXUSE = GetChar(0, 200, 1, "CastleSiege", "CSLordMixMaxUsePerDay", IAJuliaEvents);

	*(unsigned char*)GSCS_CRYWOLF_REWARD_ELF = GetChar(0, 15, 14, "CryWolf", "CrywolfAltarElfRewardGroupID", IAJuliaEvents) * 512 + GetChar(0, 255, 13, "CryWolf", "CrywolfAltarElfRewardIndexID", IAJuliaEvents);
	*(unsigned char*)GSCS_CRYWOLF_REWARD_TOP5 = GetChar(0, 15, 14, "CryWolf", "CrywolfTop5RewardGroupID", IAJuliaEvents) * 512 + GetChar(0, 255, 13, "CryWolf", "CrywolfTop5RewardIndexID", IAJuliaEvents);

	dword = GetInt(0, 1000000000, 200000000, "CastleSiege", "CSSeniorMaxCash", IAJuliaEvents);
	*(unsigned int*)GSCS_SENIOR_MAXZEN1 = dword;
	*(unsigned int*)GSCS_SENIOR_MAXZEN2 = dword;
#endif
}
void cConfigs::LoadFixes()
{
#ifdef _GS
	// Eldoradi event conf
	EldaradoEventType	= GetInt(0, 1, 0,"EldaradoEvent", "EldaradoEventType", IAJuliaEvents);

	// Other event conf
	CCAllowingPlayers	= GetInt(0, 2, 0,"ChaosCastle", "ChaosCastleAllowingPlayers", IAJuliaEvents);
	BCAllowingPlayers	= GetInt(0, 2, 0,"BloodCastle", "BloodCastleAllowingPlayers", IAJuliaEvents);
	BCEnterMasterType	= GetInt(0, 1, 0,"BloodCastle", "BloodCastleMasterEnterType", IAJuliaEvents);
	DSAllowingPlayers	= GetInt(0, 2, 0,"DevilSquare", "DevilSquareAllowingPlayers", IAJuliaEvents);
	FixDevilSquare		= GetInt(0, 1, 0,"DevilSquare", "FixDevilSquare", IAJuliaEvents);
	FixBloodCastle		= GetInt(0, 1, 0,"BloodCastle", "FixBloodCastle", IAJuliaEvents);
#endif
	UseChecksum			= GetInt(0, 1, 0, "CheckSum", "UseCheckSum", IAJuliaCommon);
	PersonalIDFix		= GetInt(0, 1, 1, "Bypasseres", "PersonalIDBypasser", IAJuliaCommon);
	GuildIDFix			= GetInt(0, 1, 1, "Bypasseres", "GuildIDBypasser", IAJuliaCommon);
	DisableLogs			= GetInt(0, 1, 0, "Logs","DisableLogs", IAJuliaCommon);

	AllowExeAnc			= GetInt(0, 1, 1, "SpecialItem", "AllowExeAnc", IAJuliaItems);
	AllowJohAnc			= GetInt(0, 1, 1, "SpecialItem", "AllowJohAnc", IAJuliaItems);
	AllowExeSock		= GetInt(0, 1, 1, "SpecialItem", "AllowExeSock", IAJuliaItems);
	MaxLifeOpt			= GetInt(0, 1, 1, "SpecialItem", "MaxLifeOpt", IAJuliaItems);
	CashShopExe			= GetInt(0, 1, 1, "SpecialItem", "CashShopExe", IAJuliaItems);

	CSSkillsOnNOrmal	= GetInt(0, 1, 1, "Skills", "CSSkillsOnNOrmal", IAJuliaSkills);
	Enable65kStats		= GetInt(0, 1, 0, "AddCommand", "Enable65kStats", IAJuliaCmd);
	DumpFile			= GetInt(0, 1, 0, "Dump", "EnableCrashDump", IAJuliaCommon);
	Disable380Opt		= GetInt(0, 1, 0, "380Opt", "DisablePowers", IACalcCharacter);
	DisableHarmonyOpt	= GetInt(0, 1, 0, "HarmonyOpt", "DisablePowers", IACalcCharacter);
	ClearPersonalShop	= GetInt(0, 1, 0, "Reset", "ClearPersonalShop", IAJuliaCommon);
}

void cConfigs::LoadCommands()
{
	/*
		COMANDO DROP
	*/
	Commands.IsDrop				= GetInt(0, 1, 1, "Drop", "DropEnabled", IAJuliaCmd);

	/*
		COMANDO RELOAD
	*/
	Commands.IsReload			= GetInt(0, 1, 1, "Reload", "ReloadEnabled", IAJuliaCmd);

	/*
		COMANDO GMOVE
	*/
	Commands.IsGmove			= GetInt(0, 1, 1, "Gmove", "GmoveEnabled", IAJuliaCmd);

	/*
		COMANDO SETPK
	*/
	Commands.IsSetPK			= GetInt(0, 1, 1, "SetPK", "SetPKEnabled", IAJuliaCmd);

	/*
		COMANDO GG
	*/
	Commands.IsGg				= GetInt(0, 1, 1, "GPost", "GgEnabled", IAJuliaCmd);

	/*
		COMANDO TIME
	*/
	Commands.IsTime				= GetInt(0, 1, 1, "Time", "TimeEnabled", IAJuliaCmd);

	/*
		COMANDO ONLINE
	*/
	Commands.IsOnline			= GetInt(0, 1, 1, "OnlineCommand", "OnlineEnabled", IAJuliaCmd);

	/*
		COMANDO STATUS
	*/
	Commands.IsStatus			= GetInt(0, 1, 1, "Status", "StatusEnabled", IAJuliaCmd);

	/*
		COMANDO SETCHAR
	*/
	Commands.IsSetChar			= GetInt(0, 1, 1, "SetChar", "SetCharEnabled", IAJuliaCmd);

	/*
		COMANDO SETZEN
	*/
	Commands.IsSetZen			= GetInt(0, 1, 1, "SetZen", "SetZenEnabled", IAJuliaCmd);

	/*
	COMANDO BAN
	*/
	Commands.IsBanPost			= GetInt(0, 1, 1, "Bans", "BanPostEnabled", IAJuliaCmd);
	Commands.IsBanChar			= GetInt(0, 1, 1, "Bans", "BanCharEnabled", IAJuliaCmd);
	Commands.IsBanAcc			= GetInt(0, 1, 1, "Bans", "BanAccEnabled", IAJuliaCmd);

	/*
		COMANDO SKIN
	*/
	Commands.SkinEnabled			= GetInt(0, 1, 1, "Skin", "SkinEnabled", IAJuliaCmd);

	/*
		COMANDO POST
	*/
	Commands.IsPost					= GetInt(0, 1, 1, "Post", "PostEnabled", IAJuliaCmd);
	Commands.PostLvl				= GetInt(0, Commands.MaxLvl, 1, "Post", "PostLevelReq", IAJuliaCmd);
	Commands.PostPriceZen			= GetInt(0, 2000000000, 10000, "Post", "PostPriceZen", IAJuliaCmd);
	Commands.PostPricePCPoint		= GetInt(0, PCPoint.Config.MaximumPCPoints, 0, "Post", "PostPricePcPoint", IAJuliaCmd);
	Commands.PostPriceWCoin			= GetInt(0, PCPoint.Config.MaximumWCPoints, 0, "Post", "PostPriceWCoin", IAJuliaCmd);
	Commands.PostPriceWebPoint		= GetInt(0, PCPoint.Config.MaximumWebPoints, 0, "Post", "PostPriceWebPoint", IAJuliaCmd);
	Commands.PostColor				= GetInt(1, 3, 1, "Post", "PostColor", IAJuliaCmd);
	Commands.PostDelay				= GetInt(0, 32767, 60, "Post", "PostDelay", IAJuliaCmd);

	/*
		COMANDO EVO
	*/
	Commands.EvoCommandEnabled		= GetInt(0,1,1,"Evo", "EvoEnabled", IAJuliaCmd);
	Commands.EvoLevelReq			= GetInt(220,Commands.MaxLvl,400,"Evo", "EvoLevelReq", IAJuliaCmd);
	Commands.EvoPriceZen			= GetInt(0,2000000000,10000,"Evo", "EvoPriceZen", IAJuliaCmd);
	Commands.EvoPricePcPoint		= GetInt(0,PCPoint.Config.MaximumPCPoints,0,"Evo", "EvoPricePcPoint", IAJuliaCmd);
	Commands.EvoPriceWCoin			= GetInt(0,PCPoint.Config.MaximumWCPoints,0,"Evo", "EvoPriceWCoin", IAJuliaCmd);
	Commands.EvoPriceWebPoint		= GetInt(0,PCPoint.Config.MaximumWebPoints,0,"Evo", "EvoPriceWebPoint", IAJuliaCmd);

	/*
		COMANDO ZEN
	*/
	Commands.ZenCommandEnabled      = GetInt(0,1,1,"Zen", "ZenEnabled", IAJuliaCmd);
	Commands.ZenLevelReq            = GetInt(1,Commands.MaxLvl,50,"Zen", "ZenLevelReq", IAJuliaCmd); 
	Commands.ZenPricePcPoint        = GetInt(0,PCPoint.Config.MaximumPCPoints,0,"Zen", "ZenPricePcPoint", IAJuliaCmd); 
	Commands.ZenPriceWCoin          = GetInt(0,PCPoint.Config.MaximumWCPoints,0,"Zen", "ZenPriceWCoin", IAJuliaCmd); 
	Commands.ZenPriceWebPoint       = GetInt(0,PCPoint.Config.MaximumWebPoints,0,"Zen", "ZenPriceWebPoint", IAJuliaCmd); 

	/*
		COMANDO CLEAR
	*/
	Commands.ClearCommandEnabled	= GetInt(0,1,1,"Clear", "ClearEnabled", IAJuliaCmd);
	Commands.ClearZenReq			= GetInt(0,2000000000,10000,"Clear", "ClearPriceZen", IAJuliaCmd);
	Commands.ClearLevelReq			= GetInt(1,Commands.MaxLvl,50,"Clear", "ClearLevelReq", IAJuliaCmd);
	Commands.ClearPricePcPoint		= GetInt(0,PCPoint.Config.MaximumPCPoints,0,"Clear", "ClearPricePcPoint", IAJuliaCmd); 
	Commands.ClearPriceWCoin		= GetInt(0,PCPoint.Config.MaximumWCPoints,0,"Clear", "ClearPriceWCoin", IAJuliaCmd); 
	Commands.ClearPriceWebPoint		= GetInt(0,PCPoint.Config.MaximumWebPoints,0,"Clear", "ClearPriceWebPoint", IAJuliaCmd);

	/*
		COMANDO ADD
	*/
	Commands.AddPointEnabled		= GetInt(0,1,1, "AddCommand", "AddPointEnabled", IAJuliaCmd);
	Commands.AddPointLevelReq		= GetInt(0,Commands.MaxLvl, 0, "AddCommand", "AddPointLevelReq", IAJuliaCmd);
	Commands.AddPriceZen			= GetInt(0,2000000000, 10000, "AddCommand", "AddPriceZen", IAJuliaCmd);
	Commands.AddPricePCPoint		= GetInt(0,PCPoint.Config.MaximumPCPoints, 0, "AddCommand", "AddPricePCPoint", IAJuliaCmd);
	Commands.AddPriceWCoin			= GetInt(0,PCPoint.Config.MaximumWCPoints, 0, "AddCommand", "AddPriceWCoin", IAJuliaCmd);
	Commands.AddPriceWebPoints		= GetInt(0,PCPoint.Config.MaximumWebPoints, 0, "AddCommand", "AddPriceWebPoints", IAJuliaCmd);
	Commands.MaxAddedStats			= GetInt(0,(Configs.Enable65kStats = 1) ? 65000 : 32000, 0, "AddCommand", "MaxAddedStats", IAJuliaCmd);
	Commands.AddPointEffect			= GetInt(0,1,1,"AddCommand","AddPointEffect",IAJuliaCmd);

	/*
		COMANDO WARE
	*/
	Commands.IsMultyVault			= GetInt(0, 1, 1, "MultyVault", "IsMultyVault", IAJuliaCmd);
	Commands.NumberOfVaults			= GetInt(2, 99, 3, "MultyVault", "NumberOfVaults", IAJuliaCmd);
	Commands.ZenForChange			= GetInt(0, 2000000000, 10000, "MultyVault", "ZenForChange", IAJuliaCmd);
	Commands.PcPointForChange		= GetInt(0, PCPoint.Config.MaximumPCPoints, 0, "MultyVault", "PcPointForChange", IAJuliaCmd);
	Commands.WCoinForChange			= GetInt(0, PCPoint.Config.MaximumWCPoints, 0, "MultyVault", "WCoinForChange", IAJuliaCmd);
	Commands.WebPointsForChange		= GetInt(0, PCPoint.Config.MaximumWebPoints, 0, "MultyVault", "WebPointsForChange", IAJuliaCmd);
#ifdef _GS

	/*
		COMANDO OFFTRADE
	*/
	OfflineTrade.Configs.Enabled		= GetInt(0, 1, 1, "OffTrade", "OffTradeEnabled", IAJuliaCmd);
	OfflineTrade.Configs.LevelReq		= GetInt(0, Commands.MaxLvl, 0,	"OffTrade",	"OffTradeLevelReq",	IAJuliaCmd);
	OfflineTrade.Configs.PriceZen 		= GetInt(0, 2000000000,	10000, "OffTrade",	"OffTradeZen", IAJuliaCmd);
#endif

	/*
		COMANDO EXCHANGE
	*/
	Commands.ExchangeCommands = GetInt(0, 1, 1, "ExchangeCommands", "ExchangeCommands", IAJuliaPcPoints);
	Commands.ExchangeWcPp = GetInt(0, 1, 1, "ExchangeCommands", "WcPpCmdEnabled", IAJuliaPcPoints);
	Commands.ExchangeWcWp = GetInt(0, 1, 1, "ExchangeCommands", "WcWpCmdEnabled", IAJuliaPcPoints);
	Commands.ExchangeWcZen = GetInt(0, 1, 1, "ExchangeCommands", "WcZenCmdEnabled", IAJuliaPcPoints);
	Commands.ExchangeWpPp = GetInt(0, 1, 1, "ExchangeCommands", "WpPpCmdEnabled", IAJuliaPcPoints);
	Commands.ExchangeWpWc = GetInt(0, 1, 1, "ExchangeCommands", "WpWcCmdEnabled", IAJuliaPcPoints);
	Commands.ExchangeWpZen = GetInt(0, 1, 1, "ExchangeCommands", "WpZenCmdEnabled", IAJuliaPcPoints);
	Commands.ExchangePpZen = GetInt(0, 1, 1, "ExchangeCommands", "PpZenCmdEnabled", IAJuliaPcPoints);
	Commands.ExchangePpWc = GetInt(0, 1, 1, "ExchangeCommands", "PpWcCmdEnabled", IAJuliaPcPoints);
	Commands.ExchangePpWp = GetInt(0, 1, 1, "ExchangeCommands", "PpWpCmdEnabled", IAJuliaPcPoints);
	Commands.ExchangeZenWc = GetInt(0, 1, 1, "ExchangeCommands", "ZenWcCmdEnabled", IAJuliaPcPoints);
	Commands.ExchangeZenWp = GetInt(0, 1, 1, "ExchangeCommands", "ZenWpCmdEnabled", IAJuliaPcPoints);
	Commands.ExchangeZenPp = GetInt(0, 1, 1, "ExchangeCommands", "ZenPpCmdEnabled", IAJuliaPcPoints);

	Commands.ExchangeMinLvl = GetInt(0, 400, 350, "ExchangeCommands", "ExchangeMinLvl", IAJuliaPcPoints);
	Commands.ExchangeTax = GetInt(0, 100, 2, "ExchangeCommands", "ExchangeTax", IAJuliaPcPoints);
	Commands.WCoin_PcPoint = GetInt(0, 32767, 100, "ExchangeCommands", "WCoin_PcPoint", IAJuliaPcPoints);
	Commands.WCoin_WebPoint = GetInt(0, 32767, 10, "ExchangeCommands", "WCoin_WebPoint", IAJuliaPcPoints);
	Commands.WCoin_Zen = GetInt(0, 2000000000, 10000000, "ExchangeCommands", "WCoin_Zen", IAJuliaPcPoints);
	Commands.WebPoint_PcPoint = GetInt(0, 32767, 10, "ExchangeCommands", "WebPoint_PcPoint", IAJuliaPcPoints);
	Commands.WebPoint_Zen = GetInt(0, 2000000000, 1000000, "ExchangeCommands", "WebPoint_Zen", IAJuliaPcPoints);
	Commands.PcPoint_Zen = GetInt(0, 2000000000, 100000, "ExchangeCommands", "PcPoint_Zen", IAJuliaPcPoints);
}

void cConfigs::Misc()
{
	/*
		OUTRAS CONFIGURACOES 
	*/
	GetPrivateProfileString("Reset", "ResetColumn", "Resets", ResetSystem.RConf.ResetColumn, sizeof(ResetSystem.RConf.ResetColumn), IAJuliaCommon);
	MuOnlineQuery.CheckColumn(ResetSystem.RConf.ResetColumn, "Character", "ALTER TABLE Character ADD [%s][int] DEFAULT (0) NOT NULL", ResetSystem.RConf.ResetColumn);
	GetPrivateProfileString("GameServerInfo", "ServerName", "GS", Configs.ServerName, sizeof(Configs.ServerName), ".\\Data\\ServerInfo.dat");
	IsPartyGap = GetInt(0, 1, 1, "PartyGap", "IsPartyGap", IAJuliaCommon);
	PartyGapLvl = GetInt(0, 400, 120, "PartyGap", "PartyGapLvl", IAJuliaCommon);
	GuildRes = GetInt(0, 32767, 5, "GuildMaster", "GuildCreateReset", IAJuliaCommon);
	Unicode32 = GetInt(0, 1, 0, "CharacterGuild", "AllowUnicode32", IAJuliaCommon);
	GuildLevel = GetInt(0, 400, 320, "GameServerInfo", "GuildCreateLevel", "..\\Data\\CommonServer.cfg");
}

long cConfigs::GetInt(long Min, long Max, long Default, LPCSTR BlockName, LPCSTR ConfigName, LPCSTR FolderName)
{
	long lResult;

	WIN32_FIND_DATAA wfd;

	if(FindFirstFileA(FolderName, &wfd) == INVALID_HANDLE_VALUE)
	{
		Log.ConsoleOutPut(1, c_BoldRed, t_Error, "[X] Error configs in %s!", FolderName);
		Log.ConsoleOutPut(1, c_BoldRed, t_Error, "[X] Can't find file!");
		Log.ConsoleOutPut(1, c_BoldRed, t_Error, "[X] Taked default value for %s(%ld)", ConfigName, Default);

		lResult = Default;
	}
	else
	{
		lResult = GetPrivateProfileInt(BlockName,ConfigName,-100500,FolderName);
	}

	if(lResult == -100500)
	{
		Log.ConsoleOutPut(1, c_BoldRed, t_Error, "[X] Error configs in %s!", FolderName);
		Log.ConsoleOutPut(1, c_BoldRed, t_Error, "[X] Can't find '%s' in [%s] section!", ConfigName, BlockName);
		Log.ConsoleOutPut(1, c_BoldRed, t_Error, "[X] Taked default value for %s(%ld)", ConfigName, Default);

		lResult = Default;
	}

	if(lResult < Min || lResult > Max)
	{
		Log.ConsoleOutPut(1, c_BoldRed, t_Error, "[X] Error configs in %s!", FolderName);
		Log.ConsoleOutPut(1, c_BoldRed, t_Error, "%s(%d) in [%s] is out of range!", ConfigName, lResult, BlockName);
		Log.ConsoleOutPut(1, c_BoldRed, t_Error, "[X] Min = %ld Max = %ld\tTaked default value(%ld)", Min, Max, Default);

		lResult = Default;
	}

	return lResult;
}

char cConfigs::GetChar(long Min, long Max, unsigned char Default, LPCSTR BlockName, LPCSTR ConfigName, LPCSTR FolderName)
{
	unsigned char cResult;

	WIN32_FIND_DATAA wfd;

	if(FindFirstFileA(FolderName, &wfd) == INVALID_HANDLE_VALUE)
	{
		Log.ConsoleOutPut(1, c_BoldRed, t_Error, "[X] Error configs in %s!", FolderName);
		Log.ConsoleOutPut(1, c_BoldRed, t_Error, "[X] Can't find file!");
		Log.ConsoleOutPut(1, c_BoldRed, t_Error, "[X] taked default value for %s(%ld)", ConfigName, Default);

		cResult = Default;
	}
	else
	{
		cResult = GetPrivateProfileInt(BlockName,ConfigName,-100500,FolderName);
	}

	if(cResult == -100500)
	{	   
		Log.ConsoleOutPut(1, c_BoldRed, t_Error, "[X] Error configs in %s!", FolderName);
		Log.ConsoleOutPut(1, c_BoldRed, t_Error, "[X] Can't find '%s' in [%s] section!", ConfigName, BlockName);
		Log.ConsoleOutPut(1, c_BoldRed, t_Error, "[X] Taked default value for %s(%ld)", ConfigName, Default);

		cResult = Default;
	}

	if(cResult < Min || cResult > Max)
	{
		Log.ConsoleOutPut(1, c_BoldRed, t_Error, "[X] Error configs in %s!", FolderName);
		Log.ConsoleOutPut(1, c_BoldRed, t_Error, "[X] %s(%d) in [%s] is out of range!", ConfigName, cResult, BlockName);
		Log.ConsoleOutPut(1, c_BoldRed, t_Error, "[X] Min = %ld Max = %ld\tTaked default value(%ld)", Min, Max, Default);

		cResult = Default;
	} 

	return cResult;
}