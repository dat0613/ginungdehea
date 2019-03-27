#pragma once

#include <d3dx9.h>

class GameObject;
class Component
{
private:

	GameObject * gameObject;	// �� ������Ʈ�� ������ ���� ������Ʈ

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