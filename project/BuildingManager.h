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

public:
	BuildingManager(ZergBot & bot) : bot(bot) {};

	void OnStart();
	bool OnStep();
	
	bool OrderExtractor();
	bool TryBuildStructure(ABILITY_ID ability_type_for_structure, UNIT_TYPEID unit_type = UNIT_TYPEID::ZERG_DRONE);
	bool TryBuildSpawningPool();

	//bool TryBuildExtractor();
	bool TryBuildHydraliskDen();
	bool TryBuildSpire();
	
	Unit GetADrone();
	Units GetTownHalls();
	Point2D GetSpawn();

};