#include "NetworkManager.h"
#include "Gun.h"
#include "Bullet.h"
#include "GameManager.h"
#include "KillLog.h"
#include "GunBox.h"

void NetworkManager::PacketHandler()
{
	user->Lock();

	while (!user->recving_packet_Q.empty())
	{
		auto packet = user->recving_packet_Q.front();

		switch (packet->packet_type)
		{
		case NETEVENT::PLAYER_ADD:
			PacketTypePlayerAdd(packet);
			break;

		case NETEVENT::PLAYER_OLD:
			PacketTypePlayerOld(packet);
			break;

		case NETEVENT::PLAYER_DEL:
			PacketTypePlayerDel(packet);
			break;

		case NETEVENT::PLAYER_MOVE:
			PacketTypePlayerMove(packet);
			break;

		case NETEVENT::PLAYER_ROLL:
			PacketTypePlayerRoll(packet);
			break;

		case NETEVENT::PLAYER_SHOOT:
			PacketTypePlayerShoot(packet);
			break;

		case NETEVENT::CREATE_GUN:
			PacketTypeCreateGun(packet);
			break;

		case NETEVENT::PLAYER_PICK_UP_GUN:
			PacketTypePlayerPickUpGun(packet);
			break;

		case NETEVENT::PLAYER_DROP_GUN:
			PacketTypePlayerDropGun(packet);
			break;

		case NETEVENT::PLAYER_MOUSE_MOVE:
			PacketTypePlayerMoveMouse(packet);
			break;

		case NETEVENT::PLAYER_FALL:
			PacketTypePlayerFall(packet);
			break;

		case NETEVENT::PLAYER_SET_POSITION:
			PacketTypePlayerSetPosition(packet);
			break;

		case NETEVENT::PLAYER_DIE:
			PacketTypePlayerDie(packet);
			break;

		case NETEVENT::PLAYER_HIT:
			PacketTypePlayerHit(packet);
			break;
		
		case NETEVENT::DESTROY_GUN:
			PacketTypeDestroyGun(packet);
			break;
		
		}

		user->recving_packet_Q.pop();
		delete packet;
	}

	user->UnLock();
}

void NetworkManager::Update()
{
	if (my_player == nullptr)
		return; 

	if (!user->isConnected)
	{
		if (TryToConnect)
		{
			if (ConnectToServer(IP, 8200))
			{
				int asdf = WSAGetLastError();
				if (asdf == WSAEWOULDBLOCK)
				{
					char * error = nullptr;
					int len = sizeof(error);

					if (getsockopt(user->sock, SOL_SOCKET, SO_ERROR, error, &len) < 0)
						exit(1);
				}

				Sleep(1000);

				MinNetPacket * packet = new MinNetPacket();
				packet->create_packet(NETEVENT::PLAYER_ADD);
				packet->push(user->ID);
				packet->push(D3DVec2ToMinNetVec2(my_player->getPosition()));
				packet->create_header();
				user->push_send_packet(packet);
			}
		}
		else
			Connect();

		return;
	}

	PacketHandler();



	if (my_player == nullptr)
		return;

	auto dir = my_player->GetMoveDir();

	if (!(fsame(lastDir.x, dir.x) && fsame(lastDir.y, dir.y)))
	{
		MinNetPacket * packet = new MinNetPacket();
		packet->create_packet(NETEVENT::PLAYER_MOVE);
		packet->push(user->ID);
		packet->push(D3DVec2ToMinNetVec2(my_player->getPosition()));
		packet->push(D3DVec2ToMinNetVec2(dir));
		packet->create_header();

		user->push_send_packet(packet);

		lastDir = dir;
	}

	if (my_player->gun != nullptr)
	{
		if (abs(my_player->gun->getDegree() - lastDegree) > 0)
		{
			lastDegree = my_player->gun->getDegree();
			MinNetPacket * packet = new MinNetPacket();

			packet->create_packet(NETEVENT::PLAYER_MOUSE_MOVE);
			packet->push(user->ID);
			packet->push(lastDegree);
			packet->create_header();

			user->push_send_packet(packet);

		}
	}
}

