#pragma once

#include "GameObject.h"

class Bullet : public GameObject
{
private:

	int OwnerID;				//���� �߻��� �÷��̾��� ID	
	D3DXVECTOR2 StartPosition;	//�Ѿ��� ����� ��ġ
	D3DXVECTOR2 Direction;		//�Ѿ��� ����
	float speed;				//ź��
	float effectiveRange;		//��ȿ ��Ÿ�
	float power;				//��ġ�� �Ÿ�

public:

	void Init(GameObject::TYPE type);
	void Update();
	void SetOption(int OwnerID, float speed, D3DXVECTOR2 targetPos, float effectiveRange, float power);
	void OnTriggerEnter(GameObject * Object);

	int GetOwnerID();

	float GetPower();

	D3DXVECTOR2 GetDir();
};