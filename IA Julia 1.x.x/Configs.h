#ifndef CONFIGS_H
#define CONFIGS_H

#include "StdAfx.h"

class cConfigs
{
	private:
		void LoadNotice();
		void LoadPets();
		void LoadCommands();
		void ZenFixes();
		void MaxStats();
		void Misc();

	public:
		void LoadFixes();
		void LoadConfigsInGS();
		void LoadAll();

		long GetInt(long Min, long Max, long Default, LPCSTR BlockName, LPCSTR ConfigName, LPCSTR FolderName);
		char GetChar(long Min, long Max, unsigned char Default, LPCSTR BlockName, LPCSTR ConfigName, LPCSTR FolderName);

	#ifdef _GS
		int EldaradoEventType;
		int CCAllowingPlayers;
		int BCAllowingPlayers;
		int BCEnterMasterType;
		int DSAllowingPlayers;
		int FixDevilSquare;
		int FixBloodCastle;
	#endif

		int SQLVersion;
		int UseChecksum;
		int PersonalIDFix;
		int GuildIDFix;
		int DisableLogs;
		int AllowExeAnc;
		int AllowJohAnc;
		int AllowExeSock;
		int CashShopExe;
		int DisableHarmonyOpt;
		int Disable380Opt;
		int MaxLifeOpt;
		int MaxItemLevel;
		int CSSkillsOnNOrmal;
		int Enable65kStats;
		int DumpFile;

		int MaxStatsSystemEnable;
		int MaxDL_Strength ;
		int MaxDL_Agility;
		int MaxDL_Vitality;
		int MaxDL_Energy ;
		int MaxDL_Command;

		int MaxDK_Strength;
		int MaxDK_Agility;
		int MaxDK_Vitality ;
		int MaxDK_Energy ;

		int MaxDW_Strength ;
		int MaxDW_Agility;
		int MaxDW_Vitality;
		int MaxDW_Energy ;

		int MaxELF_Strength ;
		int MaxELF_Agility ;
		int MaxELF_Vitality ;
		int MaxELF_Energy;

		int MaxSUM_Strength;
		int MaxSUM_Agility ;
		int MaxSUM_Vitality;
		int MaxSUM_Energy;

		int MaxMG_Strength ;
		int MaxMG_Agility ;
		int MaxMG_Vitality ;
		int MaxMG_Energy;

		char ServerName[25];
		char ConnectNotice[100];
		int ConnectInfo;
		int ClearPersonalShop;

		struct sCommands
		{
			int MaxLvl;
			int IsGg;
			int IsPost;

			int PostLvl;
			int MaxAddedStats;
			int MaxAddedStatsWithoutTimer;
			int NumberOfAddedStatsInSec;
			int PostPriceZen;
			int PostPricePCPoint;
			int PostPriceWCoin;
			int PostPriceWebPoint;
			int PostColor;
			time_t PostDelay;

			int IsBanPost;
			int IsBanAcc;
			int IsBanChar;
			int IsDrop;
			int IsReload;
			int IsGmove;
			int IsSetPK;
			int IsTime;
			int IsOnline;
			int IsZenDrop;
			int IsStatus;
			int IsSetChar;
			int IsSetZen;

			int SkinEnabled;

			int IsMultyVault;
			int NumberOfVaults;
			DWORD ZenForChange;
			int PcPointForChange;
			int WCoinForChange;
			int WebPointsForChange;

			int ExchangeCommands;
			int	ExchangeWcPp;
			int ExchangeWcWp;
			int	ExchangeWcZen;
			int ExchangeWpWc;
			int ExchangeWpPp;
			int ExchangeWpZen;
			int	ExchangePpZen;
			int	ExchangePpWc;
			int ExchangePpWp;
			int	ExchangeZenWc;
			int	ExchangeZenPp;
			int ExchangeZenWp;

			int ExchangeMinLvl;
			int ExchangeTax;

			int WCoin_WebPoint;
			int WCoin_PcPoint;
			DWORD WCoin_Zen;
			int WebPoint_PcPoint;
			DWORD WebPoint_Zen;
			DWORD PcPoint_Zen;

			int AddPointEnabled;
			int AddPointLevelReq;
			DWORD AddPriceZen;
			int AddPricePCPoint;
			int AddPriceWCoin;
			int AddPriceWebPoints;
			int	AddPointEffect;

			int EvoCommandEnabled;
			int EvoLevelReq;
			DWORD EvoPriceZen;
			int EvoPricePcPoint;
			int EvoPriceWCoin;
			int EvoPriceWebPoint;

			int ZenCommandEnabled;
			int ZenLevelReq;
			int ZenPricePcPoint;
			int ZenPriceWCoin;
			int ZenPriceWebPoint;

			int ClearCommandEnabled;
			int ClearZenReq;
			int ClearLevelReq;
			int ClearPricePcPoint;
			int ClearPriceWCoin;
			int ClearPriceWebPoint;
		} Commands;

		struct cZen
		{
			int	NormalZen;
			int ZenInParty;

		} Zen;

		int GuildRes;
		int GuildLevel;
		int IsPartyGap;
		int PartyGapLvl;
		int Unicode32;

		struct sPanda
		{
			int PetPandaDefense;
			int PetPandaAttackDamageMinLeft;
			int PetPandaAttackDamageMaxLeft;
			int PetPandaAttackDamageMinRight;
			int PetPandaAttackDamageMaxRight;
			int PetPandaMagicDamageMin;
			int PetPandaMagicDamageMax;
			int PetPandaMagicSpeed;
			int PetPandaAttackSpeed;
			int PetPandaExpirence;

			int PandaRingDefense;
			int PandaRingAttackDamageMinLeft;
			int PandaRingAttackDamageMaxLeft;
			int PandaRingAttackDamageMinRight;
			int PandaRingAttackDamageMaxRight;
			int PandaRingMagicDamageMin;
			int PandaRingMagicDamageMax;
			int PandaRingMagicSpeed;
			int PandaRingAttackSpeed;
			int PandaRingExpirence;
		} Panda;
};

extern cConfigs Configs;

#endif