void NetworkManager::Connect()
{
	//strcpy_s(IP, "127.0.0.1");
	//TryToConnect = true;
	
	//if (ConnectToServer(IP, 8200))
	//{
	//	Sleep(1000);
	//	MinNetPacket * packet = new MinNetPacket();
	//	packet->create_packet(NETEVENT::PLAYER_ADD);
	//	packet->push(user->ID);
	//	packet->push(D3DVec2ToMinNetVec2(my_player->getPosition()));
	//	packet->create_header();
	//	user->push_send_packet(packet);
	//}

	//return;

	if (IsWindowOn == false)
	{
		IsWindowOn = true;
		CreateIpInputWindow();
		ShowWindow(IpInputWindow, SW_SHOW);
		Sleep(10);
	}

	//user->ConnectToServer("127.0.0.1", 8200);
	//Sleep(100);
	//lastDir = D3DXVECTOR2(0.0f, 0.0f);

	//MinNetPacket * packet = new MinNetPacket();
	//packet->create_packet(NETEVENT::PLAYER_ADD);
	//packet->push(user->ID);
	//packet->push(D3DVec2ToMinNetVec2(my_player->getPosition()));
	//packet->create_header();
	//user->push_send_packet(packet);
}

void NetworkManager::SetMyPlayer(Player * player)
{
	my_player = player;
}

Player * NetworkManager::GetMyPlayer()
{
	return my_player;
}

void NetworkManager::SetMyPlayer(GameObject * player)
{
	my_player = (Player *)player;
	if (my_player == nullptr)
		exit(1);
}

Vector2 NetworkManager::D3DVec2ToMinNetVec2(D3DXVECTOR2 & v)
{
	return Vector2(v.x, v.y);
}

D3DXVECTOR2 NetworkManager::MinNetVec2ToD3DVec2(Vector2 & v)
{
	return D3DXVECTOR2(v.x, v.y);
}

int NetworkManager::GetEmptyPlayer()
{
	int i = 0;
	for (auto player : network_player_vector)
	{
		if (player == nullptr)
		{
			return i;
		}
		i++;
	}

	return -1;
}

PlayerNetwork * NetworkManager::GetPlayerWithId(int ID)
{
	if (user->ID == ID)
		return (PlayerNetwork *)my_player;

	for (auto player : network_player_vector)
	{
		if (player != nullptr && player->user->ID == ID)
			return player;
	}

	return nullptr;
}

Gun * NetworkManager::GetGunWithId(int id)
{
	for (auto gun : gun_list)
	{
		if (gun->ID == id)
			return gun;
	}

	return nullptr;
}

void NetworkManager::PacketTypePlayerAdd(MinNetPacket * packet)
{
	auto empty = GetEmptyPlayer();
	if (empty == -1)
		exit(1);

	auto ID = packet->pop_int();

	auto pos = MinNetVec2ToD3DVec2(packet->pop_vector2());
	auto color = packet->pop_int();

	if (ID == user->ID)
	{
		my_player->SetPlayerColor((Player::PLAYER_COLOR)color);
	}
	else
	{
		auto player = (PlayerNetwork *)(Instantiate(GameObject::PlayerNetwork));
		network_player_vector[empty] = player;
		player->user = new MinNetUser();

		player->user->ID = ID;
		player->setPosition(pos);
		player->SetPlayerColor((Player::PLAYER_COLOR)color);
	}
}

void NetworkManager::PacketTypePlayerOld(MinNetPacket * packet)
{
	PacketTypePlayerAdd(packet);
}

void NetworkManager::PacketTypePlayerDel(MinNetPacket * packet)
{
	auto ID = packet->pop_int();

	auto player = GetPlayerWithId(ID);

	if (player == nullptr)
	{
		return;
	}

	if (player->gun != nullptr)
	{
		for (auto i = gun_list.begin(); i != gun_list.end(); ++i)
		{
			auto * nowGun = *i;
			if (nowGun->ID == player->gun->ID)
			{
				nowGun->enabled = false;
				gun_list.erase(i);
				break;
			}
		}
	}


	for (int i = 0; i < MAXNETWORKPLAYER; i++)
	{
		if (network_player_vector[i] != nullptr && network_player_vector[i]->user->ID == ID)
		{
			network_player_vector[i]->enabled = false;
			network_player_vector[i] = nullptr;
		}
	}
}

