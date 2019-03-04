#include "NetworkManager.h"
#include "SniperRifle.h"

#include "Bullet.h"
#include "GraphicManager.h"
#include "SoundManager.h"

D3DXVECTOR2 SniperRifle::GetMuzzlePosition()
{
	return (D3DXVECTOR2(spriteSize.x * this->size.x * cos(D3DXToRadian(degree)), spriteSize.x * this->size.x * sin(D3DXToRadian(degree))) + position);
}

D3DXVECTOR2 SniperRifle::GetTargetPosition()
{
	return D3DXVECTOR2(D3DXVECTOR2((spriteSize.x * this->size.x + 10) * cos(D3DXToRadian(degree)), (spriteSize.x * this->size.x + 10) * sin(D3DXToRadian(degree))) + position);
}

void SniperRifle::ReloadSound()
{
	SoundManager::GetInstance()->pushSoundQ(SoundEvent::TYPE::SniperRifleReload);
}

void SniperRifle::Init(GameObject::TYPE type)
{
	Gun::Init(type);

	setSize(D3DXVECTOR2(1.2f, 1.2f));

	//SetOption(10, 30, 10, 10, 3700, 1463, 200.0f, 9000.0f);
}

void SniperRifle::Update()
{
	Gun::Update();

	if (degree < 270 && degree > 90)
		size.y = -1.2;
	else
		size.y = 1.2f;
}

bool SniperRifle::Shoot()
{
	if (Gun::Shoot())
	{
		GameObject * bullet = Instantiate(GameObject::Bullet);

		Rebound = ((rand() % 2) - 1) * 0.5;

		//GraphicManager::GetInstance()->RenderText(position, D3DXCOLOR(0, 0, 0, 255), 0, "%d", random);

		degree += Rebound;

		bullet->setPosition(GetMuzzlePosition());

		D3DXVECTOR2 targetPosition = GetTargetPosition();

		((::Bullet *)bullet)->SetOption(NetworkManager::GetInstance()->GetID(),GetBulletSpeed(), targetPosition, GetEffectiveRange(),power);

		GraphicManager::GetInstance()->AddShake(2);							//È­¸é Èçµé¸² È¿°ú
		//SoundManager::GetInstance()->pushSoundQ(SoundEvent::TYPE::Test2);	//ÃÑ ¼Ò¸®
		//int sound = rand() % 2 + SoundEvent::TYPE::SniperRifleShoot1;
		SoundManager::GetInstance()->pushSoundQ(SoundEvent::TYPE::SniperRifleShoot);
		NetworkManager::GetInstance()->Shoot(GetBulletSpeed(), bullet->getPosition(), targetPosition, GetEffectiveRange(),power);

		return true;
	}
	return false;
}

void SniperRifle::OnTriggerEnter(GameObject * object)
{

}
