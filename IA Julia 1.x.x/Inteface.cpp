#include "Stdafx.h"
#include "Offsets.h"
#include "Interface.h"
#include "Utilits.h"

char DISPLAY_TEXT[2][30] =
{
	"IA Julia Season 4.6 (GS)",
	"IA Julia Season 4.6 (CS)"
};

char SERVER_STATUS[12][32] = 
{
	"JoinServer: Desconectado",
	"JoinServer: Conectado",
	"FsGateServer: Desconectado",
	"FsGateServer: Conectado",
	"DataServer: Desconectado",
	"DataServer: Conectado",
	"ExDBServer: Desconectado",
	"ExDBServer: Conectado",
	"EventServer: Desconectado",
	"EventServer: Conectado",
	"RankingServer: Desconectado",
	"RankingServer: Conectado"
};
// -- Cor do fundo (Padrao: Branco)
HBRUSH	  BackgroundSolidColor		= CreateSolidBrush(RGB(20, 20, 20));

// -- Cores da Função (ServerStatus)
COLORREF  COLOR_CONNECTED			= RGB(0, 255, 0);
COLORREF  COLOR_DISCONNECTED		= RGB(255, 0, 0);

// -- Cores dos Logs exibidos no GS
COLORREF  TextLogColor_01			= RGB(255, 0, 0);	
COLORREF  TextLogColor_02			= RGB(0, 100, 0);
COLORREF  TextLogColor_03			= RGB(0, 0, 255);
COLORREF  TextLogColor_04			= RGB(155, 0, 0);
COLORREF  TextLogColor_05			= RGB(0, 0, 100);
COLORREF  TextLogColor_06			= RGB(210, 30, 150);
COLORREF  TextLogColor_07			= RGB(200, 200, 200);

// -- Cor do Texto Exibido no Topo (COUNT:....)
COLORREF  HeaderTextColor			= RGB(200, 200, 200);

// -- Cor do Texto e do Background Exibido no topo (SERVER INFO DISPLAYER) {[- Common -], ]+[ CASTLE ]+[}
COLORREF  ServerInfoDisplayerBG		= RGB(28, 28, 28);
COLORREF  ServerInfoDisplayerText	= RGB(200, 200, 200);

void __declspec(naked) BackgroundColor()
{
	_asm
	{
		PUSH 9						// -- Push Color
		LEA EDX,DWORD PTR SS:[EBP-0x30]
		PUSH EDX
		MOV EAX,DWORD PTR SS:[EBP-0x34]
		PUSH EAX
		CALL DWORD PTR DS:[INTERFACE_FUNC_FILLRECT]		// -- FillRect
		MOV EDI, Interface_BackgroundColorRtn01
		JMP EDI
	}
}

void __declspec(naked) BackgroundColorFix01()
{
	_asm
	{
		MOV DWORD PTR SS:[EBP-0x8],0x1E
		PUSH 1
		MOV EDX,DWORD PTR SS:[EBP-0x4]
		PUSH EDX
		CALL DWORD PTR DS:[INTERFACE_FUNC_SETBKMODE]	// -- SetBKMode
		MOV EDI, Interface_BackgroundColorRtn02
		JMP EDI
	}
}

void __declspec(naked) BackgroundColorFix02()
{
	_asm
	{
		MOV EAX,DWORD PTR DS:[INTERFACE_FUNC_GITEMLOOP]	// -- gItemloop
		PUSH 1
		MOV ECX,DWORD PTR SS:[EBP-0x14]
		PUSH ECX
		CALL DWORD PTR DS:[INTERFACE_FUNC_SETBKMODE]	// -- SetBKMode
		PUSH HeaderTextColor							// -- Color Header Text
		MOV ECX,DWORD PTR SS:[EBP-0x14]
		PUSH ECX
		CALL DWORD PTR DS:[INTERFACE_FUNC_SETTEXTCOLOR]	// -- SetTextColor
		MOV EDI, Interface_BackgroundColorRtn03
		JMP EDI
	}
}

