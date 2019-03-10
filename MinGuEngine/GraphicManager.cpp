#include "GraphicManager.h"
#include "Camera.h"

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
	D3DXMATRIX matrix, rotation, position, scale, Pcenter, Ncenter;
	auto transform = gameObject->transform;
	auto animation = gameObject->animation;
	D3DXMatrixTranslation(&position, transform->position.x, transform->position.y, 0.0f);
	D3DXMatrixTranslation(&Ncenter, -animation->frameSize.x * 0.5f, -animation->frameSize.y * 0.5f, 0.0f);
	D3DXMatrixTranslation(&Pcenter, animation->frameSize.x * 0.5f, animation->frameSize.y * 0.5f, 0.0f);
	D3DXMatrixRotationZ(&rotation, transform->rotation);
	D3DXMatrixScaling(&scale, transform->scale, transform->scale, 0.0f);
	
	auto texture = textureVector[animation->type];
	auto center = animation->frameSize * 0.5f;

	matrix = scale * Ncenter *rotation * position;

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

void GraphicManager::Init(LPDIRECT3DDEVICE9 device)
{
	this->device = device;

	D3DXCreateSprite(device, &sprite);

	textureVector.resize(Animation::TYPE::MAXANIMATION);
	textureVector[Animation::TYPE::Cube] = CreateTexture(L"./Resource/Image/Cube.png");
}

void GraphicManager::Render(list<GameObject*>& gameObjectList)
{
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
