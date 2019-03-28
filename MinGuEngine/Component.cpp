#include "Component.h"

Component::Component()
{
	this->gameObject = nullptr;
	this->destroy = false;
}

void Component::Awake()
{

}

void Component::LateUpdate()
{

}

void Component::OnDisable()
{

}

Component::~Component()
{

}

void Component::SetGameObject(GameObject * gameObject)
{
	this->gameObject = gameObject;
}

GameObject * Component::GetGameObject()
{
	return gameObject;
}