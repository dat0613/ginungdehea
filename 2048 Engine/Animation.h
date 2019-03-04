#pragma once

#include <Windows.h>

#include <d3d9.h>
#include <d3d.h>
#include <d3dx9.h>

#include <ctime>

class Animation
{
private:


public:

	Animation();
	~Animation();


	enum TYPE {
		PLAYER_BLUE_IDLE, PLAYER_BLUE_RUN, PLAYER_BLUE_ROLL,
		PLAYER_GRAY_IDLE, PLAYER_GRAY_RUN, PLAYER_GRAY_ROLL,
		PLAYER_NEON_IDLE, PLAYER_NEON_RUN, PLAYER_NEON_ROLL,
		PLAYER_PINK_IDLE, PLAYER_PINK_RUN, PLAYER_PINK_ROLL,
		PLAYER_PURPLE_IDLE, PLAYER_PURPLE_RUN, PLAYER_PURPLE_ROLL,
		PLAYER_RED_IDLE, PLAYER_RED_RUN, PLAYER_RED_ROLL,
		PLAYER_REVERSE_IDLE, PLAYER_REVERSE_RUN, PLAYER_REVERSE_ROLL,
		PLAYER_YELLOW_IDLE, PLAYER_YELLOW_RUN, PLAYER_YELLOW_ROLL,
		EnemyKillLog, AllyKillLog, GunBox,DieEffect,
		Ground, BackGround, Test2, Test3, Bullet,
		Pistol, AssaultRifle, SniperRifle, 
		MAXANIMATION
	};

	TYPE type;

	DWORD changeTime;		//한 프레임당 시간
	DWORD lastChangeTime;	//가장 최근에 프레임이 변한 시간

	D3DXVECTOR2 nowFrame;
	D3DXVECTOR2 imageSize;
	D3DXVECTOR2 frameSize;

	void SetType(TYPE type);
	TYPE GetType();

	D3DXVECTOR2 GetFrameSize();

	void Update();
};