#include "Animation.h"

#include "GraphicManager.h"

Animation::Animation()
{
	type = (TYPE)-1;
}

Animation::~Animation()
{

}

void Animation::SetType(TYPE type)
{
	if (this->type == type)
		return;

	lastChangeTime = clock();
	imageSize = GraphicManager::GetInstance()->getSpriteSize(type);
	nowFrame = D3DXVECTOR2(0.0f, 0.0f);
	this->type = type;

	switch (type)
	{
	case TYPE::PLAYER_BLUE_IDLE:
	case TYPE::PLAYER_GRAY_IDLE:
	case TYPE::PLAYER_NEON_IDLE:
	case TYPE::PLAYER_PINK_IDLE:
	case TYPE::PLAYER_PURPLE_IDLE:
	case TYPE::PLAYER_RED_IDLE:
	case TYPE::PLAYER_REVERSE_IDLE:
	case TYPE::PLAYER_YELLOW_IDLE:
		changeTime = 200;
		frameSize = D3DXVECTOR2(60.0f, 94.0f);
		break;

	case TYPE::PLAYER_BLUE_RUN:
	case TYPE::PLAYER_GRAY_RUN:
	case TYPE::PLAYER_NEON_RUN:
	case TYPE::PLAYER_PINK_RUN:
	case TYPE::PLAYER_PURPLE_RUN:
	case TYPE::PLAYER_RED_RUN:
	case TYPE::PLAYER_REVERSE_RUN:
	case TYPE::PLAYER_YELLOW_RUN:
		changeTime = 55;
		frameSize = D3DXVECTOR2(100.0f, 100.0f);
		//imageSize = D3DXVECTOR2(60.0f, 100.0f);
		break;

	case TYPE::PLAYER_BLUE_ROLL:
	case TYPE::PLAYER_GRAY_ROLL:
	case TYPE::PLAYER_NEON_ROLL:
	case TYPE::PLAYER_PINK_ROLL:
	case TYPE::PLAYER_PURPLE_ROLL:
	case TYPE::PLAYER_RED_ROLL:
	case TYPE::PLAYER_REVERSE_ROLL:
	case TYPE::PLAYER_YELLOW_ROLL:
		changeTime = 50;
		frameSize = D3DXVECTOR2(100.0f, 100.0f);
		break;
		

	default:
		changeTime = 0;
		frameSize = imageSize;
		break;
	}
}

Animation::TYPE Animation::GetType()
{
	return type;
}

D3DXVECTOR2 Animation::GetFrameSize()
{
	return frameSize;
}

void Animation::Update()
{
	if (changeTime == 0)
		return;


	DWORD curTime = clock();

	if (lastChangeTime + changeTime <= curTime)
	{
		lastChangeTime = curTime;
		
		if (nowFrame.x + frameSize.x < imageSize.x)
		{
		nowFrame.x += frameSize.x;
		}
		else
			nowFrame.x = 0.0f;
	}
}
