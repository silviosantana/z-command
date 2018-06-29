#include "BuildingManager.h"
#include "ZergBot.h"
#include "Utilities.h"

using namespace sc2;
using namespace std;

void BuildingManager::OnStart() {
	Units hatcheries = bot.Observation()->GetUnits(Unit::Self, IsUnit(UNIT_TYPEID::ZERG_HATCHERY));
	for (auto hatchery : hatcheries) {
		spawn = hatchery->pos;
		cout << "Hatchery spawn point x: " << spawn.x << ", y: " << spawn.y << endl;
		bot.setStartingPos(spawn);
	}
}

bool BuildingManager::OnStep() {

	TryBuildSpawningPool();	
	OrderExtractor();
	
	return false;
}

bool BuildingManager::TryBuildStructure(ABILITY_ID ability_type_for_structure, UNIT_TYPEID unit_type) {
	const ObservationInterface* observation = bot.Observation();

	// If a unit already is building a supply structure of this type, do nothing.
	// Also get an scv to build the structure.
	const Unit* unit_to_build = nullptr;
	Units units = observation->GetUnits(Unit::Alliance::Self);
	for (const auto& unit : units) {
		for (const auto& order : unit->orders) {
			if (order.ability_id == ability_type_for_structure) {
				return false;
			}
		}

		if (unit->unit_type == unit_type) {
			unit_to_build = unit;
		}
	}

	float rx = GetRandomScalar();
	float ry = GetRandomScalar();

	bot.Actions()->UnitCommand(unit_to_build,
		ability_type_for_structure,
		Point2D(unit_to_build->pos.x + rx * 15.0f, unit_to_build->pos.y + ry * 15.0f));

	cout << "Estrutura Construida" << std::endl;
	
	return true;
}

bool BuildingManager::TryBuildSpawningPool() {
	const ObservationInterface* observation = bot.Observation();
	size_t numOfOv = Util::CountSelfUnitsOfType(bot, UNIT_TYPEID::ZERG_OVERLORD);
	size_t numOfSpawning = Util::CountSelfUnitsOfType(bot, UNIT_TYPEID::ZERG_SPAWNINGPOOL);	

	if (numOfOv < 1) {
		return false;
	}

	if (numOfSpawning > 0) {
		return false;
	}

	return TryBuildStructure(ABILITY_ID::BUILD_SPAWNINGPOOL);

}

bool BuildingManager::OrderExtractor() {

	

	size_t numOfExtractors = Util::CountSelfUnitsOfType(bot, UNIT_TYPEID::ZERG_EXTRACTOR);
	size_t numOfSpawning = Util::CountSelfUnitsOfType(bot, UNIT_TYPEID::ZERG_SPAWNINGPOOL);

	//|| numOfSpawning == 0

	if (numOfExtractors >= 1 ) {
		return false;
	}

	//Se a quantidade de mineral for menor que 75, nao faca nada
	if (bot.Observation()->GetMinerals() < 75) {
		return false;
	}

	//Se a encomenda de um extrator estiver na fila, nao fazer nada
	if (Util::CountNumberOfCurrentAbilitiesInProgress(bot, ABILITY_ID::BUILD_EXTRACTOR) > 0){
		return false;
	}

	cout << "Ordering an Extractor" << endl;
	

	//Hatchery mais proximo do Spawn
	float distance = FLT_MAX;
	int num_geysers = 0;
	Unit nearestGeyser;
	Units geysers = bot.Observation()->GetUnits(Unit::Neutral);

	for (auto geyser : geysers) {
		if (Util::IsGeyser(*geyser)){
			num_geysers++;
			float newDistance = Distance2D(spawn, geyser->pos);
			if (newDistance < distance){
				nearestGeyser = *geyser;
				distance = newDistance;
			}
		}
	}

	cout << "Available Geysers: "<< num_geysers << endl;
	
	if(num_geysers >= 1){
		Unit builder = GetADrone();		
		bot.Actions()->UnitCommand(&builder, ABILITY_ID::BUILD_EXTRACTOR,&nearestGeyser, true);
	}

	return false; 
}

Unit BuildingManager::GetADrone(){
	Units drones = Util::GetSelfUnitsOfType(bot, UNIT_TYPEID::ZERG_DRONE);

	//Verificar se algum ocioso
	if (bot.Observation()->GetIdleWorkerCount() > 1){
		for (auto drone : drones){
			if (drone->orders.size() < 1){
				return *drone;
			}
		}
	}

	//Caso nao haja, optar aleatoriamente por algum que esta minerando
	for (auto drone : drones){
		for (auto order : drone->orders){
			if (order.ability_id == ABILITY_ID::HARVEST_GATHER || order.ability_id == ABILITY_ID::HARVEST_GATHER_DRONE){
				return *drone;
			}
		}
	}
}

Units BuildingManager::GetTownHalls(){
	vector<UNIT_TYPEID> types;
	types.push_back(UNIT_TYPEID::ZERG_HATCHERY);
	types.push_back(UNIT_TYPEID::ZERG_LAIR);
	types.push_back(UNIT_TYPEID::ZERG_HIVE);

	return bot.Observation()->GetUnits(Unit::Self, IsUnits(types));
}

Point2D BuildingManager::GetSpawn(){
	return spawn;
}