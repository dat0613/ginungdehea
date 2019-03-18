#pragma once

#include <list>

using namespace std;

class GameObject;
class UI;
class Scene 
{
public:

	enum TYPE
	{
		Test
	};

private:

	list<GameObject *> gameObjectList;
	void CollisionUpdate(GameObject * a, GameObject * b, bool CheckX);
	bool CollisionCheckCircle(GameObject * a, GameObject * b);
	bool CollisionCheckAABB(GameObject * a, GameObject * b, bool opt = true);
	void CollisionInterpolationx(GameObject * a, GameObject * b);
	void CollisionInterpolationy(GameObject * a, GameObject * b);
	void RigidbodyUpdate(GameObject * a);
	void CollisionCheckUI(UI * UI);

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