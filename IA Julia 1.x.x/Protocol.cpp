#include "StdAfx.h"
#include "Protocol.h"
#include "ChatCommands.h"
#include "User.h"
#include "DuelManager.h"
#include "PCPoint.h"
#include "MossGambler.h"
#include "Monster.h"
#include "MapSystem.h"
#include "TradeSystem.h"
#include "Territory.h"
#include "Jewels.h"
#include "OffTradeProtocol.h"
#include "Utilits.h"

BYTE RecvTable[256] =
{
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0xD7, 0x1E, 0x1F,
    0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F,
    0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F,
    0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F,
    0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F,
    0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F,
    0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E, 0x7F,
    0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F,
    0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9A, 0x9B, 0x9C, 0x9D, 0x9E, 0x9F,
    0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF,
    0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7, 0xB8, 0xB9, 0xBA, 0xBB, 0xBC, 0xBD, 0xBE, 0xBF,
    0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF,
    0xD0, 0xD1, 0xD2, 0x1D, 0xD4, 0xD5, 0xD6, 0xDC, 0xD8, 0xD9, 0xDA, 0xDB, 0xDC, 0xDD, 0xDE, 0xD6,
    0xE0, 0xE1, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6, 0xE7, 0xE8, 0xE9, 0xEA, 0xEB, 0xEC, 0xED, 0xEE, 0xEF,
    0xF0, 0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7, 0xF8, 0xF9, 0xFA, 0xFB, 0xFC, 0xFD, 0xFE, 0xFF
};

//=====================================================================================
//Protocol Server Send
//=====================================================================================
#if (IS_PROTOCOL_JPN == 0)
BYTE ProtocolServerENG(BYTE Type)
{
    switch(Type)
    {
		case 0x1D:
		{
			return 0xD4;
		}
		case 0xD6:
		{
			return 0x15;
		}
		case 0xDC:
		{
			return 0x11;
		}
    }

    return Type;
}

//=====================================================================================
//Protocol Client Send
//=====================================================================================
BYTE ProtocolClientENG(BYTE Tipo)
{
    switch(Tipo)
    {
		case 0xD4:
		{
			return 0x1D;
		}
		case 0x15:
		{
			return 0xD6;
		}
		case 0x11:
		{
			return 0xDC;
		}
	}

	return Tipo;
}
#endif

void gObjTradeOkButton(int aIndex)
{
    BYTE result = 1;
    OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);
    int number = gObj->TargetNumber;

    if(number < 0)
    {
        return;
    }

    OBJECTSTRUCT *gObj2 = (OBJECTSTRUCT*)OBJECT_POINTER(number);

    if(gObj2->Connected < PLAYER_PLAYING)
    {
        return;
    }

    if (gObj2->TargetNumber != aIndex)
    {
        Log.ConsoleOutPut(1, c_Red, t_Default, "[X] [Trade]\tThe opposite to trade is not me. (%s)(%s) Target:(%d) (%d)", gObj->AccountID, gObj->Name, gObj->TargetNumber, gObj2->TargetNumber);
        return;
    }

    if (gObj->TradeOk != 1 || gObj2->TradeOk != 1)
    {
        return;
    }

    if (TradeSystem.CheckTradeItem(gObj) || TradeSystem.CheckTradeItem(gObj2))
    {
        result = 3;
        gObjTradeCancel(aIndex);
        gObjTradeCancel(number);
        CGTradeResult(aIndex, result);
        CGTradeResult(number, result);

        return;
    }

    GSgObjTradeOkButton(aIndex);
}

void gObjPlayerKiller(LPOBJ lpObj, LPOBJ lpTargetObj)
{
    if(MapSystem.Maps[lpObj->MapNumber].PVP == 3 && lpTargetObj->Type == OBJECT_USER && lpObj->Type == OBJECT_USER)
	{
        return;
	}

    GCgObjPlayerKiller(lpObj, lpTargetObj);
}

