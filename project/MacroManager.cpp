#include "MacroManager.h"
#include "Utilities.h"

using namespace sc2;


//Scouting 
int MacroManager::getStatusScout() {
	return this->statusScout;
}

void MacroManager::setStatusScout(int status) {
	this->statusScout = status;
}

void MacroManager::incrementStatusScout() {
	this->statusScout++;
	this->statusScout = this->statusScout % 9;
}

bool MacroManager::ManageScouting() {
	Units overlords = bot_.Observation()->GetUnits(Unit::Self, IsUnit(UNIT_TYPEID::ZERG_OVERLORD));
	//std::cout << "Scouting  " << std::to_string(overlords.size())<< std::endl;

	Point2D EnemySpawnPoint = bot_.Observation()->GetGameInfo().enemy_start_locations.front();

	for (auto overlord : overlords) {

		//checar se est� em idle
		if (overlord->orders.size() < 1) {
			switch (this->statusScout) {
			case 0:
				bot_.Actions()->UnitCommand(overlord, ABILITY_ID::MOVE, Point2D(pontasX[0], pontasY[0]));
				std::cout <<  "Scouting ---------- 0 " << std::to_string(this->getStatusScout()) << " " << std::to_string(pontasX[0]) << " " << std::to_string(pontasY[0]) << std::endl;

				//log("Moving to (" + std::to_string(pontasX[0] * 32) + ", " + std::to_string(pontasY[0] * 32) + ")");
				break;
			case 1:
				bot_.Actions()->UnitCommand(overlord, sc2::ABILITY_ID::MOVE, Point2D(pontasX[0], pontasY[1]));
				std::cout << "Scouting ---------- 1 " << std::to_string(this->getStatusScout()) << " " << std::to_string(pontasX[0]) << " " << std::to_string(pontasY[1]) << std::endl;
				//log("Moving to (" + std::to_string(pontasX[1] * 32) + ", " + std::to_string(pontasY[0] * 32) + ")");
				break;
			case 2:
				bot_.Actions()->UnitCommand(overlord, sc2::ABILITY_ID::MOVE, Point2D(pontasX[0], pontasY[2]));
				std::cout << "Scouting ---------- 2 " << std::to_string(this->getStatusScout()) << " " << std::to_string(pontasX[0]) << " " << std::to_string(pontasY[2]) << std::endl;
				//log("Moving to (" + std::to_string(pontasX[1] * 32) + ", " + std::to_string(pontasY[1] * 32) + ")");
				break;
			case 3:
				bot_.Actions()->UnitCommand(overlord, sc2::ABILITY_ID::MOVE, Point2D(pontasX[1] , pontasY[0] ));
				std::cout << "Scouting ---------- 3 " << std::to_string(this->getStatusScout()) << " " << std::to_string(pontasX[1]) << " " << std::to_string(pontasY[0]) << std::endl;
				//log("Moving to (" + std::to_string(pontasX[0] * 32) + ", " + std::to_string(pontasY[1] * 32) + ")");
				break;
			case 4:
				bot_.Actions()->UnitCommand(overlord, sc2::ABILITY_ID::MOVE, Point2D(pontasX[1], pontasY[1] ));
				std::cout << "Scouting ---------- 4 " << std::to_string(this->getStatusScout()) << " " << std::to_string(pontasX[1]) << " " << std::to_string(pontasY[1]) << std::endl;
				//log("Moving to (" + std::to_string(pontasX[0] * 32) + ", " + std::to_string(pontasY[1] * 32) + ")");
				break;
			case 5:
				bot_.Actions()->UnitCommand(overlord, sc2::ABILITY_ID::MOVE, Point2D(pontasX[1] , pontasY[2] ));
				std::cout << "Scouting ---------- 5 " << std::to_string(this->getStatusScout()) << " " << std::to_string(pontasX[1]) << " " << std::to_string(pontasY[2]) << std::endl;
				//log("Moving to (" + std::to_string(pontasX[0] * 32) + ", " + std::to_string(pontasY[1] * 32) + ")");
				break;
			case 6:
				bot_.Actions()->UnitCommand(overlord, sc2::ABILITY_ID::MOVE, Point2D(pontasX[2] , pontasY[0] ));
				std::cout << "Scouting ---------- 6 " << std::to_string(this->getStatusScout()) << " " << std::to_string(pontasX[2]) << " " << std::to_string(pontasY[0]) << std::endl;
				//log("Moving to (" + std::to_string(pontasX[0] * 32) + ", " + std::to_string(pontasY[1] * 32) + ")");
				break;
			case 7:
				bot_.Actions()->UnitCommand(overlord, sc2::ABILITY_ID::MOVE, Point2D(pontasX[2] , pontasY[1] ));
				std::cout << "Scouting ---------- 7 " << std::to_string(this->getStatusScout()) << " " << std::to_string(pontasX[2]) << " " << std::to_string(pontasY[1]) << std::endl;
				//log("Moving to (" + std::to_string(pontasX[0] * 32) + ", " + std::to_string(pontasY[1] * 32) + ")");
				break;
			case 8:
				bot_.Actions()->UnitCommand(overlord, sc2::ABILITY_ID::MOVE, Point2D(pontasX[2] , pontasY[2] ));
				std::cout << "Scouting ---------- 8 " << std::to_string(this->getStatusScout()) << " " << std::to_string(pontasX[2]) << " " << std::to_string(pontasY[2]) << std::endl;
				//log("Moving to (" + std::to_string(pontasX[0] * 32) + ", " + std::to_string(pontasY[1] * 32) + ")");
				break;
			}

			this->incrementStatusScout();
		}
	}

	return true;
}


