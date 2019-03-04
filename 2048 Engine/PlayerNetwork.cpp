#include "PlayerNetwork.h"
#include "Bullet.h"
#include "SoundManager.h"

void PlayerNetwork::Init(GameObject::TYPE type)
{
	Player::Init(type);

	user = new MinNet::MinNetUser();
	mousePos = D3DXVECTOR2(0.0f, 0.0f);
}

void PlayerNetwork::Render()
{

}

void PlayerNetwork::Update()
{
	if (die == true)
	{
		if (dieTime + respawnDelay < clock())
		{
			visible = true;
			die = false;
			SetIsCanMove(true);		//SetIsCollider(true)의 역할도 같이 수행함
			shadow = true;
		}
	}

	AnimationProcess();

	if (isFalling)
	{
		position.y += 10.0f;
		//SetAnimation(Animation::TYPE((int)Animation::TYPE::PLAYER_BLUE_IDLE + (int)player_color * 3));

		int symbol = ((size.x < 0.0f) ? (-1) : (1));
		float fallDistance = 150.0f;

		size.x = (fallingPosition.y + fallDistance - position.y) / fallDistance * symbol;
		size.y = (fallingPosition.y + fallDistance - position.y) / fallDistance;

		if (fallingPosition.y + fallDistance < position.y)
		{
			isFalling = false;
			fallingPosition = { 0.0f,0.0f };

			size.x = 1.0f;
			size.y = 1.0f;

			die = true;
			dieTime = clock();

			visible = false;
			SetIsCollider(false);

			SoundManager::GetInstance()->pushSoundQ(SoundEvent::KillSound);
			
		}

		return;
	}

	RollingProcess();

	if (gun != nullptr)
	{
		gun->UpdatePosition(position + this->getSpriteSize() * 0.5f, mousePos);
	}

	if (!isRolling)
	{
		isKeyDown = false;

		if ((!(fsame(moveDir.x, 0.0f))) || (!(fsame(moveDir.y, 0.0f))))
			isKeyDown = true;

		if (isKeyDown)
		{
			if (!(fsame(velocity, maxVelocity)))
				velocity = lerp(velocity, maxVelocity, 0.1f);

			slideDir = moveDir;
		}
		else
			if (velocity > 0.0f)
				velocity = lerp(velocity, 0.0f, 0.1f);
	}


	position += moveDir * velocity;
	if (!isKeyDown)
	{
		position += slideDir * velocity;
	}
	position += pushedDir * pushedVelocity;

	pushedVelocity = lerp(pushedVelocity, 0.0f, 0.05f);

	GetPistol();
}

void PlayerNetwork::OnTriggerEnter(GameObject * obj)
{
	switch (obj->getType())
	{
	//case GameObject::TYPE::Bullet:

	//	pushedDir = ((::Bullet *)obj)->GetDir();
	//	pushedVelocity += ((::Bullet *)obj)->GetPower();

	//	break;

	case GameObject::TYPE::Hole:

		if (!isFalling && !isRolling)
		{
			isFalling = true;
			fallingPosition = position;
			velocity = pushedVelocity = 0.0f;
			shadow = false;

			if (gun != nullptr && gun->getType() == Pistol)
				DropGun();
		}

		break;
	}

}
