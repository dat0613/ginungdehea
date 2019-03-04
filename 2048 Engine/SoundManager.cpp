#include "SoundManager.h"

void SoundManager::loadSound(FMOD_SOUND ** sound, char * file, int type)
{
	switch (type)
	{
	case LOOP:
		FMOD_System_CreateSound(soundSystem, file, FMOD_LOOP_NORMAL, 0, sound);
		break;

	case NONLOOP:
		FMOD_System_CreateSound(soundSystem, file, FMOD_DEFAULT, 0, sound);
		break;
	}
}

FMOD_CHANNEL *** SoundManager::getChannelWithType(SoundEvent::TYPE type)
{
	FMOD_CHANNEL **channel = NULL;
	SoundEvent *soundEvent = NULL;

	//switch (type)
	//{
	//case SoundEvent::TYPE::Test:
	//case SoundEvent::TYPE::Test2:

	//	//추가되는 효과음은 위의 형식에 따라 여기 추가
	//	//break; 는 넣지 않음
		soundEvent = SoundEventQ.front();
		channel = &(channel_vector[type]);
	//	break;

	//case SoundEvent::TYPE::TestBackGround:
	////case SoundManager::TYPE::asdf:

	//	//추가되는 BGM은 위의 형식에 따라 여기 추가
	//	//break; 는 넣지 않음

	//	soundEvent = NULL;
	//	channel = &BGMChannel;


	//	break;
	//}
	return &channel;
}

FMOD_SOUND * SoundManager::getSoundWithType(SoundEvent::TYPE type)
{
	FMOD_SOUND *temp = NULL;

	temp = sound_vector[type];

	return temp;
}

bool SoundManager::isBGMChannelPlaying()
{
	FMOD_BOOL isPlaying;
	FMOD_Channel_IsPlaying(BGMChannel, &isPlaying);

	return isPlaying;
}

SoundManager::~SoundManager()
{
	Release();
}

void SoundManager::Init()
{
	FMOD_System_Create(&soundSystem);
	FMOD_System_Init(soundSystem, 32, FMOD_INIT_NORMAL, NULL);

	//loadSound(&Test, "./Resource/Test.wav", NONLOOP);
	////FMOD_System_CreateSound(soundSystem, "./Resource/Test.wav", FMOD_LOOP_NORMAL, 0, &Test);
	//loadSound(&Test2, "./Resource/Test2.wav", NONLOOP);
	//loadSound(&TestBackGround, "./Resource/TestBackGround.mp3", LOOP);

	BGMChannel = NULL;

	isMuted = false;
	loadEnd = false;
	volume = 0.5f;

	sound_vector.resize(SoundEvent::MAXSOUND);
	channel_vector.resize(SoundEvent::MAXSOUND);

	HANDLE loadThread;
	loadThread = (HANDLE)_beginthreadex(NULL, 0, loadSoundThread, NULL, 0, NULL);
	
}

void SoundManager::Update()
{
	if (!loadEnd)
		return;

	while (!SoundEventQ.empty())
	{
		SoundEvent* soundEvent = SoundEventQ.front();

		playSound(soundEvent->type);

		delete soundEvent;
		SoundEventQ.pop();
	}

	if (isBGMChannelPlaying())
		FMOD_System_Update(soundSystem);
}

void SoundManager::pushSoundQ(SoundEvent::TYPE type)
{
	//return;

	SoundEvent *soundEvent = NULL;
	soundEvent = new SoundEvent();
	soundEvent->type = type;

	SoundEventQ.push(soundEvent); 
}

void SoundManager::playSound(SoundEvent::TYPE type)
{
	FMOD_SOUND *sound = getSoundWithType(type);
	//FMOD_CHANNEL ***channel = getChannelWithType(type);
	FMOD_Channel_Stop(channel_vector[type]);
	FMOD_System_PlaySound(soundSystem, FMOD_CHANNEL_FREE, sound, 0, &(channel_vector[type]));
}

