#include "Scene_Test.h"
#include "MiddleTank.h"
#include "Negev.h"
#include "UITest.h"
#include "BackGround.h"
#include "Ground.h"
#include "Item.h"
#include "Cloud.h"
#include "UFOsimple.h"

void Scene_Test::Init()
{
	auto tank = Instantiate<MiddleTank>();
	tank->transform->position.y = -1000;
	tank->transform->position.x = -1500;
	Instantiate<BackGround>();
	for (int i = 0; i < 50; i++)
	{
		auto obj = Instantiate<Ground>();
		//obj->transform->position.x = i * 860;
		obj->transform->position.x = i * 10;
		obj->transform->position.y = i*-10;
	}

	Instantiate<UITest>();
	Instantiate<BackGround>();
	auto item = Instantiate<Item>();
	item->transform->position = D3DXVECTOR2(1000,-1000);
	item->SetType(Animation::TYPE::SpeedUP);
	//Instantiate<MiddleTank>()->animation->color = D3DCOLOR_ARGB(20, 255, 0, 255);

	item = Instantiate<Item>();
	item->transform->position = D3DXVECTOR2(1500, -1000);
	item->SetType(Animation::TYPE::RangeUP);

	item = Instantiate<Item>();
	item->transform->position = D3DXVECTOR2(500, -1000);
	item->SetType(Animation::TYPE::DoubleJump);

	item = Instantiate<Item>();
	item->transform->position = D3DXVECTOR2(0, -1000);
	item->SetType(Animation::TYPE::TripleShot);

	Instantiate<UFOsimple>()->transform->position = D3DXVECTOR2(3000, -2000);

	for (int i = 0; i < 15; i++)
		Instantiate<Cloud>();
}

void Scene_Test::Update()
{

}