BOOL gObjAttack(LPOBJ lpObj, LPOBJ lpTargetObj, class CMagicInf* lpMagic, int magicsend, unsigned char MSBFlag, int AttackDamage, BOOL bCombo)
{
    bool bResult = TRUE;
#ifdef _GS_CS
    BYTE castleSiegeState = *(unsigned char *) GS_CASTLESIEGESTAT;
    if(castleSiegeState==CASTLESIEGE_STATE_STARTSIEGE)
	{
        if(lpTargetObj->Type == OBJECT_USER && lpObj->Type == OBJECT_USER)
		{
            if( lpObj->GuildNumber!=0 && lpTargetObj->GuildNumber!=0 )
			{
                if(lpObj->GuildNumber == lpTargetObj->GuildNumber)
				{
                    return false;
                }

                if(lpObj->lpGuild->GetGuildUnion()!=0)
				{
                    if(lpObj->lpGuild->GetGuildUnion()==lpTargetObj->lpGuild->GetGuildUnion())
					{
                        return false;
                    }
                }
            }
        }
    }
#endif
    int MonsterTerr = Territory.CheckTerritory(lpTargetObj);
    int UserTerr = Territory.CheckTerritory(lpObj);

    if (MonsterTerr >= 0)
    {
        if (AddTab[lpObj->m_Index].TERR_Type != MonsterTerr || UserTerr != MonsterTerr)
        {
            bResult = FALSE;
        }
    }

    if (MapSystem.Maps[lpObj->MapNumber].PVP == 1 && lpTargetObj->Type == OBJECT_USER && lpObj->Type == OBJECT_USER)
	{
        bResult = FALSE;
	}

    if (bResult == FALSE)
	{
        return FALSE;
	}

    return GCgObjAttack(lpObj, lpTargetObj, lpMagic, magicsend, MSBFlag, AttackDamage, bCombo);
}

bool ProtocolCore(BYTE protoNum, LPBYTE aRecv, DWORD aLen, int aIndex, DWORD Encrypt, int Serial)
{
    OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);

    if(!Configs.Unicode32)
    {
        if(protoNum == 0xF3)
        {
            PMSG_DEFAULT2 * lpDef = (PMSG_DEFAULT2 *)aRecv;

            switch(lpDef->subcode)
            {
				case 0x01:
				{
					if (User.CharacterCreate((PMSG_CHARCREATE *)aRecv, aIndex))
					{
						JGCharacterCreateFailSend(aIndex, gObj->Name);

						return true;
					}
				}
            }
        }
    }

    switch (BYTE(protoNum))
    {
        case 0x00: // Chat Protocol
        {
            if (Chat.ChatDataSend(gObj, (PMSG_CHATDATA *)aRecv))
		    {
                return true;
		    }

            break;
        }
        case 0x01:
        {
            CloseClient(aIndex);

            return true;

            break;
        }
        case 0x02:
        {
            if(Chat.WisperChat(gObj, (PMSG_CHATDATA_WHISPER *)aRecv))
            {
                return true;
            }

            break;
        }
        case 0x03: // Player Connected Protocol
        {
            User.PlayerConnect(gObj);

            break;
        }
        case 0x18:
        {
            if(aLen != 5)
            {
                CloseClient(aIndex);

                return true;
            }

            if(aRecv[3] > 7)
            {
                CloseClient(aIndex);

                return true;
            }

            break;
        }
        case 0x24: // Equip Guardian
        {
            User.CheckRing(gObj, aRecv);

            break;
        }
        case 0x26:
        {
            Jewels.IdentifyJewel((PMSG_USE_ITEM_RECV*)aRecv, aIndex);

            break;
        }
        case 0xD0: // PC Points
        {
            if (aRecv[3] == 0x05)
            {
                PCPoint.BuyItem(aIndex, aRecv[4]);

                return true;
            }

            if((aRecv[3] == 0x06) && (aRecv[1] == 0x04))
            {
                if((gObj->MapNumber == 0) || (gObj->MapNumber == 2) || (gObj->MapNumber == 3) || (gObj->MapNumber == 51))
                {
                    PCPoint.OpenShop(aIndex);
                }
                else
                {
                    Chat.Message(1, gObj, "[PointShop] Somente em Lorencia, Devias, Noria, Elbeland.");
                    
					BYTE pNewProtocol[0x05] = {0xC1,0x05,0x18,0x01,0x7A };
                    DataRecv(RecvTable[pNewProtocol[2]], pNewProtocol, pNewProtocol[1], aIndex, Encrypt, Serial);
                }

                return true;
            }

            break;
        }
		case 0x30: // Click NPC Protocol
		{
			if(Monster.NPCTalkEx(gObj,(aRecv[4] + aRecv[3] * 256)))
			{
				return true;
			}

			break;
		}
        case 0x40:
        {
            if (Configs.IsPartyGap)
            {
                if (User.CGPartyRequestRecv((PMSG_PARTYREQUEST*)aRecv, aIndex))
                {
                    return true;
                }
            }

            break;
        }
        case 0x55:
        {
            if (User.GuildMasterInfoSave(aIndex, (PMSG_GUILDINFOSAVE *)aRecv))
            {
                return true;
            }

            break;
        }
#ifdef _GS
		case 0x86: // Chaos Machine
		{
			/*NOTHING TO DO WITH THAT SHIT*/

			break;
		}
#endif
        case 0xAA:
        {
#ifdef _GS
            if(DuelSystem.Config.Enabled)
            {
                DuelSystem.DuelProtocolCore(gObj,aRecv);

                return true;
            }
#else
            GCServerMsgStringSend("You can't use duel on CS server!", aIndex, 1);
#endif
            break;
        }
    
#ifdef _GS
#if(IS_PROTOCOL_JPN == 0)
        case 0xF1: //Login protocol (Season 4) ENG
        {
            aRecv[1] -= 0x0A;
            aLen = aRecv[1];

            for(int i = 24; i<50; i++)
            {
                aRecv[i] = aRecv[i+10];
            }

            break;
        }
        case 0xDB: // Skill ENG
        {
            protoNum = 0xD7;
            aRecv[2] = 0xD7;

            break;
        }
#endif
        case 0x32:
        {
            if(Moss.Config.Enable)
            {
                if (Moss.BuyItem(aIndex,aRecv) == TRUE)
                {
                    Moss.DataSendMoss(aIndex);

                    return true;
                }
            }

            break;
        }
#else
#if(IS_PROTOCOL_JPN == 0)
        case 0xF1: //Login protocol (Season 4) ENG
        {
            aRecv[1] -= 0x0A;
            aLen = aRecv[1];

            for (int i = 24; i < 50; i++)
            {
                aRecv[i] = aRecv[i + 10];
            }

            break;
        }
        case 0xDB: // Skill ENG
        {
            protoNum = 0xD7;
            aRecv[2] = 0xD7;
            
            break;
        }
#endif
#endif
    }

    DataRecv(protoNum, aRecv, aLen, aIndex, Encrypt, Serial);

    return true;
}