void MacroManager::OnStart(){
	// TODO: Initialise things here
	this->setStatusScout(0);

	int middleX = bot_.Observation()->GetGameInfo().width / 2;
	int middleY = bot_.Observation()->GetGameInfo().height / 2;
	pontasX[0] = (middleX * 2) - 10;
	pontasY[0] = (middleY * 2) - 10;
	pontasX[1] = 10;
	pontasY[1] = 10;
	pontasX[2] = middleX;
	pontasY[2] = middleY;
}

bool MacroManager::GetRandomUnit(const Unit*& unit_out, const ObservationInterface* observation, UnitTypeID unit_type) {
	Units my_units = observation->GetUnits(Unit::Alliance::Self);
	std::random_shuffle(my_units.begin(), my_units.end()); // Seleciona aleatoriamente uma unidade
	for (const auto unit : my_units) {
		if (unit->unit_type == unit_type) {
			unit_out = unit;
			return true;
		}
	}
	return false;
}

Units MacroManager::GetLarvae() {
	return bot_.Observation()->GetUnits(Unit::Self, IsUnit(UNIT_TYPEID::ZERG_LARVA));
}

bool MacroManager::ManageDroneProduction(){
	if (bot_.Observation()->GetMinerals() < 50){
		return false;
	}

	// Criando 24 drones
	size_t numOfDrones = Util::CountSelfUnitsOfType(bot_, UNIT_TYPEID::ZERG_DRONE);

	if (numOfDrones < 1){
		return false;
	}

	size_t numOfHatcheries = Util::CountTownHallTypeBuildings(bot_);

	// Se cada hatchery possuir menos de 24, faca mais
	if ((numOfHatcheries * 24 + 2) >= numOfDrones){
		OrderDrones();
	}
	else{
		std::cout << "Didn't order a drone, hatcheries: " << numOfHatcheries << ", drones atm: " << numOfDrones << std::endl;
	}

	return true;
}

bool MacroManager::ManageZerglingProduction() {
	if (bot_.Observation()->GetMinerals() < 50) {
		return false;
	}

	// Criando 30 zerglings
	size_t numOfZerglings = Util::CountSelfUnitsOfType(bot_, UNIT_TYPEID::ZERG_ZERGLING);
	size_t numOfDrones = Util::CountSelfUnitsOfType(bot_, UNIT_TYPEID::ZERG_DRONE);

	if (numOfDrones < 10) {
		return false;
	}

	if (numOfZerglings < 30) {
		OrderZergling();
	}

	else {
		std::cout << "Didn't order a zergling: " << numOfDrones << ", drones " << std::endl;
	}

	return true;
}

bool MacroManager::ManageOverlordProduction(){
	const ObservationInterface *obs = bot_.Observation();

	// Esperar ate 14 drones
	if (obs->GetMinerals() > 100 && obs->GetFoodUsed() == 14 && obs->GetFoodCap() == 14){
		OrderOverlords(1);
		return true;
	}

	size_t currentOv = Util::CountOverlordsAndOverseers(bot_);

	// Lae mid game, build an overlord when 4 away, build two if more than 500 minerals
	if (currentOv > 5){
		if (obs->GetFoodCap() - obs->GetFoodUsed() <= 5){
			OrderOverlords(1);
			return true;
		}
	}

	// Mid game, build an overlord when close to limit (3 away)
	if (obs->GetMinerals() > 100 && currentOv >= 2){
		if (obs->GetFoodCap() - obs->GetFoodUsed() <= 3){
			OrderOverlords(1);
			return true;
		}
	}

	return false;
}

