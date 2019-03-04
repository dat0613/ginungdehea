#include "NetworkManager.h"
#include "Scene_Test.h"
#include "head.h"
#include "Player.h"
#include "Gun.h"
#include "Hole.h"
#include "KillLog.h"

void Scene_Test::Init()
{
	Instantiate(GameObject::TestBackGround)->setPosition(0, 0);

	GameObject * player = Instantiate(GameObject::Player);
	player->setPosition(500.0f, 500.0f);
	//((Player *)player)->SetPlayerColor(Player::PLAYER_COLOR::REVERSE);
	GraphicManager::GetInstance()->SetCameraTarget(player);

	NetworkManager::GetInstance()->SetMyPlayer((player));

	SoundManager::GetInstance()->pushSoundQ(SoundEvent::Funky);

	// 0
	auto obj = Instantiate(GameObject::Hole);
	auto hole = (Hole *)obj;
	hole->FastSetting(1147, 36, 241, 209);

	// 1
	obj = Instantiate(GameObject::Hole);
	hole = (Hole *)obj;
	hole->FastSetting(130,840,256,230);

	// 2
	obj = Instantiate(GameObject::Hole);
	hole = (Hole *)obj;
	hole->FastSetting(1125,1767,287,269);

	// 3
	obj = Instantiate(GameObject::Hole);
	hole = (Hole *)obj;
	hole->FastSetting(2136,841,282,232);

	// 4
	obj = Instantiate(GameObject::Hole);
	hole = (Hole *)obj;
	hole->FastSetting(1590,456,267,212);

	// 5
	obj = Instantiate(GameObject::Hole);
	hole = (Hole *)obj;
	hole->FastSetting(687,436,261,238);

	// 6
	obj = Instantiate(GameObject::Hole);
	hole = (Hole *)obj;
	hole->FastSetting(646,1250,271,248);

	// 7
	obj = Instantiate(GameObject::Hole);
	hole = (Hole *)obj;
	hole->FastSetting(1617,1251,281,241);

	// 8
	obj = Instantiate(GameObject::Hole);
	hole = (Hole *)obj;
	hole->FastSetting(1096, 805, 350, 297);

	obj = Instantiate(GameObject::Hole);
	hole = (Hole *)obj;
	hole->FastSetting(0, -100, 2511, 33);


	//Instantiate(GameObject::DieEffect);
	NetworkManager::GetInstance()->Connect();
}

void Scene_Test::Update()
{
	Scene::Update();
	Scene::LateUpdate();
}

void Scene_Test::Release()
{

}

void Scene_Test::Render()
{
	Scene::Render();
}

Scene_Test::~Scene_Test()
{
	Release();
}