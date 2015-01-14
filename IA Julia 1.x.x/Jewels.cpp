// ================================================== //
// #			GameServer 1.00.90					# //
// #			Imagination Arts					# //
// #			Julia Project 1.1.x					# //
// ================================================== //
// #	http://imaginationarts.net/forum/			# //
// #	http://mu.raklion.ru/						# //
// ================================================== //

#include "Jewels.h"
#include "Stdafx.h"
#include "ChatCommands.h"
#include "Prodef.h"
#include "Utilits.h"

cJewels Jewels;

void cJewels::ResetConfig()
{
    AmountJewel = 0;
    for(int i=0; i<255; i++)
    {
        ArrayJewelConf[i].id			= 0;
        ArrayJewelConf[i].rate			= 0;
        ArrayJewelConf[i].opt1			= 0;
        ArrayJewelConf[i].opt2			= 0;
        ArrayJewelConf[i].minopt1		= 0;
        ArrayJewelConf[i].minopt2		= 0;
        ArrayJewelConf[i].maxopt1		= 0;
        ArrayJewelConf[i].maxopt2		= 0;
        ArrayJewelConf[i].fail1			= 0;
        ArrayJewelConf[i].fail2			= 0;
        ArrayJewelConf[i].failopt1		= 0;
        ArrayJewelConf[i].failopt2		= 0;
        ArrayJewelConf[i].successfully1	= 0;
        ArrayJewelConf[i].successfully2	= 0;
    }
}

void cJewels::Load()
{
    ResetConfig();

    char Buff[256];
    int Flag = 0;
    int i = 0;

    FILE *conf = fopen(IAJuliaJewelSystem,"r");

    if(conf == NULL)
    {
        Log.ConsoleOutPut(1, c_Cyan, t_Default, "[X] Jewels System not active. Config file not found: %s", IAJuliaJewelSystem);
        return;
    }

    while ( !feof(conf))
    {
        fgets(Buff,256,conf);

        if(Utilits.IsBadFileLine(Buff, Flag))
            continue;

        if (Flag == 1)
        {
            int n[14];
            sscanf(Buff,"%d %d %d %d %d %d %d %d %d %d %d %d %d %d", &n[0], &n[1], &n[2], &n[3], &n[4], &n[5], &n[6], &n[7], &n[8], &n[9], &n[10], &n[11], &n[12], &n[13]);
            ArrayJewelConf[i].id			= n[0];
            ArrayJewelConf[i].rate			= n[1];
            ArrayJewelConf[i].opt1			= n[2];
            ArrayJewelConf[i].opt2			= n[3];
            ArrayJewelConf[i].minopt1		= n[4];
            ArrayJewelConf[i].minopt2		= n[5];
            ArrayJewelConf[i].maxopt1		= n[6];
            ArrayJewelConf[i].maxopt2		= n[7];
            ArrayJewelConf[i].fail1			= n[8];
            ArrayJewelConf[i].fail2			= n[9];
            ArrayJewelConf[i].failopt1		= n[10];
            ArrayJewelConf[i].failopt2		= n[11];
            ArrayJewelConf[i].successfully1	= n[12];
            ArrayJewelConf[i].successfully2	= n[13];
            i++;
        }
    }

    fclose(conf);
    AmountJewel = i;
    Log.ConsoleOutPut(1, c_Magenta, t_Default, "[ы] [JewelsSystem]\tLoaded %d jewels.", AmountJewel+1);
}

