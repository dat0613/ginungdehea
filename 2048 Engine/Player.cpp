#include "NetworkManager.h"
#include "Player.h"
#include "SoundManager.h"
#include "Wall.h"
#include "Bullet.h"
#include "KillLog.h"
#include "GunBox.h"
#include "Pistol.h"


bool Player::WallCollision(GameObject * wall)
{
	auto wall_object = (::Wall *)wall;
	RECT player_rt = GetCollisionRect();
	RECT wall_rt = wall_object->GetCollisionRect();
	RECT asdf;
	return IntersectRect(&asdf, &player_rt, &wall_rt);
}

void Player::GetPistol()
{
	if ((gun == nullptr && die == false) || (gun != nullptr && gun->getType() == Pistol && gun->GetLeftBullet() == 0 && gun->GetNowBullet() == 0 && die == false))
	{
		auto weapon = Instantiate(GameObject::Pistol);
		auto pistol = (::Pistol *)weapon;
		SetGun(pistol);
	}
}

void Player::AnimationProcess()
{
	if (isRolling)
		SetAnimation(Animation::TYPE((int)Animation::TYPE::PLAYER_BLUE_ROLL + (int)player_color * 3));
	else
	{
		if ((!(fsame(moveDir.x, 0.0f))) || (!(fsame(moveDir.y,0.0f))) )
			SetAnimation(Animation::TYPE((int)Animation::TYPE::PLAYER_BLUE_RUN + (int)player_color * 3));
		else
			SetAnimation(Animation::TYPE((int)Animation::TYPE::PLAYER_BLUE_IDLE + (int)player_color * 3));
	}

	if (moveDir.x < 0)
		this->size.x = -1;
	if (moveDir.x > 0)
		this->size.x = 1;
}

void Player::RollingProcess(bool isLocal)
{
	if (isRolling)
	{
		velocity = maxRollingVelocity;
		if (RollingStartTime + RollingTime <= clock())
		{
			if (isLocal)
			{
				NetworkManager::GetInstance()->PlayerSetPosition();
			}

			isRolling = false;
			velocity = 0.0f;

			if (gun != nullptr)
			{
				gun->visible = true;
			}
		}
	}
}

void Player::Init(GameObject::TYPE type)
{
	GameObject::Init(type);

	gun = nullptr;
	fallingPosition = moveDir = pushedDir = D3DXVECTOR2(0.0f, 0.0f);
	isRolling = false;
	RollingStartTime = 0;
	RollingTime = 200;
	velocity = 0.0f;
	pushedVelocity = 0.0f;

	maxVelocity = 10;
	maxRollingVelocity = maxVelocity * 2.0f;

	SetIsCanMove(true);
	shadow = true;
	isKeyDown = false;

	player_color = BLUE;
	isFalling = false;
	die = false;

	lastAtackedPlayerID = -1;

	dieTime = 0;
	respawnDelay = 3000;

	RollingDelay = 1250;
	isMoveAfterLastSetPosition = isPushedAfterLastSetPosition = true;

	lastAttackedPlayerIDResetTime = 3000;

	autoSetPositionDelay = 2000;
	lastAutoSetPosition = 2000;

	Life = 8;
	KillCount = 0;
}

void Player::Render()
{

}