void NetworkManager::PacketTypePlayerMove(MinNetPacket * packet)
{
	auto ID = packet->pop_int();

	auto player = GetPlayerWithId(ID);
	if (player == nullptr)
	{
		return;
	}

	auto pos = MinNetVec2ToD3DVec2(packet->pop_vector2());
	player->setPosition(pos);

	auto dir = MinNetVec2ToD3DVec2(packet->pop_vector2());
	player->SetMoveDir(dir);
}

void NetworkManager::PacketTypePlayerRoll(MinNetPacket * packet)
{
	auto ID = packet->pop_int();

	auto player = GetPlayerWithId(ID);
	if (player == nullptr)
	{
		//printf("PacketTypePlayerRoll 오류. ID : %d\n", ID);
		return;
	}

	auto pos = MinNetVec2ToD3DVec2(packet->pop_vector2());
	player->isRolling = true;
	player->RollingStartTime = clock();
	if (player->gun != nullptr)
		player->gun->visible = false;
}

void NetworkManager::PacketTypePlayerShoot(MinNetPacket * packet)
{
	auto ID = packet->pop_int();
	auto speed = packet->pop_float();

	auto startPos = MinNetVec2ToD3DVec2(packet->pop_vector2());
	auto targetPos = MinNetVec2ToD3DVec2(packet->pop_vector2());

	auto power = packet->pop_float();
	auto range = packet->pop_float();

	auto obj = Instantiate(GameObject::TYPE::Bullet);
	auto bullet = (Bullet *)obj;
	bullet->setPosition(startPos);
	bullet->SetOption(ID, speed, targetPos, range, power);
}

void NetworkManager::PacketTypeCreateGun(MinNetPacket * packet)
{
	auto gun_id = packet->pop_int();
	auto gun_type = packet->pop_int();
	auto gun_bullet_per_magazine = packet->pop_int();
	auto gun_max_magazine = packet->pop_int();
	auto gun_now_bullet = packet->pop_int();
	auto gun_now_magazine = packet->pop_int();
	auto gun_reload_time = packet->pop_int();
	auto gun_shoot_delat = packet->pop_int();
	auto gun_bullet_speed = packet->pop_float();
	auto gun_effective_range = packet->pop_float();
	auto gun_power = packet->pop_float();
	auto gun_position = MinNetVec2ToD3DVec2(packet->pop_vector2());
	auto gun_degree = packet->pop_float();
	auto gun_is_new = packet->pop_bool();

	auto obj = Instantiate((GameObject::TYPE)gun_type);
	auto gun = (Gun *)obj;
	gun->ID = gun_id;
	gun->SetOption(gun_bullet_per_magazine, gun_max_magazine, gun_now_bullet, gun_now_magazine, gun_reload_time, gun_shoot_delat, gun_bullet_speed, gun_effective_range, gun_power);
	gun->setPosition(gun_position);
	gun->setDegree(gun_degree);

	gun_list.push_back(gun);

	//if (gun_is_new)
	//{
		gun->visible = false;
		gun->SetIsCollider(false);

		obj = Instantiate(GameObject::GunBox);
		auto gunbox = (GunBox *)obj;
		gunbox->SetGun(gun);
	//}

}

void NetworkManager::PacketTypeDestroyGun(MinNetPacket * packet)
{
	
}

void NetworkManager::PacketTypePlayerPickUpGun(MinNetPacket * packet)
{
	auto player_id = packet->pop_int();
	auto gun_id = packet->pop_int();

	auto player = GetPlayerWithId(player_id);
	if (player == nullptr)
	{
		return;
	}
	auto gun = GetGunWithId(gun_id);
	if (gun == nullptr)
	{
		return;
	}

	gun->visible = true;

	player->SetGun(gun);
}

