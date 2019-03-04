#include "NetworkManager.h"
#include "SoundManager.h"
#include "Pistol.h"
#include "Bullet.h"

void Pistol::Init(GameObject::TYPE type)
{
	Gun::Init(type);

	SetOption(20, 100, 20, 60, 500, 0, 40, 1000, 15);
}

bool Pistol::Shoot()
{
	if (Gun::Shoot())
	{
		GameObject * bullet = Instantiate(GameObject::Bullet);

		Rebound = ((rand() % 2) - 1) * 0.5;

		//GraphicManager::GetInstance()->RenderText(position, D3DXCOLOR(0, 0, 0, 255), 0, "%d", random);

		degree += Rebound;

		bullet->setPosition(GetMuzzlePosition());

		D3DXVECTOR2 targetPosition = GetTargetPosition();

		((::Bullet *)bullet)->SetOption(NetworkManager::GetInstance()->GetID(), GetBulletSpeed(), targetPosition, GetEffectiveRange(), power);

		GraphicManager::GetInstance()->AddShake(2);							//È­¸é Èçµé¸² È¿°ú
																			//SoundManager::GetInstance()->pushSoundQ(SoundEvent::TYPE::Test2);	//ÃÑ ¼Ò¸®
		int sound = rand() % 2 + SoundEvent::TYPE::PistolShoot1;
		SoundManager::GetInstance()->pushSoundQ((SoundEvent::TYPE)sound);
		NetworkManager::GetInstance()->Shoot(GetBulletSpeed(), bullet->getPosition(), targetPosition, GetEffectiveRange(), power);

		return true;
	}
	return false;
}

void Pistol::Update()
{
	Gun::Update();

	if (degree < 270 && degree > 90)
		size.y = -1.0;
	else
		size.y = 1.0;
}

D3DXVECTOR2 Pistol::GetTargetPosition()
{
	return D3DXVECTOR2(D3DXVECTOR2((spriteSize.x * this->size.x + 10) * cos(D3DXToRadian(degree)), (spriteSize.x * this->size.x + 10) * sin(D3DXToRadian(degree))) + position);
}

D3DXVECTOR2 Pistol::GetMuzzlePosition()
{
	return (D3DXVECTOR2(spriteSize.x * this->size.x * cos(D3DXToRadian(degree)), spriteSize.x * this->size.x * sin(D3DXToRadian(degree))) + position);
}

void Pistol::ReloadSound()
{
	SoundManager::GetInstance()->pushSoundQ(SoundEvent::TYPE::PistolReload);
}

void Pistol::OnTriggerEnter(GameObject * obj)
{

}
