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
	Units infestors = bot.Observation()->GetUnits(Unit::Self, IsUnit(UNIT_TYPEID::ZERG_INFESTOR));

	Point2D target_pos;

	size_t numOfZerglings = zerglings.size();
	size_t numOfRoachs = roachs.size();
	size_t numOfHydralisk = hydralisks.size();
	size_t numOfinfestors = infestors.size();

	Units iddleZr;
	Units iddleRc;
	Units iddleHl;


	for (auto & zerling : zerglings) {
		if (zerling->orders.empty()) {
			iddleZr.push_back(zerling);
		}
	}

	for (auto & roach : roachs) {
		if (roach->orders.empty()) {
			iddleRc.push_back(roach);
		}
	}

	for (auto & hydralisk : hydralisks) {
		if (hydralisk->orders.empty()) {
			iddleHl.push_back(hydralisk);
		}
	}


	if (bot.getAttackPhase() == 0) {
		
		Units enemy_units = bot.Observation()->GetUnits(Unit::Alliance::Enemy);			

		if (iddleZr.size() > 25) {
			
				if (enemy_units.empty()) {
					bot.Actions()->UnitCommand(iddleZr, ABILITY_ID::ATTACK_ATTACKBUILDING, EnemySpawnPoint);
				}
				else {
					bot.Actions()->UnitCommand(iddleZr, ABILITY_ID::ATTACK_ATTACKBUILDING, enemy_units.front());
				}
			
			bot.setGamePhase(1);
		}
	}
	else {
		Units enemy_units = bot.Observation()->GetUnits(Unit::Alliance::Enemy);

		if (iddleZr.size() >= 30 && iddleRc.size() >= 15 ) {
			
				
			bot.Actions()->UnitCommand(iddleZr, ABILITY_ID::ATTACK_ATTACKBUILDING, enemy_units.front());
			bot.Actions()->UnitCommand(iddleRc, ABILITY_ID::ATTACK_ATTACKBUILDING, enemy_units.front());
			bot.Actions()->UnitCommand(iddleHl, ABILITY_ID::ATTACK_ATTACKBUILDING, enemy_units.front());
			//bot.Actions()->UnitCommand(infestors, ABILITY_ID::ATTACK_ATTACK, enemy_units.front());
						
			bot.setGamePhase(2);
		}	

		if (iddleZr.size() >= 40) {

			bot.Actions()->UnitCommand(iddleZr, ABILITY_ID::ATTACK_ATTACKBUILDING, enemy_units.front());
			bot.Actions()->UnitCommand(iddleHl, ABILITY_ID::ATTACK_ATTACKBUILDING, enemy_units.front());

		}

		if (iddleRc.size() >= 25) {

			bot.Actions()->UnitCommand(iddleRc, ABILITY_ID::ATTACK_ATTACKBUILDING, enemy_units.front());
			bot.Actions()->UnitCommand(iddleHl, ABILITY_ID::ATTACK_ATTACKBUILDING, enemy_units.front());
		}
	}
	

	return true;
}

bool CombatManager::OnStep()
{
	//mudar attackPhase 0 -> 1 apos construcao dos extractos e segunda QUEEN
	if (bot.getGamePhase() == 1 && bot.getAttackPhase() == 0 && Util::CountSelfUnitsOfType(bot, UNIT_TYPEID::ZERG_QUEEN) >= 2
		&& Util::CountSelfUnitsOfType(bot, UNIT_TYPEID::ZERG_EXTRACTOR) >= 1) {
		bot.setAttackPhase(1);
	}
	
	ManageAttack();

	return false;
}