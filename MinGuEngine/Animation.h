#pragma once

#include "Component.h"

class Animation : public Component
{
public:
	enum TYPE {
		Cube, Negev, UITest, MiddleTank, Ground, Hole, BackGround, Bullet_120mm, Bullet_88mm, Explosion,
		MachineGun, SpeedUP, RangeUP, DoubleJump, TripleShot, SpeedUpEffect, Cloud1, Cloud2, Cloud3, 
		UFO1, UFO2, MAXANIMATION, NONE
	};

private:

	DWORD timePerFrame;
	DWORD lastFrameTime;

public:

	TYPE type;

	Animation();
	void Update();
	void LateUpdate();
	~Animation();

	D3DXVECTOR2 nowFrame;
	D3DXVECTOR2 imageSize;
	D3DXVECTOR2 frameSize;
	bool end = false;

	void SetType(TYPE type);
	TYPE GetType();

	D3DCOLOR color;
};