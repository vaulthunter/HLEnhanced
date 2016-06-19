#include "extdll.h"
#include "util.h"
#include "cbase.h"
#include "Effects.h"

#include "CFuncTankLaser.h"

BEGIN_DATADESC( CFuncTankLaser )
	DEFINE_FIELD( m_pLaser, FIELD_CLASSPTR ),
	DEFINE_FIELD( m_laserTime, FIELD_TIME ),
END_DATADESC()

LINK_ENTITY_TO_CLASS( func_tanklaser, CFuncTankLaser );

void CFuncTankLaser::Activate( void )
{
	if( !GetLaser() )
	{
		UTIL_Remove( this );
		ALERT( at_error, "Laser tank with no env_laser!\n" );
	}
	else
	{
		m_pLaser->TurnOff();
	}
}

void CFuncTankLaser::KeyValue( KeyValueData *pkvd )
{
	if( FStrEq( pkvd->szKeyName, "laserentity" ) )
	{
		pev->message = ALLOC_STRING( pkvd->szValue );
		pkvd->fHandled = true;
	}
	else
		CFuncTank::KeyValue( pkvd );
}

void CFuncTankLaser::Fire( const Vector &barrelEnd, const Vector &forward, entvars_t *pevAttacker )
{
	int i;
	TraceResult tr;

	if( m_fireLast != 0 && GetLaser() )
	{
		// TankTrace needs gpGlobals->v_up, etc.
		UTIL_MakeAimVectors( pev->angles );

		int bulletCount = ( gpGlobals->time - m_fireLast ) * m_fireRate;
		if( bulletCount )
		{
			for( i = 0; i < bulletCount; i++ )
			{
				m_pLaser->pev->origin = barrelEnd;
				TankTrace( barrelEnd, forward, gTankSpread[ m_spread ], tr );

				m_laserTime = gpGlobals->time;
				m_pLaser->TurnOn();
				m_pLaser->pev->dmgtime = gpGlobals->time - 1.0;
				m_pLaser->FireAtPoint( tr );
				m_pLaser->pev->nextthink = 0;
			}
			CFuncTank::Fire( barrelEnd, forward, pev );
		}
	}
	else
	{
		CFuncTank::Fire( barrelEnd, forward, pev );
	}
}

void CFuncTankLaser::Think( void )
{
	if( m_pLaser && ( gpGlobals->time > m_laserTime ) )
		m_pLaser->TurnOff();

	CFuncTank::Think();
}

CLaser *CFuncTankLaser::GetLaser( void )
{
	if( m_pLaser )
		return m_pLaser;

	edict_t	*pentLaser;

	pentLaser = FIND_ENTITY_BY_TARGETNAME( NULL, STRING( pev->message ) );
	while( !FNullEnt( pentLaser ) )
	{
		// Found the landmark
		if( FClassnameIs( pentLaser, "env_laser" ) )
		{
			m_pLaser = ( CLaser * ) CBaseEntity::Instance( pentLaser );
			break;
		}
		else
			pentLaser = FIND_ENTITY_BY_TARGETNAME( pentLaser, STRING( pev->message ) );
	}

	return m_pLaser;
}