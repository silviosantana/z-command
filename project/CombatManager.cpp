#include <iostream>
#include "CombatManager.h"
#include "ZergBot.h"
#include "Utilities.h"

using namespace std;

void CombatManager::OnStart()
{
	// Determine and save the point of enemy spawn
	EnemySpawnPoint = bot.Observation()->GetGameInfo().enemy_start_locations.front();
	ZerglingGroups = 0;
	cout << "Enemy Spawn is at X: " << EnemySpawnPoint.x << ", Y: " << EnemySpawnPoint.y << endl;
}

bool CombatManager::OnStep()
{
	Units zerglings = bot.Observation()->GetUnits(Unit::Self, IsUnit(UNIT_TYPEID::ZERG_ZERGLING));
	Units overlords = bot.Observation()->GetUnits(Unit::Self, IsUnit(UNIT_TYPEID::ZERG_OVERLORD));
	
	size_t numOfZerglings = zerglings.size();
	size_t numOfOverlords = overlords.size();

	ZerglingGroups++;

	if (numOfZerglings > 20) {
			for (auto zergling : zerglings) {
				bot.Actions()->UnitCommand(zergling, ABILITY_ID::ATTACK_ATTACK, EnemySpawnPoint);
			}

		}

	return false;
}