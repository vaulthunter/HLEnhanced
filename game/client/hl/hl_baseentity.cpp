/***
*
*	Copyright (c) 1996-2002, Valve LLC. All rights reserved.
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

/*
==========================
This file contains "stubs" of class member implementations so that we can predict certain
 weapons client side.  From time to time you might find that you need to implement part of the
 these functions.  If so, cut it from here, paste it in hl_weapons.cpp or somewhere else and
 add in the functionality you need.
==========================
*/
#include	"extdll.h"
#include	"util.h"
#include	"cbase.h"
#include	"entities/CBasePlayer.h"
#include	"Weapons.h"
#include	"nodes/Nodes.h"
#include	"entities/CSoundEnt.h"
#include	"Skill.h"

// Globals used by game logic
int gmsgWeapPickup = 0;
enginefuncs_t g_engfuncs;
globalvars_t  *gpGlobals;

ItemInfo CBasePlayerItem::ItemInfoArray[MAX_WEAPONS];

void EMIT_SOUND_DYN(edict_t *entity, int channel, const char *sample, float volume, float attenuation, int flags, int pitch) { }

// DEBUG Stubs
edict_t *DBG_EntOfVars( const entvars_t *pev ) { return nullptr; }

// UTIL_* Stubs
void UTIL_PrecacheOther( const char *szClassname ) { }
void UTIL_BloodDrips( const Vector &origin, const Vector &direction, int color, int amount ) { }
void UTIL_DecalTrace( TraceResult *pTrace, int decalNumber ) { }
void UTIL_GunshotDecalTrace( TraceResult *pTrace, int decalNumber ) { }
void UTIL_MakeVectors( const Vector &vecAngles ) { }
bool UTIL_IsValidEntity( edict_t *pent ) { return true; }
void UTIL_SetOrigin( entvars_t *, const Vector &org ) { }
bool UTIL_GetNextBestWeapon( CBasePlayer *pPlayer, CBasePlayerItem *pCurrentWeapon ) { return true; }
void UTIL_LogPrintf(char *,...) { }
void UTIL_ClientPrintAll( int,char const *,char const *,char const *,char const *,char const *) { }
void ClientPrint( entvars_t *client, int msg_dest, const char *msg_name, const char *param1, const char *param2, const char *param3, const char *param4 ) { }

void UTIL_Remove( CBaseEntity *pEntity ){ }
struct skilldata_t  gSkillData;
void UTIL_SetSize( entvars_t *pev, const Vector &vecMin, const Vector &vecMax ){ }
CBaseEntity *UTIL_FindEntityInSphere( CBaseEntity *pStartEntity, const Vector &vecCenter, float flRadius ){ return 0;}

int TrainSpeed(int iSpeed, int iMax) { 	return 0; }
CBaseEntity *FindEntityForward( CBaseEntity *pMe ) { return nullptr; }

void SpawnBlood(Vector vecSpot, int bloodColor, float flDamage) { }
int DamageDecal( CBaseEntity *pEntity, int bitsDamageType ) { return 0; }
void DecalGunshot( TraceResult *pTrace, int iBulletType ) { }
void EjectBrass ( const Vector &vecOrigin, const Vector &vecVelocity, float rotation, int model, int soundtype ) { }
void CBasePlayerAmmo::Spawn( void ) { }
CBaseEntity* CBasePlayerAmmo::Respawn( void ) { return this; }
void CBasePlayerAmmo::Materialize( void ) { }
void CBasePlayerAmmo :: DefaultTouch( CBaseEntity *pOther ) { }
void CSoundEnt::InsertSound ( int iType, const Vector &vecOrigin, int iVolume, float flDuration ) {}
void RadiusDamage( Vector vecSrc, CBaseEntity* pInflictor, CBaseEntity* pAttacker, float flDamage, float flRadius, int iClassIgnore, int bitsDamageType ) {}

bool UTIL_GiveAmmoToPlayer( CBaseEntity* pGiver, CBaseEntity* pPlayer,
							const int iAmount, const char* const pszAmmoName,
							const char* const pszPickupSound )
{
	return false;
}

/*
=====================
UTIL_TraceLine

Don't actually trace, but act like the trace didn't hit anything.
=====================
*/
void UTIL_TraceLine( const Vector& vecStart, const Vector& vecEnd, IGNORE_MONSTERS igmon, edict_t* pentIgnore, TraceResult* ptr )
{
	memset( ptr, 0, sizeof( *ptr ) );
	ptr->flFraction = 1.0;
}