#include "GraphicManager.h"
#include "Camera.h"
#include "Info.h"

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
	D3DXMATRIX matrix, CamMatrix, rotationM, positionM, scaleM, center, CamRotation, NCamCenter, PCamCenter;
	auto position = gameObject->transform->position;
	auto scale = gameObject->transform->scale;
	auto animation = gameObject->animation;
	auto frameSize = animation->frameSize;
	auto rotation = gameObject->transform->rotation;

	D3DXMatrixTranslation(&positionM, position.x * Camera::scope - Camera::position.x * Camera::scope + SCREENWIDTH * 0.5f, position.y * Camera::scope - Camera::position.y * Camera::scope + SCREENHEIGHT * 0.5f, 0.0f);
	D3DXMatrixTranslation(&center, -frameSize.x * Camera::scope * 0.5f, -frameSize.y * Camera::scope * 0.5f, 0.0f);
	D3DXMatrixScaling(&scaleM, scale * Camera::scope, scale * Camera::scope, 0.0f);
	D3DXMatrixRotationZ(&rotationM, D3DXToRadian(rotation));

	//D3DXMatrixTranslation(&NCamCenter, Camera::scope * (position.x - frameSize.x * 0.5f + Camera::position.x) + SCREENWIDTH * 0.5f, Camera::scope * (position.y - frameSize.y * 0.5f + Camera::position.y) + SCREENHEIGHT * 0.5f, 0.0f);

	D3DXMatrixRotationZ(&CamRotation, D3DXToRadian(Camera::degree));

	auto texture = textureVector[animation->type];

	CamMatrix = NCamCenter * CamRotation;
	matrix = scaleM * center * rotationM * positionM;

	matrix *= CamMatrix;

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
	textureVector[Animation::TYPE::Negev] = CreateTexture(L"./Resource/Image/Negev.png");
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
