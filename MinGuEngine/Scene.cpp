#include "Scene.h"

#include "GameObject.h"
#include "GraphicManager.h"

void Scene::Init()
{

}

void Scene::AutoUpdate()
{
	if (gameObjectList.size() <= 0)
		return;
	for (auto it = gameObjectList.begin(); it != gameObjectList.end(); it++)
	{
		auto obj = *it;

		if (obj->destroy)
		{
			gameObjectList.erase(it);
			delete obj;
		}
		else
		{
			obj->ComponentUpdate();
			obj->Update();
		}
	}
}

void Scene::AutoLateUpdate()
{
	if (gameObjectList.size() <= 0)
		return;
	for (auto obj : gameObjectList)
	{
		obj->LateUpdate();
	}
}

void Scene::Update()
{

}

void Scene::AddGameObject(GameObject * object)
{
	gameObjectList.push_back(object);
}

void Scene::AutoRender()
{
	GraphicManager::get()->Render(gameObjectList);
}
