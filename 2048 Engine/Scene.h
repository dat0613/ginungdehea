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
	std::list<GameObject *> ColliderList;		//충돌 체크가 필요한 물체들
	std::list<GameObject *> MoveObjectList;		//움직이는 물체들 (움직이는 물체들 끼리, 움직이는 물체와 충돌 체크가 필요한 물체들 끼리만 충돌체크)

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