#include "Scene_Test.h"
#include "MiddleTank.h"
#include "Negev.h"
#include "UITest.h"
#include "BackGround.h"
#include "Ground.h"
#include "Item.h"

void Scene_Test::Init()
{
	Instantiate<MiddleTank>()->transform->position.y = -1000;
	Instantiate<BackGround>();
	for (int i = 0; i < 50; i++)
	{
		auto obj = Instantiate<Ground>();
		obj->transform->position.x = i * -300;
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
}

void Scene_Test::Update()
{

}