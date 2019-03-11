#pragma once

#include <d3dx9.h>
#include "GameManager.h"
#include <map>
#include <typeinfo>

#include "Animation.h"
#include "Transform.h"
#include "GameManager.h"
#include "BoxCollider2D.h"


using namespace std;

class Component;
class GameObject
{
private:

	map<size_t, Component *> ComponentMap;


protected:



public:

	template <class T>

	T * AddComponent()
	{
		Component * comp = new T();
		comp->SetGameObject(this);
		ComponentMap.insert(make_pair(typeid(T).hash_code(), comp));
		return (T *)comp;
	}


	template <class T>

	T * GetComponent()
	{
		return ((T *)ComponentMap.find(typeid(T).hash_code)->second);
	}


	GameObject();
	virtual void Update() = 0;
	void ComponentUpdate();
	virtual void LateUpdate();
	virtual ~GameObject();

	Transform * transform;
	Animation * animation;
	BoxCollider2D * boxcollider2d;

	bool destroy;
};

template <class T>
static T * Instantiate()
{
	GameObject * object = new T();
	GameManager::get()->nowScene->AddGameObject(object);
	return (T *)object;
}