void ProtocolCoreSend(int aIndex, PBYTE aSend, int aLen)
{
    OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);

    if (aSend[0] == 0xC1 || aSend[0] == 0xC3)
    {
        switch (aSend[2])
        {
			case 0x24:
			{
				User.CheckRingSend(gObj, aSend);

				break;
			}
        }
    }

    DataSend(aIndex, aSend, aLen);
}

#if (IS_PROTOCOL_JPN == 0)
void SetProtocol()
{
#ifdef _GS
    Utilits.SetByte(0x004B21C6, 0x33);
    Utilits.SetByte(0x004B21C7, 0xD2);
    Utilits.SetByte(0x004B21C8,0xE9);
    Utilits.SetByte(0x004B21C9,0xC8);
    Utilits.SetByte(0x004B21CA,0x09);
    Utilits.SetByte(0x004B21CB,0x00);
    Utilits.SetByte(0x004B21CC,0x00);
    Utilits.SetByte(0x004B21CD,0x90);
    Utilits.SetByte(0x004B21CE,0x90);

    Utilits.SetByte(0x004B2B95,0x8A);
    Utilits.SetByte(0x004B2B96,0x51);
    Utilits.SetByte(0x004B2B97,0x02);
    Utilits.SetByte(0x004B2B98,0x52);
    Utilits.SetByte(0x004B2B99,0xFF);
    Utilits.SetByte(0x004B2B9A,0x15);
    Utilits.SetByte(0x004B2B9B,0x04);
    Utilits.SetByte(0x004B2B9C,0x28);
    Utilits.SetByte(0x004B2B9D,0x65);
    Utilits.SetByte(0x004B2B9E,0x00);
    Utilits.SetByte(0x004B2B9F,0x88);
    Utilits.SetByte(0x004B2BA0,0x45);
    Utilits.SetByte(0x004B2BA1,0xE4);
    Utilits.SetByte(0x004B2BA2,0x8B);
    Utilits.SetByte(0x004B2BA3,0x45);
    Utilits.SetByte(0x004B2BA4,0xF0);
    Utilits.SetByte(0x004B2BA5,0xE9);
    Utilits.SetByte(0x004B2BA6,0x25);
    Utilits.SetByte(0x004B2BA7,0xF6);
    Utilits.SetByte(0x004B2BA8,0xFF);
    Utilits.SetByte(0x004B2BA9,0xFF);

    Utilits.SetByte(0x004C256B,0x33);
    Utilits.SetByte(0x004C256C,0xC9);
    Utilits.SetByte(0x004C256D,0x8A);
    Utilits.SetByte(0x004C256E,0x4D);
    Utilits.SetByte(0x004C256F,0x0C);
    Utilits.SetByte(0x004C2570,0x51);
    Utilits.SetByte(0x004C2571,0xFF);
    Utilits.SetByte(0x004C2572,0x15);
    Utilits.SetByte(0x004C2573,0x00);
    Utilits.SetByte(0x004C2574,0x28);
    Utilits.SetByte(0x004C2575,0x65);
    Utilits.SetByte(0x004C2576,0x00);
    Utilits.SetByte(0x004C2577,0x8B);
    Utilits.SetByte(0x004C2578,0x75);
    Utilits.SetByte(0x004C2579,0x08);
    Utilits.SetByte(0x004C257A,0x88);
    Utilits.SetByte(0x004C257B,0x46);
    Utilits.SetByte(0x004C257C,0x02);
    Utilits.SetByte(0x004C257D,0x5F);
    Utilits.SetByte(0x004C257E,0x5E);
    Utilits.SetByte(0x004C257F,0x5B);
    Utilits.SetByte(0x004C2580,0x8B);
    Utilits.SetByte(0x004C2581,0xE5);
    Utilits.SetByte(0x004C2582,0x5D);
    Utilits.SetByte(0x004C2583,0xC3);
#else
    Utilits.SetByte(0x004C31E6, 0x33);
    Utilits.SetByte(0x004C31E7, 0xD2);
    Utilits.SetByte(0x004C31E8, 0xE9);
    Utilits.SetByte(0x004C31E9, 0xC8);
    Utilits.SetByte(0x004C31EA, 0x09);
    Utilits.SetByte(0x004C31EB, 0x00);
    Utilits.SetByte(0x004C31EC, 0x00);
    Utilits.SetByte(0x004C31ED, 0x90);
    Utilits.SetByte(0x004C31EE, 0x90);

    Utilits.SetByte(0x004C3BB5, 0x8A);
    Utilits.SetByte(0x004C3BB6, 0x51);
    Utilits.SetByte(0x004C3BB7, 0x02);
    Utilits.SetByte(0x004C3BB8, 0x52);
    Utilits.SetByte(0x004C3BB9, 0xFF);
    Utilits.SetByte(0x004C3BBA, 0x15);
    Utilits.SetByte(0x004C3BBB, 0x84);
    Utilits.SetByte(0x004C3BBC, 0x88);
    Utilits.SetByte(0x004C3BBD, 0x68);
    Utilits.SetByte(0x004C3BBE, 0x00);
    Utilits.SetByte(0x004C3BBF, 0x88);
    Utilits.SetByte(0x004C3BC0, 0x45);
    Utilits.SetByte(0x004C3BC1, 0xE4);
    Utilits.SetByte(0x004C3BC2, 0x8B);
    Utilits.SetByte(0x004C3BC3, 0x45);
    Utilits.SetByte(0x004C3BC4, 0xF0);
    Utilits.SetByte(0x004C3BC5, 0xE9);
    Utilits.SetByte(0x004C3BC6, 0x25);
    Utilits.SetByte(0x004C3BC7, 0xF6);
    Utilits.SetByte(0x004C3BC8, 0xFF);
    Utilits.SetByte(0x004C3BC9, 0xFF);

    Utilits.SetByte(0x004D350B, 0x33);
    Utilits.SetByte(0x004D350C, 0xC9);
    Utilits.SetByte(0x004D350D, 0x8A);
    Utilits.SetByte(0x004D350E, 0x4D);
    Utilits.SetByte(0x004D350F, 0x0C);
    Utilits.SetByte(0x004D3510, 0x51);
    Utilits.SetByte(0x004D3511, 0xFF);
    Utilits.SetByte(0x004D3512, 0x15);
    Utilits.SetByte(0x004D3513, 0x80);
    Utilits.SetByte(0x004D3514, 0x88);
    Utilits.SetByte(0x004D3515, 0x68);
    Utilits.SetByte(0x004D3516, 0x00);
    Utilits.SetByte(0x004D3517, 0x8B);
    Utilits.SetByte(0x004D3518, 0x75);
    Utilits.SetByte(0x004D3519, 0x08);
    Utilits.SetByte(0x004D351A, 0x88);
    Utilits.SetByte(0x004D351B, 0x46);
    Utilits.SetByte(0x004D351C, 0x02);
    Utilits.SetByte(0x004D351D, 0x5F);
    Utilits.SetByte(0x004D351E, 0x5E);
    Utilits.SetByte(0x004D351F, 0x5B);
    Utilits.SetByte(0x004D3520, 0x8B);
    Utilits.SetByte(0x004D3521, 0xE5);
    Utilits.SetByte(0x004D3522, 0x5D);
    Utilits.SetByte(0x004D3523, 0xC3);
#endif

    _asm
    {
#ifdef _GS
        Mov Dword Ptr Ds : [00652804H], Offset ProtocolClientENG
        Mov Dword Ptr Ds : [00652800H], Offset ProtocolServerENG
#else
        Mov Dword Ptr Ds : [00688880H], Offset ProtocolServerENG
        Mov Dword Ptr Ds : [00688884H], Offset ProtocolClientENG
#endif
    }
}
#endif