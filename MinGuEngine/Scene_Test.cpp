#include "Scene_Test.h"
#include "Cube.h"
#include "Negev.h"
#include "UITest.h"

void Scene_Test::Init()
{
	Instantiate<Cube>()->transform->position.y = -1000;
	Instantiate<Negev>()->transform->position.y = 1000;
	Instantiate<Negev>()->transform->position.x = 500;
	Instantiate<Negev>()->transform->position.y = -500;
	for (int i = 0; i < 10; i++)
	{
		Instantiate<Negev>()->transform->position.x = -i * 252;
	}

	Instantiate<UITest>();

	//Instantiate<Cube>()->animation->color = D3DCOLOR_ARGB(20, 255, 0, 255);
}

void Scene_Test::Update()
{

}
