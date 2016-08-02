#ifndef GAME_SHARED_CWEAPONINFOCACHE_H
#define GAME_SHARED_CWEAPONINFOCACHE_H

#include <memory>
#include <unordered_map>

#include "StringUtils.h"

#include "CWeaponInfo.h"

/**
*	Singleton class that caches weapon info.
*/
class CWeaponInfoCache final
{
public:
	static const char* const WEAPON_INFO_DIR;

	/**
	*	Callback used to enumerate weapon info.
	*	@param info Weapon info.
	*	@param pUserData User data.
	*	@return true to continue enumerating, false to stop.
	*/
	using EnumInfoCallback = bool ( * )( const CWeaponInfo& info, void* pUserData );

private:
	typedef std::unordered_map<const char*, std::unique_ptr<CWeaponInfo>, RawCharHashI, RawCharEqualToI> Infos_t;

public:
	CWeaponInfoCache() = default;
	~CWeaponInfoCache() = default;

	/**
	*	Finds weapon info by weapon name.
	*	@param pszWeaponName Name of the weapon.
	*	@return If found, the weapon info. Otherwise, null.
	*/
	const CWeaponInfo* FindWeaponInfo( const char* const pszWeaponName ) const;

	/**
	*	Loads weapon info for the given weapon name.
	*	@param iID Weapon ID.
	*	@param pszWeaponName Name of the weapon whose info should be loaded.
	*	@param pszSubDir Optional. Subdirectory to check.
	*	@return Weapon info instance.
	*/
	const CWeaponInfo* LoadWeaponInfo( const int iID, const char* const pszWeaponName, const char* const pszSubDir = nullptr );

	/**
	*	Clears all info.
	*/
	void ClearInfos();

	/**
	*	Enumerate weapon info.
	*	@param pCallback Callback to invoke on every weapon info instance.
	*	@param pUserData User data to pass.
	*/
	void EnumInfos( EnumInfoCallback pCallback, void* pUserData = nullptr ) const;

private:
	/**
	*	Loads weapon info from a file.
	*	@param pszWeaponName Name of the weapon whose info should be loaded.
	*	@param pszSubDir Optional. Subdirectory to check.
	*	@param info Weapon info structure to initialize.
	*	@return true on success, false otherwise.
	*/
	bool LoadWeaponInfoFromFile( const char* const pszWeaponName, const char* const pszSubDir, CWeaponInfo& info );

private:
	Infos_t m_Infos;

	//Used when a file failed to load.
	CWeaponInfo m_DefaultInfo;

private:
	CWeaponInfoCache( const CWeaponInfoCache& ) = delete;
	CWeaponInfoCache& operator=( const CWeaponInfoCache& ) = delete;
};

extern CWeaponInfoCache g_WeaponInfoCache;

#endif //GAME_SHARED_CWEAPONINFOCACHE_H