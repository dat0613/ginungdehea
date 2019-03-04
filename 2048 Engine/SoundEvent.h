#pragma once
#include <fmod.h>

class SoundEvent
{
private:

public:
	enum  TYPE {
		GunPickUp, PistolShoot1, PistolShoot2,PistolReload, AssaultRifleShoot1, AssaultRifleShoot2, AssaultRifleReload
		, SniperRifleShoot, SniperRifleReload, PlayerFall, PlayerRespawn, KillSound,NoBullet, DieSound, Funky, MAXSOUND
	};
	TYPE type;
};