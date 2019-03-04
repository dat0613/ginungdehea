#pragma once

#include "Singleton.h"
#include "KillLog.h"

#include <vector>
#include <queue>

using namespace std;

#define KILLLOGVECTORSIZE 5

class UIManager : public Singleton<UIManager>
{
private:
	
	vector<KillLog *> KillLogVector;
	clock_t KillLogDisappearTime;		//KillLog �� ������ �� ������� ���� �ɸ��� �ð�

	void KillLogUpdate();


public:

	void Init();
	void AddKillLog(KillLog * kill_log);
	void Update();
};