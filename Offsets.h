

#ifndef OFFSETS_HEADER
#define OFFSETS_HEADER

DWORD ClientDLL;
DWORD EngineDLL;

class Offsets
{
public:

	DWORD gEntityList()
	{
		return EntityList;
	}

	DWORD gLocalPlayer()
	{
		return LocalPlayer;
	}

	DWORD gFlashDuration()
	{
		return FlashDuration;
	}

	DWORD gRadarBase()
	{
		return RadarBase;
	}

	DWORD gServerBase()
	{
		return ServerBase;
	}

	DWORD gEnginePointer()
	{
		return EnginePointer;
	}

	DWORD gSetViewAngles()
	{
		return SetViewAngles;
	}

	DWORD gCrosshairIndex()
	{
		return CrosshairIndex;
	}

	DWORD gGlowObjectBase()
	{
		return GlowObjectBase;
	}

	DWORD gViewMatrix1()
	{
		return ViewMatrix1;
	}

	DWORD gViewMatrix2()
	{
		return ViewMatrix2;
	}

	DWORD gViewMatrix3()
	{
		return ViewMatrix3;
	}

	DWORD gVecViewOrigin()
	{
		return VecViewOrigin;
	}

	DWORD gVecOrigin()
	{
		return VecOrigin;
	}

	DWORD gVecPunch()
	{
		return VecPunch;
	}

	DWORD gTeamNum()
	{
		return TeamNum;
	}

	DWORD gShotsFired()
	{
		return ShotsFired;
	}

	DWORD gFlags()
	{
		return Flags;
	}

	DWORD gDwBoneMatrix()
	{
		return DwBoneMatrix;
	}

	DWORD gHealth()
	{
		return Health;
	}

	DWORD gLifeState()
	{
		return LifeState;
	}

	DWORD gVecVelocity()
	{
		return VecVelocity;
	}

	DWORD gDwEntitySize()
	{
		return DwEntitySize;
	}

	DWORD gbDormant()
	{
		return bDormant;
	}

	DWORD gbSpotted()
	{
		return bSpotted;
	}

	DWORD gGlowIndex()
	{
		return GlowIndex;
	}

	DWORD ghActiveWeapon()
	{
		return hActiveWeapon;
	}

	DWORD gdwActiveWeaponID()
	{
		return dwActiveWeaponID;
	}

private:
	const DWORD EntityList = 0x4A1D3A4;
	const DWORD hActiveWeapon = 0x12C0;
	const DWORD LocalPlayer = 0xA7AFBC;
	const DWORD FlashDuration = 0x1DB4;
	const DWORD RadarBase = 0x4A5204C;
	const DWORD ServerBase = 0x4A64280;
	const DWORD EnginePointer = 0x5D0214;
	const DWORD SetViewAngles = 0x4CE0;
	const DWORD CrosshairIndex = 0x2410;
	const DWORD GlowObjectBase = 0x4B303A4;
	const DWORD ViewMatrix1 = 0xE42D0058;
	const DWORD ViewMatrix2 = 0xE42D0168;
	const DWORD dwActiveWeaponID = 0x1690;
	const DWORD ViewMatrix3 = 0xE42D0478; //-=-=-=-=-=-=-=-=-=-=-=

	const DWORD VecViewOrigin = 0x104;
	const DWORD VecOrigin = 0x134;
	const DWORD VecPunch = 0x13E8;
	const DWORD TeamNum = 0xF0;
	const DWORD ShotsFired = 0x1D60;
	const DWORD Flags = 0x100;
	const DWORD GlowIndex = 0x1DCC;
	const DWORD DwBoneMatrix = 0xA78;
	const DWORD Health = 0xFC;
	const DWORD LifeState = 0x25B;
	const DWORD DwEntitySize = 0x10;
	const DWORD bDormant = 0xE9;
	const DWORD bSpotted = 0x935;
	const DWORD VecVelocity = 0x110;	 //-=-=-=-=-=-=-=-=-=-=-=

}gOffsets;


enum CSGO_Weapon_ID
{
	weapon_none,
	weapon_deagle,
	weapon_elite,
	weapon_fiveseven,
	weapon_glock,
	weapon_p228,
	weapon_usp,
	weapon_ak47,
	weapon_aug,
	weapon_awp,
	weapon_famas,
	weapon_g3sg1,
	weapon_galil,
	weapon_galilar,
	weapon_m249,
	weapon_m3,
	weapon_m4a1,
	weapon_mac10,
	weapon_mp5navy,
	weapon_p90,
	weapon_scout,
	weapon_sg550,
	weapon_sg552,
	weapon_tmp,
	weapon_ump45,
	weapon_xm1014,
	weapon_bizon,
	weapon_mag7,
	weapon_negev,
	weapon_sawedoff,
	weapon_tec9,
	weapon_taser,
	weapon_hkp2000,
	weapon_mp7,
	weapon_mp9,
	weapon_nova,
	weapon_p250,
	weapon_scar17,
	weapon_scar20,
	weapon_sg556,
	weapon_ssg08,
	weapon_knifegg,
	weapon_knife,
	weapon_flashbang,
	weapon_hegrenade,
	weapon_smokegrenade,
	weapon_molotov,
	weapon_decoy,
	weapon_incgrenade,
	weapon_c4
};
#endif