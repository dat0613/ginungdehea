#include "Animation.h"
#include "GraphicManager.h"
#include <ctime>

Animation::Animation()
{
	type = NONE;
	color = D3DCOLOR_ARGB(255, 255, 255, 255);
	nowFrame = imageSize = frameSize = { 0.0f, 0.0f };
	timePerFrame = lastFrameTime = 0;
}

void Animation::Update()
{
	if (timePerFrame == -1)
		return;

	DWORD curTime = clock();
	if (lastFrameTime + timePerFrame <= curTime)
	{
		lastFrameTime = curTime;
		if (nowFrame.x + frameSize.x < imageSize.x)
		{
			nowFrame.x += frameSize.x;
		}
		else
			nowFrame.x = 0.0f;
	}

}

void Animation::LateUpdate()
{

}

Animation::~Animation()
{

}

void Animation::SetType(TYPE type)
{
	if (this->type == type)
		return;

	this->type = type;

	imageSize = GraphicManager::get()->GetTextureSize(type);
	

	switch (type)
	{
	case Cube:
	case Negev:
	case UITest:
		timePerFrame = -1;
		frameSize = imageSize;
		break;

	}
}

Animation::TYPE Animation::GetType()
{
	return this->type;
}
