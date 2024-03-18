#include "DeliverySites.h"

DeliverySite::DeliverySite(std::string code) : code(std::move(code)) {}

std::string DeliverySite::getCode() const {
    return code;
}


void DeliverySite::setCode(const std::string& code) {
    this->code = code;
}

FireStation::FireStation(std::string code, int id) : DeliverySite(std::move(code)), id(id) {}

int FireStation::getId() const {
    return id;
}

nodeTypes FireStation::getNodeType() const {
    return FIRE_STATION;
}

void FireStation::setId(int id) {
    this->id = id;
}


City::City(std::string name, std::string code, int id, int demand, int population)
        : DeliverySite(std::move(code)), name(std::move(name)), id(id), demand(demand), population(population) {}

std::string City::getName() const {
    return name;
}

int City::getId() const {
    return id;
}

int City::getDemand() const {
    return demand;
}

int City::getPopulation() const {
    return population;
}

nodeTypes City::getNodeType() const {
    return CITY;
}

void City::setName(const std::string& name) {
    this->name = name;
}

void City::setId(int id) {
    this->id = id;
}

void City::setDemand(int demand) {
    this->demand = demand;
}

void City::setPopulation(int population) {
    this->population = population;
}


WaterReservoir::WaterReservoir(std::string name, std::string municipality, std::string code, int id, int maxDelivery)
        : DeliverySite(std::move(code)), name(std::move(name)), municipality(std::move(municipality)), id(id), maxDelivery(maxDelivery) {}

std::string WaterReservoir::getName() const {
    return name;
}

std::string WaterReservoir::getMunicipality() const {
    return municipality;
}

int WaterReservoir::getId() const {
    return id;
}

int WaterReservoir::getMaxDelivery() const {
    return maxDelivery;
}

nodeTypes WaterReservoir::getNodeType() const {
    return WATER_RESERVOIR;
}

void WaterReservoir::setName(const std::string& name) {
    this->name = name;
}

void WaterReservoir::setMunicipality(const std::string& municipality) {
    this->municipality = municipality;
}

void WaterReservoir::setId(int id) {
    this->id = id;
}

void WaterReservoir::setMaxDelivery(int maxDelivery) {
    this->maxDelivery = maxDelivery;
}
