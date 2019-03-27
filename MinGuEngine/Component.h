#pragma once

#include <d3dx9.h>

class GameObject;
class Component
{
private:

	GameObject * gameObject;	// 이 컴포넌트를 소유할 게임 오브젝트

public:

	Component();

	virtual void Awake();
	virtual void Update() = 0;
	virtual void LateUpdate();
	virtual void OnDisable();
	virtual ~Component();

	void SetGameObject(GameObject * gameObject);
	GameObject * GetGameObject();

};