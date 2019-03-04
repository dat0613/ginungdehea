#pragma once

#include <Windows.h>

#include <fmod.h>
#include <queue>
#include <process.h>

#include "Singleton.h"
#include "SoundEvent.h"

#pragma comment (lib,"fmodex_vc.lib")

#define LOOP 0
#define NONLOOP 1

class SoundManager : public Singleton<SoundManager>
{
private:

	float volume;			//��ü ����
	bool isMuted;			//���Ұ� �Ǿ�����
	bool loadEnd;

	void loadSound(FMOD_SOUND **sound ,char * file, int type);

	FMOD_SYSTEM *soundSystem;
	FMOD_CHANNEL *BGMChannel;				//��������� �ѹ��� �ϳ��� ��� �Ǳ� ������ �ϳ��� ä�θ� ������ ����

	std::queue<SoundEvent *> SoundEventQ;	//�پ��� ȿ������ ���ÿ� �������� ����ϱ� ���� ���� �̺�Ʈť

	FMOD_CHANNEL ***getChannelWithType(SoundEvent::TYPE type);	
	FMOD_SOUND *getSoundWithType(SoundEvent::TYPE type);

	bool isBGMChannelPlaying();
	void playSound(SoundEvent::TYPE type);


	
	//�Ҹ��� �߰� �ϱ����� ����
	//���� : FMOD_SOUND *������; ���� �Ҹ� ������ �߰� ��Ų �� Init �Լ����� *������ �� �Ҹ� ������ �ʱ�ȭ ������
	//enum TYPE �� ���� ������ �߰� ���� ���ο� Ÿ���� ����

	std::vector <FMOD_SOUND *> sound_vector;
	std::vector <FMOD_CHANNEL *>channel_vector;

public:
	~SoundManager();
	void Init();
	void Update();
	void pushSoundQ(SoundEvent::TYPE type);
	void playBGM(SoundEvent::TYPE type);
	void stopBGM();
	void Release();
	
	static unsigned int __stdcall loadSoundThread(void * arg);

	//void testPlay();
};