bool MacroManager::ManageGeyserProduction(){
	// Verificar a possibilidade de construir um Geyser.
	if (Util::CountSelfUnitsOfType(bot_, UNIT_TYPEID::ZERG_EXTRACTOR) < 2 || Util::CountSelfUnitsOfType(bot_, UNIT_TYPEID::ZERG_EXTRACTOR) < 1 && bot_.Observation()->GetFoodWorkers() > 14){
		bot_.GetBuildingManager().OrderExtractor();
		return true;
	}

	return false;
}

bool MacroManager::ManageHydraliskProduction() {
	if (bot_.Observation()->GetMinerals() < 100 && bot_.Observation()->GetVespene() < 50) {
		return false;
	}

	// Criando 1 Hydralisk para cada 5 drones
	size_t numOfDrones = Util::CountSelfUnitsOfType(bot_, UNIT_TYPEID::ZERG_DRONE);
	if (numOfDrones >= 5) {
		OrderHydralisk();
		std::cout << "Ordered a Hydralisk(s)" << std::endl;
		return true;
	}

	else {
		std::cout << "Didn't order a Hydralisk" << std::endl;
	}

	return false;
}

bool MacroManager::ManageQueenProduction() {
	if (bot_.Observation()->GetMinerals() < 150) {
		return false;
	}

	// Criando 1 rainha para cada 15 drones
	size_t numOfDrones = Util::CountSelfUnitsOfType(bot_, UNIT_TYPEID::ZERG_DRONE);
	
	if (numOfDrones <15) {
		std::cout << "Didn't order a Queen because of Drones:" << numOfDrones << std::endl;
		return false;
	}

	size_t numOfHatcheries = Util::CountTownHallTypeBuildings(bot_);
	size_t numOfUnits = bot_.Observation()->GetUnits(Unit::Alliance::Self).size();
	// Se cada hatchery possuir menos de 20 unidades, fa�a mais antes de criar a queen!
	if (numOfUnits >= (numOfHatcheries * 20 + 2)) {
		OrderQueen();
		std::cout << "Ordered a Queen(s)" << std::endl;
	}
	else {

		std::cout << "Didn't order a Queen" << std::endl;
	}

	return false;
}

bool MacroManager::ManageDrones(){
	// Definir o numero ideal de drones e geysers

	// Find idle drones, send them to mine a mineral patch close to the base
	Units idleDrones = Util::GetIdleDrones(bot_);

	// Find nearest mineral or rich-mineral patch
	std::vector<UNIT_TYPEID> mineralTypes;
	mineralTypes.push_back(UNIT_TYPEID::NEUTRAL_MINERALFIELD);
	mineralTypes.push_back(UNIT_TYPEID::NEUTRAL_MINERALFIELD750);
	mineralTypes.push_back(UNIT_TYPEID::NEUTRAL_VESPENEGEYSER);
	/*mineralTypes.push_back(UNIT_TYPEID::NEUTRAL_PROTOSSVESPENEGEYSER);*/

	Units allMineralPatches = Util::GetNeutralUnitsOfType(bot_, mineralTypes);

	Point2D spawn = bot_.GetBuildingManager().GetSpawn();
	float distance = FLT_MAX;
	Tag nearestPatch;
	for (auto patch : allMineralPatches){
		float newDistance = Distance2D(spawn, patch->pos);
		if (newDistance < distance){
			distance = newDistance;
			nearestPatch = (Tag)patch;
		}
	}

	for (auto drone : idleDrones){
		bot_.Actions()->UnitCommand(drone, ABILITY_ID::SMART, nearestPatch);
	}

	return false;
}

