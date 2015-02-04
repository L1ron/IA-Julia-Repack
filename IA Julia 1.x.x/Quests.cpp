#include "StdAfx.h"
#include "Configs.h"
#include "Query.h"
#include "Quests.h"
#include "Prodef.h"
#include "User.h"
#include "Utilits.h"
#include "PCPoint.h"
#include "Monster.h"
#include "ChatCommands.h"

cQuests Quests;
sQuetsItens QuestsItens[MaxItensQuest];
sQuestsItenReward QuestsItenReward[MaxItensQuest];

void cQuests::Load()
{
	Config.Enable = Configs.GetInt(0,1,1,"Quests","Enable",IAJuliaQuests);

	if(Config.Enable)
	{
		MuOnlineQuery.CheckColumn("QuestState","Character","ALTER TABLE Character ADD [QuestState][int] DEFAULT (0) NOT NULL");
		MuOnlineQuery.CheckColumn("QuestNumber","Character","ALTER TABLE Character ADD [QuestNumber][int] DEFAULT (0) NOT NULL");
		MuOnlineQuery.CheckColumn("QuestMobCount","Character","ALTER TABLE Character ADD [QuestMobCount][int] DEFAULT (0) NOT NULL");

		Config.QuestNPCID = Configs.GetInt(0,500,371,"Quests","QuestNPCID",IAJuliaQuests);
		GetPrivateProfileString("Quests", "QuestsName", "Quest System", Config.QuestName, sizeof(Config.QuestName), IAJuliaQuests);

		FILE *File;
		File = fopen(IAJuliaQuests,"r");

		if(File == NULL)
		{
			Log.ConsoleOutPut(0,c_Red,t_QUEST,"[û] [%s]\t%s nao encontrado, Quests inativas.",Config.QuestName,IAJuliaQuests);

			Config.Enable = 0;
		}
		else
		{
			int Flag = 0,Missions = 0;
			char zBuffer[1024];

			while(!feof(File))
			{
				fgets(zBuffer,1024,File);

				if(Utilits.IsBadFileLine(zBuffer,Flag) || !strncmp(zBuffer,"//",2) || !strncmp(zBuffer,"end",3) || (zBuffer[0] == 0xA))
				{
					continue;
				}

				switch(Flag)
				{
					case 1:
					{
						sscanf_s(zBuffer,"%d %d %d %d \"%[^\"]s",&Mob,&Amount,&AwardID,&AwardAmount,&MobName);

						QuestsItens[this->Missions].Mob			= this->Mob;
						QuestsItens[this->Missions].Amount		= this->Amount;
						QuestsItens[this->Missions].AwardID		= this->AwardID;
						QuestsItens[this->Missions].AwardAmount	= this->AwardAmount;
					
						strcpy_s(QuestsItens[this->Missions].MobName,MobName);

						this->Missions++;
					}
					case 2:
					{
						sscanf(zBuffer,"%d %d %d %d %d %d %d %d",&Type,&Index,&Level,&Duration,&Luck,&Skill,&Option,&Excellent);

						QuestsItenReward[Itens].Type		= this->Type;
						QuestsItenReward[Itens].Index		= this->Index;
						QuestsItenReward[Itens].Level		= this->Level;
						QuestsItenReward[Itens].Duration	= this->Duration;
						QuestsItenReward[Itens].Luck		= this->Luck;
						QuestsItenReward[Itens].Skill		= this->Skill;
						QuestsItenReward[Itens].Option		= this->Option;
						QuestsItenReward[Itens].Excellent	= this->Excellent;

						this->Itens++;
					}
				}
			}

			fclose(File);

			Log.ConsoleOutPut(1,c_Yellow,t_QUEST,"[û] [%s]\t%d missoes foram carregadas.",Config.QuestName,this->Missions);
		}
	}
}

void cQuests::Connect(LPOBJ gObj)
{
	if(Config.Enable)
	{
		AddTab[gObj->m_Index].QUEST_State = 0;
		AddTab[gObj->m_Index].QUEST_Number = 0;
		AddTab[gObj->m_Index].QUEST_MobCount= 0;

		MuOnlineQuery.ExecQuery("SELECT QuestState, QuestNumber, QuestMobCount FROM Character WHERE AccountID = '%s'",gObj->AccountID);
		MuOnlineQuery.Fetch();
		AddTab[gObj->m_Index].QUEST_State		= MuOnlineQuery.GetAsInteger("QuestState");
		AddTab[gObj->m_Index].QUEST_Number		= MuOnlineQuery.GetAsInteger("QuestNumber");
		AddTab[gObj->m_Index].QUEST_MobCount	= MuOnlineQuery.GetAsInteger("QuestMobCount");
		MuOnlineQuery.Close();
	}
}

