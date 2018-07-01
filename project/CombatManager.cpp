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
	Point2D target_pos;

	size_t numOfZerglings = zerglings.size();
	size_t numOfOverlords = overlords.size();

	ZerglingGroups++;

	if (bot.getAttackPhase() == 0) {
		Units enemy_units = bot.Observation()->GetUnits(Unit::Alliance::Enemy);
		
		if (numOfZerglings > 25) {
			for (auto zergling : zerglings) {
				if (enemy_units.empty()) {
					bot.Actions()->UnitCommand(zergling, ABILITY_ID::ATTACK_ATTACK, EnemySpawnPoint);
					std::cout << "ATACKING SPAWNPOINT" << std::endl;
				}
				else {
					bot.Actions()->UnitCommand(zergling, ABILITY_ID::ATTACK_ATTACK, enemy_units.front()->pos);
					std::cout << "ATACKING FRONT " << enemy_units.size() << std::endl;

				}
			}
			bot.setGamePhase(1);

		}
	}
	else if (bot.getAttackPhase() == 1) {

	}
	return false;
}