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

	float volume;			//전체 볼륨
	bool isMuted;			//음소거 되었는지
	bool loadEnd;

	void loadSound(FMOD_SOUND **sound ,char * file, int type);

	FMOD_SYSTEM *soundSystem;
	FMOD_CHANNEL *BGMChannel;				//배경음악은 한번에 하나만 재생 되기 때문에 하나의 채널만 가지고 있음

	std::queue<SoundEvent *> SoundEventQ;	//다양한 효과음을 동시에 여러가지 출력하기 위한 사운드 이벤트큐

	FMOD_CHANNEL ***getChannelWithType(SoundEvent::TYPE type);	
	FMOD_SOUND *getSoundWithType(SoundEvent::TYPE type);

	bool isBGMChannelPlaying();
	void playSound(SoundEvent::TYPE type);


	
	//소리를 추가 하기위한 변수
	//사용법 : FMOD_SOUND *변수명; 으로 소리 파일을 추가 시킨 후 Init 함수에서 *변수명 에 소리 파일을 초기화 시켜줌
	//enum TYPE 에 같은 변수명 추가 시켜 새로운 타입을 만듦

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