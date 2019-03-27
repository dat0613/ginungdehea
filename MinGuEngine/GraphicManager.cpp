#include "GraphicManager.h"
#include "Camera.h"
#include "Info.h"
#include <algorithm>

using namespace std;

LPDIRECT3DTEXTURE9 GraphicManager::CreateTexture(LPCWSTR file)
{
	LPDIRECT3DTEXTURE9 tex;

	D3DXCreateTextureFromFileEx(device,
		file,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		1,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		1,
		1,
		NULL,
		NULL,
		NULL,
		&tex);

	return tex;
}

void GraphicManager::RenderGameObject(GameObject * gameObject)
{
	D3DXMATRIX matrix, rotationM, positionM, scaleM, center, Pcenter, uiPosition;
	auto scale = gameObject->transform->scale;
	auto animation = gameObject->animation;
	auto frameSize = animation->frameSize;
	auto position = gameObject->transform->position - (frameSize * 0.5f);
	auto realPosition = gameObject->transform->position;
	realPosition.x += SCREENWIDTH * 0.5f;
	realPosition.y += SCREENHEIGHT * 0.5f;
	auto rotation = gameObject->transform->rotation;

	auto texture = textureVector[animation->type];

	auto sign = (gameObject->flip) ? (-1) : (1);

	D3DXMatrixScaling(&scaleM, scale * sign, scale, 0.0f);
	D3DXMatrixTranslation(&positionM, realPosition.x - Camera::position.x, realPosition.y - Camera::position.y, 0.0f);
	D3DXMatrixTranslation(&center, -gameObject->transform->center.x, -gameObject->transform->center.y, 0.0f);
	D3DXMatrixRotationZ(&rotationM, D3DXToRadian(rotation));



	if (!gameObject->isUI)
	{
		matrix = center * scaleM * rotationM * positionM;
		matrix = matrix * Camera::camMatrix;
	}
	else
	{
		D3DXMatrixTranslation(&uiPosition, position.x, position.y, 0.0f);
		matrix = uiPosition;
	}

	sprite->SetTransform(&matrix);

	sprite->Begin(D3DXSPRITE_ALPHABLEND);

	RECT rc;
	rc.left = animation->nowFrame.x;
	rc.top = 0;
	rc.right = animation->nowFrame.x + animation->frameSize.x;
	rc.bottom = animation->frameSize.y;

	sprite->Draw(texture, &rc, NULL, NULL, animation->color);
	sprite->End();
}

GraphicManager::GraphicManager()
{

}

bool cmp(const GameObject * o1, const GameObject * o2)
{
	if (o1->SortingLayer < o2->SortingLayer)
		return true;

	return false;
}

void GraphicManager::Init(LPDIRECT3DDEVICE9 device)
{
	this->device = device;

	D3DXCreateSprite(device, &sprite);

	textureVector.resize(Animation::TYPE::MAXANIMATION);
	textureVector[Animation::TYPE::MiddleTank] = CreateTexture(L"./Resource/Image/MiddleTank.png");
	textureVector[Animation::TYPE::Negev] = CreateTexture(L"./Resource/Image/Negev.png");
	textureVector[Animation::TYPE::UITest] = CreateTexture(L"./Resource/Image/UI.png");
	textureVector[Animation::TYPE::Hole] = CreateTexture(L"./Resource/Image/Hole.png");
	textureVector[Animation::TYPE::Ground] = CreateTexture(L"./Resource/Image/Ground.png");
	textureVector[Animation::TYPE::BackGround] = CreateTexture(L"./Resource/Image/BackGround.png");
	textureVector[Animation::TYPE::Bullet_120mm] = CreateTexture(L"./Resource/Image/120mm.png");
	textureVector[Animation::TYPE::Bullet_88mm] = CreateTexture(L"./Resource/Image/88mm.png");
	textureVector[Animation::TYPE::Explosion] = CreateTexture(L"./Resource/Image/Explosion.png");
	textureVector[Animation::TYPE::MachineGun] = CreateTexture(L"./Resource/Image/MachineGun.png");
}

void GraphicManager::Render(list<GameObject*>& gameObjectList)
{

	gameObjectList.sort(cmp);

	for (auto gameObject : gameObjectList)
	{
		RenderGameObject(gameObject);
	}
}


void GraphicManager::Release()
{

}

LPDIRECT3DTEXTURE9 GraphicManager::GetTexture(Animation::TYPE type)
{
	return textureVector[type];
}

D3DXVECTOR2 GraphicManager::GetTextureSize(Animation::TYPE type)
{
	auto texture = GetTexture(type);

	D3DSURFACE_DESC desc;
	texture->GetLevelDesc(0, &desc);

	return D3DXVECTOR2(desc.Width, desc.Height);
}

GraphicManager::~GraphicManager()
{

}
