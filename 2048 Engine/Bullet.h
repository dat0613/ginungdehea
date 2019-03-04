#pragma once

#include "GameObject.h"

class Bullet : public GameObject
{
private:

	int OwnerID;				//총을 발사한 플레이어의 ID	
	D3DXVECTOR2 StartPosition;	//총알이 출발한 위치
	D3DXVECTOR2 Direction;		//총알의 방향
	float speed;				//탄속
	float effectiveRange;		//유효 사거리
	float power;				//밀치는 거리

public:

	void Init(GameObject::TYPE type);
	void Update();
	void SetOption(int OwnerID, float speed, D3DXVECTOR2 targetPos, float effectiveRange, float power);
	void OnTriggerEnter(GameObject * Object);

	int GetOwnerID();

	float GetPower();

	D3DXVECTOR2 GetDir();
};