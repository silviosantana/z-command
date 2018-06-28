#pragma once

#include <sc2api/sc2_api.h>

class ZergBot;

class MacroManager{

	ZergBot & bot_;

public:

	MacroManager(ZergBot & bot) : bot_(bot) {}
	void OnStart();;

	bool ManageDroneProduction();
	bool ManageOverlordProduction();
	bool ManageGeyserProduction();
	bool ManageZerglingProduction();

	bool ManageDrones();

	bool OrderDrones(int quantity);
	bool OrderOverlords(int quantity);
	bool OrderZergling(int quantity);

	void OnStep();

	sc2::Units GetLarvae();
};