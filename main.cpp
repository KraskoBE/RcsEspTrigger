#include <iostream>
#include "Functions.h"
#include "Offsets.h"
#include "Colors.h"
#include <thread>
using namespace std;

int gamestate;
bool bESP=0, bRCS=0, bTrig=0;
DWORD Engine;

void iStatus()
{
	system("cls");
	cout << "Searching for CS:GO...";
	cout << "\n Found... Loading Hack\n\n";
	cout << "Trigger: " << bTrig << endl;
	cout << "ESP: " << bESP << endl;
	cout << "RCS: " << bRCS << endl;
}

void ReadData()
{
	while (true)
	{
		Engine = gMemory->Read<DWORD>(EngineDLL + gOffsets.gEnginePointer());
		gamestate = gMemory->Read<int>(Engine + 0xE8);

		if (GetAsyncKeyState(VK_F6))
		{
			bTrig = !bTrig;
			iStatus();
		}
		Sleep(100);
		if (GetAsyncKeyState(VK_F7))
		{
			bESP = !bESP;
			iStatus();
		}
		Sleep(100);
		if (GetAsyncKeyState(VK_F8))
		{
			bRCS = !bRCS;
			iStatus();
		}
		Sleep(100);
		Sleep(1);
	}

}

void ESP();
void Trig();
void RCS();

int main()
{
	cout << "Searching for CS:GO...";
	while (!gMemory->Process("csgo.exe"))
	{
		Sleep(1000);
	}

	cout << "\n Found... Loading Hack\n";

	ClientDLL = gMemory->Module("client.dll", ClientDLL);
	EngineDLL = gMemory->Module("engine.dll", EngineDLL);
	ColorizeMe();//====cvetovete======
	cout << "\nTrigger: " << bTrig << endl;
	cout << "ESP: " << bESP << endl;
	cout << "RCS: " << bRCS << endl;

	thread first(ReadData);
	thread second(ESP);
	thread third(Trig);
	thread fourth(RCS);

	first.join();
	second.join();
	third.join();
	fourth.join();


	return 0;
}

void Trig()
{
	while (true)
	{
		while (bTrig && gamestate == 6)
		{
			if (GetAsyncKeyState(0x12))
			{
				int PlayerInCH = Player.gCrosshairID();
				if (!Entity.gisDead(PlayerInCH) && Entity.gTeam(PlayerInCH) != Player.gTeam() && PlayerInCH>=0 && PlayerInCH<63)
				{
					Click();
					Sleep(30);
				}
			}
			Sleep(1);
		}
		Sleep(1);
	}
}

void ESP()
{
	while (true)
	{
		while (bESP && gamestate == 6)
		{
			for (int i = 0; i < 63; i++)
			{
				if (!Entity.gIsDormant(i) && !Entity.gisDead(i))
				{
					if (Entity.gTeam(i) != Player.gTeam())
						Entity.DrawGlow(i, PINK);
					else
						Entity.DrawGlow(i, GREEN);
				}
			}
			Sleep(1);
		}
		Sleep(1);
	}
}

void RCS()
{
	while (true)
	{
		me.oldPunch.x = 0;
		me.oldPunch.y = 0;
		while (bRCS && gamestate == 6 && !IsWeaponPistol(WeaponID()))
		{
			me.m_vecPunch = gMemory->Read<Vector>(Player.gPlayerBase() + gOffsets.gVecPunch());

			me.m_vecPunch.x *= 2.0f;
			me.m_vecPunch.y *= 2.0f;

			if (Player.gShotsFired() > 0)
			{
				Vector currentAngles = gMemory->Read<Vector>(Engine + gOffsets.gSetViewAngles());

				Vector modifier = me.m_vecPunch;
				modifier.x -= me.oldPunch.x;
				modifier.y -= me.oldPunch.y;

				currentAngles.x -= modifier.x;
				currentAngles.y -= modifier.y;

				gMemory->Write<Vector>(Engine + gOffsets.gSetViewAngles(), currentAngles);
			}
			me.oldPunch = me.m_vecPunch;
			Sleep(1);
		}
		Sleep(1);
	}
}