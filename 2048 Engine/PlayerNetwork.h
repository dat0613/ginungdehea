#pragma once

#include <MinNet.h>
#include "Player.h"

class PlayerNetwork : public Player
{
private:


public:
	D3DXVECTOR2 mousePos;
	MinNet::MinNetUser * user;
	void Init(GameObject::TYPE type);
	void Render();
	void Update();
	void OnTriggerEnter(GameObject * obj);
};