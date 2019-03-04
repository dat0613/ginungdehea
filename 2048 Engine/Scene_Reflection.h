#pragma once

#include "Scene.h"

class Scene_Reflection : public Scene
{
private:


public:

	virtual void Init();
	virtual void Update();
	virtual void Release();
	virtual void Render();

	virtual ~Scene_Reflection();


};