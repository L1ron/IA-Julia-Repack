#ifndef STDAFX_H
#define STDAFX_H

#pragma once

/////////////////////////////////
// ALTERAR PROTOCOLO
// 0 ENG, 1 JPN
/////////////////////////////////
#define IS_PROTOCOL_JPN 1

#include "Resource.h"

#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_DEPRECATE

// Windows Header Files:
#include <windows.h>
#include <winsock2.h>
#include <commctrl.h>
#include <sql.h>
#include <sqltypes.h>
#include <sqlext.h>
#include <Rpc.h>

#pragma comment(lib,"Rpcrt4.lib")
#pragma comment(lib,"comctl32.lib")
#pragma comment(lib,"WS2_32.lib")

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <time.h>
#include <stdio.h>
#include <vector>
#include <map>
#include <process.h>
#include <algorithm>
#include <math.h>
#include <atltime.h>
#include <string>
#include <string.h>
#endif