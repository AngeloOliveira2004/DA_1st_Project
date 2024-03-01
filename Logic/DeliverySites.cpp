#include "DeliverySites.h"

#include <utility>

// Fire_Station constructor
Fire_Station::Fire_Station(uint8_t id , std::string code)
        : type(Sinks::FIRE_STATION), id(id), code(std::move(code)) {}

std::string Fire_Station::getCode() const {
    return code;
}

u_int8_t Fire_Station::getId() const {
    return id;
}

void Fire_Station::setCode(const std::string& code) {
    this->code = code;
}

void Fire_Station::setId(u_int8_t id) {
    this->id = id;
}

// City constructor
City::City(std::string name, std::string  code, u_int8_t id,
           u_int16_t demand, u_int16_t population)
        : type(Sinks::CITY), name(std::move(name)), code(std::move(code)),
          id(id), demand(demand), population(population) {}

// City getters
std::string City::getName() const {
    return name;
}

std::string City::getCode() const {
    return code;
}

u_int8_t City::getId() const {
    return id;
}

u_int16_t  City::getDemand() const {
    return demand;
}

u_int16_t  City::getPopulation() const {
    return population;
}

// City setters
void City::setName(const std::string& name) {
    this->name = name;
}

void City::setCode(const std::string& code) {
    this->code = code;
}

void City::setId(u_int8_t id) {
    this->id = id;
}

void City::setDemand(u_int16_t demand) {
    this->demand = demand;
}

void City::setPopulation(u_int16_t  population) {
    this->population = population;
}

void City::printInfo() const {
    std::cout<< name << " " << code << " " << population << "\n";
}