void Player::Update()
{
	if (lastAutoSetPosition + autoSetPositionDelay < clock())
	{
		NetworkManager::GetInstance()->PlayerSetPosition();
		lastAutoSetPosition = clock();
	}

	if (!die && (lastAttackedTime + lastAttackedPlayerIDResetTime < clock()))
	{
		lastAtackedPlayerID = -1;
	}

	if (die == true)
	{
		if (dieTime + respawnDelay < clock())
		{
			GraphicManager::GetInstance()->SetCameraTarget((GameObject *)this);
			NetworkManager::GetInstance()->PlayerSetPosition();

			die = false;
			SetIsCanMove(true);		//SetIsCollider(true)의 역할도 같이 수행함
			shadow = true;

			color = D3DCOLOR_ARGB(255, 255, 255, 255);

		}
		else
		{
			if (lastAtackedPlayerID != -1)
				GraphicManager::GetInstance()->SetCameraTarget((GameObject *)NetworkManager::GetInstance()->GetPlayerWithId(lastAtackedPlayerID));
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

			SetIsCollider(false);
			color = D3DCOLOR_ARGB(150, 255, 255, 255);

			NetworkManager::GetInstance()->PlayerDie(lastAtackedPlayerID);
			//position.y = -1000;
			GraphicManager::GetInstance()->AddShake(30);
			SoundManager::GetInstance()->pushSoundQ(SoundEvent::DieSound);
		}

		return;
	}

	//if (InputManager::GetInstance()->OneClickKey(SKILL2))
	//{
	//	//Instantiate(GameObject::GunBox)->setPosition(InputManager::GetInstance()->getMousePosition());
	//	GetPistol();
	//}

	//if (InputManager::GetInstance()->OneClickKey(SKILL2))
	//{
	//	auto obj = Instantiate(GameObject::KillLog);
	//	auto kill_log = (::KillLog *)obj;
	//	kill_log->SetOption(-1, 0);
	//}

	//if (InputManager::GetInstance()->OneClickKey(SKILL1))
	//{

	//	auto obj = Instantiate(GameObject::KillLog);
	//	auto kill_log = (::KillLog *)obj;
	//	kill_log->SetOption(0, 3);
	//}

	if (!isRolling)
	{
		moveDir = D3DXVECTOR2(0.0f, 0.0f);

		isKeyDown = false;

		if (InputManager::GetInstance()->ClickKey(LEFT))
		{
			moveDir.x = -1.0f;
			isKeyDown = true;
		}

		if (InputManager::GetInstance()->ClickKey(RIGHT))
		{
			moveDir.x = 1.0f;
			isKeyDown = true;
		}

		if (InputManager::GetInstance()->ClickKey(UP))
		{
			moveDir.y = -1.0f;
			isKeyDown = true;
		}

		if (InputManager::GetInstance()->ClickKey(DOWN))
		{
			moveDir.y = 1.0f;
			isKeyDown = true;
		}


		if (isKeyDown)
		{
			if (!(fsame(velocity,maxVelocity)))
				velocity = lerp(velocity, maxVelocity, 0.1f);


			slideDir = moveDir;
		}
		else
		{
			if (velocity > 0.05f)
			{
				velocity = lerp(velocity, 0.0f, 0.1f);
				isMoveAfterLastSetPosition = true;
			}
			else
				velocity = 0.0f;

			if (isMoveAfterLastSetPosition && (velocity < 0.1))
			{
				isMoveAfterLastSetPosition = false;
				NetworkManager::GetInstance()->PlayerSetPosition();
			}
		}
	}

	//GraphicManager::GetInstance()->RenderText(GraphicManager::GetInstance()->ToCameraCoord (getPosition()), D3DXCOLOR(255, 0, 0, 255), 0, "%.f", velocity);

	if (InputManager::GetInstance()->ClickKey(SPACE))
	{
		if (!isRolling && RollingStartTime + RollingDelay < clock())
		{
			isRolling = true;
			RollingStartTime = clock();

			if (gun != nullptr)
			{
				gun->visible = false;
			}

			NetworkManager::GetInstance()->PlayerRoll();
		}
	}

	RollingProcess(true);

	if (InputManager::GetInstance()->OneClickKey(RELOAD))
	{
		if (gun != nullptr)
		{
			gun->Reload();
		}
	}

	//if (InputManager::GetInstance()->OneClickKey(G))
	//{
	//	if (gun != nullptr && isRolling == false)
	//	{
	//		auto drop_gun = gun;
	//		DropGun();		//이 함수에서 gun 을 nullptr 로 만들기 때문에 위에서 drop_gun 으로 gun을 일단 복사해둠
	//		NetworkManager::GetInstance()->DropGun(drop_gun);
	//	}
	//}

	position += moveDir * velocity;
	if (!isKeyDown)
	{
		position += slideDir * velocity;
	}
	if (pushedVelocity > 0.05f)
	{
		position += pushedDir * pushedVelocity;

		isPushedAfterLastSetPosition = true;
	}
	if (isPushedAfterLastSetPosition && (pushedVelocity < 0.1f))
	{
		isPushedAfterLastSetPosition = false;
		NetworkManager::GetInstance()->PlayerSetPosition();
	}

	pushedVelocity = lerp(pushedVelocity, 0.0f, 0.05f);

	if (gun != nullptr)
	{
		gun->SetDegreeWithMousePosition();

		if (gun->getType() != Pistol)
		{
			if (InputManager::GetInstance()->ClickKey(LEFTMOUSE) && gun->visible)
				gun->Shoot();
		}
		else
		{
			if (InputManager::GetInstance()->OneClickKey(LEFTMOUSE) && gun->visible)
				gun->Shoot();
		}

		gun->UpdatePosition(position + this->getSpriteSize() * 0.5f,InputManager::GetInstance()->getMousePosition());
		GraphicManager::GetInstance()->RenderText(InputManager::GetInstance()->getMousePosition() - GraphicManager::GetInstance()->GetCameraPosition(), D3DXCOLOR(0, 0, 0, 255), 0, "%d / %d", gun->GetNowBullet(), gun->GetLeftBullet());
	}

	GetPistol();
}

void Player::LateUpdate()
{
	if (gun != nullptr)
	{
		gun->zBuffer = zBuffer + 0.1f;
	}

	if (isFalling)
	{
		//if (fallingHole->GetCenter().y > GetCenter().y)
			zBuffer = 0.0f;
	}

}

D3DXVECTOR2 Player::GetMoveDir()
{
	return moveDir;
}

