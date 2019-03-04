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
	float degree;			//���ʺй� ��

	bool isCollider;	//�浹 ������ �ؾ��ϴ� ��ü����
	bool isCanMove;		//�����̴� ��ü���� (�����̴� ��ü�� �������� isCollider �� true �� ��� ��ü��� �浹 üũ�� ��)
	float velocity;		//�����̴� �ӵ�

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

	bool enabled;		//�ı� �Ұ����� ���� ����������. false �� �ı�.
	bool visible;		//�׸������� �׸��� ���� ������. true �� �׸���

	//��� ���� �Լ��� ������ ���ӿ�����Ʈ�� �����͸� ��ȯ�Ͽ� ����ؼ� �����Ҽ� �ְ� �Ͽ���.
	friend GameObject * Instantiate(GameObject::TYPE type);			//���� ������Ʈ�� Ÿ���� �޾� ��ü�� ������.

	//��� �ı� �Լ��� ���ӿ�����Ʈ�� 1������ ���� ��Ȱ��ȭ �Ǿ� �ִ� �� ���� �����ӿ� GameManager �� �ִ� nowScene �� Update() �Լ��� ���Ͽ� �ı���.
	void Destroy();											//���� ������Ʈ �ڽ��� �ı� ��.
	friend void Destroy(GameObject * obj);							//�����ͷ� �޾ƿ� ���� ������Ʈ�� �ı���.

	std::vector<D3DXVECTOR2> GetVertices();
	
	D3DXVECTOR2 GetCenter();

	int ID;
	bool shadow;
	float zBuffer;

	virtual void OnTriggerEnter(GameObject * obj);
};