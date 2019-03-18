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
		comp->Awake();
		return (T *)comp;
	}


	template <class T>

	T * GetComponent()
	{
		auto obj = ComponentMap.find(typeid(T).hash_code());
		if (obj == ComponentMap.end())
			return nullptr;
		else
			return ((T *)(obj->second));
	}


	GameObject();
	virtual void Awake();
	virtual void Update() = 0;
	void ComponentUpdate();
	virtual void LateUpdate();
	virtual ~GameObject();

	virtual void OnCollisionEnter2D();
	virtual void OnCollisionStay2D();
	virtual void OnCollisionExit2D();

	Transform * transform;
	Animation * animation;
	BoxCollider2D * boxcollider2d;

	bool destroy;
	bool isUI;
};

template <class T>
static T * Instantiate()
{
	GameObject * object = new T();
	GameManager::get()->nowScene->AddGameObject(object);
	object->Awake();
	return (T *)object;
}