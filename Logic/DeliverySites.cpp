#include "DeliverySites.h"

#include <utility>

// Fire_Station constructor
Fire_Station::Fire_Station(int id , std::string code)
        : type(Sinks::FIRE_STATION), id(id), code(std::move(code)) {}

std::string Fire_Station::getCode() const {
    return code;
}

int Fire_Station::getId() const {
    return id;
}

void Fire_Station::setCode(const std::string& code) {
    this->code = code;
}

void Fire_Station::setId(int id) {
    this->id = id;
}

void Fire_Station::printInfo() const {
    std::cout<< id << " " << code << "\n";
}

// City constructor
City::City(std::string name, std::string  code, int id,
           int demand, int population)
        : type(Sinks::CITY), name(std::move(name)), code(std::move(code)),
          id(id), demand(demand), population(population) {}

// City getters
std::string City::getName() const {
    return name;
}

std::string City::getCode() const {
    return code;
}

int City::getId() const {
    return id;
}

int  City::getDemand() const {
    return demand;
}

int  City::getPopulation() const {
    return population;
}

// City setters
void City::setName(const std::string& name) {
    this->name = name;
}

void City::setCode(const std::string& code) {
    this->code = code;
}

void City::setId(int id) {
    this->id = id;
}

void City::setDemand(int demand) {
    this->demand = demand;
}

void City::setPopulation(int  population) {
    this->population = population;
}

void City::printInfo() const {
    std::cout<< name << " " << code << " " << population << "\n";
}
