#include "Gun.h"
#include "InputManager.h"
#include "SoundManager.h"

void Gun::Init(GameObject::TYPE type)
{
	GameObject::Init(type);

	BulletPerMagazine = MaxBullet = leftBullet = nowBullet = 0;
	reloadTime = reloadStartTime = Shootdelay = lastShootTime = 0;
	BulletSpeed = 0.0f;

	Rebound = 0.0f;
	numOfSpray = 0;

	lastShoot = false;

	mousePos = D3DXVECTOR2(0.0f, 0.0f);
}

void Gun::Update()
{
	if (isPossessed)
	{
		if (reLoading)
		{
			if (reloadStartTime + reloadTime <= clock())
			{
				int needBullet = BulletPerMagazine - nowBullet;
				if (leftBullet >= needBullet)
				{
					nowBullet += needBullet;
					leftBullet -= needBullet;
				}
				else
				{
					nowBullet += leftBullet;
					leftBullet = 0;
				}

				reLoading = false;
			}
		}
		//GraphicManager::GetInstance()->RenderText(GraphicManager::GetInstance()->ToCameraCoord(position), D3DXCOLOR(255, 0, 255, 255), 0, "%.3f", degree);
	}
}

void Gun::UpdatePosition(D3DXVECTOR2 position, D3DXVECTOR2 mousePos)
{
	if (isPossessed)
	{
		this->position = position;
		this->mousePos = mousePos;
	}
}

void Gun::PickUpGun()
{
	isPossessed = true;
	visible = true;
}

void Gun::ThrowGun()
{
	isPossessed = false;
}

bool Gun::Shoot()
{
	if (nowBullet > 0)
	{
		if (!reLoading)
		{
			if (lastShootTime + Shootdelay <= clock())
			{
				lastShootTime = clock();
				nowBullet--;
				lastShoot = true;
				return true;
			}
			else
			{
				lastShoot = false;
			}
		}
	}
	else
	{
		//자동 재장전 등의 기능을 넣음
		SoundManager::GetInstance()->pushSoundQ(SoundEvent::NoBullet);
	}


	return false;
}

void Gun::SetOption(int BulletPerMagazine, int MaxBullet, int nowBullet, int leftBullet,DWORD reloadTime, DWORD ShootDelay, float BulletSpeed, float effectiveRange,float power)
{
	this->BulletPerMagazine = BulletPerMagazine;
	this->MaxBullet = MaxBullet;

	this->nowBullet = nowBullet;
	this->leftBullet = leftBullet;

	this->reloadTime = reloadTime;
	this->Shootdelay = ShootDelay;

	this->BulletSpeed = BulletSpeed;
	this->effectiveRange = effectiveRange;

	this->power = power;
}

int Gun::GetNowBullet()
{
	return nowBullet;
}

void Gun::SetNowBullet(int nowBullet)
{
	this->nowBullet = nowBullet;
}

int Gun::GetLeftBullet()
{
	return leftBullet;
}

void Gun::SetLeftBullet(int leftBullet)
{
	this->leftBullet = leftBullet;
}

bool Gun::GetIsPossessed()
{
	return isPossessed;
}

void Gun::Reload()
{
	if (!reLoading && leftBullet > 0)
	{
		reLoading = true;
		reloadStartTime = clock();
		ReloadSound();
	}
}

void Gun::ReloadCancle()
{

}

DWORD Gun::GetReloadTime()
{

	return 0;
}

DWORD Gun::GetReloadRemainTime()
{

	return 0;
}

float Gun::GetBulletSpeed()
{
	return BulletSpeed;
}

float Gun::GetEffectiveRange()
{
	return effectiveRange;
}

void Gun::SetDegreeWithMousePosition()
{
	this->degree = D3DXToDegree(atan2(position.y - mousePos.y - (-7 * 1.5f), position.x - mousePos.x)) + 180 + Rebound;
}

void Gun::SetDegreeWithDegree(float degree)
{
	setDegree(degree);
}