void cJewels::IdentifyJewel(PMSG_USE_ITEM_RECV * lpmsg, int aIndex)
{
    OBJECTSTRUCT * gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);
    CItem* lpItem = &gObj->pInventory[lpmsg->SourceSlot];
    CItem* ProtochItem = &gObj->pInventory[lpmsg->TargetSlot];

    for (int i=0; i<AmountJewel; i++)
    {
        if (lpItem->m_Type == ITEMGET(14,ArrayJewelConf[i].id))
        {
            if (Verification(ArrayJewelConf[i].opt1,ArrayJewelConf[i].opt2,ArrayJewelConf[i].minopt1,ArrayJewelConf[i].minopt2,
                             ArrayJewelConf[i].maxopt1,ArrayJewelConf[i].maxopt2,ArrayJewelConf[i].successfully1,ArrayJewelConf[i].successfully2,
                             ProtochItem))
            {
                RATE = rand()%100+1;
                if (RATE <= ArrayJewelConf[i].rate)
                {
                    Chat.Message(1,gObj,"[Jewel] Congratulation, Item Update is Successfully");
                    this->Successfully(ArrayJewelConf[i].opt1,ArrayJewelConf[i].opt2,ArrayJewelConf[i].maxopt1,ArrayJewelConf[i].maxopt2,
                                       ArrayJewelConf[i].successfully1,ArrayJewelConf[i].successfully2,ProtochItem);
                    this->DeleteItem(aIndex,lpmsg->SourceSlot);
                    GCInventoryItemOneSend(aIndex, lpmsg->TargetSlot);
                }
                else
                {
                    Chat.Message(1,gObj,"[Jewel] Sorry, Item Update is Fail");
                    this->Fail(ArrayJewelConf[i].opt1,ArrayJewelConf[i].opt2,ArrayJewelConf[i].fail1,ArrayJewelConf[i].fail2,
                               ArrayJewelConf[i].failopt1,ArrayJewelConf[i].failopt2,ProtochItem);
                    this->DeleteItem(aIndex,lpmsg->SourceSlot);
                    GCInventoryItemOneSend(aIndex, lpmsg->TargetSlot);
                }
            }
            else
            {
                Chat.Message(1,gObj,"[Jewel] Sorry, you can`t not use jewel on this item");
            }
        }
    }
}

bool cJewels::Verification(int Opt1, int Opt2,int MinOpt1, int MinOpt2, int MaxOpt1 , int MaxOpt2, int Success1, int Success2, CItem* ProtochItem)
{
    // Add Item Option
    if (Opt1 == 1 || Opt2 == 1)
    {
        if (Opt1 == 1 )
        {
            if (ProtochItem->m_Level + Success1 <= MaxOpt1 && ProtochItem->m_Level >= MinOpt1) return true;
            else return false;
        }
        if (Opt2 == 1)
        {
            if (ProtochItem->m_Level + Success2 <= MaxOpt2&& ProtochItem->m_Level >= MinOpt2) return true;
            else return false;
        }
    }
    // Luck Add
    if (Opt1 == 2 || Opt2 == 2)
    {
        if (ProtochItem->m_Option2 != 1)	return true;
        else return false;
    }
    // Skill Add
    if (Opt1 == 3 || Opt2 == 3)
    {
        if (ProtochItem->m_Type > ITEMGET(6,0)) return false;
        if (ProtochItem->m_Option1 != 1)	return true;
        else return false;
    }
    // Add Option
    if (Opt1 == 4 || Opt2 == 4)
    {
        if (Opt1 == 4 )
        {
            if (ProtochItem->m_Option3 + Success1 <= MaxOpt1 && ProtochItem->m_Option3 >= MinOpt1)	return true;
            else return false;
        }
        if (Opt2 == 4)
        {
            if (ProtochItem->m_Option3 + Success2 <= MaxOpt2 && ProtochItem->m_Option3 >= MinOpt2)	return true;
            else return false;
        }
    }
    // Excellent Opt
    if (Opt1 == 5 || Opt2 == 5)
    {
        if (ProtochItem->m_Type >= ITEMGET(12,0)) return false;
        int addexc;
        if (Opt1 == 5 )
        {
            addexc = this->AddExcOpt(ProtochItem->m_NewOption,MaxOpt1,Success1);
            if (addexc == -1 ) return false;
            return true;
        }
        if (Opt2 == 5)
        {
            addexc = this->AddExcOpt(ProtochItem->m_NewOption,MaxOpt2,Success2);
            if (addexc == -1 ) return false;
            return true;
        }
    }
    return false;
}

