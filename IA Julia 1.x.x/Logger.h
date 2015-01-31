#ifndef Logger_H
#define Logger_H

extern char Message[1024];

enum sColor
{
	c_BoldGreen,
	c_BoldRed,
	c_Red,
	c_Green,
	c_Blue,
	c_Cyan,
	c_Yellow,
	c_Magenta,
	c_Grey
};

enum sLogType
{
	t_NULL,
	t_Error,
	t_Default,
	t_GM,
	t_POST,
	t_DROP,
	t_BAN,
	t_COMMANDS,
	t_GPOST,
	t_PCPOINT,
	t_IPBLOCK,
	t_Duel,
	t_SQL,
	t_VIP,
	t_TRADE,
	t_TERRITORY,
	t_ARCHER,
	t_RESET,
	t_TEST,
	t_HELPERS,
	t_QUEST
};

class Logger
{
	public:
		void LoggerInit();
		void CheckProcent(char* message);
		void SaveFile(char *logString,char *Message);
		void ConsoleOutPut(int WOL, sColor Color, sLogType Type, const char* Format, ...);
		HANDLE Handle(BOOL Input);
		void CreateLog(sLogType Type,const char* Format, ...);
		char *LoggerTittle();

		int Online_Max;
		int Online_All;
		int Online_Gms;
};
extern Logger Log;

#endif Logger_H