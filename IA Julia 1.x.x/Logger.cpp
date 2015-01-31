#include "stdafx.h"
#include "Logger.h"
#include "Configs.h"

char Message[1024];

Logger Log;
DWORD PiD;

void __stdcall LoggerCore(PVOID pVoid)
{
	AllocConsole();

	while(true)
	{
		SetConsoleTitleA(Log.LoggerTittle());
		Sleep(5000);
	}

	_endthread();
}

char* Logger::LoggerTittle()
{
	static char Tittle[512];
#ifdef _GS
#define GType "(GS)"
#else
#define GType "(GS_CS)"
#endif
	sprintf(Tittle, "[%s] [%d/%d] IA Julia 1.1.%d.%d %s", Configs.ServerName,Online_All,Online_Max,dBuild,dCommit,GType);

	return Tittle;
}

void Logger::LoggerInit()
{
	Online_Max = GetPrivateProfileInt("GameServerInfo", "NumberOfMaxUser",0,"..\\Data\\CommonServer.cfg");
	CreateThread(0,0,(LPTHREAD_START_ROUTINE)LoggerCore, 0, 0, &PiD); 
}

void Logger::CheckProcent(char* message)
{
	for(UINT i = 0; i <= strlen(message); i++)
	{
		if(message[i] == '%')
		{
			for(UINT j = strlen(message);j >= i;j--)
				message[j + 1] = message[j];
			i++;
		}
	}
}

