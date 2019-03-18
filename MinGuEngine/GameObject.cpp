#include "GameObject.h"

GameObject::GameObject()
{
	animation = AddComponent<Animation>();
	transform = AddComponent<Transform>();
	boxcollider2d = AddComponent<BoxCollider2D>();
	destroy = false;
	isUI = false;
}

void GameObject::Awake()
{

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

void GameObject::OnCollisionEnter2D()
{

}

void GameObject::OnCollisionStay2D()
{

}

void GameObject::OnCollisionExit2D()
{

}
