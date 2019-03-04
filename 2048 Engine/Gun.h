#pragma once

#include "GameObject.h"

class Gun : public GameObject
{
private:

	int BulletPerMagazine;		//�� źâ �� �� �Ѿ�
	int MaxBullet;			//������ �� �ִ� �ִ� �Ѿ��� ����

	int nowBullet;		//���� ���� �ִ� źâ�� ���� �Ѿ��� ����
	int leftBullet;		//���� ���� �ִ� �Ѿ��� �����ϰ� ���� �Ѿ��� ����

	DWORD reloadTime;	//������ �ϴµ� �ɸ��� �ð�
	DWORD reloadStartTime;	//�������� ������ �ð�
	DWORD Shootdelay;		//���� �ӵ� (Shootdelay �������� ���) 
	DWORD lastShootTime;	//���� �������� ���� �� �ð�

	bool isPossessed;		//�÷��̾ �����ϰ� �ִ°�?

	float BulletSpeed;		//ź��
	float effectiveRange;	//��ȿ ��Ÿ�

	bool lastShoot;		//�� Ÿ�ӿ� ����� �Ͽ�����

	bool reLoading;		//������ ������

	D3DXVECTOR2 mousePos;	//���� ������ ������ ���콺�� ��ġ

	virtual D3DXVECTOR2 GetMuzzlePosition() = 0;

protected:

	float Rebound;		//�ݵ�
	int numOfSpray;		//���� ���� (�ݵ� ��� ����)
	float power;		//��ġ�� �Ÿ� (�Ѿ˿� ��)

	virtual void ReloadSound() = 0;


public:

	void Init(GameObject::TYPE type);
	void Update();
	void UpdatePosition(D3DXVECTOR2 position, D3DXVECTOR2 mousePos);

	void PickUpGun();		//���� �ֿ���
	void ThrowGun();		//���� ������

	virtual bool Shoot();

	void SetOption(int BulletPerMagazine, int MaxBullet, int nowBullet, int leftBullet, DWORD reloadTime, DWORD ShootDelay, float BulletSpeed, float effectiveRange, float power);

	int GetNowBullet();
	void SetNowBullet(int nowBullet);
	int GetLeftBullet();
	void SetLeftBullet(int leftBullet);
	bool GetIsPossessed();

	void Reload();					//������
	void ReloadCancle();			//������ ���

	DWORD GetReloadTime();			//������ �ϴµ� �ɸ��� �ð��� ����
	DWORD GetReloadRemainTime();	//������ �ϴµ� ���� �ð��� ���� ��) ������ �ð��� 5���̰� ���ݱ��� 2�� �����ٸ�, ������ �ϴµ� ���� �ð��� 3�ʰ� ��.

	float GetBulletSpeed();

	float GetEffectiveRange();

	void SetDegreeWithMousePosition();
	void SetDegreeWithDegree(float degree);
};