#include "HPBar.h"
#include "StdAfx.h"
#include "Utilits.h"

void GCDamageSend(int aIndex,int TargetIndex,int AttackDamage,int MSBFlag,int MSBDamage,int iShieldDamage)
{
	PMSG_ATTACKRESULT pResult;

#if (IS_PROTOCOL_JPN == 0)
	PHeadSetB((LPBYTE)&pResult,0x11,sizeof(pResult));	// (1.03P 1.03.16 main)
#else
	PHeadSetB((LPBYTE)&pResult,0xDC,sizeof(pResult));	// (1.03K 1.03.11 main)
#endif

	pResult.NumberH = SET_NUMBERH(TargetIndex);
	pResult.NumberL = SET_NUMBERL(TargetIndex);
	pResult.DamageH = SET_NUMBERH(AttackDamage);
	pResult.DamageL = SET_NUMBERL(AttackDamage);

	pResult.btShieldDamageH = SET_NUMBERH(iShieldDamage);
	pResult.btShieldDamageL = SET_NUMBERL(iShieldDamage);

	if(MSBFlag != false)
	{
		pResult.NumberH &= 0x7F;
		pResult.NumberH |= 0x80;
	}

	pResult.DamageType = MSBDamage;

	OBJECTSTRUCT * gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);
	OBJECTSTRUCT * gTarg = (OBJECTSTRUCT*)OBJECT_POINTER(TargetIndex);

	pResult.Life = gTarg->Life;
	pResult.MaxLife = gTarg->MaxLife + gTarg->AddLife;

	if(gTarg->Type == OBJECT_MONSTER)
	{
		pResult.Life = gTarg->Life;
		pResult.MaxLife = gTarg->MaxLife + gTarg->AddLife;
	}

	if(gTarg->Type == OBJECT_USER)
	{
		DataSend(TargetIndex, (LPBYTE)&pResult, pResult.h.size);
	}

	if(gObj->Type == OBJECT_USER)
	{
		DataSend(aIndex, (LPBYTE)&pResult, pResult.h.size);
	}

	lpGCDamageSend(aIndex, TargetIndex, AttackDamage, MSBFlag, MSBDamage, iShieldDamage);
}