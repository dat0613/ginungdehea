#include "Component.h"

Component::Component()
{
	this->gameObject = nullptr;
}

void Component::LateUpdate()
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