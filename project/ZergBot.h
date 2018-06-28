#pragma once

#include <iostream>
#include <sc2api/sc2_api.h>
#include "BuildingManager.h"
#include "MacroManager.h"
#include "CombatManager.h"

using namespace sc2;

class ZergBot : public Agent
{
private:

	BuildingManager build_man;
	MacroManager mac_man;
	CombatManager com_man;

public:

	ZergBot();
	
	BuildingManager GetBuildingManager();
	
	void OnStep() override final;
	void OnUnitIdle(const Unit * unit) final;
	void OnGameStart() override final;
	void OnGameEnd() override final;
};

