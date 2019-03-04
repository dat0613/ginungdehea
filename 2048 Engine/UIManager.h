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
	clock_t KillLogDisappearTime;		//KillLog 가 생성된 후 사라질때 까지 걸리는 시각

	void KillLogUpdate();


public:

	void Init();
	void AddKillLog(KillLog * kill_log);
	void Update();
};