void __declspec(naked) TextLogColor01()
{
	_asm
	{
		PUSH TextLogColor_01							// Text Color
		MOV EDX,DWORD PTR SS:[EBP-0x4]
		PUSH EDX
		CALL DWORD PTR DS:[INTERFACE_FUNC_SETTEXTCOLOR]	// -- SetTextColor
		MOV EDI, Interface_LogTextColorRtn				// -- Return Func Color
		JMP EDI
	}
}

void __declspec(naked) TextLogColor02()
{
	_asm
	{
		PUSH TextLogColor_02							// Text Color
		MOV EDX,DWORD PTR SS:[EBP-0x4]
		PUSH EDX
		CALL DWORD PTR DS:[INTERFACE_FUNC_SETTEXTCOLOR]	// -- SetTextColor
		MOV EDI, Interface_LogTextColorRtn				// -- Return Func Color
		JMP EDI
	}
}

void __declspec(naked) TextLogColor03()
{
	_asm
	{
		PUSH TextLogColor_03							// Text Color
		MOV EDX,DWORD PTR SS:[EBP-0x4]
		PUSH EDX
		CALL DWORD PTR DS:[INTERFACE_FUNC_SETTEXTCOLOR]	// -- SetTextColor
		MOV EDI, Interface_LogTextColorRtn				// -- Return Func Color
		JMP EDI
	}
}

void __declspec(naked) TextLogColor04()
{
	_asm
	{
		PUSH TextLogColor_04							// Text Color
		MOV EDX,DWORD PTR SS:[EBP-0x4]
		PUSH EDX
		CALL DWORD PTR DS:[INTERFACE_FUNC_SETTEXTCOLOR]	// -- SetTextColor
		MOV EDI, Interface_LogTextColorRtn				// -- Return Func Color
		JMP EDI
	}
}

void __declspec(naked) TextLogColor05()
{
	_asm
	{
		PUSH TextLogColor_05							// Text Color
		MOV EDX,DWORD PTR SS:[EBP-0x4]
		PUSH EDX
		CALL DWORD PTR DS:[INTERFACE_FUNC_SETTEXTCOLOR]	// -- SetTextColor
		MOV EDI, Interface_LogTextColorRtn				// -- Return Func Color
		JMP EDI
	}
}

void __declspec(naked) TextLogColor06()
{
	_asm
	{
		PUSH TextLogColor_06							// Text Color
		MOV EDX,DWORD PTR SS:[EBP-0x4]
		PUSH EDX
		CALL DWORD PTR DS:[INTERFACE_FUNC_SETTEXTCOLOR]	// -- SetTextColor
		MOV EDI, Interface_LogTextColorRtn				// -- Return Func Color
		JMP EDI
	}
}

void __declspec(naked) TextLogColor07()
{
	_asm
	{
		PUSH TextLogColor_07							// Text Color
		MOV EDX,DWORD PTR SS:[EBP-0x4]
		PUSH EDX
		CALL DWORD PTR DS:[INTERFACE_FUNC_SETTEXTCOLOR]	// -- SetTextColor
		MOV EDI, Interface_LogTextColorRtn				// -- Return Func Color
		JMP EDI
	}
}

void __declspec(naked) BackgroundServerInfoDisplayer01()
{
	_asm
	{
		PUSH ServerInfoDisplayerBG
		CALL DWORD PTR DS:[INTERFACE_FUNC_CREATESOLIDBRUSH]
		MOV EDI, Interface_ServerInfoDisplayerBackgroundRtn01
		JMP EDI
	}
}

void __declspec(naked) BackgroundServerInfoDisplayer02()
{
	_asm
	{
		PUSH ServerInfoDisplayerBG
		CALL DWORD PTR DS:[INTERFACE_FUNC_CREATESOLIDBRUSH]
		MOV EDI, Interface_ServerInfoDisplayerBackgroundRtn02
		JMP EDI
	}
}

void __declspec(naked) TextColorServerInfoDisplayer01()
{
	_asm
	{
		PUSH ServerInfoDisplayerText
		MOV ECX,DWORD PTR SS:[EBP-0x8]
		PUSH ECX
		CALL DWORD PTR DS:[INTERFACE_FUNC_SETTEXTCOLOR]	// -- SetTextColor
		MOV EDI, Interface_ServerInfoDisplayerTextRtn01
		JMP EDI
	}
}


