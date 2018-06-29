#include "ZergBot.h"
#include <sc2utils/sc2_manage_process.h>

using namespace std;

ZergBot::ZergBot():
	build_man(*this),
	mac_man(*this),
	com_man(*this)
	{}

BuildingManager ZergBot::GetBuildingManager(){
	return this->build_man;
}

void ZergBot::OnGameStart() {
	build_man.OnStart();
	mac_man.OnStart();
	com_man.OnStart();
}

void ZergBot::OnGameEnd(){
	cout << "Game ended" << endl;
	const char *replay_filename = "C:/Blizzard/StarCraft II/Replays/zerg_bot.SC2Replay";
	Control()->SaveReplay(replay_filename);
	Control()->SaveReplay("zerg_bot_local.SC2Replay");
	cout << "Saved the replay to " << replay_filename;
}

void ZergBot::OnStep() {
	mac_man.OnStep();
	com_man.OnStep();
	build_man.OnStep();
}

void ZergBot::OnUnitIdle(const Unit* unit) {
}