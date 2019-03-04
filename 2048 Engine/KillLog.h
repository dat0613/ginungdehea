#pragma once

#include "GameObject.h"
#include "Player.h"

class KillLog : public GameObject
{
private:

	Player::PLAYER_COLOR KillerColor;
	Player::PLAYER_COLOR VictimColor;

	clock_t CreatedTime;		//KillLog가 만들어진 시각

	D3DXVECTOR2 DestinationPosition;		//목적지의 위치
	bool TurnOff_;

public:

	void Init(GameObject::TYPE type);
	void SetOption(int KillerID, int VictimID);
	void Update();

	void TurnOff();

	clock_t GetCreatedTime();

	Player::PLAYER_COLOR GetKillerColor();
	Player::PLAYER_COLOR GetVictimColor();

	void SetDestinationPosition(D3DXVECTOR2 DestinationPosition);
};