void cQuests::QuestNPCClick(LPOBJ gObj, LPOBJ gObjNPC)
{
	if(Config.Enable)
	{
		switch(AddTab[gObj->m_Index].QUEST_State)
		{
			case 0: // 0 = None
			{
				AddTab[gObj->m_Index].QUEST_State = 1;
				AddTab[gObj->m_Index].QUEST_MobCount = 0;
				
				int MobsNeeded = QuestsItens[AddTab[gObj->m_Index].QUEST_Number].Amount;

				Chat.MessageLog
				(
					1,
					c_Blue,
					t_QUEST,
					gObj,
					"[%s] Missao: Eliminar %d %s%s",
					Config.QuestName,
					MobsNeeded,
					QuestsItens[AddTab[gObj->m_Index].QUEST_Number].MobName,
					(MobsNeeded > 1) ? "s" : ""
				);

				break;
			}
			case 1: // Pending
			{
				int MobsNeeded = QuestsItens[AddTab[gObj->m_Index].QUEST_Number].Amount;

				if(AddTab[gObj->m_Index].QUEST_MobCount == MobsNeeded)
				{
					AddTab[gObj->m_Index].QUEST_MobCount = 0;

					if(AddTab[gObj->m_Index].QUEST_Number < this->Missions)
					{
						int iAward = QuestsItens[AddTab[gObj->m_Index].QUEST_Number].AwardID;

						Chat.MessageLog
						(
							1,
							c_Blue,
							t_QUEST,
							gObj,
							"[%s] Pegue a recompensa: %d %s.",
							Config.QuestName,
							QuestsItens[AddTab[gObj->m_Index].QUEST_Number].AwardAmount,
							GetQuestReward(iAward),
							(MobsNeeded > 1) ? "s" : ""
						);
						
						GenerateAward(gObj,iAward,QuestsItens[AddTab[gObj->m_Index].QUEST_Number].AwardAmount);
						AddTab[gObj->m_Index].QUEST_Number++; // After Generate item please :D
					}
					else
					{
						AddTab[gObj->m_Index].QUEST_State = 2;

						Monster.NPCMessageLog(c_Blue,t_QUEST,gObj,gObjNPC,"Parabens! Voce completou todas as missoes!");
					}

					MuOnlineQuery.ExecQuery
					(
						"UPDATE Character SET QuestState = %d, QuestNumber = %d, QuestMobCount = %d WHERE AccountID = '%s'",
						AddTab[gObj->m_Index].QUEST_State,
						AddTab[gObj->m_Index].QUEST_Number,
						AddTab[gObj->m_Index].QUEST_MobCount,
						gObj->AccountID
					);

					MuOnlineQuery.Fetch();
					MuOnlineQuery.Close();
				}
				else if(AddTab[gObj->m_Index].QUEST_MobCount < MobsNeeded)
				{
					Chat.MessageLog
					(
						1,
						c_Blue,
						t_QUEST,
						gObj,
						"[%s] Elimine %d %s%s e depois apresente-se!",
						Config.QuestName,
						MobsNeeded,
						QuestsItens[AddTab[gObj->m_Index].QUEST_Number].MobName,
						(MobsNeeded > 1) ? "s" : ""
					);
				}

				break;
			}
			default: // Quests complete
			{
				Monster.NPCMessageLog(c_Blue,t_QUEST,gObj,gObjNPC,"Você já serviu aos guardiões de Mu.");

				break;
			}
		}
	}
	else
	{
		Monster.NPCMessageLog(c_Blue,t_QUEST,gObj,gObjNPC,"Nao estou de servico, volte mais tarde.");
	}
}

void cQuests::QuestMobDrop(LPOBJ pObj,LPOBJ mObj)
{
	if(AddTab[pObj->m_Index].QUEST_State == 1)
	{
		if
		(
			(AddTab[pObj->m_Index].QUEST_MobCount < QuestsItens[AddTab[pObj->m_Index].QUEST_Number].Amount) &&
			(mObj->Class == QuestsItens[AddTab[pObj->m_Index].QUEST_Number].Mob)
		)
		{
			AddTab[pObj->m_Index].QUEST_MobCount++;

			Chat.MessageLog
			(
				1,
				c_Green,
				t_QUEST,
				pObj,
				"[%s] Matou %d de %d %s!",
				Config.QuestName,
				AddTab[pObj->m_Index].QUEST_MobCount,
				QuestsItens[AddTab[pObj->m_Index].QUEST_Number].Amount,
				mObj->Name
			);
		}
	}
}

char* cQuests::GetQuestReward(int AwardID)
{
	switch(AwardID)
	{
		case 1:
		{
			return "Zens";

			break;
		}
		case 2:
		{
			return "Free Points";

			break;
		}
		case 3:
		{
			return "Item";

			break;
		}
		case 4:
		{
			return "PCPoints";

			break;
		}
		case 5:
		{
			return "WCoins";

			break;
		}
		default:
		{
			return "None";

			break;
		}
	}
}

void cQuests::GenerateAward(LPOBJ gObj,int AwardID,int Amount)
{
	switch(AwardID)
	{
		case 1: // Zen (Broken)
		{
			if(!((gObj->Money + Amount) >= 2000000000) && !(gObj->Money < 0) && !(Amount >= 2000000000))
			{
				gObj->Money += Amount;
				GCMoneySend(gObj->m_Index,gObj->Money);
			}

			break;
		}
		case 2: // Free Point (Fixed?)
		{
			gObj->LevelUpPoint += Amount;
			GCLevelUpMsgSend(gObj->m_Index,0);

			break;
		}
		case 3: // Item
		{
			int i = rand() % this->Itens;

			int exelent;
			int exelentrand;

			exelent = QuestsItenReward[i].Excellent;

			if(exelent == 0)
			{
				exelentrand = 0;
			}
			else
			{
				exelentrand = rand() % exelent;
			}

			DWORD Premio = QuestsItenReward[i].Type*512+QuestsItenReward[i].Index;

			ItemSerialCreateSend
			(
				gObj->m_Index,
				gObj->MapNumber,
				(BYTE)gObj->X,
				(BYTE)gObj->Y,
				Premio,
				QuestsItenReward[i].Level,
				QuestsItenReward[i].Duration,
				QuestsItenReward[i].Luck,
				QuestsItenReward[i].Skill,
				QuestsItenReward[i].Option,
				gObj->m_Index,
				exelentrand,
				0
			);

			break;
		}
		case 4: // PcPoint
		{
			PCPoint.UpdatePoints(gObj,Amount,PLUS,PCPOINT);

			break;
		}
		case 5: // wCoin
		{
			PCPoint.UpdatePoints(gObj,Amount,PLUS,WCOIN);

			break;
		}
	}
}