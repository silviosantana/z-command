#pragma once

#include <sc2api/sc2_api.h>
#include <sc2api/sc2_interfaces.h>
#include <sc2api/sc2_unit.h>

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
private:
	//Scouting
	int statusScout;
	int pontasX[3];
	int pontasY[3];
	int gasWorkerCounter;


public:

	MacroManager(ZergBot & bot) : bot_(bot) {}
	int getStatusScout();
	void setStatusScout(int status);

	int getGasWorkerCounter();
	void setGasWorkerCounter(int counter);

	void incrementStatusScout();
	void OnStart();;

	bool ManageDroneProduction();
	bool ManageOverlordProduction();
	bool ManageGeyserProduction();
	bool ManageZerglingProduction();
	bool ManageQueenProduction();
	bool ManageHydraliskProduction();
	bool ManageMutaliskProduction();
	bool ManageCorruptorProduction();
	bool ManageInfestorProduction();

	bool ManageDrones();
	void ManageQueen();
	bool ManageScouting();

	bool OrderDrones();
	bool OrderOverlords(int quantity);
	bool OrderHydralisk();
	bool OrderZergling();
	bool OrderQueen();
	void TryInjectLarva();
	bool OrderMutalisk();
	bool OrderCorruptor();
	bool OrderInfestor();

	void OnStep();
	void HandleGasWorkers();
	sc2::Units GetLarvae();
	bool GetRandomUnit(const sc2::Unit*& unit_out, const sc2::ObservationInterface* observation, sc2::UnitTypeID unit_type);
};