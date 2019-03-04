#include "NetworkManager.h"

#include "KillLog.h"
#include "UIManager.h"
#include "head.h"

void KillLog::Init(GameObject::TYPE type)
{
	GameObject::Init(type);

	CreatedTime = 0;
	DestinationPosition = { 0.0f,0.0f };
	isUI = true;

	KillerColor = VictimColor = Player::PLAYER_COLOR::BLUE;
}

void KillLog::SetOption(int KillerID, int VictimID)
{
	CreatedTime = clock();
	auto myPlayerID = NetworkManager::GetInstance()->GetID();

	if ((KillerID == myPlayerID) || (VictimID == myPlayerID))
		SetAnimation(Animation::AllyKillLog);
	else
		SetAnimation(Animation::EnemyKillLog);

	KillerColor = NetworkManager::GetInstance()->GetPlayerColorWithID(KillerID);
	VictimColor = NetworkManager::GetInstance()->GetPlayerColorWithID(VictimID);

	UIManager::GetInstance()->AddKillLog(this);
}

void KillLog::Update()
{
	D3DXVec2Lerp(&position, &position, &DestinationPosition, 0.2f);

	if (TurnOff_)
	{
		if ((fsame(position.x, DestinationPosition.x)) && (fsame(position.y, DestinationPosition.y)))
			enabled = false;
	}
}

void KillLog::TurnOff()
{
	TurnOff_ = true;

	DestinationPosition.x = SCREENWIDTH + spriteSize.x;
}

clock_t KillLog::GetCreatedTime()
{
	return CreatedTime;
}

Player::PLAYER_COLOR KillLog::GetKillerColor()
{
	return KillerColor;
}

Player::PLAYER_COLOR KillLog::GetVictimColor()
{
	return VictimColor;
}

void KillLog::SetDestinationPosition(D3DXVECTOR2 DestinationPosition)
{
	this->DestinationPosition = DestinationPosition;
}