void __declspec(naked) GetServersStatus()
{
	_asm
	{
// JOINSERVER OFF
		MOV EAX,DWORD PTR SS:[EBP-0x4]
		CMP DWORD PTR DS:[EAX+0x4],0
		JNZ _GOTOJOINSERVER_ON
		PUSH COLOR_DISCONNECTED							// -- Cor do Texto
		MOV ECX,DWORD PTR SS:[EBP-0x8]
		PUSH ECX
		CALL DWORD PTR DS:[INTERFACE_FUNC_SETTEXTCOLOR]	// -- SetTextColor
		PUSH Interface_ServerStatusText01				// -- Texto
		MOV EDI, INTERFACE_FUNC_SIZEOF					// -- Function Sizeof (Determina o tamanho)
		CALL EDI
		ADD ESP,4
		PUSH EAX										// -- Tamanho
		PUSH Interface_ServerStatusText01				// -- Texto
		PUSH 0x69										// -- Top
		PUSH 0x23										// -- Left
		MOV ECX,DWORD PTR SS:[EBP-0x8]
		PUSH ECX
		CALL DWORD PTR DS:[INTERFACE_FUNC_TEXTOUTA]		// -- TextOutA

// JOINSERVER ON
_GOTOJOINSERVER_ON:
		MOV EAX,DWORD PTR SS:[EBP-0x4]
		CMP DWORD PTR DS:[EAX+0x4],1
		JNZ _GOTOGATESERVER_OFF
		PUSH COLOR_CONNECTED							// -- Cor do Texto
		MOV ECX,DWORD PTR SS:[EBP-0x8]
		PUSH ECX
		CALL DWORD PTR DS:[INTERFACE_FUNC_SETTEXTCOLOR]	// -- SetTextColor
		PUSH Interface_ServerStatusText02				// -- Texto
		MOV EDI, INTERFACE_FUNC_SIZEOF					// -- Function Sizeof (Determina o tamanho)
		CALL EDI
		ADD ESP,4
		PUSH EAX										// -- Tamanho
		PUSH Interface_ServerStatusText02				// -- Texto
		PUSH 0x69										// -- Top
		PUSH 0x23										// -- Left
		MOV ECX,DWORD PTR SS:[EBP-0x8]
		PUSH ECX
		CALL DWORD PTR DS:[INTERFACE_FUNC_TEXTOUTA]		// -- TextOutA

// FSGATESERVER OFF
_GOTOGATESERVER_OFF:
		MOV EAX,DWORD PTR SS:[EBP-0x4]
		CMP DWORD PTR DS:[EAX+0x8],0
		JNZ _GOTOGATESERVER_ON
		PUSH COLOR_DISCONNECTED							// -- Cor do Texto
		MOV ECX,DWORD PTR SS:[EBP-0x8]
		PUSH ECX
		CALL DWORD PTR DS:[INTERFACE_FUNC_SETTEXTCOLOR]	// -- SetTextColor
		PUSH Interface_ServerStatusText03				// -- Texto
		MOV EDI, INTERFACE_FUNC_SIZEOF					// -- Function Sizeof (Determina o tamanho)
		CALL EDI
		ADD ESP,4
		PUSH EAX										// -- Tamanho
		PUSH Interface_ServerStatusText03				// -- Texto
		PUSH 0x69										// -- Top
		PUSH 0x102										// -- Left
		MOV ECX,DWORD PTR SS:[EBP-0x8]
		PUSH ECX
		CALL DWORD PTR DS:[INTERFACE_FUNC_TEXTOUTA]		// -- TextOutA

// FSGATESERVER ON
_GOTOGATESERVER_ON:
		MOV EAX,DWORD PTR SS:[EBP-0x4]
		CMP DWORD PTR DS:[EAX+0x8],1
		JNZ _GOTODATASERVER_OFF
		PUSH COLOR_CONNECTED							// -- Cor do Texto
		MOV ECX,DWORD PTR SS:[EBP-0x8]
		PUSH ECX
		CALL DWORD PTR DS:[INTERFACE_FUNC_SETTEXTCOLOR]	// -- SetTextColor
		PUSH Interface_ServerStatusText04				// -- Texto
		MOV EDI, INTERFACE_FUNC_SIZEOF					// -- Function Sizeof (Determina o tamanho)
		CALL EDI
		ADD ESP,4
		PUSH EAX										// -- Tamanho
		PUSH Interface_ServerStatusText04				// -- Texto
		PUSH 0x69										// -- Top
		PUSH 0x102										// -- Left
		MOV ECX,DWORD PTR SS:[EBP-0x8]
		PUSH ECX
		CALL DWORD PTR DS:[INTERFACE_FUNC_TEXTOUTA]		// -- TextOutA

// DATASERVER OFF
_GOTODATASERVER_OFF:
		MOV EAX,DWORD PTR SS:[EBP-0x4]
		CMP DWORD PTR DS:[EAX+0xC],0
		JNZ _GOTODATASERVER_ON
		PUSH COLOR_DISCONNECTED							// -- Cor do Texto
		MOV ECX,DWORD PTR SS:[EBP-0x8]
		PUSH ECX
		CALL DWORD PTR DS:[INTERFACE_FUNC_SETTEXTCOLOR]	// -- SetTextColor
		PUSH Interface_ServerStatusText05				// -- Texto
		MOV EDI, INTERFACE_FUNC_SIZEOF					// -- Function Sizeof (Determina o tamanho)
		CALL EDI
		ADD ESP,4
		PUSH EAX										// -- Tamanho
		PUSH Interface_ServerStatusText05				// -- Texto
		PUSH 0x69										// -- Top
		PUSH 0x1E0										// -- Left
		MOV ECX,DWORD PTR SS:[EBP-0x8]
		PUSH ECX
		CALL DWORD PTR DS:[INTERFACE_FUNC_TEXTOUTA]		// -- TextOutA

// DATASERVER ON
_GOTODATASERVER_ON:
		MOV EAX,DWORD PTR SS:[EBP-0x4]
		CMP DWORD PTR DS:[EAX+0xC],1
		JNZ _GOTOEXDBSERVER_OFF
		PUSH COLOR_CONNECTED							// -- Cor do Texto
		MOV ECX,DWORD PTR SS:[EBP-0x8]
		PUSH ECX
		CALL DWORD PTR DS:[INTERFACE_FUNC_SETTEXTCOLOR]	// -- SetTextColor
		PUSH Interface_ServerStatusText06				// -- Texto
		MOV EDI, INTERFACE_FUNC_SIZEOF					// -- Function Sizeof (Determina o tamanho)
		CALL EDI
		ADD ESP,4
		PUSH EAX										// -- Tamanho
		PUSH Interface_ServerStatusText06				// -- Texto
		PUSH 0x69										// -- Top
		PUSH 0x1E0										// -- Left
		MOV ECX,DWORD PTR SS:[EBP-0x8]
		PUSH ECX
		CALL DWORD PTR DS:[INTERFACE_FUNC_TEXTOUTA]		// -- TextOutA

// EXDB OFF
_GOTOEXDBSERVER_OFF:
		MOV EAX,DWORD PTR SS:[EBP-0x4]
		CMP DWORD PTR DS:[EAX+0x10],0
		JNZ _GOTOEXDBSERVER_ON
		PUSH COLOR_DISCONNECTED							// -- Cor do Texto
		MOV ECX,DWORD PTR SS:[EBP-0x8]
		PUSH ECX
		CALL DWORD PTR DS:[INTERFACE_FUNC_SETTEXTCOLOR]	// -- SetTextColor
		PUSH Interface_ServerStatusText07				// -- Texto
		MOV EDI, INTERFACE_FUNC_SIZEOF					// -- Function Sizeof (Determina o tamanho)
		CALL EDI
		ADD ESP,4
		PUSH EAX										// -- Tamanho
		PUSH Interface_ServerStatusText07				// -- Texto
		PUSH 0x69										// -- Top
		PUSH 0x2C5										// -- Left
		MOV ECX,DWORD PTR SS:[EBP-0x8]
		PUSH ECX
		CALL DWORD PTR DS:[INTERFACE_FUNC_TEXTOUTA]		// -- TextOutA

// EXDB ON
_GOTOEXDBSERVER_ON:
		MOV EAX,DWORD PTR SS:[EBP-0x4]
		CMP DWORD PTR DS:[EAX+0x10],1
		JNZ _GOTOEVENTSERVER_OFF
		PUSH COLOR_CONNECTED							// -- Cor do Texto
		MOV ECX,DWORD PTR SS:[EBP-0x8]
		PUSH ECX
		CALL DWORD PTR DS:[INTERFACE_FUNC_SETTEXTCOLOR]	// -- SetTextColor
		PUSH Interface_ServerStatusText08				// -- Texto
		MOV EDI, INTERFACE_FUNC_SIZEOF					// -- Function Sizeof (Determina o tamanho)
		CALL EDI
		ADD ESP,4
		PUSH EAX										// -- Tamanho
		PUSH Interface_ServerStatusText08				// -- Texto
		PUSH 0x69										// -- Top
		PUSH 0x2C5										// -- Left
		MOV ECX,DWORD PTR SS:[EBP-0x8]
		PUSH ECX
		CALL DWORD PTR DS:[INTERFACE_FUNC_TEXTOUTA]		// -- TextOutA

// EVENTSERVER OFF
_GOTOEVENTSERVER_OFF:
		MOV EAX,DWORD PTR SS:[EBP-0x4]
		CMP DWORD PTR DS:[EAX+0x14],0
		JNZ _GOTOEVENTSERVER_ON
		PUSH COLOR_DISCONNECTED							// -- Cor do Texto
		MOV ECX,DWORD PTR SS:[EBP-0x8]
		PUSH ECX
		CALL DWORD PTR DS:[INTERFACE_FUNC_SETTEXTCOLOR]	// -- SetTextColor
		PUSH Interface_ServerStatusText09				// -- Texto
		MOV EDI, INTERFACE_FUNC_SIZEOF					// -- Function Sizeof (Determina o tamanho)
		CALL EDI
		ADD ESP,4
		PUSH EAX										// -- Tamanho
		PUSH Interface_ServerStatusText09				// -- Texto
		PUSH 0x69										// -- Top
		PUSH 0x3A9										// -- Left
		MOV ECX,DWORD PTR SS:[EBP-0x8]
		PUSH ECX
		CALL DWORD PTR DS:[INTERFACE_FUNC_TEXTOUTA]		// -- TextOutA

// EVENTSERVER ON
_GOTOEVENTSERVER_ON:
		MOV EAX,DWORD PTR SS:[EBP-0x4]
		CMP DWORD PTR DS:[EAX+0x14],1
		JNZ _GOTORANKINGSERVER_OFF
		PUSH COLOR_CONNECTED							// -- Cor do Texto
		MOV ECX,DWORD PTR SS:[EBP-0x8]
		PUSH ECX
		CALL DWORD PTR DS:[INTERFACE_FUNC_SETTEXTCOLOR]	// -- SetTextColor
		PUSH Interface_ServerStatusText10				// -- Texto
		MOV EDI, INTERFACE_FUNC_SIZEOF					// -- Function Sizeof (Determina o tamanho)
		CALL EDI
		ADD ESP,4
		PUSH EAX										// -- Tamanho
		PUSH Interface_ServerStatusText10				// -- Texto
		PUSH 0x69										// -- Top
		PUSH 0x3A9										// -- Left
		MOV ECX,DWORD PTR SS:[EBP-0x8]
		PUSH ECX
		CALL DWORD PTR DS:[INTERFACE_FUNC_TEXTOUTA]		// -- TextOutA

// RANKINGSERVER OFF
_GOTORANKINGSERVER_OFF:
		MOV EAX,DWORD PTR SS:[EBP-0x4]
		CMP DWORD PTR DS:[EAX+0x18],0
		JNZ _GOTORANKINGSERVER_ON
		PUSH COLOR_DISCONNECTED							// -- Cor do Texto
		MOV ECX,DWORD PTR SS:[EBP-0x8]
		PUSH ECX
		CALL DWORD PTR DS:[INTERFACE_FUNC_SETTEXTCOLOR]	// -- SetTextColor
		PUSH Interface_ServerStatusText11				// -- Texto
		MOV EDI, INTERFACE_FUNC_SIZEOF					// -- Function Sizeof (Determina o tamanho)
		CALL EDI
		ADD ESP,4
		PUSH EAX										// -- Tamanho
		PUSH Interface_ServerStatusText11				// -- Texto
		PUSH 0x69										// -- Top
		PUSH 0x480										// -- Left
		MOV ECX,DWORD PTR SS:[EBP-0x8]
		PUSH ECX
		CALL DWORD PTR DS:[INTERFACE_FUNC_TEXTOUTA]		// -- TextOutA

//RANKINGSERVER ON
_GOTORANKINGSERVER_ON:
		MOV EAX,DWORD PTR SS:[EBP-0x4]
		CMP DWORD PTR DS:[EAX+0x18],1
		JNZ _RTN
		PUSH COLOR_CONNECTED							// -- Cor do Texto
		MOV ECX,DWORD PTR SS:[EBP-0x8]
		PUSH ECX
		CALL DWORD PTR DS:[INTERFACE_FUNC_SETTEXTCOLOR]	// -- SetTextColor
		PUSH Interface_ServerStatusText12				// -- Texto
		MOV EDI, INTERFACE_FUNC_SIZEOF					// -- Function Sizeof (Determina o tamanho)
		CALL EDI
		ADD ESP,4
		PUSH EAX										// -- Tamanho
		PUSH Interface_ServerStatusText12				// -- Texto
		PUSH 0x69										// -- Top
		PUSH 0x480										// -- Left
		MOV ECX,DWORD PTR SS:[EBP-0x8]
		PUSH ECX
		CALL DWORD PTR DS:[INTERFACE_FUNC_TEXTOUTA]		// -- TextOutA

// RETURN
_RTN:
		MOV EDI, Interface_ServerStatusRtn
		JMP EDI
	}
}

