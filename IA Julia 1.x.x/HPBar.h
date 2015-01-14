#ifndef HPBAR_H
#define HPBAR_H

#include "StdAfx.h"
#include "Configs.h"
#include "User.h"
#include "Prodef.h"

struct PMSG_ATTACKRESULT
{
	PBMSG_HEAD h; // C1:DC

	BYTE NumberH; // 3
	BYTE NumberL; // 4
	BYTE DamageH; // 5
	BYTE DamageL; // 6
	BYTE DamageType; // 7
	BYTE btShieldDamageH; // 8
	BYTE btShieldDamageL; // 9

	float Life; //A
	float MaxLife; //E
	float AddLife; //Inner bug hp bar fix.
};

void GCDamageSend(int aIndex, int TargetIndex, int AttackDamage, int MSBFlag, int MSBDamage, int iShieldDamage);

// Enviar dano para o cliente (Apenas GS??) [HP Bar]
#define lpGCDamageSend ((void(*)(int aIndex, int TargetIndex, int AttackDamage, int MSBFlag, int MSBDamage, int iShieldDamage)) 0x00455CB0)

#endif