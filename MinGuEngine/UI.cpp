#include "UI.h"

UI::UI()
{
	isUI = true;
}

UI::~UI()
{

}

void UI::OnMouse(bool On)
{
	if(On)
		animation->color = D3DCOLOR_ARGB(255, 100, 100, 100);
	else
		animation->color = D3DCOLOR_ARGB(255, 255, 255, 255);
}

void UI::OnClick()
{

}

void UI::Update()
{

}