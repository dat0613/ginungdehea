#include "UITest.h"

UITest::UITest()
{

}

UITest::~UITest()
{

}

void UITest::Awake()
{
	animation->SetType(Animation::TYPE::UITest);
	transform->position = { 200, 200 };
	boxcollider2d->size = { 100, 100 };
}

void UITest::Update()
{

}

void UITest::OnClick()
{
	printf("³ë¹«Çö!\n");
}
