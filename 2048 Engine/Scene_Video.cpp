#include "PlayerNetwork.h"
#include "NetworkManager.h"
#include "Scene_video.h"
#include "head.h"
#include "Gun.h"
#include "Hole.h"
#include "KillLog.h"
#include "InputManager.h"

void Scene_Video::Init()
{
	color_array[0] = Player::PLAYER_COLOR::RED;
	color_array[1] = Player::PLAYER_COLOR::BLUE;
	color_array[2] = Player::PLAYER_COLOR::GRAY;
	color_array[3] = Player::PLAYER_COLOR::NEON;
	color_array[4] = Player::PLAYER_COLOR::PURPLE;
	color_array[5] = Player::PLAYER_COLOR::PINK;
	color_array[6] = Player::PLAYER_COLOR::YELLOW;
	color_array[7] = Player::PLAYER_COLOR::REVERSE;

	degree_array[0] = 90;
	degree_array[1] = 90 - 45;
	degree_array[2] = 90 + 45;
	degree_array[3] = 90 - 90;
	degree_array[4] = 90 + 90;
	degree_array[5] = 90 - 135;
	degree_array[6] = 90 + 135;
	degree_array[7] = 90 - 180;

	flip_array[0] = false;
	flip_array[1] = true;
	flip_array[2] = false;
	flip_array[3] = true;
	flip_array[4] = false;
	flip_array[5] = true;
	flip_array[6] = false;
	flip_array[7] = true;

	D3DXVECTOR2 axis = { 800,850 };
	float distance = 100.0f;

	Instantiate(GameObject::TestBackGround)->setPosition(0, 0);

	GameObject * player = Instantiate(GameObject::Player);
	((Player *)player)->SetPlayerColor(Player::PLAYER_COLOR::RED);
	GraphicManager::GetInstance()->SetCameraTarget(axis - player->getSpriteSize() * 0.5f);
	player->setPosition(axis.x + distance * cos(D3DXToRadian(90)), axis.y - distance * sin(D3DXToRadian(90)));
	player->visible = false;
	Myplayer = (Player *)player;
	NetworkManager::GetInstance()->SetMyPlayer(Myplayer);
	GraphicManager::GetInstance()->SetCameraTarget(player);

	//SoundManager::GetInstance()->pushSoundQ(SoundEvent::Funky);

	// 0
	auto obj = Instantiate(GameObject::Hole);
	auto hole = (Hole *)obj;
	hole->FastSetting(1147, 36, 241, 209);

	// 1
	obj = Instantiate(GameObject::Hole);
	hole = (Hole *)obj;
	hole->FastSetting(130, 840, 256, 230);

	// 2
	obj = Instantiate(GameObject::Hole);
	hole = (Hole *)obj;
	hole->FastSetting(1125, 1767, 287, 269);

	// 3
	obj = Instantiate(GameObject::Hole);
	hole = (Hole *)obj;
	hole->FastSetting(2136, 841, 282, 232);

	// 4
	obj = Instantiate(GameObject::Hole);
	hole = (Hole *)obj;
	hole->FastSetting(1590, 456, 267, 212);

	// 5
	obj = Instantiate(GameObject::Hole);
	hole = (Hole *)obj;
	hole->FastSetting(687, 436, 261, 238);

	// 6
	obj = Instantiate(GameObject::Hole);
	hole = (Hole *)obj;
	hole->FastSetting(646, 1250, 271, 248);

	// 7
	obj = Instantiate(GameObject::Hole);
	hole = (Hole *)obj;
	hole->FastSetting(1617, 1251, 281, 241);

	// 8
	obj = Instantiate(GameObject::Hole);
	hole = (Hole *)obj;
	hole->FastSetting(1096, 805, 350, 297);

	numOfPlayer = 0;
}

void Scene_Video::Update()
{
	Scene::Update();
	Scene::LateUpdate();

	D3DXVECTOR2 axis = { 800,850 };

	if (InputManager::GetInstance()->OneClickKey(SKILL1))
	{
		if (0 < numOfPlayer && numOfPlayer < 8)
		{
			float distance = 100.0f;
			auto obj = Instantiate(GameObject::PlayerNetwork);
			auto netPlayer = (PlayerNetwork *)obj;
			netPlayer->setPosition(axis.x + distance * cos(D3DXToRadian(degree_array[numOfPlayer])), axis.y - distance * sin(D3DXToRadian(degree_array[numOfPlayer])));
			if (flip_array[numOfPlayer])
				netPlayer->setSize(-1.0f, 1.0f);
			netPlayer->SetPlayerColor(color_array[numOfPlayer++]);
		}
		if (numOfPlayer == 0)
		{
			Myplayer->visible = true;
			numOfPlayer++;
		}
	}
}

void Scene_Video::Release()
{

}

void Scene_Video::Render()
{
	Scene::Render();
}