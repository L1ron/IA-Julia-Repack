#include "StdAfx.h"
#include "Configs.h"
#include "Maps.h"
#include "Fixes.h"
#include "Utilits.h"
#include "Protocol.h"
#include "Logger.h"
#include "AntiAFK.h"
#include "DuelManager.h"
#include "MoveReq.h"
#include "PCPoint.h"
#include "ChatCommands.h"
#include "MossGambler.h"
#include "Monster.h"
#include "Query.h"
#include "Vip.h"
#include "HappyHour.h"
#include "Territory.h"
#include "News.h"
#include "OffTrade.h"
#include "ResetSystem.h"
#include "Socket.h"
#include "TradeSystem.h"
#include "HPBar.h"
#include "Interface.h"

DWORD MainTick()
{
	while(true)
	{
		int Temp_All = 0;
		int Temp_Gms = 0;

		for(int i = 0; i < OBJECT_MIN; i++)
		{
			if (AddTab[i].TEMP_Golden_Drop)
			{
				AddTab[i].TEMP_Golden_Drop = false;
			}
		}

		for(int i = OBJECT_MIN; i <= OBJECT_MAX; i++)
		{
			OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(i);

			if(gObj->Connected < PLAYER_LOGGED)
			{
				continue;
			}

			if(GmSystem.IsGMBD(i))
			{
				Temp_Gms++;
			}
			else
			{
				Temp_All++;
			}

			if(gObj->Connected < PLAYER_PLAYING)
			{
				continue;
			}

			if(AddTab[gObj->m_Index].OfflineTrade != true)
			{
				User.OnlineTimeTick(gObj);
			}

			Territory.Tick(gObj);

			if(AddTab[gObj->m_Index].OfflineTrade != true)
			{
				AntiAFK.Tick(gObj);
			}

			PCPoint.Tick(gObj);
			Vip.Tick(gObj);
			HappyHour.TickTimerHappyHour();
#ifdef _GS
			Moss.CheckTime();
#endif
			Sleep(1000);
			Log.Online_All = Temp_All;
			Log.Online_Gms = Temp_Gms;
		}

		return 1;
	}
}

