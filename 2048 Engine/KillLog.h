#pragma once

#include "GameObject.h"
#include "Player.h"

class KillLog : public GameObject
{
private:

	Player::PLAYER_COLOR KillerColor;
	Player::PLAYER_COLOR VictimColor;

	clock_t CreatedTime;		//KillLog�� ������� �ð�

	D3DXVECTOR2 DestinationPosition;		//�������� ��ġ
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