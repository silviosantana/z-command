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

	this->expansions_ = search::CalculateExpansionLocations(bot.Observation(), bot.Query());
	startLocation_ = bot.Observation()->GetStartLocation();
}

bool BuildingManager::OnStep() {
	TryBuildSpawningPool();
	TryBuildRoachWarren();

	TryBuildHatchery(2, ABILITY_ID::BUILD_HATCHERY);
	
	if (bot.getGamePhase() == 0) {
		
	}
	else if (bot.getGamePhase() == 1) {
		OrderExtractor();
		TryBuildRoachWarren();		
		TryBuildHatchery(2, ABILITY_ID::BUILD_HATCHERY);
		TryEvolveUnit(ABILITY_ID::RESEARCH_ZERGLINGMETABOLICBOOST, UNIT_TYPEID::ZERG_SPAWNINGPOOL);
		TryEvolveUnit(ABILITY_ID::RESEARCH_GLIALREGENERATION, UNIT_TYPEID::ZERG_ROACHWARREN);
		TryBuildHydraliskDen();
		
		
	}
	else if (bot.getGamePhase() >= 2) {
		TryBuildRoachWarren();
		TryBuildHydraliskDen();
		TryBuildHatchery(4, ABILITY_ID::BUILD_HATCHERY);
		//TryMorphUnit(ABILITY_ID::MORPH_HIVE, UNIT_TYPEID::ZERG_LAIR);
		TryMorphUnit(ABILITY_ID::MORPH_LAIR, UNIT_TYPEID::ZERG_HATCHERY);
		//TryBuildSpire();
		TryEvolveUnit(ABILITY_ID::RESEARCH_ZERGLINGMETABOLICBOOST, UNIT_TYPEID::ZERG_SPAWNINGPOOL);
		TryEvolveUnit(ABILITY_ID::RESEARCH_GLIALREGENERATION, UNIT_TYPEID::ZERG_ROACHWARREN);
		TryEvolveUnit(ABILITY_ID::RESEARCH_ZERGLINGADRENALGLANDS, UNIT_TYPEID::ZERG_SPAWNINGPOOL);
		TryEvolveUnit(ABILITY_ID::RESEARCH_TUNNELINGCLAWS, UNIT_TYPEID::ZERG_ROACHWARREN);
		//TryBuildInfestationPit();

	}
	
	return false;
}

bool BuildingManager::TryEvolveUnit(ABILITY_ID ability_type_for_unit, UNIT_TYPEID unit_type) {

	size_t numOfCntr = Util::CountSelfUnitsOfType(bot, unit_type);

	if (numOfCntr == 0 ) {
		return false;
	}

	const ObservationInterface* observation = bot.Observation();

	Units units = bot.Observation()->GetUnits(Unit::Self);
	const Unit* Unit = nullptr;

	for (const auto& unit : units) {
		if (unit->unit_type == unit_type) {
			Unit = unit;
		}
	}

	bot.Actions()->UnitCommand(Unit, ability_type_for_unit);
}

bool BuildingManager::TryMorphUnit(ABILITY_ID ability_type_for_unit, UNIT_TYPEID unit_type) {
	
	size_t numOfCntr = Util::CountSelfUnitsOfType(bot, unit_type);
	

	if (unit_type == UNIT_TYPEID::ZERG_HATCHERY && Util::CountSelfUnitsOfType(bot, UNIT_TYPEID::ZERG_LAIR) >= 1 ) {
		false;
	}

	if (unit_type == UNIT_TYPEID::ZERG_LAIR && Util::CountSelfUnitsOfType(bot, UNIT_TYPEID::ZERG_HIVE) >= 1) {
		false;
	}

	if (numOfCntr == 0 || GetRandomScalar() > -0.75 ) {
		return false;
	}
	
	const ObservationInterface* observation = bot.Observation();

	Units units = bot.Observation()->GetUnits(Unit::Self);
	const Unit* centerUnit = nullptr;

	for (const auto& unit : units) {
		if (unit->unit_type == unit_type) {
			centerUnit = unit;
		}
	}

	if (unit_type == UNIT_TYPEID::ZERG_HATCHERY) {
		bot.Actions()->UnitCommand(centerUnit, ABILITY_ID::MORPH_LAIR); 
	}
	else if (unit_type == UNIT_TYPEID::ZERG_LAIR) {
		bot.Actions()->UnitCommand(centerUnit, ABILITY_ID::MORPH_HIVE);
	}	
	
	return true;
}

