#pragma once

#include "GameObject.h"
#include "InputManager.h"
#include "Gun.h"
#include "Hole.h"

#define abs(a)  (((a)>0) ? (a):-(a))			//���밪 �Լ�
#define EPSILON 0.0001f							//float�� �ڷ����� ���� ����
#define fsame(a, b) (((abs(a - b)) < EPSILON) ? (1) : (0))		//float�� �ΰ����� ������ Ȯ���ϴ� ��ũ�� �Լ�. EPSILON �� ���� ���� ��Ȯ���� �޶���


class Player : public GameObject
{
	friend class NetworkManager;

public:
	enum PLAYER_COLOR { BLUE, GRAY, NEON, PINK, PURPLE, RED, REVERSE, YELLOW };

private:
	bool WallCollision(GameObject * wall);
	bool isMoveAfterLastSetPosition;
	bool isPushedAfterLastSetPosition;
	int lastAtackedPlayerID;	//���� ���������� ������ �÷��̾��� ID,  -1�Ͻ� ���ݹ��� �ʾҴ� ����.
	clock_t lastAttackedTime;	//���������� ���ݹ��� �ð�
	clock_t lastAttackedPlayerIDResetTime;		//lastAttackedPlayerID �� �ʱ�ȭ �ϴ� �ð�

	clock_t RollingDelay;

	clock_t lastAutoSetPosition;
	clock_t autoSetPositionDelay;
	

protected:
	void GetPistol();

	D3DXVECTOR2 moveDir;		//�����̴� ����
	D3DXVECTOR2 slideDir;		//�̲������� ����
	D3DXVECTOR2 pushedDir;		//���� �°� �з����� ����
	bool isKeyDown;				//Ű�� �Է� �Ͽ�����, Network �Ͻ� �����̴� ������

	int maxVelocity;
	int maxRollingVelocity;

	float pushedVelocity;		//�з����� �ӵ�

	bool isRolling;
	DWORD RollingStartTime;
	DWORD RollingTime;

	void AnimationProcess();
	void RollingProcess(bool isLocal = false);

	Gun * gun;
	bool isFalling;		//�÷��̾ ������ �ִ���
	D3DXVECTOR2 fallingPosition;	//�÷��̾ ���� ��ġ
	PLAYER_COLOR player_color;

	bool die;
	clock_t dieTime;		//�÷��̰� ����� �ð�
	clock_t respawnDelay;	//������ �ϱ���� �ɸ��� �ð�

	int Life;				//�÷��̾��� ���� ����� ����
	int KillCount;			//�ٸ� �÷��̾ óġ�� ��



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