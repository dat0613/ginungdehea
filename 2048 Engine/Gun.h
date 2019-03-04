#pragma once

#include "GameObject.h"

class Gun : public GameObject
{
private:

	int BulletPerMagazine;		//한 탄창 당 들어갈 총알
	int MaxBullet;			//소지할 수 있는 최대 총알의 갯수

	int nowBullet;		//지금 쓰고 있는 탄창에 남은 총알의 갯수
	int leftBullet;		//지금 쓰고 있는 총알을 제외하고 남은 총알의 갯수

	DWORD reloadTime;	//재장전 하는데 걸리는 시간
	DWORD reloadStartTime;	//재장전을 시작한 시간
	DWORD Shootdelay;		//연사 속도 (Shootdelay 간격으로 사격) 
	DWORD lastShootTime;	//제일 마지막에 총을 쏜 시간

	bool isPossessed;		//플레이어가 소지하고 있는가?

	float BulletSpeed;		//탄속
	float effectiveRange;	//유효 사거리

	bool lastShoot;		//전 타임에 사격을 하였는지

	bool reLoading;		//재장전 중인지

	D3DXVECTOR2 mousePos;	//총의 각도에 관여할 마우스의 위치

	virtual D3DXVECTOR2 GetMuzzlePosition() = 0;

protected:

	float Rebound;		//반동
	int numOfSpray;		//연사 갯수 (반동 제어에 사용됨)
	float power;		//밀치는 거리 (총알에 들어감)

	virtual void ReloadSound() = 0;


public:

	void Init(GameObject::TYPE type);
	void Update();
	void UpdatePosition(D3DXVECTOR2 position, D3DXVECTOR2 mousePos);

	void PickUpGun();		//총이 주워짐
	void ThrowGun();		//총이 버려짐

	virtual bool Shoot();

	void SetOption(int BulletPerMagazine, int MaxBullet, int nowBullet, int leftBullet, DWORD reloadTime, DWORD ShootDelay, float BulletSpeed, float effectiveRange, float power);

	int GetNowBullet();
	void SetNowBullet(int nowBullet);
	int GetLeftBullet();
	void SetLeftBullet(int leftBullet);
	bool GetIsPossessed();

	void Reload();					//재장전
	void ReloadCancle();			//재장전 취소

	DWORD GetReloadTime();			//재장전 하는데 걸리는 시간을 받음
	DWORD GetReloadRemainTime();	//재장전 하는데 남은 시간을 받음 예) 재장전 시간이 5초이고 지금까지 2초 지났다면, 재장전 하는데 남은 시간은 3초가 됨.

	float GetBulletSpeed();

	float GetEffectiveRange();

	void SetDegreeWithMousePosition();
	void SetDegreeWithDegree(float degree);
};