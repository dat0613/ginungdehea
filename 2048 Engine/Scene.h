#pragma once

#include "GameObject.h"
#include "GraphicManager.h"
#include "SoundManager.h"
#include "InputManager.h"
#include <list>
#include <ctime>

class Scene
{
private:
	std::list<GameObject *> UpdateList;
	std::list<GameObject *> ColliderList;		//�浹 üũ�� �ʿ��� ��ü��
	std::list<GameObject *> MoveObjectList;		//�����̴� ��ü�� (�����̴� ��ü�� ����, �����̴� ��ü�� �浹 üũ�� �ʿ��� ��ü�� ������ �浹üũ)

	GameObject* GetGameObject(int num);

	bool CheckAABBCollision(GameObject * o1, GameObject * o2);
	bool CheckCircleCollision(GameObject * o1, GameObject * o2);
	bool CheckOBBCollision(GameObject * o1, GameObject * o2);


protected:

public:
	virtual ~Scene();
	virtual void Init() = 0;
	virtual void Update();
	virtual void LateUpdate();
	virtual void Collision();
	virtual void Render();
	virtual void Release();

	void pushUpdateList(GameObject * obj);
};