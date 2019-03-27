#include "Scene_Test.h"
#include "MiddleTank.h"
#include "Negev.h"
#include "UITest.h"
#include "BackGround.h"
#include "Ground.h"

void Scene_Test::Init()
{
	Instantiate<MiddleTank>()->transform->position.y = -1000;
	Instantiate<BackGround>();
	for (int i = 0; i < 10; i++)
	{
		auto obj = Instantiate<Ground>();
		obj->transform->position.x = i * 860;
	}

	Instantiate<UITest>();
	Instantiate<BackGround>();

	//Instantiate<MiddleTank>()->animation->color = D3DCOLOR_ARGB(20, 255, 0, 255);
}

void Scene_Test::Update()
{

}
