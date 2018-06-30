#pragma once

#include <sc2api/sc2_api.h>
#include <sc2api/sc2_interfaces.h>

class ZergBot;

struct IsTownHall {
	bool operator()(const sc2::Unit& unit) {
		switch (unit.unit_type.ToType()) {
		case sc2::UNIT_TYPEID::ZERG_HATCHERY: return true;
		case sc2::UNIT_TYPEID::ZERG_LAIR: return true;
		case sc2::UNIT_TYPEID::ZERG_HIVE: return true;
		default: return false;
		}
	}
};

class MacroManager{

	ZergBot & bot_;

public:

	MacroManager(ZergBot & bot) : bot_(bot) {}
	void OnStart();;

	bool ManageDroneProduction();
	bool ManageOverlordProduction();
	bool ManageGeyserProduction();
	bool ManageZerglingProduction();
	bool ManageQueenProduction();
	bool ManageHydraliskProduction();

	bool ManageDrones();

	bool OrderDrones();
	bool OrderOverlords(int quantity);
	bool OrderHydralisk();
	bool OrderZergling();
	bool OrderQueen();

	void OnStep();
	void HandleGasWorkers();
	sc2::Units GetLarvae();
	bool GetRandomUnit(const sc2::Unit*& unit_out, const sc2::ObservationInterface* observation, sc2::UnitTypeID unit_type);
};