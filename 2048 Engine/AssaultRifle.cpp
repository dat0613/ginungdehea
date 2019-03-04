#include "NetworkManager.h"
#include "Gun.h"
#include "AssaultRifle.h"
#include "InputManager.h"
#include "SoundManager.h"

#include "Bullet.h"

D3DXVECTOR2 AssaultRifle::GetMuzzlePosition()
{
	return (D3DXVECTOR2(spriteSize.x * this->size.x * cos(D3DXToRadian(degree)),spriteSize.x * this->size.x * sin(D3DXToRadian(degree))) + position);
}

void AssaultRifle::ReloadSound()
{
	SoundManager::GetInstance()->pushSoundQ(SoundEvent::TYPE::AssaultRifleReload);
}

D3DXVECTOR2 AssaultRifle::GetTargetPosition()
{
	return D3DXVECTOR2(D3DXVECTOR2((spriteSize.x * this->size.x + 10) * cos(D3DXToRadian(degree)), (spriteSize.x * this->size.x + 10) * sin(D3DXToRadian(degree))) + position);
}

void AssaultRifle::Init(GameObject::TYPE type)
{
	Gun::Init(type);

	setSize(D3DXVECTOR2(1.5f, 1.5f));

	//SetOption(30, 180, 30, 90, 2100, 85, 60.0f,3000.0f);
}

void AssaultRifle::Update()
{
	Gun::Update();

	if (degree < 270 && degree > 90)
		size.y = -1.5;
	else
		size.y = 1.5f;
}

bool AssaultRifle::Shoot()
{
	if(Gun::Shoot())
	{
	 	GameObject * bullet = Instantiate(GameObject::Bullet);

		Rebound = ((rand() % 20) - 10) * 0.5;

		//GraphicManager::GetInstance()->RenderText(position, D3DXCOLOR(0, 0, 0, 255), 0, "%d", random);

		degree += Rebound;

		bullet->setPosition(GetMuzzlePosition());
		
		D3DXVECTOR2 targetPosition = GetTargetPosition();

		((::Bullet *)bullet)->SetOption(NetworkManager::GetInstance()->GetID(),GetBulletSpeed(),targetPosition ,GetEffectiveRange(),power);

		GraphicManager::GetInstance()->AddShake(2);							//È­¸é Èçµé¸² È¿°ú

		int sound = rand() % 2 + SoundEvent::TYPE::AssaultRifleShoot1;
		SoundManager::GetInstance()->pushSoundQ(SoundEvent::TYPE(sound));	//ÃÑ ¼Ò¸®
		
		NetworkManager::GetInstance()->Shoot(GetBulletSpeed(), bullet->getPosition(), targetPosition, GetEffectiveRange(), power);

		return true;
	}
	return false;
}

void AssaultRifle::OnTriggerEnter(GameObject * object)
{

}