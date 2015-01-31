#ifndef QUESTS_H
#define QUESTS_H

#include "StdAfx.h"
#include "User.h"

class cQuests
{
	public:
		void Load();
        void Connect(LPOBJ gObj);

		void QuestNPCClick(LPOBJ gObj, LPOBJ gObjNPC);
		void QuestMobDrop(LPOBJ pObj,LPOBJ mObj);
		char* GetQuestReward(int AwardID);
		void GenerateAward(LPOBJ gObj,int AwardID,int Amount);

		struct
		{
			int Enable;
			int QuestNPCID;
			char QuestName[32];
		} Config;

		int Missions;
	    int Mob,Amount,AwardID,AwardAmount;
		char MobName[32];

        int Itens;
		int Type,Index,Level,Option,Luck,Skill,Duration,Excellent;
};

extern cQuests Quests;

#define MaxNumQuests	100
#define MaxItensQuest	100

struct sQuetsItens
{
	int Mob;
	int Amount;
	int AwardID;
	int AwardAmount;
	
	char MobName[64];
};

struct sQuestsItenReward
{
	int Type;
	int Index;
	int Level;
	int Option;
	int Luck;
	int Skill;
	int Duration;
	int Excellent;
};

#endif