extern "C" __declspec(dllexport) void __cdecl RMST()
{
	DWORD OldProtect;

	if(VirtualProtect(LPVOID(0x401000),GSSIZE, PAGE_EXECUTE_READWRITE, &OldProtect))
	{
		CreateDirectory(IAJuliaConsoleLogs,NULL);
		CreateDirectory(IAJuliaChatLogs,NULL);
		CreateDirectory(IAJuliaLog,NULL);

		if(GetPrivateProfileInt("Connect","ConsoleDebug",0,IAJuliaGS))
		{
			Sleep(500);
			Log.LoggerInit();
			Sleep(500);

			Log.ConsoleOutPut(0,c_Green,t_NULL,"IA Julia 1.1.%d.%d Season 4.6 Remake V%d",dBuild, dCommit, Remakever);
			Log.ConsoleOutPut(0,c_Green,t_NULL,"Suporte Skype: SmileYzn@live.com");
			Log.ConsoleOutPut(0,c_Green,t_NULL,"Data: %s %s",__DATE__,__TIME__);
			Log.ConsoleOutPut(0,c_Green,t_NULL,"Creditos: Comunidade MuOnline, WebZen\n");
		}

		InterfaceLoad();
		LoadQuery();
		Maps.MapInit();
		Fixes.ASMFixes();
		Socket.Load();
		Configs.LoadAll();
		ResetSystem.Init();

#if (IS_PROTOCOL_JPN == 0)
		SetProtocol();
#endif

#ifdef _GS
		OfflineTrade.InitOfflineTrade();

		if(DuelSystem.Config.Enabled)
		{
			DuelSystem.DuelCreateThread();
			Utilits.HookThis((DWORD)&HookSetDuelOption,0x004037B5);
			Utilits.HookThis((DWORD)&HookIsDuelEnable,0x00404BCE);
			Utilits.HookThis((DWORD)&HookIsOnDuel,0x00404B56);
			Utilits.HookThis((DWORD)&HookDuelCheck1,0x00403017);
			Utilits.HookThis((DWORD)&HookDuelCheck2,0x004012DA);
			Utilits.HookThis((DWORD)&GSgObjUserDie,0x0040367A);
		}

		Utilits.HookThis((DWORD)&CheckItemType,0x00402E9B);
		Utilits.HookThis((DWORD)&ProtocolCore, 0x004038BE);
		Utilits.HookThis((DWORD)&gObjGameClose_Func, 0x004034B8);
		Utilits.HookThis((DWORD)&ProtocolCoreSend,0x004055BF);
		Utilits.HookThis((DWORD)&MyObjCalCharacter,0x004031A7);
		Utilits.HookThis((DWORD)&MonsterDie, 0x004184C4);
		Utilits.HookThis((DWORD)&GCEquipmentSendHook, 0x00407509);
		Utilits.HookThis((DWORD)&GCKillPlayerExpSendHook, 0x00406D11);
		Utilits.HookThis((DWORD)&MyItemSerialCreateSend, 0x00407004);
		Utilits.HookThis((DWORD)&MygEventMonsterItemDrop, 0x00402AD1);
		Utilits.HookThis((DWORD)&gObjLevelUpPointAddEx,0x00406D7F);
		Utilits.HookThis((DWORD)&gObjPlayerKiller, 0x0040655F);
		Utilits.HookThis((DWORD)&gObjAttack, 0x00403CA6);
		Utilits.HookThis((DWORD)&gObjTradeOkButton, 0x00404A93);
		Utilits.HookThis((DWORD)&GSItemDurRepaire, 0x00405097);
		Utilits.HookThis((DWORD)&gObjInventoryMoveItemEx, 0x004021AD);
		Utilits.HookThis((DWORD)&CGItemDropRequestEx, 0x00401163);
		Utilits.HookThis((DWORD)&_gObjCheckTeleportArea, 0x0040268A);
		Utilits.HookThis((DWORD)&GetRandomOpExe, 0x0049D3BB);
		Utilits.HookThis((DWORD)&GCDamageSend, 0x00403BA7);                    // HP Bar
#endif

#ifdef _GS_CS
		Utilits.HookThis((DWORD)&CheckItemType, 0x00402E32);
		Utilits.HookThis((DWORD)&ProtocolCore, 0x00403A17);
		Utilits.HookThis((DWORD)&ProtocolCoreSend, 0x00405AE7);
		Utilits.HookThis((DWORD)&gObjGameClose_Func, 0x00403599);
		Utilits.HookThis((DWORD)&MyObjCalCharacter, 0x004031F7);
		Utilits.HookThis((DWORD)&MonsterDie, 0x0041A1AE);
		Utilits.HookThis((DWORD)&GCEquipmentSendHook, 0x00407E37);
		Utilits.HookThis((DWORD)&GCKillPlayerExpSendHook, 0x0040751D);
		Utilits.HookThis((DWORD)&MygEventMonsterItemDrop, 0x004029F0);
		Utilits.HookThis((DWORD)&gObjLevelUpPointAddEx, 0x004075B3);
		Utilits.HookThis((DWORD)&gObjPlayerKiller, 0x00406C8A);
		Utilits.HookThis((DWORD)&gObjAttack, 0x00403E72);
		Utilits.HookThis((DWORD)&gObjTradeOkButton, 0x00404E08);
		Utilits.HookThis((DWORD)&GSItemDurRepaire, 0x0040551A);
		Utilits.HookThis((DWORD)&gObjInventoryMoveItemEx, 0x00401F96);
		Utilits.HookThis((DWORD)&CGItemDropRequestEx, 0x004082F6);
		Utilits.HookThis((DWORD)&_gObjCheckTeleportArea, 0x00402522);
		//Utilits.HookThis((DWORD)&GCDamageSend,0x00403D55);                    //HP BAR GS_CS
#endif

		DWORD ThreadID;
		HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)MainTick, NULL, 0, &ThreadID);

		if(hThread == 0)
		{
			Log.ConsoleOutPut(1, c_Red, t_Error,"CreateThread() failed with error %d", GetLastError());

			return;
		}

		CloseHandle(hThread);

		hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)NewsSystem, NULL, 0, &ThreadID);

		if(hThread == 0)
		{
			Log.ConsoleOutPut(1, c_Red, t_Error,"CreateThread() failed with error %d", GetLastError());

			return;
		}

		CloseHandle(hThread);

#ifdef _GS
		hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)MonsterAddTick, NULL, 0, &ThreadID);

		if(hThread == 0)
		{
			Log.ConsoleOutPut(1, c_Red, t_Error,"CreateThread() failed with error %d", GetLastError());

			return;
		}

		CloseHandle(hThread);
#endif
	}
}