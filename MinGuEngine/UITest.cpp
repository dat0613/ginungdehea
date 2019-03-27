#include "UITest.h"
#include "Camera.h"

UITest::UITest()
{

}

UITest::~UITest()
{

}

void UITest::Awake()
{
	animation->SetType(Animation::TYPE::UITest);
	transform->position = { 200.0f, 200.0f };
	boxcollider2d->size = { 100.0f, 100.0f };
}

void UITest::Update()
{

}

void UITest::OnClicking()
{
	Camera::ZoomIn();
}

void UITest::OnClick()
{
	printf("버튼 눌림!\n");
}
