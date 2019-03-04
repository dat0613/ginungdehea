#pragma once

#include "GameObject.h"

class Emote : public GameObject
{
public:

	enum EMOTE_TYPE { Thumbs, Smile, Sad, GG };

private:

	EMOTE_TYPE type;


public:

	void SetOption(EMOTE_TYPE type);

};