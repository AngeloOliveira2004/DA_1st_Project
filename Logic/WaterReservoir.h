//Sink

#include <utility>

#include "string"

#ifndef PROJETO_WATERRESERVATIONS_H
#define PROJETO_WATERRESERVATIONS_H

#include "stdafx.h"

class WaterReservoir {
private:
    std::string name;
    std::string municipality;
    std::string code;
    int id;
    int maxDelivery;
public:
    WaterReservoir(std::string  name,
                   std::string  municipality,
                   std::string  code,
                   int id,
                   int maxDelivery)
            : name(std::move(name)), municipality(std::move(municipality)), code(std::move(code)), id(id), maxDelivery(maxDelivery) {}

    // Getters
    std::string getName() const { return name; }
    std::string getMunicipality() const { return municipality; }
    std::string getCode() const { return code; }
    int getId() const { return id; }
    int getMaxDelivery() const { return maxDelivery; }

    // Setters
    void setName(const std::string& name) { this->name = name; }
    void setMunicipality(const std::string& municipality) { this->municipality = municipality; }
    void setCode(const std::string& code) { this->code = code; }
    void setId(int id) { this->id = id; }
    void setMaxDelivery(int maxDelivery) { this->maxDelivery = maxDelivery; }

    void printInfo()
    {
        std::cout << name << " " << municipality << " " << code << " "<<maxDelivery <<  " " << id<<"\n";
    }
};

namespace std {
    template <>
    struct hash<WaterReservoir> {
        size_t operator()(const WaterReservoir& waterReservoir) const {
            // Use hash of the city code for hashing
            return hash<string>{}(waterReservoir.getCode());
        }
    };

    template<>
    struct equal_to<WaterReservoir> {
        bool operator()(const WaterReservoir& waterReservoir1, const WaterReservoir& waterReservoir2) const {
            // Compare only the city codes for equality
            return waterReservoir1.getCode() == waterReservoir1.getCode();
        }
    };
}
#endif //PROJETO_WATERRESERVATIONS_H
