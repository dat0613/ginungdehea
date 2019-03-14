#include "Scene.h"

#include "GameObject.h"
#include "GraphicManager.h"
#include "RigidBody2D.h"

bool Scene::CollisionCheckCircle(GameObject * a, GameObject * b)
{
	float asdf = D3DXVec2Length(&(a->transform->position - b->transform->position));
	if (a->boxcollider2d->radius + b->boxcollider2d->radius > asdf)
		return true;

	return false;
}

bool Scene::CollisionCheckAABB(GameObject * a, GameObject * b)
{
	if (CollisionCheckCircle(a, b))
    {
		auto aps = (a->transform->position - a->boxcollider2d->size * 0.5f);
		auto bps = (b->transform->position - b->boxcollider2d->size * 0.5f);
		RECT rectA = { aps.x, aps.y, aps.x + a->boxcollider2d->size.x, aps.y + a->boxcollider2d->size.y };
		RECT rectB = { bps.x, bps.y, bps.x + b->boxcollider2d->size.x, bps.y + b->boxcollider2d->size.y };
		RECT rect;
		auto result = IntersectRect(&rect, &rectA, &rectB);

		if (result)
		{
			return true;
		}
	}

	return false;
}

void Scene::CollisionUpdate(GameObject * a, GameObject * b)
{
	auto Arigidbody2d = a->GetComponent<RigidBody2D>();
	auto Brigidbody2d = b->GetComponent<RigidBody2D>();

	if(Arigidbody2d == nullptr || Brigidbody2d == nullptr)


	if (Arigidbody2d != nullptr)
	{
		if (Arigidbody2d->bodyType != RigidBody2D::BodyType::Static)
		{

		}
	}
	

	if (Brigidbody2d != nullptr)
	{
		if (Brigidbody2d->bodyType != RigidBody2D::BodyType::Static)
		{

		}
	}
}

void Scene::CollisionInterpolation(GameObject * a, GameObject * b)
{

}

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

void Scene::AutoCollision()
{
	vector<GameObject *> gameObjectVector(gameObjectList.size());

	int i = 0;
	for (auto object : gameObjectList)
	{
		gameObjectVector[i++] = object;
	}

	int max = gameObjectVector.size();
	for (int i = 0; i < max - 1; i++)
	{
		for (int j = i + 1; j < max; j++)
		{
			if (CollisionCheckAABB(gameObjectVector[i], gameObjectVector[j]))
			{
				gameObjectVector[i]->OnCollisionStay2D();
				gameObjectVector[j]->OnCollisionStay2D();

			}
		}
	}
}