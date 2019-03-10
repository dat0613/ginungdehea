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

public:
	
	virtual void Init();
	TYPE type;
	void AutoUpdate();
	void AutoLateUpdate();
	virtual void Update();
	void AddGameObject(GameObject * object);
	void AutoRender();

};