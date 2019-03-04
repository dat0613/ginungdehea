#pragma once

#include "GameObject.h"
#include "FontEvent.h"
#include <d3d9.h>
#include <d3dx9.h>
#include "Singleton.h"
#include <queue>
#include "InputManager.h"
#include <list>
#include "Animation.h"

class GraphicManager : public Singleton<GraphicManager>
{
private:
	
	LPDIRECT3DDEVICE9 device;

	std::queue<FontEvent *> fontEventQ;

	std::list<GameObject *> *renderTargetList;

	LPD3DXFONT font;

	LPD3DXSPRITE sprite;

	//LPDIRECT3DTEXTURE9 *TextureArray;

	LPDIRECT3DTEXTURE9 getImgWithType(Animation::TYPE type);
	LPDIRECT3DTEXTURE9 CreateTexture(LPCSTR  file, D3DXIMAGE_INFO * info = NULL);

	D3DXVECTOR2 cameraPos;
	GameObject * cameraTarget;
	D3DXVECTOR2 FocusPosition;
	std::vector<LPDIRECT3DTEXTURE9> TextureArray;
	
	void InitFont();
	
	void pushFontQ(FontEvent * evnt);

	int Shake;

	RECT cameraMax;

	static bool comp(const GameObject * a,const GameObject * b);

public:
	~GraphicManager();
	void Init(LPDIRECT3DDEVICE9 device);
	void Render();
	void Release();
	void CameraUpdate();
	void SetCameraTarget(GameObject * object);
	void SetCameraTarget(D3DXVECTOR2 position);

	GameObject * GetCameraTarget();


	void RenderText(D3DXVECTOR2 position, D3DCOLOR color,int size, char * format, ...);

	D3DXVECTOR2 getSpriteSize(Animation::TYPE type);
	void setRenderTargetList(std::list<GameObject *> * list);

	D3DXVECTOR2 GetCameraPosition();

	D3DXVECTOR2 ToCameraCoord(D3DXVECTOR2 pos);		//D3DXVECTOR2 ¸¦ Ä«¸Þ¶ó¿¡ ¸Â°Ô²û ¹Ù²ãÁÜ

	void AddShake(int shake);
	void SetShake(int shake);
	int GetShake();

};