unsigned int __stdcall SoundManager::loadSoundThread(void * arg)
{
	SoundManager::GetInstance()->loadSound(&SoundManager::GetInstance()->sound_vector[SoundEvent::TYPE::GunPickUp], "./Resource/Sound/gun_pick_up.wav", NONLOOP);
	SoundManager::GetInstance()->loadSound(&SoundManager::GetInstance()->sound_vector[SoundEvent::TYPE::PistolShoot1], "./Resource/Sound/pistol_shoot_1.mp3", NONLOOP);
	SoundManager::GetInstance()->loadSound(&SoundManager::GetInstance()->sound_vector[SoundEvent::TYPE::PistolShoot2], "./Resource/Sound/pistol_shoot_2.mp3", NONLOOP);
	SoundManager::GetInstance()->loadSound(&SoundManager::GetInstance()->sound_vector[SoundEvent::TYPE::PistolReload], "./Resource/Sound/pistol_reload.mp3", NONLOOP);
	SoundManager::GetInstance()->loadSound(&SoundManager::GetInstance()->sound_vector[SoundEvent::TYPE::AssaultRifleShoot1], "./Resource/Sound/assault_rifle_shoot_1_test.mp3", NONLOOP);
	SoundManager::GetInstance()->loadSound(&SoundManager::GetInstance()->sound_vector[SoundEvent::TYPE::AssaultRifleShoot2], "./Resource/Sound/assault_rifle_shoot_2_test.mp3", NONLOOP);
	SoundManager::GetInstance()->loadSound(&SoundManager::GetInstance()->sound_vector[SoundEvent::TYPE::AssaultRifleReload], "./Resource/Sound/assault_rifle_reload.mp3", NONLOOP);
	SoundManager::GetInstance()->loadSound(&SoundManager::GetInstance()->sound_vector[SoundEvent::TYPE::SniperRifleShoot], "./Resource/Sound/sniper_rifle_shoot.mp3", NONLOOP);
	SoundManager::GetInstance()->loadSound(&SoundManager::GetInstance()->sound_vector[SoundEvent::TYPE::SniperRifleReload], "./Resource/Sound/sniper_rifle_reload.mp3", NONLOOP);  //
	SoundManager::GetInstance()->loadSound(&SoundManager::GetInstance()->sound_vector[SoundEvent::TYPE::NoBullet], "./Resource/Sound/ting.mp3", NONLOOP);  //
	SoundManager::GetInstance()->loadSound(&SoundManager::GetInstance()->sound_vector[SoundEvent::TYPE::KillSound], "./Resource/Sound/player_kill.wav", NONLOOP);
	SoundManager::GetInstance()->loadSound(&SoundManager::GetInstance()->sound_vector[SoundEvent::TYPE::DieSound], "./Resource/Sound/sniper_rifle_shoot_2_test.mp3", NONLOOP);
	SoundManager::GetInstance()->loadSound(&SoundManager::GetInstance()->sound_vector[SoundEvent::TYPE::Funky], "./Resource/Sound/Funky.mp3", LOOP);
	SoundManager::GetInstance()->loadEnd = true;

	return 0;
}

void SoundManager::playBGM(SoundEvent::TYPE type)
{
	stopBGM();
	SoundEvent * evnt = new SoundEvent();
	evnt->type = type;
	SoundEventQ.push(evnt);
}



void SoundManager::stopBGM()		//효과음은 멈출수 없음
{
	if (isBGMChannelPlaying())
	{
		FMOD_RESULT retval = FMOD_Channel_Stop(BGMChannel);
 		retval = retval;
	}
}

void SoundManager::Release()
{
	for (auto sound : sound_vector)
	{
		FMOD_Sound_Release(sound);
	}

	FMOD_System_Close(soundSystem);
	FMOD_System_Release(soundSystem);
}