#include "Scene.h"

#include "GameObject.h"
#include "GraphicManager.h"
#include "RigidBody2D.h"
#include "UI.h"

#define Abs(num) (num > 0) ? num : -num

bool Scene::CollisionCheckCircle(GameObject * a, GameObject * b)
{
	float asdf = D3DXVec2Length(&(a->transform->position - b->transform->position));
	if (a->boxcollider2d->radius + b->boxcollider2d->radius > asdf)
		return true;

	return false;
}

bool Scene::CollisionCheckAABB(GameObject * a, GameObject * b, bool opt)
{
	if (!opt)
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
		return false;
	}

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


void Scene::CollisionUpdate(GameObject * a, GameObject * b, bool CheckX)
{
	auto Arigidbody2d = a->GetComponent<RigidBody2D>();
	auto Brigidbody2d = b->GetComponent<RigidBody2D>();

	if (Arigidbody2d == nullptr || Brigidbody2d == nullptr)
		return;

	if (Arigidbody2d->bodyType != RigidBody2D::BodyType::Static)
	{
		if (CheckX)
			CollisionInterpolationx(a, b);
		else
			CollisionInterpolationy(a, b);
	}




	if (Brigidbody2d->bodyType != RigidBody2D::BodyType::Static)
	{
		if (CheckX)
			CollisionInterpolationx(b, a);
		else
			CollisionInterpolationy(b, a);
	}
}

void Scene::CollisionInterpolationx(GameObject * a, GameObject * b)
{
	auto rigidbody2d = a->GetComponent<RigidBody2D>();

	auto velocity = rigidbody2d->velocity;

	int sign = (velocity.x > 0) ? (1) : (-1);

	bool inter = false;

	if (Abs(velocity.x) > 0.001f)
	{
		while (CollisionCheckAABB(a, b, false))
		{
			a->transform->position.x -= sign;
			rigidbody2d->velocity.x = 0.0f;
			inter = true;
		}
		//if(inter)
		//	a->transform->position.x -= -sign;

	}
}

void Scene::CollisionInterpolationy(GameObject * a, GameObject * b)
{
	auto rigidbody2d = a->GetComponent<RigidBody2D>();

	auto velocity = rigidbody2d->velocity;

	int sign = (velocity.y > 0) ? (1) : (-1);
	
	bool inter = false;

	if (Abs(velocity.y) > 0.001f)
	{
		while (CollisionCheckAABB(a, b, false))
		{
			a->transform->position.y -= sign;
			rigidbody2d->Collision();
			inter = true;
		}
		//if(inter)
		//	a->transform->position.y -= -sign;
	}
}

void Scene::RigidbodyUpdate(GameObject * a)
{
	auto rigidbody = a->GetComponent<RigidBody2D>();

	if (rigidbody != nullptr)
	{
		rigidbody->xMove();
		rigidbody->yMove();
	}

}

void Scene::CollisionCheckUI(UI * UI)
{
	auto mouse = InputManager::get()->mousePositionScreen;

	RECT rect;
	rect.left = UI->transform->position.x - UI->boxcollider2d->size.x * 0.5f;
	rect.top = UI->transform->position.y - UI->boxcollider2d->size.y * 0.5f;
	rect.right = UI->transform->position.x + UI->boxcollider2d->size.x * 0.5f;
	rect.bottom = UI->transform->position.y + UI->boxcollider2d->size.y * 0.5f;

	bool On = (rect.left <= mouse.x && mouse.x <= rect.right && rect.top <= mouse.y && mouse.y <= rect.bottom);

	UI->OnMouse(On);
	if (On)
	{
		if (InputManager::get()->GetKeyDown(InputManager::KEY::MOUSE0))
		{
			UI->OnClick();
		}
	}

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
			gameObjectList.erase(it--);
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


	for (auto object1 : gameObjectVector)
	{
		for (auto object2 : gameObjectVector)
		{
			if (object1 != object2)
			{
				if (!object1->isUI && !object2->isUI && CollisionCheckAABB(object1, object2))
				{
					object1->OnCollisionStay2D();
					object2->OnCollisionStay2D();
				}
			}
		}

		auto rigidbody = object1->GetComponent<RigidBody2D>();

		if (rigidbody != nullptr && rigidbody->bodyType != RigidBody2D::BodyType::Static)
		{// 움직이는 객체들만 세부적인 충돌 보정을 진행함
			rigidbody->xMove();	// 먼저 x좌표를 움직임
			for (auto object2 : gameObjectVector)
			{
				if (object1 != object2)
				{
					if (!object1->isUI && !object2->isUI && CollisionCheckAABB(object1, object2))
					{// x좌표만 움직인 후 세부 보정
						CollisionUpdate(object1, object2, true);
					}
				}
			}

			rigidbody->yMove();	// y자표를 움직임
			for (auto object2 : gameObjectVector)
			{
				if (object1 != object2)
				{
					if (!object1->isUI && !object2->isUI && CollisionCheckAABB(object1, object2))
					{// y좌표만 움직인 후 세부 보정
						CollisionUpdate(object1, object2, false);
					}
				}
			}
		}
	}

	for (auto object : gameObjectVector)
	{
		if (object->isUI)
		{
			CollisionCheckUI((UI *)object);
		}
	}

}