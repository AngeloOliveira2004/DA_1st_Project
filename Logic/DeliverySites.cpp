
#include "DeliverySites.h"

// Constructor definition
DeliverySite::DeliverySite(std::string name,
                           std::string municipality,
                           std::string code,
                           int id,
                           int maxDelivery,
                           int demand,
                           int population,
                           nodeTypes nodeType)
        : name(std::move(name)),
          municipality(std::move(municipality)),
          code(std::move(code)), id(id), maxDelivery(maxDelivery), demand(demand),
          population(population), type(nodeType) {}

// Setter definitions
void DeliverySite::setCode(const std::string& code) {
    this->code = code;
}

void DeliverySite::setId(int id) {
    this->id = id;
}

void DeliverySite::setMunicipality(const std::string& municipality) {
    this->municipality = municipality;
}

// Setter for name
void DeliverySite::setName(const std::string& name) {
    this->name = name;
}

// Setter for maxDelivery
void DeliverySite::setMaxDelivery(int maxDelivery) {
    this->maxDelivery = maxDelivery;
}

// Setter for demand
void DeliverySite::setDemand(int demand) {
    this->demand = demand;
}

// Setter for population
void DeliverySite::setPopulation(int population) {
    this->population = population;
}

// Getter definitions
std::string DeliverySite::getName() const {
    return name;
}

std::string DeliverySite::getMunicipality() const {
    return municipality;
}

std::string DeliverySite::getCode() const {
    return code;
}

[[maybe_unused]] int DeliverySite::getId() const {
    return id;
}

int DeliverySite::getMaxDelivery() const {
    return maxDelivery;
}

int DeliverySite::getDemand() const {
    return demand;
}

// Getter for population
int DeliverySite::getPopulation() const {
    return population;
}

void DeliverySite::printInfo() const {
    // Print delivery site information
    std::cout << "Name: " << name << std::endl;
    std::cout << "Municipality: " << municipality << std::endl;
    std::cout << "Code: " << code << std::endl;
    std::cout << "ID: " << id << std::endl;
    std::cout << "Max Delivery: " << maxDelivery << std::endl;
}

