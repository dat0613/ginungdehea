#include "Hole.h"
#include "GraphicManager.h"

void Hole::Init(GameObject::TYPE type)
{
	GameObject::Init(type);

	SetIsCollider(true);
}

void Hole::Update()
{
//	GraphicManager::GetInstance()->RenderText(GraphicManager::GetInstance()->ToCameraCoord(D3DXVECTOR2(0.0f,0.0f)), D3DXCOLOR(255, 255, 0, 255), 0, "%.f,%.f", 0.0f, 0.0f);
//	GraphicManager::GetInstance()->RenderText(GraphicManager::GetInstance()->ToCameraCoord(position), D3DXCOLOR(255, 255, 0, 255), 0, "%.f,%.f", position.x, position.y);
//	GraphicManager::GetInstance()->RenderText(GraphicManager::GetInstance()->ToCameraCoord(position + spriteSize), D3DXCOLOR(255, 255, 0, 255), 0, "%.f,%.f", spriteSize.x, spriteSize.y);
}

void Hole::LateUpdate()
{

}

void Hole::FastSetting(float x, float y, float width, float height)
{
	float space = 60.0f;
	setPosition(x + space, y);
	setSpriteSize(width - space * 2, height - 94);
}

void Hole::OnTriggerEnter(GameObject * obj)
{
	//	GraphicManager::GetInstance()->RenderText(GraphicManager::GetInstance()->ToCameraCoord(position + spriteSize), D3DXCOLOR(255, 0, 0, 255), 0, "Ãæµ¹");
}