bool BuildingManager::TryBuildSpineCrawler() {

	size_t numOfSC = Util::CountSelfUnitsOfType(bot, UNIT_TYPEID::ZERG_SPINECRAWLER);
	size_t numOfCenters = Util::CountSelfUnitsOfType(bot, UNIT_TYPEID::ZERG_HATCHERY) + Util::CountSelfUnitsOfType(bot, UNIT_TYPEID::ZERG_LAIR) + Util::CountSelfUnitsOfType(bot, UNIT_TYPEID::ZERG_HIVE);
	
	if (GetRandomScalar() > 0.5 && numOfSC < 2 * numOfCenters){
		return TryBuildStructure(ABILITY_ID::BUILD_SPINECRAWLER);
	}

	return true;
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

	bool bad_location = true;
	float rx;
	float ry;
	Point2D startingPos = bot.getStartingPos();

	while (bad_location) {

		rx = GetRandomScalar();
		ry = GetRandomScalar();		

		if (bot.Query()->Placement(ability_type_for_structure, Point2D(startingPos.x + rx * 15.0f, startingPos.y + ry * 15.0f))) //verifica se a posicao gerada é valida
		{
			bot.Actions()->UnitCommand(unit_to_build, ability_type_for_structure, Point2D(startingPos.x + rx * 15.0f, startingPos.y + ry * 15.0f));
			
			//cout << "Estrutura construída -> " << int(ability_type_for_structure) << std::endl;
			bad_location = false;
		}
	}

	return true;
}

//BUILD_HATCHERY

bool BuildingManager::TryBuildHatchery(int maxOfCenters, ABILITY_ID ability_type_for_structure, UNIT_TYPEID unit_type) {

	size_t numOfCenters = Util::CountSelfUnitsOfType(bot, UNIT_TYPEID::ZERG_HATCHERY) + Util::CountSelfUnitsOfType(bot, UNIT_TYPEID::ZERG_LAIR) + Util::CountSelfUnitsOfType(bot, UNIT_TYPEID::ZERG_HIVE);
	const ObservationInterface* observation = bot.Observation();

	if (numOfCenters == maxOfCenters) {
		return false;
	}

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


	//encontrando uma posicao para construir
	float minimum_distance = std::numeric_limits<float>::max();
	Point3D closest_expansion;
	for (const auto& expansion : expansions_) {
		float current_distance = Distance2D(startLocation_, expansion);
		if (current_distance < .01f) {
			continue;
		}

		if (current_distance < minimum_distance) {
			if (bot.Query()->Placement(ability_type_for_structure, expansion)) {
				closest_expansion = expansion;
				minimum_distance = current_distance;
			}
		}
	}

	bot.Actions()->UnitCommand(unit_to_build,
		ability_type_for_structure,
		closest_expansion);
}

bool BuildingManager::TryBuildSpawningPool() {
	const ObservationInterface* observation = bot.Observation();
	size_t numOfOv = Util::CountSelfUnitsOfType(bot, UNIT_TYPEID::ZERG_OVERLORD);
	size_t numOfSpawning = Util::CountSelfUnitsOfType(bot, UNIT_TYPEID::ZERG_SPAWNINGPOOL);	

	if (bot.Observation()->GetMinerals() < 200) {
		return false;
	}

	if (numOfOv < 1) {
		return false;
	}

	if (numOfSpawning > 0) {
		return false;
	}

	//Se a encomenda de um SpawningPool estiver na fila, nao fazer nada
	if (Util::CountNumberOfCurrentAbilitiesInProgress(bot, ABILITY_ID::BUILD_SPAWNINGPOOL) > 0) {
		return false;
	}

	return TryBuildStructure(ABILITY_ID::BUILD_SPAWNINGPOOL);
}

bool BuildingManager::TryBuildHydraliskDen() {

	const ObservationInterface* observation = bot.Observation();
	size_t numOfLairs = Util::CountSelfUnitsOfType(bot, UNIT_TYPEID::ZERG_LAIR);
	size_t numOfDens = Util::CountSelfUnitsOfType(bot, UNIT_TYPEID::ZERG_HYDRALISKDEN);

	if ((bot.Observation()->GetMinerals() < 100) || (bot.Observation()->GetVespene() < 50)) {
		return false;
	}

	if (numOfLairs < 1) {
		return false;
	}

	if (numOfDens > 0) {
		return false;
	}

	//Se a encomenda de um HydraliskDen estiver na fila, nao fazer nada
	if (Util::CountNumberOfCurrentAbilitiesInProgress(bot, ABILITY_ID::BUILD_HYDRALISKDEN) > 0) {
		return false;
	}

	return TryBuildStructure(ABILITY_ID::BUILD_HYDRALISKDEN);

}







bool BuildingManager::TryBuildInfestationPit() {

	const ObservationInterface* observation = bot.Observation();
	size_t numOfLairs = Util::CountSelfUnitsOfType(bot, UNIT_TYPEID::ZERG_LAIR);
	size_t numOfPits = Util::CountSelfUnitsOfType(bot, UNIT_TYPEID::ZERG_INFESTATIONPIT);

	if ((bot.Observation()->GetMinerals() < 100) || (bot.Observation()->GetVespene() < 100)) {
		return false;
	}

	if (numOfLairs < 1) {
		return false;
	}

	if (numOfPits > 0) {
		return false;
	}

	//Se a encomenda de um HydraliskDen estiver na fila, nao fazer nada
	if (Util::CountNumberOfCurrentAbilitiesInProgress(bot, ABILITY_ID::BUILD_INFESTATIONPIT) > 0) {
		return false;
	}

	return TryBuildStructure(ABILITY_ID::BUILD_INFESTATIONPIT);

}