void NetworkManager::PacketTypePlayerDropGun(MinNetPacket * packet)
{
	auto player_id = packet->pop_int();
	auto gun_id = packet->pop_int();
	auto gun_now_bullet = packet->pop_int();
	auto gun_left_bullet = packet->pop_int();
	auto gun_position = MinNetVec2ToD3DVec2(packet->pop_vector2());
	auto gun_degree = packet->pop_float();

	auto player = GetPlayerWithId(player_id);

	if (player == nullptr)
	{
		return;
	}

	auto gun = GetGunWithId(gun_id);

	if (gun == nullptr)
	{
		return;
	}

	player->DropGun();
	gun->SetNowBullet(gun_now_bullet);
	gun->SetLeftBullet(gun_left_bullet);
	gun->setPosition(gun_position);
	gun->setDegree(gun_degree);

	for (auto i = gun_list.begin(); i != gun_list.end(); ++i)
	{
		auto * nowGun = *i;
		if (nowGun->ID == gun_id)
		{
			nowGun->enabled = false;
			gun_list.erase(i);
			break;
		}
	}
}

void NetworkManager::PacketTypePlayerMoveMouse(MinNetPacket * packet)
{
	auto ID = packet->pop_int();
	auto player = GetPlayerWithId(ID);

	if (player == nullptr)
	{
		return;
	}

	if (player->gun != nullptr)
	{
		player->gun->SetDegreeWithDegree(packet->pop_float());
	}
}

void NetworkManager::PacketTypePlayerSetAvatar(MinNetPacket * packet)
{
	auto color = packet->pop_int();
	my_player->SetPlayerColor((Player::PLAYER_COLOR)color);
}

void NetworkManager::PacketTypePlayerFall(MinNetPacket * packet)
{
	auto ID = packet->pop_int();
	auto pos = MinNetVec2ToD3DVec2(packet->pop_vector2());

	auto player = GetPlayerWithId(ID);
	if (player == nullptr)
	{
		return;
	}

	player->setPosition(pos);
}

void NetworkManager::PacketTypePlayerSetPosition(MinNetPacket * packet)
{
	auto ID = packet->pop_int();
	auto pos = MinNetVec2ToD3DVec2(packet->pop_vector2());

	auto player = GetPlayerWithId(ID);
	if (player == nullptr)
	{
		return;
	}

	player->setPosition(pos);
}

void NetworkManager::PacketTypePlayerDie(MinNetPacket * packet)
{
	auto die_player_ID = packet->pop_int();
	auto kill_player_ID = packet->pop_int();

	auto obj = Instantiate(GameObject::KillLog);
	auto kill_log = (::KillLog *)obj;
	kill_log->SetOption(kill_player_ID, die_player_ID);

	if (kill_player_ID == user->ID && die_player_ID != user->ID)
	{
		SoundManager::GetInstance()->pushSoundQ(SoundEvent::KillSound);
	}

	if (die_player_ID != user->ID && kill_player_ID != user->ID)
	{
		SoundManager::GetInstance()->pushSoundQ(SoundEvent::DieSound);
	}
}

void NetworkManager::PacketTypePlayerHit(MinNetPacket * packet)
{

	auto ID = packet->pop_int();
	auto power = packet->pop_float();
	auto position = MinNetVec2ToD3DVec2(packet->pop_vector2());
	auto dir = MinNetVec2ToD3DVec2(packet->pop_vector2());

	auto player = GetPlayerWithId(ID);

	if (player == nullptr)
	{
		return;
	}

	player->setPosition(position);
	player->SetPushedDir(dir);
	player->AddPushedVelocity(power);
}

void NetworkManager::CreateIpInputWindow()
{
	HINSTANCE instance = GetModuleHandle(NULL);

	WNDCLASS WndClass;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)COLOR_WINDOW;		// 화면을 흰색으로 칠함
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);					// 마우스 모양을 표시함
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);					// 왼쪽 위 상단에 나타나는 아이콘
	WndClass.hInstance = instance;									// 현재 윈도우 인스턴스
	WndClass.lpfnWndProc = IpInputProc;									// 콜백함수 등록 
	WndClass.lpszClassName = IpInputClass;								// 창의 이름(lpszClass는 현재 First로 입력되어 있음)
	WndClass.lpszMenuName = NULL;										// 메뉴 이름 
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	IpInputWindow = CreateWindow(IpInputClass, IpInputClass,
		WS_OVERLAPPEDWINDOW ^ WS_MAXIMIZEBOX ^ WS_MINIMIZEBOX,
		GetSystemMetrics(SM_CXSCREEN) / 2 - 500, GetSystemMetrics(SM_CYSCREEN) / 2 - 150, 270, 120,
		NULL,
		(HMENU)NULL,
		instance,
		NULL);
}

