#pragma once

#include "Singleton.h"

#include <d3dx9.h>
#include <list>
#include <vector>
#include "GameObject.h"

using namespace std;

class GraphicManager : public Singleton<GraphicManager>
{
private:

	LPDIRECT3DDEVICE9 device;
	LPD3DXSPRITE sprite;
	LPDIRECT3DTEXTURE9 CreateTexture(LPCWSTR file);
	vector<LPDIRECT3DTEXTURE9> textureVector;
	void RenderGameObject(GameObject * gameObject);

public:
	
	GraphicManager();
	void Init(LPDIRECT3DDEVICE9 device);
	void Render(list<GameObject *>& gameObjectList);
	void Release();
	LPDIRECT3DTEXTURE9 GetTexture(Animation::TYPE type);
	D3DXVECTOR2 GetTextureSize(Animation::TYPE type);
	~GraphicManager();
};