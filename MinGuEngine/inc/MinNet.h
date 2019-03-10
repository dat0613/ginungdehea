#pragma once

#include <cstdio>
#include <WinSock2.h>
#include <iostream>
#include <queue>
#include <thread>

#pragma comment (lib,"ws2_32.lib")

using namespace std;

namespace MinNet
{
	class Defines
	{
	public:
		static const short HEADERSIZE = 2 + 4;
		static const short MAXCONN = 64 - 1;
		enum MinNetPacketType { CLIENT_ACCEPT_ALLOW = -4, CLIENT_ACCEPT_DISALLOW, CLIENT_REQUEST_ID, CLIENT_ANSWER_ID };
	};

	class BitConverter
	{
	public:
		static byte* GetBytes(int data);
		static byte* GetBytes(bool data);
		static byte* GetBytes(short data);
		static byte* GetBytes(float data);

		static int ToInt(byte* byte_array, int start_position);
		static bool ToBool(byte* byte_array, int start_position);
		static short ToShort(byte* byte_array, int start_position);
		static float ToFloat(byte* byte_array, int start_position);

		static void ByteCopy(byte* dst, int dst_position, byte *src, int src_length);
	};

	class Vector3
	{
	public:

		float x;
		float y;
		float z;

		Vector3();
		Vector3(float x, float y, float z);
		friend ostream& operator<< (ostream& o, const Vector3& vector3);

	};

	class Vector2
	{
	public:

		float x;
		float y;

		Vector2();
		Vector2(float x, float y);
		friend ostream& operator<< (ostream& o, const Vector2& vector2);
	};

	class MinNetPacket
	{
		friend class MinNetUser;
	public:

		MinNetPacket();
		~MinNetPacket();

		byte *buffer;
		int buffer_position;
		int packet_type;

		void create_packet(int packet_type);
		void create_header();
		void set_buffer_position(unsigned int pos);

		void push(int data);
		void push(bool data);
		void push(short data);
		void push(float data);
		void push(Vector2 data);
		void push(Vector3 data);

		int pop_int();
		bool pop_bool();
		short pop_short();
		float pop_float();
		Vector2 pop_vector2();
		Vector3 pop_vector3();


	private:


	};

	class MinNetPacketEvent
	{
	public:
		MinNetPacketEvent();
		MinNetPacketEvent(MinNetUser * user, MinNetPacket * packet);
		~MinNetPacketEvent();

		MinNetUser * user;
		MinNetPacket * packet;
	};

	class MinNetUser
	{
	public:
		bool isConnected;
		SOCKET sock;
		queue<MinNetPacket *> sending_packet_Q;
		queue<MinNetPacket *> recving_packet_Q;

		int ID;

		thread *recvThread;
		thread *sendThread;

		int recvn(byte* buf, int len, int flags);
		int sendn(byte* buf, int len, int flags);

		MinNetUser();
		~MinNetUser();

		bool ConnectToServer(char* IP, short PORT);
		bool DisConnectToServer();
		void push_send_packet(MinNetPacket * packet);

		void Lock();
		void UnLock();


	protected:

	private:
		CRITICAL_SECTION recv_CS;
		CRITICAL_SECTION send_CS;

		void PacketTypeClientAnswerId(MinNetPacket * packet);

		bool MinNetPacketHandler(MinNetPacket * packet);
		void sendFunction();
		void recvFunction();
		void send_handling_thread();
		void recv_handling_thread();

	};


	class MinNetServer
	{
	public:

		SOCKET sock;

		bool StartServer(short PORT);
		bool StopServer();
		char* getHostIP();
		MinNetUser* AcceptUser();
		void ExpelUser(MinNetUser * user);
		int RecvPacketFromUser(MinNetUser* user, MinNetPacket* receive_packet);
		int RecvPacketFromUser(MinNetPacketEvent * packet_event);
		int SendPacketToUser(MinNetUser* user, MinNetPacket* send_packet);
		int SendPacketToUser(MinNetPacketEvent * packet_event);

	private:

	};


}