int NetworkManager::GetID()
{
	return user->ID;
}

void NetworkManager::PlayerRoll()
{
	if (my_player == nullptr)
		return;

	MinNetPacket * packet = new MinNetPacket();
	packet->create_packet(NETEVENT::PLAYER_ROLL);

	packet->push(user->ID);
	packet->push(D3DVec2ToMinNetVec2(my_player->getPosition()));

	packet->create_header();
	user->push_send_packet(packet);
}

void NetworkManager::Shoot(float speed, D3DXVECTOR2 startPos, D3DXVECTOR2 targetPos, float EffectiveRange, float power)
{
	if (my_player == nullptr)
		return;

	MinNetPacket * packet = new MinNetPacket();
	packet->create_packet(NETEVENT::PLAYER_SHOOT);

	packet->push(user->ID);
	packet->push(speed);
	packet->push(D3DVec2ToMinNetVec2(startPos));
	packet->push(D3DVec2ToMinNetVec2(targetPos));
	packet->push(power);
	packet->push(EffectiveRange);

	packet->create_header();
	user->push_send_packet(packet);
}

void NetworkManager::PickUpGun(Gun * gun)
{
	if (my_player == nullptr)
		return;

	MinNetPacket * packet = new MinNetPacket();

	packet->create_packet(NETEVENT::PLAYER_PICK_UP_GUN);

	packet->push(user->ID);
	packet->push(gun->ID);

	packet->create_header();

	user->push_send_packet(packet);
}

void NetworkManager::DropGun(Gun * gun)
{
	if (my_player == nullptr)
		return;

	MinNetPacket * packet = new MinNetPacket();

	packet->create_packet(NETEVENT::PLAYER_DROP_GUN);


	packet->push(user->ID);
	packet->push(gun->ID);
	packet->push(gun->GetNowBullet());
	packet->push(gun->GetLeftBullet());
	packet->push(D3DVec2ToMinNetVec2(gun->getPosition()));
	packet->push(gun->getDegree());


	packet->create_header();

	user->push_send_packet(packet);

	for (auto i = gun_list.begin(); i != gun_list.end(); ++i)
	{
		auto * nowGun = *i;
		if (nowGun->ID == gun->ID)
		{
			nowGun->enabled = false;
			gun_list.erase(i);
			break;
		}
	}
}

void NetworkManager::PlayerFall(D3DXVECTOR2 fallPosition)
{
	if (my_player == nullptr)
		return;

	MinNetPacket * packet = new MinNetPacket();

	packet->create_packet(NETEVENT::PLAYER_FALL);
	
	packet->push(user->ID);
	packet->push(D3DVec2ToMinNetVec2(fallPosition));
	packet->create_header();

	user->push_send_packet(packet);
}

void NetworkManager::PlayerSetPosition()
{
	if (my_player == nullptr)
		return;

	MinNetPacket * packet = new MinNetPacket();

	packet->create_packet(NETEVENT::PLAYER_SET_POSITION);

	packet->push(user->ID);
	packet->push(D3DVec2ToMinNetVec2(my_player->getPosition()));
	packet->create_header();

	user->push_send_packet(packet);
}

void NetworkManager::PlayerDie(int killerID)
{
	if (my_player == nullptr)
		return;

	if (killerID == -1)
		killerID = user->ID;

	auto obj = Instantiate(GameObject::KillLog);
	auto kill_log = (::KillLog *)obj;

	kill_log->SetOption(killerID, user->ID);

	MinNetPacket * packet = new MinNetPacket();

	packet->create_packet(NETEVENT::PLAYER_DIE);

	packet->push(user->ID);
	packet->push(killerID);

	packet->create_header();

	user->push_send_packet(packet);
}

