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

	//Variaveis de estrategia
	int gamePhase;
	int attackPhase;
	
	Point2D startingPos;
	
	BuildingManager build_man;
	MacroManager mac_man;
	CombatManager com_man;
	 
public:

	ZergBot();

	Point2D getStartingPos();

	void setStartingPosCoords(float x, float y);

	void setStartingPos(Point2D pos);

	int getGamePhase();

	void setGamePhase(int phase);

	int getAttackPhase();

	void setAttackPhase(int phase);

	BuildingManager GetBuildingManager();
	
	void OnStep() override final;
	void OnUnitIdle(const Unit * unit) override final;
	void OnGameStart() override final;
	void OnGameEnd() override final;
	size_t CountUnitType(UNIT_TYPEID unit_type);
	const Unit * FindNearestMineralPatch(const Point2D & start);
};

