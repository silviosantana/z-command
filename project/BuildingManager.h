#pragma once
#include <sc2api/sc2_unit.h>
#include "sc2api/sc2_api.h"
#include "sc2lib/sc2_lib.h"

//Esta classe eh responsavel pela construcao de unidades

using namespace sc2;
class ZergBot;

class BuildingManager {
	ZergBot & bot;
	bool timeToExpand = false;
	Point2D spawn;
	std::vector<sc2::Point3D> expansions_;
	Point3D startLocation_;

public:
	BuildingManager(ZergBot & bot) : bot(bot) {};

	void OnStart();
	bool OnStep();
	bool BuildingManager::TryBuildSpineCrawler();
	bool OrderExtractor();
	bool TryBuildStructure(ABILITY_ID ability_type_for_structure, UNIT_TYPEID unit_type = UNIT_TYPEID::ZERG_DRONE);
	bool TryMorphUnit(ABILITY_ID ability_type_for_unit, UNIT_TYPEID unit_type);
	bool TryBuildSpawningPool();
	bool TryBuildHatchery(int maxOfCenters, ABILITY_ID ability_type_for_structure, UNIT_TYPEID unit_type = UNIT_TYPEID::ZERG_DRONE);
	bool TryEvolveUnit(ABILITY_ID ability_type_for_unit, UNIT_TYPEID unit_type);
	
	//bool TryBuildExtractor();
	bool TryBuildHydraliskDen();
	bool TryBuildSpire();
	bool TryBuildInfestationPit();
	bool TryBuildRoachWarren();
	
	Unit GetADrone();
	Units GetTownHalls();
	Point2D GetSpawn();

};