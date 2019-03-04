#pragma once

#include "GameObject.h"
#include "InputManager.h"
#include "Gun.h"
#include "Hole.h"

#define abs(a)  (((a)>0) ? (a):-(a))			//절대값 함수
#define EPSILON 0.0001f							//float형 자료형의 오차 범위
#define fsame(a, b) (((abs(a - b)) < EPSILON) ? (1) : (0))		//float형 두가지가 같은지 확인하는 매크로 함수. EPSILON 의 값에 따라 정확도가 달라짐


class Player : public GameObject
{
	friend class NetworkManager;

public:
	enum PLAYER_COLOR { BLUE, GRAY, NEON, PINK, PURPLE, RED, REVERSE, YELLOW };

private:
	bool WallCollision(GameObject * wall);
	bool isMoveAfterLastSetPosition;
	bool isPushedAfterLastSetPosition;
	int lastAtackedPlayerID;	//나를 마지막으로 공격한 플레이어의 ID,  -1일시 공격받지 않았던 것임.
	clock_t lastAttackedTime;	//마지막으로 공격받은 시간
	clock_t lastAttackedPlayerIDResetTime;		//lastAttackedPlayerID 를 초기화 하는 시간

	clock_t RollingDelay;

	clock_t lastAutoSetPosition;
	clock_t autoSetPositionDelay;
	

protected:
	void GetPistol();

	D3DXVECTOR2 moveDir;		//움직이는 방향
	D3DXVECTOR2 slideDir;		//미끄러지는 방향
	D3DXVECTOR2 pushedDir;		//총을 맞고 밀려나는 방향
	bool isKeyDown;				//키를 입력 하였는지, Network 일시 움직이는 중인지

	int maxVelocity;
	int maxRollingVelocity;

	float pushedVelocity;		//밀려나는 속도

	bool isRolling;
	DWORD RollingStartTime;
	DWORD RollingTime;

	void AnimationProcess();
	void RollingProcess(bool isLocal = false);

	Gun * gun;
	bool isFalling;		//플레이어가 빠지고 있는지
	D3DXVECTOR2 fallingPosition;	//플레이어가 빠진 위치
	PLAYER_COLOR player_color;

	bool die;
	clock_t dieTime;		//플레이가 사망한 시간
	clock_t respawnDelay;	//리스폰 하기까지 걸리는 시간

	int Life;				//플레이어의 남은 목숨의 개수
	int KillCount;			//다른 플레이어를 처치한 수



public:
	void Init(GameObject::TYPE type);
	void Render();
	void Update();
	void LateUpdate();

	D3DXVECTOR2 GetMoveDir();

	void SetPushedDir(D3DXVECTOR2 pushedDir);

	void AddPushedVelocity(float pushedVelocity);

	void SetMoveDir(D3DXVECTOR2 dir);
	void SetMoveDir(float x, float y);

	void SetGun(Gun * gun);
	Gun * GetGun();

	void SetLife(int Life);
	int GetLife();

	void SetKillCount(int KillCount);
	int GetKillCount();

	void DropGun();

	void OnTriggerEnter(GameObject * obj);
	RECT GetCollisionRect();

	PLAYER_COLOR GetPlayerColor();
	void SetPlayerColor(PLAYER_COLOR color);
};