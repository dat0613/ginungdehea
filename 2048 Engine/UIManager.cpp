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

	float Top_Space = 100.0f; // ���� ���� ���� ų�α׿� ��ܹ� ������ �Ÿ�
	float Middle_Space = 20.0f;	// ų�α׿� ų�α� ���� �� ���� ����
	float Right_Space = 20.0f;	// ų�α׿� ȭ�� ������ ������ �Ÿ�

	if (KillLogVector[KILLLOGVECTORSIZE - 1] != nullptr)
	{
		auto LastKillLog = KillLogVector[KILLLOGVECTORSIZE - 1];
		KillLogVector[KILLLOGVECTORSIZE - 1] = nullptr;

		LastKillLog->TurnOff();
		// ų�αװ� �� ��
		// ������ �ڸ��� ��� �־�� ��
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