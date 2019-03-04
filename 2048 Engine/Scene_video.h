#pragma once

#include "Scene.h"
#include "Player.h"

class Scene_Video : public Scene
{
private:

	int numOfPlayer;
	Player::PLAYER_COLOR color_array[8];
	Player * Myplayer;
	float degree_array[8];
	bool flip_array[8];

public:

	virtual void Init();
	virtual void Update();
	virtual void Release();
	virtual void Render();
};