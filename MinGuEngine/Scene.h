#pragma once

#include <list>

using namespace std;

class GameObject;
class Scene 
{
public:

	enum TYPE
	{
		Test
	};

private:

	list<GameObject *> gameObjectList;
	bool CollisionCheckCircle(GameObject * a, GameObject * b);
	bool CollisionCheckAABB(GameObject * a, GameObject * b);
	void CollisionUpdate(GameObject * a, GameObject * b);
	void CollisionInterpolation(GameObject * a, GameObject * b);

public:
	
	virtual void Init();
	TYPE type;
	void AutoUpdate();
	void AutoLateUpdate();
	virtual void Update();
	void AddGameObject(GameObject * object);
	void AutoRender();
	void AutoCollision();
};