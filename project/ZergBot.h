#pragma once

#include <iostream>
#include <sc2api/sc2_api.h>

using namespace sc2;

class ZergBot : public Agent
{
private:
	
	size_t CountUnitType(UNIT_TYPEID unit_type);
	bool TryBuildStructure(ABILITY_ID ability_type_for_structure, UNIT_TYPEID unit_type);
	bool TryBuildSupplyDepot();
	const Unit * FindNearestMineralPatch(const Point2D & start);
	bool TryBuildBarracks();

public:

	ZergBot();
	void OnStep() override final;
	void OnUnitIdle(const Unit * unit) final;
	void OnGameStart() override final;
	void OnGameEnd() override final;
};

