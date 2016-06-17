/***
*
*	Copyright (c) 1996-2001, Valve LLC. All rights reserved.
*
*	This product contains software technology licensed from Id
*	Software, Inc. ("Id Technology").  Id Technology (c) 1996 Id Software, Inc.
*	All Rights Reserved.
*
*   Use, distribution, and modification of this source code and/or resulting
*   object code is restricted to non-commercial enhancements to products from
*   Valve LLC.  All other use, distribution, or modification is prohibited
*   without written permission from Valve LLC.
*
****/
#ifndef GAME_SHARED_ENTITIES_WEAPONS_CGLOCK_H
#define GAME_SHARED_ENTITIES_WEAPONS_CGLOCK_H

class CGlock : public CBasePlayerWeapon
{
public:
	DECLARE_CLASS( CGlock, CBasePlayerWeapon );

	void Spawn( void ) override;
	void Precache( void ) override;
	int iItemSlot( void ) override { return 2; }
	bool GetItemInfo( ItemInfo* p ) override;

	void PrimaryAttack( void ) override;
	void SecondaryAttack( void ) override;
	void GlockFire( float flSpread, float flCycleTime, const bool fUseAutoAim );
	bool Deploy() override;
	void Reload( void ) override;
	void WeaponIdle( void ) override;

	virtual bool UseDecrement() const override
	{
#if defined( CLIENT_WEAPONS )
		return true;
#else
		return false;
#endif
	}

private:
	int m_iShell;


	unsigned short m_usFireGlock1;
	unsigned short m_usFireGlock2;
};

#endif //GAME_SHARED_ENTITIES_WEAPONS_CGLOCK_H