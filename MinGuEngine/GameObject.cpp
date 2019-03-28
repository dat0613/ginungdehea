#include "GameObject.h"

GameObject::GameObject()
{
	transform = AddComponent<Transform>();
	animation = AddComponent<Animation>();
	boxcollider2d = AddComponent<BoxCollider2D>();
	destroy = false;
	isUI = false;
	tag = NONE;
	SortingLayer = 0;
	flip = false;
}

void GameObject::Awake()
{

}

void GameObject::Update()
{
}

void GameObject::ComponentUpdate()
{
	for (auto comp : ComponentMap)
	{
		if (!comp.second->destroy)
			comp.second->Update();
		else
			ComponentMap.erase(comp.first);
	}
}

void GameObject::LateUpdate()
{

}

void GameObject::OnDisable()
{

}

void GameObject::ComponentOnDisable()
{
	for (auto comp : ComponentMap)
	{
		comp.second->OnDisable();
	}
}

GameObject::~GameObject()
{
	for (auto comp : ComponentMap)
	{
		delete comp.second;
	}

	ComponentMap.clear();
}

void GameObject::OnCollisionEnter2D(GameObject * obj)
{

}

void GameObject::OnCollisionStay2D(GameObject * obj)
{

}

void GameObject::OnCollisionExit2D(GameObject * obj)
{

}