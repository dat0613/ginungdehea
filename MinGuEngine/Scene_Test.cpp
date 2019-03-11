#include "Scene_Test.h"
#include "Cube.h"
#include "Negev.h"

void Scene_Test::Init()
{
	auto obj = Instantiate<Cube>();
	obj->transform->position = obj->transform->position;
	Instantiate<Negev>();
	//Instantiate<Cube>()->animation->color = D3DCOLOR_ARGB(20, 255, 0, 255);
}

void Scene_Test::Update()
{

}
