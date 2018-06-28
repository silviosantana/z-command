#include "ZergBot.h"


ZergBot::ZergBot()
{
}

size_t ZergBot::CountUnitType(UNIT_TYPEID unit_type) {
	return Observation()->GetUnits(Unit::Alliance::Self, IsUnit(unit_type)).size();
}

bool ZergBot::TryBuildStructure(ABILITY_ID ability_type_for_structure, UNIT_TYPEID unit_type = UNIT_TYPEID::ZERG_DRONE) {
	const ObservationInterface* observation = Observation();

	// If a unit already is building a supply structure of this type, do nothing.
	// Also get an scv to build the structure.
	const Unit* unit_to_build = nullptr;
	Units units = observation->GetUnits(Unit::Alliance::Self);
	for (const auto& unit : units) {
		for (const auto& order : unit->orders) {
			if (order.ability_id == ability_type_for_structure) {
				return false;
			}
		}

		if (unit->unit_type == unit_type) {
			unit_to_build = unit;
		}
	}

	float rx = GetRandomScalar();
	float ry = GetRandomScalar();

	Actions()->UnitCommand(unit_to_build,
		ability_type_for_structure,
		Point2D(unit_to_build->pos.x + rx * 15.0f, unit_to_build->pos.y + ry * 15.0f));

	return true;
}

bool ZergBot::OrderOverlod() {
	const ObservationInterface* observation = Observation();

	// If we are not supply capped, don't train a overlord.
	if (observation->GetFoodUsed() <= observation->GetFoodCap() - 2)
		return false;

	Units larvas = observation->GetUnits(Unit::Self, IsUnit(UNIT_TYPEID::ZERG_LARVA));

	// Skip if no larvae
	if (larvas.size() < 1)
	{
		return false;
	}

	// Skip if not enough minerals
	if (observation->GetMinerals() < 100)
	{
		return false;
	}

	for (auto larva : larvas)
	{
		Actions()->UnitCommand(larva, ABILITY_ID::TRAIN_OVERLORD);
		std::cout << "Ordered an Overlord" << std::endl;
		return true;
	}

	return false;
}

const Unit* ZergBot::FindNearestMineralPatch(const Point2D& start) {
	Units units = Observation()->GetUnits(Unit::Alliance::Neutral);
	float distance = std::numeric_limits<float>::max();
	const Unit* target = nullptr;
	for (const auto& u : units) {
		if (u->unit_type == UNIT_TYPEID::NEUTRAL_MINERALFIELD) {
			float d = DistanceSquared2D(u->pos, start);
			if (d < distance) {
				distance = d;
				target = u;
			}
		}
	}
	return target;
}

bool ZergBot::TryBuildSpawningPool() {
	const ObservationInterface* observation = Observation();

	if (CountUnitType(UNIT_TYPEID::ZERG_OVERLORD) < 1) {
		return false;
	}

	if (CountUnitType(UNIT_TYPEID::ZERG_SPAWNINGPOOL) > 0) {
		return false;
	}

	return TryBuildStructure(ABILITY_ID::BUILD_SPAWNINGPOOL);

}


void ZergBot::OnGameStart() {
	std::cout << "Hello, World!" << std::endl;
}

void ZergBot::OnGameEnd()
{
}

void ZergBot::OnStep() {
	OrderOverlod();
	TryBuildSpawningPool();
}

void ZergBot::OnUnitIdle(const Unit* unit) {
	switch (unit->unit_type.ToType()) {
	case UNIT_TYPEID::ZERG_LARVA: {
		if (CountUnitType(UNIT_TYPEID::ZERG_DRONE) < 25) {
			Actions()->UnitCommand(unit, ABILITY_ID::TRAIN_DRONE);
		}
		else if (CountUnitType(UNIT_TYPEID::ZERG_SPAWNINGPOOL) >= 1){
			Actions()->UnitCommand(unit, ABILITY_ID::TRAIN_ZERGLING);
		}
		
		break;
	}
	case UNIT_TYPEID::ZERG_DRONE: {
		const Unit* mineral_target = FindNearestMineralPatch(unit->pos);
		if (!mineral_target) {
			break;
		}
		Actions()->UnitCommand(unit, ABILITY_ID::SMART, mineral_target);
		break;
	}
	
	case UNIT_TYPEID::ZERG_ZERGLING: {
		if (CountUnitType(UNIT_TYPEID::ZERG_ZERGLING) > 24) {
			const GameInfo& game_info = Observation()->GetGameInfo();
			Actions()->UnitCommand(unit, ABILITY_ID::ATTACK_ATTACK, game_info.enemy_start_locations.front());
		}
		break;
	}
	default: {
		break;
	}
	}
}