void NetworkManager::PlayerHit(float power)
{
	if (my_player == nullptr)
		return;

	MinNetPacket * packet = new MinNetPacket();
	
	packet->create_packet(NETEVENT::PLAYER_HIT);

	packet->push(user->ID);
	packet->push(power);
	packet->push(D3DVec2ToMinNetVec2(my_player->position));
	packet->push(D3DVec2ToMinNetVec2(my_player->pushedDir));

	packet->create_header();

	user->push_send_packet(packet);
}

Player::PLAYER_COLOR NetworkManager::GetPlayerColorWithID(int ID)
{
	if (ID == user->ID || ID == -1)
		return my_player->GetPlayerColor();

	for (auto player : network_player_vector)
	{
		if (player != nullptr)
		{
			if (player->user->ID == ID)
				return player->GetPlayerColor();
		}
	}
}

void NetworkManager::Init()
{
	network_player_vector.resize(MAXNETWORKPLAYER, nullptr);

	user = new MinNetUser();
	lastDegree = 0.0f;
	lastDir = D3DXVECTOR2(0.0f, 0.0f);
	TryToConnect = IsWindowOn = false;

	//Connect();
}

bool NetworkManager::ConnectToServer(char * IP, short PORT)
{
	return user->ConnectToServer(IP, PORT);
}

LRESULT CALLBACK IpInputProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	static HWND IpStatic, IpEdit, DoneBtn, CancleBtn;
	switch (iMessage)
	{
	case WM_CREATE:
		IpStatic = CreateWindow("Static",
			TEXT("서버의 IP 입력 :"),
			WS_CHILD | WS_VISIBLE,
			10, 10, 120, 25,
			hWnd,
			(HMENU)NULL,
			((LPCREATESTRUCT)lParam)->hInstance,
			NULL
		);

		IpEdit = CreateWindow("Edit",
			TEXT(""),
			WS_CHILD | WS_VISIBLE | WS_BORDER | WS_EX_STATICEDGE,
			120, 10, 130, 25,
			hWnd,
			(HMENU)1,
			((LPCREATESTRUCT)lParam)->hInstance,
			NULL
		);

		DoneBtn = CreateWindow("Button",
			TEXT("확인"),
			WS_CHILD | WS_VISIBLE | WS_BORDER | WS_EX_STATICEDGE,
			150, 45, 100, 25,
			hWnd,
			(HMENU)2,
			((LPCREATESTRUCT)lParam)->hInstance,
			NULL
		);
		break;

	case WM_COMMAND:

		if (LOWORD(wParam) == 2 && HIWORD(wParam) == BN_CLICKED && (HWND)lParam == DoneBtn)
		{//확인 버튼 클릭
			GetDlgItemText(hWnd, 1, NetworkManager::GetInstance()->IP, sizeof(NetworkManager::GetInstance()->IP));

			char * str = NetworkManager::GetInstance()->IP;
			for (int i = 0; i < sizeof(NetworkManager::GetInstance()->IP) - 1; i++)
			{
				for (int j = i; j < sizeof(NetworkManager::GetInstance()->IP) - 1; j++)
				{
					if (str[i] != '\0')
						break;

					if (str[i] == '\0' && str[j] != '\0')
					{
						str[i] = str[j];
						str[j] = '\0';
						break;
					}
				}
			}
			NetworkManager::GetInstance()->TryToConnect = true;
			NetworkManager::GetInstance()->IsWindowOn = false;
			DestroyWindow(hWnd);
		}

		break;

	case WM_GETMINMAXINFO:

		((MINMAXINFO*)lParam)->ptMaxTrackSize.x = 270;
		((MINMAXINFO*)lParam)->ptMaxTrackSize.y = 120;
		((MINMAXINFO*)lParam)->ptMinTrackSize.x = 270;
		((MINMAXINFO*)lParam)->ptMinTrackSize.y = 120;
		return FALSE;
		break;

	case WM_DESTROY:
		NetworkManager::GetInstance()->IsWindowOn = false;
		break;

	case WM_CLOSE:
		NetworkManager::GetInstance()->IsWindowOn = false;
		DestroyWindow(hWnd);
		return 0;

	default:
		break;

	}


	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
