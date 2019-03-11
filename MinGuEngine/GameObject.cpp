#include "GameObject.h"

GameObject::GameObject()
{
	animation = AddComponent<Animation>();
	transform = AddComponent<Transform>();
	boxcollider2d = AddComponent<BoxCollider2D>();
	destroy = false;
}

void GameObject::ComponentUpdate()
{
	for (auto comp : ComponentMap)
	{
		comp.second->Update();
	}
}

void GameObject::LateUpdate()
{

}

GameObject::~GameObject()
{
	for (auto comp : ComponentMap)
	{
		delete comp.second;
	}

	ComponentMap.clear();
}