void Player::SetPushedDir(D3DXVECTOR2 pushedDir)
{
	this->pushedDir = pushedDir;
}

void Player::AddPushedVelocity(float pushedVelocity)
{
	this->pushedVelocity += pushedVelocity;
}

void Player::SetMoveDir(D3DXVECTOR2 dir)
{
	moveDir = dir;
}

void Player::SetMoveDir(float x, float y)
{
	moveDir = D3DXVECTOR2(x, y);
}

void Player::SetGun(Gun * gun)
{
	if (this->gun != nullptr)
	{
		if (this->gun->getType() != Pistol)
			NetworkManager::GetInstance()->DropGun(this->gun);

		DropGun();
	}

	if (gun != nullptr)
	{
		SoundManager::GetInstance()->pushSoundQ(SoundEvent::GunPickUp);
		this->gun = gun;
		this->gun->PickUpGun();
	}
}

Gun * Player::GetGun()
{
	return gun;
}

void Player::SetLife(int Life)
{
	this->Life = Life;
}

int Player::GetLife()
{
	return Life;
}

void Player::SetKillCount(int KillCount)
{
	this->KillCount = KillCount;
}

int Player::GetKillCount()
{
	return KillCount;
}

void Player::DropGun()
{
	if (gun == nullptr)
		return;

	if (this->gun->getType() == Pistol)
	{
		this->gun->enabled = false;
	}

	gun->ThrowGun();
	gun->setPosition(position.x, position.y + spriteSize.y);
	gun = nullptr;
	SoundManager::GetInstance()->pushSoundQ(SoundEvent::GunPickUp);
}

void Player::OnTriggerEnter(GameObject * obj)
{
	switch (obj->getType())
	{
	//case GameObject::TYPE::AssaultRifle:
	//case GameObject::TYPE::SniperRifle:
	//	if (gun == nullptr && ((Gun *)obj)->GetIsPossessed() == false)
	//	{
	//		if (InputManager::GetInstance()->OneClickKey(F))
	//		{
	//			auto gun = (Gun *)obj;
	//			SetGun(gun);
	//			NetworkManager::GetInstance()->PickUpGun(gun);
	//		}
	//	}
	//	break;

	case GameObject::TYPE::Wall:

		if (!WallCollision(obj))
			break;

		if (!(fsame(moveDir.x, 0.0f)))
		{

			position.y -= moveDir.y * velocity;
			position.x -= moveDir.x * velocity;

			int loopCount = 0;

			while (!WallCollision(obj))
			{
				position.x += moveDir.x * velocity * 0.1f;

				loopCount++;
				if (loopCount > velocity)
					break;

			}
			position.y += moveDir.y * velocity;
			position.x -= moveDir.x * velocity * 0.1f;

		}

		if (!(fsame(moveDir.y, 0.0f)))
		{

			position.x -= moveDir.x * velocity;
			position.y -= moveDir.y * velocity;

			int loopCount = 0;

			while (!WallCollision(obj))
			{
				position.y += moveDir.y * velocity * 0.1f;


				loopCount++;
				if (loopCount > velocity)
					break;
			}
			position.x += moveDir.x * velocity;
			position.y -= moveDir.y * velocity * 0.1f;
		}

		break;

	case GameObject::TYPE::Bullet:

		if (!isRolling)
		{
			::Bullet * bullet;
			bullet = (::Bullet *)obj;

			pushedDir = bullet->GetDir();
			pushedVelocity += bullet->GetPower();
			lastAtackedPlayerID = bullet->GetOwnerID();
			lastAttackedTime = clock();

			NetworkManager::GetInstance()->PlayerHit(bullet->GetPower());
		}
		
		break;

	case GameObject::TYPE::Hole:

		if (!isFalling && !isRolling)
		{
			isFalling = true;
			fallingPosition = position;
			velocity = pushedVelocity = 0.0f;
			shadow = false;

			if (gun != nullptr)
			{
				auto drop_gun = gun;
				DropGun();		//이 함수에서 gun 을 nullptr 로 만들기 때문에 위에서 drop_gun 으로 gun을 일단 복사해둠
				NetworkManager::GetInstance()->DropGun(drop_gun);
			}


			NetworkManager::GetInstance()->PlayerFall(fallingPosition);
		}

		break;

	case GameObject::TYPE::GunBox:

		auto gunbox = (::GunBox *)obj;
		SetGun(gunbox->GetGun());
		NetworkManager::GetInstance()->PickUpGun(gunbox->GetGun());

		break;
	
	}
}

RECT Player::GetCollisionRect()
{
	RECT rt;
	rt.left = position.x;
	rt.top = position.y + spriteSize.y * 0.7;
	rt.right = position.x + spriteSize.x;
	rt.bottom = position.y + spriteSize.y;

	return rt;
}

Player::PLAYER_COLOR Player::GetPlayerColor()
{
	return player_color;
}

void Player::SetPlayerColor(PLAYER_COLOR color)
{
	player_color = color;
}
