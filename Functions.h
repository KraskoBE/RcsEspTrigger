#include "Memory.h"
#include "Offsets.h"
#include <windows.h>
#include <cstdio>
#include <conio.h>
#include <FCNTL.H>
#include <io.h>
#include <iostream>
#include <string>
#include <sstream>
#include <random>
#include <stdint.h>
#include "Colors.h"

struct
{
	DWORD gPlayerBase()
	{
		return gMemory->Read<DWORD>(ClientDLL + gOffsets.gLocalPlayer());
	}

	int gTeam()
	{
		DWORD PlayerBase = gPlayerBase();
		return gMemory->Read<int>(PlayerBase + gOffsets.gTeamNum());
	}

	int gCrosshairID()
	{
		DWORD PlayerBase = gPlayerBase();
		return gMemory->Read<int>(PlayerBase + gOffsets.gCrosshairIndex()) - 1;
	}

	void gVelocity(float* Buffer)
	{
		DWORD PlayerBase = gPlayerBase();
		if (PlayerBase)
		{
			Buffer = gMemory->Read<float*>(PlayerBase + gOffsets.gVecVelocity());
		}
	}

	void gAngles(float* Angles)
	{
		DWORD AnglePointer = gMemory->Read<DWORD>(EngineDLL + gOffsets.gEnginePointer());
		if (AnglePointer)
		{
			Angles = gMemory->Read<float*>(AnglePointer + gOffsets.gSetViewAngles());
		}
	}

	void sAngles(float* Angles)
	{
		DWORD AnglePointer = gMemory->Read<DWORD>(EngineDLL + gOffsets.gEnginePointer());
		if (AnglePointer)
		{
			gMemory->Write<float*>(AnglePointer + gOffsets.gSetViewAngles(), Angles);
		}
	}

	void gPunch(float* Punch)
	{
		DWORD PlayerBase = gPlayerBase();
		if (PlayerBase)
		{
			Punch = gMemory->Read<float*>(PlayerBase + gOffsets.gVecPunch());
		}
	}

	float gViewOrigin()
	{
		DWORD PlayerBase = gPlayerBase();
		if (PlayerBase)
		{
			float Vecview[3];
			Vecview[2] = gMemory->Read<float>(PlayerBase + gOffsets.gVecViewOrigin() + 0x4);
			return Vecview[2];
		}
	}

	void gPosition(float* Position)
	{
		DWORD PlayerBase = gPlayerBase();
		if (PlayerBase)
		{
			Position = gMemory->Read<float*>(PlayerBase + gOffsets.gVecViewOrigin());
		}
	}

	int gShotsFired()
	{
		DWORD PlayerBase = gPlayerBase();
		if (PlayerBase)
		{
			return gMemory->Read<int>(PlayerBase + gOffsets.gShotsFired());
		}
	}

	int gfFlags()
	{
		DWORD PlayerBase = gPlayerBase();
		if (PlayerBase)
		{
			return gMemory->Read<int>(PlayerBase + gOffsets.gFlags());
		}
	}

	bool gIsDead()
	{
		DWORD PlayerBase = gPlayerBase();
		return gMemory->Read<bool>(PlayerBase + gOffsets.gLifeState());
	}

	void sJump()
	{
		gMemory->Write<int>(ClientDLL + gOffsets.gjumpOffset(), 5);
		Sleep(20);
		gMemory->Write<int>(ClientDLL + gOffsets.gjumpOffset(), 4);
	}
}Player;


struct
{
	DWORD gEntityBase(int PlayerNum)
	{
		return gMemory->Read<DWORD>(ClientDLL + gOffsets.gEntityList() + (gOffsets.gDwEntitySize() * PlayerNum));
	}

	bool gisDead(int PlayerNum)
	{
		DWORD EntityBase = gEntityBase(PlayerNum);
		return gMemory->Read<bool>(EntityBase + gOffsets.gLifeState());
	}

	int gTeam(int PlayerNum)
	{
		DWORD EntityBase = gEntityBase(PlayerNum);
		return gMemory->Read<int>(EntityBase + gOffsets.gTeamNum());
	}

