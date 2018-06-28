#include "sc2api/sc2_api.h"
#include "ZergBot.h"
#include "Common.h"

using namespace sc2;

namespace Util {


	struct IsUnit
	{
		sc2::UNIT_TYPEID m_type;

		IsUnit(sc2::UNIT_TYPEID type);
		bool operator()(const sc2::Unit& unit, const sc2::ObservationInterface*);
	};

	int GetPlayer(const sc2::Unit & unit);
	bool IsCombatUnit(const sc2::Unit & unit, ZergBot & bot);
	bool IsCombatUnitType(const sc2::UnitTypeID & type, ZergBot & bot);
	bool IsSupplyProvider(const sc2::Unit & unit);
	bool IsSupplyProviderType(const sc2::UnitTypeID & type);
	bool IsTownHall(const sc2::Unit & unit);
	bool IsTownHallType(const sc2::UnitTypeID & type);
	bool IsRefinery(const sc2::Unit & unit);
	bool IsRefineryType(const sc2::UnitTypeID & type);
	bool IsDetector(const sc2::Unit & type);
	bool IsDetectorType(const sc2::UnitTypeID & type);
	bool IsGeyser(const sc2::Unit & unit);
	bool IsMineral(const sc2::Unit & unit);
	bool IsWorker(const sc2::Unit & unit);
	bool IsWorkerType(const sc2::UnitTypeID & unit);
	bool IsIdle(const sc2::Unit & unit);
	bool IsCompleted(const sc2::Unit & unit);
	float GetAttackRange(const sc2::UnitTypeID & type, ZergBot & bot);

	int GetUnitTypeMineralPrice(const sc2::UnitTypeID type, const ZergBot & bot);
	int GetUnitTypeGasPrice(const sc2::UnitTypeID type, const ZergBot & bot);
	sc2::UnitTypeID GetTownHall(const sc2::Race & race);
	sc2::UnitTypeID GetSupplyProvider(const sc2::Race & race);
	std::string     GetStringFromRace(const sc2::Race & race);
	sc2::Race       GetRaceFromString(const std::string & race);
	sc2::Point2D    CalcCenter(const std::vector<sc2::Unit> & units);

	sc2::UnitTypeID GetUnitTypeIDFromName(const std::string & name, ZergBot & bot);
	sc2::UpgradeID  GetUpgradeIDFromName(const std::string & name, ZergBot & bot);
	sc2::BuffID     GetBuffIDFromName(const std::string & name, ZergBot & bot);
	sc2::AbilityID  GetAbilityIDFromName(const std::string & name, ZergBot & bot);

	float Dist(const sc2::Point2D & p1, const sc2::Point2D & p2);
	float DistSq(const sc2::Point2D & p1, const sc2::Point2D & p2);

	// Kevin-provided helper functions
	void    VisualizeGrids(const sc2::ObservationInterface* obs, sc2::DebugInterface* debug);
	float   TerainHeight(const sc2::GameInfo& info, const sc2::Point2D& point);
	bool    Placement(const sc2::GameInfo& info, const sc2::Point2D& point);
	bool    Pathable(const sc2::GameInfo& info, const sc2::Point2D& point);

	// Added by me (Slava)
	size_t CountSelfUnitsOfType(const ZergBot &bot, sc2::UNIT_TYPEID unitType);
	int CountNumberOfCurrentAbilitiesInProgress(const ZergBot &bot, ABILITY_ID abilityId);
	sc2::Units GetSelfUnitsOfType(const ZergBot & bot, sc2::UNIT_TYPEID unitType);
	sc2::Units GetSelfUnitsOfType(const ZergBot & bot, std::vector<sc2::UNIT_TYPEID> unitTypes);
	sc2::Units GetNeutralUnitsOfType(const ZergBot& bot, sc2::UNIT_TYPEID unitType);
	sc2::Units GetNeutralUnitsOfType(const ZergBot& bot, std::vector<sc2::UNIT_TYPEID> unitTypes);


	// Zerg specific
	size_t CountTownHallTypeBuildings(const ZergBot &bot);
	size_t CountOverlordsAndOverseers(const ZergBot &bot);
	sc2::Units GetIdleDrones(const ZergBot &bot);
}
