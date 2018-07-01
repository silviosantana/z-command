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

bool CombatManager::ManageAttack() {
	Units zerglings = bot.Observation()->GetUnits(Unit::Self, IsUnit(UNIT_TYPEID::ZERG_ZERGLING));
	Units roachs = bot.Observation()->GetUnits(Unit::Self, IsUnit(UNIT_TYPEID::ZERG_ROACH));
	Units hydralisks = bot.Observation()->GetUnits(Unit::Self, IsUnit(UNIT_TYPEID::ZERG_HYDRALISK));
	
	Point2D target_pos;

	size_t numOfZerglings = zerglings.size();
	size_t numOfRoachs = roachs.size();
	size_t numOfHydralisk = hydralisks.size();


	if (bot.getAttackPhase() == 0) {
		
		Units enemy_units = bot.Observation()->GetUnits(Unit::Alliance::Enemy);
		if (numOfZerglings > 25) {
			for (auto zergling : zerglings) {
				if (enemy_units.empty()) {
					bot.Actions()->UnitCommand(zergling, ABILITY_ID::ATTACK_ATTACK, EnemySpawnPoint);
				}
				else {
					bot.Actions()->UnitCommand(zergling, ABILITY_ID::ATTACK_ATTACK, enemy_units.front());
				}
			}
			bot.setGamePhase(1);
		}
	}
	else if (bot.getAttackPhase() == 1) {
		Units enemy_units = bot.Observation()->GetUnits(Unit::Alliance::Enemy);
		if (numOfZerglings >= 20 && numOfRoachs >= 5 && numOfHydralisk >= 5) {
			for (auto zergling : zerglings) {
				bot.Actions()->UnitCommand(zergling, ABILITY_ID::ATTACK_ATTACK, enemy_units.front());
			}
			for (auto roach : roachs) {
				bot.Actions()->UnitCommand(roach, ABILITY_ID::ATTACK_ATTACK, enemy_units.front());
			}
			for (auto hydralisk : hydralisks) {
				bot.Actions()->UnitCommand(hydralisk, ABILITY_ID::ATTACK_ATTACK, enemy_units.front());
			}
			bot.setGamePhase(2);
		}
	}

	return true;
}

bool CombatManager::OnStep()
{
	//mudar attackPhase 0 -> 1 apos construcao dos extractos e segunda QUEEN
	if (bot.getGamePhase() == 1 && bot.getAttackPhase() == 0 && Util::CountSelfUnitsOfType(bot, UNIT_TYPEID::ZERG_QUEEN) >= 2
		&& Util::CountSelfUnitsOfType(bot, UNIT_TYPEID::ZERG_EXTRACTOR) >= 2) {
		bot.setAttackPhase(1);
	}
	
	ManageAttack();

	return false;
}