#include "Scene_Reflection.h"
#include "Object.h"
#include "Controller.h"

void Scene_Reflection::Init()
{
	auto obj = Instantiate(GameObject::TestBackGround);
	obj->SetIsCollider(false);
	obj->setPosition(-2000, -2000);

	obj = Instantiate(GameObject::TYPE::Object);
	obj->setPosition(0, 0);
	auto object = ((Object *)obj);
	//object->setSpeed(10, 10);

	GraphicManager::GetInstance()->SetCameraTarget(obj);

	obj = Instantiate(GameObject::TYPE::Controller);
	auto control = (Controller *)obj;
	control->setObject(object);

	for (int i = 0; i < 10; i++)
	{// y
		for (int j = 0; j < 10; j++)
		{// x
			obj = Instantiate(GameObject::TYPE::Object);
			obj->setPosition((j * 110) - 2000 , (i * 110) - 2000);
		}
	}





}

void Scene_Reflection::Update()
{
	Scene::Update();
	Scene::LateUpdate();

	Scene::Collision();
}

void Scene_Reflection::Release()
{
	Scene::Release();
}

void Scene_Reflection::Render()
{
	Scene::Render();
}

Scene_Reflection::~Scene_Reflection()
{
	Release();
}
