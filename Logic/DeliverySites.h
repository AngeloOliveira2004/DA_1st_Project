#ifndef PROJETO_DELIVERYSITES_H
#define PROJETO_DELIVERYSITES_H

#include "stdafx.h"

enum class Sinks {
    FIRE_STATION,
    CITY
};

class Fire_Station {
private:
    Sinks type;

    uint8_t id;
    std::string code;

public:
    Fire_Station(uint8_t id , std::string code);

    // Getters
    [[nodiscard]] std::string getCode() const;
    [[nodiscard]] u_int8_t getId() const;

    // Setters
    void setCode(const std::string& code);
    void setId(u_int8_t id);
};

class City{
private:
    Sinks type;

    std::string name;
    std::string code;
    u_int8_t id;
    u_int16_t demand;
    u_int16_t population;
public:
    City(std::string name, std::string code, u_int8_t id,
         u_int16_t demand, u_int16_t population);

    // Getters
    [[nodiscard]] std::string getName() const;
    [[nodiscard]] std::string getCode() const;
    [[nodiscard]] u_int8_t getId() const;
    [[nodiscard]] u_int16_t  getDemand() const;
    [[nodiscard]] u_int16_t  getPopulation() const;

    // Setters
    void setName(const std::string& name);
    void setCode(const std::string& code);
    void setId(u_int8_t id);
    void setDemand(u_int16_t demand);
    void setPopulation(u_int16_t  population);

    void printInfo() const;
};
/*
namespace std {
    template <>
    struct hash<City> {
        size_t operator()(const City& city) const {
            // Use hash of the city code for hashing
            return hash<string>{}(city.getCode());
        }
    };

    template<>
    struct equal_to<City> {
        bool operator()(const City& city1, const City& city2) const {
            // Compare only the city codes for equality
            return city1.getCode() == city2.getCode();
        }
    };
}
*/

#endif //PROJETO_DELIVERYSITES_H
