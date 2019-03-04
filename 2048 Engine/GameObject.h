#pragma once

#include <ctime>
#include <cmath>

#include <d3dx9.h>
#include <d3d9.h>
#include "Animation.h"

#include <vector>

#define _USE_MATH_DEFINES


class GameObject
{
public:
	enum TYPE { Player, PlayerNetwork, KillLog,DieEffect, GunBox, Pistol,AssaultRifle, SniperRifle, Bullet, Test1, Test2, Test3, Wall, Hole, TestBackGround,Object,Controller, MAXOBJECT };
	enum { NOT_NEED_ID = -2, NEED_ID = -1 };

private:
	
	clock_t deltaTime;
	
	void qsort(std::vector<D3DXVECTOR2>& v, std::vector<float>& radian_array, int s, int e);

protected:

	TYPE type;
	Animation animation;

	D3DCOLOR color;
	
	D3DXVECTOR2 spriteSize;
	D3DXVECTOR2 position;
	D3DXVECTOR2 size;
	float degree;			//육십분법 값

	bool isCollider;	//충돌 판정을 해야하는 물체인지
	bool isCanMove;		//움직이는 물체인지 (움직이는 물체를 기준으로 isCollider 가 true 인 모든 객체들과 충돌 체크를 함)
	float velocity;		//움직이는 속도

	float lerp(float p1, float p2, float d1); 
	
public:

	bool operator < (const GameObject &a);
	bool operator < (const GameObject *a);

	void UpdateZBuffer();

	bool isUI;

	virtual void Init(TYPE type);
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();
	virtual void Release();

	void SetDeltaTime(clock_t delta);
	clock_t GetDeltaTime();

	D3DXCOLOR GetColor();
	void SetColor(D3DXCOLOR color);
	

	void setSize(float x, float y);
	void setSize(D3DXVECTOR2 size);
	D3DXVECTOR2 getSize();

	D3DXVECTOR2 getPosition();
	void setPosition(float x, float y);
	void setPosition(D3DXVECTOR2 set);
	
	float getDegree();
	void setDegree(float degree);

	TYPE getType();
	void setType(TYPE type);

	float GetVelocity();
	void SetVelocity(float velocity);

	D3DXVECTOR2 getSpriteSize();
	void setSpriteSize(float x, float y);
	void setSpriteSize(D3DXVECTOR2 size);

	bool GetIsCollier();
	void SetIsCollider(bool isCollider);

	bool GetIsCanMove();
	void SetIsCanMove(bool isCanMove);

	Animation& GetAnimation();
	void SetAnimation(Animation::TYPE type);

	bool enabled;		//파괴 할것인지 하지 않을것인지. false 가 파괴.
	bool visible;		//그릴것인지 그리지 않을 것인지. true 가 그리기

	//모든 생성 함수는 생성된 게임오브젝트의 포인터를 반환하여 계속해서 관리할수 있게 하였음.
	friend GameObject * Instantiate(GameObject::TYPE type);			//게임 오브젝트의 타입을 받아 객체를 생성함.

	//모든 파괴 함수는 게임오브젝트가 1프레임 동안 비활성화 되어 있는 후 다음 프레임에 GameManager 에 있는 nowScene 의 Update() 함수에 의하여 파괴됨.
	void Destroy();											//게임 오브젝트 자신을 파괴 함.
	friend void Destroy(GameObject * obj);							//포인터로 받아온 게임 오브젝트를 파괴함.

	std::vector<D3DXVECTOR2> GetVertices();
	
	D3DXVECTOR2 GetCenter();

	int ID;
	bool shadow;
	float zBuffer;

	virtual void OnTriggerEnter(GameObject * obj);
};