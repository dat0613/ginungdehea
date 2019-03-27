#pragma once

#include "GameObject.h"

class UI : public GameObject
{
private:

public:

	UI();
	~UI();

	void OnMouse(bool On);
	virtual void OnClick();
	virtual void OnClicking();
	void Update();
};