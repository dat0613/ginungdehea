#include "NetworkManager.h"
#include "GraphicManager.h"
#include "head.h"
#include "KillLog.h"

#include <algorithm>
#include <iostream>
#include <functional>


LPDIRECT3DTEXTURE9 GraphicManager::getImgWithType(Animation::TYPE type)
{
	LPDIRECT3DTEXTURE9 temp = LPDIRECT3DTEXTURE9();

	temp = TextureArray[type];

	return temp;
}

LPDIRECT3DTEXTURE9 GraphicManager::CreateTexture(LPCSTR file, D3DXIMAGE_INFO * info)
{
	LPDIRECT3DTEXTURE9 tex;

	if (info != NULL)
		D3DXGetImageInfoFromFile(file, info);

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

void GraphicManager::InitFont()
{
	D3DXCreateFont(device, 30, 0, FW_NORMAL,
		1, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE,
		"Arial", &font);
}

void GraphicManager::Release()
{
	for (auto texture : TextureArray)
		texture->Release();

	sprite->Release();

	font->Release();

}

void GraphicManager::CameraUpdate()
{
	D3DXVECTOR2 TargetPosition, TargetSpriteSize;
		D3DXVECTOR2 mousePos = InputManager::GetInstance()->getMousePosition();

	if (cameraTarget != nullptr)
	{
		TargetPosition = cameraTarget->getPosition();
		TargetSpriteSize = cameraTarget->getSpriteSize();
	}
	else
	{
		TargetPosition = FocusPosition;
		TargetSpriteSize = { 0.0f,0.0f };
	}



		auto targetCenter = TargetPosition - cameraPos + TargetSpriteSize * 0.5f;
		targetCenter.x = SCREENWIDTH * 0.5f;
		targetCenter.y = SCREENHEIGHT * 0.5f;

		auto fixMousePos = mousePos - cameraPos;

		int max_radius = 300;


		int x_space = 300;
		int y_space = 200;

		RECT max = { x_space,y_space,SCREENWIDTH - x_space,SCREENHEIGHT - y_space };

		if (fixMousePos.x < max.left)
			fixMousePos.x = max.left;
		if (fixMousePos.y < max.top)
			fixMousePos.y = max.top;
		if (fixMousePos.x > max.right)
			fixMousePos.x = max.right;
		if (fixMousePos.y > max.bottom)
			fixMousePos.y = max.bottom;


		auto detail = fixMousePos - targetCenter;

		D3DXVECTOR2 dif;

		dif.x = (TargetPosition.x + TargetSpriteSize.x * 0.5f) - cameraPos.x - SCREENWIDTH * 0.5f;
		dif.y = (TargetPosition.y + TargetSpriteSize.y * 0.5f) - cameraPos.y - SCREENHEIGHT * 0.5f;


	//dif += detail;

	//dif *= 0.15f;

	cameraPos += dif;
	

	int Power = 3;

	if (Shake > 0)
	{
		int ShakeDirectionX = rand() % 3;
		int ShakeDirectionY = rand() % 3;

		ShakeDirectionX--;
		ShakeDirectionY--;

		cameraPos.x += ShakeDirectionX * Power * Shake;
		cameraPos.y += ShakeDirectionY * Power * Shake;

		Shake--;
	}

	//if (cameraPos.x < cameraMax.left)
	//	cameraPos.x = cameraMax.left;
	//if (cameraPos.x + SCREENWIDTH > cameraMax.right)
	//	cameraPos.x = cameraMax.right - SCREENWIDTH;
	//if (cameraPos.y < cameraMax.top)
	//	cameraPos.y = cameraMax.top;
	//if (cameraPos.y + SCREENHEIGHT > cameraMax.bottom)
	//	cameraPos.y = cameraMax.bottom - SCREENHEIGHT;
}

void GraphicManager::SetCameraTarget(GameObject * object)
{
	if (object != nullptr)
		cameraTarget = object;
}

void GraphicManager::SetCameraTarget(D3DXVECTOR2 position)
{
	FocusPosition = position;
}

GameObject * GraphicManager::GetCameraTarget()
{
	return cameraTarget;
}

bool GraphicManager::comp(const GameObject * a, const GameObject * b)
{
	return a->zBuffer < b->zBuffer;
}

GraphicManager::~GraphicManager()
{
	Release();
}

void GraphicManager::Init(LPDIRECT3DDEVICE9 device)
{
	this->device = device;
	D3DXCreateSprite(device, &sprite);

	cameraMax.left = 0;
	cameraMax.top = 0;
	cameraMax.bottom = 4000;
	cameraMax.right = 4000;

	Shake = 0;

	InitFont();

	FocusPosition = cameraPos = D3DXVECTOR2(0.0f, 0.0f);
	
	cameraTarget = nullptr;

	TextureArray.resize(Animation::TYPE::MAXANIMATION);

	TextureArray[Animation::TYPE::PLAYER_BLUE_IDLE] = CreateTexture("./Resource/Image/Player_blue_idle.png");
	TextureArray[Animation::TYPE::PLAYER_BLUE_RUN] = CreateTexture("./Resource/Image/Player_blue_run.png");
	TextureArray[Animation::TYPE::PLAYER_BLUE_ROLL] = CreateTexture("./Resource/Image/Player_blue_roll.png");

	TextureArray[Animation::TYPE::PLAYER_GRAY_IDLE] = CreateTexture("./Resource/Image/Player_gray_idle.png");
	TextureArray[Animation::TYPE::PLAYER_GRAY_RUN] = CreateTexture("./Resource/Image/Player_gray_run.png");
	TextureArray[Animation::TYPE::PLAYER_GRAY_ROLL] = CreateTexture("./Resource/Image/Player_gray_roll.png");

	TextureArray[Animation::TYPE::PLAYER_NEON_IDLE] = CreateTexture("./Resource/Image/Player_neon_idle.png");
	TextureArray[Animation::TYPE::PLAYER_NEON_RUN] = CreateTexture("./Resource/Image/Player_neon_run.png");
	TextureArray[Animation::TYPE::PLAYER_NEON_ROLL] = CreateTexture("./Resource/Image/Player_neon_roll.png");

	TextureArray[Animation::TYPE::PLAYER_PINK_IDLE] = CreateTexture("./Resource/Image/Player_pink_idle.png");
	TextureArray[Animation::TYPE::PLAYER_PINK_RUN] = CreateTexture("./Resource/Image/Player_pink_run.png");
	TextureArray[Animation::TYPE::PLAYER_PINK_ROLL] = CreateTexture("./Resource/Image/Player_pink_roll.png");

	TextureArray[Animation::TYPE::PLAYER_PURPLE_IDLE] = CreateTexture("./Resource/Image/Player_purple_idle.png");
	TextureArray[Animation::TYPE::PLAYER_PURPLE_RUN] = CreateTexture("./Resource/Image/Player_purple_run.png");
	TextureArray[Animation::TYPE::PLAYER_PURPLE_ROLL] = CreateTexture("./Resource/Image/Player_purple_roll.png");

	TextureArray[Animation::TYPE::PLAYER_RED_IDLE] = CreateTexture("./Resource/Image/Player_red_idle.png");
	TextureArray[Animation::TYPE::PLAYER_RED_RUN] = CreateTexture("./Resource/Image/Player_red_run.png");
	TextureArray[Animation::TYPE::PLAYER_RED_ROLL] = CreateTexture("./Resource/Image/Player_red_roll.png");

	TextureArray[Animation::TYPE::PLAYER_REVERSE_IDLE] = CreateTexture("./Resource/Image/Player_reverse_idle.png");
	TextureArray[Animation::TYPE::PLAYER_REVERSE_RUN] = CreateTexture("./Resource/Image/Player_reverse_run.png");
	TextureArray[Animation::TYPE::PLAYER_REVERSE_ROLL] = CreateTexture("./Resource/Image/Player_reverse_roll.png");

	TextureArray[Animation::TYPE::PLAYER_YELLOW_IDLE] = CreateTexture("./Resource/Image/Player_yellow_idle.png");
	TextureArray[Animation::TYPE::PLAYER_YELLOW_RUN] = CreateTexture("./Resource/Image/Player_yellow_run.png");
	TextureArray[Animation::TYPE::PLAYER_YELLOW_ROLL] = CreateTexture("./Resource/Image/Player_yellow_roll.png");

	TextureArray[Animation::TYPE::EnemyKillLog] = CreateTexture("./Resource/Image/EnemyKillLog.png");
	TextureArray[Animation::TYPE::AllyKillLog] = CreateTexture("./Resource/Image/AllyKillLog.png");

	TextureArray[Animation::TYPE::GunBox] = CreateTexture("./Resource/Image/GunBox.png");

	TextureArray[Animation::TYPE::DieEffect] = CreateTexture("./Resource/Image/DieEffect.png");

	TextureArray[Animation::TYPE::Ground] = CreateTexture("./Resource/Image/TestBackGround__.png");
	TextureArray[Animation::TYPE::BackGround] = CreateTexture("./Resource/Image/TestBackGround__.png");
	TextureArray[Animation::TYPE::Test2] = CreateTexture("./Resource/Image/Test2.png");
	TextureArray[Animation::TYPE::Test3] = CreateTexture("./Resource/Image/test3.bmp");

	TextureArray[Animation::TYPE::Bullet] = CreateTexture("./Resource/Image/bullet.png");

	TextureArray[Animation::Pistol] = CreateTexture("./Resource/Image/Pistol.png");
	TextureArray[Animation::TYPE::AssaultRifle] = CreateTexture("./Resource/Image/AssaultRifle.png");
	TextureArray[Animation::TYPE::SniperRifle] = CreateTexture("./Resource/Image/SniperRifle.png");
}

void GraphicManager::Render()
{
	static int FPS;
	static int frame;
	static int lastTime;

	if (lastTime != time(NULL))
	{
		FPS = frame;
		frame = 0;
		lastTime = time(NULL);
	}
	frame++;

	//RenderText(D3DXVECTOR2(0, 0), D3DXCOLOR(255, 255, 255, 255), 0, "FPS : %d", FPS);		//fps 그리기

	D3DXVECTOR2 mousePos = InputManager::GetInstance()->getMousePosition();

	D3DXMATRIX BackGroundMatrix, BackGroundZBuffer;

	//renderTargetList->sort(comp);

	std::list<GameObject *>::iterator iter;			//std::list 안에 있는 오브젝트를 가리키기 위한 변수

	iter = renderTargetList->begin();						//list의 제일 앞을 가리킴

	while (iter != renderTargetList->end())				//list의 제일 마지막 까지 순회할때 까지 루프
	{
		GameObject * nowObject = *iter;				//형변환(?)

		if (nowObject->enabled && nowObject->visible)
		{
			//그려야 하는 객체의 그림, 위치, 각도 등 을 불러와 계산하여 그림

			D3DXMATRIX matrix, rotation, position, scale, zBuffer;
			D3DXVECTOR2 target_object_position = nowObject->getPosition();
			D3DXVECTOR2 target_object_sprite_size = nowObject->getSpriteSize();
			D3DXVECTOR2 target_object_size = nowObject->getSize();

			float target_object_angle = nowObject->getDegree();

			auto& anim = nowObject->GetAnimation();

			D3DXVECTOR2 retouch(0.0f, 0.0f);

			if (target_object_size.x < 0)
			{
				retouch = target_object_sprite_size;
			}

			if (!nowObject->isUI)
				D3DXMatrixTranslation(&position, target_object_position.x - cameraPos.x + retouch.x, target_object_position.y - cameraPos.y, 0.0f);
			else
				D3DXMatrixTranslation(&position, target_object_position.x + retouch.x, target_object_position.y, 0.0f);
			
			D3DXMatrixTranslation(&zBuffer, 0.0f, 0.0f, nowObject->zBuffer);
			D3DXMatrixRotationZ(&rotation, D3DXToRadian(target_object_angle));
			D3DXMatrixScaling(&scale, target_object_size.x, target_object_size.y, 0);

			auto texture = getImgWithType(anim.GetType());

			anim.Update();

			matrix = scale * rotation * position;// *zBuffer;

			sprite->SetTransform(&matrix);

			sprite->Begin(D3DXSPRITE_ALPHABLEND);

			device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
			device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
			device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);

			RECT rc;
			rc.left = anim.nowFrame.x;
			rc.top = 0;
			rc.right = anim.nowFrame.x + anim.frameSize.x;
			rc.bottom = anim.frameSize.y;

			sprite->Draw(texture, &rc, NULL, NULL, nowObject->GetColor());
			sprite->End();

			if (nowObject->shadow)
			{
				D3DXMatrixTranslation(&position, target_object_position.x - cameraPos.x + retouch.x, target_object_position.y - cameraPos.y + target_object_sprite_size.y * 1.5f, 0.0f);
				D3DXMatrixScaling(&scale, target_object_size.x, -target_object_size.y * 0.5f, 0);

				matrix = scale * rotation * position;// *zBuffer;

				sprite->SetTransform(&matrix);

				sprite->Begin(D3DXSPRITE_ALPHABLEND);

				device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
				device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
				device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);

				sprite->Draw(texture, &rc, NULL, NULL, D3DCOLOR_ARGB(100, 0, 0, 0));
				sprite->End();
			}

			if (nowObject->getType() == GameObject::KillLog)
			{

				auto top_space = 10.0f;
				auto left_space = 10.0f;

				auto kill_log = (KillLog *)nowObject;

				auto killer_color = kill_log->GetKillerColor();
				auto victim_color = kill_log->GetVictimColor();

				D3DXVECTOR2 position = { 0.0f,0.0f };
				D3DXMATRIX kill_log_matrix;
				auto kill_log_position = kill_log->getPosition();

				position.x = kill_log_position.x + left_space;
				position.y = kill_log_position.y + top_space;

				//RenderText(position, D3DXCOLOR(255, 0, 0, 255), 0, "%d", killerID);

				RECT rc = { 0,9,50,50 + 9 };
				D3DXMatrixTranslation(&kill_log_matrix, position.x, position.y, 0.0f);
				
				sprite->SetTransform(&kill_log_matrix);

				sprite->Begin(D3DXSPRITE_ALPHABLEND);

				device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
				device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
				device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);

				sprite->Draw(TextureArray[(int)killer_color * 3], &rc, NULL, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
				sprite->End();



				position.x = kill_log_position.x + kill_log->getSpriteSize().x - left_space - rc.right - rc.left;
				D3DXMatrixTranslation(&kill_log_matrix, position.x, position.y, 0.0f);

				//RenderText(position, D3DXCOLOR(255, 0, 0, 255), 0, "%d", VictimID);

				sprite->SetTransform(&kill_log_matrix);

				sprite->Begin(D3DXSPRITE_ALPHABLEND);

				device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
				device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
				device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);

				sprite->Draw(TextureArray[(int)victim_color * 3], &rc, NULL, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
				sprite->End();


			
			
			}
		}

		iter++;
	}

	while (!fontEventQ.empty())
	{
		FontEvent * fontEvent = fontEventQ.front();

		RECT rt = { fontEvent->x,fontEvent->y,0,0 };
		font->DrawTextA(NULL, fontEvent->str, -1, &rt, DT_NOCLIP, fontEvent->color);

		delete fontEvent;

		fontEventQ.pop();
	}
}

