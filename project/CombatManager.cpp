#include <iostream>
#include "CombatManager.h"
#include "ZergBot.h"
#include "Utilities.h"

using namespace std;

void CombatManager::OnStart()
{
	// Determine and save the point of enemy spawn
	EnemySpawnPoint = bot.Observation()->GetGameInfo().enemy_start_locations.front();
	cout << "Enemy Spawn is at X: " << EnemySpawnPoint.x << ", Y: " << EnemySpawnPoint.y << endl;
}

bool CombatManager::OnStep()
{
	Units zerglings = bot.Observation()->GetUnits(Unit::Self, IsUnit(UNIT_TYPEID::ZERG_ZERGLING));
	size_t numOfZerglings = zerglings.size();

	if (numOfZerglings > 15) {
		for(auto zergling : zerglings){
				bot.Actions()->UnitCommand(zergling, ABILITY_ID::ATTACK_ATTACK, EnemySpawnPoint);
			}
	}

	return false;
}