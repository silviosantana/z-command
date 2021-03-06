#include "MacroManager.h"
#include "Utilities.h"
#include "time.h"

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

//Vespene gas 
int MacroManager::getGasWorkerCounter() {
	return this->gasWorkerCounter;
}

void MacroManager::setGasWorkerCounter(int counter) {
	this->gasWorkerCounter = counter;
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
	this->setGasWorkerCounter(0);
	
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

	size_t numOfDrones = Util::CountSelfUnitsOfType(bot_, UNIT_TYPEID::ZERG_DRONE);

	if (numOfDrones < 1){
		return false;
	}

	size_t numOfHatcheries = Util::CountTownHallTypeBuildings(bot_);

	if (bot_.getGamePhase() == 0) {
		if (numOfDrones < (numOfHatcheries * 18)) {
			OrderDrones();
		}
		else {
			//std::cout << "Didn't order a drone, hatcheries: " << numOfHatcheries << ", drones atm: " << numOfDrones << std::endl;
		}
	}
	else if (bot_.getGamePhase() == 1){
		// Se cada hatchery possuir menos de 24, faca mais
		if (numOfDrones < (numOfHatcheries * 10)) {
			OrderDrones();
		}
		else {
			//std::cout << "Didn't order a drone, hatcheries: " << numOfHatcheries << ", drones atm: " << numOfDrones << std::endl;
		}
	}
	else {
		if (numOfDrones < (numOfHatcheries * 18)) {
			OrderDrones();
		}
		else {
			//std::cout << "Didn't order a drone, hatcheries: " << numOfHatcheries << ", drones atm: " << numOfDrones << std::endl;
		}

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

	if (bot_.getGamePhase() == 0 || bot_.getGamePhase() == 1) {
		if (numOfZerglings < 35) {
			OrderZergling();
		}
		else {
			//std::cout << "Didn't order a zergling: " << numOfDrones << ", drones " << "game phase: " << bot_.getGamePhase() << "attack phase: "<< bot_.getAttackPhase() <<  std::endl;
		}
	}
	else if (bot_.getGamePhase() == 2) {
		if (numOfZerglings < 40) {
			OrderZergling();

		}
		else{
			//std::cout << "Didn't order a zergling: " << numOfDrones << ", drones " << "game phase: " << bot_.getGamePhase() << "attack phase: " << bot_.getAttackPhase() << std::endl;
		}
		
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

	if (currentOv < 8 && obs->GetMinerals() > 100 && bot_.getGamePhase() == 1) {
		OrderOverlords(1);
	}

	if (currentOv < 15 && obs->GetMinerals() > 100 && bot_.getGamePhase() == 2) {
		OrderOverlords(1);
	}

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

bool MacroManager::ManageHydraliskProduction() {
	Units hydralisks = bot_.Observation()->GetUnits(Unit::Self, IsUnit(UNIT_TYPEID::ZERG_HYDRALISK));
	size_t numOfHydralisk = hydralisks.size();

	if (bot_.Observation()->GetMinerals() < 100 && bot_.Observation()->GetVespene() < 50) {
		return false;
	}

	if (bot_.getGamePhase() == 1) {
		if (numOfHydralisk <= 5) {
			OrderHydralisk();
			return true;
		}
		else {
			std::cout << "Didn't order a Hydralisk" << "game phase: " << bot_.getGamePhase() << "attack phase: " << bot_.getAttackPhase() << std::endl;
		}
	}else if (bot_.getGamePhase() == 2) {
		OrderHydralisk();
	}
	return false;
}

bool MacroManager::ManageMutaliskProduction() {
	size_t numOfSpire = Util::CountSelfUnitsOfType(bot_, UNIT_TYPEID::ZERG_SPIRE);

	if (numOfSpire < 1) {
		return false;
	}

	if (bot_.Observation()->GetMinerals() < 100 && bot_.Observation()->GetVespene() < 100) {
		return false;
	}

	// Criando 1 Mutalisk para cada 5 drones
	size_t numOfDrones = Util::CountSelfUnitsOfType(bot_, UNIT_TYPEID::ZERG_DRONE);
	if (numOfDrones > 1) {
		OrderMutalisk();
		std::cout << "Ordered a Mutalisk(s)" << std::endl;
		return true;
	}

	else {
		std::cout << "Didn't order a Mutalisk" << std::endl;
	}

	return false;
}

bool MacroManager::ManageCorruptorProduction() {
	size_t numOfSpire = Util::CountSelfUnitsOfType(bot_, UNIT_TYPEID::ZERG_SPIRE);

	if (numOfSpire < 1) {
		return false;
	}

	if (bot_.Observation()->GetMinerals() < 150 && bot_.Observation()->GetVespene() < 100) {
		return false;
	}

	// Criando 1 Corruptor para cada 2 drones
	size_t numOfDrones = Util::CountSelfUnitsOfType(bot_, UNIT_TYPEID::ZERG_DRONE);
	if (numOfDrones > 1) {
		OrderCorruptor();
		std::cout << "Ordered a Corruptor(s)" << std::endl;
		return true;
	}

	else {
		std::cout << "Didn't order a Corruptor" << std::endl;
	}

	return false;
}

bool MacroManager::ManageInfestorProduction() {
	size_t numOfPits = Util::CountSelfUnitsOfType(bot_, UNIT_TYPEID::ZERG_INFESTATIONPIT);

	if (numOfPits < 1) {
		return false;
	}

	if (bot_.Observation()->GetMinerals() < 100 && bot_.Observation()->GetVespene() < 150) {
		return false;
	}

	OrderInfestor();

	

	return false;
}

bool MacroManager::ManageRoachProduction() {
	size_t numOfRoachWarren = Util::CountSelfUnitsOfType(bot_, UNIT_TYPEID::ZERG_ROACHWARREN);
	Units roachs = bot_.Observation()->GetUnits(Unit::Self, IsUnit(UNIT_TYPEID::ZERG_ROACH));
	size_t numOfRoachs = roachs.size();

	if (numOfRoachWarren < 1) {
		return false;
	}

	if (bot_.Observation()->GetMinerals() < 75 && bot_.Observation()->GetVespene() < 25) {
		return false;
	}

	if (bot_.getGamePhase() == 1) {
		if (numOfRoachs <= 25) {
			OrderRoach();
		} else {
			std::cout << "Didn't order a Roach" << "game phase: " << bot_.getGamePhase() << "attack phase: " << bot_.getAttackPhase() << std::endl;
		}
	}
	else if (bot_.getGamePhase() == 2) {
		OrderRoach();
	}

	return false;
}

bool MacroManager::ManageQueenProduction() {
	if (bot_.Observation()->GetMinerals() < 150) {
		return false;
	}

	if (Util::CountNumberOfCurrentAbilitiesInProgress(bot_, ABILITY_ID::TRAIN_QUEEN) > 0) {
		return false;
	}

	
	size_t numOfDrones = Util::CountSelfUnitsOfType(bot_, UNIT_TYPEID::ZERG_DRONE);
	size_t numOfQueens = Util::CountSelfUnitsOfType(bot_, UNIT_TYPEID::ZERG_QUEEN);

	if (numOfDrones <15) {
		return false;
	}

	if (bot_.getGamePhase() == 0) {
		if (numOfQueens >= 1) {
			return false;
		}
		OrderQueen();
		//std::cout << "Ordered a Queen(s)" << std::endl;

	}
	else if (bot_.getGamePhase() == 1){
		if (numOfQueens >= 2) {
			return false;
		}
		else {
			OrderQueen();
			//std::cout << "Ordered a Queen(s)" << std::endl;
		}
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

	

	//mineralTypes.push_back(UNIT_TYPEID::NEUTRAL_VESPENEGEYSER);
	/*mineralTypes.push_back(UNIT_TYPEID::NEUTRAL_PROTOSSVESPENEGEYSER);*/

	Units allMineralPatches = Util::GetNeutralUnitsOfType(bot_, mineralTypes);

	Point2D spawn = bot_.GetBuildingManager().GetSpawn();
	float distance = FLT_MAX;

	//Units allHatcheriesPatches = Util::GetSelfUnitsOfType(bot_, centerTypes);


	Tag nearestPatch;


	for (auto patch : allMineralPatches){
		float newDistance = Distance2D(spawn, patch->pos);
		if (newDistance < distance){
			distance = newDistance;
			nearestPatch = (Tag)patch;
		}
	}

	//std::cout << "Drones em idle: " << idleDrones.size() << std::endl;

	for (auto drone : idleDrones){

		//bot_.Actions()->UnitCommand(drone, ABILITY_ID::SMART, nearestPatch);
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
		//std::cout << "Ordered an Overlord" << std::endl;
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
		//std::cout << "Ordered an Zergling" << std::endl;
		return true;	
		
	}

	return false;
}

bool MacroManager::OrderDrones() {

	std::vector<UNIT_TYPEID> centerTypes;
	centerTypes.push_back(UNIT_TYPEID::ZERG_HATCHERY);
	centerTypes.push_back(UNIT_TYPEID::ZERG_HIVE);
	centerTypes.push_back(UNIT_TYPEID::ZERG_LAIR);
	Units centers = Util::GetSelfUnitsOfType(bot_, centerTypes);

	int numHarvester= 100;
	int newNumHarvester;

	Unit bestCenter;

	for (auto & center : centers) {

		newNumHarvester = center->assigned_harvesters;

		if (newNumHarvester < numHarvester) {
			bestCenter = *center;
			numHarvester = newNumHarvester;
		}
	}

	

	// Constru��o de drones
	Units larvae = GetLarvae();
	if (larvae.size() < 1 || bot_.Observation()->GetMinerals() < 50 || bot_.Observation()->GetFoodCap() == bot_.Observation()->GetFoodUsed()) {
		return false;
	}

	for (auto larva : larvae) {		

		if (Distance2D(larva->pos, bestCenter.pos) < 30.0f) {
			bot_.Actions()->UnitCommand(larva, ABILITY_ID::TRAIN_DRONE);
			//std::cout << "mais necessitado: " << bestCenter.assigned_harvesters << std::endl;
			//std::cout << "Ordered a drone(s)" << std::endl;
			return true;
		}		
	}

	return false;
}

bool MacroManager::OrderHydralisk() {
	//Construcao de Hydralisks
	Units larvae = GetLarvae();

	size_t numOfLairs= Util::CountSelfUnitsOfType(bot_, UNIT_TYPEID::ZERG_LAIR);
	size_t numOfHidraDum = Util::CountSelfUnitsOfType(bot_, UNIT_TYPEID::ZERG_HYDRALISKDEN);

	if (numOfLairs = 0 || numOfHidraDum == 0) {
		return false;
	}

	if (larvae.size() < 1){
		return false;
	}

	if ((bot_.Observation()->GetMinerals() < 100 || bot_.Observation()->GetVespene() < 50)) {
		return false;
	}

	for (auto larva : larvae) {
		bot_.Actions()->UnitCommand(larva, ABILITY_ID::TRAIN_HYDRALISK);
		//std::cout << "Ordered a Hydralisk(s)" << std::endl;
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
			//std::cout << " Really ordered a QUEEN! " << std::endl;
			bot_.Actions()->UnitCommand(unit, ABILITY_ID::TRAIN_QUEEN);
			return true;
		}

		return false;
	}

	return false;
}

void MacroManager::ManageQueen() {
	TryInjectLarva();
}

void MacroManager::TryInjectLarva() {
	const ObservationInterface* observation = bot_.Observation();
	Units queens = observation->GetUnits(Unit::Alliance::Self, IsUnit(UNIT_TYPEID::ZERG_QUEEN));
	Units hatcheries = observation->GetUnits(Unit::Alliance::Self, IsTownHall());

	//if we don't have queens or hatcheries don't do anything
	if (queens.empty() || hatcheries.empty())
		return;

	for (size_t i = 0; i < queens.size(); ++i) {
		for (size_t j = 0; j < hatcheries.size(); ++j) {

			//if hatchery isn't complete ignore it
			if (hatcheries.at(j)->build_progress != 1) {
				continue;
			}
			else {

				//Inject larva and move onto next available queen
				if (i < queens.size()) {
					if (queens.at(i)->energy >= 25 && queens.at(i)->orders.empty()) {
						bot_.Actions()->UnitCommand(queens.at(i), ABILITY_ID::EFFECT_INJECTLARVA, hatcheries.at(j));
					}
					++i;
				}
			}
		}
	}
}

bool MacroManager::OrderMutalisk() {
	//Construcao de Mutalisk
	Units larvae = GetLarvae();

	if (larvae.size() < 1) {
		return false;
	}

	if (bot_.Observation()->GetMinerals() < 100 && bot_.Observation()->GetVespene() < 100) {
		return false;
	}

	for (auto larva : larvae) {
		bot_.Actions()->UnitCommand(larva, ABILITY_ID::TRAIN_MUTALISK);
		return true;
	}

	return false;
}

bool MacroManager::OrderCorruptor() {
	//Construcao de Corruptor
	Units larvae = GetLarvae();

	if (larvae.size() < 1) {
		return false;
	}

	if (bot_.Observation()->GetMinerals() < 150 && bot_.Observation()->GetVespene() < 100) {
		return false;
	}

	for (auto larva : larvae) {
		bot_.Actions()->UnitCommand(larva, ABILITY_ID::TRAIN_CORRUPTOR);
		return true;
	}

	return false;
}

bool MacroManager::OrderInfestor() {
	//Construcao de Infestor
	Units larvae = GetLarvae();

	if (larvae.size() < 1) {
		return false;
	}

	if (bot_.Observation()->GetMinerals() < 100 && bot_.Observation()->GetVespene() < 150) {
		return false;
	}

	for (auto larva : larvae) {
		bot_.Actions()->UnitCommand(larva, ABILITY_ID::TRAIN_INFESTOR);
		return true;
	}

	return false;
}

bool MacroManager::OrderRoach() {
	//Construcao de Infestor
	Units larvae = GetLarvae();

	if (larvae.size() < 1) {
		return false;
	}

	if (bot_.Observation()->GetMinerals() < 75 && bot_.Observation()->GetVespene() < 25) {
		return false;
	}

	for (auto larva : larvae) {		
		bot_.Actions()->UnitCommand(larva, ABILITY_ID::TRAIN_ROACH);
		//std::cout << "Ordered an Roach" << std::endl;
		return true;		
	}

	return false;
}

void MacroManager::HandleGasWorkers() {
	// for each unit we have
	std::vector<UNIT_TYPEID> types;
	types.push_back(UNIT_TYPEID::ZERG_EXTRACTOR);
	
	Units extractors = bot_.Observation()->GetUnits(Unit::Self, IsUnits(types));
	size_t numOfExt = extractors.size();

	for (const auto & unit : extractors) {
		
		//std::cout << "tag: " << std::to_string(unit->tag) << " " << i++ << std::endl;

		if (unit->unit_type.ToType() == UNIT_TYPEID::ZERG_EXTRACTOR
			&& unit->build_progress >= 1.0f) {

			//// if we haven't assigned any workers to this refinery yet set count to 0
			if (this->extractorWorkerCount.find(unit->tag) == this->extractorWorkerCount.end())
			{
				std::cout << "Inseriu " << std::to_string(unit->tag) << std::endl;
				this->extractorWorkerCount[unit->tag] = 0;
			}

			int count = this->extractorWorkerCount[unit->tag];
			for (int i = 0; i < (3 - count); i++) {

				const Unit* worker = nullptr;
				if (!GetRandomUnit(worker, bot_.Observation(), UNIT_TYPEID::ZERG_DRONE)) {
					return;
				}
				if (worker != nullptr) {
					bot_.Actions()->UnitCommand(worker, ABILITY_ID::SMART, unit);
					this->extractorWorkerCount[unit->tag] += 1;
					std::cout << "botou drone pra extrair size:" <<this->extractorWorkerCount.size() << std::endl;
				}
			}
				
			//std::cout << "achou extractor size:" << numOfExt << " " <<this->extractorWorkerCount.size() << " " << this->gasWorkerCounter << std::endl;
		}
	}
}

sc2::Point2D MacroManager::getNearestCenter(sc2::Point2D worker) {

	std::vector<UNIT_TYPEID> centerTypes;
	centerTypes.push_back(UNIT_TYPEID::ZERG_HATCHERY);
	centerTypes.push_back(UNIT_TYPEID::ZERG_HIVE);
	centerTypes.push_back(UNIT_TYPEID::ZERG_LAIR);
	
	Point2D nearest;
	float distance = FLT_MAX;
	float newDistance;
	Units centers = Util::GetSelfUnitsOfType(bot_, centerTypes);

	for (auto & center : centers) {

		newDistance = Distance2D(worker, center->pos);

		if (newDistance < distance) {			
			distance = newDistance;
			nearest = center->pos;
		}	
	}

	return nearest;
}

void MacroManager::printWorkersByCenters() {

	std::vector<UNIT_TYPEID> centerTypes;
	centerTypes.push_back(UNIT_TYPEID::ZERG_HATCHERY);
	centerTypes.push_back(UNIT_TYPEID::ZERG_HIVE);
	centerTypes.push_back(UNIT_TYPEID::ZERG_LAIR);	
	
	Units centers = Util::GetSelfUnitsOfType(bot_, centerTypes);

	for (auto & center : centers) {

		if (center->unit_type == UNIT_TYPEID::ZERG_HATCHERY) {
			std::cout << "Hatchery: " << center->assigned_harvesters << std::endl;
		}
		else if (center->unit_type == UNIT_TYPEID::ZERG_HIVE) {
			std::cout << "Hive: " << center->assigned_harvesters << std::endl;
		}
		else if (center->unit_type == UNIT_TYPEID::ZERG_LAIR) {
			std::cout << "Lair: " << center->assigned_harvesters << std::endl;
		}
		
	}
}

void MacroManager::ManagerIdleWorkers() {
	bool find = true;
	Units workers = bot_.Observation()->GetUnits(Unit::Alliance::Self, IsUnit(UNIT_TYPEID::ZERG_DRONE));
	std::vector<UNIT_TYPEID> types;
	types.push_back(UNIT_TYPEID::ZERG_EXTRACTOR);


	Point2D spawn;

	// for each of our workers
	for (auto & worker : workers) {

		if (worker == nullptr) { continue; }
		bool isIdle = worker->orders.empty();
		

		if (isIdle) {
			Point2D spawn = getNearestCenter(worker->pos);
			float distance = FLT_MAX;
			const Unit* target = nullptr;

			Units fields = bot_.Observation()->GetUnits(Unit::Alliance::Neutral);
			Units extrac = bot_.Observation()->GetUnits(Unit::Alliance::Self, IsUnit(UNIT_TYPEID::ZERG_EXTRACTOR));



			for (const auto& u : extrac) {

				float newDistance = Distance2D(spawn, u->pos);

				if (newDistance < distance) {
					if (u->assigned_harvesters >= u->ideal_harvesters) {
						continue;
					}
					distance = newDistance;
					target = u;
					bot_.Actions()->UnitCommand(worker, ABILITY_ID::HARVEST_GATHER_DRONE, target);
					find = false;
				}
			}

			if (find) {
				for (const auto& u : fields) {

					float newDistance = Distance2D(spawn, u->pos);

					if (newDistance < distance) {

						distance = newDistance;
						target = u;
						bot_.Actions()->UnitCommand(worker, ABILITY_ID::HARVEST_GATHER_DRONE, target);
					}
				}
			}
		}
	}
}



void MacroManager::OnStep(){
	
	
	if (GetRandomScalar() < -0.95) {
		std::cout << "Zerglings: " << Util::CountSelfUnitsOfType(bot_, UNIT_TYPEID::ZERG_ZERGLING) << " | Roach: " << Util::CountSelfUnitsOfType(bot_, UNIT_TYPEID::ZERG_ROACH) << " | Overlord: " << Util::CountSelfUnitsOfType(bot_, UNIT_TYPEID::ZERG_OVERLORD) << " | Hidra: " << Util::CountSelfUnitsOfType(bot_, UNIT_TYPEID::ZERG_HYDRALISK) << " | " << "Queens: " << Util::CountSelfUnitsOfType(bot_, UNIT_TYPEID::ZERG_QUEEN) << " | AttackPhase: " << bot_.getAttackPhase() << " | GamePhase: " << bot_.getGamePhase() << std::endl;
		printWorkersByCenters();
	}

	///Manage Production of Units
	ManageDroneProduction();
	ManageOverlordProduction();
	//ManageInfestorProduction();
	ManageQueenProduction();
	
	ManageRoachProduction();
	ManageZerglingProduction();
	ManageHydraliskProduction();

	//ManageMutaliskProduction();
	//ManageCorruptorProduction();
	

	//Manage Units
	//ManageDrones();
	ManageScouting();
	ManageQueen();
	HandleGasWorkers();
	ManagerIdleWorkers();

}