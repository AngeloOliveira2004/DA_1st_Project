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

    int id;
    std::string code;

public:
    Fire_Station(int id , std::string code);

    // Getters
    [[nodiscard]] std::string getCode() const;
    [[nodiscard]] int getId() const;

    // Setters
    void setCode(const std::string& code);
    void setId(int id);

    void printInfo() const;
};

class City{
private:
    Sinks type;

    std::string name;
    std::string code;
    int id;
    int demand;
    int population;
public:
    City(std::string name, std::string code, int id,
         int demand, int population);

    // Getters
    [[nodiscard]] std::string getName() const;
    [[nodiscard]] std::string getCode() const;
    [[nodiscard]] int getId() const;
    [[nodiscard]] int  getDemand() const;
    [[nodiscard]] int  getPopulation() const;

    // Setters
    void setName(const std::string& name);
    void setCode(const std::string& code);
    void setId(int id);
    void setDemand(int demand);
    void setPopulation(int  population);

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