bool MacroManager::OrderOverlords(int quantity){
	// Before ordering, check how many are in simultanious production, use quantity as limit.
	// If it's already being built, ignore, unless it's less than what the limit is
	if (Util::CountNumberOfCurrentAbilitiesInProgress(bot_, ABILITY_ID::TRAIN_OVERLORD) >= quantity){
		return false;
	}

	Units larvae = GetLarvae();

	// Se nao houver larvas, saia
	if (larvae.size() < 1){
		return false;
	}

	// Se nao houver minerais, saia
	if (bot_.Observation()->GetMinerals() < 100){
		return false;
	}

	for (auto larva : larvae){
		bot_.Actions()->UnitCommand(larva, ABILITY_ID::TRAIN_OVERLORD);
		std::cout << "Ordered an Overlord" << std::endl;
		return true;
	}

	return false;
}

bool MacroManager::OrderZergling() {
	Units larvae = GetLarvae();
	size_t numOfDrones = Util::CountSelfUnitsOfType(bot_, UNIT_TYPEID::ZERG_DRONE);
	size_t numOfSpa = Util::CountSelfUnitsOfType(bot_, UNIT_TYPEID::ZERG_SPAWNINGPOOL);

	if (numOfSpa < 1) {
		return false;
	}

	// Se nao houver minerais, saia
	if (bot_.Observation()->GetMinerals() < 50) {
		return false;
	}

	for (auto larva : larvae) {
		
		bot_.Actions()->UnitCommand(larva, ABILITY_ID::TRAIN_ZERGLING);
		std::cout << "Ordered an Zergling" << std::endl;
		return true;
	}

	return false;
}

bool MacroManager::OrderDrones() {
	// Constru��o de drones
	Units larvae = GetLarvae();
	if (larvae.size() < 1 || bot_.Observation()->GetMinerals() < 50 || bot_.Observation()->GetFoodCap() == bot_.Observation()->GetFoodUsed()) {
		return false;
	}

	for (auto larva : larvae) {
		bot_.Actions()->UnitCommand(larva, ABILITY_ID::TRAIN_DRONE);
		std::cout << "Ordered a drone(s)" << std::endl;
		return true;
	}

	return false;
}

bool MacroManager::OrderHydralisk() {
	//Construcao de Hydralisks
	Units larvae = GetLarvae();

	if (bot_.Observation()->GetFoodCap() == bot_.Observation()->GetFoodUsed()) {
		return false;
	}

	if (larvae.size() < 1 || (bot_.Observation()->GetMinerals() < 100 && bot_.Observation()->GetVespene() < 50)){
		return false;
	}

	for (auto larva : larvae) {
		bot_.Actions()->UnitCommand(larva, ABILITY_ID::TRAIN_HYDRALISK);
		std::cout << "Ordered a Hydralisk(s)" << std::endl;
		return true;
	}

	return false;
}

bool MacroManager::OrderQueen() {

	if (bot_.Observation()->GetMinerals() < 150) {
		return false;
	}

	else {

		if (Util::CountTownHallTypeBuildings(bot_) >= 1) {

			const Unit* unit = nullptr;
			if (!GetRandomUnit(unit, bot_.Observation(), UNIT_TYPEID::ZERG_HATCHERY)) {
				return false;
			}
			std::cout << " Really ordered a QUEEN! " << std::endl;
			bot_.Actions()->UnitCommand(unit, ABILITY_ID::TRAIN_QUEEN);
			return true;
		}

		return false;
	}

	return false;
}

void MacroManager::OnStep()
{
	ManageDroneProduction();
	ManageOverlordProduction();
	//ManageGeyserProduction(); A unica unidade do jogo est� sendo criada no BM
	ManageZerglingProduction();
	ManageDrones();
	HandleGasWorkers();
	ManageQueenProduction();
}

void MacroManager::HandleGasWorkers() {
	// for each unit we have
	
	for (auto & unit : bot_.Observation()->GetUnits(Unit::Alliance::Self))
	{
		// if that unit is a refinery
		//		if (unit.unit_type.toType() == UNIT_TYPEID::ZERG_EXTRACTOR && unit.isCompleted())

		if (unit->unit_type.ToType() == UNIT_TYPEID::ZERG_EXTRACTOR)
		{
			std::cout << "achou extractor" << std::endl;
			// if it's less than we want it to be, fill 'er up
			for (int i = 0; i<2; ++i)
			{
				Units idleDrones = Util::GetIdleDrones(bot_);
				
				if (idleDrones.size() > 0) {
					auto gasWorker = idleDrones[0];

					bot_.Actions()->UnitCommand(gasWorker, ABILITY_ID::SMART, unit);

					//m_workerData.setWorkerJob(gasWorker, WorkerJobs::Gas, unit);					
				}
			}
		}
	}
}