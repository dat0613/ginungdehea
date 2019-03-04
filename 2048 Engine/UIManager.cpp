#include "UIManager.h"
#include "head.h"

void UIManager::KillLogUpdate()
{
	auto CurTime = clock();

	for (int i = 0; i < KILLLOGVECTORSIZE;i++)
	{
		if (KillLogVector[i] != nullptr)
		{
			if (KillLogVector[i]->GetCreatedTime() + KillLogDisappearTime < CurTime)
			{
				KillLogVector[i]->TurnOff();
				KillLogVector[i] = nullptr;
			}
		}
	}
}

void UIManager::Init()
{
	KillLogDisappearTime = 2000;
	KillLogVector.resize(KILLLOGVECTORSIZE, nullptr);
}

void UIManager::AddKillLog(KillLog * kill_log)
{

	float Top_Space = 100.0f; // 가장 위에 있을 킬로그와 상단바 사이의 거리
	float Middle_Space = 20.0f;	// 킬로그와 킬로그 사이 의 여백 공간
	float Right_Space = 20.0f;	// 킬로그와 화면 오른쪽 사이의 거리

	if (KillLogVector[KILLLOGVECTORSIZE - 1] != nullptr)
	{
		auto LastKillLog = KillLogVector[KILLLOGVECTORSIZE - 1];
		KillLogVector[KILLLOGVECTORSIZE - 1] = nullptr;

		LastKillLog->TurnOff();
		// 킬로그가 다 참
		// 마지막 자리를 비워 주어야 함
	}

	for (int i = KILLLOGVECTORSIZE - 1; i > 0;i--)
	{
		if (KillLogVector[i - 1] != nullptr)
		{
			KillLogVector[i] = KillLogVector[i - 1];
			KillLogVector[i - 1] = nullptr;

			KillLogVector[i]->SetDestinationPosition({ SCREENWIDTH - kill_log->getSpriteSize().x - Right_Space,Top_Space + i * (Middle_Space + kill_log->getSpriteSize().y)});
		}
	}

	kill_log->setPosition({ SCREENWIDTH + kill_log->getSpriteSize().x,Top_Space });
	kill_log->SetDestinationPosition({ SCREENWIDTH - kill_log->getSpriteSize().x - Right_Space,Top_Space });
	KillLogVector[0] = kill_log;
}

void UIManager::Update()
{
	KillLogUpdate();
}