	void gVelocity(int PlayerNumber, float* Buffer)
	{
		DWORD BaseEntity = gEntityBase(PlayerNumber);
		if (BaseEntity)
		{
			Buffer = gMemory->Read<float*>(BaseEntity + gOffsets.gVecVelocity());
		}
	}

	void gBonePosition(int PlayerNumber, int TargetBone, float* BonePosition)
	{
		DWORD BaseEntity = gEntityBase(PlayerNumber);
		if (BaseEntity)
		{
			DWORD BoneMatrix = gMemory->Read<DWORD>(BaseEntity + gOffsets.gDwBoneMatrix());
			if (BoneMatrix)
			{
				BonePosition[0] = gMemory->Read<float>(BoneMatrix + 0x30 * TargetBone + 0x0C);
				BonePosition[1] = gMemory->Read<float>(BoneMatrix + 0x30 * TargetBone + 0x1C);
				BonePosition[2] = gMemory->Read<float>(BoneMatrix + 0x30 * TargetBone + 0x2C);
			}
		}
	}

	DWORD gGlowPointer()
	{
		return gMemory->Read<DWORD>(ClientDLL + gOffsets.gGlowObjectBase());
	}

	bool gIsDormant(int PlayerNum)
	{
		DWORD BaseEntity = gEntityBase(PlayerNum);
		return gMemory->Read<bool>(BaseEntity + gOffsets.gbDormant());
	}

	bool gSpotted(int PlayerNum)
	{
		DWORD BaseEntity = gEntityBase(PlayerNum);
		return gMemory->Read<bool>(BaseEntity + gOffsets.gbSpotted());
	}

	int gGlowIndex(int PlayerNum)
	{
		DWORD BaseEntity = gEntityBase(PlayerNum);
		return gMemory->Read<bool>(BaseEntity + gOffsets.gGlowIndex());
	}

	void DrawGlow(int PlayerNum, RGBA color)
	{
		gMemory->Write<RGBA>(gGlowPointer() + ((gGlowIndex(PlayerNum) * 0x34) + 0x4), color);
		gMemory->Write<twoBools>(gGlowPointer() + ((gGlowIndex(PlayerNum) * 0x34) + 0x24), tBOOLs);
	}

}Entity;

struct Vector
{
	float x, y, z;
};

struct Player
{
	Vector m_vecPunch;
	Vector oldPunch;
	int m_iShotsFired;
}me;

//====EOF STRUCTS===============================EOF STRUCTS==========================EOF STRUCTS===---

float ManhattanDistance(Vector c1, float c2[])
{
	float dx = abs(c2[0] - c1.x);
	float dy = abs(c2[1] - c1.y);
	float dz = abs(c2[2] - c1.z);

	return dx + dy + dz;
}

void Click()
{
	mouse_event(MOUSEEVENTF_LEFTDOWN, NULL, NULL, NULL, NULL);
	Sleep(1);
	mouse_event(MOUSEEVENTF_LEFTUP, NULL, NULL, NULL, NULL);
	Sleep(30);
}

int WeaponID()
{

	DWORD ActiveWeapon = gMemory->Read<DWORD>(Player.gPlayerBase() + gOffsets.ghActiveWeapon());
	DWORD entNum = ActiveWeapon & 0xFFF;
	DWORD WeaponID = gMemory->Read<DWORD>(ClientDLL + gOffsets.gEntityList() + (entNum - 1) * gOffsets.gDwEntitySize());
	int myWeaponID = gMemory->Read<int>(WeaponID + gOffsets.gdwActiveWeaponID());
	return myWeaponID;
}

bool IsWeaponPistol(int iWeaponID)
{
	return(iWeaponID == weapon_deagle || iWeaponID == weapon_elite || iWeaponID == weapon_fiveseven || iWeaponID == weapon_glock
		|| iWeaponID == weapon_p228 || iWeaponID == weapon_usp || iWeaponID == weapon_tec9 || iWeaponID == weapon_taser || iWeaponID == weapon_hkp2000);

	return false;
}