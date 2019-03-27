#include "BackGround.h"
#include "Camera.h"

BackGround::BackGround()
{

}

BackGround::~BackGround()
{

}

void BackGround::Awake()
{
	animation->SetType(Animation::TYPE::BackGround);
	SortingLayer = -1;
	transform->scale = 6.0f;
}

void BackGround::Update()
{
	transform->position = Camera::position;
}