void Logger::ConsoleOutPut(int WOL, sColor Color, sLogType Type, const char* Format, ...)
{
	SYSTEMTIME t;
	GetLocalTime(&t);
	DWORD dwBytesWritten;
	HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);
	va_list pArguments;
	va_start(pArguments, Format);
	vsprintf_s(Message, Format, pArguments);
	CheckProcent(Message);
	va_end(pArguments);

	char currdate[11] = { 0 };
	char outputmsg[2048];

	if(WOL == 1)
	{
		sprintf_s(currdate, "(%02d:%02d:%02d)", t.wHour, t.wMinute, t.wSecond);
		sprintf_s(outputmsg, "%s %s\n", currdate, Message);
	}
	else
	{
		sprintf_s(outputmsg, "%s\n", Message);
	}

	switch (Color)
	{
		case c_BoldGreen:
		{
			SetConsoleTextAttribute(this->Handle(FALSE), FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_INTENSITY);

			break;
		}
		case c_BoldRed:
		{
			SetConsoleTextAttribute(this->Handle(FALSE), FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_RED);

			break;
		}
		case c_Red:
		{
			SetConsoleTextAttribute(this->Handle(FALSE), FOREGROUND_RED | FOREGROUND_INTENSITY);

			break;
		}
		case c_Green:
		{
			SetConsoleTextAttribute(this->Handle(FALSE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);

			break;
		}
		case c_Blue:
		{
			SetConsoleTextAttribute(this->Handle(FALSE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);

			break;
		}
		case c_Cyan:
		{
			SetConsoleTextAttribute(this->Handle(FALSE), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);

			break;
		}
		case c_Yellow:
		{
			SetConsoleTextAttribute(this->Handle(FALSE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);

			break;
		}
		case c_Magenta:
		{
			SetConsoleTextAttribute(this->Handle(FALSE), FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);

			break;
		}
		case c_Grey:
		{
			SetConsoleTextAttribute(this->Handle(FALSE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);

			break;
		}
	}

	CreateLog(Type, outputmsg);
	WriteFile(this->Handle(FALSE), outputmsg, strlen(outputmsg), &dwBytesWritten, NULL);
	SetConsoleTextAttribute(this->Handle(FALSE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

	return;
}

HANDLE Logger::Handle(BOOL Input)
{
	if (Input != FALSE)
	{
		return GetStdHandle(STD_INPUT_HANDLE);
	}
	else
	{
		return GetStdHandle(STD_OUTPUT_HANDLE);
	}
}

void Logger::CreateLog(sLogType Type, const char* Format, ...)
{
	SYSTEMTIME now;
	GetLocalTime(&now);

	char ConsoleLog[55];
	char GMLog[55];
	char CommandsLog[55];
	char GPostLog[55];
	char PostLog[55];
	char DropLog[55];
	char BanLog[55];
	char DuelLog[55];
	char PcPointLog[55];
	char IpBlockLog[55];
	char ErrorLog[55];
	char Date[55];
	char SqlLog[55];
	char VipLog[55];
	char TradeLog[55];
	char TerritoryLog[55];
	char ArcherLog[55];
	char ResetLog[55];
	char HelpersLog[55];
	char QuestsLog[55];
	char TestLog[55];

	sprintf(Date, "..\\IA Julia\\ConsoleLogs\\%02d-%02d-%02d\\", now.wDay, now.wMonth, now.wYear);
	CreateDirectory(Date, NULL);

	sprintf(CommandsLog, "..\\IA Julia\\ConsoleLogs\\%02d-%02d-%02d\\Commands.log", now.wDay, now.wMonth, now.wYear);
	sprintf(ConsoleLog, "..\\IA Julia\\ConsoleLogs\\%02d-%02d-%02d\\CONSOLE.log", now.wDay, now.wMonth, now.wYear);
	sprintf(GPostLog, "..\\IA Julia\\ConsoleLogs\\%02d-%02d-%02d\\[GPOST].log", now.wDay, now.wMonth, now.wYear);
	sprintf(PostLog, "..\\IA Julia\\ConsoleLogs\\%02d-%02d-%02d\\[POST].log", now.wDay, now.wMonth, now.wYear);
	sprintf(DropLog, "..\\IA Julia\\ConsoleLogs\\%02d-%02d-%02d\\DROP.log", now.wDay, now.wMonth, now.wYear);
	sprintf(BanLog, "..\\IA Julia\\ConsoleLogs\\%02d-%02d-%02d\\BAN.log", now.wDay, now.wMonth, now.wYear);
	sprintf(GMLog, "..\\IA Julia\\ConsoleLogs\\%02d-%02d-%02d\\GM.log", now.wDay, now.wMonth, now.wYear);
	sprintf(DuelLog, "..\\IA Julia\\ConsoleLogs\\%02d-%02d-%02d\\DuelManager.log", now.wDay, now.wMonth, now.wYear);
	sprintf(PcPointLog, "..\\IA Julia\\ConsoleLogs\\%02d-%02d-%02d\\PCPoint.log", now.wDay, now.wMonth, now.wYear);
	sprintf(IpBlockLog, "..\\IA Julia\\ConsoleLogs\\%02d-%02d-%02d\\IpBlock.log", now.wDay, now.wMonth, now.wYear);
	sprintf(ErrorLog, "..\\IA Julia\\ConsoleLogs\\%02d-%02d-%02d\\Error.log", now.wDay, now.wMonth, now.wYear);
	sprintf(SqlLog, "..\\IA Julia\\ConsoleLogs\\%02d-%02d-%02d\\Sql.log", now.wDay, now.wMonth, now.wYear);
	sprintf(VipLog, "..\\IA Julia\\ConsoleLogs\\%02d-%02d-%02d\\Vip.log", now.wDay, now.wMonth, now.wYear);
	sprintf(TradeLog, "..\\IA Julia\\ConsoleLogs\\%02d-%02d-%02d\\Trade.log", now.wDay, now.wMonth, now.wYear);
	sprintf(TerritoryLog, "..\\IA Julia\\ConsoleLogs\\%02d-%02d-%02d\\Territory.log", now.wDay, now.wMonth, now.wYear);
	sprintf(ArcherLog, "..\\IA Julia\\ConsoleLogs\\%02d-%02d-%02d\\Archer.log", now.wDay, now.wMonth, now.wYear);
	sprintf(ResetLog, "..\\IA Julia\\ConsoleLogs\\%02d-%02d-%02d\\Reset.log", now.wDay, now.wMonth, now.wYear);
	sprintf(HelpersLog, "..\\IA Julia\\ConsoleLogs\\%02d-%02d-%02d\\Helpers.log", now.wDay, now.wMonth, now.wYear);
	sprintf(QuestsLog, "..\\IA Julia\\ConsoleLogs\\%02d-%02d-%02d\\Quests.log", now.wDay, now.wMonth, now.wYear);
	sprintf(TestLog, "..\\IA Julia\\ConsoleLogs\\%02d-%02d-%02d\\Test.log", now.wDay, now.wMonth, now.wYear);

	va_list pArguments1;
	va_start(pArguments1, Format);
	vsprintf_s(Message, Format, pArguments1);
	va_end(pArguments1);

	switch (Type)
	{
		case t_NULL:
		{
			break;
		}
		case t_Error:
		{
			SaveFile(ErrorLog, Message);

			break;
		}
		case t_Default:
		{
			SaveFile(ConsoleLog, Message);

			break;
		}
		case t_PCPOINT:
		{
			SaveFile(ConsoleLog, Message);
			SaveFile(PcPointLog, Message);

			break;
		}
		case t_IPBLOCK:
		{
			SaveFile(ConsoleLog, Message);
			SaveFile(IpBlockLog, Message);

			break;
		}
		case t_GM:
		{
			SaveFile(ConsoleLog, Message);
			SaveFile(GMLog, Message);

			break;
		}
		case t_COMMANDS:
		{
			SaveFile(ConsoleLog, Message);
			SaveFile(CommandsLog, Message);

			break;
		}
		case t_POST:
		{
			SaveFile(ConsoleLog, Message);
			SaveFile(PostLog, Message);
			SaveFile(CommandsLog, Message);

			break;
		}
		case t_GPOST:
		{
			SaveFile(ConsoleLog, Message);
			SaveFile(GPostLog, Message);
			SaveFile(CommandsLog, Message);
			SaveFile(GMLog, Message);

			break;
		}
		case t_DROP:
		{
			SaveFile(ConsoleLog, Message);
			SaveFile(DropLog, Message);
			SaveFile(CommandsLog, Message);
			SaveFile(GMLog, Message);

			break;
		}
		case t_BAN:
		{
			SaveFile(ConsoleLog, Message);
			SaveFile(BanLog, Message);
			SaveFile(CommandsLog, Message);
			SaveFile(GMLog, Message);

			break;
		}
		case t_Duel:
		{
			SaveFile(ConsoleLog, Message);
			SaveFile(DuelLog, Message);

			break;
		}
		case t_SQL:
		{
			SaveFile(ConsoleLog, Message);
			SaveFile(SqlLog, Message);

			break;
		}
		case t_VIP:
		{
			SaveFile(ConsoleLog, Message);
			SaveFile(VipLog, Message);

			break;
		}
		case t_TRADE:
		{
			SaveFile(ConsoleLog, Message);
			SaveFile(TradeLog, Message);

			break;
		}
		case t_TERRITORY:
		{
			SaveFile(ConsoleLog, Message);
			SaveFile(TerritoryLog, Message);

			break;
		}
		case t_ARCHER:
		{
			SaveFile(ConsoleLog, Message);
			SaveFile(ArcherLog, Message);

			break;
		}
		case t_RESET:
		{
			SaveFile(ResetLog, Message);

			break;
		}
		case t_HELPERS:
		{
			SaveFile(HelpersLog, Message);

			break;
		}
		case t_QUEST:
		{
			SaveFile(QuestsLog, Message);

			break;
		}
		case t_TEST:
		{
			SaveFile(TestLog, Message);

			break;
		}
	}
}

void Logger::SaveFile(char *logString, char *Message)
{
	FILE *stream;
	stream = fopen(logString,"a+");

	if(stream != nullptr)
	{
		fprintf(stream,Message);
		fclose(stream);
	}
}