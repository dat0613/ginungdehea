#pragma once

#include "Singleton.h"

#include <MinNet.h>
#include <list>
#include <vector>

#pragma comment (lib,"minnet.lib")

#include "PlayerNetwork.h"

#define MAXNETWORKPLAYER 5

#define abs(a)  (((a)>0) ? (a):-(a))			//���밪 �Լ�
#define EPSILON 0.01f							//float�� �ڷ����� ���� ����
#define fsame(a, b) (((abs(a - b)) < EPSILON) ? (1) : (0))		//float�� �ΰ����� ������ Ȯ���ϴ� ��ũ�� �Լ�. EPSILON �� ���� ���� ��Ȯ���� �޶���

using namespace std;
using namespace MinNet;

class NetworkManager : public Singleton<NetworkManager>
{
private:

	MinNetUser * user;
	
	Player * my_player;
	vector<PlayerNetwork *> network_player_vector;
	list<Gun *> gun_list;

	inline Vector2 D3DVec2ToMinNetVec2(D3DXVECTOR2 &v);
	inline D3DXVECTOR2 MinNetVec2ToD3DVec2(Vector2 &v);
	D3DXVECTOR2 lastDir;

	float lastDegree;

	int GetEmptyPlayer();

	Gun * GetGunWithId(int id);
	
	void PacketHandler();

	void PacketTypePlayerAdd(MinNetPacket * packet);
	void PacketTypePlayerOld(MinNetPacket * packet);
	void PacketTypePlayerDel(MinNetPacket * packet);
	void PacketTypePlayerMove(MinNetPacket * packet);
	void PacketTypePlayerRoll(MinNetPacket * packet);
	void PacketTypePlayerShoot(MinNetPacket * packet);
	void PacketTypeCreateGun(MinNetPacket * packet);
	void PacketTypeDestroyGun(MinNetPacket * packet);
	void PacketTypePlayerPickUpGun(MinNetPacket * packet);
	void PacketTypePlayerDropGun(MinNetPacket * packet);
	void PacketTypePlayerMoveMouse(MinNetPacket * packet);
	void PacketTypePlayerSetAvatar(MinNetPacket * packet);
	void PacketTypePlayerFall(MinNetPacket * packet);
	void PacketTypePlayerSetPosition(MinNetPacket * packet);
	void PacketTypePlayerDie(MinNetPacket * packet);
	void PacketTypePlayerHit(MinNetPacket * packet);

	void CreateIpInputWindow();
	HWND IpInputWindow;
	LPCTSTR IpInputClass = TEXT("IpInput");


public:
	char IP[255];
	bool TryToConnect;
	bool IsWindowOn;

	enum NETEVENT {
		PLAYER_ADD, PLAYER_DEL, PLAYER_OLD, PLAYER_MOVE,
		PLAYER_ROLL, PLAYER_SHOOT, PLAYER_FALL, PLAYER_MOUSE_MOVE,
		PLAYER_SET_POSITION, PLAYER_DIE, PLAYER_HIT, PLAYER_PICK_UP_GUN,
		PLAYER_DROP_GUN, CREATE_GUN, DESTROY_GUN
	};
	//ADD : ���ο� �÷��̾ ����
	//DEL : �÷��̾ ����
	//OLD : ���� ���� ���� �ִ� �÷��̾���� ����

	int GetID();

	PlayerNetwork * GetPlayerWithId(int ID);
	void PlayerRoll();
	void Shoot(float speed, D3DXVECTOR2 startPos, D3DXVECTOR2 targetPos, float EffectiveRange, float power);
	void PickUpGun(Gun * gun);
	void DropGun(Gun * gun);
	void PlayerFall(D3DXVECTOR2 fallPosition);
	void PlayerSetPosition();
	void PlayerDie(int killerID);
	void PlayerHit(float power);

	Player::PLAYER_COLOR GetPlayerColorWithID(int ID);

	void Init();
	bool ConnectToServer(char * IP, short PORT);
	void Update();
	void Connect();

	void SetMyPlayer(Player * player);
	Player * GetMyPlayer();

	void SetMyPlayer(GameObject * player);

	friend LRESULT CALLBACK IpInputProc(HWND hWmd, UINT iMessage, WPARAM wParam, LPARAM lParam);
};