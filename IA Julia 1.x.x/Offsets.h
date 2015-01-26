#ifndef _OFFSET_H_
#define _OFFSET_H_

//-----------------------------------------------------
// -- GameServer Protodef
//-----------------------------------------------------
#ifdef _GS

// -- Interface Offsets
#define Interface_BackgroundColor01 0x0057A97C
#define Interface_BackgroundColor02 0x004C15C6
#define Interface_BackgroundColor03 0x00528364
#define Interface_BackgroundColorRtn01 0x0057A993
#define Interface_BackgroundColorRtn02 0x004C15CD
#define Interface_BackgroundColorRtn03 0x00528369

#define Interface_LogTextColor01 0x004C1611
#define Interface_LogTextColor02 0x004C1622
#define Interface_LogTextColor03 0x004C1633
#define Interface_LogTextColor04 0x004C1644
#define Interface_LogTextColor05 0x004C1655
#define Interface_LogTextColor06 0x004C1666
#define Interface_LogTextColor07 0x004C1677
#define Interface_LogTextColorRtn 0x004C1683

#define Interface_ServerInfoDisplayerTitle 0x0077D728
#define Interface_ServerInfoDisplayerFontFix01 0x004C687E

#define Interface_ServerInfoDisplayerBackground01 0x004C6897
#define Interface_ServerInfoDisplayerBackground02 0x004C68A8
#define Interface_ServerInfoDisplayerBackgroundRtn02 0x004C68B3
#define Interface_ServerInfoDisplayerBackgroundRtn01 0x004C68A2

#define Interface_ServerInfoDisplayerText01 0x004C6E67
#define Interface_ServerInfoDisplayerTextRtn01 0x004C6E76

#define Interface_LogRealocate 0x004C16C7

#define Interface_ServerStatus 0x004C6C02
#define Interface_ServerStatusRtn 0x004C6DE8

#define Interface_ServerStatusText01 0x0065302D
#define Interface_ServerStatusText02 0x0065304D
#define Interface_ServerStatusText03 0x0065306D
#define Interface_ServerStatusText04 0x0065308D
#define Interface_ServerStatusText05 0x006530AD
#define Interface_ServerStatusText06 0x006530CD
#define Interface_ServerStatusText07 0x006530ED
#define Interface_ServerStatusText08 0x0065310D
#define Interface_ServerStatusText09 0x0065313D
#define Interface_ServerStatusText10 0x0065315D
#define Interface_ServerStatusText11 0x0065317D
#define Interface_ServerStatusText12 0x0065319D


//-----------------------------------------------------
// -- Castle Protodef
//-----------------------------------------------------
#else

// -- Interface
#define Interface_BackgroundColor01 0x0058DC05
#define Interface_BackgroundColor02 0x004D2566
#define Interface_BackgroundColor03 0x0053A944
#define Interface_BackgroundColorRtn01 0x0058DC1C
#define Interface_BackgroundColorRtn02 0x004D256D
#define Interface_BackgroundColorRtn03 0x0053A949

#define Interface_LogTextColor01 0x004D25B1
#define Interface_LogTextColor02 0x004D25C2
#define Interface_LogTextColor03 0x004D25D3
#define Interface_LogTextColor04 0x004D25E4
#define Interface_LogTextColor05 0x004D25F5
#define Interface_LogTextColor06 0x004D2606
#define Interface_LogTextColor07 0x004D2617
#define Interface_LogTextColorRtn 0x004D2623

#define Interface_ServerInfoDisplayerTitle 0x007D1DD0
#define Interface_ServerInfoDisplayerFontFix01 0x004D781E

#define Interface_ServerInfoDisplayerBackground01 0x004D7837
#define Interface_ServerInfoDisplayerBackground02 0x004D7848
#define Interface_ServerInfoDisplayerBackgroundRtn01 0x004D7842
#define Interface_ServerInfoDisplayerBackgroundRtn02 0x004D7853

#define Interface_ServerInfoDisplayerText01 0x004D7E07
#define Interface_ServerInfoDisplayerTextRtn01 0x004D7E16

#define Interface_LogRealocate 0x004D2667

#define Interface_ServerStatus 0x004D7BA2
#define Interface_ServerStatusRtn 0x004D7D88

#define Interface_ServerStatusText01 0x0069501D
#define Interface_ServerStatusText02 0x0069503D
#define Interface_ServerStatusText03 0x0069505D
#define Interface_ServerStatusText04 0x0069507D
#define Interface_ServerStatusText05 0x0069509D
#define Interface_ServerStatusText06 0x006950BD
#define Interface_ServerStatusText07 0x006950DD
#define Interface_ServerStatusText08 0x006950FD
#define Interface_ServerStatusText09 0x0069512D
#define Interface_ServerStatusText10 0x0069514D
#define Interface_ServerStatusText11 0x0069516D
#define Interface_ServerStatusText12 0x0069518D

#endif

#endif