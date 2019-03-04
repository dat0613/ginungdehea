#include "DieEffect.h"
#include "GraphicManager.h"

void DieEffect::Init(GameObject::TYPE type)
{
	GameObject::Init(type);
	isUI = true;
	color = D3DCOLOR_ARGB(255, 0, 0, 0);
	//visible = false;
}

void DieEffect::Update()
{
	//int max = 255;
	//int min = 190;

	//float radian = D3DXToRadian(clock());

	//int alpha =  (max - min) * 0.5f * sin(radian * 0.3) + max - (max - min) * 0.5f;
	//color = D3DCOLOR_ARGB(alpha, 255, 0, 0);
	//GraphicManager::GetInstance()->RenderText(GraphicManager::GetInstance()->ToCameraCoord({0.0f,0.0f}), D3DXCOLOR(255, 0, 255, 255), 0, "%d", alpha);
}

void DieEffect::LateUpdate()
{
	zBuffer = 2.0f;
}