void cJewels::Successfully(int Opt1 , int Opt2 , int MaxOpt1 , int MaxOpt2, int Success1 , int Success2 , CItem* ProtochItem)
{
    // Add Item Option
    if (Opt1 == 1 || Opt2 == 1)
    {
        if (Opt1 == 1 )	ProtochItem->m_Level += Success1;
        if (Opt2 == 1)	ProtochItem->m_Level += Success2;
    }
    // Luck Add
    if (Opt1 == 2 || Opt2 == 2)	ProtochItem->m_Option2 = 1;

    // Skill Add
    if (Opt1 == 3 || Opt2 == 3)	ProtochItem->m_Option1 = 1;

    // Add Option
    if (Opt1 == 4 || Opt2 == 4)
    {
        if (Opt1 == 4 )	ProtochItem->m_Option3 += Success1;
        if (Opt2 == 4)	ProtochItem->m_Option3 += Success2;
    }

    // Exc Opt
    if (Opt1 == 5 || Opt2 == 5)
    {
        int addexc;
        if (Opt1 == 5 )
        {
            addexc = this->AddExcOpt(ProtochItem->m_NewOption,MaxOpt1,Success1);
            ProtochItem->m_NewOption = addexc;
        }
        if (Opt2 == 5)
        {
            addexc = this->AddExcOpt(ProtochItem->m_NewOption,MaxOpt2,Success2);
            ProtochItem->m_NewOption = addexc;
        }
    }
}

void cJewels::Fail(int Opt1, int Opt2 , int Fail1, int Fail2 , int FailOpt1, int FailOpt2, CItem* ProtochItem)
{
    // Down Item level
    if (Opt1 == 1 || Opt2 == 1)
    {
        if (Opt1 == 1)
        {
            if (Fail1 == 0) ProtochItem->m_Level = 0;
            if (Fail1 == 2) ProtochItem->m_Level -= FailOpt1;
        }
        if (Opt2 == 2)
        {
            if (Fail2 == 0) ProtochItem->m_Level = 0;
            if (Fail2 == 2) ProtochItem->m_Level -= FailOpt2;
        }
    }

    if (Opt1 == 4 || Opt2 == 4)
    {
        if (Opt1 == 4)
        {
            if (Fail1 == 0) ProtochItem->m_Option3 = 0;
            if (Fail1 == 2) ProtochItem->m_Option3 -= FailOpt1;
        }
        if (Opt2 == 4)
        {
            if (Fail2 == 0) ProtochItem->m_Option1 = 0;
            if (Fail2 == 2) ProtochItem->m_Option3 -= FailOpt2;
        }
    }
    if (Opt1 == 5 || Opt2 == 5)
    {
        if (Opt1 == 5)
        {
            if (Fail1 == 0) ProtochItem->m_NewOption = 0;
        }
        if (Opt2 == 5)
        {
            if (Fail2 == 0) ProtochItem->m_NewOption = 0;
        }
    }
}

int cJewels::AddExcOpt(int exc, int maxopt , int success)
{
    int arrayopt[6]= {0,0,0,0,0,0};
    int num = 32;
    int amountopt = 0;
    int added = 0;

    //Узнаем какие опции на шмотке
    for (int i=5; i>=0; i--)
    {
        if ( exc >= num )
        {
            arrayopt[i] = 1;
            amountopt++;
            exc = exc - num;
        }
        num = num / 2;
    }

    if (maxopt <= amountopt)
        return -1;

    //Выбираем любую недостающую опцию
    int randomopt = rand()%(6-amountopt)+1;
    amountopt = 0;

    for (int i=0; i<6; i++)
    {
        if (!arrayopt[i])
        {
            amountopt++;
            if (amountopt == randomopt )
            {
                arrayopt[i] = 1;
                added++;
                if (success == added)	break;
            }
        }
        else
            continue;
    }

    num = 1;
    exc = 0;
    // Получаем код
    for (int i=0 ; i<6; i++)
    {
        if (arrayopt[i])
        {
            exc += num;
        }
        num = num * 2;
    }

    return exc;
}

void cJewels::DeleteItem(int aIndex, int Slot)
{
    gObjInventoryDeleteItem(aIndex,Slot);
    GCInventoryItemDeleteSend(aIndex,Slot,1);
}