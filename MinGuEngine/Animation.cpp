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
			end = false;
		}
		else if (-nowFrame.x  + frameSize.x < imageSize.x)
		{//	Update 순서때문에 미리 애니메이션이 끝났는지 체크 해야함.
			end = true;
		}
		else
		{ 
			nowFrame.x = 0.0f;
			end = false;
		}
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
	
	timePerFrame = -1;
	frameSize = imageSize;

	switch (type)
	{
	case Animation::TYPE::Explosion:
		timePerFrame = 30;
		frameSize = D3DXVECTOR2(200, 200);
		break;
	}
}

Animation::TYPE Animation::GetType()
{
	return this->type;
}
