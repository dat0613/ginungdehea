#include "GameObject.h"

GameObject::GameObject()
{
	animation = AddComponent<Animation>();
	transform = AddComponent<Transform>();
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

void GameObject::OnCollisionEnter2D(GameObject * obj)
{

}

void GameObject::OnCollisionStay2D(GameObject * obj)
{

}

void GameObject::OnCollisionExit2D(GameObject * obj)
{

}