bool BuildingManager::TryBuildSpire() {

	const ObservationInterface* observation = bot.Observation();
	size_t numOfLairs = Util::CountSelfUnitsOfType(bot, UNIT_TYPEID::ZERG_LAIR);
	size_t numOfSpires = Util::CountSelfUnitsOfType(bot, UNIT_TYPEID::ZERG_SPIRE);

	if ((bot.Observation()->GetMinerals() < 200) || (bot.Observation()->GetVespene() < 200)) {
		return false;
	}

	if (numOfLairs < 1) {
		return false;
	}

	if (numOfSpires > 0) {
		return false;
	}

	//Se a encomenda de um Spire estiver na fila, nao fazer nada
	if (Util::CountNumberOfCurrentAbilitiesInProgress(bot, ABILITY_ID::BUILD_SPIRE) > 0) {
		return false;
	}

	return TryBuildStructure(ABILITY_ID::BUILD_SPIRE);

}
bool BuildingManager::TryBuildRoachWarren() {

	const ObservationInterface* observation = bot.Observation();
	size_t numOfLairs		= Util::CountSelfUnitsOfType(bot, UNIT_TYPEID::ZERG_LAIR);
	size_t numOfRoachWarren = Util::CountSelfUnitsOfType(bot, UNIT_TYPEID::ZERG_ROACHWARREN);

	if (bot.Observation()->GetMinerals() < 150) {
		return false;
	}

	//if (numOfLairs < 1) {
	//	return false;
	//}

	if (numOfRoachWarren > 0) {
		return false;
	}

	//Se a encomenda de um Spire estiver na fila, nao fazer nada
	if (Util::CountNumberOfCurrentAbilitiesInProgress(bot, ABILITY_ID::BUILD_ROACHWARREN) > 0) {
		return false;
	}

	return TryBuildStructure(ABILITY_ID::BUILD_ROACHWARREN);

}

bool BuildingManager::OrderExtractor() {

	size_t numOfExtractors = Util::CountSelfUnitsOfType(bot, UNIT_TYPEID::ZERG_EXTRACTOR);
	size_t numOfSpawning = Util::CountSelfUnitsOfType(bot, UNIT_TYPEID::ZERG_SPAWNINGPOOL);


	if (numOfExtractors >= 2 || numOfSpawning == 0) {
		return false;
	}

	//Se a quantidade de mineral for menor que 75, nao faca nada
	if (bot.Observation()->GetMinerals() < 75) {
		return false;
	}

	//Se a encomenda de um extrator estiver na fila, nao fazer nada
	if (Util::CountNumberOfCurrentAbilitiesInProgress(bot, ABILITY_ID::BUILD_EXTRACTOR) > 0) {
		return false;
	}

	//cout << "Ordering an Extractor" << endl;


	//Hatchery mais proximo do Spawn
	float distance = FLT_MAX;
	int num_geysers = 0;
	Unit nearestGeyser;
	Units geysers = bot.Observation()->GetUnits(Unit::Neutral);

	for (auto geyser : geysers) {
		if (Util::IsGeyser(*geyser)) {
			num_geysers++;
			float newDistance = Distance2D(spawn, geyser->pos);
			if (newDistance < distance) {
				nearestGeyser = *geyser;
				distance = newDistance;
			}
		}
	}

	//cout << "Available Geysers: " << num_geysers << endl;

	if (num_geysers >= 1) {
		Unit builder = GetADrone();
		bot.Actions()->UnitCommand(&builder, ABILITY_ID::BUILD_EXTRACTOR, &nearestGeyser, true);
	}

	return false;
}

Unit BuildingManager::GetADrone() {
	Units drones = Util::GetSelfUnitsOfType(bot, UNIT_TYPEID::ZERG_DRONE);

	//Verificar se algum ocioso
	if (bot.Observation()->GetIdleWorkerCount() > 1) {
		for (auto drone : drones) {
			if (drone->orders.size() < 1) {
				return *drone;
			}
		}
	}

	//Caso nao haja, optar aleatoriamente por algum que esta minerando
	for (auto drone : drones) {
		for (auto order : drone->orders) {
			if (order.ability_id == ABILITY_ID::HARVEST_GATHER || order.ability_id == ABILITY_ID::HARVEST_GATHER_DRONE) {
				return *drone;
			}
		}
	}
}

Units BuildingManager::GetTownHalls() {
	vector<UNIT_TYPEID> types;
	types.push_back(UNIT_TYPEID::ZERG_HATCHERY);
	types.push_back(UNIT_TYPEID::ZERG_LAIR);
	types.push_back(UNIT_TYPEID::ZERG_HIVE);

	return bot.Observation()->GetUnits(Unit::Self, IsUnits(types));
}

Point2D BuildingManager::GetSpawn() {
	return spawn;
}