void InterfaceLoad()
{
	// -- Background Color
	Utilits.SetByte(Interface_BackgroundColor01, 0xE9);
	Utilits.HookThis((DWORD)&BackgroundColor, Interface_BackgroundColor01);

	Utilits.SetByte(Interface_BackgroundColor02, 0xE9);
	Utilits.HookThis((DWORD)&BackgroundColorFix01, Interface_BackgroundColor02);

	Utilits.SetByte(Interface_BackgroundColor03, 0xE9);
	Utilits.HookThis((DWORD)&BackgroundColorFix02, Interface_BackgroundColor03);
	
	// -- Log Text Color
	Utilits.SetByte(Interface_LogTextColor01, 0xE9);
	Utilits.HookThis((DWORD)&TextLogColor01, Interface_LogTextColor01);

	Utilits.SetByte(Interface_LogTextColor02, 0xE9);
	Utilits.HookThis((DWORD)&TextLogColor02, Interface_LogTextColor02);

	Utilits.SetByte(Interface_LogTextColor03, 0xE9);
	Utilits.HookThis((DWORD)&TextLogColor03, Interface_LogTextColor03);

	Utilits.SetByte(Interface_LogTextColor04, 0xE9);
	Utilits.HookThis((DWORD)&TextLogColor04, Interface_LogTextColor04);

	Utilits.SetByte(Interface_LogTextColor05, 0xE9);
	Utilits.HookThis((DWORD)&TextLogColor05, Interface_LogTextColor05);

	Utilits.SetByte(Interface_LogTextColor06, 0xE9);
	Utilits.HookThis((DWORD)&TextLogColor06, Interface_LogTextColor06);

	Utilits.SetByte(Interface_LogTextColor07, 0xE9);
	Utilits.HookThis((DWORD)&TextLogColor07, Interface_LogTextColor07);

	// -- ServerInfoDisplayer
	Utilits.SetByte(Interface_ServerInfoDisplayerFontFix01, 0x00);

	Utilits.SetByte(Interface_ServerInfoDisplayerBackground01, 0xE9);
	Utilits.HookThis((DWORD)&BackgroundServerInfoDisplayer01, Interface_ServerInfoDisplayerBackground01);

	Utilits.SetByte(Interface_ServerInfoDisplayerBackground02, 0xE9);
	Utilits.HookThis((DWORD)&BackgroundServerInfoDisplayer02, Interface_ServerInfoDisplayerBackground02);

	Utilits.SetByte(Interface_ServerInfoDisplayerText01, 0xE9);
	Utilits.HookThis((DWORD)&TextColorServerInfoDisplayer01, Interface_ServerInfoDisplayerText01);

	DWORD *OffSetDisplayText = (DWORD*)(Interface_ServerInfoDisplayerTitle);
    memset(&OffSetDisplayText[0],0,30);

#ifdef _GS
	memcpy(&OffSetDisplayText[0],DISPLAY_TEXT[0],strlen(DISPLAY_TEXT[0]));
#else
	memcpy(&OffSetDisplayText[0],DISPLAY_TEXT[1],strlen(DISPLAY_TEXT[1]));
#endif
	
	//-- Test
	Utilits.SetByte(Interface_LogRealocate, 0x7D);
	
	Utilits.SetByte(Interface_ServerStatus, 0xE9);
	Utilits.HookThis((DWORD)&GetServersStatus, Interface_ServerStatus);

	DWORD *JoinServerOff = (DWORD*)(Interface_ServerStatusText01);
    memset(&JoinServerOff[0],0,32);
    memcpy(&JoinServerOff[0],SERVER_STATUS[0],strlen(SERVER_STATUS[0]));

	DWORD *JoinServerOn = (DWORD*)(Interface_ServerStatusText02);
    memset(&JoinServerOn[0],0,32);
    memcpy(&JoinServerOn[0],SERVER_STATUS[1],strlen(SERVER_STATUS[1]));
	
	DWORD *GateServerOff = (DWORD*)(Interface_ServerStatusText03);
    memset(&GateServerOff[0],0,32);
    memcpy(&GateServerOff[0],SERVER_STATUS[2],strlen(SERVER_STATUS[2]));

	DWORD *GateServerOn = (DWORD*)(Interface_ServerStatusText04);
    memset(&GateServerOn[0],0,32);
    memcpy(&GateServerOn[0],SERVER_STATUS[3],strlen(SERVER_STATUS[3]));

	DWORD *DataServerOff = (DWORD*)(Interface_ServerStatusText05);
    memset(&DataServerOff[0],0,32);
    memcpy(&DataServerOff[0],SERVER_STATUS[4],strlen(SERVER_STATUS[4]));

	DWORD *DataServerOn = (DWORD*)(Interface_ServerStatusText06);
    memset(&DataServerOn[0],0,32);
    memcpy(&DataServerOn[0],SERVER_STATUS[5],strlen(SERVER_STATUS[5]));

	DWORD *ExDBServerOff = (DWORD*)(Interface_ServerStatusText07);
    memset(&ExDBServerOff[0],0,32);
    memcpy(&ExDBServerOff[0],SERVER_STATUS[6],strlen(SERVER_STATUS[6]));

	DWORD *ExDBServerOn = (DWORD*)(Interface_ServerStatusText08);
    memset(&ExDBServerOn[0],0,32);
    memcpy(&ExDBServerOn[0],SERVER_STATUS[7],strlen(SERVER_STATUS[7]));

	DWORD *EventServerOff = (DWORD*)(Interface_ServerStatusText09);
    memset(&EventServerOff[0],0,32);
    memcpy(&EventServerOff[0],SERVER_STATUS[8],strlen(SERVER_STATUS[8]));

	DWORD *EventServerOn = (DWORD*)(Interface_ServerStatusText10);
    memset(&EventServerOn[0],0,32);
    memcpy(&EventServerOn[0],SERVER_STATUS[9],strlen(SERVER_STATUS[9]));

	DWORD *RankingServerOff = (DWORD*)(Interface_ServerStatusText11);
    memset(&RankingServerOff[0],0,32);
    memcpy(&RankingServerOff[0],SERVER_STATUS[10],strlen(SERVER_STATUS[10]));

	DWORD *RankingServerOn = (DWORD*)(Interface_ServerStatusText12);
    memset(&RankingServerOn[0],0,32);
    memcpy(&RankingServerOn[0],SERVER_STATUS[11],strlen(SERVER_STATUS[11]));
}