void GraphicManager::RenderText(D3DXVECTOR2 position, D3DCOLOR color, int size, char * format, ...)
{
	char buff[1024];
	va_list arglist;

	va_start(arglist, format);
	vsprintf_s(buff, format, arglist);
	va_end(arglist);

	FontEvent * font_event = new FontEvent();
	font_event->Init(buff, position.x, position.y, 0, color);

	pushFontQ(font_event);
}

void GraphicManager::pushFontQ(FontEvent * evnt)
{
	fontEventQ.push(evnt);
}

D3DXVECTOR2 GraphicManager::getSpriteSize(Animation::TYPE type)
{
	LPDIRECT3DTEXTURE9 texture = getImgWithType(type);

	D3DSURFACE_DESC desc;

	texture->GetLevelDesc(0, &desc);


	D3DXVECTOR2 sprite_size;
	sprite_size.x = desc.Width;
	sprite_size.y = desc.Height;

	return sprite_size;
}

void GraphicManager::setRenderTargetList(std::list<GameObject*>* list)
{
	this->renderTargetList = list;
}

D3DXVECTOR2 GraphicManager::GetCameraPosition()
{
	return cameraPos;
}

D3DXVECTOR2 GraphicManager::ToCameraCoord(D3DXVECTOR2 pos)
{
	return pos - cameraPos;
}

void GraphicManager::AddShake(int shake)
{
	this->Shake += shake;
}

void GraphicManager::SetShake(int shake)
{
	this->Shake = shake;
}

int GraphicManager::GetShake()
{
	return Shake;
}
