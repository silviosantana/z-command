#pragma once

#include <sc2api/sc2_api.h>
using namespace sc2;

class ZergBot;

class CombatManager{
	ZergBot & bot;
	Point2D EnemySpawnPoint;

public:
	CombatManager(ZergBot & bot) : bot(bot) {};

	void OnStart();
	bool OnStep();
};